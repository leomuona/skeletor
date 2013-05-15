#ifndef OPENGL_SKELETON_RENDERER_HPP
#define OPENGL_SKELETON_RENDERER_HPP

#include "graphics/skeleton_renderer_interface.hpp"
#include "math/vec2.hpp"
#include "math/mat4x4.hpp"

#include <string>
#include <vector>

namespace skeletor {
class Player;
namespace animation {
class Box;
class SkeletonPose;
class Skeleton;
class Joint;
}; // namespace animation
namespace graphics {
class Camera;

/**
 * Skeleton renderer that uses OpenGL.
 * Renders skeletons (and boxes) that are added into the renderer.
 */
class OpenGLSkeletonRenderer : public SkeletonRendererInterface
{
public:
        /** 
         * Initializes SDL, window and OpenGL.
         *
         * @param dimension - window dimensions.
         * @param bpp - color depth, usually 32.
         * @param fs - fullscreen or not
         * @param title - window title.
         * @throws RuntimeException if fails.
         */
        void initRenderer(
                const math::Vec2i &dimension, int bpp, bool fs,
                const std::string &title);
        
        /**
         * Add a box for rendering..
         * 
         * @param box - box to be added.
         */
        void addBox(const animation::Box &box);

        /**
         * Resize window.
         *
         * @param resolution - resolution
         */
        void onResize(const math::Vec2i &resolution);
        
        /**
         * Swap buffers.
         */
        void swapBuffers();

        /**
         * Draw current frame.
         *
         * @param camera - camera
         * @param player - player
         */
        void drawFrame(const Camera &camera, const Player &player);

        /**
         * Clean up before deleting the renderer.
         */
        void cleanUp();

private:
        /** \brief Vector of boxes that are drawn */
        std::vector<const animation::Box *> m_boxes;

        /** \brief OpenGL projection matrix. */
        math::Mat4x4f m_projectionMatrix;

        /** \brief Resolution of the screen, e.g. 800x600 */
        math::Vec2i m_resolution;

        /**
         * Render a single joint of skeleton.
         */
        void render(const animation::Joint &joint, const animation::SkeletonPose &skeletonPose) const; 

        /**
         * Renders the skeleton pose.
	 *
	 * @param skeleton pose.
         */
        void render(const animation::SkeletonPose &skeletonPose) const;

        /**
         * Renders the box.
         *
         * @param box.
         */
        void render(const animation::Box &box) const;

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
