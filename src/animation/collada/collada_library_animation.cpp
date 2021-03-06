#include "animation/collada/collada_library_animation.hpp"
#include "animation/skeleton.hpp"
#include "util/string.hpp"

#include <assert.h>
#include <map>

namespace skeletor {
namespace animation {
namespace collada {

using namespace rapidxml;

template <typename T> bool PComp(const T * const &a, const T * const &b)
{
	return *a < *b;
}

AnimationLibrary *load_library_animations(rapidxml::xml_node<> *root)
{
	AnimationLibrary *lib = new AnimationLibrary();

	xml_node<> *lib_anim = root->first_node("library_animations");
	xml_node<> *animations = lib_anim->first_node("animation");

	while (animations != NULL) {
		Animation *animation = new Animation;

		if (animations->first_attribute("id")) {
			animation->id = animations->first_attribute("id")->value();
		}

		animation->sources = load_animation_sources(animations);
		animation->channels = load_animation_channels(animations);
		animation->samples = load_animation_samples(animations);

		// first, let's sort the sources and sample vectors.
		std::sort(animation->sources.begin(), animation->sources.end(), PComp<Source>);
		std::sort(animation->samples.begin(), animation->samples.end(), PComp<Sample>);

		// do the sample -> source mapping
		for (int i=0; i<animation->samples.size(); ++i) {
			Sample *s = animation->samples[i];
			for (int j=0; j<s->source.size(); ++j) {
				std::string src_str = s->source[j];
				Source *src = animation->getSource(src_str);
				s->inputs.insert(
					std::pair<std::string, Source*>(s->semantic[j], src));
			}
		}

		lib->animations.push_back(animation);

		animations = animations->next_sibling("animation");
	}

	return lib;
}

std::vector<Source *> load_animation_sources(rapidxml::xml_node<> *node)
{
	std::vector<Source *> sources;

	xml_node<> *xml_source = node->first_node("source");

	while (xml_source != NULL) {
		Source *source = new Source;

		if (xml_source->first_attribute("id")) {
			source->id = xml_source->first_attribute("id")->value();
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

		source->array = util::split(array, ' ');
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

			source->names.push_back(name);
			source->types.push_back(type);

			param = param->next_sibling("param");
		}

		xml_source = xml_source->next_sibling("source");
	}

	return sources;
}

std::vector<Sample *> load_animation_samples(rapidxml::xml_node<> *node)
{
	std::vector<Sample *> samples;

	xml_node<> *sampler = node->first_node("sampler");
	while (sampler != NULL) {
		Sample *sample = new Sample;

		if (sampler->first_attribute("id")) {
			sample->id = sampler->first_attribute("id")->value();
		}

		xml_node<> *input  = sampler->first_node("input");

		while (input != NULL) {
			if (input->first_attribute("semantic")) {
				std::string sem =
					input->first_attribute("semantic")->value();
				util::removeIfFirst(sem, '#');
				sample->semantic.push_back(sem);
			}
			if (input->first_attribute("source")) {
				std::string src =
					input->first_attribute("source")->value();
				util::removeIfFirst(src, '#');
				sample->source.push_back(src);
			}

			input = input->next_sibling("input");
		}

		samples.push_back(sample);
		sampler = sampler->next_sibling("sampler");
	}

	return samples;
}

std::vector<Channel *> load_animation_channels(rapidxml::xml_node<> *node)
{
	std::vector<Channel *> channels;
	xml_node<> *channel = node->first_node("channel");

	while (channel != NULL) {
		Channel *ch = new Channel;

		if (channel->first_attribute("source")) {
			ch->source = channel->first_attribute("source")->value();
			util::removeIfFirst(ch->source, '#');
		}
		if (channel->first_attribute("target")) {
			ch->target = channel->first_attribute("target")->value();
			util::removeIfFirst(ch->target, '#');
		}

		channels.push_back(ch);
		channel = channel->next_sibling("channel");
	}

	return channels;
}

typedef struct JointFrame
{
	// case with separate transformations, e.g. how MAYA saves
	std::vector<KeyFrame> rotateX;
	std::vector<KeyFrame> rotateY;
	std::vector<KeyFrame> rotateZ;
	std::vector<KeyFrame> translate;

	// and single transformation, how Blender saves
	std::vector<KeyFrame> transform;

	size_t getSize()
	{
		size_t size = 0;
		size = std::max(size, rotateX.size());
		size = std::max(size, rotateY.size());
		size = std::max(size, rotateZ.size());
		size = std::max(size, translate.size());
		size = std::max(size, transform.size());
		return size;
	}

	float getTime(int idx)
	{
		if (rotateX.size() > idx) {
			return rotateX[idx].getTime();
		} else if (rotateY.size() > idx) {
			return rotateY[idx].getTime();
		} else if (rotateZ.size() > idx) {
			return rotateZ[idx].getTime();
		} else if (translate.size() > idx) {
			return translate[idx].getTime();
		} else if (transform.size() > idx) {
			return transform[idx].getTime();
		} else {
			assert(!"JointFrame should always have time");
		}
	}

} JointFrame;

void animationLibraryToKeyFrameAnimation(AnimationLibrary &anims, Skeleton &skeleton)
{
	std::map<std::string, JointFrame> keyframes;

	for (int i=0; i<anims.animations.size(); ++i) {
		Animation *anim = anims.animations[i];

		for (int c=0; c<anim->channels.size(); ++c) {
			Channel *ch = anim->channels[c];
			Sample *sample = anim->getSample(ch->source);

			std::vector<std::string> target(util::split(ch->target, '/'));
			std::string &joint     = target[0];
			std::string &transform = target[1];
			util::toLower(transform);

			if (keyframes.find(joint) == keyframes.end()) {
				keyframes.insert(std::pair<std::string, JointFrame>(joint, JointFrame()));
			}
			std::map<std::string, JointFrame>::iterator it;
			it = keyframes.find(joint);

			if (util::beginsWith(transform, "rotatex")) {
				it->second.rotateX = rotateTransformation(transform, *sample);
			} else if (util::beginsWith(transform, "rotatey")) {
				it->second.rotateY = rotateTransformation(transform, *sample);
			} else if (util::beginsWith(transform, "rotatez")) {
				it->second.rotateZ = rotateTransformation(transform, *sample);
			} else if (util::beginsWith(transform, "translate")) {
				it->second.translate = translateTransformation(transform, *sample);
			} else if (util::beginsWith(transform, "transform")) {
				it->second.transform = transformTransformation(transform, *sample);
			} else {
				std::cout << "wat: " << transform << std::endl;
			}
		}
	}

	// now we can merge the map into single transformation.
	std::map<std::string, JointFrame>::iterator it = keyframes.begin();
	while (it != keyframes.end()) {
		Joint *joint = skeleton.getJoint(it->first);
		if (joint == NULL) {
			std::cout << "No joint with id: " << it->first << std::endl;
			++it;
			continue;
		}
		std::vector<KeyFrame> &j_keyframes = joint->getKeyFrames();

		size_t size = it->second.getSize();
		for (unsigned int i=0; i<size; ++i) {
			math::Mat4x4f transformation;
			math::Mat4x4f translate;
			math::Mat4x4f rotateX;
			math::Mat4x4f rotateY;
			math::Mat4x4f rotateZ;

			JointFrame &jf = it->second;

			if (!jf.transform.empty()) {
				transformation = jf.transform[i].getTransform();
			} else {
				if (!jf.translate.empty()) {
					translate = jf.translate[i].getTransform();
				}
				if (!jf.rotateX.empty()) {
					rotateX = jf.rotateX[i].getTransform();
				}
				if (!jf.rotateY.empty()) {
					rotateY = jf.rotateY[i].getTransform();
				}
				if (!jf.rotateZ.empty()) {
					rotateZ = jf.rotateZ[i].getTransform();
				}
				transformation =  translate * rotateZ * rotateY * rotateX;
			}

			j_keyframes.push_back(KeyFrame(jf.getTime(i), transformation));
		}

		++it;
	}
}

std::vector<KeyFrame> rotateTransformation(const std::string &name, Sample &sample)
{
	std::vector<KeyFrame> keyframes;

	std::vector<float> times;
	std::vector<math::Vec3f> output;
	std::vector<Interpolations> interpolation;
	std::vector<math::Vec2f> intan;
	std::vector<math::Vec2f> outan;

	times = parseINPUTSource(*sample.inputs.at("INPUT"));
	output = parseOUTPUTSource(*sample.inputs.at("OUTPUT"));
	interpolation = parseINTERPOLATIONSource(*sample.inputs.at("INTERPOLATION"));
	intan = parseTANGENTSource(*sample.inputs.at("IN_TANGENT"));
	outan = parseTANGENTSource(*sample.inputs.at("OUT_TANGENT"));

	assert(times.size() == output.size() &&
	       output.size() == interpolation.size() &&
	       interpolation.size() == intan.size() &&
	       intan.size() == outan.size());

	unsigned int size = times.size();
	for (unsigned int i=0; i<size; ++i) {
		math::Mat4x4f transformation;

		std::string n(name);
		util::toLower(n);

		output[i].x *= DEGREES_2_RADIANS;

		if (util::beginsWith(n, "rotatex")) {
			transformation.rotate(math::Vec3f(1, 0, 0), output[i].x);
		} else if (util::beginsWith(n, "rotatey")) {
			transformation.rotate(math::Vec3f(0, 1, 0), output[i].x);
		} else if (util::beginsWith(n, "rotatez")) {
			transformation.rotate(math::Vec3f(0, 0, 1), output[i].x);
		} else {
			std::cout << "unknown rotate: " << n << std::endl;
		}

		keyframes.push_back(KeyFrame(times[i], transformation));
	}

	return keyframes;
}

std::vector<KeyFrame> transformTransformation(const std::string &name, Sample &sample)
{
	std::vector<KeyFrame> keyframes;

	std::vector<float> times;
	std::vector<math::Mat4x4f> output;
	std::vector<Interpolations> interpolation;

	times = parseINPUTSource(*sample.inputs.at("INPUT"));
	output = parseOUTPUTMatrixSource(*sample.inputs.at("OUTPUT"));
	interpolation = parseINTERPOLATIONSource(*sample.inputs.at("INTERPOLATION"));

	assert(times.size() == output.size() &&
	       output.size() == interpolation.size());

	unsigned int size = times.size();
	for (unsigned int i=0; i<size; ++i) {
		output[i].transpose();
		keyframes.push_back(KeyFrame(times[i], output[i]));
	}

	return keyframes;
}

std::vector<KeyFrame> translateTransformation(const std::string &name, Sample &sample)
{
	std::vector<KeyFrame> keyframes;

	std::vector<float> times;
	std::vector<math::Vec3f> output;
	std::vector<Interpolations> interpolation;
	std::vector<math::Vec2f> intan_x, intan_y, intan_z;
	std::vector<math::Vec2f> outan_x, outan_y, outan_z;

	// translation has x, y, z, so intan and outtan holds all of these.
	times = parseINPUTSource(*sample.inputs.at("INPUT"));
	output = parseOUTPUTSource(*sample.inputs.at("OUTPUT"));
	interpolation = parseINTERPOLATIONSource(*sample.inputs.at("INTERPOLATION"));
	intan_x = parseTANGENTSource(*sample.inputs.at("IN_TANGENT"), 6, 0);
	intan_y = parseTANGENTSource(*sample.inputs.at("IN_TANGENT"), 6, 2);
	intan_z = parseTANGENTSource(*sample.inputs.at("IN_TANGENT"), 6, 4);
	outan_x = parseTANGENTSource(*sample.inputs.at("OUT_TANGENT"), 6, 0);
	outan_y = parseTANGENTSource(*sample.inputs.at("OUT_TANGENT"), 6, 2);
	outan_z = parseTANGENTSource(*sample.inputs.at("OUT_TANGENT"), 6, 4);

	assert(times.size() == output.size() &&
	       output.size() == interpolation.size() &&
	       interpolation.size() == intan_x.size() &&
	       intan_x.size() == intan_y.size() &&
	       intan_y.size() == intan_z.size() &&
	       intan_z.size() == outan_x.size() &&
	       outan_x.size() == outan_y.size() &&
	       outan_y.size() == outan_z.size());

	unsigned int size = times.size();
	for (unsigned int i=0; i<size; ++i) {
		math::Mat4x4f transformation;
		transformation.translate(output[i]);
		keyframes.push_back(KeyFrame(times[i], transformation));
	}

	return keyframes;
}

std::vector<float> parseINPUTSource(Source &source)
{
	std::vector<float> times;
	for (int i=0; i<source.array.size(); ++i) {
		float f = util::lexicalCast<std::string, float>(source.array[i]);
		times.push_back(f);
	}
	return times;
}

std::vector<math::Vec3f> parseOUTPUTSource(Source &source)
{
	std::vector<math::Vec3f> output;
	int stride = std::max(source.types.size(), source.names.size());
	for (int i=0; i<source.array.size(); i+=stride) {
		float x, y, z;
		x = y = z = 0;
		x = util::lexicalCast<std::string, float>(source.array[i]);

		if (stride > 1) {
			y = util::lexicalCast<std::string, float>(source.array[i+1]);
		}
		if (stride > 2) {
			z = util::lexicalCast<std::string, float>(source.array[i+2]);
		}

		output.push_back(math::Vec3f(x, y, z));
	}

	return output;
}

std::vector<math::Mat4x4f> parseOUTPUTMatrixSource(Source &source)
{
	std::vector<math::Mat4x4f> output;
	for (int i=0; i<source.array.size()/16; ++i) {
		math::Mat4x4f matrix;
		for (int j=0; j<16; ++j) {
			matrix.m[j] = util::lexicalCast<std::string, float>(source.array[i*16+j]);
		}
		output.push_back(matrix);
	}
	return output;
}

std::vector<Interpolations> parseINTERPOLATIONSource(Source &source)
{
	std::vector<Interpolations> output;
	for (int i=0; i<source.array.size(); ++i) {
		std::string str = source.array[i];
		util::toLower(str);

		if (str == "bezier") {
			output.push_back(kBezier);
		} else if (str == "linear") {
			output.push_back(kLinear);
		} else {
			std::cout << "Unkown Interpolation: " << str << std::endl;
			output.push_back(kUnknown);
		}
	}
	return output;
}

std::vector<math::Vec2f> parseTANGENTSource(Source &source, int stride, int offset)
{
	std::vector<math::Vec2f> tangents;
	for (int i=0; i<source.array.size(); i+=stride) {
		int j = offset + i;
		tangents.push_back(math::Vec2f(
			util::lexicalCast<std::string, float>(source.array[j]),
			util::lexicalCast<std::string, float>(source.array[j+1])));
	}
	return tangents;
}

}; // namespace collada
}; // namespace animation
}; // namespace skeletor
