#include "ltiInvariantHandler.h"

namespace hypro {
template <typename State>
void ltiInvariantHandler<State>::handle() {
	assert( !mState->getTimestamp().isEmpty() );
	// check if initial Valuation fulfills Invariant
	assert( mState->getLocation() != nullptr );

	TRACE( "hydra.worker", "Check invariant: " << mState->getLocation()->getInvariant() << " for set " << mState );
	std::pair<CONTAINMENT, State> invariantSatisfyingPair = mState->partiallySatisfies( mState->getLocation()->getInvariant(), mIndex );
	//std::cout << "ltiInvariantHandler::handle(), Check invariant: \n" << mState->getLocation()->getInvariant() << " for set \n";
	//for(auto & v : mState->vertices()){
	//	std::cout << v << std::endl;
	//}
	//std::cout << "ltiInvariantHandler::handle(), invariantSatisfyingPair: " << invariantSatisfyingPair.first << " satisfying set: \n";
	//for(auto & v : invariantSatisfyingPair.second.vertices()){
	//	std::cout << v << std::endl;
	//}
	if ( invariantSatisfyingPair.first != CONTAINMENT::NO ) {
		mContainment = invariantSatisfyingPair.first;
		mState->setSet( invariantSatisfyingPair.second.getSet( mIndex ), mIndex );
		return;
	}  // if set does not satisfy the invariant, return false
	else {
		mContainment = CONTAINMENT::NO;
		return;
	}
}

template <typename State>
std::pair<CONTAINMENT, State> ltiInvariantHandler<State>::ltiIntersectInvariant( const State& stateSet ) {
	assert( !stateSet.getTimestamp().isEmpty() );
	// check if initial Valuation fulfills Invariant
	assert( stateSet.getLocation() != nullptr );

	TRACE( "hydra.worker", "Check invariant: " << stateSet.getLocation()->getInvariant() << " for set " << stateSet );
	return stateSet.partiallySatisfies( stateSet.getLocation()->getInvariant(), 0 );
}
}  // namespace hypro