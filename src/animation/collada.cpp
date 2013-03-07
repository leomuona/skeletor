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

		Joint *root_joint = loadJoints(root, joints_name);
		skeleton = new Skeleton(root_joint);

		ctrl = ctrl->next_sibling("controller");
	}

	return skeleton;
}

Joint *Collada::loadJoints(rapidxml::xml_node<> *root, const std::string &sid)
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
	math::Mat4x4f m(buildNodeInvBindPose(node));
	Joint *joint = new Joint(parent, m, node->first_attribute("name")->value());

	rapidxml::xml_node<> *children = node->first_node("node");
	while (children != NULL) {
		joint->addChild(buildJointHierarchy(children, joint));
		children = children->next_sibling("node");
	}

	return joint;
}

math::Mat4x4f Collada::buildNodeInvBindPose(rapidxml::xml_node<> *node)
{
	std::string translate("0 0 0");
	std::string jointOrientZ("0 0 1 0");
	std::string jointOrientY("0 1 0 0");
	std::string jointOrientX("1 0 0 0");
	std::string rotateZ("0 0 1 0");
	std::string rotateY("0 1 0 0");
	std::string rotateX("1 0 0 0");

	if (node->first_attribute("translate")) {
		translate = node->first_attribute("translate")->value();
	}
	if (node->first_attribute("jointOrientZ")) {
		jointOrientZ = node->first_attribute("jointOrientZ")->value();
	}
	if (node->first_attribute("jointOrientY")) {
		jointOrientY = node->first_attribute("jointOrientY")->value();
	}
	if (node->first_attribute("jointOrientX")) {
		jointOrientX = node->first_attribute("jointOrientX")->value();
	}
	if (node->first_attribute("rotateZ")) {
		rotateZ = node->first_attribute("rotateZ")->value();
	}
	if (node->first_attribute("rotateY")) {
		rotateY = node->first_attribute("rotateY")->value();
	}
	if (node->first_attribute("rotateX")) {
		rotateX = node->first_attribute("rotateX")->value();
	}

	math::Mat4x4f x, y, z, t;

	std::vector<std::string> rotX(util::stringSplit(jointOrientX));
	std::vector<std::string> rotY(util::stringSplit(jointOrientY));
	std::vector<std::string> rotZ(util::stringSplit(jointOrientZ));
	std::vector<std::string> tran(util::stringSplit(translate));

	x.rotate(math::Vec3f(1, 0, 0), util::lexicalCast<std::string, float>(rotX[3]));
	y.rotate(math::Vec3f(0, 1, 0), util::lexicalCast<std::string, float>(rotY[3]));
	z.rotate(math::Vec3f(0, 0, 1), util::lexicalCast<std::string, float>(rotZ[3]));
	t.translate(math::Vec3f(util::lexicalCast<std::string, float>(tran[0]),
	                        util::lexicalCast<std::string, float>(tran[1]),
	                        util::lexicalCast<std::string, float>(tran[2])));

	return (t * x * y * z);
}

}; // namespace animation
}; // namespace skeletor
