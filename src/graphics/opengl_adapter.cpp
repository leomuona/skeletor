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

	m_resolution.set(width, height);

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

void OpenGLAdapter::onResize(const math::Vec2i &resolution)
{
	float aspect = (float) resolution.x / (float) resolution.y;
	m_resolution = resolution;

	glViewport(0, 0, resolution.x, resolution.y);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	setPerspectiveProjection(60.0f, 1.0f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void OpenGLAdapter::swapBuffers()
{
        SDL_GL_SwapBuffers();
}

void OpenGLAdapter::clearBuffer()
{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLAdapter::loadIdentity()
{
        glLoadIdentity();
}

void OpenGLAdapter::lookAt(float camX, float camY, float camZ,
                           float lookX, float lookY, float lookZ,
                           float upX, float upY, float upZ)
{
        gluLookAt(camX, camY, camZ, lookX, lookY, lookZ, upX, upY, upZ);
}

void OpenGLAdapter::cleanUp()
{
        SDL_Quit();
}

void OpenGLAdapter::setPerspectiveProjection(float fovy, float _near, float _far)
{
	float radians = 0.5f * fovy * DEGREES_2_RADIANS;
	float d       = cosf(radians) / sinf(radians);
	float aspect  = (float) m_resolution.x / (float) m_resolution.y;
	float deltaZ  = _far - _near;

	m_projectionMatrix.set(
		d / aspect, .0f, .0f                 , .0f,
		.0f       , d  , .0f                 , .0f,
		.0f       , .0f, -(_far+_near)/deltaZ, (-2*_far*_near)/deltaZ,
		.0f       , .0f, -1.0f               , .0f
	);

	glMultMatrixf(m_projectionMatrix.m);
}

}; // namespace graphics
}; // namespace skeletor
