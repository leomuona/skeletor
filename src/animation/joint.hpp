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
	// inverse bind pose transform.
	math::Mat4x4f m_invBindPose;

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
	 * @param invert bind pose matrix transormation
	 * @param human readable name or something
	 */
	Joint(Joint *parent, const math::Mat4x4f &invBindPose, const std::string &name);

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

};

}; // namespace animation
}; // namespace skeletor

#endif // JOINT_HPP
