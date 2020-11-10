/**
 * This file contains transformation functions for matrices and vectors.
 */

#pragma once

namespace hypro {

template <typename Number, typename IdxType>
matrix_t<Number> selectRows( const matrix_t<Number>& original, const std::vector<IdxType>& rowIndices ) {
	matrix_t<Number> res = matrix_t<Number>( rowIndices.size(), original.cols() );
	for ( Eigen::Index index = 0; index < res.rows(); index++ ) {
		res.row( index ) = original.row( Eigen::Index( rowIndices[index] ) );
	}
	return res;
}

template <typename Number, typename IdxType>
matrix_t<Number> removeRows( const matrix_t<Number>& original, const std::vector<IdxType>& rowIndices ) {
	// compute all rows that need to remain, select those.
	std::vector<IdxType> remainingRows;
	for ( Eigen::Index i = 0; i < original.rows(); ++i ) {
		if ( std::find( rowIndices.begin(), rowIndices.end(), IdxType( i ) ) == rowIndices.end() ) {
			remainingRows.emplace_back( i );
		}
	}
	return selectRows( original, remainingRows );
}

template <typename Number>
matrix_t<Number>& appendRow( matrix_t<Number>& original, const vector_t<Number>& row ) {
	assert( row.rows() == original.cols() );
	original.conservativeResize( original.rows() + 1, original.cols() );
	original.row( original.rows() - 1 ) = row;
	return original;
}

template <typename Number>
vector_t<Number>& appendRow( vector_t<Number>& original, Number entry ) {
	original.conservativeResize( original.rows() + 1 );
	original( original.rows() - 1 ) = entry;
	return original;
}

template <typename Number, typename IdxType>
vector_t<Number> selectRows( const vector_t<Number>& original, const std::vector<IdxType>& rowIndices ) {
	vector_t<Number> res = vector_t<Number>( rowIndices.size() );
	for ( Eigen::Index index = 0; index < res.rows(); index++ ) {
		res( index ) = original( Eigen::Index( rowIndices[index] ) );
	}
	return res;
}

template <typename Number, typename IdxType>
vector_t<Number> removeRows( const vector_t<Number>& original, const std::vector<IdxType>& rowIndices ) {
	return vector_t<Number>( removeRows( matrix_t<Number>( original ), rowIndices ) );
}

template <typename Number, typename IdxType>
matrix_t<Number> removeCol( const matrix_t<Number>& original, IdxType colIndex ) {
	if ( colIndex == 0 ) {
		return original.block( 0, 1, original.rows(), original.cols() - 1 );
	}
	if ( Eigen::Index( colIndex ) == original.cols() - 1 ) {
		return original.block( 0, 0, original.rows(), original.cols() - 1 );
	}
	matrix_t<Number> res = matrix_t<Number>( original.rows(), original.cols() - 1 );
	res.block( 0, 0, original.rows(), colIndex ) = original.leftCols( colIndex );
	res.block( 0, colIndex, original.rows(), original.cols() - ( colIndex + 1 ) ) = original.rightCols( original.cols() - ( colIndex + 1 ) );
	return res;
}

template <typename Number, typename IdxType>
matrix_t<Number> selectCols( const matrix_t<Number>& original, const std::vector<IdxType>& colIndices ) {
	matrix_t<Number> res = matrix_t<Number>( original.rows(), Eigen::Index( colIndices.size() ) );
	for ( Eigen::Index index = 0; index < res.cols(); index++ ) {
		res.col( index ) = original.col( Eigen::Index( colIndices[index] ) );
	}
	return res;
}

template <typename Number>
static matrix_t<Number> combine(
	  const matrix_t<Number>& lhsMatrix, const matrix_t<Number>& rhsMatrix,
	  const std::vector<std::string>& haVar, const std::vector<std::string>& lhsVar, const std::vector<std::string>& rhsVar ) {
	Eigen::Index lhsRows = lhsMatrix.rows();
	Eigen::Index rhsRows = rhsMatrix.rows();
	matrix_t<Number> tmpMatrix = matrix_t<Number>::Zero( lhsRows + rhsRows, haVar.size() );

	size_t col = 0;
	unsigned colLhs = 0;
	while ( colLhs < lhsMatrix.cols() ) {
		if ( haVar[col] == lhsVar[colLhs] ) {
			tmpMatrix.block( 0, col, lhsRows, 1 ) = lhsMatrix.block( 0, colLhs, lhsRows, 1 );
			col++;
			colLhs++;
			continue;
		}
		if ( haVar[col] < lhsVar[colLhs] ) {
			col++;
			continue;
		}
	}

	col = 0;
	unsigned colRhs = 0;
	while ( colRhs < rhsMatrix.cols() ) {
		if ( haVar[col] == rhsVar[colRhs] ) {
			tmpMatrix.block( lhsRows, col, rhsRows, 1 ) = rhsMatrix.block( 0, colRhs, rhsRows, 1 );
			col++;
			colRhs++;
			continue;
		}
		if ( haVar[col] < rhsVar[colRhs] ) {
			col++;
			continue;
		}
	}
	return tmpMatrix;
}

template <typename Number>
static vector_t<Number> combine( const vector_t<Number>& lhs, const vector_t<Number>& rhs ) {
	vector_t<Number> newVec = vector_t<Number>::Zero( lhs.size() + rhs.size() );
	newVec.head( lhs.size() ) = lhs;
	newVec.tail( rhs.size() ) = rhs;

	return newVec;
}

// interprets all vectors as row-vectors and creates a matrix
template <typename Number>
static matrix_t<Number> combineRows( const std::vector<vector_t<Number>>& vectors ) {
	if ( vectors.empty() ) {
		return matrix_t<Number>( 0, 0 );
	}
	matrix_t<Number> res = matrix_t<Number>( vectors.size(), vectors.begin()->rows() );

	Eigen::Index rowCount = 0;
	for ( const auto& r : vectors ) {
		assert( r.rows() == res.cols() );
		res.row( rowCount ) = r;
		++rowCount;
	}

	return res;
}

}  // namespace hypro
