#ifndef OPENGL_SKELETON_RENDERER_HPP
#define OPENGL_SKELETON_RENDERER_HPP

namespace skeletor {
namespace animation {
class Skeleton;
class Joint;
}; // namespace animation
namespace graphics {


class OpenGLSkeletonRenderer
{
public:
	void render(const animation::Skeleton &skeleton) const;

private:
	void render(const animation::Joint &joint) const;
};

}; // namespace graphics
}; // namespace skeletor

#endif // OPENGL_SKELETON_RENDERER_HPP
