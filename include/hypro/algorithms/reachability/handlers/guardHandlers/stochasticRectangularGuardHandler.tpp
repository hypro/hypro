/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "stochasticRectangularGuardHandler.h"

namespace hypro {
    template<typename State>
    void stochasticRectangularGuardHandler<State>::operator()(const State &state) {
        assert(!state.getTimestamp().isEmpty());

        // TRACE( "hydra.worker.discrete", "Applying handler " << this->handlerName() );

        for (auto &transitionPtr: state.getLocation()->getTransitions()) {
            CONTAINMENT containmentResult = CONTAINMENT::BOT;
            State guard(state);
            if (!transitionPtr->getGuard().empty()) {
                guard = State{CarlPolytope < typename State::NumberType >
                              {transitionPtr->getGuard().getMatrix(), transitionPtr->getGuard().getVector()}};
            }

            // intersect
            auto resultingSet = state.intersect(guard);

            // determine full vs. partial containment
            if (resultingSet == state) {
                containmentResult = CONTAINMENT::FULL;
            }

            // reduction
            resultingSet.removeRedundancy();

            // return containment information
            if (resultingSet.isEmpty()) {
                containmentResult = CONTAINMENT::NO;
            } else if (containmentResult != CONTAINMENT::FULL) {
                containmentResult = CONTAINMENT::PARTIAL;
            } else {
                containmentResult = CONTAINMENT::FULL;
            }

            StochasticTransition <Number> *stoTrans = dynamic_cast<StochasticTransition <Number> *>( transitionPtr.get());
            // if ( !stoTrans ) {
            // 	std::cout << "here is normal tran" << std::endl;
            // } else {
            // 	std::cout << "here is sto tran" << std::endl;
            // }
            if (containmentResult != CONTAINMENT::NO) {
                mGuardSatisfyingStates[stoTrans].emplace_back(std::move(resultingSet));
            }
            mGuardContainment[stoTrans] = containmentResult;
        }
    }

}  // namespace hypro
