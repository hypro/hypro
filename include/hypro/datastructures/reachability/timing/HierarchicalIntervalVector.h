/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../../types.h"
#include "../../../util/convenienceOperators.h"
#include "../../../util/logging/Logger.h"

#include <utility>
#include <vector>

namespace hypro {

    template<typename T, typename Number>
    struct endPoint {
        T type;
        Number timePoint;

        endPoint(const T &t, const Number &n)
                : type(t), timePoint(n) {}

        friend bool operator==(const endPoint<T, Number> &lhs, const endPoint<T, Number> &rhs) {
            return (lhs.type == rhs.type && lhs.timePoint == rhs.timePoint);
        }

        friend bool operator!=(const endPoint<T, Number> &lhs, const endPoint<T, Number> &rhs) { return !(lhs == rhs); }

        friend std::ostream &operator<<(std::ostream &out, const endPoint<T, Number> &in) {
            return out << "(" << carl::convert<Number, double>(in.timePoint) << "," << in.type << ")";
        }
    };

    template<typename T, typename Number>
    class HierarchicalIntervalVector {
    private:
        std::vector<T> mOrder;
        std::vector<endPoint<T, Number>> mIntervals;

        using Ivec = std::vector<endPoint<T, Number>>;

    public:
        HierarchicalIntervalVector() = delete;

        explicit HierarchicalIntervalVector(const std::vector<T> &order)
                : mOrder(order) {}

        HierarchicalIntervalVector(const HierarchicalIntervalVector<T, Number> &in)
                : mOrder(in.getTypeOrder()), mIntervals(in.getIntervals()) {}

        /**
         * @brief Destroy the Hierarchical Interval Vector object
         */
        ~HierarchicalIntervalVector() {}

        HierarchicalIntervalVector<T, Number> &operator=(const HierarchicalIntervalVector<T, Number> &orig) = default;

        HierarchicalIntervalVector<T, Number> &operator=(HierarchicalIntervalVector<T, Number> &&orig) = default;

        void initialize(const T &baseElement, Number endTime);

        void insertInterval(const T &type, const carl::Interval<Number> &timespan);

        void fill(const T &type, Number startingPoint);

        void clear() { mIntervals.clear(); }

        typename Ivec::iterator begin() { return mIntervals.begin(); }

        typename Ivec::const_iterator begin() const { return mIntervals.begin(); }

        typename Ivec::iterator end() { return mIntervals.end(); }

        typename Ivec::const_iterator end() const { return mIntervals.end(); }

        const std::vector<T> &getTypeOrder() const { return mOrder; }

        void setTypeOrder(const std::vector<T> &in) { mOrder = in; }

        /**
         * @brief      Determines if it has an entry of the passed type.
         * @param[in]  type  The type
         * @return     True if has entry, False otherwise.
         */
        bool hasEntry(const T &type) const;

        /**
         * @brief      Determines if it has entry for the exact or a smaller time interval.
         * @param[in]  timeInterval  The time interval.
         * @return     True if has entry, False otherwise.
         */
        bool hasEntry(const carl::Interval<Number> &timeInterval) const;

        /**
         * @brief      Determines if it has entry where the type matches and the interval is a subset of some contained
         * interval.
         * @param[in]  timeInterval  The time interval.
         * @param[in]  type          The type.
         * @return     True if has entry, False otherwise.
         */
        bool hasEntry(const carl::Interval<Number> &timeInterval, const T &type) const;

        /**
         * @brief      Determines if it the interval intersects some contained interval where the type matches.
         * @param[in]  timeInterval  The time interval.
         * @param[in]  type       The type.
         * @return     True if there exists a matching entry, False otherwise.
         */
        bool intersectsEntry(const carl::Interval<Number> &timeInterval, const T &type) const;

        /**
         * @brief Determines, if the passed entry is fully contained in the HIV.
         *
         * @param timeInterval
         * @param type
         * @return true
         * @return false
         */
        bool coversEntry(const carl::Interval<Number> &timeInterval, const T &type) const;

        std::vector<carl::Interval<Number>> getIntersectionIntervals(const carl::Interval<Number> &timeInterval,
                                                                     const T &type) const;

        std::vector<carl::Interval<Number>> getIntersectingIntervals(const carl::Interval<Number> &timeInterval,
                                                                     const T &type) const;

        void merge(const HierarchicalIntervalVector<T, Number> &rhs);

        const endPoint<T, Number> &back() const;

        std::size_t size() const;

        bool empty() const;

        Number getTimeHorizon() const;

        friend std::ostream &operator<<(std::ostream &out, const HierarchicalIntervalVector<T, Number> &in) {
            for (const auto &valuePair: in.mIntervals) {
                out << valuePair << ", ";
            }
            return out;
        }

        friend bool
        operator==(const HierarchicalIntervalVector<T, Number> &lhs, const HierarchicalIntervalVector<T, Number> &rhs) {
            return (lhs.mOrder == rhs.mOrder && lhs.mIntervals == rhs.mIntervals);
        }

        friend bool
        operator!=(const HierarchicalIntervalVector<T, Number> &lhs, const HierarchicalIntervalVector<T, Number> &rhs) {
            return !(lhs == rhs);
        }

        const std::vector<endPoint<T, Number>> &getIntervals() const { return mIntervals; }

    private:
        bool isLess(const T &lhs, const T &rhs) const;

        std::size_t getOrderIndex(const T &type) const;

        bool isSane() const;
    };

}  // namespace hypro

#include "HIV_util.h"
#include "HierarchicalIntervalVector.tpp"
