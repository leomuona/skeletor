#include "util/string.hpp"

#include <iterator>

namespace skeletor {
namespace util {

std::vector<std::string> stringSplit(const std::string &s)
{
	std::stringstream ss(s);
	std::istream_iterator<std::string> begin(ss);
	std::istream_iterator<std::string> end;
	std::vector<std::string> vstrings(begin, end);
	return vstrings;
}

}; // namespace util
}; // namespace skeletor
