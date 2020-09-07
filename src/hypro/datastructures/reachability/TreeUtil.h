#pragma once
#include "TreeTraversal.h"

namespace hypro {
template <typename R>
std::size_t getNumberNodes( R& root ) {
	TreeIterator<TreeNode<R>> cur{ root };
	TreeIterator<TreeNode<R>> end{};
	std::size_t count = 0;
	while ( cur != end ) {
		++cur;
		++count;
	}
	return count;
}
}  // namespace hypro
