#include "animation/skeleton_pose.hpp"

namespace skeletor {
namespace animation {

math::Mat4x4f SkeletonPose::getTransform(const Joint *joint) const
{
	std::map<const Joint *, math::Mat4x4f>::const_iterator it;
	it = m_localPoses.find(joint);
	if (it != m_localPoses.end()) {
		return it->second;
	} else {
		return math::Mat4x4f();
	}
}

void SkeletonPose::apply(float time)
{
	m_localPoses.clear();

	std::vector<std::pair<Joint *, int> > joints;
	m_skeleton->preOrder(joints);

	for (int i=0; i<joints.size(); ++i) {
		const Joint *joint = joints[i].first;
		float t = fmod(time, joint->getMaxTime());

		if (isnan(t)) {
			m_localPoses.insert(std::pair<const Joint *, math::Mat4x4f>(joint, math::Mat4x4f()));
			continue;
		}

		std::pair<KeyFrame, KeyFrame> keyframes(joint->find(t));
		KeyFrame k = keyframes.first.lerp(keyframes.second, t);
		m_localPoses.insert(std::pair<const Joint *, math::Mat4x4f>(joint, k.getTransform()));
	}
}

}; // namespace animation
}; // namespace skeletor
