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
bool detectJumpFixedPoint( ReachTreeNode<BoxT<Number, Converter, Settings>>& node, std::vector<ReachTreeNode<BoxT<Number, Converter, Settings>>>& roots, bool use_partial_coverage = false, std::size_t first_segments_to_test = 0 ) {
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
		for ( ReachTreeNode<BoxT<Number, Converter, Settings>>& treeNode : preorder( root ) ) {
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
					assert( treeNode.getInitialBoundingBox() );
					// use standard check
					const auto& nodeInitialBoundingBox = treeNode.getInitialBoundingBox();
					if ( nodeInitialBoundingBox && treeNode.getInitialSet().contains( initialBoxes.front() ) ) {
						TRACE( "hypro.reachability", "Fixed-point detected." );
						std::cout << "Found fixed point for location " << node.getLocation()->getName() << ". Set " << initialBoxes.front() << " is contained in the initial set " << treeNode.getInitialSet() << std::endl;
#ifdef HYPRO_STATISTICS
						STOP_BENCHMARK_OPERATION( "Fixed-point detection" );
#endif
						node.setFixedPoint();
						return true;
					} else if ( first_segments_to_test > 0 ) {
						std::size_t set_index = 0;
						while ( set_index < first_segments_to_test && set_index < treeNode.getFlowpipe().size() ) {
							if ( treeNode.getFlowpipe()[set_index].contains( initialBoxes.front() ) ) {
								std::cout << "Found fixed point for location " << node.getLocation()->getName() << ". Set " << initialBoxes.front() << " is contained in segment " << set_index << ": " << treeNode.getFlowpipe()[set_index] << std::endl;
								node.setFixedPoint();
								return true;
							}
							++set_index;
						}
					}
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

template <typename Number, typename Converter, typename Settings>
bool is_covered( const BoxT<Number, Converter, Settings>& coveree, const std::vector<BoxT<Number, Converter, Settings>>& coverers ) {
	using Box = BoxT<Number, Converter, Settings>;
	std::vector<Box> remainders{ coveree };
	// std::cout << "Trying to cover " << coveree << " by " << coverers << std::endl;

	for ( const auto& cover_box : coverers ) {
		std::vector<Box> next_remainders{};
		for ( const auto& remainder : remainders ) {
			auto tmp = remainder.setMinus2( cover_box );
			next_remainders.insert( std::end( next_remainders ), std::begin( tmp ), std::end( tmp ) );
		}
		remainders = next_remainders;
	}
	// std::cout << "Remainders after coverage: " <<  remainders << std::endl;
	return remainders.empty();
}

template <typename Set>
bool is_covered( const Set&, const std::vector<Set>& ) {
	return false;
}

/**
 * Collects pointers to all transitions between a node and its parent that are Zeno
 * @details The idea is to check, whether the initial set in the child node fully satisfies a guard of a transition to the parent node and whether both transitions do have identity-resets. In this case, the jump back does not provide new information but allows for Zeno-behavior.
 * @tparam Set The used set representation
 * @param parent The parent node
 * @param child The child node
 * @return A vector of transitions that are Zeno
 */
template <typename Set>
std::vector<const Transition<typename Set::NumberType>*> getZenoTransitions( const ReachTreeNode<Set>* parent, const ReachTreeNode<Set>* child ) {
	using N = typename Set::NumberType;
	std::vector<const Transition<N>*> result;
	//// structural check: if child is not a child of parent, exit
	//// TODO this is a pointer comparison, we need a comparison of reachTreeNodes
	// if( std::none_of(std::begin(parent->getChildren()), std::end(parent->getChildren()), [child](const auto* childNode){ return childNode == child; }) ) {
	//	return result;
	// }
	//  structural check: if the reset from the parent to the child is non-identity, this cannot be a Zeno transition
	//  TODO this is a very conservative check - if the overlay of both resets yields identity, this is also a Zeno transition.
	if ( !child->getTransition()->getReset().isIdentity() ) {
		return result;
	}
	// simple check: if the initial set fully satisfies the guard back to the parent and no variable is reset, we know (since the initial set already fully satisfies the guard from the parent to the child), that this is a Zeno loop.
	for ( auto& transition : child->getLocation()->getTransitions() ) {
		if ( transition->getTarget() == parent->getLocation() && transition->getReset().isIdentity() && intersect( child->getInitialSet(), transition->getGuard() ).first == CONTAINMENT::FULL ) {
			std::cout << "There is a Zeno-transition from " << transition->getSource()->getName() << " to " << transition->getTarget()->getName() << " with set " << child->getInitialSet() << std::endl;
			result.push_back( transition.get() );
		}
	}
	return result;
}

}  // namespace hypro
