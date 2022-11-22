/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "SingularWorker.h"

namespace hypro {

template <typename Representation, typename Automaton>
REACHABILITY_RESULT SingularWorker<Representation, Automaton>::computeForwardReachability( const ReachTreeNode<Representation, LocationT>& task ) {
	if ( computeTimeSuccessors( task ) == REACHABILITY_RESULT::UNKNOWN ) {
		return REACHABILITY_RESULT::UNKNOWN;
	}
	computeJumpSuccessors( task );
	return REACHABILITY_RESULT::SAFE;
}

template <typename Representation, typename Automaton>
REACHABILITY_RESULT SingularWorker<Representation, Automaton>::computeTimeSuccessors( const ReachTreeNode<Representation, LocationT>& task, bool checkSafety ) {
	using Number = typename Representation::NumberType;

	Representation initialSet = task.getInitialSet();

	auto [containment, segment] = intersect( initialSet, task.getLocation()->getInvariant(), mSubspace );
	if ( containment == CONTAINMENT::NO ) {
		return REACHABILITY_RESULT::SAFE;
	}

	if ( checkSafety ) {
		std::tie( containment, std::ignore ) = ltiIntersectBadStates( segment, task.getLocation(), mHybridAutomaton, mSubspace );
		if ( containment != CONTAINMENT::NO ) {
			// Todo: memorize the intersecting state set and keep state.
			return REACHABILITY_RESULT::UNKNOWN;
		}
	}

	// compute time successor states
	// assert singular flow
	assert( task.getLocation()->getLinearFlow( mSubspace ).getFlowMatrix().leftCols( initialSet.dimension() ) == matrix_t<Number>::Zero( initialSet.dimension() + 1, initialSet.dimension() ) );

	// construct point describing the dynamics
	std::vector<Point<Number>> dynamics;
	// The last column of the flow matrix are the constant derivatives. Only take the head to have consistent dimensions with the initial set
	dynamics.emplace_back( vector_t<Number>( task.getLocation()->getLinearFlow( mSubspace ).getFlowMatrix().col( initialSet.dimension() ) ).head( initialSet.dimension() ) );

	Representation timeSuccessors = singularApplyBoundedTimeEvolution( segment, dynamics, carl::convert<tNumber, Number>( mSettings.localTimeHorizon ) );
	auto [invariantContainment, constrainedTimeSuccessors] = intersect( timeSuccessors, task.getLocation()->getInvariant(), mSubspace );
	if ( invariantContainment == CONTAINMENT::NO ) {
		return REACHABILITY_RESULT::SAFE;
	}
	// add state to flowpipe
	mFlowpipe.addState( constrainedTimeSuccessors );
	if ( checkSafety ) {
		std::tie( containment, segment ) = ltiIntersectBadStates( constrainedTimeSuccessors, task.getLocation(), mHybridAutomaton, mSubspace );
		if ( containment != CONTAINMENT::NO ) {
			// Todo: memorize the intersecting state set and keep state.
			return REACHABILITY_RESULT::UNKNOWN;
		}
	}
	return REACHABILITY_RESULT::SAFE;
}

template <typename Representation, typename Automaton>
void SingularWorker<Representation, Automaton>::computeJumpSuccessors( const ReachTreeNode<Representation, LocationT>& task ) {
	// for each transition intersect each computed time successor set with the guard. If the intersection is non-empty, store for post-processing.

	JumpPredecessors transitionEnablingStateSets;
	for ( auto& stateSet : mFlowpipe ) {
		for ( const auto& transitionPtr : task.getLocation()->getTransitions() ) {
			auto [containment, set] = intersect( stateSet, transitionPtr->getGuard(), mSubspace );
			if ( containment != CONTAINMENT::NO ) {
				transitionEnablingStateSets[transitionPtr.get()] = { set };
			}
		}
	}

	// post processing: apply reset on those sets, intersect the sets with the invariant of the target location. If the resulting state set is non-empty, add it to the jump successors set.
	postProcessJumpSuccessors( transitionEnablingStateSets );
}

template <typename Representation, typename Automaton>
void SingularWorker<Representation, Automaton>::postProcessJumpSuccessors( const JumpSuccessors& guardSatisfyingSets ) {
	singularJumpHandler<Representation, LocationT> jmpHandler;
	mJumpSuccessorSets = jmpHandler.applyJump( guardSatisfyingSets, mSubspace );
}

template <typename Representation, typename Automaton>
REACHABILITY_RESULT SingularWorker<Representation, Automaton>::computeBackwardReachability( const ReachTreeNode<Representation, LocationT>& task ) {
	std::cout << "backward automata is " << mHybridAutomaton << std::endl;
	if ( computeTimePredecessors( task ) == REACHABILITY_RESULT::UNKNOWN ) {
		return REACHABILITY_RESULT::UNKNOWN;
	}
	computeJumpPredecessors();
	return REACHABILITY_RESULT::SAFE;
}

template <typename Representation, typename Automaton>
REACHABILITY_RESULT SingularWorker<Representation, Automaton>::computeTimePredecessors( const ReachTreeNode<Representation, LocationT>& task ) {
	Representation badSet = task.getState();

	auto [containment, segment] = rectangularIntersectInvariant( badSet );
	if ( containment == CONTAINMENT::NO ) {
		return REACHABILITY_RESULT::SAFE;
	}

	// add state to flowpipe
	mFlowpipe.addState( segment );

	std::tie( containment, segment ) = rectangularBadIntersectInitialStates( segment, mHybridAutomaton );
	if ( containment != CONTAINMENT::NO ) {
		// Todo: memorize the intersecting state set and keep state.
		return REACHABILITY_RESULT::UNKNOWN;
	}

	// compute time predecessors states
	Representation timePredecessors = rectangularApplyReverseTimeEvolution( segment, badSet.getLocation()->getRectangularFlow() );
	std::cout << "time" << std::endl;
	auto [invariantContainment, constrainedTimePredecessors] = rectangularIntersectInvariant( timePredecessors );
	if ( invariantContainment == CONTAINMENT::NO ) {
		return REACHABILITY_RESULT::SAFE;
	}

	// add state to flowpipe
	mFlowpipe.addState( constrainedTimePredecessors );

	std::tie( containment, segment ) = rectangularBadIntersectInitialStates( constrainedTimePredecessors, mHybridAutomaton );
	if ( containment != CONTAINMENT::NO ) {
		// Todo: memorize the intersecting state set and keep state.
		return REACHABILITY_RESULT::UNKNOWN;
	}

	return REACHABILITY_RESULT::SAFE;
}

template <typename Representation, typename Automaton>
void SingularWorker<Representation, Automaton>::computeJumpPredecessors() {
	// for each state: find possible transitions and intersect the set with reset of the transitions
	rectangularResetHandler<Representation, Automaton> resetHandler;
	for ( auto& state : mFlowpipe ) {
		std::cout << "reset check" << std::endl;
		resetHandler.rectangularIntersectReset( state, mHybridAutomaton );
	}

	// jump to source location
	reverseProcessJumpPredecessors( resetHandler.getResetSatisfyingStateSets() );
}

template <typename Representation, typename Automaton>
void SingularWorker<Representation, Automaton>::reverseProcessJumpPredecessors( const JumpSuccessors& guardSatisfyingSets ) {
	singularJumpHandler<Representation, LocationT> jmpHandler;
	mJumpPredecessorSets = jmpHandler.applyReverseJump( guardSatisfyingSets, nullptr );
}

}  // namespace hypro
