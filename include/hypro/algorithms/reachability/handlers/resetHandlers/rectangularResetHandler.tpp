/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "rectangularResetHandler.h"

namespace hypro {
template <typename State, typename Automaton>
void rectangularResetHandler<State, Automaton>::handle() {
	TRACE( "hypro.worker", "Applying Reset trafo for subspace " << mIndex );
	assert( mState->getSetType( mIndex ) == representation_name::carl_polytope );
	auto res = mState->partialIntervalAssignment( mIntervalResets, mIndex );

	mState->setSetDirect( res.getSet( mIndex ), mIndex );
	mState->setSetType( res.getSetType( mIndex ), mIndex );
}

template <typename State, typename Automaton>
void rectangularResetHandler<State, Automaton>::rectangularIntersectReset( const State& state, const Automaton& automaton ) {
	assert( !state.getTimestamp().isEmpty() );

	// TRACE( "hydra.worker.discrete", "Applying handler " << this->handlerName() );

	for ( auto& location : automaton.getLocations() ) {
		for ( auto& transitionPtr : location->getTransitions() ) {
			if ( state.getLocation() == transitionPtr->getTarget() ) {
				CONTAINMENT containmentResult = CONTAINMENT::BOT;
				State reset( state );
				if ( !transitionPtr->getReset().empty() ) {
					if ( transitionPtr->getReset().getMatrix().size() > 0 ) {
						reset = State{ CarlPolytope<typename State::NumberType>{ transitionPtr->getReset().getMatrix(), transitionPtr->getReset().getVector() } };
					} else {
						for ( size_t i = 0; i < reset.getNumberSets(); i++ ) {
							std::cout << "interval" << std::endl;
							IntervalAssignment<Number> intervalReset = transitionPtr->getReset().getIntervalReset( i );
							reset = reset.partialIntervalAssignment( intervalReset.mIntervals, i );
						}
					}
				}

				auto resultingSet = state.intersect( reset );

				// determine full vs. partial containment
				if ( resultingSet == state ) {
					containmentResult = CONTAINMENT::FULL;
				}

				// reduction
				resultingSet.removeRedundancy();

				// return containment information
				if ( resultingSet.isEmpty() ) {
					containmentResult = CONTAINMENT::NO;
				} else if ( containmentResult != CONTAINMENT::FULL ) {
					containmentResult = CONTAINMENT::PARTIAL;
				} else {
					containmentResult = CONTAINMENT::FULL;
				}

				if ( containmentResult != CONTAINMENT::NO ) {
					mResetSatisfyingStates[transitionPtr.get()].emplace_back( std::move( resultingSet ) );
				}

				mResetContainment[transitionPtr.get()] = containmentResult;
			}
		}
	}
}
}  // namespace hypro
