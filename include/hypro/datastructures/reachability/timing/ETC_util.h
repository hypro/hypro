/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "EventTimingContainer.h"

namespace hypro {

    template<typename N>
    static EventTimingContainer<N> merge(std::initializer_list<EventTimingContainer<N>> l) {
        return merge(std::vector<EventTimingContainer<N>>(l));
    }

    template<typename N>
    static EventTimingContainer<N> merge(std::vector<EventTimingContainer<N>> l) {
        assert(l.size() != 0);
        // refine/replace transitions
        auto lIt = l.begin();
        auto res = (*lIt);
        lIt++;
        for (; lIt != l.end(); ++lIt) {
            for (const auto &transitionTimingPair: (*lIt).getTransitionTimings()) {
                if (!res.hasTransition(transitionTimingPair.first)) {
                    // Test: Only insert transitions everyone agrees on.
                    // res.setTransitionTimings(transitionTimingPair.first, transitionTimingPair.second);
                } else {
                    auto tmp = res.getTransitionTimings(transitionTimingPair.first);
                    tmp = merge({tmp, transitionTimingPair.second});

                    res.setTransitionTimings(transitionTimingPair.first, tmp);
                }
            }
            // Test: Only insert transitions everyone agrees on - cleanup: Remove all timings which are not present in the current node.
            for (auto tPairIt = res.rGetTransitionTimings().begin(); tPairIt != res.rGetTransitionTimings().end();) {
                if (!(*lIt).hasTransition((*tPairIt).first)) {
                    tPairIt = res.rGetTransitionTimings().erase(tPairIt);
                } else {
                    ++tPairIt;
                }
            }

            res.setInvariantTimings(merge({res.getInvariantTimings(), (*lIt).getInvariantTimings()}));
            res.setBadStateTimings(merge({res.getBadStateTimings(), (*lIt).getBadStateTimings()}));
        }
        return res;
    }

    template<typename N>
    static EventTimingContainer<N> unite(std::initializer_list<EventTimingContainer<N>> l) {
        assert(l.size() != 0);
        // refine/replace transitions
        auto lIt = l.begin();
        auto res = *lIt++;
        for (; lIt != l.end(); ++lIt) {
            for (const auto &transitionTimingPair: (*lIt).getTransitionTimings()) {
                if (!res.hasTransition(transitionTimingPair.first)) {
                    // Test: Only insert transitions everyone agrees on.
                    // res.setTransitionTimings(transitionTimingPair.first, transitionTimingPair.second);
                } else {
                    auto tmp = res.getTransitionTimings(transitionTimingPair.first);
                    tmp = unite({tmp, transitionTimingPair.second});

                    res.setTransitionTimings(transitionTimingPair.first, tmp);
                }
            }
            // Test: Only insert transitions everyone agrees on - cleanup: Remove all timings which are not present in the current node.
            for (auto tPairIt = res.rGetTransitionTimings().begin(); tPairIt != res.rGetTransitionTimings().end();) {
                if (!(*lIt).hasTransition((*tPairIt).first)) {
                    tPairIt = res.rGetTransitionTimings().erase(tPairIt);
                } else {
                    ++tPairIt;
                }
            }

            res.setInvariantTimings(unite({res.getInvariantTimings(), (*lIt).getInvariantTimings()}));
            res.setBadStateTimings(unite({res.getBadStateTimings(), (*lIt).getBadStateTimings()}));
        }
        return res;
    }

    std::vector<carl::Interval<tNumber>> getEnabledTimings(const HierarchicalIntervalVector<CONTAINMENT, tNumber> &in);

    template<typename N>
    static bool positiveCover(const HierarchicalIntervalVector<CONTAINMENT, N> &in, const carl::Interval<N> &intv) {
        DEBUG("hypro.datastructures.etc", "In-interval: " << intv);
        // get all intervals that satisfy bot criteria: Intersection interval-wise and correct type.
        auto intervals = getEnabledTimings(in);
        // we assume the intervals returned are pairwise-disjunct.
        if (intervals.size() == 1) {
            DEBUG("hypro.datastructures.etc", "Obtained enabled interval: " << intervals[0]);
            if (carl::set_is_subset(intv, intervals[0])) {
                return true;
            }
#ifdef HYPRO_LOGGING
            else {
                DEBUG("hypro.datastructures.etc", "Interval: " << intv << " is not contained in " << intervals[0]);
            }
#endif
        }
        return false;
    }

    template<typename N>
    static std::optional<EventTimingContainer<N>> intersect(const std::vector<EventTimingContainer<N>> &candidates) {
        if (candidates.size() == 0) {
            return std::nullopt;
        }

        EventTimingContainer<N> res = candidates.front();
        TRACE("hypro.datastructures.timing", "Start with " << res);
        for (auto cIt = ++candidates.begin(); cIt != candidates.end(); ++cIt) {
            // pairwise intersect invariant timings
            res.setInvariantTimings(merge({res.getInvariantTimings(), cIt->getInvariantTimings()}));
            TRACE("hypro.datastructures.timing", "Intersected invariant, got " << res);

            // pairwise intersect bad state timings
            auto tmp = intersect({res.getBadStateTimings(), cIt->getBadStateTimings()});
            if (tmp) {
                res.setBadStateTimings(*tmp);
            }
            TRACE("hypro.datastructures.timing", "Intersected bad states, got " << res);

            // intersect transition timings, if possible
            for (const auto &tHIVPair: res.getTransitionTimings()) {
                // intersect-join both.
                const auto &rhsTimings = cIt->getTransitionTimings();
                if (rhsTimings.find(tHIVPair.first) != rhsTimings.end()) {
                    tmp = intersect({tHIVPair.second, rhsTimings.at(tHIVPair.first)});
                    if (tmp) {
                        res.setTransitionTimings(tHIVPair.first, *tmp);
                    }
                }

                // add all transition information which is not there.
                for (const auto &rhsPair: rhsTimings) {
                    if (res.getTransitionTimings().find(rhsPair.first) == res.getTransitionTimings().end()) {
                        res.setTransitionTimings(rhsPair.first, rhsPair.second);
                    }
                }
            }
            TRACE("hypro.datastructures.timing", "Intersected transition timings, got " << res);
        }

        return res;
    }

}  // namespace hypro
