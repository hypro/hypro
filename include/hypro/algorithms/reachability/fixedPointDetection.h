/*
 * Copyright (c) 2022.
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
#include "../../representations/Polytopes/carlPolytope/util.h"
#include "../../representations/equivalence.h"
#include "FlowpipeConstructionConvenience.h"

namespace hypro {

/**
 * Function to detect a fixed point for a potential jump. This function is a specialization.
 *
 * @details All nodes in the current reach tree are traversed and the method tests either, whether the current nodes' initial set is contained in the initial sets of the other nodes or in case boxes are used additionally, if the current nodes' initial set can be covered.
 * @tparam Number The used number type
 * @tparam Converter The converter used by the representation
 * @tparam Settings The settings of the representation
 * @param node The current node
 * @param roots The set of roots of the current reach tree
 * @param use_partial_coverage If true, coverage-tests are run as well
 * @param first_segments_to_test Number of segments at the beginning of a flowpipe that are tested for containment
 * @return True, if a fixed point has been detected, false otherwise
 */
template <typename Number, typename Converter, typename Settings, typename Location>
bool detectJumpFixedPoint( ReachTreeNode<BoxT<Number, Converter, Settings>, Location>& node, std::vector<ReachTreeNode<BoxT<Number, Converter, Settings>, Location>>& roots, std::function<bool( const BoxT<Number, Converter, Settings>&, const Location* )>& callback, bool use_partial_coverage = false, std::size_t first_segments_to_test = 0 ) {
	DEBUG( "hypro.reachability", "Try to find fixed point for node @" << &node );
	using BoxVector = std::vector<BoxT<Number, Converter, Settings>>;
	assert( !node.getInitialBoundingBox() && "The bounding box should not have been set to ensure the node is not compared to itself." );
#ifdef HYPRO_STATISTICS
	START_BENCHMARK_OPERATION( "Fixed-point detection" );
#endif

	// try callback
	if ( callback ) {
		if ( callback( node.getInitialSet(), node.getLocation() ) ) {
			node.setFixedPoint( true );
			return true;
		}
	}

	BoxVector initialBoxes{ node.getInitialSet() };
	for ( auto& root : roots ) {
		for ( ReachTreeNode<BoxT<Number, Converter, Settings>, Location>& treeNode : preorder( root ) ) {
			// if the location matches and treenode is not the passed node (the passed node has no bounding box yet)
			if ( treeNode.getInitialBoundingBox() && treeNode.getLocation() == node.getLocation() ) {
				// use expensive coverage check
				if ( use_partial_coverage ) {
					// from all currently held remaining initial boxes subtract the current initial set to check (partial) coverage
					BoxVector tmp;
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
					if ( tmp.empty() ) {
#ifdef HYPRO_STATISTICS
						STOP_BENCHMARK_OPERATION( "Fixed-point detection" );
						COUNT( "FP-by-coverage" );
#endif
						DEBUG( "hypro.reachability", "The nodes' initial set " << node.getInitialSet() << " in location " << node.getLocation()->getName() << " could be covered by several other initial sets." );
						node.setFixedPoint( true, &treeNode );
						return true;
					}
#ifdef HYPRO_LOGGING
					DEBUG( "hypro.reachability", "Remaining boxes to be covered: " );
					for ( const auto& b : tmp ) {
						DEBUG( "hypro.reachability", b );
					}
#endif
					// the remaining boxes are the ones used in the next iteration
					swap( tmp, initialBoxes );
				} else {
					assert( treeNode.getInitialBoundingBox() );
					// use standard check
					const auto& nodeInitialBoundingBox = treeNode.getInitialBoundingBox();
					if ( nodeInitialBoundingBox && treeNode.getInitialSet().contains( initialBoxes.front() ) ) {
						DEBUG( "hypro.reachability", "Found fixed point for node @" << &node << " in location " << node.getLocation()->getName() << ". Set " << initialBoxes.front() << " is contained in the initial set " << treeNode.getInitialSet() );
#ifdef HYPRO_STATISTICS
						STOP_BENCHMARK_OPERATION( "Fixed-point detection" );
#endif
						node.setFixedPoint( true, &treeNode );
						return true;
					} else if ( first_segments_to_test > 0 ) {
						// check if the initial set can be covered by the given number of segments from the flowpipe of the current node
						if ( is_covered( node.getInitialSet(), BoxVector( std::begin( treeNode.getFlowpipe() ), std::next( std::begin( treeNode.getFlowpipe() ), first_segments_to_test ) ) ) ) {
							DEBUG( "hypro.reachability", "Found fixed point for node @" << &node << " in location " << node.getLocation()->getName() << ". Achieved coverage by the first " << first_segments_to_test << " segments." );
							node.setFixedPoint();
							return true;
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

/**
 * General function to detect fixed points for jumps.
 *
 * @details The function checks for containment of the jump-successor set within one of the initial sets in the current reach tree.
 * @tparam Set The set-representation
 * @param node The current node
 * @param roots The set of roots of the current reach tree
 * @return True, if a fixed point has been detected, false otherwise
 */
template <typename Set, typename Loc>
bool detectJumpFixedPoint( ReachTreeNode<Set, Loc>& node, std::vector<ReachTreeNode<Set, Loc>>& roots, std::function<bool( const Set&, const Loc* )>&, bool, std::size_t ) {
	assert( !node.getInitialBoundingBox() && "The bounding box should not have been set to ensure the node is not compared to itself." );
	using Number = typename Set::NumberType;
#ifdef HYPRO_STATISTICS
	START_BENCHMARK_OPERATION( "Fixed-point detection" );
#endif
	std::vector<carl::Interval<Number>> boundingBox = computeBoundingBox( node.getInitialSet() ).intervals();
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

/**
 * Checks whether a box is covered by a set of boxes.
 * @tparam Number The number representation
 * @tparam Converter The converter used by the representation
 * @tparam Settings The settings of the representation
 * @param coveree The box to be covered
 * @param coverers The set of boxes that should cover the coveree
 * @return True, if the coveree can be fully covered by the coverers, false otherwise
 */
template <typename Number, typename Converter, typename Settings>
bool is_covered( const BoxT<Number, Converter, Settings>& coveree, const std::vector<BoxT<Number, Converter, Settings>>& coverers ) {
	using Box = BoxT<Number, Converter, Settings>;
	std::vector<Box> remainders{ coveree };

	for ( const auto& cover_box : coverers ) {
		std::vector<Box> next_remainders{};
		for ( const auto& remainder : remainders ) {
			auto tmp = remainder.setMinus2( cover_box );
			next_remainders.insert( std::end( next_remainders ), std::begin( tmp ), std::end( tmp ) );
		}
		remainders = next_remainders;
	}
	return remainders.empty();
}

/**
 * General function for checking coverage - since only boxes can be used for this efficiently, always returns false
 * @tparam Set The set-representation
 * @return False
 */
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

/**
 * Function to check, whether the incoming transition of the passed node closes a Zeno-cycle.
 * @details The idea is to check, whether the initial set in the child node fully satisfies a guard of a transition to the parent node and whether both transitions do have identity-resets. In this case, the jump back does not provide new information but allows for Zeno-behavior.
 * @tparam Set The used set representation
 * @param child The child node
 * @return A vector of transitions that are Zeno
 */
template <typename Set, typename Loc>
std::vector<const Transition<typename Set::NumberType, Loc>*> getZenoTransitions( const ReachTreeNode<Set, Loc>* child ) {
	using N = typename Set::NumberType;
	std::vector<const Transition<N, Loc>*> result;
	// search in the path to the root for a zeno-cycle
	auto* parent = child->getParent();
	// collect cummulative reset
	Reset cummulative = child->getTransition()->getReset();
	while ( parent != nullptr ) {
		// simple check: if the initial set fully satisfies the guard back to the parent and no variable is reset, we know (since the initial set already fully satisfies the guard from the parent to the child), that this is a Zeno loop.
		for ( auto& transition : child->getLocation()->getTransitions() ) {
			// TODO this check is very conservative - here we check, whether the initial set is fully contained, while we could also check for partial coverage
			// and only consider this part.
			if ( transition->getTarget() == parent->getLocation() && ( cummulative + transition->getReset() ).isIdentity() && intersect( child->getInitialSet(), transition->getGuard() ).first == CONTAINMENT::FULL ) {
				DEBUG( "hypro.reachability", "Detected Zeno-transition from " << transition->getSource()->getName() << " to " << transition->getTarget()->getName() << " with set " << child->getInitialSet() )
				result.push_back( transition.get() );
			}
		}
		// update the cummulative reset, if possible
		if ( parent->getTransition() != nullptr ) {
			cummulative = cummulative + parent->getTransition()->getReset();
		}
		assert( parent->getTransition() != nullptr || parent->getParent() == nullptr );
		// ascend, to checkk if the parent can be part of a Zeno cycle
		parent = parent->getParent();
	}
	return result;
}

template <class... Ts>
bool isZenoCycle( const Path<Ts...>& path ) {
	// check, whether the locations match
	if ( path.elements.front().second->getSource() != path.elements.back().second->getTarget() ) {
		return false;
	}
#ifdef HYPRO_HAVE_SMT
	// keep first guard set
	auto initialGuardCondition = CarlPolytope<Number>( path.elements.front().second->getGuard().getMatrix(), path.elements.front().second->getGuard().getVector() );
	// manually set dimension as the guard-condition may be "true" and hides the state space dimension
	initialGuardCondition.setDimension( path.elements.front().second->getSource()->dimension() );
	//  collect expression for all guards and resets
	auto currentSet = initialGuardCondition;
	for ( const auto& element : path.elements ) {
		auto& guardCondition = element.second->getGuard();
		auto& reset = element.second->getReset();
		//  non-trivial guard -> dimensions must be equal
		assert( ( guardCondition.isTrue() || guardCondition.isFalse() ) || currentSet.dimension() == guardCondition.dimension() );
		auto guardConstraints = halfspacesToConstraints<mpq_class, Number>( guardCondition.getMatrix(), guardCondition.getVector() );
		// apply guard - conjunction
		currentSet.addConstraints( guardConstraints );
		currentSet.setDimension( initialGuardCondition.dimension() );
		if ( !reset.isIdentity() ) {
			currentSet = currentSet.affineTransformation( reset.getMatrix(), reset.getVector() );
		}
	}
	return symbolicEquivalence( currentSet, initialGuardCondition );
#endif
	return false;
}

/**
 * Checks for fixed points by checking for containment and coverage (if possible) for not only the first but the first n segments.
 * @tparam Set The used set-representation
 * @param currentNode The current node which is checked for a fixed point
 * @param roots The roots of the current reach tree
 * @param numberSets The number of sets that are to be compared
 * @return True, if a fixed point can be detected, false otherwise
 */
template <typename Set, typename Loc>
bool detectContinuousFixedPoints( ReachTreeNode<Set, Loc>& currentNode, const std::vector<ReachTreeNode<Set, Loc>>& roots, std::size_t numberSets = 2 ) {
	auto nonDiscreteDimensions = currentNode.getLocation()->getLinearFlow().getNonDiscreteDimensions();
	std::size_t set_index = 0;
	while ( set_index < numberSets && set_index < currentNode.getFlowpipe().size() ) {
		for ( auto& other_node : preorder( roots ) ) {
			if ( &other_node != &currentNode && other_node.getLocation() == currentNode.getLocation() ) {
				// fill coverer
				std::vector<Set> coverer;
				for ( std::size_t i = 0; i < numberSets; ++i ) {
					if ( other_node.getFlowpipe().size() > i ) {
						coverer.push_back( other_node.getFlowpipe()[i].projectOn( nonDiscreteDimensions ) );
					}
				}
				if ( is_covered( currentNode.getFlowpipe()[set_index].projectOn( nonDiscreteDimensions ), coverer ) ) {
					currentNode.setFixedPoint();
					return true;
				}

				std::size_t other_set_index = 0;
				while ( other_set_index < numberSets && other_set_index < other_node.getFlowpipe().size() ) {
					if ( other_node.getFlowpipe()[other_set_index].projectOn( nonDiscreteDimensions ).contains( currentNode.getFlowpipe()[set_index].projectOn( nonDiscreteDimensions ) ) ) {
						currentNode.setFixedPoint();
						return true;
					}
					++other_set_index;
				}
			}
		}
		++set_index;
	}
	return false;
}

}  // namespace hypro
