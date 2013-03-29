#ifndef KEYFRAME_HPP
#define KEYFRAME_HPP

#include "math/mat4x4.hpp"

namespace skeletor {
namespace animation {

class KeyFrame
{
private:
	// time of this transformation
	float m_time;

	// transformation of the keyframe
	math::Mat4x4f m_transform;

public:
	KeyFrame(float time, const math::Mat4x4f &transform);

	float getTime() const;
	math::Mat4x4f getTransform() const;
};

}; // namespace animation
}; // namespace skeletor

#endif // KEYFRAME_HPP
