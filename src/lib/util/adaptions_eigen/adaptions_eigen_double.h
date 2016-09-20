
#pragma once

#include "adaptions_eigen.h"

namespace Eigen {

	template <>
	inline bool operator<( const hypro::vector_t<double>& lhs, const hypro::vector_t<double>& rhs ) {
		if ( lhs.rows() != rhs.rows() ){
			return false;
		}

		for ( unsigned dim = 0; dim < lhs.rows(); ++dim ) {
			if ( lhs( dim ) > rhs( dim ) ) {
				return false;
			} else if ( lhs( dim ) < rhs( dim ) ) {
				return true;
			}
		}
		return false;
	}

	template <>
	inline bool operator<=( const hypro::vector_t<double>& lhs, const hypro::vector_t<double>& rhs ) {
		if ( lhs.rows() != rhs.rows() ) {
			return false;
		}

		for ( unsigned dim = 0; dim < lhs.rows(); ++dim ) {
			if ( lhs( dim ) > rhs( dim ) ) {
				return false;
			} else if ( lhs( dim ) <= rhs( dim ) ) {
				return true;
			}
		}
		return false;
	}

	template<>
	inline bool operator>( const hypro::vector_t<double>& lhs, const hypro::vector_t<double>& rhs ) { return rhs < lhs;}

	template<>
	inline bool operator>=( const hypro::vector_t<double>& lhs, const hypro::vector_t<double>& rhs ) { return rhs <= lhs;}

	template <>
	inline bool operator==( const hypro::vector_t<double>& lhs, const hypro::vector_t<double>& rhs ) {
		if ( lhs.rows() != rhs.rows() ){
			return false;
		}
		if ( VectorHashValue(lhs) != VectorHashValue(rhs) ){
			return false;
		}

		for ( unsigned dim = 0; dim < lhs.rows(); ++dim ) {
			// compare with 128 ULPs
			if ( !carl::AlmostEqual2sComplement(lhs( dim ), rhs( dim ), 128) ) {
				return false;
			}
		}
		return true;
	}

	template<>
	inline bool operator!=( const hypro::vector_t<double>& lhs, const hypro::vector_t<double>& rhs ) {
		return !(lhs == rhs);
	}

	template <>
	inline bool operator==( const hypro::matrix_t<double>& lhs, const hypro::matrix_t<double>& rhs ) {
		if ( lhs.rows() != rhs.rows() || lhs.cols() != rhs.cols() ){
			return false;
		}
		if ( MatrixHashValue(lhs) != MatrixHashValue(rhs) ){
			return false;
		}

		for ( unsigned rowIndex = 0; rowIndex < lhs.rows(); ++rowIndex ) {
			for ( unsigned colIndex = 0; colIndex < lhs.cols(); ++colIndex ) {
				// compare with 128 ULPs
				if ( !carl::AlmostEqual2sComplement(lhs(rowIndex, colIndex), rhs(rowIndex, colIndex), 128) ) {
					return false;
				}
			}
		}
		return true;
	}

	template <>
	inline bool operator!=( const hypro::matrix_t<double>& lhs, const hypro::matrix_t<double>& rhs ) {
		return !(lhs == rhs);
	}

} // namespace Eigen

namespace hypro {
	template<>
	inline std::pair<bool,double> linearDependent(const vector_t<double>& lhs, const vector_t<double>& rhs) {
		unsigned firstNonZeroPos = 0;
		if(lhs.nonZeros() == 0 || rhs.nonZeros() == 0){
			return std::make_pair(true,0);
		}

		// both are non-Zero vectors
		while(lhs(firstNonZeroPos) == 0){
			++firstNonZeroPos;
		}
		if(rhs(firstNonZeroPos) == 0) {
			return std::make_pair(false,0);
		}
		double scalar = lhs(firstNonZeroPos)/rhs(firstNonZeroPos);
		if(lhs == rhs*scalar) {
			//std::cout << __func__ << ": scalar: " << scalar << std::endl;
			return std::make_pair(true,scalar);
		}
		return std::make_pair(false,0);
	}

} // namespace hypro
