#include "test/physics/bullet_physics.hpp"

#include "physics/bullet_physics.hpp"

#include "btBulletDynamicsCommon.h"

#include <iostream>

namespace skeletor {
namespace test {
namespace physics {

int testBulletPhysics()
{
        int result = 0;

        using namespace skeletor::physics;
        std::cout << "Starting testBulletPhysics...\n";

        BulletPhysics *bp = new BulletPhysics();
        bp->initPhysics();

        // TODO: What should be tested in addition to initialization and destruction?

        delete bp; // destructor calls exitPhysics()

        std::cout << "testBulletPhysics done with return code " << result << ".\n";
        return result;
}

}; // namespace physics
}; // namespace test
}; // namespace skeletor

