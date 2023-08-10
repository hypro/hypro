/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Class that describes a transition of a stochastic hybrid automaton.
 */

#pragma once

#include "Transition.h"

namespace hypro {

/**
 * @brief      Class for a transition in a stochastic automaton.
 * @tparam     Number  The used number type.
 */
    template<typename LocationType>
    class StochasticTransition : public Transition<LocationType> {
        using Number = typename LocationType::NumberType;

    private:
        Number mProbability = 1;
        Number mTransitionWeight;
        carl::Interval<Number> mTransitionInterval;

    public:
        //   StochasticTransition()
        // 		: Transition<Number>()
        // 		, mProbability()
        // 		, mTransitionWeight()
        // 		, mTransitionInterval() {}

        // StochasticTransition( const StochasticTransition<Number>& orig )
        // 		: Transition<Number>( orig )
        // 		, mProbability()
        // 		, mTransitionWeight()
        // 		, mTransitionInterval() {}

        //   StochasticTransition( StochasticLocation<Number>* source, StochasticLocation<Number>* target )
        // 		: Transition<Number>( source, target )
        // 		, mProbability()
        // 		, mTransitionWeight()
        // 		, mTransitionInterval() {}

        // 	StochasticTransition( StochasticLocation<Number>* source, StochasticLocation<Number>* target, const Condition<Number>& guard, const Reset<Number>& reset )
        // 		: Transition<Number>( source, target, guard, reset )
        // 		, mProbability()
        // 		, mTransitionWeight()
        // 		, mTransitionInterval() {}

        void setProbability(Number probability) {
            mProbability = probability;
        }

        Number getProbability() {
            return mProbability;
        }

        void setTransitionWeight(Number weight) {
            mTransitionWeight = weight;
        }

        Number getTransitionWeight() {
            return mTransitionWeight;
        }

        void setTransitionInterval(Number interval) {
            mTransitionInterval = interval;
        }

        Number getTransitionInterval() {
            return mTransitionInterval;
        }
    };

}  // namespace hypro
