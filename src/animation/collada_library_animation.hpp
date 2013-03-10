#ifndef COLLADA_LIBRARY_ANIMATION
#define COLLADA_LIBRARY_ANIMATION

#include "rapidxml.hpp"

#include <string>
#include <vector>

namespace skeletor {
namespace animation {

typedef struct
{
	std::string id;

	// e.g Name, float: tells which type of array we have.
	std::vector<std::string> types;

	// name array. tells how to map values in arrays and types.
	std::vector<std::string> names;

	// stride == size of (type/name) arrays.

	std::vector<std::string> array;
} Source;

typedef struct
{
} Channel;

typedef struct
{
	// INPUT, OUTPUT, INTERPOLATION, IN_TANGENT, OUT_TANGENT
	std::string semantic;

	// refers to Source id.
	std::string source;
} Sample;

typedef struct
{
	std::string id;
	std::vector<Source> sources;
	std::vector<Channel> channels;
	std::vector<Sample> samples;
} Animation;

typedef struct
{
	std::vector<Animation> animations;
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

}; // namespace animation
}; // namespace skeletor

#endif // COLLADA_LIBRARY_ANIMATION
