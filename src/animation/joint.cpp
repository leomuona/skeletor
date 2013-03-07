#include "animation/joint.hpp"

namespace skeletor {
namespace animation {

Joint::Joint(Joint *parent, const math::Mat4x4f &localMatrix, const std::string &name)
	: m_parent(parent)
	, m_localMatrix(localMatrix)
	, m_name(name)
{
	if (parent != NULL) {
		m_bindPoseMatrix = m_localMatrix * parent->getLocalMatrix();
	} else {
		m_bindPoseMatrix = m_localMatrix;
	}

	m_invBindPoseMatrix = m_bindPoseMatrix.getInverse();
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

const math::Mat4x4f &Joint::getLocalMatrix() const
{
	return m_localMatrix;
}

math::Mat4x4f &Joint::getLocalMatrix()
{
	return m_localMatrix;
}

const math::Mat4x4f &Joint::getBindPoseMatrix() const
{
	return m_bindPoseMatrix;
}

math::Mat4x4f &Joint::getBindPoseMatrix()
{
	return m_bindPoseMatrix;
}

const math::Mat4x4f &Joint::getInvBindPoseMatrix() const
{
	return m_invBindPoseMatrix;
}

math::Mat4x4f &Joint::getInvBindPoseMatrix()
{
	return m_invBindPoseMatrix;
}

}; // namespace animation
}; // namespace skeletor
