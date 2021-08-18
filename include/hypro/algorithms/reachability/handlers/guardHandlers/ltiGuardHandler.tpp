#include "ltiGuardHandler.h"

namespace hypro {
template <typename State>
bool ltiGuardHandler<State>::operator()( const State& stateSet ) {
	bool haveSatisfiedGuard = false;
	assert( !stateSet.getTimestamp().isEmpty() );

	for ( auto const& transitionPtr : stateSet.getLocation()->getTransitions() ) {
		auto [contained, state] = stateSet.partiallySatisfies( transitionPtr->getGuard(), 0 );
		assert( contained != CONTAINMENT::BOT );
		if ( contained != CONTAINMENT::NO ) {
			mGuardSatisfyingStates[transitionPtr.get()].emplace_back( std::move( state ) );
			haveSatisfiedGuard = true;
		}
	}
	return haveSatisfiedGuard;
}

}  // namespace hypro