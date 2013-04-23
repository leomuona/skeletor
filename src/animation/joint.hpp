#ifndef JOINT_HPP
#define JOINT_HPP

#include "animation/keyframe.hpp"
#include "math/mat4x4.hpp"

#include <string>
#include <vector>

namespace skeletor {
namespace animation {

class Joint
{
private:
	math::Mat4x4f m_localMatrix;
	math::Mat4x4f m_bindPoseMatrix;
	math::Mat4x4f m_invBindPoseMatrix;

	std::string m_id;
	std::string m_sid;

	// human readable joint name.
	std::string m_name;

	// parent Joint, NULL on parent.
	Joint *m_parent;

	// child nodes of this node.
	std::vector<Joint *> m_children;

	// keyframes of this joint.
	// this structure can be expected to be ordered by KeyFrames time.
	std::vector<KeyFrame> m_keyframes;

public:
	/**
	 * Constructor.
	 *
	 * @param parent joint, NULL if root.
	 * @param joints local matrix
	 */
	Joint(Joint *parent, const math::Mat4x4f &localMatrix);

	/**
	 * Adds the given node as a child node to this.
	 *
	 * @param child node.
	 */
	void addChild(Joint *child);

	void setName(const std::string &name);
	std::string getName() const;

	void setSID(const std::string &sid);
	std::string getSID() const;

	void setID(const std::string &id);
	std::string getID() const;

        Joint *getParent() const;

	/**
	 * Gives references to this joints keyframe container.
	 *
	 * @return reference to keyframe container.
	 */
	std::vector<KeyFrame> &getKeyFrames();
	/**
	 * Gives const references to this joints keyframe container.
	 *
	 * @return const reference to keyframe container.
	 */
	const std::vector<KeyFrame> &getKeyFrames() const;

	/**
	 * Finds two closest keyframes to given time.
	 *
	 * @param time.
	 * @return std::pair<> of two closest KeyFrames;
	 */
	std::pair<KeyFrame, KeyFrame> find(float time) const;

	/**
	 * Getter for children
	 *
	 * @return children of the current joint
	 */
	const std::vector<Joint *> &getChildren() const;

	const math::Mat4x4f &getLocalMatrix() const;
	math::Mat4x4f &getLocalMatrix();
	const math::Mat4x4f &getBindPoseMatrix() const;
	math::Mat4x4f &getBindPoseMatrix();
	const math::Mat4x4f &getInvBindPoseMatrix() const;
	math::Mat4x4f &getInvBindPoseMatrix();

	/**
	 * Gets the max time of keyframes
	 *
	 * @return max time.
	 */
	float getMaxTime() const;

	/**
	 * Gets the min time of keyframes
	 *
	 * @return min time.
	 */
	float getMinTime() const;

	/**
	 * Sets the bind pose matrix.
	 *
	 * @param bind pose matrix
	 */
	void setBindPoseMatrix(const math::Mat4x4f &bindPoseMatrix);

	/**
	 * Fixes blender exported keyframes.
	 *
	 * Changes the space from 'global space' to 'bind pose space'.
	 */
	void fixBlenderExportKeyFrames();

};

}; // namespace animation
}; // namespace skeletor

#endif // JOINT_HPP
