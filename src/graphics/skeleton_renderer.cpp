#include "graphics/skeleton_renderer.hpp"
#include "graphics/opengl_adapter.hpp"
#include "graphics/opengl_skeleton_renderer.hpp"

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

void SkeletonRenderer::onResize(const math::Vec2i &resolution)
{
	m_graphicsAdapter->onResize(resolution);
}

void SkeletonRenderer::swapBuffers()
{
        m_graphicsAdapter->swapBuffers();
}

void SkeletonRenderer::addSkeleton(animation::SkeletonPose &skeleton)
{
        m_skeletons.push_back(skeleton);
}

void SkeletonRenderer::drawSkeleton(animation::SkeletonPose &skeleton)
{
	OpenGLSkeletonRenderer osr;
	osr.render(skeleton.getSkeleton());
}

void SkeletonRenderer::drawFrame()
{
        m_graphicsAdapter->clearBuffer();
        m_graphicsAdapter->loadIdentity();

        for (std::vector<animation::SkeletonPose>::iterator it = 
                        m_skeletons.begin(); it != m_skeletons.end(); ++it) {
                drawSkeleton(*it);
        }
}

}; // namespace graphics
}; // namespace skeletor
