/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <algorithm>
#include <iosfwd>

namespace hypro {

/**
 * Integer valued interval containing both its bounds.
 */
    struct Interval {
        int lower;
        int upper;

        int width() const {
            return upper - lower + 1;
        }

        bool operator==(Interval const &other) const {
            return lower == other.lower && upper == other.upper;
        }

        void intersect(Interval const &other) {
            *this = intersect(*this, other);
        }

        void convexHull(Interval const &other) {
            lower = std::min(lower, other.lower);
            upper = std::max(upper, other.upper);
        }

        static Interval intersect(Interval const &left, Interval const &right) {
            return {std::max(left.lower, right.lower), std::min(left.upper, right.upper)};
        }

        friend std::ostream &operator<<(std::ostream &out, Interval const &interval) {
            out << "[ " << interval.lower << ", " << interval.upper << " ]";
            return out;
        }
    };

}  // namespace hypro
