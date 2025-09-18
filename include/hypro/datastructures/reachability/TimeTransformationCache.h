/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../HybridAutomaton/Location.h"

#include <unordered_map>

namespace hypro {

/**
 * @brief Returns only the linear part (matrix) of a matrix describing affine dynamics.
 * @tparam Number The used number type
 * @param timeTrafo The matrix describing affine dynamics
 * @return auto The sub-matrix describing only the linear dynamics.
 */
    template<class Number>
    auto timeTrafoMatrixBlock(matrix_t<Number> const &timeTrafo) {
        return timeTrafo.block(0, 0, timeTrafo.rows() - 1, timeTrafo.cols() - 1);
    }

/**
 * @brief Returns only the translation vector of a matrix describing affine dynamics.
 * @tparam Number The used number type
 * @param timeTrafo The matrix describing affine dynamics
 * @return auto The sub-vector describing the translational part of the dynamics
 */
    template<class Number>
    auto timeTrafoVectorBlock(matrix_t<Number> const &timeTrafo) {
        return timeTrafo.col(timeTrafo.cols() - 1).head(timeTrafo.rows() - 1);
    }

// need to get inverser of matrix -> fullMatrix inverse, other two through the functions
    template<typename Number>
    struct LTITimeTransformation {
        matrix_t<Number> fullMatrix;
        matrix_t<Number> matrix;
        vector_t<Number> vector;

       LTITimeTransformation inverse() const {
            LTITimeTransformation inv;

            // Invert linear block
            inv.matrix = matrix.inverse();

            // Compute inverse translation: -A^{-1} b
            inv.vector = -inv.matrix * vector;

            // Rebuild full homogeneous matrix
            inv.fullMatrix.setIdentity(matrix.rows() + 1, matrix.cols() + 1);
            inv.fullMatrix.template block<Eigen::Dynamic, Eigen::Dynamic>(
            0, 0, matrix.rows(), matrix.cols()
            ) = inv.matrix;
            inv.fullMatrix.template block<Eigen::Dynamic, 1>(
            0, matrix.cols(), matrix.rows(), 1
            ) = inv.vector;

            return inv;
        }
    };

    template<typename Location>
    class TimeTransformationCache {
        using Number = typename Location::NumberType;
        // for each loc, matrix multiplies by itself
        std::unordered_map<Location const *, LTITimeTransformation<Number>> mMatrices{};

    public:
        LTITimeTransformation<Number> const &
        getTransformation(Location const *loc, tNumber timeStep, std::size_t I = 0) {
            auto search = mMatrices.find(loc);

            if (search == mMatrices.end()) {
                auto matrix = computeTimeTransformation(loc->getLinearFlow(I), timeStep);
                std::tie(search, std::ignore) = mMatrices.emplace(std::make_pair(loc,
                                                                                 LTITimeTransformation<Number>{matrix,
                                                                                                               matrix_t<Number>(
                                                                                                                       timeTrafoMatrixBlock(
                                                                                                                               matrix)),
                                                                                                               vector_t<Number>(
                                                                                                                       timeTrafoVectorBlock(
                                                                                                                               matrix))}));
            }
            return search->second;
        }
    };

}  // namespace hypro
