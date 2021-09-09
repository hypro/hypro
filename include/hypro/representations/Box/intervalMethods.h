#pragma once
#include "../../datastructures/Halfspace.h"

#include <carl/interval/Interval.h>
#include <carl/interval/IntervalEvaluation.h>
#include <carl/interval/set_theory.h>

namespace hypro {

/**
 * @brief      Performs intersection of a vector of intervals with a halfspace.
 * @details    The idea is to use ICP-style contractions to obtain the resulting box.
 * As we know the constraint (the halfspace) is linear, we only need to perform one contraction per dimension and the order does not matter.
 * @param      intervals  The intervals as a vector (call by reference).
 * @param[in]  hsp        The halfspace
 *
 * @tparam     Number     The used number type.
 *
 * @return     True, if one of the resulting intervals is empty, False otherwise.
 */
template <typename Number>
bool icpIntersectHalfspace( std::vector<carl::Interval<Number>>& intervals, const Halfspace<Number>& hsp ) {
	assert( Eigen::Index( intervals.size() ) == hsp.normal().rows() );

	// contraction variable cVar, other variables (for that run) oVar.
	for ( Eigen::Index cVar = 0; cVar < hsp.normal().rows(); ++cVar ) {
		if ( hsp.normal()( cVar ) != 0 ) {
			// initialize with constant part.
			carl::Interval<Number> newIntv = Number( -1 ) * carl::Interval<Number>( hsp.offset(), carl::BoundType::INFTY, hsp.offset(), carl::BoundType::WEAK );
			// update interval using interval arithmetic (ICP-style: propagation).
			for ( Eigen::Index oVar = 0; oVar < hsp.normal().rows(); ++oVar ) {
				if ( cVar != oVar && hsp.normal()( oVar ) != 0 ) {
					newIntv += hsp.normal()( oVar ) * intervals[oVar];
				}
			}
			newIntv /= Number( -hsp.normal()( cVar ) );
			intervals[cVar] = set_intersection( intervals[cVar], newIntv );
			if ( intervals[cVar].isEmpty() ) {
				return true;
			}
		}
	}
	return false;
}

template <typename Number>
void reduceIntervalsNumberRepresentation( std::vector<carl::Interval<Number>>&, unsigned ) {
	// do nothing.
}

void reduceIntervalsNumberRepresentation( std::vector<carl::Interval<mpq_class>>& intervals, unsigned limit );

}  // namespace hypro
