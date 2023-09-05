/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

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
