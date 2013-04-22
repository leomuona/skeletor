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
namespace animation {
class SkeletonPose;
}; // namespace animation
namespace physics {

class BulletRagdoll;

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

        /**
         * Create skeleton with given identifier.
         * 
         * @param id - identifier
         * @param skeletonPose - skeleton pose that is created.
         */
        void createSkeleton(unsigned int id,
                            const animation::SkeletonPose &skeletonPose);
        
        /**
         * Return collision object of given id.
         *
         * @param id identifier of collision object
         * @return btCollisionObject* pointer to collision object
         */
        btCollisionObject* getBoxCollisionObject(unsigned int id);

        /**
         * Proceed simulation over timeStep.
         * Will do bunch of substeps in order of fixedTimeStep.
         *
         * @param timeStep how long the simulation step should last.
         * @param maxSubSteps maximum number of substeps, 0 = disable subdividing.
         * @param fixedTimeStep the delta time of substeps.
         */
        void stepSimulation(float timeStep, int maxSubSteps = 1,
                            float fixedTimeStep = (1.f/60.f));

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
         * We need a body map, to keep track of box bodies.
         */
        std::map<unsigned int, btCollisionObject*> m_boxes;

        /**
         * Map for bullet ragdolls.
         */
        std::map<unsigned int, BulletRagdoll*> m_ragdolls;
};

}; // namespace physics
}; // namespace skeletor

#endif // BULLET_PHYSICS_HPP
