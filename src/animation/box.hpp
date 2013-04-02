#ifndef BOX_HPP
#define BOX_HPP

#include "math/vec3.hpp"

namespace skeletor {
namespace animation {

class Box {
public:
        Box(unsigned int id, float mass);

        // setters and getters
        void setId(unsigned int id){ m_id = id; }
        unsigned int getId(){ return m_id; }

        void setMass(float mass){ m_mass = mass; }
        float getMass(){ return m_mass; }

        void setEdge(int i, const math::Vec3f &pa, const math::Vec3f &pb);
        void getEdge(int i, math::Vec3f &pa, math::Vec3f &pb);

private:
        unsigned int m_id;
        math::Vec3f m_edges[12][2];
        float m_mass;
};

}; // namespace animation
}; // namespace skeletor

#endif // BOX_HPP
