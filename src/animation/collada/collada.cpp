#include "animation/collada/collada.hpp"
#include "animation/collada/collada_library_animation.hpp"
#include "animation/collada/collada_library_visual_scene.hpp"
#include "animation/joint.hpp"
#include "animation/skeleton.hpp"
#include "util/string.hpp"

#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

namespace skeletor {
namespace animation {
namespace collada {

std::string getAuthoringTool(rapidxml::xml_node<> *root)
{
	using namespace rapidxml;
	xml_node<> *asset = root->first_node("asset");
	while (asset != NULL) {
		xml_node<> *cunt = asset->first_node("contributor");
		if (cunt) {
			return cunt->first_node("authoring_tool")->value();
		}

		asset = asset->next_sibling("channel");
	}

	return "";
}

skeletor::animation::Skeleton *loadSkeleton(const std::string &filename)
{
	using namespace rapidxml;
	Skeleton *skeleton = NULL;

	file<> xmlFile(filename.c_str());
	xml_document<> doc;
	doc.parse<0>(xmlFile.data());

	xml_node<> *root = doc.first_node("COLLADA");
	std::string authoring_tool = getAuthoringTool(root);
	std::cout << filename << ": authoring tool used: " << authoring_tool << std::endl;

	Joint *root_joint = load_library_visual_scenes(root);
	skeleton = new Skeleton(root_joint);

	AnimationLibrary *lib = load_library_animations(root);
	animationLibraryToKeyFrameAnimation(*lib, *skeleton);

	util::toLower(authoring_tool);
	if (util::beginsWith(authoring_tool, "maya")) {
		skeleton->setupBindPoseMatrices();
	} else if (util::beginsWith(authoring_tool, "blender")) {
		// blender specific stuff.
	}

	return skeleton;
}

}; // namespace collada
}; // namespace animation
}; // namespace skeletor
