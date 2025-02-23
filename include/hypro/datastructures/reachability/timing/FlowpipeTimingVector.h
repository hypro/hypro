/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "IntegralInterval.h"

#include <algorithm>
#include <iterator>
#include <limits>
#include <vector>

namespace hypro {

    class FlowpipeTimingVector {
        std::vector <Interval> mIntervals{};

    public:
        FlowpipeTimingVector() = default;

        FlowpipeTimingVector(Interval interval)
                : mIntervals({interval}) {};

        std::vector <Interval> const &intervals() const {
            return mIntervals;
        }

        void shrinkInterval(Interval newInterval, size_t ind) {
            assert(ind < mIntervals.size());
            assert(newInterval.lower >= mIntervals[ind].lower && newInterval.upper <= mIntervals[ind].upper);

            mIntervals[ind] = newInterval;
        }

        int max() const {
            return mIntervals.empty() ? std::numeric_limits<int>::lowest() : mIntervals.back().upper;
        }

        int min() const {
            return mIntervals.empty() ? std::numeric_limits<int>::max() : mIntervals.back().lower;
        }

        bool empty() const {
            return mIntervals.empty();
        }

        bool contains(int time) const {
            for (auto &interval: mIntervals) {
                // First interval that goes beyond time
                if (interval.upper >= time) {
                    // If this one doesn't contain time, then none after will either
                    return interval.lower <= time;
                }
            }
            // If no intervals reaches beyond time then time isn't contained
            return false;
        }

        bool operator==(FlowpipeTimingVector const &other) const {
            return mIntervals == other.mIntervals;
        }

        void appendInterval(Interval interval) {
            assert(mIntervals.empty() || interval.lower > mIntervals.back().upper);

            mIntervals.push_back(interval);
        }

        void extendBack(int n = 1) {
            mIntervals.back().upper += n;
        }

        void shrinkBack(int n = 1) {
            mIntervals.back().upper -= n;
            if (mIntervals.back().width() <= 0) mIntervals.pop_back();
        }

        void intersect(FlowpipeTimingVector const &other) {
            *this = intersect(*this, other);
        }

        static FlowpipeTimingVector intersect(FlowpipeTimingVector const &left, FlowpipeTimingVector const &right) {
            auto intervalLeft = left.mIntervals.begin();
            auto intervalRight = right.mIntervals.begin();
            FlowpipeTimingVector result{};

            while (intervalLeft != left.mIntervals.end() && intervalRight != right.mIntervals.end()) {
                // interval right is entirely left of intervalRight
                if (intervalRight->upper < intervalLeft->lower) {
                    intervalRight = std::next(intervalRight);
                    continue;
                }

                if (intervalLeft->upper < intervalRight->lower) {
                    intervalLeft = std::next(intervalLeft);
                    continue;
                }

                result.appendInterval(Interval::intersect(*intervalLeft, *intervalRight));

                if (intervalLeft->upper > intervalRight->upper) {
                    intervalRight = std::next(intervalRight);
                } else {
                    intervalLeft = std::next(intervalLeft);
                }
            }
            return result;
        }

        friend std::ostream &operator<<(std::ostream &out, FlowpipeTimingVector const &left) {
            out << "{ ";
            for (auto const &interval: left.mIntervals) {
                out << interval << " ";
            }
            out << "}";

            return out;
        }
    };
}  // namespace hypro
