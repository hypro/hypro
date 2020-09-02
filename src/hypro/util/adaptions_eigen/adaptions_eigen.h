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

#include "../../config.h"
#include "../../types.h"
#include "queries.h"
#include "transformation.h"

#include <carl/numbers/numbers.h>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Eigenvalues>
#include <functional>
#include <iosfwd>
#include <limits>
CLANG_WARNING_DISABLE( "-Wdeprecated-register" )
#include <eigen3/unsupported/Eigen/src/MatrixFunctions/MatrixExponential.h>
CLANG_WARNING_RESET

namespace Eigen {

/// less-operator
template <typename Number>
inline bool operator<( const hypro::vector_t<Number>& lhs, const hypro::vector_t<Number>& rhs ) {
	if ( lhs.rows() != rhs.rows() ) {
		return false;
	}

	for ( unsigned dim = 0; dim < lhs.rows(); ++dim ) {
		if ( lhs( dim ) > rhs( dim ) ) {
			return false;
		} else if ( lhs( dim ) < rhs( dim ) ) {
			return true;
		}
	}
	// false, if all coordinates are equal
	return false;
}
/// less-equal operator
template <typename Number>
inline bool operator<=( const hypro::vector_t<Number>& lhs, const hypro::vector_t<Number>& rhs ) {
	if ( lhs.rows() != rhs.rows() ) {
		return false;
	}

	for ( unsigned dim = 0; dim < lhs.rows(); ++dim ) {
		if ( lhs( dim ) > rhs( dim ) ) {
			return false;
		} else if ( lhs( dim ) < rhs( dim ) ) {
			return true;
		}
	}
	// true, if all coordinates are equal
	return true;
}
/// larger operator
template <typename Number>
inline bool operator>( const hypro::vector_t<Number>& lhs, const hypro::vector_t<Number>& rhs ) {
	return rhs < lhs;
}
/// larger-equal operator
template <typename Number>
inline bool operator>=( const hypro::vector_t<Number>& lhs, const hypro::vector_t<Number>& rhs ) {
	return rhs <= lhs;
}

/**
 * computes a hash chain over a vector nx1 using carl::hash_add and returns it
 * @param pVector input vector
 * @return size_t hash seed
 */
template <typename Number>
std::size_t VectorHashValue( const hypro::vector_t<Number>& pVector ) {
	//std::cout << "VECTOR_HASH(" << pVector.transpose() << ")" << std::endl;
	size_t seed = 0;
	for ( unsigned i = 0; i < pVector.rows(); i++ ) {
		std::size_t tmp = std::hash<Number>()( pVector( i ) );
		//std::cout << __func__ << ": " << i << ", "<< pVector(i) << " -> " << tmp << std::endl;
		carl::hash_add( seed, tmp );
	}
	//std::cout << seed << std::endl;
	return seed;
}

/**
 * computes a hash chain over a matrix using carl::hash_add
 * @param pMatrix input matrix
 * @return size_t
 */
template <typename Number>
std::size_t MatrixHashValue( const hypro::matrix_t<Number>& pMatrix ) {
	size_t seed = 0;
	for ( unsigned i = 0; i < pMatrix.rows(); i++ ) {
		for ( unsigned j = 0; j < pMatrix.cols(); j++ ) {
			carl::hash_add( seed, pMatrix( i, j ) );
		}
	}
	return seed;
}
/// equals-operator
template <typename Number>
inline bool operator==( const hypro::vector_t<Number>& lhs, const hypro::vector_t<Number>& rhs ) {
	if ( lhs.rows() != rhs.rows() ) {
		return false;
	}

	for ( std::size_t i = 0, size = lhs.size(); i < size; ++i ) {
		if ( ( *( lhs.data() + i ) ) != ( *( rhs.data() + i ) ) ) {
			return false;
		}
	}
	return true;
}
/// not-equal operator
template <typename Number>
inline bool operator!=( const hypro::vector_t<Number>& lhs, const hypro::vector_t<Number>& rhs ) {
	return !( lhs == rhs );
}
/// equal operator
template <typename Number>
inline bool operator==( const hypro::matrix_t<Number>& lhs, const hypro::matrix_t<Number>& rhs ) {
	if ( lhs.rows() != rhs.rows() || lhs.cols() != rhs.cols() ) {
		return false;
	}

	for ( std::size_t i = 0, size = lhs.size(); i < size; ++i ) {
		if ( ( *( lhs.data() + i ) ) != ( *( rhs.data() + i ) ) ) {
			return false;
		}
	}
	return true;
}
/// not-equal operator
template <typename Number>
inline bool operator!=( const hypro::matrix_t<Number>& lhs, const hypro::matrix_t<Number>& rhs ) {
	return !( lhs == rhs );
}
/// outstream operator
template <typename Number>
inline std::ostream& operator<<( std::ostream& _out, const hypro::vector_t<Number>& in ) {
	for ( unsigned rowIndex = 0; rowIndex < in.rows(); ++rowIndex ) {
		_out << in( rowIndex ) << std::endl;
	}
	return _out;
}
/// outstream operator
template <typename Number>
inline std::ostream& operator<<( std::ostream& _out, const hypro::matrix_t<Number>& in ) {
	for ( unsigned rowIndex = 0; rowIndex < in.rows(); ++rowIndex ) {
		for ( unsigned colIndex = 0; colIndex < in.cols(); ++colIndex ) {
			_out << in( rowIndex, colIndex ) << " ";
		}
		_out << std::endl;
	}
	return _out;
}

/**
 * @brief computes the Euclidean norm of a vector_t
 * @tparam Number
 * @param in
 * @param roundUp
 * @return Number
 */
template <typename Number>
Number norm( const hypro::vector_t<Number>& in, bool roundUp = true ) {
	Number squares = 0;
	for ( size_t i = 0, size = in.size(); i < size; ++i ) {
		squares = squares + carl::pow( *( in.data() + i ), 2 );
	}
	assert( squares >= 0 );
	if ( squares == 0 ) {
		return 0;
	}

	std::pair<Number, Number> dist = carl::sqrt_safe( squares );
	if ( roundUp ) {
		return dist.second;
	} else {
		return dist.first;
	}
}
/// specialization of Euclidean norm for a vector_t
template <>
inline double norm( const hypro::vector_t<double>& in, bool roundUp ) {
	if ( roundUp )
		return in.norm() + std::numeric_limits<double>::min();
	else
		return in.norm();
}
/**
 * @brief computes the maximum-norm of a matrix *
 * @tparam Number
 * @param in
 * @return Number
 */
template <typename Number>
Number inftyNorm( const hypro::matrix_t<Number>& in ) {
	Number norm = carl::abs( *( in.data() ) );
	for ( size_t i = 1, size = in.size(); i < size; ++i ) {
		Number value = carl::abs( *( in.data() + i ) );
		norm = norm < value ? value : norm;
	}
	return norm;
}
/// computes the absolute value (element-wise) of a matrix
template <typename Number>
hypro::matrix_t<Number> abs( const hypro::matrix_t<Number>& in ) {
	hypro::matrix_t<Number> result = in;
	for ( size_t i = 1, size = result.size(); i < size; ++i ) {
		*( result.data() + i ) = carl::abs( *( result.data() + i ) );
	}
	return result;
}

}  // namespace Eigen

namespace hypro {
/// number type conversion for a matrix
template <typename From, typename To>
matrix_t<To> convert( const matrix_t<From>& _mat ) {
	matrix_t<To> resultMat( _mat.rows(), _mat.cols() );

	for ( unsigned i = 0; i < _mat.rows(); ++i ) {
		for ( unsigned j = 0; j < _mat.cols(); ++j ) {
			resultMat( i, j ) = carl::convert<From, To>( _mat( i, j ) );
		}
	}
	assert( resultMat.rows() == _mat.rows() && resultMat.cols() == _mat.cols() );
	return resultMat;
}
/// number type conversion for diagonal matrices
template <typename From, typename To>
Eigen::DiagonalMatrix<To, Eigen::Dynamic> convert( const Eigen::DiagonalMatrix<From, Eigen::Dynamic>& _mat ) {
	Eigen::DiagonalMatrix<To, Eigen::Dynamic> resultMat( _mat.rows() );

	for ( unsigned i = 0; i < _mat.rows(); ++i ) {
		resultMat.diagonal()( i ) = carl::convert<From, To>( _mat.diagonal()( i ) );
	}
	assert( resultMat.rows() == _mat.rows() );
	return resultMat;
}
/// normalization of a vector_t
template <typename Number>
vector_t<Number> normalize( const vector_t<Number>& in ) {
	return in / norm( in );
}
/// projection of a vector on a subspace
template <typename Number>
vector_t<Number> project( const vector_t<Number>& in, const std::vector<std::size_t>& dimensions ) {
	if ( dimensions.empty() ) {
		return vector_t<Number>::Zero( 0 );
	}
	vector_t<Number> projectedVector = vector_t<Number>::Zero( dimensions.size() );

	for ( std::size_t i = 0; i < dimensions.size(); ++i ) {
		if ( dimensions.at( i ) < std::size_t( in.rows() ) && dimensions.at( i ) >= 0 ) {
			projectedVector( i ) = in( dimensions.at( i ) );
		}
	}
	return projectedVector;
}
/// scalar projection of a vector onto another vector
template <typename Number>
vector_t<Number> scalarProjection( const vector_t<Number>& source, const vector_t<Number>& target ) {
	Number targetLength = norm( target );
	vector_t<Number> res = ( ( source.dot( target ) ) / ( targetLength * targetLength ) ) * target;
	return res;
}
/// dimension of the subspace spanned by a set of vectors
template <typename Number>
int effectiveDimension( const std::vector<vector_t<Number>>& vertices ) {
	if ( !vertices.empty() ) {
		if ( vertices.size() == 1 ) {
			return 0;
		}
		long maxDim = vertices.begin()->rows();
		matrix_t<Number> matr = matrix_t<Number>( vertices.size() - 1, maxDim );
		// use first vertex as origin, start at second vertex
		unsigned rowIndex = 0;
		for ( auto vertexIt = ++vertices.begin(); vertexIt != vertices.end(); ++vertexIt, ++rowIndex ) {
			matr.row( rowIndex ) = ( *vertexIt - *vertices.begin() ).transpose();
		}
		return int( matr.fullPivLu().rank() );
	}
	return -1;
}
/**
 * @brief Tests for linear dependency of two vectors
 * * @tparam Number
 * @param lhs
 * @param rhs
 * @return std::pair<bool, Number> True, if they are linear dependent. The number is the conversion factor, if they are linear dependent.
 */
template <typename Number>
inline std::pair<bool, Number> linearDependent( const vector_t<Number>& lhs, const vector_t<Number>& rhs ) {
	unsigned firstNonZeroPos = 0;
	if ( lhs.nonZeros() == 0 || rhs.nonZeros() == 0 ) {
		return std::make_pair( true, 0 );
	}

	// both are non-Zero vectors
	while ( firstNonZeroPos != lhs.rows() && lhs( firstNonZeroPos ) == 0 ) {
		++firstNonZeroPos;
	}
	if ( firstNonZeroPos == lhs.rows() ) {
		return std::make_pair( false, 0 );
	}
	if ( rhs( firstNonZeroPos ) == 0 ) {
		return std::make_pair( false, 0 );
	}
	Number scalar = lhs( firstNonZeroPos ) / rhs( firstNonZeroPos );
	if ( lhs == rhs * scalar ) {
		//std::cout << __func__ << ": scalar: " << scalar << std::endl;
		return std::make_pair( true, scalar );
	}
	return std::make_pair( false, 0 );
}
/// rounding function for exact arithmetic types
template <typename Number, carl::DisableIf<std::is_same<Number, double>> = carl::dummy>
vector_t<Number> reduceNumberRepresentation( const vector_t<Number>& in ) {
	vector_t<Number> res = in;
	if ( in.rows() > 1 ) {
		// collect common denominator to obtain integer vector
		Number commonDenominator = carl::getDenom( in( 0 ) );
		for ( unsigned i = 1; i < in.rows(); ++i ) {
			commonDenominator *= carl::getDenom( in( i ) );
		}
		// make the vector integer
		res *= commonDenominator;

		// find gcd for the numerators
		Number gcd = carl::gcd( res( 0 ), res( 1 ) );
		for ( unsigned i = 2; i < res.rows(); ++i ) {
			gcd = carl::gcd( gcd, res( i ) );
		}
		assert( gcd != Number( 0 ) );
		res = res / gcd;
	}
	return res;
}
/// reduction for double (noop)
template <typename Number, carl::EnableIf<std::is_same<Number, double>> = carl::dummy>
vector_t<Number> reduceNumberRepresentation( const vector_t<Number>& in ) {
	return in;
}
/// method to create code string of a matrix
template <typename Number>
std::string createCode( const matrix_t<Number>& in, unsigned index = 0 ) {
	std::stringstream st;
	st << "matrix_t<Number> matrix" << index << " = matrix_t<Number>(" << in.rows() << "," << in.cols() << ");\n";
	st << "matrix" << index << " << ";
	for ( unsigned rowIndex = 0; rowIndex < in.rows(); ++rowIndex ) {
		for ( unsigned colIndex = 0; colIndex < in.cols(); ++colIndex ) {
			if ( rowIndex == in.rows() - 1 && colIndex == in.cols() - 1 ) {
				st << in( rowIndex, colIndex );
			} else {
				st << in( rowIndex, colIndex ) << ", ";
			}
		}
	}
	st << ";\n";
	return st.str();
}

/// method to create code string of a vector
template <typename Number>
std::string createCode( const vector_t<Number>& in, unsigned index = 0 ) {
	std::stringstream st;
	st << "vector_t<Number> vector" << index << " = vector_t<Number>(" << in.rows() << ");\n";
	st << "vector" << index << " << ";
	for ( unsigned rowIndex = 0; rowIndex < in.rows(); ++rowIndex ) {
		if ( rowIndex == in.rows() - 1 ) {
			st << in( rowIndex );
		} else {
			st << in( rowIndex ) << ", ";
		}
	}
	st << ";\n";
	return st.str();
}

/**
	 * @brief Computes the matrix exponential via conversion to double and then using eigen::exp.
	 *
	 * @tparam Number The used number representation.
	 * @param inMatrix Matrix describing the system of linear ODEs.
	 * @return matrix_t<Number> Matrix exponential of inMatrix.
	 */
template <typename Number>
matrix_t<Number> matrixExponential( const matrix_t<Number>& inMatrix ) {
	// convert to double to be able to use eigen::exp.
	auto doubleMatrix = convert<Number, double>( inMatrix );
	auto expMatrix = doubleMatrix.exp();
	// convert back to the original number representation
	return convert<double, Number>( expMatrix );
}
/// Tests whether a point lies in a half-space
template <typename Number>
bool satisfiesIneqation( const vector_t<Number>& constraint, Number constant, const vector_t<Number>& point ) {
	Number sp = constraint.dot( point );

	if ( sp < constant ) {
		return true;
	}
	return carl::AlmostEqual2sComplement( sp, constant );
}

}  // namespace hypro

namespace std {
/// hash functor
template <class Number>
struct hash<hypro::vector_t<Number>> {
	std::size_t operator()( hypro::vector_t<Number> const& vector ) const {
		return Eigen::VectorHashValue( vector );
	}
};
/// hash functor
template <class Number>
struct hash<hypro::matrix_t<Number>> {
	std::size_t operator()( hypro::matrix_t<Number> const& matrix ) const {
		return Eigen::MatrixHashValue( matrix );
	}
};
/// absolute value function
inline mpq_class abs( const mpq_class& x ) {
	return carl::abs( x );
}
/// square-root function
inline mpq_class sqrt( const mpq_class& x ) {
	return carl::sqrt( x );
}
/// maximum function
inline mpq_class max( const mpq_class& x, const mpq_class& y ) {
	return ( x > y ? x : y );
}

}  // namespace std
