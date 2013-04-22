#ifndef PHYSICS_INTERFACE_HPP
#define PHYSICS_INTERFACE_HPP

#include "math/vec3.hpp"

namespace skeletor {

namespace animation {
class SkeletonPose;
}; // namespace animation
namespace physics {

class PhysicsInterface
{
public:
        virtual void initPhysics() = 0;
        virtual void exitPhysics() = 0;
        virtual void createUniqueBox(unsigned int id,
                                     const math::Vec3f &location,
                                     float edge, float mass) = 0;
        virtual void createSkeleton(unsigned int id,
                        const animation::SkeletonPose &skeletonPose) = 0;
        virtual void stepSimulation(float timeStep, int maxSubSteps = 1,
                                    float fixedTimeStep = (1.f/60.f)) = 0;
};

}; // namespace physics
}; // namespace skeletor

#endif // PHYSICS_INTERFACE_HPP
