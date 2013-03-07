#include "animation/joint.hpp"

namespace skeletor {
namespace animation {

Joint::Joint(Joint *parent, const math::Mat4x4f &invBindPose, const std::string &name)
	: m_parent(parent)
	, m_invBindPose(invBindPose)
	, m_name(name)
{
}

void Joint::addChild(Joint *child)
{
	m_children.push_back(child);
}

std::string Joint::getName() const
{
	return m_name;
}

const std::vector<Joint *> &Joint::getChildren() const
{
	return m_children;
}

}; // namespace animation
}; // namespace skeletor
