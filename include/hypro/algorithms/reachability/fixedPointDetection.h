/*
 * Copyright (c) 2021.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
/*
 * Created by Stefan Schupp <stefan.schupp@tuwien.ac.at> on 09.09.21.
 */

#pragma once
#include "../../datastructures/reachability/ReachTreev2.h"
#include "../../representations/GeometricObjectBase.h"

namespace hypro {

template <typename Set>
bool detectJumpFixedPoint( ReachTreeNode<Set>& node, std::vector<ReachTreeNode<Set>>& roots ) {
	using Number = typename Set::NumberType;
#ifdef HYPRO_STATISTICS
	START_BENCHMARK_OPERATION( "Fixed-point detection" );
#endif
	std::vector<carl::Interval<Number>> boundingBox = Converter<Number>::toBox( node.getInitialSet() ).intervals();
	for ( auto& root : roots ) {
		for ( auto& treeNode : preorder( root ) ) {
			const auto& nodeInitialBoundingBox = treeNode.getInitialBoundingBox();
			// if the location matches and the bounding boxes contain each other, then also perform the (possibly expensive) full containment test.
			if ( nodeInitialBoundingBox && treeNode.getLocation() == node.getLocation() && std::equal( std::begin( boundingBox ), std::end( boundingBox ), std::begin( nodeInitialBoundingBox.value() ), std::end( nodeInitialBoundingBox.value() ), []( const auto& setBoxIntv, const auto& initBoxIntv ) { return initBoxIntv.contains( setBoxIntv ); } ) && treeNode.getInitialSet().contains( node.getInitialSet() ) ) {
				TRACE( "hypro.reachability", "Fixed-point detected." );
#ifdef HYPRO_STATISTICS
				STOP_BENCHMARK_OPERATION( "Fixed-point detection" );
#endif
				node.setFixedPoint();
				return true;
			}
		}
	}
#ifdef HYPRO_STATISTICS
	STOP_BENCHMARK_OPERATION( "Fixed-point detection" );
#endif
	node.setFixedPoint( false );
	return false;
}

}  // namespace hypro
