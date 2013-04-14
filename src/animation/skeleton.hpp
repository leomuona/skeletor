#ifndef SKELETON_HPP
#define SKELETON_HPP

#include "animation/joint.hpp"

#include <map>
#include <ostream>
#include <utility>
#include <vector>

namespace skeletor {
namespace animation {

class Skeleton
{
private:
	Joint *m_root;

	// access to each joint presumably in O(1) by joints id.
	std::map<std::string, Joint *> m_joints;

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
	 * Get the joint by their id.
	 *
	 * @param joint string unique id
	 *
	 * @return joint
	 */
	Joint *getJoint(const std::string &id);
	const Joint *getJoint(const std::string &id) const;

	/**
	 * Overloaded << ostream operator.
	 * Makes it possible to: std::cout << this.
	 */
	friend std::ostream &operator<<(std::ostream &os, const Skeleton &s);

	/**
	 * Sets up the bind pose matrices for the joints.
	 */
	void setupBindPoseMatrices();

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

inline Joint *Skeleton::getJoint(const std::string &id)
{
	std::map<std::string, Joint *>::iterator it;
	it = m_joints.find(id);
	return (it == m_joints.end()) ? NULL : it->second;
}

inline const Joint *Skeleton::getJoint(const std::string &id) const
{
	std::map<std::string, Joint *>::const_iterator it;
	it = m_joints.find(id);
	return (it == m_joints.end()) ? NULL : it->second;
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
