#ifndef BOX_HPP
#define BOX_HPP

#include "math/vec3.hpp"
#include "math/mat4x4.hpp"

namespace skeletor {
namespace animation {

class Box {
public:
        Box(unsigned int id, float mass);

        // setters and getters
        void setId(unsigned int id){ m_id = id; }
        unsigned int getId() const { return m_id; }

        void setMass(float mass){ m_mass = mass; }
        float getMass() const { return m_mass; }

        void setLocation(const math::Vec3f &location);
        math::Vec3f getLocation() const;

        /**
         * Set vertex with index 0-7
         */
        void setVertex(int i, const math::Vec3f &v);
        
        /**
         * Get vertex with index 0-7
         */
        math::Vec3f getVertex(int i) const;

        /**
         * MultMatrix includes location and rotation and can be given to
         * OpenGL.
         *
         * @param matrix multication matrix
         */
        void setMultMatrix(const math::Mat4x4f &matrix);
        math::Mat4x4f getMultMatrix() const;

private:
        unsigned int m_id;
        math::Vec3f m_vertices[8];
        math::Mat4x4f m_matrix;
        float m_mass;
};

}; // namespace animation
}; // namespace skeletor

#endif // BOX_HPP
