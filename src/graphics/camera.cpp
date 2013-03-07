#include "graphics/camera.hpp"

namespace skeletor {
namespace graphics {

Camera::Camera()
{
        m_position = Vec3f(1.f, 0.f, 1.f);
        m_up = Vec3f(0.f, 1.f ,0.f);
        m_lookAt = Vec3f(0.f, 0.f, 0.f);
}

void Camera::setPosition(const math::Vec3f &position)
{
        m_position.set(position.x, position.y, position.z);
}

void Camera::setUp(const math::Vec3f &up)
{
        m_up.set(position.x, position.y, position.z);
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

