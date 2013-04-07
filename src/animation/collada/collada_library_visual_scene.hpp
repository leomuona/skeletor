#ifndef COLLADA_LIBRARY_VISUAL_SCENE_HPP
#define COLLADA_LIBRARY_VISUAL_SCENE_HPP

#include "math/mat4x4.hpp"
#include "rapidxml.hpp"

#include <string>
#include <vector>

namespace skeletor {
namespace animation {
class Joint;
namespace collada {

/**
 * Parses the joints information from COLLADA file.
 *
 * Joints are found from:
 *   <library_visual_scenes>
 *     <visual_scene>
 *       <node ... PARAM="JOINT">
 *         ...
 *
 * in structural manner.
 *
 * @param root node of the xml
 *
 * @return root node of the joints
 */
Joint *load_library_visual_scenes(rapidxml::xml_node<> *root);

/**
 * Searches through the dom tree recursively for skeleton root node.
 *
 * @param node to start searching from
 * @param name of the root node.
 *
 * @return root node in the dom tree.
 */
rapidxml::xml_node<> *findRootNode(rapidxml::xml_node<> *node,
                                   const std::string &name);

/**
 * Builds the joint hierarchy from the COLLADA file.
 *
 * @param xml_node
 * @param node parent
 *
 * @return joint.
 */
Joint *buildJointHierarchy(rapidxml::xml_node<> *node, Joint *parent);

/**
 * Read the matrix transformation from file, or build it
 *
 * @param node
 *
 * @return local matrix tranformation.
 */
math::Mat4x4f getNodeLocalMatrix(rapidxml::xml_node<> *node);

/**
 * Constructs the node local matrix from node information.
 *
 * The local matrix is constructed from all node transformations
 * (rotate, transform, scale) in the order they are.
 *
 * @param xml_node to parse
 * @return local transformation matrix.
 */
math::Mat4x4f buildNodeLocalMatrix(rapidxml::xml_node<> *node);

}; // namespace collada
}; // namespace animation
}; // namespace skeletor

#endif // COLLADA_LIBRARY_VISUAL_SCENE_HPP
