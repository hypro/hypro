#pragma once
#include "../../types.h"

#include <carl/interval/Interval.h>
#include <tuple>

namespace hypro {

/**
 * @brief      Determines if a constraint set represented by a matrix and a vector in fact defines a box.
 * @details	   Uses simple checks to syntactically detect a box-description via half-spaces. This can be used, to use a box-representation instead of a H-Polytope representation, if desired.
 * @param[in]  constraints  The constraints.
 * @param[in]  constants    The constants.
 * @tparam     Number       The used number type.
 * @return     True if box, False otherwise.
 */
template <typename Number>
std::tuple<bool, std::vector<carl::Interval<Number>>> isBox( const matrix_t<Number>& constraints, const vector_t<Number>& constants ) {
	// dimensions do not match
	if ( constraints.rows() != constants.rows() ) {
		return std::tuple<bool, std::vector<carl::Interval<Number>>>( false, {} );
	}
	Eigen::Index dimension = constraints.cols();
	std::vector<carl::Interval<Number>> boundsDefined = std::vector<carl::Interval<Number>>( dimension, carl::Interval<Number>::unboundedInterval() );
	using optionalPair = std::pair<std::optional<Number>, std::optional<Number>>;
	std::vector<optionalPair> boundsPairs = std::vector<optionalPair>( dimension, std::pair<std::optional<Number>, std::optional<Number>>() );

	// collect potential intervals for each dimension
	for ( Eigen::Index r = 0; r < constraints.rows(); ++r ) {
		// count non-zero coefficients
		std::size_t posNonZeroCoeff = 0;
		std::size_t negNonZeroCoeff = 0;
		for ( Eigen::Index c = 0; c < constraints.cols(); ++c ) {
			// based on the sign of the coefficient and the constant value set bound type
			if ( constraints( r, c ) > carl::constant_zero<Number>().get() ) {
				Number val = constants( r ) / constraints( r, c );
				++posNonZeroCoeff;
				if ( !boundsPairs[c].second ) {
					// std::cout << "Set upper bound to " << Number(val) << std::endl;
					boundsPairs[c].second = val;
				} else if ( val < boundsPairs[c].second ) {
					// std::cout << "Set upper bound multiple times." << std::endl;
					boundsPairs[c].second = val;
				}
			} else if ( constraints( r, c ) < carl::constant_zero<Number>().get() ) {
				Number val = constants( r ) / constraints( r, c );
				++negNonZeroCoeff;
				if ( !boundsPairs[c].first ) {
					// std::cout << "Set lower bound to " << Number(val) << std::endl;
					boundsPairs[c].first = val;
				} else if ( val > boundsPairs[c].first ) {
					// std::cout << "Set lower bound multiple times." << std::endl;
					boundsPairs[c].first = val;
				}
			}
			// if there exists more than one non-zero coefficient per row, return false.
			if ( posNonZeroCoeff + negNonZeroCoeff > 1 ) {
				// std::cout << "Too many coefficients, described set is not a box." << std::endl;
				return std::tuple<bool, std::vector<carl::Interval<Number>>>( false, std::vector<carl::Interval<Number>>() );
			}
		}
	}
	// safely construct intervals
	for ( std::size_t i = 0; i < boundsPairs.size(); ++i ) {
		if ( boundsPairs[i].first ) {
			if ( boundsPairs[i].second ) {
				boundsDefined[i] = carl::Interval( *boundsPairs[i].first, carl::BoundType::WEAK, *boundsPairs[i].second, carl::BoundType::WEAK );
			} else {
				boundsDefined[i] = carl::Interval( *boundsPairs[i].first, carl::BoundType::WEAK, *boundsPairs[i].first, carl::BoundType::INFTY );
			}
		} else {
			if ( boundsPairs[i].second ) {
				boundsDefined[i] = carl::Interval( *boundsPairs[i].second, carl::BoundType::INFTY, *boundsPairs[i].second, carl::BoundType::WEAK );
			}
		}
	}
	// return true and the collected intervals.
	// std::cout << "Described set is a box." << std::endl;
	return std::tuple<bool, std::vector<carl::Interval<Number>>>( true, boundsDefined );
}

}  // namespace hypro
