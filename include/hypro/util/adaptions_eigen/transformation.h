/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * This file contains transformation functions for matrices and vectors.
 */

#pragma once

namespace hypro {

    template<typename Number, typename IdxType>
    matrix_t<Number> selectRows(const matrix_t<Number> &original, const std::vector<IdxType> &rowIndices) {
        matrix_t<Number> res = matrix_t<Number>(rowIndices.size(), original.cols());
        for (Eigen::Index index = 0; index < res.rows(); index++) {
            res.row(index) = original.row(Eigen::Index(rowIndices[index]));
        }
        return res;
    }

    template<typename Number, typename IdxType>
    matrix_t<Number> removeRows(const matrix_t<Number> &original, const std::vector<IdxType> &rowIndices) {
        // compute all rows that need to remain, select those.
        std::vector<IdxType> remainingRows;
        for (Eigen::Index i = 0; i < original.rows(); ++i) {
            if (std::find(rowIndices.begin(), rowIndices.end(), IdxType(i)) == rowIndices.end()) {
                remainingRows.emplace_back(i);
            }
        }
        return selectRows(original, remainingRows);
    }

    template<typename Number>
    matrix_t<Number> &appendRow(matrix_t<Number> &original, const vector_t<Number> &row) {
        assert(row.rows() == original.cols());
        original.conservativeResize(original.rows() + 1, original.cols());
        original.row(original.rows() - 1) = row;
        return original;
    }

    template<typename Number>
    matrix_t<Number> &concatenateVertically(matrix_t<Number> &original, const matrix_t<Number> &other) {
        assert(original.cols() == other.cols());
        Eigen::Index originalRowCount = original.rows();
        original.conservativeResize(original.rows() + other.rows(), original.cols());
        original.block(originalRowCount, 0, other.rows(), other.cols()) = other;
        return original;
    }

    template<typename Number>
    vector_t<Number> &concatenateVertically(vector_t<Number> &original, const vector_t<Number> &other) {
        Eigen::Index originalRowCount = original.rows();
        original.conservativeResize(original.rows() + other.rows(), original.cols());
        original.block(originalRowCount, 0, other.rows(), other.cols()) = other;
        return original;
    }

    template<typename Number>
    vector_t<Number> &appendRow(vector_t<Number> &original, Number entry) {
        original.conservativeResize(original.rows() + 1);
        original(original.rows() - 1) = entry;
        return original;
    }

/**
 * @brief Append a specified number of zeroes at the end of a vector_t
 * @tparam Number The used number type
 * @param original The original vector
 * @param numberZeroes The number of zeroes that should be appended to original
 * @return A reference to the updated vector_t
 */
    template<typename Number>
    vector_t<Number> appendZeroes(vector_t<Number> &original, std::size_t numberZeroes) {
        auto oldSize = original.rows();
        original.conservativeResize(original.rows() + numberZeroes);
        original.block(oldSize, 0, 1, numberZeroes) = vector_t<Number>::Zero(numberZeroes);
        return original;
    }

    template<typename Number, typename IdxType>
    vector_t<Number> selectRows(const vector_t<Number> &original, const std::vector<IdxType> &rowIndices) {
        vector_t<Number> res = vector_t<Number>(rowIndices.size());
        for (Eigen::Index index = 0; index < res.rows(); index++) {
            res(index) = original(Eigen::Index(rowIndices[index]));
        }
        return res;
    }

    template<typename Number, typename IdxType>
    vector_t<Number> removeRows(const vector_t<Number> &original, const std::vector<IdxType> &rowIndices) {
        return vector_t<Number>(removeRows(matrix_t<Number>(original), rowIndices));
    }

    template<typename Number, typename IdxType>
    matrix_t<Number> removeCol(const matrix_t<Number> &original, IdxType colIndex) {
        if (colIndex == 0) {
            return original.block(0, 1, original.rows(), original.cols() - 1);
        }
        if (Eigen::Index(colIndex) == original.cols() - 1) {
            return original.block(0, 0, original.rows(), original.cols() - 1);
        }
        matrix_t<Number> res = matrix_t<Number>(original.rows(), original.cols() - 1);
        res.block(0, 0, original.rows(), colIndex) = original.leftCols(colIndex);
        res.block(0, colIndex, original.rows(), original.cols() - (colIndex + 1)) = original.rightCols(
                original.cols() - (colIndex + 1));
        return res;
    }

    template<typename Number, typename IdxType>
    matrix_t<Number> selectCols(const matrix_t<Number> &original, const std::vector<IdxType> &colIndices) {
        matrix_t<Number> res = matrix_t<Number>(original.rows(), Eigen::Index(colIndices.size()));
        for (Eigen::Index index = 0; index < res.cols(); index++) {
            res.col(index) = original.col(Eigen::Index(colIndices[index]));
        }
        return res;
    }

    template<typename Number>
    static matrix_t<Number> combine(
            const matrix_t<Number> &lhsMatrix, const matrix_t<Number> &rhsMatrix,
            const std::vector<std::string> &haVar, const std::vector<std::string> &lhsVar,
            const std::vector<std::string> &rhsVar) {
        Eigen::Index lhsRows = lhsMatrix.rows();
        Eigen::Index rhsRows = rhsMatrix.rows();
        matrix_t<Number> tmpMatrix = matrix_t<Number>::Zero(lhsRows + rhsRows, haVar.size());

        size_t col = 0;
        unsigned colLhs = 0;
        while (colLhs < lhsMatrix.cols()) {
            if (haVar[col] == lhsVar[colLhs]) {
                tmpMatrix.block(0, col, lhsRows, 1) = lhsMatrix.block(0, colLhs, lhsRows, 1);
                col++;
                colLhs++;
                continue;
            }
            // if (haVar[col] < lhsVar[colLhs]) {
            else {
                col++;
                continue;
            }
        }

        col = 0;
        unsigned colRhs = 0;
        while (colRhs < rhsMatrix.cols()) {
            if (haVar[col] == rhsVar[colRhs]) {
                tmpMatrix.block(lhsRows, col, rhsRows, 1) = rhsMatrix.block(0, colRhs, rhsRows, 1);
                col++;
                colRhs++;
                continue;
            }
            // if (haVar[col] < rhsVar[colRhs]) {
            else {
                col++;
                continue;
            }
        }
        return tmpMatrix;
    }

    template<typename Number>
    static vector_t<Number> combine(const vector_t<Number> &lhs, const vector_t<Number> &rhs) {
        vector_t<Number> newVec = vector_t<Number>::Zero(lhs.size() + rhs.size());
        newVec.head(lhs.size()) = lhs;
        newVec.tail(rhs.size()) = rhs;

        return newVec;
    }

// interprets all vectors as row-vectors and creates a matrix
    template<typename Number>
    static matrix_t<Number> createMatrix(const std::vector<vector_t<Number>> &_in) {
        if (_in.empty()) {
            return matrix_t<Number>(0, 0);
        }
        matrix_t<Number> res = matrix_t<Number>(_in.size(), _in.begin()->rows());

        Eigen::Index rowCount = 0;
        for (const auto &r: _in) {
            assert(r.rows() == res.cols());
            res.row(rowCount) = r;
            ++rowCount;
        }

        return res;
    }

    template<typename Number>
    static vector_t<Number> createVector(const std::vector<Number> &_in) {
        if (_in.empty()) {
            return vector_t<Number>(0);
        }
        vector_t<Number> result(_in.size());
        for (unsigned rowId = 0; rowId != _in.size(); ++rowId) {
            result(rowId) = Number(_in[rowId]);
        }
        return result;
    }

}  // namespace hypro
