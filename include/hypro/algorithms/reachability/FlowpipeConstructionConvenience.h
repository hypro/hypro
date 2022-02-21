/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../datastructures/HybridAutomaton/Condition.h"
#include "../../datastructures/HybridAutomaton/State.h"
#include "types.h"

#include <utility>

namespace hypro {

/**
 * @brief Intersects a state set with a condition and returns the result
 * @details Includes handling of true- and false-conditions.
 * @tparam Representation The type of state set representation
 * @tparam Number The used number type
 * @param valuationSet The state set
 * @param condition The condition
 * @return std::pair<CONTAINMENT, Representation>
 */
template <class Representation, class Number>
std::pair<CONTAINMENT, Representation> intersect( Representation const& valuationSet, Condition<Number> const& condition, std::size_t subspace = 0 ) {
	// shortcut true condition
	if ( condition.isTrue() ) {
		return std::make_pair( CONTAINMENT::FULL, valuationSet );
	}
	// shortcut false condition
	if ( condition.isFalse() || valuationSet.empty() ) {
		return std::make_pair( CONTAINMENT::NO, Representation::Empty() );
	}
	// assert( valuationSet.dimension() == condition.dimension() );
	return valuationSet.satisfiesHalfspaces( condition.getMatrix( subspace ), condition.getVector( subspace ) );
}

/**
 * @brief Returns only the linear part (matrix) of a matrix describing affine dynamics.
 * @tparam Number The used number type
 * @param timeTrafo The matrix describing affine dynamics
 * @return auto The sub-matrix describing only the linear dynamics.
 */
template <class Number>
auto timeTrafoMatrixBlock( matrix_t<Number> const& timeTrafo ) {
	return timeTrafo.block( 0, 0, timeTrafo.rows() - 1, timeTrafo.cols() - 1 );
}

/**
 * @brief Returns only the translation vector of a matrix describing affine dynamics.
 * @tparam Number The used number type
 * @param timeTrafo The matrix describing affine dynamics
 * @return auto The sub-vector describing the translational part of the dynamics
 */
template <class Number>
auto timeTrafoVectorBlock( matrix_t<Number> const& timeTrafo ) {
	return timeTrafo.col( timeTrafo.cols() - 1 ).head( timeTrafo.rows() - 1 );
}

/**
 * @brief Applies LTI-time evolution for a fixed time step, i.e., an affine transformation. *
 * @tparam Representation The representation type
 * @tparam Number The number type
 * @param valuationSet The set which is evolved
 * @param timeTransformation The matrix describing the affine dynamics
 * @return Representation The set after time elapse
 */
template <class Representation, class Number>
Representation applyTimeEvolution( Representation const& valuationSet, matrix_t<Number> const& timeTransformation ) {
	return valuationSet.affineTransformation( timeTrafoMatrixBlock( timeTransformation ), timeTrafoVectorBlock( timeTransformation ) );
}

/**
 * @brief Wrapper function which applies an affine reset function to a set
 * @tparam Representation The representation type
 * @tparam Number The number type
 * @param valuationSet The original set
 * @param reset The object describing the reset function
 * @return Representation The set after applying the reset function
 */
template <class Representation, class Number>
Representation applyReset( Representation const& valuationSet, Reset<Number> const& reset, std::size_t subspace = 0 ) {
	if ( !reset.isIntervalIdentity() && std::any_of( reset.getIntervalReset( subspace ).getIntervals().begin(), reset.getIntervalReset( subspace ).getIntervals().end(),
													 []( const auto& interval ) { return !interval.isEmpty(); } ) ) {
		assert( false && "lti analyzer does not currently support interval assignments on reset" );
		WARN( "hypro.reachability", "lti analyzer does not currently support interval assignments on reset" );
	}
	if ( reset.isAffineIdentity() ) {
		return valuationSet;
	}
	return valuationSet.affineTransformation( reset.getMatrix( subspace ), reset.getVector( subspace ) );
}

/**
 * @brief Computes the bounding box of the passed set via conversion. *
 * @tparam Representation The type of representation of the original set
 * @param set The original set
 * @return Box<typename Representation::NumberType> The bounding box of the original set
 */
template <class Representation>
Box<typename Representation::NumberType> computeBoundingBox( const Representation& set ) {
	return hypro::Converter<typename Representation::NumberType>::toBox( set );
}

template <typename Number, typename Representation, typename... Rargs>
Box<Number> computeBoundingBox( const hypro::State<Number, Representation, Rargs...>& set ) {
	return std::visit( genericConvertAndGetVisitor<Box<Number>>(), set.getSet() );
}
template <class Representation>
Box<typename Representation::NumberType> computeBoundingBox( const ReachTreeNode<Representation>& node ) {
	auto box = computeBoundingBox( node.getFlowpipe().front() );
	for ( const auto& s : getSegments( node ) ) {
		box = box.unite( computeBoundingBox( s ) );
	}
	return box;
}

template <class Representation>
Box<typename Representation::NumberType> computeBoundingBox( const std::vector<ReachTreeNode<Representation>>& trees ) {
	auto box = computeBoundingBox( trees.front() );
	for ( auto treeIt = std::next( std::begin( trees ) ); treeIt != std::end( trees ); ++treeIt ) {
		box = box.unite( computeBoundingBox( *treeIt ) );
	}
	return box;
}

/**
 * @brief Computes the set difference of a state set with a condition.
 * @tparam Representation The type of state set representation
 * @tparam Number The used number type
 * @param valuationSet The state set
 * @param condition The condition
 * @return Vector of non empty state sets, whose union represents the set difference.
 */
template <class Representation, class Number>
std::vector<Representation> setDifference( Representation const& valuationSet, Condition<Number> const& condition ) {
	auto [containment, intersectedMinus] = intersect( valuationSet, condition );
	if ( containment == CONTAINMENT::NO ) {
		return valuationSet.empty() ? std::vector<Representation>{} : std::vector<Representation>{ valuationSet };
	} else if ( containment == CONTAINMENT::FULL ) {
		return {};
	}
	// case distinction because box constructor only works for bounded sets
	if ( Representation::type_enum == representation_name::box ) {
		if ( std::get<0>( isBox( condition.getMatrix(), condition.getVector() ) ) ) {
			return valuationSet.setMinus2( intersectedMinus );
		} else {
			// if the guard is not box shaped then set difference is not guaranteed overapproximative for boxes.
			// therefore the set difference is computed with polytopes and the result is converted back to boxes.
			HPolytope<Number> valuationSetPolytope( valuationSet.matrix(), valuationSet.vector() );
			HPolytope<Number> minusPolytope( condition.getMatrix(), condition.getVector() );
			std::vector<HPolytope<Number>> resAsPolytopes = valuationSetPolytope.setMinus2( minusPolytope );
			std::vector<Representation> resAsBoxes;
			for ( auto const& pol : resAsPolytopes ) {
				if ( pol.empty() ) {
					continue;
				} else {
					resAsBoxes.push_back( Representation( pol.matrix(), pol.vector() ) );
					// if polytope was bounded and not empty, the resulting box should be non empty
					assert( !resAsBoxes.back().empty() && "Polytope computed by set difference was not bounded" );
				}
			}
			return resAsBoxes;
		}
	} else {
		return valuationSet.setMinus2( Representation( condition.getMatrix(), condition.getVector() ) );
	}
}

}  // namespace hypro