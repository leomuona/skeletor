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

	friend std::ostream &operator<<(std::ostream &os, const Skeleton &s);

	void preOrder(std::vector<std::pair<Joint *,int> > &v) const;
	void preOrder(std::vector<std::pair<Joint *,int> > &v, Joint *joint, int depth) const;

};

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
