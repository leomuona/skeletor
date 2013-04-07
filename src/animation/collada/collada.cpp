#include "animation/collada/collada.hpp"
#include "animation/collada/collada_library_animation.hpp"
#include "animation/collada/collada_library_visual_scene.hpp"
#include "animation/joint.hpp"
#include "animation/skeleton.hpp"

#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

namespace skeletor {
namespace animation {
namespace collada {

skeletor::animation::Skeleton *loadSkeleton(const std::string &filename)
{
	using namespace rapidxml;
	Skeleton *skeleton = NULL;

	file<> xmlFile(filename.c_str());
	xml_document<> doc;
	doc.parse<0>(xmlFile.data());

	xml_node<> *root = doc.first_node("COLLADA");

	Joint *root_joint = load_library_visual_scenes(root);
	skeleton = new Skeleton(root_joint);

	AnimationLibrary *lib = load_library_animations(root);
	animationLibraryToKeyFrameAnimation(*lib, *skeleton);

	skeleton->setupBindPoseMatrices();

	return skeleton;
}

}; // namespace collada
}; // namespace animation
}; // namespace skeletor
