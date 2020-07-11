#pragma once

#include "../../../representations/types.h"
#include "../../../types.h"
#include "../../../util/logging/Logger.h"
#include "../HybridAutomaton.h"
#include "../Location.h"
#include "../flow/operations.h"
#include "Decomposition.h"

#include <algorithm>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/graph_traits.hpp>

namespace hypro {

template <typename Number>
representation_name getRepresentationForAutomaton( const HybridAutomaton<Number> &ha );
template <typename Number>
representation_name getRepresentationForLocation( const Location<Number> &loc );
template <typename Number>
representation_name getRepresentationForSubspace( const Location<Number> &loc, size_t index );
/**
    * decomposed the given space into a set of set of variables. Each of the variable sets indicate
    * dependent variables
    */
template <typename Number>
Decomposition getSubspaceDecomposition( const HybridAutomaton<Number> &automaton );
template <typename Number>
bool checkDecomposed( const HybridAutomaton<Number> &automaton );
template <typename Number>
std::pair<HybridAutomaton<Number>, Decomposition> decomposeAutomaton( const HybridAutomaton<Number> &automaton );

namespace detail {
/// adds edges in the subspace graph for related variables of a linear transformation
template <typename Number>
void addEdgesForLinTrafo( matrix_t<Number> linTrafo, boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> &graph );
/// adds edges in the subspace graph for related variables of an affine transformation
template <typename Number>
void addEdgesForAffineTrafo( matrix_t<Number> affineTrafo, boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> &graph );
/// adds edges in the subspace graph for related variables in a condition
template <typename Number>
void addEdgesForCondition( Condition<Number> condition, boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> &graph );
/// adds edges in the subspace graph for related variables in an interval transformation
template <typename Number>
void addEdgesForRectTrafo( const std::vector<carl::Interval<Number>> &intervals, boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> &graph );
/// adds edges in the subspace graph for related variables in an interval assignment
template <typename Number>
void addEdgesForRectMap( const std::map<carl::Variable, carl::Interval<Number>> &map, boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> &graph );
}  // namespace detail

/// checks whether the automaton is a timed automaton
template <typename Number>
bool isTimedAutomaton( const HybridAutomaton<Number> &ha );
/// checks whether the automaton is a rectangular automaton
template <typename Number>
bool isRectangularAutomaton( const HybridAutomaton<Number> &ha );

/// checks whether the location exhibits timed automata semantics
template <typename Number>
bool isTimedLocation( const Location<Number> &loc );
/// checks whether the location exhibits rectangular automata semantics
template <typename Number>
bool isRectangularLocation( const Location<Number> &loc );

/// checks whether the subspace at index exhibits timed automata semantics
template <typename Number>
bool isTimedSubspace( const Location<Number> &loc, size_t index );
/// checks whether the subspace at index exhibits rectangular automata semantics
template <typename Number>
bool isRectangularSubspace( const Location<Number> &loc, size_t index );
/// checks whether the subspace at index exhibits discrete automata semantics
template <typename Number>
bool isDiscreteSubspace( const Location<Number> &loc, size_t index );

/// detects most common dynamics type for a hybrid automaton
template <typename Number>
DynamicType getDynamicType( const HybridAutomaton<Number> &automaton ) {
	DynamicType res = DynamicType::undefined;
	std::for_each( automaton.getLocations().begin(), automaton.getLocations().end(), [&res]( const auto *loc ) {
		DynamicType cur = getDynamicType( *loc );
		res = cur == res ? res : DynamicType::mixed;
	} );
	assert( res != DynamicType::undefined );
	return res;
}

template <typename Number>
DynamicType getDynamicType( const Location<Number> &location ) {
	if ( location.getLinearFlows().size() > 0 ) {
		if ( location.getRectangularFlows().size() > 0 ) {
			// both types of flow are present
			return DynamicType::mixed;
		}

		// check subtypes of affine dynamic
		// dynamic
		DynamicType res = DynamicType::discrete;
		std::for_each( location.getLinearFlows().begin(), location.getLinearFlows().end(), [&res]( const auto &f ) {
			if ( res != DynamicType::affine ) {
				if ( !f.isDiscrete() ) {
					if ( !f.isTimed() ) {
						res = DynamicType::affine;
					} else {
						res = DynamicType::timed;
					}
				}
			}
		} );
		// invariant
		if ( res != DynamicType::affine ) {
			if ( !location.getInvariant().isAxisAligned() ) {
				res = DynamicType::affine;
			}
		}
		// transitions: guard & reset
		if ( res != DynamicType::affine ) {
			for ( const auto &transition : location.getTransitions() ) {
				// check guard
				if ( !transition->getGuard().isAxisAligned() ) {
					res = DynamicType::affine;
				}
				// corner case: resets to intervals
				if ( transition->getReset().getIntervalResets().size() > 0 ) {
					return DynamicType::mixed;
				}
				// check reset
				if ( res != DynamicType::affine ) {
					std::for_each( transition->getReset().getAffineResets().begin(), transition->getReset().getAffineResets().end(), [&res]( const auto &reset ) {
						if ( !reset.isConstant() ) {
							res = DynamicType::affine;
						}
					} );
				}
			}
		}
		return res;
	} else if ( location.getRectangularFlows().size() > 0 ) {
		// as soon as there is rectangular flow we return
		return DynamicType::rectangular;
	} else {
		// happens only when no flow at all is defined
		return DynamicType::discrete;
	}
}

}  // namespace hypro

#include "DecompositionMethods.tpp"
