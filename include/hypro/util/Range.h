/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

namespace hypro {
    template<typename T>
    struct Range {
        typename T::const_iterator begin = nullptr;
        typename T::const_iterator end = nullptr;

        Range(typename T::const_iterator b, typename T::const_iterator e)
                : begin(b), end(e) {}

        bool isEmpty() const {
            return begin == end;
        }

        explicit operator T() const {
            return T(begin, end);
        }
    };

    template<typename T>
    T toContainer(Range<T> &r) {
        return T(r);
    }

    template<typename T>
    Range<T> selectFirstConsecutiveRange(const T &in, std::function<bool(typename T::value_type)> cmp) {
        auto b = in.begin();
        // search for beginnig of range
        while (b != in.end() && !cmp(*b)) {
            ++b;
        }
        // if not found, return empty range
        if (b == in.end()) {
            return Range<T>(in.end(), in.end());
        }
        // find end of range
        auto e = b;
        ++e;
        while (e != in.end() && cmp(*e)) {
            ++e;
        }
        return Range<T>(b, e);
    }

}  // namespace hypro
