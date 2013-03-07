#ifndef UTIL_STRING_HPP
#define UTIL_STRING_HPP

#include <string>
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

}; // namespace util
}; // namespace skeletor

#endif // UTIL_STRING_HPP
