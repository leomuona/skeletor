#ifndef KEYFRAME_HPP
#define KEYFRAME_HPP

#include "math/mat4x4.hpp"

namespace skeletor {
namespace animation {

/**
 * KeyFrames are joint specific transformations at a given time.
 *
 * If every joint is transformed to keyframe at given time, it makes a pose
 * that the given keyframe presents.
 */
class KeyFrame
{
private:
	// time of this transformation
	float m_time;

	// indepent rotation values of x, y and z.
	math::Vec3f m_rotate;

	// translation of the KeyFrame.
	math::Vec3f m_translate;

	// scaling on x, y, z axes
	math::Vec3f m_scale;

	// transformation of the keyframe
	// matrix representation of the transformation, t * rotZ * rotY * rotX
	math::Mat4x4f m_transform;

public:
	/**
	 * Constructor.
	 *
	 * @param time
	 * @param matrix transformation.
	 */
	KeyFrame(float time, const math::Mat4x4f &transform);

	/**
	 * Get the time of the keyframe.
	 * @param time (seconds)
	 */
	float getTime() const;

	/**
	 * Get the transformation of the keyframe.
	 * This is copy of the transform matrix given at constructor.
	 * @return transformation matrix
	 */
	math::Mat4x4f getTransform() const;

	/**
	 * Get translations of the keyframe.
	 * @return translation vector
	 */
	math::Vec3f getTranslate() const;

	/**
	 * Get rotation of the keyframe.
	 * @return rotate vector
	 */
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
