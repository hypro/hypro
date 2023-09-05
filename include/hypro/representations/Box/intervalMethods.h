/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../datastructures/Halfspace.h"
#include "../../types.h"

namespace hypro {

/**
 * @brief      Performs intersection of a vector of intervals with a halfspace.
 * @details    The idea is to use ICP-style contractions to obtain the resulting box.
 * As we know the constraint (the halfspace) is linear, we only need to perform one contraction per dimension and the order does not matter.
 * @param      intervals  The intervals as a vector (call by reference).
 * @param[in]  hsp        The halfspace
 *
 * @tparam     Number     The used number type.
 *
 * @return     True, if one of the resulting intervals is empty, False otherwise.
 */
    template<typename Number>
    bool icpIntersectHalfspace(std::vector<carl::Interval<Number>> &intervals, const Halfspace<Number> &hsp) {
        assert(Eigen::Index(intervals.size()) == hsp.normal().rows());

        // contraction variable cVar, other variables (for that run) oVar.
        for (Eigen::Index cVar = 0; cVar < hsp.normal().rows(); ++cVar) {
            if (hsp.normal()(cVar) != 0) {
                // initialize with constant part.
                carl::Interval<Number> newIntv = Number(-1) *
                                                 carl::Interval<Number>(hsp.offset(), carl::BoundType::INFTY,
                                                                        hsp.offset(), carl::BoundType::WEAK);
                // update interval using interval arithmetic (ICP-style: propagation).
                for (Eigen::Index oVar = 0; oVar < hsp.normal().rows(); ++oVar) {
                    if (cVar != oVar && hsp.normal()(oVar) != 0) {
                        newIntv += hsp.normal()(oVar) * intervals[oVar];
                    }
                }
                newIntv /= Number(-hsp.normal()(cVar));
                intervals[cVar] = set_intersection(intervals[cVar], newIntv);
                if (isEmpty(intervals[cVar])) {
                    return true;
                }
            }
        }
        return false;
    }

    template<typename Number>
    void reduceIntervalsNumberRepresentation(std::vector<carl::Interval<Number>> &, unsigned) {
        // do nothing.
    }

    void reduceIntervalsNumberRepresentation(std::vector<carl::Interval<mpq_class>> &intervals, unsigned limit);

}  // namespace hypro
