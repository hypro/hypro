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

	StochasticHybridAutomaton() 
		: HybridAutomaton<Number>()
		, mProbInitialStates() {}
	StochasticHybridAutomaton( const StochasticHybridAutomaton<Number>& hybrid )
		: HybridAutomaton<Number>( hybrid ) {
			for(auto probInit : hybrid.getProbInitialState() ) {
				for(auto l : this->getLocations() ){
					if(probInit.first->hash() == l->hash()){
						StochasticLocation<Number>* stoLoc = dynamic_cast<StochasticLocation<Number>*>( l );
						this->addProbInitialState(stoLoc,probInit.second.first,probInit.second.second);
					}
				}
			}
		}

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