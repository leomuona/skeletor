#include "graphics/skeleton_renderer.hpp"
#include "graphics/opengl_adapter.hpp"

namespace skeletor {
namespace graphics {

SkeletonRenderer::SkeletonRenderer()
{
        m_graphicsAdapter = new OpenGLAdapter();
}

SkeletonRenderer::~SkeletonRenderer()
{
        delete m_graphicsAdapter;
}

void SkeletonRenderer::initRenderer(
const math::Vec2i &dimension, int bpp, bool fs, const std::string &title)
{
        m_graphicsAdapter->initWindow(
                dimension.x, dimension.y, bpp, fs, title.c_str());
        m_graphicsAdapter->initGraphics();
}

}; // namespace graphics
}; // namespace skeletor
