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
}

}; // namespace animation
}; // namespace skeletor

#endif // SKELETON_POSE_HPP
