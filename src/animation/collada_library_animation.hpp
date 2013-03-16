#ifndef COLLADA_LIBRARY_ANIMATION
#define COLLADA_LIBRARY_ANIMATION

#include "util/search.hpp"
#include "rapidxml.hpp"

#include <string>
#include <vector>
#include <iostream>

namespace skeletor {
namespace animation {

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
	 */
	std::vector<std::string> semantic;

	// refers to Source id.
	std::vector<std::string> source;

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
	std::vector<Source> sources;
	std::vector<Channel> channels;
	std::vector<Sample> samples;

	/**
	 * Find the Source with corresponding id.
	 *
	 * This function expects that sources has been sorted.
	 * So yesh, this uses binary search, so O(log n).
	 *
	 * @param source id
	 * @return Source object
	 */
	Source &getSource(const std::string &id)
	{
		int idx = util::binarySearch<Source, std::string>(sources, id);
		return sources[idx];
	}

	Sample &getSample(const std::string &id)
	{
		int idx = util::binarySearch<Sample, std::string>(samples, id);
		return samples[idx];
	}

} Animation;

typedef struct
{
	std::vector<Animation> animations;
} AnimationLibrary;

class Skeleton;

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
std::vector<Source> load_animation_sources(rapidxml::xml_node<> *node);

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
std::vector<Sample> load_animation_samples(rapidxml::xml_node<> *node);

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
std::vector<Channel> load_animation_channels(rapidxml::xml_node<> *node);

/**
 * Transforms the AnimationLibrary structure into KeyFrame animation.
 *
 * @param AnimationLibrary
 * @param Animated Skeleton, keyframes are saved here.
 */
void animationLibraryToKeyFrameAnimation(AnimationLibrary &anim, Skeleton &skeleton);

}; // namespace animation
}; // namespace skeletor

#endif // COLLADA_LIBRARY_ANIMATION
