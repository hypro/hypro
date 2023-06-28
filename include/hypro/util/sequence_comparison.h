/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "convenienceOperators.h"
#include "logging/Logger.h"

#include <algorithm>

namespace hypro {

/**
 * @brief Compares two vectors of pointerst by checking whether the pointed-to contents agree.
 * @tparam T Content-type
 * @param lhs Left-hand-side sequence
 * @param rhs Right-hand-side sequence
 * @return true If all elements from the lhs are found in the rhs
 * @return false Otherwise
 */
    template<typename T>
    bool contains(const std::vector<T *> &lhs, const std::vector<T *> &rhs) {
        TRACE("hypro.util", "Compare sequences " << lhs << " and " << rhs);
        if (lhs.size() != rhs.size()) {
            return false;
        }
        for (auto lhsIt = lhs.begin(); lhsIt != lhs.end(); ++lhsIt) {
            auto found = std::find_if(rhs.begin(), rhs.end(), [&lhsIt](const auto *rhs) { return **lhsIt == *rhs; });
            if (found == rhs.end()) {
                return false;
            }
        }
        return true;
    }

/**
 * @brief Compares two sequences of pointers.
 * @tparam T The type which is pointed to
 * @param lhs Left-hand-side sequence
 * @param rhs Right-hand-side sequence
 * @return true If both sequences contain each other, i.e., all pointed to elements are equal.
 * @return false Otherwise
 */
    template<typename T>
    bool is_equal(const std::vector<T *> &lhs, const std::vector<T *> &rhs) {
        TRACE("hypro.datastructures", "Call to function");
        return contains(lhs, rhs) && contains(rhs, lhs);
    }

}  // namespace hypro
