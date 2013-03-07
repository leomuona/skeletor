#ifndef GRAPHICS_ADAPTER_INTERFACE_HPP
#define GRAPHICS_ADAPTER_INTERFACE_HPP

#include "math/vec2.hpp"

namespace skeletor {
namespace graphics {

class GraphicsAdapterInterface
{
public:
        virtual void initWindow(
                int width, int height, int bpp, bool fs, const char* title) = 0;
	virtual void onResize(const math::Vec2i &resolution) = 0;
        virtual void initGraphics() = 0;
        virtual void swapBuffers() = 0;
        virtual void clearBuffer() = 0;
        virtual void loadIdentity() = 0;
        virtual void lookAt(float camX, float camY, float camZ,
                            float lookX, float lookY, float lookZ,
                            float upX, float upY, float upZ) = 0;
        virtual void cleanUp() = 0;
};

}; // namespace graphics
}; // namespace skeletor

#endif // GRAPHICS_ADAPTER_INTERFACE_HPP
