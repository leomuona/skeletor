#include "graphics/opengl_skeleton_renderer.hpp"

#include "animation/skeleton.hpp"
#include "animation/joint.hpp"

#include <GL/gl.h>

namespace skeletor {
namespace graphics {

void OpenGLSkeletonRenderer::render(const animation::Skeleton &skeleton) const
{
	float psize = 0;
	glGetFloatv(GL_POINT_SIZE, &psize);
	glPointSize(5.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	render(skeleton.getRootJoint());
	glPointSize(psize);
}

void OpenGLSkeletonRenderer::render(const animation::Joint &joint) const
{
	const std::vector<animation::Joint *> &children = joint.getChildren();

	for (int i=0; i<children.size(); ++i) {
		math::Mat4x4f &t(children[i]->getLocalMatrix());
		glBegin(GL_LINES);
			glVertex3f(0, 0, 0);
			glVertex3f(t.m[12], t.m[13], t.m[14]);
		glEnd();
	}

	for (int i=0; i<children.size(); ++i) {
		glBegin(GL_POINTS);
			glVertex3f(0, 0, 0);
		glEnd();
		glPushMatrix();
		glMultMatrixf(children[i]->getLocalMatrix().m);
		render(children[i]);
		glPopMatrix();
	}
}

}; // namespace skeletor
}; // namespace graphics
