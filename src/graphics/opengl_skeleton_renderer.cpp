#include "graphics/opengl_skeleton_renderer.hpp"

#include "graphics/camera.hpp"
#include "animation/box.hpp"
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

void OpenGLSkeletonRenderer::addBox(const animation::Box &box)
{
        m_boxes.push_back(&box);
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
	glMultMatrixf(camera.getModelViewMatrix().m);

        // enable depth test
        glEnable(GL_DEPTH_TEST);

        for (std::vector<const animation::SkeletonPose *>::iterator it = 
                        m_skeletons.begin(); it != m_skeletons.end(); ++it) {
                render(*(*it));
        }
        for (std::vector<const animation::Box *>::iterator it = 
                        m_boxes.begin(); it != m_boxes.end(); ++it) {
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

void OpenGLSkeletonRenderer::render(const animation::Box &box) const
{
        glPushMatrix();
        
        math::Mat4x4f matrix = box.getMultMatrix();
        glMultMatrixf((GLfloat *) matrix.m);

        math::Vec3f vs[8];
        for (int i=0; i<8; ++i) {
                vs[i] = box.getVertex(i);
        }
        glBegin(GL_QUADS);
                // front: 0,1,3,2
                glColor3f(0.0f, 0.0f, 1.0f); // color blue 
                glVertex3f(vs[0].x, vs[0].y, vs[0].z);
                glVertex3f(vs[1].x, vs[1].y, vs[1].z);
                glVertex3f(vs[3].x, vs[3].y, vs[3].z); 
                glVertex3f(vs[2].x, vs[2].y, vs[2].z);
                // back: 4,5,7,6
                glColor3f(0.0f, 0.0f, 1.0f); // color blue 
                glVertex3f(vs[4].x, vs[4].y, vs[4].z);
                glVertex3f(vs[5].x, vs[5].y, vs[5].z);
                glVertex3f(vs[7].x, vs[7].y, vs[7].z); 
                glVertex3f(vs[6].x, vs[6].y, vs[6].z); 
                // right: 1,3,7,5
                glColor3f(1.0f, 0.0f, 0.0f); // color red 
                glVertex3f(vs[1].x, vs[1].y, vs[1].z);
                glVertex3f(vs[3].x, vs[3].y, vs[3].z);
                glVertex3f(vs[7].x, vs[7].y, vs[7].z); 
                glVertex3f(vs[5].x, vs[5].y, vs[5].z); 
                // left: 0,2,6,4
                glColor3f(1.0f, 0.0f, 0.0f); // color red 
                glVertex3f(vs[0].x, vs[0].y, vs[0].z);
                glVertex3f(vs[2].x, vs[2].y, vs[2].z);
                glVertex3f(vs[6].x, vs[6].y, vs[6].z); 
                glVertex3f(vs[4].x, vs[4].y, vs[4].z); 
                // top: 0,1,5,4
                glColor3f(0.0f, 1.0f, 0.0f); // color green 
                glVertex3f(vs[0].x, vs[0].y, vs[0].z);
                glVertex3f(vs[1].x, vs[1].y, vs[1].z);
                glVertex3f(vs[5].x, vs[5].y, vs[5].z); 
                glVertex3f(vs[4].x, vs[4].y, vs[4].z); 
                // bottom: 2,3,7,6
                glColor3f(0.0f, 1.0f, 0.0f); // color green 
                glVertex3f(vs[2].x, vs[2].y, vs[2].z);
                glVertex3f(vs[3].x, vs[3].y, vs[3].z);
                glVertex3f(vs[7].x, vs[7].y, vs[7].z); 
                glVertex3f(vs[6].x, vs[6].y, vs[6].z); 
        glEnd();

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
