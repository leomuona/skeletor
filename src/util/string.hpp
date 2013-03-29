#ifndef UTIL_STRING_HPP
#define UTIL_STRING_HPP

#include <string>
#include <sstream>
#include <vector>

namespace skeletor {
namespace util {

/**
 * Splits the given string into substrings by given delim.
 *
 * @param string to split
 * @param delim to use for splitting
 * @param vector to save the elements.
 *
 * @return reference to given vector
 */
std::vector<std::string> &split(
const std::string &s, char delim, std::vector<std::string> &elems);

/**
 * Splits the given string into substrings by given delim.
 *
 * @param string to split
 * @param delim to use for splitting.
 *
 * @return splitted string in vector
 */
std::vector<std::string> split(const std::string &s, char delim);

/**
 * Removes the first character from string if it equals given char.
 *
 * @param string
 * @param char to remove
 */
void removeIfFirst(std::string &s, char c);

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

/**
 * Test if string begins with given string
 *
 * @param string to test
 * @param string to begin with
 *
 * @return true/false
 */
bool beginsWith(const std::string &s, const std::string &begins);

/**
 * Transforms the string to lowercase
 */
void toLower(std::string &s);

}; // namespace util
}; // namespace skeletor

#endif // UTIL_STRING_HPP
