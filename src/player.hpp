#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "math/mat4x4.hpp"
#include "math/vec2.hpp"
#include "math/vec3.hpp"
#include "graphics/camera.hpp"

namespace skeletor {

/**
 * Player is user controller character.
 *
 * The camera lookat is at player, and the camera moves with player.
 *
 *         __ * player facing direction
 *          /|
 *         /
 *        * player
 *       /
 *      /
 *     /
 *    * Camera position
 */
class Player
{
private:
	/** \brief distance of the camera. */
	float m_cameraDistance;

	/** \brief amount of units moved/second. */
	float m_movementSpeed;

	/**
	 * position of the player character.
	 *
	 * We assume that y is up, and movement (mainly) happens on xz-plane.
	 */
	math::Vec3f m_position;

	/** \brief character facing direction (normalized) */
	math::Vec3f m_direction;

	/** \brief camera model. */
	graphics::Camera m_camera;

public:
	/**
	 * Constructor.
	 *
	 * @param starting position
	 * @param starting facing direction
	 */
	Player(const math::Vec3f &position, const math::Vec3f &direction);

	/**
	 * Move the player by amount of movement vector.
	 *
	 * The movement vector only tells the amount of movement and in
	 * which direction.
	 *
	 * e.g, Vec2f(0, 1) only says that move forward by this amount.
	 *
	 * This function calculates how this affects the position of the player.
	 *
	 * @param movement vector.
	 * @param delta time
	 */
	void move(const math::Vec2f &movementVector, float delta);

	/**
	 * onCamera motion event
	 *
	 * @param amount of motion.
	 * @param delta time
	 */
	void onCameraMotion(const math::Vec2f &motion, float dt);

	/**
	 * Zoom in or out
	 *
	 * @param amount of zoom.
	 */
	void onCameraZoom(float factor);

	/**
	 * Camera getter.
	 *
	 * @param Camera
	 */
	const graphics::Camera &getCamera() const;

	/**
	 * Get player direction.
	 *
	 * @param Direction vector
	 */
	math::Vec3f getDirection() const;

	/**
	 * Get player position.
	 *
	 * @param position vector
	 */
	math::Vec3f getPosition() const;

	/**
	 * Get transformation matrix.
	 *
	 * This returns the top-level transformation matrix, so what this
	 * includes is the transformation and rotation (on xz-plane)
	 * of the player character.
	 *
	 * @return transformation matrix.
	 */
	math::Mat4x4f getTransformation() const;
};

inline const graphics::Camera &Player::getCamera() const
{
	return m_camera;
}

inline math::Vec3f Player::getDirection() const
{
	return m_direction;
}

inline math::Vec3f Player::getPosition() const
{
	return m_position;
}

inline math::Mat4x4f Player::getTransformation() const
{
	math::Mat4x4f transformation;
	transformation.translate(m_position);

	// assume that initial direction is parallel to z-axis
	math::Vec3f initial(0, 0, 1);
	math::Vec3f plane_vec(m_direction.x, 0, m_direction.z);
	plane_vec.normalize();

	math::Vec3f cross(initial.cross(plane_vec));
	float angle = std::atan2(cross.length(), initial.dot(plane_vec));

	if (cross.y < 0) {
		angle = -angle;
	}

	transformation.rotate(math::Vec3f(0, 1, 0), angle);
	return transformation;
}

}; // namespace skeletor

#endif // PLAYER_HPP
