#include "util/string.hpp"

#include <algorithm>

namespace skeletor {
namespace util {

std::vector<std::string> &split(
const std::string &s, char delim, std::vector<std::string> &elems)
{
	std::stringstream ss(s);
	std::string item;
	while(std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

std::vector<std::string> split(const std::string &s, char delim)
{
	std::vector<std::string> elems;
	return split(s, delim, elems);
}

void removeIfFirst(std::string &s, char c)
{
	if (s.size() > 0 && s[0] == c) {
		s.erase(s.begin());
	}
}

bool beginsWith(const std::string &s, const std::string &begins)
{
	return (s.compare(0, begins.length(), begins) == 0);
}

void toLower(std::string &s)
{
	std::transform(s.begin(), s.end(), s.begin(), ::tolower);
}

}; // namespace util
}; // namespace skeletor
