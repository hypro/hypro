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
	using stochasticInitialMap = std::map< const locationConditionMap, Number>;

  private:
	// Number mProbability = 1;
	stochasticInitialMap mProbInitialStates;

  public:

	void setProbInitialStates( const stochasticInitialMap probInitialStates ) {
		mProbInitialStates = probInitialStates;
	}
    void addProbInitialState( const StochasticLocation<Number>* loc, const Condition<Number>& state, Number prob ) { 
        mInitialStates.emplace( std::make_pair( std::make_pair( loc, state ), prob ) ); 
    }
	const matrix_t<Number>& getProbInitialState() const {
		return mProbInitialStates;
	}
};

}  // namespace hypro