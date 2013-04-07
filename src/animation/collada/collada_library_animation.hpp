#ifndef COLLADA_LIBRARY_ANIMATION
#define COLLADA_LIBRARY_ANIMATION

#include "animation/keyframe.hpp"
#include "math/mat4x4.hpp"
#include "math/vec2.hpp"
#include "math/vec3.hpp"
#include "util/search.hpp"
#include "rapidxml.hpp"

#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace skeletor {
namespace animation {
class Skeleton;
namespace collada {

enum Interpolations {
	kLinear,
	kBezier,
	kUnknown,
};

typedef struct Source
{
	std::string id;

	// e.g Name, float: tells which type of array we have.
	std::vector<std::string> types;

	// name array. tells how to map values in arrays and types.
	std::vector<std::string> names;

	// stride == size of (type/name) arrays.

	std::vector<std::string> array;

	bool operator<(const Source &other) const
	{
		return id < other.id;
	}

	bool operator>(const Source &other) const
	{
		return id > other.id;
	}

} Source;

typedef struct Channel
{
	// this points to sample
	std::string source;

	// this tells the joint id, and applied transformation.
	std::string target;
} Channel;

typedef struct Sample
{
	std::string id;

	/**
	 * INPUT, OUTPUT, INTERPOLATION, IN_TANGENT, OUT_TANGENT
	 *
	 * INPUT = keypoints of the TIME domain, seconds.
	 * OUTPUT = keypoints of the animated values.
	 * INTERPOLATION = tells how to interpolate between INPUT and OUTPUT
	 *                 keypoints.
	 *
	 * if INTERPOLATION == BEZIER
	 *   IN_TANGENT  = control point 1
	 *   OUT_TANGENT = control point 2
	 *
	 */
	std::vector<std::string> semantic;

	// refers to Source id.
	std::vector<std::string> source;

	/**
	 * key - value mapping.
	 * key is the semantic name
	 * value is the source that key refers to.
	 */
	std::map<std::string, Source *> inputs;

	bool operator<(const Sample &other) const
	{
		return id < other.id;
	}

	bool operator>(const Sample &other) const
	{
		return id > other.id;
	}

} Sample;

typedef struct
{
	std::string id;
	std::vector<Source *> sources;
	std::vector<Channel *> channels;
	std::vector<Sample *> samples;

	/**
	 * Find the Source with corresponding id.
	 *
	 * This function expects that sources has been sorted.
	 * So yesh, this uses binary search, so O(log n).
	 *
	 * @param source id
	 * @return Source object
	 */
	Source *getSource(const std::string &id)
	{
		int idx = util::binarySearch<Source*, std::string>(sources, id);
		return sources[idx];
	}

	Sample *getSample(const std::string &id)
	{
		int idx = util::binarySearch<Sample*, std::string>(samples, id);
		return samples[idx];
	}

} Animation;

typedef struct
{
	std::vector<Animation *> animations;
} AnimationLibrary;


/**
 * Parses the <library_animations> node from COLLADA file.
 *
 * @param pointer to xml root node.
 *
 * @return Parsed animation library.
 */
AnimationLibrary *load_library_animations(rapidxml::xml_node<> *root);

/**
 * Parses the:
 *
 * <library_animations>
 *   <animation>
 *     <source>
 *
 * nodes
 *
 * @param node pointing to <animation> node
 *
 * @return parsed information in vector.
 */
std::vector<Source *> load_animation_sources(rapidxml::xml_node<> *node);

/**
 * Parses the:
 *
 * <library_animations>
 *   <animation>
 *     <sampler>
 *
 * node
 *
 * @param node pointing to <animation> node
 *
 * @return parsed information in vector.
 */
std::vector<Sample *> load_animation_samples(rapidxml::xml_node<> *node);

/**
 * Parses the:
 *
 * <library_animations>
 *   <animation>
 *     <source>
 *
 * node
 *
 * @param node pointing to <source> node
 *
 * @return parsed information in vector.
 */
std::vector<Channel *> load_animation_channels(rapidxml::xml_node<> *node);

/**
 * Transforms the AnimationLibrary structure into KeyFrame animation.
 *
 * @param AnimationLibrary
 * @param Animated Skeleton, keyframes are saved here.
 */
void animationLibraryToKeyFrameAnimation(AnimationLibrary &anim, Skeleton &skeleton);

/**
 * Parses a COLLADA rotate sequence/sample into transformation matrix.
 *
 * @param transformation name, e.g rotateX.ANGLE, translate, transform(0)(3)
 * @param sample in question.
 */
std::vector<KeyFrame> rotateTransformation(const std::string &name, Sample &sample);
std::vector<KeyFrame> transformTransformation(const std::string &name, Sample &sample);
std::vector<KeyFrame> translateTransformation(const std::string &name, Sample &sample);

/**
 * Simple, just tells the keyframe timings.
 *
 * @param Source.
 * @return frame times in vector
 */
std::vector<float> parseINPUTSource(Source &source);

/**
 * Parse the output source.
 *
 * Not necessarily all values from math::Vec3f are used.
 * Usually only x is used, but at most x, y, z are used.
 *
 * OUTPUT tells the amount of transformation between transformations.
 *
 * @param Source.
 * @return transformation in Vec3f container.
 */
std::vector<math::Vec3f> parseOUTPUTSource(Source &source);

/**
 * Parse the output source as 4x4 Matrix.
 *
 * Blender and Max saves the transformation values like dis.
 * Or when transform sequence is given.
 *
 * @param Source
 * @return transformations in 4x4 float matrix.
 */
std::vector<math::Mat4x4f> parseOUTPUTMatrixSource(Source &source);

/**
 * Parses the interpolation source.
 *
 * @param Source
 * @return interpolations vector.
 */
std::vector<Interpolations> parseINTERPOLATIONSource(Source &source);

/**
 * Parses the tangents sources (IN_TANGENT / OUT_TANGENT)
 *
 * Always reads just two values from single sample
 * Translation target holds 6 values on each 'sample', so stride and offset needed.
 *
 * @param Source
 * @param stride how many elements per sample. defaults to 2.
 * @param offset of values read. defaults to 0
 * @return tangents.
 */
std::vector<math::Vec2f> parseTANGENTSource(Source &source, int stride = 2, int offset = 0);

}; // namespace collada
}; // namespace animation
}; // namespace skeletor

#endif // COLLADA_LIBRARY_ANIMATION
