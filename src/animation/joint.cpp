#include "animation/joint.hpp"

namespace skeletor {
namespace animation {

Joint::Joint(Joint *parent, const math::Mat4x4f &localMatrix)
	: m_parent(parent)
	, m_localMatrix(localMatrix)
{
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

std::pair<KeyFrame, KeyFrame> Joint::find(float time) const
{
	// first set the time within the min-max times.
	float maxtime = m_keyframes[m_keyframes.size()-1].getTime();
	time = fmod(time, maxtime);

	int x = 0;
	int y = 0;

	// find the first value that is less (or equal).
	// then find the first value that is more (or equal).
	for (int i=0; i<m_keyframes.size(); ++i) {
		if (m_keyframes[i].getTime() >= time) {
			x = i;
			break;
		}
	}

	for (int i=m_keyframes.size(); i>=0; --i) {
		if (m_keyframes[i].getTime() <= time) {
			y = i;
			break;
		}
	}

	return std::pair<KeyFrame, KeyFrame>(m_keyframes[x], m_keyframes[y]);
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

float Joint::getMaxTime() const
{
	if (m_keyframes.empty()) {
		return 0;
	}

	return m_keyframes[m_keyframes.size()-1].getTime();
}

void Joint::setBindPoseMatrix(const math::Mat4x4f &bindPoseMatrix)
{
	m_bindPoseMatrix = bindPoseMatrix;
	m_invBindPoseMatrix = bindPoseMatrix.getInverse();
}

}; // namespace animation
}; // namespace skeletor
