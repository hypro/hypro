#pragma once

#include "../../datastructures/HybridAutomaton/Condition.h"
#include "types.h"

#include <utility>

namespace hypro {

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
	return valuationSet.affineTransformation( reset.getMatrix(), reset.getVector() );
}

}  // namespace hypro