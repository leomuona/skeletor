#include "animation/skeleton.hpp"
#include "animation/joint.hpp"

namespace skeletor {
namespace animation {

Skeleton::Skeleton(Joint *root, const std::string &source)
	: m_root(root)
	, m_source(source)
{
	std::vector<std::pair<Joint *, int> > joints;
	preOrder(joints);

	for (int i=0; i<joints.size(); ++i) {
		Joint *j = joints[i].first;
		m_joints.insert(std::pair<std::string, Joint *>(j->getID(), j));
	}
}

void Skeleton::fixMayaExportBindPoses()
{
	std::map<std::string, Joint *>::iterator it = m_joints.begin();
	while (it != m_joints.end()) {
		Joint *joint = it->second;

		math::Mat4x4f bindPose = joint->getLocalMatrix();
		if (!joint->getKeyFrames().empty()) {
			bindPose *= joint->getKeyFrames()[0].getTransform().getInverse();
		}
		joint->setBindPoseMatrix(bindPose);

		++it;
	}
}

void Skeleton::fixBlenderExportKeyFrames()
{
	std::map<std::string, Joint *>::iterator it = m_joints.begin();
	while (it != m_joints.end()) {
		it->second->fixBlenderExportKeyFrames();
		++it;
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
