#ifndef COLLADA_HPP
#define COLLADA_HPP

#include <string>

namespace skeletor {
namespace animation {

class Skeleton;

class Collada
{
public:

	/**
	 * Parses the collada file and returns the constructed skeleton.
	 *
	 * @param file to load.
	 * @return skeleton constructed from collada file.
	 */
	static Skeleton *loadSkeleton(const std::string &file);
};

}; // namespace animation
}; // namespace skeletor

#endif // COLLADA_HPP
