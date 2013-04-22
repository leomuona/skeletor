#include "physics/bullet_ragdoll.hpp"

#include "animation/skeleton_pose.hpp"
#include "animation/skeleton.hpp"
#include "animation/joint.hpp"

#include "btBulletDynamicsCommon.h"

namespace skeletor {
namespace physics {

BulletRagdoll::BulletRagdoll(unsigned int id, btDynamicsWorld *ownerWorld,
                             animation::SkeletonPose *skeletonPose)
{
        m_id = id;
        m_ownerWorld = ownerWorld;
        animation::Skeleton skeleton = skeletonPose->getSkeleton();
        animation::Joint rootJoint = skeleton.getRootJoint();
        // create all joints recursively
        createJointRecursively(&rootJoint);
}

BulletRagdoll::~BulletRagdoll()
{
        int i;
        // delete joints
        for (i=0; i < m_joints.size(); ++i) {
                m_ownerWorld->removeConstraint(m_joints[i]);
                delete m_joints[i];
        }
        m_joints.clear();

        // delete bodies
        for (i=0; i < m_bodies.size(); ++i) {
                m_ownerWorld->removeRigidBody(m_bodies[i]);
                delete m_bodies[i]->getMotionState();
                delete m_bodies[i];
        }
        m_bodies.clear();

        // delete shapes
        for (i=0; i < m_shapes.size(); ++i) {
                delete m_shapes[i];
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

std::vector<btCollisionShape*> BulletRagdoll::getShapes() const
{
        return m_shapes;
}

void BulletRagdoll::setShapes(std::vector<btCollisionShape*> shapes)
{
        m_shapes = shapes;
}

std::vector<btRigidBody*> BulletRagdoll::getBodies() const
{
        return m_bodies;
}

void BulletRagdoll::setBodies(std::vector<btRigidBody*> bodies)
{
        m_bodies = bodies;
}

std::vector<btTypedConstraint*> BulletRagdoll::getJoints() const
{
        return m_joints;
}

void BulletRagdoll::setJoints(std::vector<btTypedConstraint*> joints)
{
        m_joints = joints;
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

void BulletRagdoll::createJointRecursively(animation::Joint *joint)
{
        // TODO: create joint and call child joints recursively.
}

}; // namespace physics
}; // namespace skeletor

