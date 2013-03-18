#ifndef PHYSICS_INTERFACE_HPP
#define PHYSICS_INTERFACE_HPP

namespace skeletor {
namespace physics {

class PhysicsInterface
{
public:
        virtual void initPhysics() = 0;
        virtual void exitPhysics() = 0;
};

}; // namespace physics
}; // namespace skeletor

#endif // PHYSICS_INTERFACE_HPP
