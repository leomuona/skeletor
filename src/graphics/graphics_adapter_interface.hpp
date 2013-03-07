#ifndef GRAPHICS_ADAPTER_INTERFACE_HPP
#define GRAPHICS_ADAPTER_INTERFACE_HPP

namespace skeletor {
namespace graphics {

class GraphicsAdapterInterface
{
public:
        virtual void initWindow(
                int width, int height, int bpp, bool fs, const char* title) = 0;
        virtual void initGraphics() = 0;
        virtual void swapBuffers() = 0;
        virtual void clearBuffer() = 0;
        virtual void loadIdentity() = 0;
};

}; // namespace graphics
}; // namespace skeletor

#endif // GRAPHICS_ADAPTER_INTERFACE_HPP
