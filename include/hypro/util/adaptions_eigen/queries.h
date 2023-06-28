/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "adaptions_eigen.h"

namespace hypro {

/// finds duplicate rows in a matrix, returns indices of duplicate rows
    template<typename Number>
    std::vector<Eigen::Index> getDuplicateRows(const matrix_t<Number> &m) {
        std::vector<Eigen::Index> result;

        for (Eigen::Index i = 0; i < m.rows(); ++i) {
            for (Eigen::Index j = i + 1; j < m.rows(); ++j) {
                if (vector_t<Number>(m.row(i)) == vector_t<Number>(m.row(j))) {
                    result.push_back(i);
                }
            }
        }
        return result;
    }

/// finds duplicate rows in a pair of matrix and vector, returns indices of duplicate rows
    template<typename Number>
    std::vector<Eigen::Index> getDuplicateRows(const matrix_t<Number> &m, const vector_t<Number> &v) {
        assert(m.rows() == v.rows());
        std::vector<Eigen::Index> result;

        for (Eigen::Index i = 0; i < m.rows(); ++i) {
            for (Eigen::Index j = i + 1; j < m.rows(); ++j) {
                if (vector_t<Number>(m.row(i)) == vector_t<Number>(m.row(j)) && v(i) == v(j)) {
                    result.push_back(i);
                }
            }
        }
        return result;
    }


/// returns true if the passed row is also a row in the passed matrix
    template<typename Number>
    bool hasRow(const matrix_t<Number> &m, const vector_t<Number> &row) {
        if (m.cols() == row.rows()) {
            for (Eigen::Index i = 0; i < m.rows(); ++i) {
                if (vector_t<Number>(m.row(i)) == row) {
                    return true;
                }
            }
        }
        return false;
    }

}  // namespace hypro
