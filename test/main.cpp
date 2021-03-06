
#include <stdio.h>
#include <string>

#include "test/animation/animation.hpp"
#include "test/player.hpp"
#include "test/util/util.hpp"
#include "test/physics/physics.hpp"

/**
 * Test framework main.
 *
 * All tests should return 0 on success, != 0 on fail
 *
 * @param argc number of arguments
 * @param argv arguments
 *        first argument is ignored (binary name)
 *        second argument tells the subsystem to test
 *        third argument and so on are handled by subsystem.
 */
int main(int argc, char **argv)
{
	if (argc < 2) {
		printf("Usage: %s <subsystem> <arg1> ... <argN>\n", argv[0]);
		return 1;
	}

	using namespace skeletor;
	std::string subsys(argv[1]);

	if (subsys == "animation") {
		return test::animation::testAnimation(argv[2]);
	} else if (subsys == "util") {
		return test::util::testUtil(argv[2]);
	} else if (subsys == "player_movement") {
		return test::testPlayerMovement();
	} else if (subsys == "physics") {
                return test::physics::testPhysics(argv[2]);
        } else {
		printf("invalid subsystem/test: %s\n", subsys.c_str());
		return 1;
	}
}
