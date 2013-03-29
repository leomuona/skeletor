#include "animation/keyframe.hpp"

namespace skeletor {
namespace animation {

KeyFrame::KeyFrame(float time, const math::Mat4x4f &transform)
	: m_time(time)
	, m_transform(transform)
{
}

float KeyFrame::getTime() const
{
	return m_time;
}

math::Mat4x4f KeyFrame::getTransform() const
{
	return m_transform;
}

}; // namespace animation
}; // namespace skeletor
