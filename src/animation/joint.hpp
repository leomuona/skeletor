#ifndef JOINT_HPP
#define JOINT_HPP

#include "math/mat4x4.hpp"

#include <string>

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
};

}; // namespace animation
}; // namespace skeletor

#endif // JOINT_HPP
