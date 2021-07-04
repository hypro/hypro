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

	  void calculateProbability(  const State& preStateSet, StochasticTransition<Number>* transitionPtr, Number prob,  const StochasticHybridAutomaton<typename State::NumberType>& automaton  );
    carl::Interval<Number> timeInterval( const State& preStateSet, State& state, const rectangularFlow<Number>& flow, StochasticTransition<Number>* transitionPtr, bool isToTargetState );
    void intervalCalculation( const State& preStateSet, State& stateSet, StochasticTransition<Number>* transitionPtr );
    carl::Interval<Number> intervalIntersect(carl::Interval<Number> lhs, carl::Interval<Number> rhs);
    void calculateDisjointIntervals();
    std::vector<carl::Interval<Number>> calculateComplement(carl::Interval<Number> lhs, carl::Interval<Number> rhs);
    IntervalTransitionMap getEnabledTransitions() { return mEnabledTransitions; }
    Number gslIntegration( DistributionType type, Number intervalVolume, Number expLambda, carl::Interval<Number> interval );
    static Number computeUniformedIntergration( Number* k, size_t dim, void* params);
    static Number computeExponentialIntergration( Number* k, size_t dim, void* params);
    static Number computeNormalIntergration( Number* k, size_t dim, void* params);
    static Number computeIntergration( Number* k, size_t dim, void* params);
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
struct distributionParams { Number uniformedLower;
                            Number uniformedUpper;
                            Number expLambda;
                            Number normalSigma;
                            Number normalMu; };
}  // namespace hypro

#endif
#include "stochasticRectangularProbabilityHandler.tpp"