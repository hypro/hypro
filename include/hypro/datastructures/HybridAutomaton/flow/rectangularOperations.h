#pragma once
#include "../../../carlTypes.h"
#include "rectangular.h"

namespace hypro {

/**
 * @brief Creates a set of constraints which describe forward time evolution for the passed variable.
 * @details The primed variable serves as the initialization, the original variable will be the variable for which the result is described. The variable t is the used clock/time variable, the passed interval describes the flow. The method creates constraints in the assumption that t >= 0 holds.
 * @tparam N Number type (rational)
 * @tparam D Number type (float) used to describe the flow
 * @param original The original variable (the result is described in this var)
 * @param primed The initial valuation of the original variable
 * @param t The variable which reflects time
 * @param flow The interval describing the dynamics
 * @return std::vector<ConstraintT<N>> A set of constraints which describe all possible time successors
 */
template <typename N, typename D>
std::vector<ConstraintT<N>> createFlowConstraints( carl::Variable original, carl::Variable primed, carl::Variable t, const carl::Interval<D>& flow ) {
	std::vector<ConstraintT<N>> res;

	// catch equations
	if ( flow.lowerBoundType() == carl::BoundType::WEAK && flow.upperBoundType() == carl::BoundType::WEAK && flow.lower() == flow.upper() ) {
		res.emplace_back( PolyT<N>( primed ) + PolyT<N>( carl::convert<D, N>( flow.lower() ) ) * PolyT<N>( t ) - PolyT<N>( original ), carl::Relation::EQ );
		return res;
	}

	// lower flow bound
	// x' + lb*t - x <= 0
	// x >= x' + lb*t
	if ( flow.lowerBoundType() != carl::BoundType::INFTY ) {
		res.emplace_back( PolyT<N>( primed ) + PolyT<N>( carl::convert<D, N>( flow.lower() ) ) * PolyT<N>( t ) - PolyT<N>( original ), carl::Relation::LEQ );
	}

	// upper flow bound
	// x' + ub*t - x >= 0
	// x <= x' + ub*t
	if ( flow.upperBoundType() != carl::BoundType::INFTY ) {
		res.emplace_back( PolyT<N>( primed ) + PolyT<N>( carl::convert<D, N>( flow.upper() ) ) * PolyT<N>( t ) - PolyT<N>( original ), carl::Relation::GEQ );
	}

	return res;
}

/**
 * @brief Creates a set of constraints which describe backward time evolution for the passed variable.
 * @details The primed variable serves as the initialization, the original variable will be the variable for which the result is described. The variable t is the used clock/time variable, the passed interval describes the flow. The method creates constraints under the assumption that t <= 0 holds.
 * @tparam N Number type (rational)
 * @tparam D Number type (float) used to describe the flow
 * @param original The original variable (the result is described in this var)
 * @param primed The initial valuation of the original variable
 * @param t The variable which reflects time
 * @param flow The interval describing the dynamics
 * @return std::vector<ConstraintT<N>> A set of constraints which describe all possible time predeccessors
 */
template <typename N, typename D>
std::vector<ConstraintT<N>> createReverseFlowConstraints( carl::Variable original, carl::Variable primed, carl::Variable t, const carl::Interval<D>& flow ) {
	std::vector<ConstraintT<N>> res;

	// catch equations
	if ( flow.lowerBoundType() == carl::BoundType::WEAK && flow.upperBoundType() == carl::BoundType::WEAK && flow.lower() == flow.upper() ) {
		res.emplace_back( PolyT<N>( primed ) + PolyT<N>( carl::convert<D, N>( flow.lower() ) ) * PolyT<N>( t ) - PolyT<N>( original ), carl::Relation::EQ );
		return res;
	}

	// lower flow bound
	// x' + lb*t -x >= 0
	// x <= x' + lb*t, t <= 0
	if ( flow.lowerBoundType() != carl::BoundType::INFTY ) {
		res.emplace_back( PolyT<N>( primed ) + PolyT<N>( carl::convert<D, N>( flow.lower() ) ) * PolyT<N>( t ) - PolyT<N>( original ), carl::Relation::GEQ );
	}

	// upper flow bound
	// x' + ub*t -x <= 0
	// x >= x' + ub*t, t <= 0
	if ( flow.upperBoundType() != carl::BoundType::INFTY ) {
		res.emplace_back( PolyT<N>( primed ) + PolyT<N>( carl::convert<D, N>( flow.upper() ) ) * PolyT<N>( t ) - PolyT<N>( original ), carl::Relation::LEQ );
	}

	return res;
}

/**
 * @brief Creates a set of constraints which describe under-approximative backward time evolution for the passed variable.
 * @details The primed variable serves as the initialization, the original variable will be the variable for which the result is described. The variable t is the used clock/time variable, the passed interval describes the flow. The method creates constraints under the assumption that t <= 0 holds.
 * @tparam N Number type (rational)
 * @tparam D Number type (float) used to describe the flow
 * @param original The original variable (the result is described in this var)
 * @param primed The initial valuation of the original variable
 * @param t The variable which reflects time
 * @param flow The interval describing the dynamics
 * @return std::vector<ConstraintT<N>> A set of constraints which describe all possible time predeccessors
 */
template <typename N, typename D>
std::vector<ConstraintT<N>> createUnderapproximativeReverseFlowConstraints( carl::Variable original, carl::Variable primed, carl::Variable t, const carl::Interval<D>& flow ) {
	std::vector<ConstraintT<N>> res;

	// catch equations
	if ( flow.lowerBoundType() == carl::BoundType::WEAK && flow.upperBoundType() == carl::BoundType::WEAK && flow.lower() == flow.upper() ) {
		res.emplace_back( -PolyT<N>( primed ) + PolyT<N>( carl::convert<D, N>( flow.lower() ) ) * PolyT<N>( t ) + PolyT<N>( original ), carl::Relation::EQ );
		return res;
	}

	// lower flow bound
	// x' + lb*t - x >= 0
	// x <= x' + lb*t
	if ( flow.lowerBoundType() != carl::BoundType::INFTY ) {
		res.emplace_back( -PolyT<N>( primed ) + PolyT<N>( carl::convert<D, N>( flow.lower() ) ) * PolyT<N>( t ) + PolyT<N>( original ), carl::Relation::GEQ );
	}

	// upper flow bound
	// x' + ub*t - x >= 0
	// x <= x' + ub*t
	if ( flow.upperBoundType() != carl::BoundType::INFTY ) {
		res.emplace_back( -PolyT<N>( primed ) + PolyT<N>( carl::convert<D, N>( flow.upper() ) ) * PolyT<N>( t ) + PolyT<N>( original ), carl::Relation::LEQ );
	}

	return res;
}

}  // namespace hypro
