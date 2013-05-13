#include "test/player.hpp"

#include "src/player.hpp"
#include "math/vec2.hpp"
#include "math/vec3.hpp"

#include <assert.h>
#include <iostream>

namespace skeletor {
namespace test {

int testPlayerMovement()
{
	/* first we do this:
	 *
	 *    ->
	 *     |
	 *     |
	 * O -->
	 *
	 * and then, direction turn 90 degrees
	 *                 |
	 *    ->           u
	 *         to                   |
	 *                      and     |
	 * O           O            O<--u
	 *
	 * so back to origo O
	 */


	using namespace skeletor;
	using namespace skeletor::math;

	Player player(Vec3f(0, 0, 0), Vec3f(1, 0, 0));
	float movementSpeed = player.getMovementSpeed();

	Mat4x4f a = player.getTransformation();

	player.move(Vec2f(0, 1), 1.0/movementSpeed);
	assert(player.getPosition() == Vec3f(1, 0, 0));

	player.move(Vec2f(1, 0), 1.0/movementSpeed);
	std::cout << player.getPosition();
	assert(player.getPosition() == Vec3f(1, 0, -1));

	Mat4x4f b = player.getTransformation();

	// should be same expect for 12 and 14
	for (int i=0; i<16; ++i) {
		if (i != 12 && i != 14) {
			assert(a.m[i] == b.m[i]);
		}
	}

	// now, rotate camera by 90 degrees, or M_PI/2 radians
	player.onCameraMotion(Vec2f(0, M_PI/2), 0);
	// and walk back to origo
	player.move(Vec2f(0, 1), 1.0/movementSpeed);
	player.move(Vec2f(1, 0), 1.0/movementSpeed);
	std::cout << player.getPosition();

	assert(player.getPosition() == Vec3f(0, 0, 0));

	return 0;
}

}; // namespace test
}; // namespace skeletor
