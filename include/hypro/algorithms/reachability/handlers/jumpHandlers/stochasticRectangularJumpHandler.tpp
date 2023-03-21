/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "stochasticRectangularJumpHandler.h"

namespace hypro {

template <typename State>
auto stochasticRectangularJumpHandler<State>::applyJump( const TransitionStateMap& states, StochasticTransition<Number>* transition, const AnalysisParameters& strategy ) -> TransitionStateMap {
	// holds a mapping of transitions to states which need to be aggregated
	TransitionStateMap toAggregate;
	// holds a mapping of transitions to states which are ready to apply the reset function and the intersection with the invariant
	TransitionStateMap toProcess;
	// holds a mapping of transitions to already processed (i.e. aggregated, resetted and reduced) states
	TransitionStateMap processedStates;
	for ( const auto& [transitionPtr, statesVec] : states ) {
		// only handle sets related to the passed transition, in case any is passed.
		if ( transition == nullptr || transitionPtr == transition ) {
			// check aggregation settings

			if ( ( strategy.aggregation == AGG_SETTING::NO_AGG && strategy.clustering == -1 ) ||
				 ( strategy.aggregation == AGG_SETTING::MODEL && transitionPtr->getAggregation() == AGG_SETTING::NO_AGG ) ) {
				// just copy the states to the toProcess map.

				auto& targetVec = toProcess[transitionPtr];
				targetVec.insert( targetVec.end(), statesVec.begin(), statesVec.end() );
			} else {  // store for aggregation
				auto& targetVec = toAggregate[transitionPtr];
				targetVec.insert( targetVec.end(), statesVec.begin(), statesVec.end() );
			}
		}
	}

	// aggregate all sets marked for aggregation
	// aggregate( toProcess, toAggregate, strategy );

	DEBUG( "hydra.worker", "Apply jump on " << toProcess.size() << " transitions." );

	for ( const auto& [transitionPtr, statesVec] : toProcess ) {
		DEBUG( "hydra.worker", "Apply jump on " << statesVec.size() << " states." );
		for ( const auto& state : statesVec ) {
			// copy state - as there is no aggregation, the containing set and timestamp is already valid
			// TODO: Why copy?

			// std::cout<<"before apply: " << &state <<", " << state.getLocation() << std::endl;
			assert( !state.getTimestamp().isEmpty() );
			State newState( state );
			// std::cout << "new state set: " << newState << std::endl;

			// apply reset function
			applyReset( newState, transitionPtr );
			newState.removeRedundancy();
			// std::cout << "new state set after reset: " << newState << std::endl;

			// set target location in state set
			newState.setLocation( transitionPtr->getTarget() );

			// check invariant in new location
			auto [containment, stateSet] = rectangularIntersectInvariant( newState );
			if ( containment == CONTAINMENT::NO ) {
				continue;
			}

			// reduce if possible (Currently only for support functions)
			stateSet.reduceRepresentation();

			DEBUG( "hydra.worker.discrete", "State after reduction: " << stateSet );

			// Note: Here we misuse the state's timestamp to carry the transition timing to the next stage -> just don't reset
			// the timestamp in case no aggregation happens.

			if ( processedStates.find( transitionPtr ) == processedStates.end() ) {
				processedStates[transitionPtr] = std::vector<State>();
			}
			processedStates[transitionPtr].emplace_back( stateSet );
			// std::cout<<"after apply: " <<&stateSet <<", " << stateSet.getLocation() << std::endl;

			// std::cout << "new state set add to processed: " << stateSet << std::endl;

			mPredecessor.emplace_back( std::make_pair( stateSet, state ) );
			// if (state == stateSet) {
			// 	std::cout << "operator == is true!" <<std::endl;
			// }
		}
	}
	return processedStates;
}

template <typename State>
void stochasticRectangularJumpHandler<State>::applyReset( State& state, StochasticTransition<Number>* transitionPtr ) const {
	if ( !transitionPtr->getReset().empty() ) {
		if ( transitionPtr->getReset().getMatrix().size() > 0 ) {
			state = State{ CarlPolytope<typename State::NumberType>{ transitionPtr->getReset().getMatrix(), transitionPtr->getReset().getVector() } };
		} else if ( !transitionPtr->getReset().getIntervalResets().empty() ) {
			std::cout << "interval reset not empty" << std::endl;
			for ( size_t i = 0; i < state.getNumberSets(); i++ ) {
				IntervalAssignment<Number> intervalReset = transitionPtr->getReset().getIntervalReset( i );
				state = state.partialIntervalAssignment( intervalReset.mIntervals, i );
			}
		}
	}
}

template <typename State>
State stochasticRectangularJumpHandler<State>::applyReverseJump( State& state, StochasticTransition<Number>* transitionPtr, const AnalysisParameters& strategy ) {
	assert( !state.getTimestamp().isEmpty() );
	State newState( state );

	// apply guard function
	applyGuard( newState, transitionPtr );

	// set target location in state set
	newState.setLocation( transitionPtr->getSource() );

	// check invariant in new location
	auto [containment, stateSet] = rectangularIntersectInvariant( newState );
	// if ( containment == CONTAINMENT::NO ) {
	// 	continue;
	// }

	// reduce if possible (Currently only for support functions)
	stateSet.reduceRepresentation();

	DEBUG( "hydra.worker.discrete", "State after reduction: " << stateSet );

	return stateSet;
}

template <typename State>
void stochasticRectangularJumpHandler<State>::applyGuard( State& state, StochasticTransition<Number>* transitionPtr ) const {
	if ( !transitionPtr->getGuard().empty() ) {
		// std::cout << "guard is not empty" << std::endl;
		state.setSet( typename State::template nth_representation<0>{ transitionPtr->getGuard().getMatrix(), transitionPtr->getGuard().getVector() } );
	}
}
}  // namespace hypro
