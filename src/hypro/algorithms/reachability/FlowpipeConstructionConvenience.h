#pragma once

#include "../../datastructures/HybridAutomaton/Condition.h"
#include "types.h"

#include <utility>

namespace hypro {

/**
 * @brief Intersects a state set with a condition and returns the result
 *
 * @tparam Representation The type of state set representation
 * @tparam Number The used number type
 * @param valuationSet The state set
 * @param condition The condition
 * @return std::pair<CONTAINMENT, Representation>
 */
template <class Representation, class Number>
std::pair<CONTAINMENT, Representation> intersect( Representation const& valuationSet, Condition<Number> const& condition ) {
	// shortcut true condition
	if ( condition.isTrue() ) {
		return std::make_pair( CONTAINMENT::FULL, valuationSet );
	}
	// shortcut false condition
	if ( condition.isFalse() ) {
		return std::make_pair( CONTAINMENT::NO, Representation::Empty() );
	}
	assert( valuationSet.dimension() == condition.dimension() );
	return valuationSet.satisfiesHalfspaces( condition.getMatrix(), condition.getVector() );
}

template <class Number>
auto timeTrafoMatrixBlock( matrix_t<Number> const& timeTrafo ) {
	return timeTrafo.block( 0, 0, timeTrafo.rows() - 1, timeTrafo.cols() - 1 );
}

template <class Number>
auto timeTrafoVectorBlock( matrix_t<Number> const& timeTrafo ) {
	return timeTrafo.col( timeTrafo.cols() - 1 ).head( timeTrafo.rows() - 1 );
}

template <class Representation, class Number>
Representation applyTimeEvolution( Representation const& valuationSet, matrix_t<Number> const& timeTransformation ) {
	return valuationSet.affineTransformation( timeTrafoMatrixBlock( timeTransformation ), timeTrafoVectorBlock( timeTransformation ) );
}

template <class Representation, class Number>
Representation applyReset( Representation const& valuationSet, Reset<Number> const& reset ) {
    if ( std::any_of( reset.getIntervalReset().getIntervals().begin(), reset.getIntervalReset().getIntervals().end(),
            []( const auto& interval ){ return !interval.isEmpty(); } ) ) {
        assert( false && "lti analyzer does not currently support interval assignments on reset" );
        WARN( "hypro.reachability", "lti analyzer does not currently support interval assignments on reset" );
    }
	return valuationSet.affineTransformation( reset.getMatrix(), reset.getVector() );
}

}  // namespace hypro