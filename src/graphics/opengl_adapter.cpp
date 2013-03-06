#include "graphics/opengl_adapter.hpp"

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdexception>

namespace skeletor {
namespace graphics {

OpenGLAdapter::OpenGLAdapter() {}

OpenGLAdapter::~OpenGLAdapter() {}

void OpenGLAdapter::initWindow(
int width, int height, int bpp, bool fs, char *title)
{
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
                throw new std::runtime_error("Window initialization failed.");
        }

        // flags: opengl, doublebuffering and fullscreen if wanted
        int flags = (SDL_OPENGL | SDL_DOUBLEBUF);
        if (fs) {
                flags |= SDL_FULLSCREEN;
        }
        if (SDL_SetVideoMode(width, height, bpp, flags) == NULL) {
                throw new std::runtime_error("Setting video mode failed.");
        }

        SDL_EnableUnicode(SDL_TRUE);
        SDL_WM_SetCaption(title, NULL);
}

void OpenGLAdapter::initGraphics()
{

}

}; // namespace graphics
}; // namespace skeletor
