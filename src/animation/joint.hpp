#ifndef JOINT_HPP
#define JOINT_HPP

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

	// human readable joint name.
	std::string m_name;

	// parent Joint, NULL on parent.
	Joint *m_parent;

	// child nodes of this node.
	std::vector<Joint *> m_children;

public:
	/**
	 * Constructor.
	 *
	 * @param parent joint, NULL if root.
	 * @param joints local matrix
	 * @param human readable name or something
	 */
	Joint(Joint *parent, const math::Mat4x4f &localMatrix, const std::string &name);

	/**
	 * Adds the given node as a child node to this.
	 *
	 * @param child node.
	 */
	void addChild(Joint *child);

	std::string getName() const;

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

};

}; // namespace animation
}; // namespace skeletor

#endif // JOINT_HPP
