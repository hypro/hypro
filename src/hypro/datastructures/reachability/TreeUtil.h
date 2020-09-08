#pragma once
#include "TreeTraversal.h"

namespace hypro {
template <typename R>
std::size_t getNumberNodes( R& root ) {
	TreeIterator<R> cur{ root };
	TreeIterator<R> end{};
	std::size_t count = 0;
	while ( cur != end ) {
		++cur;
		++count;
	}
	return count;
}
}  // namespace hypro
