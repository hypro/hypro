/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "DiscreteWorker.h"

namespace hypro {

template <typename Representation, typename Automaton>
template <typename OutputIt>
REACHABILITY_RESULT DiscreteWorker<Representation, Automaton>::computeTimeSuccessors( const Representation& initialSet, LocationT const* loc, OutputIt out, bool checkSafety ) const {
	auto [containment, segment] = intersect( initialSet, loc->getInvariant(), mSubspace );
	// If the first segment did not fulfill the invariant of the location, the jump here should not have been made
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

template <typename Representation, typename Automaton>
auto DiscreteWorker<Representation, Automaton>::computeJumpSuccessors( std::vector<Representation> const& flowpipe, LocationT const* loc ) const
	  -> std::map<Transition<LocationT>*, Representation> {
	std::map<Transition<LocationT>*, Representation> enabledSegments;

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
	std::map<Transition<LocationT>*, Representation> successors;
	for ( const auto& enabled : enabledSegments ) {
		auto [containment, successor] = computeJumpSuccessorsForGuardEnabled( enabled.second, enabled.first );
		if ( containment != CONTAINMENT::NO ) {
			successors[enabled.first] = successor;
		}
	}

	return successors;
}

template <typename Representation, typename Automaton>
std::pair<CONTAINMENT, Representation> DiscreteWorker<Representation, Automaton>::computeJumpSuccessorsForGuardEnabled( const Representation& enabledSet, Transition<LocationT> const* transition ) const {
	auto successor = applyReset( enabledSet, transition->getReset(), mSubspace );
	return intersect( successor, transition->getTarget()->getInvariant(), mSubspace );
}

}  // namespace hypro
