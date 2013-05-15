#ifndef PHYSICS_INTERFACE_HPP
#define PHYSICS_INTERFACE_HPP

#include "math/vec3.hpp"
#include "math/mat4x4.hpp"

namespace skeletor {

namespace animation {
class SkeletonPose;
}; // namespace animation
namespace physics {

/**
 * Physics interface. Use whatever physics library you want.
 */
class PhysicsInterface
{
public:
        /**
         * Initialize physics. Preferrably done in constructor.
         */
        virtual void initPhysics() = 0;

        /**
         * Exit physics. Preferrably done in destructor.
         */
        virtual void exitPhysics() = 0;
        
        /**
         * Create unique box to be simulated.
         */
        virtual void createUniqueBox(unsigned int id,
                                     const math::Vec3f &location,
                                     float edge, float mass) = 0;
        
        /**
         * Create skeleton from skeletor's skeletonPose.
         */
        virtual void createSkeleton(unsigned int id,
                        animation::SkeletonPose *skeletonPose,
                        const math::Mat4x4f &transMat) = 0;

        /**
         * Do one simulation, normally this is added to main loop.
         */
        virtual void stepSimulation(float timeStep, int maxSubSteps = 1,
                                    float fixedTimeStep = (1.f/60.f)) = 0;
};

}; // namespace physics
}; // namespace skeletor

#endif // PHYSICS_INTERFACE_HPP
