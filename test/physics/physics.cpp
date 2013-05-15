#include "test/physics/physics.hpp"

#include "test/physics/bullet_physics.hpp"
#include "test/physics/bullet_objects_converter.hpp"

#include <stdio.h>

namespace skeletor {
namespace test {
namespace physics {

int testPhysics(const std::string &test)
{
	if (test == "bullet_physics") {
		return testBulletPhysics();
        } else if (test == "bullet_objects_converter") {
                return testBulletObjectsConverter();
	} else {
		printf("invalid physics test: %s\n", test.c_str());
		return 1;
	}
}

}; // namespace physics
}; // namespace test
}; // namespace skeletor
