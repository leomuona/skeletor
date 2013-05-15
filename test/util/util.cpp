#include "test/util/util.hpp"
#include "test/util/string.hpp"
#include "test/util/search.hpp"

#include <stdio.h>

namespace skeletor {
namespace test {
namespace util {

int testUtil(const std::string &test)
{
	if (test == "string") {
		return testString();
	} else if (test == "search") {
		return testSearch();
	} else {
		printf("invalid util test: %s\n", test.c_str());
		return 1;
	}
}

}; // util
}; // test
}; // skeletor
