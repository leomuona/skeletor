#ifndef UTIL_SEARCH_HPP
#define UTIL_SEARCH_HPP

#include <vector>

namespace skeletor {
namespace util {

int midpoint(int imin, int imax);

/**
 * Function is a bit specialized binary_search,
 * expects that T responds to T.id where id is type of E.
 *
 * So in short, T.id must be type of E.
 *
 * Oh, yeah, and expects that given vector is sorted.
 *
 * Uses < and > for E and T.id comparison.
 *
 * @param vector to search for
 * @param value to look for
 *
 * @return index of the value, or -1 if not found.
 */
template <typename T, typename E>
int binarySearch(const std::vector<T> &v, const E &id)
{
	int imin = 0;
	int imax = v.size()-1;

	while (imax >= imin) {
		int imid = midpoint(imin, imax);

		if (v[imid].id < id) {
			imin = imid + 1;
		} else if (v[imid].id > id) {
			imax = imid - 1;
		} else {
			return imid;
		}
	}

	return -1;
}

}; // namespace util
}; // namespace skeletor

#endif // UTIL_SEARCH_HPP
