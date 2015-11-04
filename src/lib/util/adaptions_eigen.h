/*
 * This file contains the additions needed for eigen3 to support our own floating
 * type FLOAT_T.
 * @file   eigenTypetraits.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since   2014-05-02
 * @version 2014-05-02
 */

#pragma once

namespace Eigen {
template <typename Number>
struct NumTraits<carl::FLOAT_T<Number>> {
	enum {
		IsComplex = 0,
		IsInteger = 0,
		ReadCost = 1,
		AddCost = 1,
		MulCost = 1,
		IsSigned = 1,
		RequireInitialization = 1
	};

	typedef carl::FLOAT_T<Number> Real;
	typedef carl::FLOAT_T<Number> NonInteger;
	typedef carl::FLOAT_T<Number> Nested;

	static inline Real epsilon() { return std::numeric_limits<Real>::epsilon(); }
	static inline Real dummy_precision() {
		// make sure to override this for floating-point types
		return Real( 0 );
	}
	static inline carl::FLOAT_T<Number> highest() { return carl::FLOAT_T<Number>::maxVal(); }
	static inline carl::FLOAT_T<Number> lowest() { return carl::FLOAT_T<Number>::minVal(); }
};

template <typename Number>
bool operator<( const hypro::vector_t<Number>& lhs, const hypro::vector_t<Number>& rhs ) {
	if ( lhs.rows() != rhs.rows() ) return false;

	for ( unsigned dim = 0; dim < lhs.rows(); ++dim ) {
		if ( lhs( dim ) > rhs( dim ) ) {
			return false;
		} else if ( lhs( dim ) < rhs( dim ) ) {
			return true;
		}
	}
	return false;
}

template <typename Number>
bool operator==( const hypro::vector_t<Number>& lhs, const hypro::vector_t<Number>& rhs ) {
	if ( lhs.rows() != rhs.rows() ) return false;

	for ( unsigned dim = 0; dim < lhs.rows(); ++dim ) {
		if ( !carl::AlmostEqual2sComplement( lhs( dim ), rhs( dim ), TOLLERANCE_ULPS ) ) {
			return false;
		}
	}
	return true;
}

template <typename Number>
bool operator==( const hypro::matrix_t<Number>& lhs, const hypro::matrix_t<Number>& rhs ) {
	if ( lhs.rows() != rhs.rows() || lhs.cols() != rhs.cols() ) return false;

	for ( unsigned rowIndex = 0; rowIndex < lhs.rows(); ++rowIndex ) {
		for ( unsigned colIndex = 0; colIndex < lhs.cols(); ++colIndex ) {
			if ( !carl::AlmostEqual2sComplement( lhs( rowIndex, colIndex ), rhs( rowIndex, colIndex ), TOLLERANCE_ULPS ) ) {
				return false;
			}
		}
	}
	return true;
}

// according to http://eigen.tuxfamily.org/bz/show_bug.cgi?id=257 comment 14 we use this:
template <typename Number>
hypro::matrix_t<Number> pseudoInverse( const hypro::matrix_t<Number>& a,
									   Number epsilon = std::numeric_limits<Number>::epsilon() ) {
	Eigen::JacobiSVD<hypro::matrix_t<Number>> svd( a, Eigen::ComputeThinU | Eigen::ComputeThinV );
	Number tolerance = epsilon * std::max( a.cols(), a.rows() ) * svd.singularValues().array().abs()( 0 );
	return svd.matrixV() *
		   ( svd.singularValues().array().abs() > tolerance )
				 .select( svd.singularValues().array().inverse(), 0 )
				 .matrix()
				 .asDiagonal() *
		   svd.matrixU().adjoint();
}
} // namespace Eigen