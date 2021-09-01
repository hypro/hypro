#include "DiscreteWorker.h"

namespace hypro {

template <typename Representation>
template <typename OutputIt>
REACHABILITY_RESULT DiscreteWorker<Representation>::computeTimeSuccessors( const Representation& initialSet, Location<Number> const* loc, OutputIt out, bool checkSafety ) const {
	auto [containment, segment] = intersect( initialSet, loc->getInvariant(), mSubspace );
	//If the first segment did not fulfill the invariant of the location, the jump here should not have been made
	assert( containment != CONTAINMENT::NO );

	// insert segment
	*out = segment;
	++out;

	// intersect with badstates
	if ( checkSafety ) {
		std::tie( containment, std::ignore ) = ltiIntersectBadStates( segment, loc, mHybridAutomaton, mSubspace );
		if ( containment != CONTAINMENT::NO ) {
			return REACHABILITY_RESULT::UNKNOWN;
		}
	}

	return REACHABILITY_RESULT::SAFE;
}

template <typename Representation>
auto DiscreteWorker<Representation>::computeJumpSuccessors( std::vector<Representation> const& flowpipe, Location<Number> const* loc ) const
	  -> std::map<Transition<Number>*, Representation> {
	std::map<Transition<Number>*, Representation> enabledSegments;

	assert( flowpipe.size() <= 1 );
	if ( flowpipe.size() == 0 ) {
		return {};
	}
	// intersect with guard
	for ( const auto& transition : loc->getTransitions() ) {
		auto [containment, intersected] = intersect( flowpipe[0], transition->getGuard(), mSubspace );
		if ( containment != CONTAINMENT::NO ) {
			enabledSegments[transition] = intersected;
		}
	}

	// apply reset and intersect with target invariant
	std::map<Transition<Number>*, Representation> successors;
	for ( const auto& enabled : enabledSegments ) {
		auto [containment, successor] = computeJumpSuccessorsForGuardEnabled( enabled.second, enabled.first );
		if ( containment != CONTAINMENT::NO ) {
			successors[enabled.first] = successor;
		}
	}

	return successors;
}

template <typename Representation>
std::pair<CONTAINMENT, Representation> DiscreteWorker<Representation>::computeJumpSuccessorsForGuardEnabled( const Representation& enabledSet, Transition<Number> const* transition ) const {
	auto successor = applyReset( enabledSet, transition->getReset(), mSubspace );
	return intersect( successor, transition->getTarget()->getInvariant(), mSubspace );
}

}  // namespace hypro
