#include "physics/bullet_physics.hpp"

#include "animation/skeleton_pose.hpp"
#include "physics/bullet_opengl_debug_drawer.hpp"
#include "physics/bullet_ragdoll.hpp"

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
        std::map<unsigned int, BulletRagdoll*>::iterator it;
        for (it = m_ragdolls.begin(); it != m_ragdolls.end(); it++) {
                delete it->second;
        }
        m_ragdolls.clear();

        // search and destroy rigidbodies
        for (int i=m_dynamicsWorld->getNumCollisionObjects()-1; i>=0; --i) {
                btCollisionObject *obj = 
                                m_dynamicsWorld->getCollisionObjectArray()[i];
                btRigidBody *body = btRigidBody::upcast(obj);
                if (body && body->getMotionState()) {
                        delete body->getMotionState();
                }
                m_dynamicsWorld->removeCollisionObject(obj);
                delete obj;
        }
        m_boxes.clear();
        
        // search and destroy collisionshapes
        for (int i=0; i<m_collisionShapes.size(); ++i) {
                btCollisionShape *shape = m_collisionShapes[i];
                delete shape;
        }
        m_collisionShapes.clear();

        if (m_debugDrawer != NULL) {
                delete m_debugDrawer;
        }

        // delete rest of the stuff
        delete m_dynamicsWorld;
        delete m_solver;
        delete m_overlappingPairCache;
        delete m_dispatcher;
        delete m_collisionConf;
}

void BulletPhysics::createSkeleton(unsigned int id,
                                   animation::SkeletonPose *skeletonPose,
                                   const math::Mat4x4f &transMat)
{
        BulletRagdoll *ragdoll = new BulletRagdoll(id, m_dynamicsWorld,
                                                   skeletonPose, transMat);
        m_ragdolls[id] = ragdoll;
}

BulletRagdoll* BulletPhysics::getSkeletonRagdoll(unsigned int id)
{
        return m_ragdolls[id];
}

btCollisionObject* BulletPhysics::getBoxCollisionObject(unsigned int id)
{
        return m_boxes[id];
}

void BulletPhysics::stepSimulation(float timeStep, int maxSubSteps,
                            float fixedTimeStep)
{
        m_dynamicsWorld->stepSimulation(timeStep, maxSubSteps, fixedTimeStep);
}

void BulletPhysics::createUniqueBox(unsigned int id,
                                    const math::Vec3f &location,
                                    float edge, float mass)
{
        btBoxShape *shape = new btBoxShape(btVector3(edge, edge, edge));
        m_collisionShapes.push_back(shape);
        
        btTransform boxTransform;
        boxTransform.setIdentity();
        float x = location.x - edge/2;
        float y = location.y - edge/2;
        float z = location.z - edge/2;
        boxTransform.setOrigin(btVector3(x, y, z));
        
        // rigidbody is dynamic (not static) if mass is non zero
        bool isDynamic = (mass != 0.f);
        btVector3 localInertia(0,0,0);
        if (isDynamic) {
                shape->calculateLocalInertia(mass, localInertia);
        }
        
        // create motion state and rigid body
        btDefaultMotionState *myMotionState = 
                        new btDefaultMotionState(boxTransform);
        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,
                        myMotionState, shape, localInertia);
        btRigidBody *body = new btRigidBody(rbInfo);

        m_dynamicsWorld->addRigidBody(body);
        m_boxes[id] = body;
}

void BulletPhysics::initOpenGLDebugDrawer(int debugMode)
{
        m_debugDrawer = new BulletOpenGLDebugDrawer();
        m_debugDrawer->setDebugMode(debugMode);
        m_dynamicsWorld->setDebugDrawer(m_debugDrawer);
}

void BulletPhysics::debugDrawWorld()
{
        m_dynamicsWorld->debugDrawWorld();
}

}; // namespace physics
}; // namespace skeletor
