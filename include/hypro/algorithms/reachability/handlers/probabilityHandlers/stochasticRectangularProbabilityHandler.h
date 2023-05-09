/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <flags.h>

#ifdef HYPRO_GSL_INTEGRATION
#include <gsl/gsl_math.h>
// #include <gsl/gsl_monte.h>
#include <gsl/gsl_monte_miser.h>
#include <gsl/gsl_monte_plain.h>
#include <gsl/gsl_monte_vegas.h>
#include <stdlib.h>

namespace hypro {
template <typename State, typename Number>
class stochasticRectangularProbabilityHandler {
    using IntervalTransitionMap = std::map<carl::Interval<Number>, std::vector<StochasticTransition<Number>*>>;
    using IntervalTransitionMaps = std::map<carl::Interval<Number>*, std::vector<StochasticTransition<Number>*>>;

  public:
    void calculateProbability( const State& preStateSet, StochasticTransition<Number>* transitionPtr, Number prob, const StochasticHybridAutomaton<typename State::NumberType>& automaton );
    carl::Interval<Number> timeInterval( const State& preStateSet, State& state, const rectangularFlow<Number>& flow, StochasticTransition<Number>* transitionPtr, bool isToTargetState );
    void intervalCalculation( const State& preStateSet, State& stateSet, StochasticTransition<Number>* transitionPtr );
    carl::Interval<Number> intervalIntersect( carl::Interval<Number> lhs, carl::Interval<Number> rhs );
    void calculateDisjointIntervals();
    std::vector<carl::Interval<Number>> calculateComplement( carl::Interval<Number> lhs, carl::Interval<Number> rhs );
    IntervalTransitionMap getEnabledTransitions() { return mEnabledTransitions; }
    Number gslIntegration( DistributionType type, Number intervalVolume, Number expLambda, carl::Interval<Number> interval );
    static Number computeUniformedIntergration( Number* k, size_t dim, void* params );
    static Number computeExponentialIntergration( Number* k, size_t dim, void* params );
    static Number computeNormalIntergration( Number* k, size_t dim, void* params );
    static Number computeIntergration( Number* k, size_t dim, void* params );
    std::vector<carl::Interval<Number>> getDisjInterval() { return mDisjIntervals; }
    std::vector<std::vector<StochasticTransition<Number>*>> getDisjTransitionSets() { return mDisjTransitionSets; }
    std::vector<carl::Interval<Number>> getStateInterval() { return mStateInterval; }
    Number getProbability() { return mProbability; }

  protected:
    std::vector<carl::Interval<Number>> mStateInterval;
    carl::Interval<Number> mTargetInterval;
    IntervalTransitionMap mEnabledTransitions;
    std::vector<carl::Interval<Number>> mIntervals;
    std::vector<std::vector<StochasticTransition<Number>*>> mTransitionSets;
    std::vector<carl::Interval<Number>> mDisjIntervals;
    std::vector<std::vector<StochasticTransition<Number>*>> mDisjTransitionSets;
    Number mUniformedRef;
    Number mExpLambda;
    Number mNormalSigma;
    Number mNormalMu;
    Number mProbability;
};

template <typename Number>
struct distributionParams {
    Number uniformedLower;
    Number uniformedUpper;
    Number expLambda;
    Number normalSigma;
    Number normalMu;
};
}  // namespace hypro

#endif

#include "stochasticRectangularProbabilityHandler.tpp"
