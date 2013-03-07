#include "graphics/opengl_adapter.hpp"

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdexcept>
#include <string>

namespace skeletor {
namespace graphics {

OpenGLAdapter::OpenGLAdapter() {}

OpenGLAdapter::~OpenGLAdapter() {}

void OpenGLAdapter::initWindow(
int width, int height, int bpp, bool fs, const char *title)
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

        SDL_WM_SetCaption(title, NULL);
}

void OpenGLAdapter::initGraphics()
{
        // init Projection Matrix
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        // init ModelView Matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        // init clear color
        glClearColor(0.f, 0.f, 0.f, 1.f);

        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
                std::string errormsg = "OpenGL initialization failed. ";
                errormsg.append(reinterpret_cast<const char*>(gluErrorString(error)));
                throw new std::runtime_error(errormsg);
        }
}

}; // namespace graphics
}; // namespace skeletor
