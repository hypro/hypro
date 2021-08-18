#pragma once
#include "../../../carlTypes.h"
#include "rectangular.h"

namespace hypro {

template <typename N, typename D>
std::vector<ConstraintT<N>> createFlowConstraints( carl::Variable original, carl::Variable primed, carl::Variable t, const carl::Interval<D>& flow ) {
	std::vector<ConstraintT<N>> res;

	// catch equations
	if ( flow.lowerBoundType() == carl::BoundType::WEAK && flow.upperBoundType() == carl::BoundType::WEAK && flow.lower() == flow.upper() ) {
		res.emplace_back( PolyT<N>( primed ) + PolyT<N>( carl::convert<D, N>( flow.lower() ) ) * PolyT<N>( t ) - PolyT<N>( original ), carl::Relation::EQ );
		return res;
	}

	// lower flow bound
	if ( flow.lowerBoundType() != carl::BoundType::INFTY ) {
		// ConstraintT<N> lb = ConstraintT<N>(PolyT<N>(primed) + PolyT<N>(flow.lower()) * PolyT<N>(t) - PolyT<N>(original), carl::Relation::LEQ);
		res.emplace_back( PolyT<N>( primed ) + PolyT<N>( carl::convert<D, N>( flow.lower() ) ) * PolyT<N>( t ) - PolyT<N>( original ), carl::Relation::LEQ );
	}

	// upper flow bound
	if ( flow.upperBoundType() != carl::BoundType::INFTY ) {
		// ConstraintT<N> ub = ConstraintT<N>(PolyT<N>(primed) + PolyT<N>(flow.upper()) * PolyT<N>(t) - PolyT<N>(original), carl::Relation::GEQ);
		res.emplace_back( PolyT<N>( primed ) + PolyT<N>( carl::convert<D, N>( flow.upper() ) ) * PolyT<N>( t ) - PolyT<N>( original ), carl::Relation::GEQ );
	}

	return res;
}

}  // namespace hypro
