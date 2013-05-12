#include "test/animation/animation.hpp"
#include "test/animation/collada.hpp"

#include <stdio.h>

namespace skeletor {
namespace test {
namespace animation {

int testAnimation(const std::string &test)
{
	if (test == "collada") {
		return testCollada();
	} else {
		printf("invalid animation test: %s\n", test.c_str());
		return 1;
	}
}

}; // animation
}; // test
}; // skeletor
