#ifndef SKELETON_RENDERER_HPP
#define SKELETON_RENDERER_HPP

#include "math/vec2.hpp"

#include <string>

namespace skeletor {
class Player;
namespace animation {
class SkeletonPose;
class Box;
}; // namespace animation

namespace graphics {
class Camera;

/**
 * Skeleton renderer interface. Use this with rendering API of your choice.
 */
class SkeletonRendererInterface
{
public:

        /**
         * Initializes window and graphics.
         * Call this before calling other function in this class.
         */
        virtual void initRenderer(
                const math::Vec2i &dimension, int bpp, bool fs,
                const std::string &title) = 0;

        /**
         * Resize function.
         */
	virtual void onResize(const math::Vec2i &resolution) = 0;

        /**
         * Swap buffers.
         */
        virtual void swapBuffers() = 0;

        /**
         * Add a box for rendering.
         */
        virtual void addBox(const animation::Box &box) = 0;

        /**
         * Draw current frame.
         */
        virtual void drawFrame(const Camera &camera, const Player &player) = 0;

        /**
         * Clean up before exiting program.
         */
        virtual void cleanUp() = 0;
};

}; // namespace graphics
}; // namespace skeletor

#endif // SKELETON_RENDERER_HPP
