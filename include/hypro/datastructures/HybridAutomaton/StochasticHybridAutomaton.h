/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Class that describes a stochastic hybrid automaton.
 */

#pragma once

#include "HybridAutomaton.h"

namespace hypro {

/**
 * @brief      Class for a stochastic automaton.
 * @tparam     Number  The used number type.
 */
    template<typename Number>
    class StochasticHybridAutomaton : public HybridAutomaton<Number> {
    public:
        using stochasticInitialMap = std::map<const StochasticLocation<Number> *, std::pair<Condition<Number>, Number> >;

        StochasticHybridAutomaton()
                : HybridAutomaton<Number>(), mProbInitialStates() {}

        StochasticHybridAutomaton(const StochasticHybridAutomaton<Number> &hybrid)
                : HybridAutomaton<Number>(hybrid) {
            for (auto probInit: hybrid.getProbInitialState()) {
                for (auto l: this->getLocations()) {
                    if (probInit.first->hash() == l->hash()) {
                        StochasticLocation<Number> *stoLoc = dynamic_cast<StochasticLocation<Number> *>( l );
                        this->addProbInitialState(stoLoc, probInit.second.first, probInit.second.second);
                    }
                }
            }
        }

    private:
        // Number mProbability = 1;
        stochasticInitialMap mProbInitialStates;

    public:
        void setProbInitialStates(const stochasticInitialMap probInitialStates) {
            mProbInitialStates = probInitialStates;
        }

        void addProbInitialState(const StochasticLocation<Number> *loc, const Condition<Number> &state, Number prob) {
            mProbInitialStates.emplace(std::make_pair(loc, std::make_pair(state, prob)));
        }

        const stochasticInitialMap &getProbInitialState() const {
            return mProbInitialStates;
        }
    };

}  // namespace hypro
