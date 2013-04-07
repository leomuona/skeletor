#include "animation/parse.hpp"
#include "animation/collada/collada.hpp"

namespace skeletor {
namespace animation {

Skeleton *Parse::load(const std::string &file)
{
	std::string ext(file.substr(file.find_last_of(".") + 1));

	if (ext == "dae") {
		return collada::loadSkeleton(file);
	} else {
		return NULL;
	}
}

}; // namespace animation
}; // namespace skeletor
