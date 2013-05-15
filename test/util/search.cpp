#include "test/util/search.hpp"

#include "src/util/search.hpp"

#include <assert.h>
#include <string>
#include <stdio.h>

namespace skeletor {
namespace test {
namespace util {

typedef struct TestElem {
	int id;
	TestElem(int id) : id(id) {}
} TestElem;

int testSearch()
{
	using namespace skeletor::util;

	std::vector<TestElem *> v;

	// init array
	for (int i=-10; i<=10; ++i) {
		v.push_back(new TestElem(i));
	}

	// now do the search
	for (int i=10; i>=-10; --i) {
		int idx = binarySearch<TestElem *, int>(v, i);

		assert(idx != -1);
		assert(v[idx]->id == i);
	}

	assert((binarySearch<TestElem *, int>(v, 11) == -1));

	for (int i=0; i<v.size(); ++i) {
		delete v[i];
	}
	v.clear();

	return 0;
}

}; // namespace util
}; // namespace test
}; // namespace skeletor
