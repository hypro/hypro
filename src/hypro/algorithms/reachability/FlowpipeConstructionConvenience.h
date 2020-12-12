#pragma once

#include "../../datastructures/HybridAutomaton/Condition.h"
#include "types.h"

#include <utility>

namespace hypro {

template <class Representation, class Number>
std::pair<CONTAINMENT, Representation> intersect( Representation const& valuationSet, Condition<Number> const& condition, std::size_t I = 0 ) {
	if ( condition.empty() ) {
		return std::make_pair( CONTAINMENT::FULL, valuationSet );
	}
	//assert( valuationSet.dimension() == condition.dimension() );
	return valuationSet.satisfiesHalfspaces( condition.getMatrix( I ), condition.getVector( I ) );
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
Representation applyReset( Representation const& valuationSet, Reset<Number> const& reset, std::size_t subspace = 0 ) {
	return valuationSet.affineTransformation( reset.getMatrix( subspace ), reset.getVector( subspace ) );
}

}  // namespace hypro