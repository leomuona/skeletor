#include "animation/skeleton_pose.hpp"

#include <assert.h>

namespace skeletor {
namespace animation {

SkeletonPose::SkeletonPose()
	: m_skeleton(NULL)
{
}

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
		std::pair<KeyFrame, KeyFrame> keyframes(joint->find(t));
		KeyFrame k = keyframes.first.lerp(keyframes.second, t);
		m_localPoses.insert(std::pair<const Joint *, math::Mat4x4f>(joint, k.getTransform()));
	}
}

void SkeletonPose::xFade(SkeletonPose &a, SkeletonPose &b, float dt, float max)
{
	m_localPoses.clear();

	Skeleton &as = a.getSkeleton();
	Skeleton &bs = b.getSkeleton();

	std::vector<std::pair<Joint *, int> > a_joints, b_joints;
	as.preOrder(a_joints);
	bs.preOrder(b_joints);

	assert(a_joints.size() == b_joints.size());

	for (int i=0; i<a_joints.size(); ++i) {
		const Joint *a_joint = a_joints[i].first;
		const Joint *b_joint = b_joints[i].first;

		KeyFrame begin(0, a.getTransform(a_joint));
		KeyFrame end(max, b.getTransform(b_joint));
		KeyFrame k = begin.lerp(end, dt);

		m_localPoses.insert(std::pair<const Joint *, math::Mat4x4f>(a_joint, k.getTransform()));
	}
}

}; // namespace animation
}; // namespace skeletor
