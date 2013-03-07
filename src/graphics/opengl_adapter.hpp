#ifndef OPENGL_ADAPTER_HPP
#define OPENGL_ADAPTER_HPP

#include "graphics/graphics_adapter_interface.hpp"

namespace skeletor {
namespace graphics {

class OpenGLAdapter : public GraphicsAdapterInterface
{
public:
        OpenGLAdapter();
        ~OpenGLAdapter();

        /**
         * Initializes the window. Call initGraphics() right after.
         *
         * @throws RuntimeException if fails.
         */
        void initWindow(
                int width, int height, int bpp, bool fs, const char *title);

        /**
         * Initializes OpenGL graphics. Call this after initWindow().
         *
         * @throws RuntimeException if fails.
         */
        void initGraphics();
};

}; // namespace graphics
}; // namespace skeletor

#endif // OPENGL_ADAPTER_HPP