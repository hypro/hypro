
/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "hypro/util/adaptions_eigen/adaptions_eigen.h"

namespace Eigen {

    template<>
    inline bool operator<(const hypro::vector_t<double> &lhs, const hypro::vector_t<double> &rhs) {
        if (lhs.rows() != rhs.rows()) {
            return false;
        }

        for (unsigned dim = 0; dim < lhs.rows(); ++dim) {
            if (lhs(dim) > rhs(dim)) {
                return false;
            } else if (lhs(dim) < rhs(dim)) {
                return true;
            }
        }
        return false;
    }

    template<>
    inline bool operator<=(const hypro::vector_t<double> &lhs, const hypro::vector_t<double> &rhs) {
        if (lhs.rows() != rhs.rows()) {
            return false;
        }

        for (unsigned dim = 0; dim < lhs.rows(); ++dim) {
            if (lhs(dim) > rhs(dim)) {
                return false;
            } else if (lhs(dim) <= rhs(dim)) {
                return true;
            }
        }
        return false;
    }

    template<>
    inline bool operator>(const hypro::vector_t<double> &lhs, const hypro::vector_t<double> &rhs) {
        return rhs < lhs;
    }

    template<>
    inline bool operator>=(const hypro::vector_t<double> &lhs, const hypro::vector_t<double> &rhs) {
        return rhs <= lhs;
    }

    template<>
    inline bool operator==(const hypro::vector_t<double> &lhs, const hypro::vector_t<double> &rhs) {
        if (lhs.rows() != rhs.rows()) {
            return false;
        }

        for (unsigned dim = 0; dim < lhs.rows(); ++dim) {
            // compare with 128 ULPs
            if (!carl::AlmostEqual2sComplement(lhs(dim), rhs(dim), hypro::default_double_comparison_ulps)) {
                return false;
            }
        }
        return true;
    }

    template<>
    inline bool operator!=(const hypro::vector_t<double> &lhs, const hypro::vector_t<double> &rhs) {
        return !(lhs == rhs);
    }

    template<>
    inline bool operator==(const hypro::matrix_t<double> &lhs, const hypro::matrix_t<double> &rhs) {
        if (lhs.rows() != rhs.rows() || lhs.cols() != rhs.cols()) {
            return false;
        }

        for (unsigned rowIndex = 0; rowIndex < lhs.rows(); ++rowIndex) {
            for (unsigned colIndex = 0; colIndex < lhs.cols(); ++colIndex) {
                // compare with 128 ULPs
                if (!carl::AlmostEqual2sComplement(lhs(rowIndex, colIndex), rhs(rowIndex, colIndex),
                                                   hypro::default_double_comparison_ulps)) {
                    return false;
                }
            }
        }
        return true;
    }

    template<>
    inline bool operator!=(const hypro::matrix_t<double> &lhs, const hypro::matrix_t<double> &rhs) {
        return !(lhs == rhs);
    }

}  // namespace Eigen

namespace hypro {
    template<>
    inline std::pair<bool, double> linearDependent(const vector_t<double> &lhs, const vector_t<double> &rhs) {
        unsigned firstNonZeroPos = 0;
        if (lhs.nonZeros() == 0 || rhs.nonZeros() == 0) {
            return std::make_pair(true, 0);
        }
        // both are non-Zero vectors
        while (firstNonZeroPos != lhs.rows() && lhs(firstNonZeroPos) == 0) {
            ++firstNonZeroPos;
        }
        if (firstNonZeroPos == lhs.rows()) {
            return std::make_pair(false, 0);
        }
        if (rhs(firstNonZeroPos) == 0) {
            return std::make_pair(false, 0);
        }
        double scalar = lhs(firstNonZeroPos) / rhs(firstNonZeroPos);
        if (lhs == vector_t<double>(rhs * scalar)) {
            return std::make_pair(true, scalar);
        }
        return std::make_pair(false, 0);
    }

    template<>
    bool satisfiesIneqation(const vector_t<double> &constraint, double constant, const vector_t<double> &point) {
        double sp = point.dot(constraint);
        double absDiff = fabs(sp - constant);

        if (sp < constant) {
            return true;
        }

        if (absDiff <= FLT_EPSILON) {
            return true;
        }

        return carl::AlmostEqual2sComplement(sp, constant, hypro::default_double_comparison_ulps);
    }

}  // namespace hypro
