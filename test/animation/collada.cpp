#include "test/animation/collada.hpp"

#include "animation/joint.hpp"
#include "animation/parse.hpp"
#include "animation/skeleton.hpp"

#include <assert.h>
#include <stdio.h>
#include <vector>
#include <iostream>

namespace skeletor {
namespace test {
namespace animation {

int testCollada()
{
	using namespace skeletor::animation;
	printf("Loading skeleton from %s\n", "../res/test_cube_simple.dae");
	Skeleton *skeleton = Parse::load("../res/test_cube_simple.dae");

	std::vector<std::pair<Joint *, int> > joints;
	skeleton->preOrder(joints);

	if (joints.size() != 1) {
		printf("invalid number of joints, expected 2, got %lu\n", joints.size());
		return 1;
	}

	Joint *root = joints[0].first;

	if (root->getKeyFrames().size() != 3) {
		printf("invalid number of keyframes, expected 3, got %lu\n", root->getKeyFrames().size());
		return 1;
	}

	KeyFrame a = root->getKeyFrames()[0];
	KeyFrame b = root->getKeyFrames()[1];
	KeyFrame c = root->getKeyFrames()[2];

	double mid = 0.4166666;

	KeyFrame t_ab = a.lerp(b, mid - (mid * 0.5));
	KeyFrame t_bc = b.lerp(c, mid + (mid * 0.5));

	std::cout << t_ab.getTransform();
	std::cout << t_bc.getTransform();

	assert(t_ab.getTransform() == t_bc.getTransform());

	return 0;
}

}; // animation
}; // test
}; // skeletor
