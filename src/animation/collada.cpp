#include "animation/collada.hpp"
#include "animation/skeleton.hpp"

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
			std::string id = srcs->first_attribute("id")->value();

			if (id.find("joints") != std::string::npos) {
				xml_node<> *name = srcs->first_node("Name_array");

				joints_count = name->first_attribute("count")->value();
				joints_name  = name->value();
				break;
			}

			srcs = srcs->next_sibling("source");
		}

		std::cout << "amount: " << joints_count << std::endl;
		std::cout << "names: "  << joints_name << std::endl;

		ctrl = ctrl->next_sibling("controller");
	}

	return NULL;
}

}; // namespace animation
}; // namespace skeletor
