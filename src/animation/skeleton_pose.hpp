#ifndef SKELETON_POSE_HPP
#define SKELETON_POSE_HPP

#include "animation/skeleton.hpp"
#include "math/mat4x4.hpp"
#include "player.hpp"

#include <map>

namespace skeletor {
namespace animation {

class Joint;

/**
 * Reflects a single pose (current pose) of the skeleton.
 *
 * m_localPoses are local transformed matrices.
 *
 * calling apply(current time), sets the skeleton to given time.
 */
class SkeletonPose
{
private:
	// skeleton, includes num of joints
	Skeleton* m_skeleton;

	// Player controlling this skeleton
	// TODO: make generic Character class.
	Player *m_player;

	// local joint poses, as many as num of skeleton's joints
	std::map<const Joint *, math::Mat4x4f> m_localPoses;

public:
	SkeletonPose();

	Skeleton &getSkeleton();
	const Skeleton &getSkeleton() const;

	Player *getPlayer();
	const Player *getPlayer() const;

	void setSkeleton(Skeleton *skeleton);
	void setPlayer(Player *player);

	/**
	 * Gets the transformation for the given joint.
	 *
	 * @param joint
	 *
	 * @return transformation.
	 */
	math::Mat4x4f getTransform(const Joint *joint) const;

	/**
	 * Applies the Pose to skeleton by transforming m_localPoses.
	 *
	 * @param time, must be between [0, max skeleton time]
	 */
	void apply(float time);

};

inline Skeleton &SkeletonPose::getSkeleton()
{
	return *m_skeleton;
}

inline const Skeleton &SkeletonPose::getSkeleton() const
{
	return *m_skeleton;
}

inline Player *SkeletonPose::getPlayer()
{
	return m_player;
}

inline const Player *SkeletonPose::getPlayer() const
{
	return m_player;
}

inline void SkeletonPose::setSkeleton(Skeleton *skeleton)
{
	m_skeleton = skeleton;
}

inline void SkeletonPose::setPlayer(Player *player)
{
	m_player = player;
}

}; // namespace animation
}; // namespace skeletor

#endif // SKELETON_POSE_HPP
