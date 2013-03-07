#include "graphics/opengl_skeleton_renderer.hpp"

#include "animation/skeleton.hpp"
#include "animation/joint.hpp"

#include <GL/gl.h>

namespace skeletor {
namespace graphics {

void OpenGLSkeletonRenderer::render(const animation::Skeleton &skeleton) const
{
	glBegin(GL_LINES);
	render(skeleton.getRootJoint());
	glEnd();
}

void OpenGLSkeletonRenderer::render(const animation::Joint &joint) const
{
	const std::vector<animation::Joint *> &children = joint.getChildren();
	for (int i=0; i<children.size(); ++i) {
		glVertex3f(0, 0, 0);
		glPushMatrix();
		glMultMatrixf(children[i]->getMatrixLocalTransformation().m);
		render(children[i]);
		glPopMatrix();
	}
}

}; // namespace skeletor
}; // namespace graphics
