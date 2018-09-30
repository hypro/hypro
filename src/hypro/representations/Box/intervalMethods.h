#pragma once
#include "../../datastructures/Halfspace.h"
#include <carl/interval/Interval.h>
#include <carl/interval/IntervalEvaluation.h>

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
	template<typename Number>
	bool icpIntersectHalfspace(std::vector<carl::Interval<Number>>& intervals, const Halfspace<Number>& hsp) {
		assert(Eigen::Index(intervals.size()) == hsp.normal().rows());

		// contraction variable cVar, other variables (for that run) oVar.
		for(Eigen::Index cVar = 0; cVar < hsp.normal().rows(); ++cVar) {
			if(hsp.normal()(cVar) != 0) {
				// initialize with constant part.
				carl::Interval<Number> newIntv = Number(-1) * carl::Interval<Number>(hsp.offset(),carl::BoundType::INFTY,hsp.offset(),carl::BoundType::WEAK);
				// update interval using interval arithmetic (ICP-style: propagation).
				for(Eigen::Index oVar = 0; oVar < hsp.normal().rows(); ++oVar) {
					if(cVar != oVar && hsp.normal()(oVar) != 0) {
						newIntv += hsp.normal()(oVar)*intervals[oVar];
					}
				}
				newIntv /= Number(-hsp.normal()(cVar));

				intervals[cVar] = intervals[cVar].intersect(newIntv);
				if(intervals[cVar].isEmpty()) {
					return true;
				}
			}

		}
		return false;
	}

	template<typename Number>
	void reduceIntervalsNumberRepresentation( std::vector<carl::Interval<Number>>& , unsigned ) {
		// do nothing.
	}

	template<>
	void reduceIntervalsNumberRepresentation( std::vector<carl::Interval<mpq_class>>& intervals, unsigned limit) {
		mpq_class limit2 = mpq_class(limit)*mpq_class(limit);
		for(unsigned d = 0; d < intervals.size(); ++d) {
			//std::cout << "(Upper Bound) mpq_class: " << intervals[d].upper() << std::endl;
			if(intervals[d].upper() != 0) {
				mpq_class numerator = carl::getNum(intervals[d].upper());
				mpq_class denominator = carl::getDenom(intervals[d].upper());
				mpq_class largest = carl::abs(numerator) > carl::abs(denominator) ? carl::abs(numerator) : carl::abs(denominator);
				if(largest > limit2){
					mpq_class dividend = largest / mpq_class(limit);
					assert(largest/dividend == limit);
					mpq_class val = mpq_class(carl::ceil(numerator/dividend));
					mpq_class newDenom;
					if(intervals[d].upper() > 0) {
						newDenom = mpq_class(carl::floor(denominator/dividend));
					} else {
						newDenom = mpq_class(carl::ceil(denominator/dividend));
					}
					if(newDenom != 0) {
						val = val / newDenom;
						assert(val >= intervals[d].upper());
						intervals[d].setUpper(mpq_class(val));
					}
					//std::cout << "Assert: " << val << " >= " << intervals[d].upper() << std::endl;
					//std::cout << "(Upper bound) Rounding Error: " << carl::convert<mpq_class,double>(val - intervals[d].upper()) << std::endl;
				}
			}

			//std::cout << "(Lower Bound) mpq_class: " << intervals[d].lower() << std::endl;
			if(intervals[d].lower() != 0) {
				mpq_class numerator = carl::getNum(intervals[d].lower());
				mpq_class denominator = carl::getDenom(intervals[d].lower());
				mpq_class largest = carl::abs(numerator) > carl::abs(denominator) ? carl::abs(numerator) : carl::abs(denominator);
				if(largest > limit2){
					mpq_class dividend = largest / mpq_class(limit);
					assert(largest/dividend == limit);
					mpq_class val = mpq_class(carl::floor(numerator/dividend));
					mpq_class newDenom;
					if( intervals[d].lower() > 0) {
						newDenom = mpq_class(carl::ceil(denominator/dividend));
					} else {
						newDenom = mpq_class(carl::floor(denominator/dividend));
					}
					if(newDenom != 0) {
						val = val / newDenom;
						assert(val <= intervals[d].lower());
						intervals[d].setLower(val);
					}
					//std::cout << "Assert: " << val << " <= " << intervals[d].lower() << std::endl;
					//std::cout << "(Lower bound) Rounding Error: " << carl::convert<mpq_class,double>(val - intervals[d].lower()) << std::endl;
				}
			}
		}
	}

} // namespace hypro
