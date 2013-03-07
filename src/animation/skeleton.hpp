#ifndef SKELETON_HPP
#define SKELETON_HPP

#include "animation/joint.hpp"

#include <ostream>
#include <utility>
#include <vector>

namespace skeletor {
namespace animation {

class Skeleton
{
private:
	Joint *m_root;

public:
	/**
	 * Contructor.
	 *
	 * @param root joint.
	 */
	Skeleton(Joint *root);

	Joint &getRootJoint();
	const Joint &getRootJoint() const;

	/**
	 * Overloaded << ostream operator.
	 * Makes it possible to: std::cout << this.
	 */
	friend std::ostream &operator<<(std::ostream &os, const Skeleton &s);

	/**
	 * Forms a preorder traverse into v vector.
	 *
	 * Calls private preorder method: liek: preorder(v, m_root, 0).
	 *
	 * @param vector v to save the traverse order.
	 */
	void preOrder(std::vector<std::pair<Joint *,int> > &v) const;

private:
	/**
	 * @param vector v to save the traverse order.
	 * @param current joint
	 * @param current depth
	 */
	void preOrder(std::vector<std::pair<Joint *,int> > &v, Joint *joint, int depth) const;

};

inline Joint &Skeleton::getRootJoint()
{
	return *m_root;
}

inline const Joint &Skeleton::getRootJoint() const
{
	return *m_root;
}

inline std::ostream &operator<<(std::ostream &os, const Skeleton &s)
{
	std::vector<std::pair<Joint *, int> > joints;
	s.preOrder(joints);

	for (int i=0; i<joints.size(); ++i) {
		Joint *joint = joints[i].first;
		for (int j=0; j<joints[i].second; ++j) os << "  ";
		os << joint->getName() << std::endl;
	}

	return os;
}

}; // namespace animation
}; // namespace skeletor

#endif // SKELETON_HPP
