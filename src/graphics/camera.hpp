#include "math/vec3.hpp"

namespace skeletor {
namespace graphics {

class Camera {
private:
        math::Vec3f m_position;
        math::Vec3f m_up;
        math::Vec3f m_lookAt;

public:
        Camera();

	void rotatePositionAroundYAxis(float d, float speed);

        void setPosition(const math::Vec3f &m_position);
        void setLookAt(const math::Vec3f &lookAt);
        void setUp(const math::Vec3f &up);
        math::Vec3f getPosition();
        math::Vec3f getLookAt();
        math::Vec3f getUp();
};

}; // namespace graphics
}; // namespace skeletor
