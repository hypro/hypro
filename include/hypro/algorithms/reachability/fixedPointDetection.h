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

template <typename Number, typename Converter, typename Settings>
bool detectJumpFixedPoint( ReachTreeNode<BoxT<Number, Converter, Settings>>& node, std::vector<ReachTreeNode<BoxT<Number, Converter, Settings>>>& roots, bool use_partial_coverage = false ) {
	assert( !node.getInitialBoundingBox() && "The bounding box should not have been set to ensure the node is not compared to itself." );
#ifdef HYPRO_STATISTICS
	START_BENCHMARK_OPERATION( "Fixed-point detection" );
#endif

	std::vector<BoxT<Number, Converter, Settings>> initialBoxes{ node.getInitialSet() };
	// auto printBoxes = [](const std::vector<BoxT<Number,Converter,Settings>>& boxes){
	//	for(const auto& b : boxes){
	//		std::cout << b << "\n";
	//	}
	//	std::cout << std::endl;
	// };
	// std::cout << "Intialize boxes to be checked to \n";
	// printBoxes(initialBoxes);
	for ( auto& root : roots ) {
		for ( auto& treeNode : preorder( root ) ) {
			// if the location matches and treenode is not the passed node (the passed node has no bounding box yet)
			if ( treeNode.getInitialBoundingBox() && treeNode.getLocation() == node.getLocation() ) {
				// use expensive coverage check
				if ( use_partial_coverage ) {
					// from all currently held remaining initial boxes subtract the current initial set to check (partial) coverage
					std::vector<Box<Number>> tmp;
					// std::cout << "current initial set:" << treeNode.getInitialSet();
					// std::cout << "current boxes:\n";
					// printBoxes(initialBoxes);
					for ( const auto& box : initialBoxes ) {
						auto remaining_boxes = box.setMinus2( treeNode.getInitialSet() );
						tmp.insert( std::end( tmp ), std::begin( remaining_boxes ), std::end( remaining_boxes ) );
					}
					// clear duplicates
					for ( auto it = std::begin( tmp ); it != std::end( tmp ); ++it ) {
						for ( auto oit = std::next( it ); oit != std::end( tmp ); ) {
							if ( *it == *oit ) {
								oit = tmp.erase( oit );
							} else {
								++oit;
							}
						}
					}
					// the remaining boxes are the ones used in the next iteration
					swap( tmp, initialBoxes );
					// std::cout << "remaining boxes:\n";
					// printBoxes(initialBoxes);
					if ( initialBoxes.empty() ) {
#ifdef HYPRO_STATISTICS
						STOP_BENCHMARK_OPERATION( "Fixed-point detection" );
						COUNT( "FP-by-coverage" );
#endif
						node.setFixedPoint();
						return true;
					}
				} else {
					// use standard check
					const auto& nodeInitialBoundingBox = treeNode.getInitialBoundingBox();
					if ( nodeInitialBoundingBox && treeNode.getInitialSet().contains( initialBoxes.front() ) )
						TRACE( "hypro.reachability", "Fixed-point detected." );
#ifdef HYPRO_STATISTICS
					STOP_BENCHMARK_OPERATION( "Fixed-point detection" );
#endif
					node.setFixedPoint();
					return true;
				}
			}
		}
	}
#ifdef HYPRO_STATISTICS
	STOP_BENCHMARK_OPERATION( "Fixed-point detection" );
#endif
	node.setFixedPoint( false );
	return false;
}

template <typename Set>
bool detectJumpFixedPoint( ReachTreeNode<Set>& node, std::vector<ReachTreeNode<Set>>& roots, bool use_partial_coverage = false ) {
	assert( !node.getInitialBoundingBox() && "The bounding box should not have been set to ensure the node is not compared to itself." );
	using Number = typename Set::NumberType;
#ifdef HYPRO_STATISTICS
	START_BENCHMARK_OPERATION( "Fixed-point detection" );
#endif
	std::vector<carl::Interval<Number>> boundingBox = Converter<Number>::toBox( node.getInitialSet() ).intervals();
	for ( auto& root : roots ) {
		for ( auto& treeNode : preorder( root ) ) {
			// if the location matches and the bounding boxes contain each other, then also perform the (possibly expensive) full containment test.
			// Attention: to ensure the current node is not used by itself, its bounding box has not been set yet.
			if ( treeNode.getLocation() == node.getLocation() ) {
				const auto& nodeInitialBoundingBox = treeNode.getInitialBoundingBox();
				if ( nodeInitialBoundingBox && std::equal( std::begin( boundingBox ), std::end( boundingBox ), std::begin( nodeInitialBoundingBox.value() ), std::end( nodeInitialBoundingBox.value() ), []( const auto& setBoxIntv, const auto& initBoxIntv ) { return initBoxIntv.contains( setBoxIntv ); } ) && treeNode.getInitialSet().contains( node.getInitialSet() ) ) {
					TRACE( "hypro.reachability", "Fixed-point detected." );
#ifdef HYPRO_STATISTICS
					STOP_BENCHMARK_OPERATION( "Fixed-point detection" );
#endif
					node.setFixedPoint();
					return true;
				}
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
