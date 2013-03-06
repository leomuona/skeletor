#include "graphics/skeleton_renderer.hpp"
#include "graphics/opengl_adapter.hpp"

namespace skeletor {
namespace graphics {

SkeletonRenderer::SkeletonRender()
{
        m_graphics_adapter = new OpenGLAdapter();
}

SkeletonRenderer::~SkeletonRenderer()
{
        delete m_graphics_adapter;
}

void SkeletonRenderer::initRenderer(
const math::vec2i &dimension, int bpp, bool fs, const std::string &title)
{
        m_graphics_adapter->initWindow(
                dimension.x, dimension.y, bpp, fs, title.c_str);
        m_graphics_adapter->initGraphics();
}

}; // namespace graphics
}; // namespace skeletor
