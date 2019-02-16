#pragma once
#include "EventTimingContainer.h"

namespace hypro {

    template<typename N>
    static EventTimingContainer<N> merge(std::initializer_list<EventTimingContainer<N>> l) {
        assert(l.size() != 0);
		// refine/replace transitions
        auto lIt = l.begin();
        auto res = *lIt++;
        for(;lIt != l.end(); ++lIt) {
            for(const auto& transitionTimingPair : (*lIt).getTransitionTimings()) {
                if(!res.hasTransition(transitionTimingPair.first)) {
                    res.setTransitionTimings(transitionTimingPair.first, transitionTimingPair.second);
                } else {
                    auto tmp = res.getTransitionTimings(transitionTimingPair.first);
                    tmp = merge({tmp,transitionTimingPair.second});

                    res.setTransitionTimings(transitionTimingPair.first, tmp);
                }
            }
            res.setInvariantTimings( merge({res.getInvariantTimings(), (*lIt).getInvariantTimings()}) );
            res.setBadStateTimings( merge({res.getBadStateTimings(), (*lIt).getBadStateTimings()}) );
        }
        return res;
    }

    template<typename N>
    static std::optional<EventTimingContainer<N>> intersect(const std::vector<EventTimingContainer<N>>& candidates) {
        if(candidates.size() == 0) {
            return std::nullopt;
        }

        EventTimingContainer<N> res = candidates.front();
        for(auto cIt = ++candidates.begin(); cIt != candidates.end(); ++cIt) {
            // pairwise intersect invariant timings
            auto tmp = intersect({res.getInvariantTimings(), cIt->getInvariantTimings()});
            if(tmp){
                res.setInvariantTimings(*tmp);
            }

            // pairwise intersect bad state timings
            tmp = intersect({res.getBadStateTimings(), cIt->getBadStateTimings()});
            if(tmp) {
                res.setInvariantTimings(*tmp);
            }

            // intersect transition timings, if possible
            for(const auto& tHIVPair : res.getTransitionTimings()) {
                // intersect-join both.
                const auto& rhsTimings = cIt->getTransitionTimings();
                if(rhsTimings.find(tHIVPair.first) != rhsTimings.end()) {
                    tmp = intersect({tHIVPair.second, rhsTimings.at(tHIVPair.first)});
                    if(tmp) {
                        res.setTransitionTimings(tHIVPair.first, *tmp);
                    }
                }

                // add all transition information which is not there.
                for(const auto& rhsPair : rhsTimings) {
                    if(res.getTransitionTimings().find(rhsPair.first) == res.getTransitionTimings().end()) {
                        res.setTransitionTimings(rhsPair.first, rhsPair.second);
                    }
                }
            }
        }

        return res;
    }

} // namespace hypro
