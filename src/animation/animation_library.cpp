#include "animation/animation_library.hpp"
#include "animation/parse.hpp"
#include "animation/skeleton.hpp"
#include "animation/skeleton_pose.hpp"

#include <iostream>

namespace skeletor {
namespace animation {

AnimationLibrary *AnimationLibrary::m_instance = NULL;

AnimationLibrary::AnimationLibrary()
	: m_crossFadeTime(0.3)
{
}

AnimationLibrary *AnimationLibrary::instance()
{
	if (m_instance == NULL) {
		m_instance = new AnimationLibrary;
	}

	return m_instance;
}

Skeleton *AnimationLibrary::getSkeleton(const std::string &id)
{
	std::map<std::string, Skeleton *>::iterator it = m_animations.find(id);
	if (it == m_animations.end()) {
		std::pair<std::map<std::string, Skeleton *>::iterator, bool> ret;
		ret = m_animations.insert(
			std::pair<std::string, Skeleton *>(id, loadSkeleton(id)));
		it = ret.first;
	}
	return it->second;
}

Skeleton *AnimationLibrary::loadSkeleton(const std::string &path)
{
	std::cout << "Loading skeleton/animations from " << path << std::endl;
	return Parse::load(path);
}

}; // namespace animation
}; // namespace skeletor
