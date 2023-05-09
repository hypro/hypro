/*
 * Copyright (c) 2023-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../../../datastructures/reachability/timing/EventTimingContainer.h"
#include "../../../../datastructures/reachability/timing/EventTimingProvider.h"

namespace hypro {

    template<typename Number, typename State>
    inline bool
    updateTiming(typename EventTimingContainer<Number>::Node_t current, carl::Interval <tNumber> entryTimestamp,
                 Transition<Number> *transition, StrategyNode<State> currentStratNode, bool insert) {
        bool skip = false;
        for (auto tChild: current->getChildren()) {
            if (tChild->getLocation() == transition->getTarget() && tChild->getEntryTransition() == transition &&
                set_has_intersection(tChild->getEntryTimestamp(), entryTimestamp)) {
                // in case no aggregation happened, the timing node should cover all separate branches in one, i.e. we unify the entry time
                // stamps. Otherwise we can use regular refinement by intersection (2nd case).
                if ((currentStratNode.aggregation == AGG_SETTING::NO_AGG && currentStratNode.clustering == -1) ||
                    (currentStratNode.aggregation == AGG_SETTING::MODEL &&
                     transition->getAggregation() == AGG_SETTING::NO_AGG)) {
                    tChild->setEntryTimestamp(set_intersection(entryTimestamp, tChild->getEntryTimestamp()));
                } else {
                    tChild->setEntryTimestamp(set_convexHull(entryTimestamp, tChild->getEntryTimestamp()));
                }
                skip = true;
                break;
            }
        }

        if (!skip && insert) {
            typename EventTimingContainer<Number>::Node_t newChild = EventTimingProvider<Number>::getInstance().addChildToNode(
                    current, SettingsProvider<State>::getInstance().getReachabilitySettings().timeBound *
                             SettingsProvider<State>::getInstance().getReachabilitySettings().jumpDepth);
            newChild->setLocation(transition->getTarget());
            newChild->setEntryTransition(transition);
            newChild->setEntryTimestamp(entryTimestamp);
        }

        return skip;
    }

}  // namespace hypro
