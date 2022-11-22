/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "ReachTreev2.h"
#include "TreeTraversal.h"

namespace hypro {

namespace detail {
template <typename R>
struct UnpackRepresentation {};

template <typename R, class... Ts>
struct UnpackRepresentation<ReachTreeNode<R, Ts...>&> {
	using Representation = R;
};

template <typename R, class... Ts>
struct UnpackRepresentation<const ReachTreeNode<R, Ts...>&> {
	using Representation = R;
};

template <typename R, class... Ts>
struct UnpackRepresentation<std::vector<ReachTreeNode<R, Ts...>>&> {
	using Representation = R;
};

template <typename R, class... Ts>
struct UnpackRepresentation<std::vector<const ReachTreeNode<R, Ts...>>&> {
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
auto getSegments( RootType&& root ) -> std::vector<typename detail::UnpackRepresentation<RootType>::Representation> {
	std::vector<typename detail::UnpackRepresentation<RootType>::Representation> res;
	visitPreorder( std::forward<RootType>( root ), [&res]( auto& node ) { res.insert( res.end(), std::begin( node.getFlowpipe() ), std::end( node.getFlowpipe() ) ); } );
	return res;
}

template <typename RootType>
auto getMaximalDepth( RootType&& root ) -> std::vector<std::vector<typename detail::UnpackRepresentation<RootType>::Representation>> {
	std::vector<std::vector<typename detail::UnpackRepresentation<RootType>::Representation>> res;
	visitPreorder( std::forward<RootType>( root ), [&res]( auto& node ) { res.insert( res.end(), node.getFlowpipe() ); } );
	return res;
}

template <typename RootType>
auto getNumberNodes( std::vector<RootType>&& roots ) -> std::size_t {
	std::size_t res{ 0 };
	for ( auto&& root : roots ) {
		visitPreorder( std::forward<RootType>( root ), [&res]( auto& node ) { ++res; } );
	}
	return res;
}

template <typename RootType>
auto getNumberNodes( RootType&& root ) -> std::size_t {
	std::size_t res{ 0 };
	visitPreorder( std::forward<RootType>( root ), [&res]( auto& node ) { ++res; } );
	return res;
}

template <typename RootType>
auto getNumberSegments( std::vector<RootType>&& roots ) -> std::size_t {
	std::size_t res = 0;
	for ( auto&& root : roots ) {
		visitPreorder( std::forward<RootType>( root ), [&res]( auto& node ) { res += node.getFlowpipe().size(); } );
	}
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
