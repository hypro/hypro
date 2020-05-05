#include "ltiGuardHandler.h"

namespace hypro {
template <typename State>
bool ltiGuardHandler<State>::operator()( const State& stateSet ) {
	bool haveSatisfiedGuard = false;
	assert( !stateSet.getTimestamp().isEmpty() );

	for ( auto transitionPtr : stateSet.getLocation()->getTransitions() ) {
		std::pair<CONTAINMENT, State> statePair = stateSet.partiallySatisfies( transitionPtr->getGuard(), 0 );
		assert( statePair.first != CONTAINMENT::BOT );
		if ( statePair.first != CONTAINMENT::NO ) {
			if ( std::find( transitionPtr, mGuardSatisfyingStates.begin(), mGuardSatisfyingStates.end() ) == mGuardSatisfyingStates.end() ) {
				mGuardSatisfyingStates[transitionPtr] = std::vector<State>();
			}
			mGuardSatisfyingStates[transitionPtr].emplace_back( std::move( statePair.second ) );
			haveSatisfiedGuard = true;
		}
	}
	return haveSatisfiedGuard;
}

}  // namespace hypro