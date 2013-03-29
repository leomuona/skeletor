#include "graphics/camera.hpp"

#include "math/vec4.hpp"
#include "math/mat4x4.hpp"

namespace skeletor {
namespace graphics {

Camera::Camera()
{
        m_position = math::Vec3f(15.f, 0.f, 15.f);
        m_up = math::Vec3f(0.f, 1.f ,0.f);
        m_lookAt = math::Vec3f(0.f, 5.f, 0.f);
}

void Camera::rotatePositionAroundYAxis(float d, float speed)
{
	math::Mat4x4f rot;
	rot.rotate(math::Vec3f(0, 1, 0), d * speed);
	math::Vec4f tmp(m_position.x, m_position.y, m_position.z, 0);

	tmp = tmp * rot;

	m_position = math::Vec3f(tmp.x, tmp.y, tmp.z);
}

void Camera::setPosition(const math::Vec3f &position)
{
        m_position.set(position.x, position.y, position.z);
}

void Camera::setUp(const math::Vec3f &up)
{
        m_up.set(up.x, up.y, up.z);
}

void Camera::setLookAt(const math::Vec3f &lookAt)
{
        m_lookAt.set(lookAt.x, lookAt.y, lookAt.z);
}

math::Vec3f Camera::getPosition()
{
        return m_position;
}

math::Vec3f Camera::getUp()
{
        return m_up;
}

math::Vec3f Camera::getLookAt()
{
        return m_lookAt;
}

}; // namespace graphics
}; // namespace skeletor

