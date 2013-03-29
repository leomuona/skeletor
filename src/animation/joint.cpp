#include "animation/joint.hpp"

namespace skeletor {
namespace animation {

Joint::Joint(Joint *parent, const math::Mat4x4f &localMatrix)
	: m_parent(parent)
	, m_localMatrix(localMatrix)
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

void Joint::setName(const std::string &name)
{
	m_name = name;
}

std::string Joint::getName() const
{
	return m_name;
}

void Joint::setSID(const std::string &sid)
{
	m_sid = sid;
}

std::string Joint::getSID() const
{
	return m_sid;
}

void Joint::setID(const std::string &id)
{
	m_id = id;
}

std::string Joint::getID() const
{
	return m_id;
}

std::vector<KeyFrame> &Joint::getKeyFrames()
{
	return m_keyframes;
}

const std::vector<KeyFrame> &Joint::getKeyFrames() const
{
	return m_keyframes;
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
