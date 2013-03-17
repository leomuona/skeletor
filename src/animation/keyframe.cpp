#include "animation/keyframe.hpp"

namespace skeletor {
namespace animation {

KeyFrame::KeyFrame(float time, const math::Mat4x4f &transform)
	: m_time(time)
	, m_transform(transform)
{
}

}; // namespace animation
}; // namespace skeletor
