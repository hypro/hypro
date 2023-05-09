/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "adaptions_includes.h"

#include <hypro/flags.h>

namespace hypro {

#ifdef CARL_OLD_INTERVALS
    template <typename Number>
    carl::Interval<Number> set_intersection( const carl::Interval<Number>& lhs, const carl::Interval<Number>& rhs ) {
        return lhs.intersect( rhs );
    }
#endif

    template<typename Number>
    carl::BoundType lowerBoundType(const carl::Interval<Number> &in) {
#ifdef CARL_OLD_STRUCTURE
        return in.lowerBoundType();
#else
        return in.lower_bound_type();
#endif
    }

    template<typename Number>
    carl::BoundType upperBoundType(const carl::Interval<Number> &in) {
#ifdef CARL_OLD_STRUCTURE
        return in.upperBoundType();
#else
        return in.upper_bound_type();
#endif
    }

    template<typename Number>
    void setUpperBound(carl::Interval<Number> &in, Number bound) {
#ifdef CARL_OLD_STRUCTURE
        in.setUpper( bound );
#else
        in.set_upper(bound);
#endif
    }

    template<typename Number>
    void setLowerBound(carl::Interval<Number> &in, Number bound) {
#ifdef CARL_OLD_STRUCTURE
        in.setLower( bound );
#else
        in.set_lower(bound);
#endif
    }

    template<typename Number>
    void setUpperBoundType(carl::Interval<Number> &in, carl::BoundType bound) {
#ifdef CARL_OLD_STRUCTURE
        in.setUpperBoundType( bound );
#else
        in.set_upper_bound_type(bound);
#endif
    }

    template<typename Number>
    void setLowerBoundType(carl::Interval<Number> &in, carl::BoundType bound) {
#ifdef CARL_OLD_STRUCTURE
        in.setLowerBoundType( bound );
#else
        in.set_lower_bound_type(bound);
#endif
    }

    template<typename Number>
    bool isEmpty(const carl::Interval<Number> &in) {
#ifdef CARL_OLD_STRUCTURE
        return in.isEmpty();
#else
        return in.is_empty();
#endif
    }

    template<typename Number>
    bool isZero(const carl::Interval<Number> &in) {
#ifdef CARL_OLD_STRUCTURE
        return in.isZero();
#else
        return in.is_zero();
#endif
    }

    template<typename Number>
    bool isUnbounded(const carl::Interval<Number> &in) {
#ifdef CARL_OLD_STRUCTURE
        return in.isUnbounded();
#else
        return in.is_unbounded();
#endif
    }

    template<typename Number>
    carl::Interval<Number> createEmptyInterval() {
#ifdef CARL_OLD_STRUCTURE
        return carl::Interval<Number>::emptyInterval();
#else
        return carl::Interval<Number>::empty_interval();
#endif
    }

    template<typename Number>
    carl::Interval<Number> createUnboundedInterval() {
#ifdef CARL_OLD_STRUCTURE
        return carl::Interval<Number>::unboundedInterval();
#else
        return carl::Interval<Number>::unbounded_interval();
#endif
    }

    template<typename Number>
    std::vector<carl::Interval<Number>>
    split_homogeneously_weak_bounds(const carl::Interval<Number> &in, std::size_t splits) {
        std::vector<carl::Interval<Number>> result;
        if (splits == 0) {
            assert(false);
            result.emplace_back(createEmptyInterval<Number>());
            return result;
        } else if (splits == 1) {
            result.push_back(in);
            return result;
        }
        Number diameter = in.diameter();
        diameter /= Number(splits);

        carl::Interval<Number> tmp;
        tmp.set(in.lower(), in.lower() + diameter);
        setLowerBoundType(tmp, lowerBoundType(in));
        setUpperBoundType(tmp, carl::BoundType::WEAK);
        result.push_back(tmp);

        setLowerBoundType(tmp, carl::BoundType::WEAK);
        for (unsigned i = 1; i < (splits - 1); ++i) {
            tmp += diameter;
            result.push_back(tmp);
        }

        tmp += diameter;
        setUpperBoundType(tmp, upperBoundType(in));
        result.push_back(tmp);
        return result;
    }

}  // namespace hypro
