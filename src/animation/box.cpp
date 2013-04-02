#include "animation/box.hpp"

namespace skeletor {
namespace animation {

Box::Box(unsigned int id, float mass)
{
        m_id = id;
        m_mass = mass;
}

void Box::setEdge(int i, const math::Vec3f &pa, const math::Vec3f &pb)
{
        m_edges[i][0] = pa;
        m_edges[i][1] = pb;
}

void Box::getEdge(int i, math::Vec3f &pa, math::Vec3f &pb)
{
        pa = m_edges[i][0];
        pb = m_edges[i][1];
}

}; // namespace animation
}; // namespace skeletor
