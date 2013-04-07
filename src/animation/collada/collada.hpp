#ifndef COLLADA_HPP
#define COLLADA_HPP

#include <string>

namespace skeletor {
namespace animation {
class Skeleton;
namespace collada {

/**
 * Parses the collada file and returns the constructed skeleton.
 *
 * @param file to load.
 * @return skeleton constructed from collada file.
 */
Skeleton *loadSkeleton(const std::string &file);

}; // namespace collada
}; // namespace animation
}; // namespace skeletor

#endif // COLLADA_HPP
