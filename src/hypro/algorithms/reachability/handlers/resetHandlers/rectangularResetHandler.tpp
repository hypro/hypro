#include "rectangularResetHandler.h"

namespace hypro {
template <typename State>
void rectangularResetHandler<State>::handle() {
	TRACE( "hypro.worker", "Applying Reset trafo for subspace " << mIndex );
	assert( mState->getSetType( mIndex ) == representation_name::carl_polytope );
	auto res = mState->partialIntervalAssignment( mIntervalResets, mIndex );

	mState->setSetDirect( res.getSet( mIndex ), mIndex );
	mState->setSetType( res.getSetType( mIndex ), mIndex );
}

template <typename State>
void rectangularResetHandler<State>::rectangularIntersectReset( const State& state, const HybridAutomaton<Number>& automaton ) {
	assert( !state.getTimestamp().isEmpty() );

	// TRACE( "hydra.worker.discrete", "Applying handler " << this->handlerName() );

	for ( auto& location : automaton.getLocations() ) {
		for ( auto& transitionPtr : location->getTransitions() ) {
			if ( state.getLocation() == transitionPtr->getTarget()) {
				CONTAINMENT containmentResult = CONTAINMENT::BOT;
				State reset(state);
				if ( !transitionPtr->getReset().empty() ){
					if ( transitionPtr->getReset().getMatrix().size() > 0 ) {
						std::cout << "affine is  " << std::endl;
						reset = State{ CarlPolytope<typename State::NumberType>{ transitionPtr->getReset().getMatrix(), transitionPtr->getReset().getVector() } };
					} else {
						for ( size_t i = 0; i < reset.getNumberSets(); i++ ) {
							std::cout << "interval" << std::endl;
							IntervalAssignment<Number> intervalReset = transitionPtr->getReset().getIntervalReset( i );
							reset = reset.partialIntervalAssignment( intervalReset.mIntervals, i );
						}
					}
				}

				std::cout << "reset is " << reset <<std::endl;
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

				std::cout << "find transition reset result: " << containmentResult << std::endl;
				std::cout << resultingSet << std::endl;
				mResetContainment[transitionPtr.get()] = containmentResult;
			}
		}
	}
}
}  // namespace hypro
