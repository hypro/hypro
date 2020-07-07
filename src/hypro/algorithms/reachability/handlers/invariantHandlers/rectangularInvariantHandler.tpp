#include "rectangularInvariantHandler.h"

namespace hypro {
template <typename State>
std::pair<CONTAINMENT, State> rectangularIntersectInvariant( const State& stateSet ) {
	// check if initial Valuation fulfills Invariant
	assert( stateSet.getLocation() != nullptr );
	CONTAINMENT containmentResult = CONTAINMENT::BOT;

	TRACE( "hydra.worker", "Check invariant: " << stateSet.getLocation()->getInvariant() << " for set " << stateSet );

	// create constraints for invariant. Note that we need to properly match dimension indices with variable names at some point.
	// create carlPolytope, as intersection is defined for those
	// TEMPORARY!
	State invariant{ CarlPolytope<typename State::NumberType>{ stateSet.getLocation()->getInvariant().getMatrix(), stateSet.getLocation()->getInvariant().getVector() } };

	// intersect
	auto resultingSet = stateSet.intersect( invariant );

	// determine full vs. partial containment
	if ( resultingSet == stateSet ) {
		containmentResult = CONTAINMENT::FULL;
	}

	// reduction
	resultingSet.removeRedundancy();

	// return containment information
	if ( resultingSet.isEmpty() ) {
		return std::make_pair( CONTAINMENT::NO, resultingSet );
	} else if ( containmentResult != CONTAINMENT::FULL ) {
		return std::make_pair( CONTAINMENT::PARTIAL, resultingSet );
	} else {
		return std::make_pair( CONTAINMENT::FULL, resultingSet );
	}
}

}  // namespace hypro
