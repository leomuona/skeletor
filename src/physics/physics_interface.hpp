#ifndef PHYSICS_INTERFACE_HPP
#define PHYSICS_INTERFACE_HPP

#include "math/vec3.hpp"

namespace skeletor {
namespace physics {

class PhysicsInterface
{
public:
        virtual void initPhysics() = 0;
        virtual void exitPhysics() = 0;
        virtual void createUniqueBox(unsigned int id,
                                     const math::Vec3f &location,
                                     float edge, float mass) = 0;
};

}; // namespace physics
}; // namespace skeletor

#endif // PHYSICS_INTERFACE_HPP
