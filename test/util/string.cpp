#include "test/util/string.hpp"

#include "src/util/string.hpp"
#include "src/math/math.hpp"

#include <assert.h>
#include <string>
#include <cmath>

namespace skeletor {
namespace test {
namespace util {

int testString()
{
	using namespace skeletor::util;

	std::string a = "a,b,c,d";
	std::vector<std::string> res = split(a, ',');

	assert(res.size() == 4 && res[0] == "a" && res[1] == "b" && res[2] == "c" && res[3] == "d");

	std::string s_pi = "3.141592";
	double pi = lexicalCast<std::string, double>(s_pi);

	assert(std::abs(pi - M_PI) < EPSILON);

	std::string sa = "asdasdasdasd";

	assert(!beginsWith(sa, "asdasdddd"));
	assert(beginsWith(sa, "asdasd"));

	std::string ups = "DSAJKDJSAKL";
	toLower(ups);

	assert(ups == "dsajkdjsakl");

	return 0;
}

}; // namespace util
}; // namespace test
}; // namespace skeletor
