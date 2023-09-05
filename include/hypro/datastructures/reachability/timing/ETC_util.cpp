/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "ETC_util.h"

namespace hypro {

    std::vector<carl::Interval < tNumber>>

    getEnabledTimings(const HierarchicalIntervalVector<CONTAINMENT, tNumber> &in) {
        DEBUG("hypro.datastructures.etc", "In: " << in);

        std::vector<carl::Interval < tNumber>>
        res;
        // iterate over the stored timings
        for (auto eventIt = in.begin(); eventIt != in.end(); ++eventIt) {
            // handle the first entry differently
            if (eventIt == in.begin() &&
                static_cast<int>( eventIt->type ) > 0) {
                res.emplace_back(carl::Interval<tNumber>(0, eventIt->timePoint));
                TRACE("hypro.datastructures.etc", "Found interval " << res.back());
            }

            if (eventIt != in.begin()) {
                // consecutive interval
                if (static_cast<int>( eventIt->type ) > 0 && static_cast<int>( std::prev(eventIt)->type ) > 0) {
                    res[res.size() - 1] = res[res.size() - 1].convexHull(
                            carl::Interval<tNumber>(std::prev(eventIt)->timePoint, eventIt->timePoint));
                    TRACE("hypro.datastructures.etc", "Extended interval " << res.back());
                } else if (static_cast<int>( eventIt->type ) > 0) {
                    // add new interval
                    assert(static_cast<int>( std::prev(eventIt)->type ) <= 0);
                    res.emplace_back(std::prev(eventIt)->timePoint, eventIt->timePoint);
                    TRACE("hypro.datastructures.etc", "Found interval " << res.back());
                }
            }
        }
        DEBUG("hypro.datastructures.etc", "Return " << res.size() << " intervals.");
        return res;
    }

}  // namespace hypro
