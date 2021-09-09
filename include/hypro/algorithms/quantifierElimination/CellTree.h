#pragma once
#include "../../carlTypes.h"

#include <optional>
#include <vector>

namespace hypro {
namespace qe {

template <typename Data>
struct CellTreeNode {
	Data mData;
	std::vector<const CellTreeNode<Data>&> mChildren;
	std::optional<const CellTreeNode<Data>&> mParent;

	void addChild( const CellTreeNode<Data>& c ) {
		mChildren.push_back( c );
		c.mParent = ( *this );
	}
}

template <typename Data>
struct CellTree {
	std::optional<const CellTreeNode<Data>&> mRoot;
}

}  // namespace qe
}  // namespace hypro
