#pragma once
#include "adaptions_eigen.h"

namespace hypro {

/// finds duplicate rows in a matrix, returns indices of duplicate rows
template <typename Number>
std::vector<Eigen::Index> getDuplicateRows( const matrix_t<Number>& m ) {
	std::vector<Eigen::Index> result;

	std::cout << "Find duplicate rows in " << std::endl
			  << m << std::endl;

	for ( Eigen::Index i = 0; i < m.rows(); ++i ) {
		for ( Eigen::Index j = i + 1; j < m.rows(); ++j ) {
			if ( vector_t<Number>( m.row( i ) ) == vector_t<Number>( m.row( j ) ) ) {
				//std::cout << "Row " << i << " (" << vector_t<Number>( m.row( i ) ) << ") has a duplicate in row " << j << " (" << vector_t<Number>( m.row( j ) ) << ")." << std::endl;
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