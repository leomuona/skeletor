#ifndef PLAYER_HPP
#define PLAYER_HPP

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
	 * We assume that y is up, and movement (mainly) happens on xz-axis.
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
	 * @param delta
	 */
	void move(const math::Vec2f &movementVector, float delta);

	/**
	 * onCamera motion event
	 *
	 * @param amount of motion.
	 */
	void onCameraMotion(const math::Vec2f &motion);

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

};

inline const graphics::Camera &Player::getCamera() const
{
	return m_camera;
}

}; // namespace skeletor

#endif // PLAYER_HPP
