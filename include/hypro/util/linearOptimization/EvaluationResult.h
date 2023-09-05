/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../types.h"

namespace hypro {

/**
 * @brief      Struct holding results obtained from the linear optimization engine.
 * @tparam     Number  The used number type.
 */
    template<typename Number>
    struct EvaluationResult {
        vector_t<Number> optimumValue;            //*< The point leading to the evaluation value (extremum in direction).
        Number supportValue = Number(0);        //*< The value returned by the evaluation.
        SOLUTION errorCode = SOLUTION::INFEAS;    //*< Potential error code indicating success or failure of the evaluation.

        EvaluationResult() {}

        explicit EvaluationResult(SOLUTION err)
                : errorCode(err) {}

        EvaluationResult(const Number &val, SOLUTION err)
                : supportValue(val), errorCode(err) {}

        EvaluationResult(const vector_t<Number> &val, SOLUTION err)
                : optimumValue(val), errorCode(err) {}

        EvaluationResult(Number sValue, const vector_t<Number> val, SOLUTION err)
                : optimumValue(val), supportValue(sValue), errorCode(err) {}

        ~EvaluationResult() {
        }

        friend std::ostream &operator<<(std::ostream &_out, const EvaluationResult<Number> &_in) {
            _out << _in.supportValue << "(" << _in.errorCode << ") : \n"
                 << _in.optimumValue;
            return _out;
        }
    };

    template<typename Number>
    bool operator<(const EvaluationResult<Number> &lhs, const EvaluationResult<Number> &rhs) {
        if (lhs.errorCode == SOLUTION::INFEAS) {
            return true;
        }
        if (rhs.errorCode == SOLUTION::INFEAS) {
            return false;
        }
        if (lhs.errorCode == SOLUTION::INFTY) {
            // note that if both are infty, this operator does not make sense and always will return false.
            return false;
        }
        if (rhs.errorCode == SOLUTION::INFTY) {
            return true;
        }

        return lhs.supportValue < rhs.supportValue;
    }

    template<typename Number>
    bool operator>(const EvaluationResult<Number> &lhs, const EvaluationResult<Number> &rhs) {
        return rhs < lhs;
    }

    template<typename Number>
    bool operator==(const EvaluationResult<Number> &lhs, const EvaluationResult<Number> &rhs) {
        if (lhs.errorCode != rhs.errorCode) {
            return false;
        }
        if (lhs.supportValue != rhs.supportValue) {
            return false;
        }

        return lhs.optimumValue == rhs.optimumValue;
    }

}  // namespace hypro
