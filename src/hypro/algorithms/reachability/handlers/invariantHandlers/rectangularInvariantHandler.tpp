#include "rectangularInvariantHandler.h"

namespace hypro {
template <typename State>
CONTAINMENT rectangularInvariantHandler<State>::operator()( State& stateSet ) {
	assert( !stateSet.getTimestamp().isEmpty() );
	// check if initial Valuation fulfills Invariant
	assert( stateSet.getLocation() != nullptr );
	auto& vpool = hypro::VariablePool::getInstance();
	CONTAINMENT containmentResult = CONTAINMENT::BOT;

	TRACE( "hydra.worker", "Check invariant: " << stateSet.getLocation()->getInvariant() << " for set " << stateSet );

	// create constraints for invariant. Note that we need to properly match dimension indices with variable names at some point.
	// create carlPolytope, as intersection is defined for those
	// TEMPORARY!
	State invariant{CarlPolytope<typename State::NumberType>{stateSet.getLocation()->getInvariant().getMatrix(), stateSet.getLocation()->getInvariant().getVector()}};

	// intersect
	auto resultingSet{stateSet.intersect( invariant )};

	// determine full vs. partial containment
	if ( std::get<CarlPolytope<typename State::NumberType>>( resultingSet ) == std::get<CarlPolytope<typename State::NumberType>>( stateSet.getSet() ) ) {
		containmentResult = CONTAINMENT::FULL;
	}

	// reduction
	resultingSet.removeRedundancy();

	// set result
	stateSet.setSetDirect( resultingSet.getSet() );

	// return containment information
	if ( resultingSet.empty() ) {
		return CONTAINMENT::NO;
	} else if ( containmentResult != CONTAINMENT::FULL ) {
		return CONTAINMENT::PARTIAL;
	} else {
		return containmentResult;
	}
}
}  // namespace hypro
