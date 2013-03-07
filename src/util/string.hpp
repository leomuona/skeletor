#ifndef UTIL_STRING_HPP
#define UTIL_STRING_HPP

#include <string>
#include <sstream>
#include <vector>

namespace skeletor {
namespace util {

/**
 * Splits the given string into substrings by ' '.
 *
 * @param string to split
 * @return splitted string in vector
 */
std::vector<std::string> stringSplit(const std::string &s);

/**
 * Lexical cast.
 *
 * example use:
 * float value = skeletor::util::lexicalCast<std::string, float>("0.55");
 *
 * @param value to case
 * @return casted value
 */
template<typename from, typename to>
static to lexicalCast(from value)
{
	std::stringstream os;
	to ret;

	os << value;
	os >> ret;

	return ret;
}

}; // namespace util
}; // namespace skeletor

#endif // UTIL_STRING_HPP
