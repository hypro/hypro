/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "RectangularWorker.h"

namespace hypro {

template <typename State, typename Automaton>
REACHABILITY_RESULT
RectangularSyncWorker<State, Automaton>::computeForwardReachability( ReachTreeNode<State, LocationT> &task ) {
	DEBUG( "hypro.reachability.rectangular", "Start forward computation in worker" );
	if ( computeTimeSuccessors( task ) == REACHABILITY_RESULT::UNKNOWN ) {
		return REACHABILITY_RESULT::UNKNOWN;
	}
	computeJumpSuccessors( task.getLocation() );
	return REACHABILITY_RESULT::SAFE;
}

template <typename State, typename Automaton>
REACHABILITY_RESULT
RectangularSyncWorker<State, Automaton>::computeTimeSuccessors( ReachTreeNode<State, LocationT> &task ) {
	State initialSet = task.getInitialSet();

	auto [containment, segment] = rectangularIntersectInvariant( initialSet, task.getLocation() );
	if ( containment == CONTAINMENT::NO ) {
		DEBUG( "hypro.reachability.rectangular", "Initial set not contained in the invariant" );
		return REACHABILITY_RESULT::SAFE;
	}

	std::tie( containment, segment ) = rectangularIntersectBadStates( segment, task.getLocation(), mHybridAutomaton );
	if ( containment != CONTAINMENT::NO ) {
		// Todo: memorize the intersecting state set and keep state.
		DEBUG( "hypro.reachability.rectangular", "Initial set intersects bad states, abort" );
		// add state to flowpipe
		mFlowpipe.addState( segment );
		task.getFlowpipe().push_back( segment );
		return REACHABILITY_RESULT::UNKNOWN;
	}

	// compute time successor states
	State timeSuccessors{ segment };
	if ( mSettings.fixedParameters().localTimeHorizon < 0 ) {
		timeSuccessors = std::move(
			  rectangularApplyTimeEvolution( segment, task.getLocation()->getRectangularFlow() ) );
	} else {
		timeSuccessors = std::move(
			  rectangularApplyBoundedTimeEvolution( segment, task.getLocation()->getRectangularFlow(),
													mSettings.fixedParameters().localTimeHorizon ) );
	}

	TRACE( "hypro.reachability.rectangular", "Time successors: " << timeSuccessors );
	auto [invariantContainment, constrainedTimeSuccessors] = rectangularIntersectInvariant( timeSuccessors,
																							task.getLocation() );
	TRACE( "hypro.reachability.rectangular",
		   "Time successors constrained by invariants: " << constrainedTimeSuccessors );
	if ( invariantContainment == CONTAINMENT::NO ) {
		DEBUG( "hypro.reachability.rectangular",
			   "Time successors are not contained in the invariant, return SAFE (This should never happen)" );
		assert( false &&
				"It cannot happen that time successors, which include the initial set completely invalidate the invariant region, if the initial set is at least partially contained in the invariant region." );
		// add state to flowpipe
		mFlowpipe.addState( constrainedTimeSuccessors );
		task.getFlowpipe().push_back( constrainedTimeSuccessors );
		return REACHABILITY_RESULT::SAFE;
	}

	// add state to flowpipe
	mFlowpipe.addState( constrainedTimeSuccessors );
	task.getFlowpipe().push_back( constrainedTimeSuccessors );

	std::tie( containment, segment ) = rectangularIntersectBadStates( constrainedTimeSuccessors, task.getLocation(),
																	  mHybridAutomaton );
	if ( containment != CONTAINMENT::NO ) {
		// Todo: memorize the intersecting state set and keep state.
		DEBUG( "hypro.reachability.rectangular", "Time successors intersect bad states, abort" );
		return REACHABILITY_RESULT::UNKNOWN;
	}

	return REACHABILITY_RESULT::SAFE;
}

template <typename State, typename Automaton>
void RectangularSyncWorker<State, Automaton>::computeJumpSuccessors( const LocationT *location ) {
	// for each transition intersect each computed time successor set with the guard. If the intersection is non-empty, store for post-processing.
	rectangularGuardHandler<State, LocationT> guardHandler;
	for ( auto &state : mFlowpipe ) {
		guardHandler( state, location );
	}

	// post processing: apply reset on those sets, intersect the sets with the invariant of the target location. If the resulting state set is non-empty, add it to the jump successors set.
	postProcessJumpSuccessors( guardHandler.getGuardSatisfyingStateSets() );
}

template <typename State, typename Automaton>
void RectangularSyncWorker<State, Automaton>::postProcessJumpSuccessors( const JumpSuccessors &guardSatisfyingSets ) {
	singularJumpHandler<State, LocationT> jmpHandler;
	mJumpSuccessorSets = jmpHandler.applyJump( guardSatisfyingSets );
}

template <typename State, typename Automaton>
REACHABILITY_RESULT
RectangularSyncWorker<State, Automaton>::computeBackwardReachability( ReachTreeNode<State, LocationT> &task ) {
	if ( computeTimePredecessors( task ) == REACHABILITY_RESULT::UNKNOWN ) {
		return REACHABILITY_RESULT::UNKNOWN;
	}
	computeJumpPredecessors();
	return REACHABILITY_RESULT::SAFE;
}

template <typename State, typename Automaton>
void RectangularSyncWorker<State, Automaton>::clear() {
	mFlowpipe.clear();
	mJumpSuccessorSets.clear();
}
}  // namespace hypro
