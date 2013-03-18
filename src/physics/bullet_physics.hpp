#ifndef BULLET_PHYSICS_HPP
#define BULLET_PHYSICS_HPP

#include "physics/physics_interface.hpp"

class btBroadphaseInterface;
class btCollisionDispatcher;
class btDefaultCollisionConfiguration;
class btDiscreteDynamicsWorld;
class btSequentialImpulseConstraintSolver;

namespace skeletor {
namespace physics {

class BulletPhysics : public PhysicsInterface
{
public:
        ~BulletPhysics();

        /**
         * Initializes physics engine.
         */
        void initPhysics();

        /**
         * Clean up physics engine. (deletes objectives)
         */
        void exitPhysics();

private:
        /**
         * Holds default collision configuration setup for memory and
         * collision.
         */
        btDefaultCollisionConfiguration *m_collisionConf;
        
        /**
         * Default collision dispatcher.
         */
        btCollisionDispatcher *m_dispatcher;
        
        /**
         * Broadphase used by the world.
         */
        btBroadphaseInterface *m_overlappingPairCache;
        
        /**
         * Default constraint solver.
         */
        btSequentialImpulseConstraintSolver *m_solver;
        
        /**
         * The world.
         */
        btDiscreteDynamicsWorld *m_dynamicsWorld;

};

}; // namespace physics
}; // namespace skeletor

#endif // BULLET_PHYSICS_HPP
