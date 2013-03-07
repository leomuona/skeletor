#ifndef OPENGL_ADAPTER_HPP
#define OPENGL_ADAPTER_HPP

#include "graphics/graphics_adapter_interface.hpp"
#include "math/mat4x4.hpp"

namespace skeletor {
namespace graphics {

class OpenGLAdapter : public GraphicsAdapterInterface
{
private:
	/** \brief Opengl projection matrix. */
	math::Mat4x4f m_projectionMatrix;

	/** \brief Resoluation of the screen, e.g. 800x600 */
	math::Vec2i m_resolution;

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

	/**
	 * onResize event, this function will set up the projection matrix.
	 *
	 * @param window resolution
	 */
	void onResize(const math::Vec2i &resolution);

        void swapBuffers();

        /**
         * Clears color and depth buffer.
         */
        void clearBuffer();

        /**
         * Load Identity Matrix
         */
        void loadIdentity();

        /**
         * Use the camera and look at a specified point.
         */
        void lookAt(float camX, float camY, float camZ,
                    float lookX, float lookY, float lookZ,
                    float upX, float upY, float upZ);

        /**
         * Clean up the OpenGL and SDL before exiting program.
         * Call this before destructor.
         */
        void cleanUp();
private:
	/**
	 * Helper function to set the projection matrix (perspective).
	 *
	 * @param fovy - field of view
	 * @param near value
	 * @param far value
	 */
	void setPerspectiveProjection(float fovy, float near, float far);
};

}; // namespace graphics
}; // namespace skeletor

#endif // OPENGL_ADAPTER_HPP
