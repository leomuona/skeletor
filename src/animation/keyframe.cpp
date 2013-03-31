#include "animation/keyframe.hpp"

namespace skeletor {
namespace animation {

KeyFrame::KeyFrame(
float time, const math::Mat4x4f &transform,
const math::Vec3f &rotate, const math::Vec3f &translate)
	: m_time(time)
	, m_transform(transform)
	, m_rotate(rotate)
	, m_translate(translate)
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

math::Vec3f KeyFrame::getTranslate() const
{
	return m_translate;
}

math::Vec3f KeyFrame::getRotate() const
{
	return m_rotate;
}

KeyFrame KeyFrame::lerp(const KeyFrame &other, float time) const
{
	// which is smaller?
	const KeyFrame &first  = (this->m_time < other.getTime()) ? *this : other;
	const KeyFrame &second = (this->m_time > other.getTime()) ? *this : other;
	float d_time           = second.getTime() - first.getTime();
	float factor           = 1.0f / d_time;
	float t                = factor * (time - first.getTime());

	math::Vec3f lerp_rot   = first.getRotate().lerp(second.getRotate(), t);
	math::Vec3f lerp_trans = first.getTranslate().lerp(second.getTranslate(), t);

	math::Mat4x4f translate, rotateX, rotateY, rotateZ;
	translate.translate(lerp_trans);
	rotateX.rotate(math::Vec3f(1, 0, 0), lerp_rot.x);
	rotateY.rotate(math::Vec3f(0, 1, 0), lerp_rot.y);
	rotateZ.rotate(math::Vec3f(0, 0, 1), lerp_rot.z);

	return KeyFrame(time, translate * rotateZ * rotateY * rotateX, lerp_rot, lerp_trans);
}

}; // namespace animation
}; // namespace skeletor
