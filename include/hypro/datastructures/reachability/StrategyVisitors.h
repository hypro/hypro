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

#include <variant>

namespace hypro {

    template<typename State>
    struct setCreationVisitor {
        matrix_t<typename State::NumberType> mMatrix;
        vector_t<typename State::NumberType> mVector;

        setCreationVisitor() = delete;

        setCreationVisitor(const matrix_t<typename State::NumberType> &constraints,
                           const vector_t<typename State::NumberType> &constants)
                : mMatrix(constraints), mVector(constants) {}

        template<typename SElement>
        typename State::repVariant operator()(const SElement &se) {
            return SElement::representationType(mMatrix, mVector);
        }
    };

}  // namespace hypro
