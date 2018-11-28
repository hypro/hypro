#pragma once
#include "../../types.h"
#include <boost/tuple/tuple.hpp>

namespace hypro {

/**
 * @brief      Determines if a constraint set represented by a matrix and a vector in fact defines a box.
 * @param[in]  constraints  The constraints.
 * @param[in]  constants    The constants.
 * @tparam     Number       The used number type.
 * @return     True if box, False otherwise.
 */
template<typename Number>
boost::tuple<bool,std::vector<carl::Interval<Number>>> isBox(const matrix_t<Number>& constraints, const vector_t<Number>& constants) {
    // dimensions do not match
	if(constraints.rows() != constants.rows()) {
		return boost::tuple<bool,std::vector<carl::Interval<Number>>>(false);
	}
	Eigen::Index dimension = constraints.cols();
	std::vector<carl::Interval<Number>> boundsDefined = std::vector<carl::Interval<Number>>(dimension, carl::Interval<Number>::unboundedInterval());

    // collect potential intervals for each dimension
	for(Eigen::Index r = 0; r < constraints.rows(); ++r) {
        // count non-zero coefficients
		std::size_t posNonZeroCoeff = 0;
		std::size_t negNonZeroCoeff = 0;
		for(Eigen::Index c = 0; c < constraints.cols(); ++c) {
            // based on the sign of the coefficient and the constant value set bound type
			if(constraints(r,c) > carl::constant_zero<Number>().get()) {
				Number val = constants(r)/constraints(r,c);
				++posNonZeroCoeff;
				if(boundsDefined[c].upperBoundType() == carl::BoundType::INFTY) {
					//std::cout << "Set upper bound to " << Number(val) << std::endl;
					boundsDefined[c].setUpperBound(val, carl::BoundType::WEAK);
				} else if(val < boundsDefined[c].upper()) {
					//std::cout << "Set upper bound multiple times." << std::endl;
					boundsDefined[c].setUpperBound(val, carl::BoundType::WEAK);
				}
			} else if (constraints(r,c) < carl::constant_zero<Number>().get()) {
				Number val = constants(r)/constraints(r,c);
				++negNonZeroCoeff;
				if(boundsDefined[c].lowerBoundType() == carl::BoundType::INFTY) {
					//std::cout << "Set lower bound to " << Number(val) << std::endl;
					boundsDefined[c].setLowerBound(val, carl::BoundType::WEAK);
				} else if( val > boundsDefined[c].lower()){
					//std::cout << "Set lower bound multiple times." << std::endl;
					boundsDefined[c].setLowerBound(val, carl::BoundType::WEAK);
				}
			}
            // if there exists more than one non-zero coefficient per row, return false.
			if(posNonZeroCoeff + negNonZeroCoeff > 1) {
				//std::cout << "Too many coefficients, described set is not a box." << std::endl;
				return boost::tuple<bool,std::vector<carl::Interval<Number>>>(false);
			}
		}
	}
	// return true and the collected intervals.
	return boost::tuple<bool,std::vector<carl::Interval<Number>>>(true,boundsDefined);
}

} // hypro