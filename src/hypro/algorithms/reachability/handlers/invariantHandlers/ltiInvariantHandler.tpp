#include "ltiInvariantHandler.h"

namespace hypro {
template <typename State>
std::pair<CONTAINMENT, State> ltiIntersectInvariant( const State& stateSet ) {
	assert( !stateSet.getTimestamp().isEmpty() );
	// check if initial Valuation fulfills Invariant
	assert( stateSet.getLocation() != nullptr );

	TRACE( "hydra.worker", "Check invariant: " << stateSet.getLocation()->getInvariant() << " for set " << stateSet );
	return stateSet.partiallySatisfies( stateSet.getLocation()->getInvariant(), 0 );
}
}  // namespace hypro