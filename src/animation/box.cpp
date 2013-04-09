#include "animation/box.hpp"

namespace skeletor {
namespace animation {

Box::Box(unsigned int id, float mass)
{
        m_id = id;
        m_mass = mass;
}

void Box::setLocation(const math::Vec3f &location)
{
        m_matrix.m[12] = location.x;
        m_matrix.m[13] = location.y;
        m_matrix.m[14] = location.z;
        m_matrix.m[15] = 1.f;
}

math::Vec3f Box::getLocation() const
{
        math::Vec3f location;
        location.set(m_matrix.m[12], m_matrix.m[13], m_matrix.m[14]);
        return location;
}

void Box::setMultMatrix(const math::Mat4x4f &matrix)
{
        m_matrix = matrix;
}

math::Mat4x4f Box::getMultMatrix() const
{
        return m_matrix;
}

void Box::setVertex(int i, const math::Vec3f &v)
{
        m_vertices[i] = v;
}

math::Vec3f Box::getVertex(int i) const
{
        return m_vertices[i];
}

}; // namespace animation
}; // namespace skeletor
