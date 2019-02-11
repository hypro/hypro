#pragma once
#include "HierarchicalIntervalVector.h"

namespace hypro {

    template<typename T, typename N>
    static HierarchicalIntervalVector<T,N> merge(std::initializer_list<HierarchicalIntervalVector<T,N>> l) {
        assert(l.size() != 0);
        auto lIt = l.begin();
        HierarchicalIntervalVector<T,N> res = *lIt++;
        for(;lIt != l.end(); ++lIt) {
            N prevTimepoint = N(0);
            for(auto& endPoint : *lIt.getIntervals()) {
                res.insertInterval(endPoint.type, carl::Interval<N>(prevTimepoint, endPoint.timePoint));
                prevTimepoint = endPoint.timePoint;
            }
        }
        return res;
    }

} // namespace
