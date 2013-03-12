#ifndef OPENGL_SKELETON_RENDERER_HPP
#define OPENGL_SKELETON_RENDERER_HPP

#include "graphics/skeleton_renderer_interface.hpp"
#include "math/vec2.hpp"
#include "math/mat4x4.hpp"

#include <string>
#include <vector>

namespace skeletor {
namespace animation {
class SkeletonPose;
class Skeleton;
class Joint;
}; // namespace animation
namespace graphics {
class Camera;

class OpenGLSkeletonRenderer : public SkeletonRendererInterface
{
public:
        /** 
         * Initializes SDL, window and OpenGL.
         *
         * @throws RuntimeException if fails.
         */
        void initRenderer(
                const math::Vec2i &dimension, int bpp, bool fs,
                const std::string &title);
        
        void addSkeleton(const animation::SkeletonPose &skeleton);

        void onResize(const math::Vec2i &resolution);
        
        void swapBuffers();

        void drawFrame(Camera &camera);

        void cleanUp();

private:
        /** \brief Vector of skeletons that are drawn */
        std::vector<animation::SkeletonPose> m_skeletons;

        /** \brief OpenGL projection matrix. */
        math::Mat4x4f m_projectionMatrix;

        /** \brief Resolution of the screen, e.g. 800x600 */
        math::Vec2i m_resolution;

        /**
         * Render a single joint of skeleton.
         */
        void render(const animation::Joint &joint) const; 

        /**
         * Render a skeleton.
         */
        void render(const animation::Skeleton &skeleton) const;

        /**
	 * Helper function to set the projection matrix (perspective).
	 *
	 * @param fovy - field of view
	 * @param near value
	 * @param far value
	 */
	void setPerspectiveProjection(float fovy, float near, float far); 
};

}; // namespace graphics
}; // namespace skeletor

#endif // OPENGL_SKELETON_RENDERER_HPP
