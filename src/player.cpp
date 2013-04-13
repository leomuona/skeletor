#include "player.hpp"

#include <iostream>

namespace skeletor {

Player::Player(const math::Vec3f &position, const math::Vec3f &direction)
	: m_cameraDistance(20.0f)
	, m_movementSpeed(20.0f)
	, m_position(position)
	, m_direction(direction)
{
	m_direction.normalize();

	m_camera.setUp(math::Vec3f(0, 1, 0));
	m_camera.setLookAt(m_position); // look at player.
	m_camera.setPosition(m_position + -m_direction * m_cameraDistance);
}

void Player::move(const math::Vec2f &movementVector, float delta)
{
	math::Vec2f dir_x(m_direction.z, -m_direction.x);
	math::Vec2f dir_y(m_direction.x,  m_direction.z);
	dir_x.normalize();
	dir_y.normalize();
	dir_x *= movementVector.x;
	dir_y *= movementVector.y;

	math::Vec3f diff;
	diff.x += dir_x.x * m_movementSpeed * delta;
	diff.z += dir_x.y * m_movementSpeed * delta;
	diff.x += dir_y.x * m_movementSpeed * delta;
	diff.z += dir_y.y * m_movementSpeed * delta;

	m_position += diff;
	m_camera.setLookAt(m_camera.getLookAt() + diff);
	m_camera.setPosition(m_camera.getPosition() + diff);
}

void Player::onCameraMotion(const math::Vec2f &motion, float dt)
{
	m_camera.onCameraMotion(motion, dt);

	m_direction = -m_camera.getPosition() + m_camera.getLookAt();
	m_direction.normalize();
}

void Player::onCameraZoom(float factor)
{
	m_cameraDistance *= factor;
	m_camera.onCameraZoom(factor);
}

}; // namespace skeletor
