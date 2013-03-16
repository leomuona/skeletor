#include "animation/skeleton.hpp"
#include "animation/joint.hpp"

namespace skeletor {
namespace animation {

Skeleton::Skeleton(Joint *root)
	: m_root(root)
{
	std::vector<std::pair<Joint *, int> > joints;
	preOrder(joints);

	for (int i=0; i<joints.size(); ++i) {
		Joint *j = joints[i].first;
		m_joints.insert(std::pair<std::string, Joint *>(j->getID(), j));
	}
}

void Skeleton::preOrder(std::vector<std::pair<Joint *, int> > &v) const
{
	preOrder(v, m_root, 0);
}

void Skeleton::preOrder(std::vector<std::pair<Joint *, int> > &v, Joint *joint, int depth) const
{
	if (joint != NULL) {
		v.push_back(std::pair<Joint *, int>(joint, depth));
		const std::vector<Joint *> &children(joint->getChildren());
		for (int i=0; i<children.size(); ++i) {
			preOrder(v, children[i], depth+1);
		}
	}
}

}; // namespace animation
}; // namespace skeletor
