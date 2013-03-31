#include "animation/skeleton_pose.hpp"

namespace skeletor {
namespace animation {

void SkeletonPose::apply(float time)
{
	m_localPoses.clear();

	std::vector<std::pair<Joint *, int> > joints;
	m_skeleton->preOrder(joints);

	for (int i=0; i<joints.size(); ++i) {
		Joint *joint = joints[i].first;
		float t = fmod(time, joint->getMaxTime());

		if (isnan(t)) {
			m_localPoses.push_back(math::Mat4x4f());
			continue;
		}

		std::pair<KeyFrame, KeyFrame> keyframes(joint->find(t));
		KeyFrame k = keyframes.first.lerp(keyframes.second, t);
		m_localPoses.push_back(k.getTransform());
	}
}

}; // namespace animation
}; // namespace skeletor
