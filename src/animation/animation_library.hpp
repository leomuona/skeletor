#ifndef ANIMATION_LIBRARY_HPP
#define ANIMATION_LIBRARY_HPP

#include <map>
#include <string>

namespace skeletor {
namespace animation {

class Skeleton;
class SkeletonPose;

/**
 * Class that contains all the skeletons and animations.
 *
 * Animations should have an unique string identifier, should be fine to use
 * the filename/path
 */
class AnimationLibrary
{
private:
	std::map<std::string, Skeleton *> m_animations;

	// Singleton instance.
	static AnimationLibrary *m_instance;

	AnimationLibrary();
public:
	/**
	 * Get singleton instance.
	 *
	 * @return singleton instance.
	 */
	static AnimationLibrary *instance();

	/**
	 * Returns the skeleton with given id. If no skeleton has been loaded
	 * with given id, it will load it and add part to m_animations structure.
	 *
	 * @param skeleton unique id.
	 *
	 * @return Skeleton.
	 */
	Skeleton *getSkeleton(const std::string &id);

private:
	/**
	 * Loads the skeleton from the given path.
	 *
	 * @param path of the file to load.
	 */
	Skeleton *loadSkeleton(const std::string &path);
};

}; // namespace animation
}; // namespace skeletor

#endif // ANIMATION_LIBRARY_HPP
