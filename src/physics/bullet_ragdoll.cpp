#include "physics/bullet_ragdoll.hpp"

#include "animation/skeleton_pose.hpp"
#include "animation/skeleton.hpp"
#include "animation/joint.hpp"
#include "math/math.hpp"

#include "btBulletDynamicsCommon.h"
#include <cmath>

namespace skeletor {
namespace physics {

BulletRagdoll::BulletRagdoll(unsigned int id, btDynamicsWorld *ownerWorld,
                             animation::SkeletonPose *skeletonPose,
                             const math::Mat4x4f &transMat)
{
        m_id = id;
        m_ownerWorld = ownerWorld;
        m_boneRadius = 0.05f;

        animation::Skeleton skeleton = skeletonPose->getSkeleton();       
        animation::Joint rootJoint = skeleton.getRootJoint();
        
        // create all joints recursively
        createJointRecursively(&rootJoint, transMat, skeletonPose);
}

BulletRagdoll::~BulletRagdoll()
{
        // delete joints
        std::map<std::string, btTypedConstraint*>::iterator jit;
        for (jit = m_joints.begin(); jit != m_joints.end(); ++jit) {
                m_ownerWorld->removeConstraint(jit->second);
                delete jit->second;
        }
        m_joints.clear();

        // clear bodies, delete is done in bullet physics destructor
        m_bodies.clear();

        // delete shapes
        std::map<std::string, btCollisionShape*>::iterator sit;
        for (sit = m_shapes.begin(); sit != m_shapes.end(); ++sit) {
                delete sit->second;
        }
        m_shapes.clear();
}

unsigned int BulletRagdoll::getId() const
{
        return m_id;
}

void BulletRagdoll::setId(unsigned int id)
{
        m_id = id;
}

btDynamicsWorld* BulletRagdoll::getOwnerWorld() const
{
        return m_ownerWorld;
}

void BulletRagdoll::setOwnerWorld(btDynamicsWorld *world)
{
        m_ownerWorld = world;
}

std::map<std::string, btCollisionShape*> BulletRagdoll::getShapes() const
{
        return m_shapes;
}

std::map<std::string, btRigidBody*> BulletRagdoll::getBodies() const
{
        return m_bodies;
}

std::map<std::string, btTypedConstraint*> BulletRagdoll::getJoints() const
{
        return m_joints;
}

btRigidBody* BulletRagdoll::createRigidBody(float mass,
       const btTransform &startTransform, btCollisionShape *shape)
{
        bool isDynamic = (mass != 0.f);
        btVector3 localInertia(0, 0, 0);
        if (isDynamic) {
                shape->calculateLocalInertia(mass, localInertia);
        }

        btDefaultMotionState *motionState =
                new btDefaultMotionState(startTransform);
        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState,
                                                        shape, localInertia);
        btRigidBody *body = new btRigidBody(rbInfo);
        m_ownerWorld->addRigidBody(body);

        return body;
}

void BulletRagdoll::createJointRecursively(animation::Joint *joint,
        math::Mat4x4f matrix, animation::SkeletonPose *skeletonPose)
{
        if (joint == NULL) {
                return;
        }
        matrix = ((matrix * joint->getBindPoseMatrix()) 
                  * skeletonPose->getTransform(joint));
        animation::Joint *parent = joint->getParent();
        if (parent != NULL) {
                // Calculate the length of bone
                math::Mat4x4f t = joint->getLocalMatrix();
                float bonelen = std::sqrt(std::pow(t.m[12], 2)
                                        + std::pow(t.m[13], 2)
                                        + std::pow(t.m[14], 2));
                btCapsuleShape *shape = new btCapsuleShape(m_boneRadius,
                                                           bonelen);
                m_shapes.insert(std::pair<std::string, btCollisionShape*>(
                                        joint->getID(), shape));
                // NOTE: Maybe mass should be bone specified in future?
                float mass = bonelen * M_PI * std::pow(m_boneRadius, 2);

                btTransform transform;
                transform.setFromOpenGLMatrix(matrix.m);
                // NOTE: Is the body created to center of mass or at the edge?
                btRigidBody *body = createRigidBody(mass, transform, shape);
                m_bodies.insert(std::pair<std::string, btRigidBody*>(
                                        joint->getID(), body));
                // Set damping
                body->setDamping(0.05f, 0.85f);

                // Create joint constraint: A = parent, B = this
                btTransform localA, localB;
                math::Mat4x4f parentMatrix = parent->getLocalMatrix()*(-1.0f);
                localA.setFromOpenGLMatrix(parentMatrix.m);
                localB.setFromOpenGLMatrix(joint->getLocalMatrix().m);
                
                animation::ConstraintData cdata = joint->getConstraintData();
                if (cdata.type == animation::ConstraintData::CONE_TWIST
                                && m_bodies[parent->getID()] != NULL) {
                        btConeTwistConstraint *coneC;
                        btRigidBody *parentBody = m_bodies[parent->getID()];
                        coneC = new btConeTwistConstraint(*parentBody, *body,
                                                          localA, localB);
                        coneC->setLimit(cdata.swing1Angle, cdata.swing2Angle,
                                        cdata.twistAngle);
                        m_ownerWorld->addConstraint(coneC, true);
                        m_joints.insert(std::pair<std::string,
                                btTypedConstraint*>(joint->getID(), coneC)); 
                }
        }
        
        std::vector<animation::Joint*> children = joint->getChildren();
        for (int i=0; i < children.size(); ++i) {
                createJointRecursively(children[i], matrix, skeletonPose);
        }
}

}; // namespace physics
}; // namespace skeletor

