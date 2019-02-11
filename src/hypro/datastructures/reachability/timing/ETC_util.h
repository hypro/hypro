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
            for(const auto& transitionTimingPair : *lIt.getTransitionTimings()) {
                if(!res.hasTransition(transitionTimingPair.first)) {
                    res.setTransitionTimings(transitionTimingPair.first, transitionTimingPair.second);
                } else {
                    auto tmp = res.getTransitionTimings(transitionTimingPair.first);
                    tmp = merge({tmp,transitionTimingPair.second});

                    res.setTransitionTimings(transitionTimingPair.first, tmp);
                }
            }
            res.setInvariantTimings( merge({res.getInvariantTimings(), *lIt.getInvariantTimings()}) );
            res.setBadStateTimings( merge({res.getBadStateTimings(), *lIt.getBadStateTimings()}) );
        }
        return res;
    }

} // namespace hypro
