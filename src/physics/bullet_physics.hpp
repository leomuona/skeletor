#ifndef BULLET_PHYSICS_HPP
#define BULLET_PHYSICS_HPP

#include "physics/physics_interface.hpp"
#include "math/vec3.hpp"

#include <vector>
#include <map>

class btBroadphaseInterface;
class btCollisionDispatcher;
class btCollisionObject;
class btCollisionShape;
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

        /**
         * Create unique box with given values.
         * Use this only if there is only one box like this to be created.
         * @param location - where is the center of box
         * @param edge - edge length of box
         * @param mass - mass of box, with zero object is static.
         */
        void createUniqueBox(unsigned int id, const math::Vec3f &location,
                             float edge, float mass);

        btCollisionObject* getCollisionObject(unsigned int id);
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

        /**
         * Collision shapes, kept pointers for deletion.
         */
        std::vector<btCollisionShape*> m_collisionShapes;

        /**
         * We need a body map, to keep track of body objects.
         */
        std::map<unsigned int, btCollisionObject*> m_bodyMap;
};

}; // namespace physics
}; // namespace skeletor

#endif // BULLET_PHYSICS_HPP
