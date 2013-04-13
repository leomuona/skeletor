#ifndef SKELETON_RENDERER_HPP
#define SKELETON_RENDERER_HPP

#include "math/vec2.hpp"

#include <string>

namespace skeletor {

namespace animation {
class SkeletonPose;
class Box;
}; // namespace animation

namespace graphics {
class Camera;

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

	virtual void onResize(const math::Vec2i &resolution) = 0;

        virtual void swapBuffers() = 0;

        /**
         * Add a skeleton to skeleton-vector, that is rendered.
         */
        virtual void addSkeleton(const animation::SkeletonPose &skeleton) = 0;

        /**
         * Add box for rendering.
         */
        virtual void addBox(const animation::Box &box) = 0;

        /**
         * Draw a frame.
         */
        virtual void drawFrame(const Camera &camera) = 0;

        /**
         * Clean up before exiting program.
         */
        virtual void cleanUp() = 0;
};

}; // namespace graphics
}; // namespace skeletor

#endif // SKELETON_RENDERER_HPP
