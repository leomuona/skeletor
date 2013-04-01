#include "graphics/camera.hpp"

#include "math/vec4.hpp"

namespace skeletor {
namespace graphics {

Camera::Camera()
{
        m_position = math::Vec3f(15.f, 0.f, 15.f);
        m_up = math::Vec3f(0.f, 1.f ,0.f);
        m_lookAt = math::Vec3f(0.f, 5.f, 0.f);
}

void Camera::onCameraMotion(const math::Vec2f &motion)
{
	math::Vec3f pos   = m_position - m_lookAt;
	math::Vec3f cross = pos.cross(m_up);
	const float len   = pos.length();
	cross.normalize();

	// horizontal motion
	pos  = rotatePointAroundAxis(pos, cross, motion.y);
	m_up = rotatePointAroundAxis(m_up, cross, motion.y);
	m_up.normalize();

	// vertical motion
	pos = rotatePointAroundAxis(pos, m_up, motion.x);

	m_position = pos + m_lookAt;

	onCameraZoom(len / pos.length());
}

void Camera::onCameraZoom(float factor)
{
	math::Vec3f look_to_eye = -m_lookAt + m_position;
	look_to_eye *= factor;
	m_position = m_lookAt + look_to_eye;

	updateModelViewMatrix();
}

void Camera::updateModelViewMatrix()
{
	math::Vec3f view_dir = m_lookAt - m_position;
	math::Vec3f view_side;
	math::Vec3f view_up;

	view_dir.normalize();
	view_up = m_up - m_up.dot(view_dir) * view_dir;
	view_side = view_dir.cross(view_up);

	m_modelview.set(
		 view_side.x,  view_side.y,  view_side.z, 0,
		 view_up.x  ,  view_up.y  ,  view_up.z  , 0,
		-view_dir.x , -view_dir.y , -view_dir.z , 0,
		 0          ,  0          ,  0          , 1);

	math::Vec4f translate(m_position.x, m_position.y, m_position.z, 0);
	math::Vec4f tmp = m_modelview * translate;

	m_modelview.m[12] = -tmp.x;
	m_modelview.m[13] = -tmp.y;
	m_modelview.m[14] = -tmp.z;
}

const math::Mat4x4f &Camera::getModelViewMatrix() const
{
	return m_modelview;
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

math::Vec3f Camera::getPosition() const
{
        return m_position;
}

math::Vec3f Camera::getUp() const
{
        return m_up;
}

math::Vec3f Camera::getLookAt() const
{
        return m_lookAt;
}

math::Vec3f Camera::rotatePointAroundAxis(
const math::Vec3f &point, const math::Vec3f &axis, float theta)
{
	return point * std::cos(theta)
	     + (point * (point.dot(axis))) * (1-std::cos(theta))
	     + axis.cross(point) * std::sin(theta);
}

}; // namespace graphics
}; // namespace skeletor

