#include "physics/bullet_objects_converter.hpp"

#include "animation/box.hpp"
#include "animation/joint.hpp"
#include "animation/skeleton_pose.hpp"
#include "math/vec3.hpp"
#include "math/mat4x4.hpp"
#include "physics/bullet_ragdoll.hpp"
#include "btBulletDynamicsCommon.h"

#include <map>
#include <string>
#include <iostream>

namespace skeletor {
namespace physics {

void BulletObjectsConverter::convertBox(btCollisionObject *obj, animation::Box *target)
{
        btRigidBody *body = btRigidBody::upcast(obj);
        if (body) {
                // mass
                float mass = body->getInvMass();
                target->setMass(mass);
                // location and rotation matrix
                btTransform bodyTransform = body->getCenterOfMassTransform();
                math::Mat4x4f mat;
                btScalar t_mat[16];
                bodyTransform.getOpenGLMatrix(t_mat);
                for (int i=0; i<16; ++i) {
                        mat.m[i] = (float) t_mat[i];
                }
                target->setMultMatrix(mat);
        } 

        // set edges
        btBoxShape *shape = static_cast<btBoxShape*>(obj->getCollisionShape());
        if (shape) {
                btVector3 btv;
                math::Vec3f mv;
                for (int i = 0; i < 8; ++i) {
                        shape->getVertex(i, btv);
                        mv.x = btv.getX();
                        mv.y = btv.getY();
                        mv.z = btv.getZ();
                        target->setVertex(i, mv);
                }
        }
}

void BulletObjectsConverter::convertSkeleton(BulletRagdoll *obj, animation::SkeletonPose *target)
{
        animation::Joint *rootJoint = &target->getSkeleton().getRootJoint();
        BulletObjectsConverter::convertJointRecursively(obj, rootJoint);
}

void BulletObjectsConverter::convertJointRecursively(BulletRagdoll *ragdoll, animation::Joint *target)
{
        btCapsuleShape* shape;
        btRigidBody* body;
        if (target->getParent()) {
                shape = static_cast<btCapsuleShape*>(
                        ragdoll->getShapes()[target->getID()]);
                body = ragdoll->getBodies()[target->getID()];
                
                btTransform trans = body->getCenterOfMassTransform();
                float halfHeight = (float) shape->getHalfHeight();
                math::Mat4x4f mat;
                btScalar t_mat[16];
                trans.getOpenGLMatrix(t_mat);
                for (int i=0; i<16; ++i) {
                        mat.m[i] = (float) t_mat[i];
                }
                // TODO: what the fuck am I doing?
        
        }

        std::vector<animation::Joint*> children = target->getChildren();
        for (int i=0; i < children.size(); ++i) {
                convertJointRecursively(ragdoll, children[i]);
        }
}

}; // namespace physics
}; // namespace skeletor
