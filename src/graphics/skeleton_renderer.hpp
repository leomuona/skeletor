#ifndef SKELETON_RENDERER_HPP
#define SKELETON_RENDERER_HPP

#include "math/vec2.hpp"
#include "graphics/graphics_adapter_interface.hpp"

#include <string>

namespace skeletor {
namespace graphics {

class SkeletonRenderer
{
private:
        GraphicsAdapterInterface *m_graphicsAdapter;

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

};

}; // namespace graphics
}; // namespace skeletor

#endif // SKELETON_RENDERER_HPP
