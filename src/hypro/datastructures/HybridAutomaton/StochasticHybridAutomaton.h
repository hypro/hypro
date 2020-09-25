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
template <typename Number>
class StochasticHybridAutomaton : public HybridAutomaton<Number> {
  public:
	using stochasticInitialMap = std::map<const StochasticLocation<Number>*, std::pair< Condition<Number>, Number>>;

  private:
	// Number mProbability = 1;
	stochasticInitialMap mProbInitialStates;

  public:

	void setProbInitialStates( const stochasticInitialMap probInitialStates ) {
		mProbInitialStates = probInitialStates;
	}
    void addProbInitialState( const StochasticLocation<Number>* loc, const Condition<Number>& state, Number prob ) { 
        mProbInitialStates.emplace( std::make_pair( loc, std::make_pair( state , prob ) ) ); 
    }
	const stochasticInitialMap& getProbInitialState() const {
		return mProbInitialStates;
	}
};

}  // namespace hypro