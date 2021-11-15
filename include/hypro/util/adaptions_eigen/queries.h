#pragma once
#include "adaptions_eigen.h"

namespace hypro {

/// finds duplicate rows in a matrix, returns indices of duplicate rows
template <typename Number>
std::vector<Eigen::Index> getDuplicateRows( const matrix_t<Number>& m ) {
	std::vector<Eigen::Index> result;

	for ( Eigen::Index i = 0; i < m.rows(); ++i ) {
		for ( Eigen::Index j = i + 1; j < m.rows(); ++j ) {
			if ( vector_t<Number>( m.row( i ) ) == vector_t<Number>( m.row( j ) ) ) {
				result.push_back( i );
			}
		}
	}
	return result;
}

/// finds duplicate rows in a pair of matrix and vector, returns indices of duplicate rows
template <typename Number>
std::vector<Eigen::Index> getDuplicateRows( const matrix_t<Number>& m, const vector_t<Number>& v ) {
	assert( m.rows() == v.rows() );
	std::vector<Eigen::Index> result;

	for ( Eigen::Index i = 0; i < m.rows(); ++i ) {
		for ( Eigen::Index j = i + 1; j < m.rows(); ++j ) {
			if ( vector_t<Number>( m.row( i ) ) == vector_t<Number>( m.row( j ) ) && v( i ) == v( j ) ) {
				result.push_back( i );
			}
		}
	}
	return result;
}


/// returns true if the passed row is also a row in the passed matrix
template <typename Number>
bool hasRow( const matrix_t<Number>& m, const vector_t<Number>& row ) {
	if ( m.cols() == row.rows() ) {
		for ( Eigen::Index i = 0; i < m.rows(); ++i ) {
			if ( vector_t<Number>( m.row( i ) ) == row ) {
				return true;
			}
		}
	}
	return false;
}

}  // namespace hypro