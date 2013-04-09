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
        m_location = location;
}

math::Vec3f Box::getLocation() const
{
        return m_location;
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
