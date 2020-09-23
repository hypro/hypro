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
template <typename Number>
class StochasticTransition : public Transition<Number> {
  private:
	Number mProbability = 1;
    Number mTransitionWeight;
	Number mTransitionInterval;

  public:
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