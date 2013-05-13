#include "test/animation/keyframe.hpp"

#include "animation/keyframe.hpp"
#include "math/mat4x4.hpp"
#include "math/vec3.hpp"

#include <assert.h>
#include <stdio.h>
#include <vector>
#include <iostream>

namespace skeletor {
namespace test {
namespace animation {

int testKeyFrame()
{
	using namespace skeletor::animation;
	using namespace skeletor::math;

	Mat4x4f ma, mb;
	ma.rotate(Vec3f(0, 1, 0), 0.5);
	mb.rotate(Vec3f(0, 1, 0), 1.0);

	KeyFrame a(0, ma);
	KeyFrame b(1.0, mb);

	KeyFrame c = a.lerp(b, 0.5);

	std::cout << "rotate: " << c.getRotate() << std::endl;
	assert(c.getRotate() == Vec3f(0, 0.75, 0));

	return 0;
}

}; // animation
}; // test
}; // skeletor
