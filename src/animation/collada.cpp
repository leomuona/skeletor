#include "animation/collada.hpp"
#include "animation/joint.hpp"
#include "animation/skeleton.hpp"
#include "math/vec3.hpp"
#include "util/string.hpp"

#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

#include <iostream>
#include <fstream>
#include <vector>

namespace skeletor {
namespace animation {

Skeleton *Collada::loadSkeleton(const std::string &filename)
{
	using namespace rapidxml;
	Skeleton *skeleton = NULL;

	file<> xmlFile(filename.c_str());
	xml_document<> doc;
	doc.parse<0>(xmlFile.data());

	xml_node<> *root = doc.first_node("COLLADA");
	xml_node<> *libc = root->first_node("library_controllers");
	xml_node<> *ctrl = libc->first_node("controller");

	while (ctrl != NULL) {
		xml_node<> *skin = ctrl->first_node("skin");
		xml_node<> *srcs = skin->first_node("source");

		std::string joints_name;
		std::string joints_count;

		while (srcs != NULL) {
			xml_node<> *thq = srcs->first_node("technique_common");
			xml_node<> *acs = thq->first_node("accessor");
			xml_node<> *param = acs->first_node("param");
			std::string param_s = param->first_attribute("name")->value();

			if (param_s == "JOINT") {
				xml_node<> *name = srcs->first_node("Name_array");

				joints_count = name->first_attribute("count")->value();
				joints_name  = name->value();
				break;
			}

			srcs = srcs->next_sibling("source");
		}

		std::cout << "amount: " << joints_count << std::endl;
		std::cout << "names: "  << joints_name << std::endl;

		Joint *root_joint = load_library_visual_scenes(root, joints_name);
		skeleton = new Skeleton(root_joint);

		ctrl = ctrl->next_sibling("controller");
	}

	return skeleton;
}

Joint *Collada::load_library_visual_scenes(
rapidxml::xml_node<> *root, const std::string &sid)
{
	using namespace rapidxml;
	Joint *root_joint = NULL;

	xml_node<> *lib_vs = root->first_node("library_visual_scenes");
	xml_node<> *vs = lib_vs->first_node("visual_scene");

	std::vector<std::string> s_ids(util::stringSplit(sid));

	while (vs != NULL) {
		xml_node<> *node = vs->first_node("node");
		xml_node<> *root_node = findRootNode(node, "root");
		root_joint = buildJointHierarchy(root_node, NULL);

		vs = vs->next_sibling("visual_scene");
	}

	return root_joint;
}

rapidxml::xml_node<> *Collada::findRootNode(rapidxml::xml_node<> *node, const std::string &name)
{
	while (node != NULL) {
		std::string node_name = node->first_attribute("name")->value();
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

Joint *Collada::buildJointHierarchy(rapidxml::xml_node<> *node, Joint *parent)
{
	math::Mat4x4f localMatrix(buildNodeLocalMatrix(node));
	Joint *joint = new Joint(parent, localMatrix, node->first_attribute("name")->value());

	rapidxml::xml_node<> *children = node->first_node("node");
	while (children != NULL) {
		joint->addChild(buildJointHierarchy(children, joint));
		children = children->next_sibling("node");
	}

	return joint;
}

math::Mat4x4f Collada::buildNodeLocalMatrix(rapidxml::xml_node<> *node)
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

	std::vector<std::string> rotX(util::stringSplit(jointOrientX));
	std::vector<std::string> rotY(util::stringSplit(jointOrientY));
	std::vector<std::string> rotZ(util::stringSplit(jointOrientZ));
	std::vector<std::string> tran(util::stringSplit(translate));
	std::vector<std::string> g_rotX(util::stringSplit(rotateX));
	std::vector<std::string> g_rotY(util::stringSplit(rotateY));
	std::vector<std::string> g_rotZ(util::stringSplit(rotateZ));

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

}; // namespace animation
}; // namespace skeletor
