#pragma once

#include "ReachTreev2.h"
#include "TreeTraversal.h"

namespace hypro {

namespace detail {
template <typename R>
struct UnpackRepresentation {};

template <typename R>
struct UnpackRepresentation<ReachTreeNode<R>&> {
	using Representation = R;
};

template <typename R>
struct UnpackRepresentation<std::vector<ReachTreeNode<R>>&> {
	using Representation = R;
};

}  // namespace detail

template <class RootType, class Function>
void visitPreorder( RootType&& root, Function func ) {
	for ( auto& node : preorder( std::forward<RootType>( root ) ) ) {
		func( node );
	}
}

template <typename RootType>
auto getFlowpipes( RootType&& root ) -> std::vector<std::vector<typename detail::UnpackRepresentation<RootType>::Representation>> {
	std::vector<std::vector<typename detail::UnpackRepresentation<RootType>::Representation>> res;
	visitPreorder( std::forward<RootType>( root ), [&res]( auto& node ) { res.insert( res.end(), node.getFlowpipe() ); } );
	return res;
}

template <typename RootType>
auto getMaximalDepth( RootType&& root ) -> std::vector<std::vector<typename detail::UnpackRepresentation<RootType>::Representation>> {
	std::vector<std::vector<typename detail::UnpackRepresentation<RootType>::Representation>> res;
	visitPreorder( std::forward<RootType>( root ), [&res]( auto& node ) { res.insert( res.end(), node.getFlowpipe() ); } );
	return res;
}

template <typename RootType>
auto getNumberNodes( RootType&& root ) -> std::vector<std::vector<typename detail::UnpackRepresentation<RootType>::Representation>> {
	std::vector<std::vector<typename detail::UnpackRepresentation<RootType>::Representation>> res;
	visitPreorder( std::forward<RootType>( root ), [&res]( auto& node ) { res.insert( res.end(), node.getFlowpipe() ); } );
	return res;
}

template <typename RootType>
auto getNumberSegments( RootType&& root ) -> std::size_t {
	std::size_t res = 0;
	visitPreorder( std::forward<RootType>( root ), [&res]( auto& node ) { res += node.getFlowpipe().size(); } );
	return res;
}

template <typename RootType, typename Representation>
auto isAlreadyReachable( RootType&& root, Representation set ) -> bool {
	for ( auto& node : preorder( std::forward<RootType>( root ) ) ) {
		if ( node.getInitialSet().contains( set ) ) {
			return true;
		}
	}
	return false;
}

}  // namespace hypro
