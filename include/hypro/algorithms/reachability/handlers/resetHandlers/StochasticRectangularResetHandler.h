/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../IHandler.h"

namespace hypro {
    template<typename State>
    class StochasticRectangularResetHandler : public IResetHandler {
        using Number = typename State::NumberType;
        using TransitionStatesMap = typename std::map<StochasticTransition < Number> *, std::vector<State>>;
        using TransitionContainmentMap = std::map<const StochasticTransition <Number> *, CONTAINMENT>;

    protected:
        State *mState;    // A state containing the first segment for each subspace
        std::vector<carl::Interval < Number>> mIntervalResets;
        TransitionStatesMap mResetSatisfyingStates;
        TransitionContainmentMap mResetContainment;

        size_t mIndex;

    public:
        void handle();

        const char *handlerName() { return "rectangularResetHandler"; }

        void rectangularIntersectReset(const State &stateSet, const HybridAutomaton<Number> &automaton);

        const TransitionStatesMap &getResetSatisfyingStateSets() const { return mResetSatisfyingStates; }

        const TransitionContainmentMap &getResetContainment() const { return mResetContainment; }
    };
}  // namespace hypro

#include "StochasticRectangularResetHandler.tpp"
