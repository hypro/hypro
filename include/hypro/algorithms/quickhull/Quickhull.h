/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../util/typetraits.h"

namespace hypro {
/**
 * @brief Class defining an implementation of the quickhull algorithm to compute convex hulls of a set of vertices.
 *
 * @tparam Number Number type
 * @tparam true
 * @tparam void
 */
    template<typename Number, bool Euclidian = true, typename = void>
    class QuickhullAlgorithm;

/**
 * @brief Typedef for regular quickhull implementation for the Euclidean space
 *
 * @tparam Number
 */
    template<typename Number>
    using Quickhull = QuickhullAlgorithm<Number, true, void>;

/**
 * @brief Typedef for quickhull implementation in the projective space for vertex enumeration
 *
 * @tparam Number
 */
    template<typename Number>
    using QuickIntersection = QuickhullAlgorithm<Number, false, void>;
}  // namespace hypro

#include "quickhull_exact/Quickhull.h"
