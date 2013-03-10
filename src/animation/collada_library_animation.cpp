#include "animation/collada_library_animation.hpp"
#include "util/string.hpp"

namespace skeletor {
namespace animation {

using namespace rapidxml;

AnimationLibrary *load_library_animations(rapidxml::xml_node<> *root)
{
	AnimationLibrary *lib = new AnimationLibrary();

	xml_node<> *lib_anim = root->first_node("library_animations");
	xml_node<> *animations = lib_anim->first_node("animation");

	while (animations != NULL) {
		Animation animation;

		if (animations->first_attribute("id")) {
			animation.id = animations->first_attribute("id")->value();
		}

		animation.sources = load_animation_sources(animations);
		animation.channels = load_animation_channels(animations);
		animation.samples = load_animation_samples(animations);

		lib->animations.push_back(animation);

		animations = animations->next_sibling("animation");
	}

	return lib;
}

std::vector<Source> load_animation_sources(rapidxml::xml_node<> *node)
{
	std::vector<Source> sources;

	xml_node<> *xml_source = node->first_node("source");

	while (xml_source != NULL) {
		Source source;

		if (xml_source->first_attribute("id")) {
			source.id = xml_source->first_attribute("id")->value();
		}

		xml_node<> *thq = xml_source->first_node("technique_common");
		xml_node<> *acs = thq->first_node("accessor");
		xml_node<> *param = acs->first_node("param");

		std::string array;

		if (xml_source->first_node("Name_array")) {
			array = xml_source->first_node("Name_array")->value();
		}
		if (xml_source->first_node("float_array")) {
			array = xml_source->first_node("float_array")->value();
		}

		source.array = util::stringSplit(array);
		sources.push_back(source);

		while (param != NULL) {
			std::string name, type;
			if (param->first_attribute("name")) {
				name = param->first_attribute("name")->value();
			} else {
				name = "<notset>";
			}
			if (param->first_attribute("type")) {
				type = param->first_attribute("type")->value();
			} else {
				type = "<notset>";
			}

			source.names.push_back(name);
			source.types.push_back(type);

			param = param->next_sibling("param");
		}

		xml_source = xml_source->next_sibling("source");
	}

	return sources;
}

std::vector<Sample> load_animation_samples(rapidxml::xml_node<> *node)
{
	std::vector<Sample> samples;

	xml_node<> *sample = node->first_node("sampler");
	xml_node<> *input  = sample->first_node("input");

	while (input != NULL) {
		Sample sample;

		if (input->first_attribute("semantic")) {
			sample.semantic = input->first_attribute("semantic")->value();
		}
		if (input->first_attribute("source")) {
			sample.source = input->first_attribute("source")->value();
		}

		samples.push_back(sample);
		input = input->next_sibling("input");
	}

	return samples;
}

std::vector<Channel> load_animation_channels(rapidxml::xml_node<> *node)
{
	return std::vector<Channel>();
}

}; // namespace animation
}; // namespace skeletor
