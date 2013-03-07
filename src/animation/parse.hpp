#ifndef PARSE_HPP
#define PARSE_HPP

#include <string>

namespace skeletor {
namespace animation {

class Skeleton;

class Parse
{
public:
	static Skeleton *load(const std::string &file);
};

}; // namespace animation
}; // namespace skeletor

#endif // PARSE_HPP
