#include "physics/bullet_physics.hpp"

#include "btBulletDynamicsCommon.h"

namespace skeletor {
namespace physics {

BulletPhysics::~BulletPhysics()
{
        exitPhysics();
}

void BulletPhysics::initPhysics()
{
        // create all the objects
        m_collisionConf = new btDefaultCollisionConfiguration();
        m_dispatcher = new btCollisionDispatcher(m_collisionConf);
        m_overlappingPairCache = new btDbvtBroadphase();
        m_solver = new btSequentialImpulseConstraintSolver;
        m_dynamicsWorld = new btDiscreteDynamicsWorld(
                        m_dispatcher, m_overlappingPairCache, m_solver,
                        m_collisionConf); 

        // set gravity 9.81 m/s^2
        m_dynamicsWorld->setGravity(btVector3(.0f,-9.81f,.0f));

}

void BulletPhysics::exitPhysics()
{
        // delete all the objects
        delete m_dynamicsWorld;
        delete m_solver;
        delete m_overlappingPairCache;
        delete m_dispatcher;
        delete m_collisionConf;
}

}; // namespace physics
}; // namespace skeletor
