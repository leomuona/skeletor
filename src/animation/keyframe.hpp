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

	// indepent rotation values of x, y and z.
	math::Vec3f m_rotate;

	// translation of the KeyFrame.
	math::Vec3f m_translate;

	// transformation of the keyframe
	// matrix representation of the transformation, t * rotZ * rotY * rotX
	math::Mat4x4f m_transform;

public:
	/**
	 * Constructor.
	 *
	 * @param time
	 * @param matrix transformation.
	 * @param rotation values of axes (in radians)
	 * @param translate
	 */
	KeyFrame(float time, const math::Mat4x4f &transform,
	         const math::Vec3f &rotate, const math::Vec3f &translate);

	float getTime() const;
	math::Mat4x4f getTransform() const;
	math::Vec3f getTranslate() const;
	math::Vec3f getRotate() const;

	/**
	 * Function will linear interpolate this with the other keyframe.
	 *
	 * @param other
	 * @param time - should be between two given times.
	 *
	 * @return linear interpolated KeyFrame between this and the other.
	 */
	KeyFrame lerp(const KeyFrame &other, float time) const;
};

}; // namespace animation
}; // namespace skeletor

#endif // KEYFRAME_HPP
