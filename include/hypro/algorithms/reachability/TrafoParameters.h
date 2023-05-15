
/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../representations/SupportFunction/util.h"
#include "../../types.h"

namespace hypro {

    template<typename Number>
    class TrafoParameters {
    private:
        matrix_t<Number> mMatrix;
        vector_t<Number> mVector;
        std::shared_ptr<lintrafoParameters<Number>> mLintrafoParameters;

    public:
        TrafoParameters() = default;

        TrafoParameters(const matrix_t<Number> &A)
                : mMatrix(A), mVector(vector_t<Number>::Zero(A.cols())), mLintrafoParameters(
                std::make_shared<lintrafoParameters<Number>>(A, vector_t<Number>::Zero(A.cols()))) {}

        TrafoParameters(const matrix_t<Number> &A, const vector_t<Number> &b)
                : mMatrix(A), mVector(b),
                  mLintrafoParameters(std::make_shared<lintrafoParameters<Number>>(mMatrix, mVector)) {}

        TrafoParameters(std::shared_ptr<lintrafoParameters<Number>> parameters)
                : mMatrix(parameters.matrix()), mVector(parameters.vector()), mLintrafoParameters(parameters) {}

        const matrix_t<Number> &matrix() const {
            return mMatrix;
        }

        const vector_t<Number> &vector() const {
            return mVector;
        }

        std::shared_ptr<lintrafoParameters<Number>> parameters() const {
            return mLintrafoParameters;
        }

        void setMatrix(const matrix_t<Number> &A) {
            mMatrix = A;
        }

        void setVector(const vector_t<Number> &b) {
            mVector = b;
        }
    };

}  // namespace hypro
