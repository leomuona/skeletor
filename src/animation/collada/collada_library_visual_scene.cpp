#include "animation/collada/collada_library_visual_scene.hpp"
#include "animation/joint.hpp"
#include "math/vec3.hpp"
#include "util/string.hpp"

#include "rapidxml.hpp"

#include <iostream>
#include <fstream>
#include <vector>

namespace skeletor {
namespace animation {
namespace collada {

Joint *load_library_visual_scenes(rapidxml::xml_node<> *root)
{
	using namespace rapidxml;
	Joint *root_joint = NULL;

	xml_node<> *lib_vs = root->first_node("library_visual_scenes");
	xml_node<> *vs = lib_vs->first_node("visual_scene");

	while (vs != NULL) {
		xml_node<> *node = vs->first_node("node");
		xml_node<> *root_node = findRootNode(node, "root");
		if (root_node) {
			root_joint = buildJointHierarchy(root_node, NULL);
		}

		vs = vs->next_sibling("visual_scene");
	}

	return root_joint;
}

rapidxml::xml_node<> *findRootNode(rapidxml::xml_node<> *node, const std::string &name)
{
	while (node != NULL) {
		std::string node_name = node->first_attribute("name")->value();
		util::toLower(node_name);
		if (node_name == name) {
			return node;
		}

		rapidxml::xml_node<> *child = node->first_node("node");
		while (child != NULL) {
			rapidxml::xml_node<> *root = findRootNode(child, name);
			if (root) {
				return root;
			}

			child = child->next_sibling("node");
		}

		node = node->next_sibling("node");
	}

	return NULL;
}

Joint *buildJointHierarchy(rapidxml::xml_node<> *node, Joint *parent)
{
	math::Mat4x4f localMatrix(getNodeLocalMatrix(node));
	Joint *joint = new Joint(parent, localMatrix);

	if (node->first_attribute("name")) {
		joint->setName(node->first_attribute("name")->value());
	}
	if (node->first_attribute("sid")) {
		joint->setSID(node->first_attribute("sid")->value());
	}
	if (node->first_attribute("id")) {
		joint->setID(node->first_attribute("id")->value());
	}

	rapidxml::xml_node<> *children = node->first_node("node");
	while (children != NULL) {
		joint->addChild(buildJointHierarchy(children, joint));
		children = children->next_sibling("node");
	}

	return joint;
}

math::Mat4x4f getNodeLocalMatrix(rapidxml::xml_node<> *node)
{
	if (node->first_node("matrix")) {
		math::Mat4x4f matrix;
		rapidxml::xml_node<> *matrix_node = node->first_node("matrix");
		std::vector<std::string> arr(util::split(matrix_node->value(), ' '));
		for (int i=0; i<16; ++i) {
			matrix.m[i] = util::lexicalCast<std::string, float>(arr[i]);
		}
		matrix.transpose();
		return matrix;
	} else {
		return buildNodeLocalMatrix(node);
	}
}

math::Mat4x4f buildNodeLocalMatrix(rapidxml::xml_node<> *node)
{
	std::string translate("0 0 0");
	std::string jointOrientZ("0 0 1 0");
	std::string jointOrientY("0 1 0 0");
	std::string jointOrientX("1 0 0 0");
	std::string rotateZ("0 0 1 0");
	std::string rotateY("0 1 0 0");
	std::string rotateX("1 0 0 0");

	if (node->first_node("translate")) {
		translate = node->first_node("translate")->value();
	}

	rapidxml::xml_node<> *rotate = node->first_node("rotate");
	while (rotate != NULL) {
		std::string sid = rotate->first_attribute("sid")->value();
		std::string value = rotate->value();
		if (sid == "jointOrientZ") {
			jointOrientZ = value;
		} else if (sid == "jointOrientY") {
			jointOrientY = value;
		} else if (sid == "jointOrientX") {
			jointOrientX = value;
		} else if (sid == "rotateZ") {
			rotateZ = value;
		} else if (sid == "rotateY") {
			rotateY = value;
		} else if (sid == "rotateX") {
			rotateX = value;
		}

		rotate = rotate->next_sibling("rotate");
	}

	math::Mat4x4f x, y, z, t, g_x, g_y, g_z;

	std::vector<std::string> rotX(util::split(jointOrientX, ' '));
	std::vector<std::string> rotY(util::split(jointOrientY, ' '));
	std::vector<std::string> rotZ(util::split(jointOrientZ, ' '));
	std::vector<std::string> tran(util::split(translate, ' '));
	std::vector<std::string> g_rotX(util::split(rotateX, ' '));
	std::vector<std::string> g_rotY(util::split(rotateY, ' '));
	std::vector<std::string> g_rotZ(util::split(rotateZ, ' '));

	x.rotate(math::Vec3f(1, 0, 0), DEGREES_2_RADIANS * util::lexicalCast<std::string, float>(rotX[3]));
	y.rotate(math::Vec3f(0, 1, 0), DEGREES_2_RADIANS * util::lexicalCast<std::string, float>(rotY[3]));
	z.rotate(math::Vec3f(0, 0, 1), DEGREES_2_RADIANS * util::lexicalCast<std::string, float>(rotZ[3]));
	t.translate(math::Vec3f(util::lexicalCast<std::string, float>(tran[0]),
	                        util::lexicalCast<std::string, float>(tran[1]),
	                        util::lexicalCast<std::string, float>(tran[2])));

	g_x.rotate(math::Vec3f(1, 0, 0), DEGREES_2_RADIANS * util::lexicalCast<std::string, float>(g_rotX[3]));
	g_y.rotate(math::Vec3f(0, 1, 0), DEGREES_2_RADIANS * util::lexicalCast<std::string, float>(g_rotY[3]));
	g_z.rotate(math::Vec3f(0, 0, 1), DEGREES_2_RADIANS * util::lexicalCast<std::string, float>(g_rotZ[3]));

	return t * z * y * x * g_z * g_y * g_x;
}

}; // namespace collada
}; // namespace animation
}; // namespace skeletor
