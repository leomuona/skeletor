#include "physics/bullet_objects_converter.hpp"

#include "animation/box.hpp"
#include "math/vec3.hpp"
#include "math/mat4x4.hpp"
#include "btBulletDynamicsCommon.h"

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
                btTransform bodyTransform;
                body->getMotionState()->getWorldTransform(bodyTransform);
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

}; // namespace physics
}; // namespace skeletor
