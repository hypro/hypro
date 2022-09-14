#pragma once
#ifdef HYPRO_USE_CLP
#include <CoinPackedMatrix.hpp>

namespace hypro {
namespace detail {

/**
 * @brief Create a CoinPackedMatrix from a matrix_t-type.
 * @detail CoinPacketMatrices are implemented as sparse matrices, however we utilize dense matrices here.
 *
 * @tparam Number
 * @param in
 * @return CoinPackedMatrix
 */
template <typename Number>
CoinPackedMatrix createMatrix( const matrix_t<Number>& in ) {
	CoinBigIndex numberElements = in.cols() * in.rows();
	double* elements = new double[numberElements];
	int* rowIndices = new int[numberElements];
	int* colIndices = new int[numberElements];

	int pos = 0;
	for ( int rowI = 0; rowI < in.rows(); ++rowI ) {
		for ( int colI = 0; colI < in.cols(); ++colI ) {
			elements[pos] = toDouble( in( rowI, colI ) );
			rowIndices[pos] = rowI;
			colIndices[pos] = colI;
			++pos;
		}
	}
	assert( pos == numberElements );

	CoinPackedMatrix matrix = CoinPackedMatrix( true, rowIndices, colIndices, elements, numberElements );
	delete[] elements;
	delete[] rowIndices;
	delete[] colIndices;
	return matrix;
}

}  // namespace detail

}  // namespace hypro
#endif
