#ifndef SKELETON_POSE_HPP
#define SKELETON_POSE_HPP

#include "math/mat4x4.hpp"
#include "animation/skeleton.hpp"

#include <vector>

namespace skeletor {
namespace animation {

class SkeletonPose
{
private:
        // skeleton, includes num of joints 
        Skeleton* m_skeleton;        
        // local joint poses, as many as num of skeleton's joints
        std::vector<math::Mat4x4f> m_localPoses;

public:

	Skeleton &getSkeleton();
	const Skeleton &getSkeleton() const;

	void setSkeleton(Skeleton *skeleton);
};

inline Skeleton &SkeletonPose::getSkeleton()
{
	return *m_skeleton;
}

inline const Skeleton &SkeletonPose::getSkeleton() const
{
	return *m_skeleton;
}

inline void SkeletonPose::setSkeleton(Skeleton *skeleton)
{
	m_skeleton = skeleton;
}

}; // namespace animation
}; // namespace skeletor

#endif // SKELETON_POSE_HPP
