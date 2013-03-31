#include "graphics/opengl_skeleton_renderer.hpp"

#include "graphics/camera.hpp"
#include "animation/skeleton_pose.hpp"
#include "animation/skeleton.hpp"
#include "animation/joint.hpp"

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdexcept>

namespace skeletor {
namespace graphics {

void OpenGLSkeletonRenderer::initRenderer(
const math::Vec2i &dimension, int bpp, bool fs, const std::string &title)
{
        // -- init window --
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
                throw new std::runtime_error("Window initialization failed.");
        }

	m_resolution = dimension;

        // flags: opengl, doublebuffering and fullscreen if wanted
        int flags = (SDL_OPENGL | SDL_DOUBLEBUF);
        if (fs) {
                flags |= SDL_FULLSCREEN;
        }
        if (SDL_SetVideoMode(dimension.x, dimension.y, bpp, flags) == NULL) {
                throw new std::runtime_error("Setting video mode failed.");
        }

	SDL_Event resizeEvent;
	resizeEvent.type = SDL_VIDEORESIZE;
	resizeEvent.resize.w = m_resolution.x;
	resizeEvent.resize.h = m_resolution.y;
	SDL_PushEvent(&resizeEvent);

        SDL_WM_SetCaption(title.c_str(), NULL);

        // -- init OpenGL --
        // init Projection Matrix
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        // init ModelView Matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        // init clear color
        glClearColor(1.f, 1.f, 1.f, 1.f);

        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
                std::string errormsg = "OpenGL initialization failed. ";
                errormsg.append(reinterpret_cast<const char*>(gluErrorString(error)));
                throw new std::runtime_error(errormsg);
        } 
}

void OpenGLSkeletonRenderer::addSkeleton(const animation::SkeletonPose &skeleton)
{
        m_skeletons.push_back(&skeleton);
}

void OpenGLSkeletonRenderer::onResize(const math::Vec2i &resolution)
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

void OpenGLSkeletonRenderer::drawFrame(Camera &camera)
{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glLoadIdentity();

        math::Vec3f camPos = camera.getPosition();
        math::Vec3f camLook = camera.getLookAt();
        math::Vec3f camUp = camera.getUp();
        gluLookAt(camPos.x, camPos.y, camPos.z,
                                  camLook.x, camLook.y, camLook.z,
                                  camUp.x, camUp.y, camUp.z);

        for (std::vector<const animation::SkeletonPose *>::iterator it = 
                        m_skeletons.begin(); it != m_skeletons.end(); ++it) {
                render(*(*it));
        } 
}

void OpenGLSkeletonRenderer::swapBuffers()
{
        SDL_GL_SwapBuffers();
}

void OpenGLSkeletonRenderer::render(const animation::SkeletonPose &skeletonPose) const
{
	float psize = 0;
	glGetFloatv(GL_POINT_SIZE, &psize);
	glPointSize(5.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	render(skeletonPose.getSkeleton().getRootJoint(), skeletonPose);
	glPointSize(psize);
}

void OpenGLSkeletonRenderer::render(
const animation::Joint &joint, const animation::SkeletonPose &skeletonPose) const
{
	glPushMatrix();
	glMultMatrixf((joint.getBindPoseMatrix() * skeletonPose.getTransform(&joint)).m);
	glBegin(GL_POINTS);
		glVertex3f(0, 0, 0);
	glEnd();

	const std::vector<animation::Joint *> &children = joint.getChildren();

	for (int i=0; i<children.size(); ++i) {
		math::Mat4x4f t = children[i]->getLocalMatrix();
		glBegin(GL_LINES);
			glVertex3f(0, 0, 0);
			glVertex3f(t.m[12], t.m[13], t.m[14]);
		glEnd();
	}

	for (int i=0; i<children.size(); ++i) {
		render(*children[i], skeletonPose);
	}

	glPopMatrix();
}

void OpenGLSkeletonRenderer::setPerspectiveProjection(float fovy, float _near, float _far)
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

void OpenGLSkeletonRenderer::cleanUp()
{
        SDL_Quit();
}

}; // namespace skeletor
}; // namespace graphics
