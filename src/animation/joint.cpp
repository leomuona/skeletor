#include "animation/joint.hpp"

namespace skeletor {
namespace animation {

Joint::Joint(Joint *parent, math::Mat4x4f &invBindPose, const std::string &name)
	: m_parent(parent)
	, m_invBindPose(invBindPose)
	, m_name(name)
{
}

void Joint::addChild(Joint *child)
{
	m_children.push_back(child);
}

}; // namespace animation
}; // namespace skeletor
