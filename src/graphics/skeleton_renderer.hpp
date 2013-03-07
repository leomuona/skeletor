#ifndef SKELETON_RENDERER_HPP
#define SKELETON_RENDERER_HPP

#include "math/vec2.hpp"
#include "graphics/graphics_adapter_interface.hpp"
#include "animation/skeleton_pose.hpp"

#include <string>
#include <vector>

namespace skeletor {
namespace graphics {

class SkeletonRenderer
{
private:
        GraphicsAdapterInterface *m_graphicsAdapter;
        std::vector<animation::SkeletonPose> m_skeletons;

        /**
         * Draw a skeleton -helper function.
         */
        void drawSkeleton(animation::SkeletonPose &skeleton);

public:
        SkeletonRenderer();
        ~SkeletonRenderer();

        /**
         * Initializes window and graphics.
         * Call this before calling other function in this class.
         */
        void initRenderer(
                const math::Vec2i &dimension, int bpp, bool fs,
                const std::string &title);

	void onResize(const math::Vec2i &resolution);

        void swapBuffers();

        /**
         * Add a skeleton to skeleton-vector, that is rendered.
         */
        void addSkeleton(animation::SkeletonPose &skeleton);

        /**
         * Draw a frame.
         */
        void drawFrame();

        /**
         * Clean up before exiting program.
         */
        void cleanUp();
};

}; // namespace graphics
}; // namespace skeletor

#endif // SKELETON_RENDERER_HPP
