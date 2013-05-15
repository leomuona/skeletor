#ifndef GRAPHICS_CAMERA_HPP
#define GRAPHICS_CAMERA_HPP

#include "math/vec2.hpp"
#include "math/vec3.hpp"
#include "math/mat4x4.hpp"

namespace skeletor {
namespace graphics {

/**
 * Camera for looking around.
 */
class Camera {
private:
        math::Vec3f m_position;
        math::Vec3f m_up;
        math::Vec3f m_lookAt;

	/** \brief magical correction amount. */
	const float m_yUpCorrection;

	const math::Vec3f xAxis;
	const math::Vec3f yAxis;
	const math::Vec3f zAxis;

	math::Mat4x4f m_modelview;

public:
        Camera();

        /**
         * Rotate position around the Y-axis.
         *
         * @param d - the amazing d.
         * @param speed - speed of choice
         */
	void rotatePositionAroundYAxis(float d, float speed);

	/**
	 * On camera motion event.
	 *
	 * @param amount of motion.
	 * @param delta time
	 */
	void onCameraMotion(const math::Vec2f &motion, float dt);

	/**
	 * On camera zoom event.
	 *
	 * @param amount of zoom, e.g 1.1, zoom by 10%
	 */
	void onCameraZoom(float factor);

	/**
	 * Updates the modelview matrix using the position, lookat and up
	 * vectors.
	 *
	 * The Math is fairly simple.
	 */
	void updateModelViewMatrix();

	/**
	 * Get const reference to modelview matrix.
	 *
	 * @return const reference to modelview matrix.
	 */
	const math::Mat4x4f &getModelViewMatrix() const;

        void setPosition(const math::Vec3f &m_position);
        void setLookAt(const math::Vec3f &lookAt);
        void setUp(const math::Vec3f &up);
	math::Vec3f getPosition() const;
	math::Vec3f getLookAt() const;
	math::Vec3f getUp() const;

	/**
	 * Helper function for camera calcuation.
	 *
	 * Rotates given point around given axis for theta amount (in radians). 
	 *
	 * @param point to rotate
	 * @param axis to rotate around
	 * @param amount to rotate in radians
	 *
	 * @return rotated point.
	 */
	math::Vec3f rotatePointAroundAxis(
		const math::Vec3f &point, const math::Vec3f &axis, float theta);
};

}; // namespace graphics
}; // namespace skeletor

#endif // GRAPHICS_CAMERA_HPP
