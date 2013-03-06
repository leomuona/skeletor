#ifndef SKELETON_HPP
#define SKELETON_HPP

#include "animation/joint.hpp"

#include <vector>

namespace skeletor {
namespace animation {

class Skeleton
{
	std::vector<Joint> m_joints;
};

}; // namespace animation
}; // namespace skeletor

#endif // SKELETON_HPP
