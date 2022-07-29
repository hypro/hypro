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
template <typename Number, typename LocationType>
class StochasticTransition : public Transition<Number, LocationType> {
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

	void setProbability( Number probability ) {
		mProbability = probability;
	}
	Number getProbability() {
		return mProbability;
	}

	void setTransitionWeight( Number weight ) {
		mTransitionWeight = weight;
	}
	Number getTransitionWeight() {
		return mTransitionWeight;
	}

	void setTransitionInterval( Number interval ) {
		mTransitionInterval = interval;
	}
	Number getTransitionInterval() {
		return mTransitionInterval;
	}
};

}  // namespace hypro