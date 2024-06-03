/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "RectangularSyncWorker.h"

namespace hypro {

template <typename State, typename Automaton>
REACHABILITY_RESULT
RectangularSyncWorker<State, Automaton>::computeForwardReachability( ReachTreeNode<State, LocationT>& task ) {
	DEBUG( "hypro.reachability.rectangular", "Start forward computation in worker" );
	if ( computeTimeSuccessors( task ) == REACHABILITY_RESULT::UNKNOWN ) {
		return REACHABILITY_RESULT::UNKNOWN;
	}
	computeJumpSuccessors( task );
	return REACHABILITY_RESULT::SAFE;
}

template <typename State, typename Automaton>
REACHABILITY_RESULT
RectangularSyncWorker<State, Automaton>::computeTimeSuccessors( ReachTreeNode<State, LocationT>& task ) {
	if ( !task.getFlowpipe().empty() ) {
		// the time successors of this node has already been computed, because of label synchronization
		// TODO check intersection with bad states (i.e intersect each flowpipe segment with the bad states and check if the intersection is empty)
		return REACHABILITY_RESULT::SAFE;
	}

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
void RectangularSyncWorker<State, Automaton>::computeJumpSuccessors( ReachTreeNode<State, LocationT>& task ) {
	// for each transition intersect each computed time successor set with the guard. If the intersection is non-empty, store for post-processing.
	rectangularSyncGuardHandler<State, LocationT> guardHandler;
	for ( auto& state : mFlowpipe ) {
		guardHandler( state, task.getLocation(), mNonSyncLabels );
	}

	// post process non synchronizing jumps: apply reset on those sets, intersect the sets with the invariant of the target location. If the resulting state set is non-empty, add it to the jump successors set.
	postProcessJumpSuccessors( guardHandler.getNonSyncGuardSatisfyingStateSets() );
	// post process synchronizing jumps: for each transition, find nodes in the other automata that can synchronize, intersect their times, and compute their jump successors
	postProcessSyncJumpSuccessors( task, guardHandler.getSyncGuardSatisfyingStateSets() );
}

template <typename State, typename Automaton>
void RectangularSyncWorker<State, Automaton>::postProcessJumpSuccessors( const JumpSuccessors& guardSatisfyingSets ) {
	singularJumpHandler<State, LocationT> jmpHandler;
	mJumpSuccessorSets = jmpHandler.applyJump( guardSatisfyingSets );
}

template <typename State, typename Automaton>
void RectangularSyncWorker<State, Automaton>::postProcessSyncJumpSuccessors( ReachTreeNode<State, LocationT>& task, const JumpSuccessors& guardSatisfyingSets ) {
	if ( !(std::is_same<State, VPolytope<Number>>() || std::is_same<State, HPolytope<Number>>()) ) {
		assert( false && "Label Synchronization is implemented for VPolytopes and HPolytopes only." );
	}
	for ( typename JumpSuccessors::const_iterator it = guardSatisfyingSets.begin();
		  it != guardSatisfyingSets.end(); ++it ) {
		auto transitionPtr = it->first;
		auto statesVec = it->second;
		assert( statesVec.size() == 1 && "Rectangular Flowpipes have only one state in the time successors." );
		auto& state = statesVec.front();
		auto time = state.getTimeProjection();							 // time is a polytope not an interval
		assert( time.dimension() == 1 );
		auto label = transitionPtr->getLabels();										 // get the vector of labels of the transition //TODO: try to handle transition with multiple labels.
		std::set<RectangularSyncWorker<State, Automaton>*> visitedWorkers{ this };
		auto nodeTimePairs = findSyncSuccessors( task, *transitionPtr, label, time, visitedWorkers );
		for ( auto& [node, syncTime] : nodeTimePairs ) {
			std::map<size_t, ReachTreeNode<State, LocationT>* > inheritedMap;
			// iterate over task.getSyncNodes and insert them in inheritedMap
			for ( size_t i = 0; i < task.getSyncNodes().size(); i++ ) {
				if ( i != mVariablePoolIndex ) {
					inheritedMap.insert( std::make_pair( i, task.getSyncNodes()[i] ) );
				}
			}
			node->updateTreeWithSyncNodes( std::map<size_t, ReachTreeNode<State, LocationT>*>{ std::make_pair( mVariablePoolIndex, node ) }, inheritedMap );
		}
		// here we have computed sync successors, added them to the reach Trees, updated the book-keeping of sync nodes in the tree.
	}
}

template <typename State, typename Automaton>
std::multimap<ReachTreeNode<State, typename Automaton::LocationType>*, State>
RectangularSyncWorker<State, Automaton>::findSyncSuccessors( ReachTreeNode<State, LocationT>& task,
															 Transition<LocationT> transition,
															 const std::vector<Label>& label,
															 State syncTime,
															 std::set<RectangularSyncWorker<State, Automaton>*> visitedWorkers ) {
	assert( label.size() == 1 && "the analyzer assumes that every transition has only one label. It cannot handle models where the transitions can have multiple labels." );
	if ( visitedWorkers == mSyncDict.at( label.front() ) ) {
		// check if the synchronizing transition is enabled
		rectangularSyncGuardHandler<State, LocationT> guardHandler;
		JumpSuccessors transitionSourceNodeMap = guardHandler.intersectWithGuard( task.getFlowpipe(), &transition );
		if ( transitionSourceNodeMap.empty() ) {
			// if the intersection with the guard is empty (i.e. the transition is not enabled), the synchronization is not possible
			return {};
		}
		rectangularSyncJumpHandler<State, LocationT> jmpHandler;
		mSyncJumpSuccessorSets = jmpHandler.applyJump( transitionSourceNodeMap, syncTime );
		if (mSyncJumpSuccessorSets.empty()) {
			// if the jump succecssors are empty (i.e. intersection of guardSatisfyingSet with common time is empty or intersection with invariant of target location ), the synchronization is not possible
			return {};
		}
		std::multimap<ReachTreeNode<State, LocationT>*, State> syncNodeTimeMap{};
		// update the ReachTree with the new successor nodes
		for ( const auto& transitionStatesPair : mSyncJumpSuccessorSets ) {
			assert( transitionStatesPair.second.size() == 1 && "In Rectangular Analysis a jump can only have one successor." );
			auto& childNode = task.addChild( transitionStatesPair.second.front(), carl::Interval<SegmentInd>( 0, 0 ), transitionStatesPair.first );
			assert( childNode.getDepth() == task.getDepth() + 1 );
			childNode.initializeSyncNodes( task.getSyncNodes().size() );
			// TODO change name of mSyncChildrenToRemove to mSyncJumpSuccessorSets
			mSyncChildrenToRemove.insert( &childNode );
			auto resultTime = transitionStatesPair.second.front().getTimeProjection();
			syncNodeTimeMap.emplace( std::make_pair( &childNode, resultTime ) );
		}
		return syncNodeTimeMap;
	} else {
		// get a pointer to the worker, in which we search for synchronizing nodes
		RectangularSyncWorker<State, Automaton>* ptrToWorker = nullptr;
		for ( typename std::set<RectangularSyncWorker<State, Automaton>*>::const_iterator it = mSyncDict.at( label.front() ).begin();
			  it != mSyncDict.at( label.front() ).end(); ++it ) {
			if ( visitedWorkers.count( *it ) == 0 ) {
				ptrToWorker = *it;
				break;
			}
		}
		assert( ptrToWorker != nullptr );  // if we reach this execution branch, mSyncDict\visitedWorkers is not empty
		visitedWorkers.insert( ptrToWorker );
		// in this function we misuse mVariablePoolIndex to get the "index of the worker", to access the right syncNode.
		auto candidateTransitionMap = ptrToWorker->getCandidateNodes( task.getSyncNodeAtIndex( ptrToWorker->getVariablePoolIndex() ), label );
		std::multimap<ReachTreeNode<State, LocationT>*, State> syncNodeTimeMap{};
		for ( auto& nodeTransitionPair : candidateTransitionMap ) {
			ptrToWorker->changeVariablePool();
			ptrToWorker->computeTimeSuccessors( *nodeTransitionPair.first );
			this->changeVariablePool();
			// compute the time intesection
			auto timeIntersection = syncTime.intersect( nodeTransitionPair.first->getFlowpipe().front().getTimeProjection() );
			bool firstSyncCondition = nodeTransitionPair.first->getSyncNodeAtIndex( this->getVariablePoolIndex() ).isAncestorOf( &task );
			bool secondSyncCondition = true;
			for ( size_t i = 0; i < task.getSyncNodes().size(); i++ ) {
				if ( i != this->getVariablePoolIndex() && i != ptrToWorker->getVariablePoolIndex() ) {
					if ( !nodeTransitionPair.first->getSyncNodeAtIndex( i ).isAncestorOf( &( task.getSyncNodeAtIndex( i ) ) ) &&
						 !task.getSyncNodeAtIndex( i ).isAncestorOf( &( nodeTransitionPair.first->getSyncNodeAtIndex( i ) ) ) ) {
						secondSyncCondition = false;
						break;
					}
				}
			}
			if ( !timeIntersection.empty() && firstSyncCondition && secondSyncCondition ) {
				auto nodeTimePairs = ptrToWorker->findSyncSuccessors( *nodeTransitionPair.first, nodeTransitionPair.second, label, timeIntersection, visitedWorkers );
				for ( auto& [node, syncTime1] : nodeTimePairs ) {
					// check if the synchronizing transition is enabled
					rectangularSyncGuardHandler<State, LocationT> guardHandler;
					JumpSuccessors transitionSourceNodeMap = guardHandler.intersectWithGuard( task.getFlowpipe(), &transition );
					if ( transitionSourceNodeMap.empty() ) {
						// if the intersection with the guard is empty (i.e. the transition is not enabled), the synchronization is not possible
						continue;
					}
					rectangularSyncJumpHandler<State, LocationT> jmpHandler;
					mSyncJumpSuccessorSets = jmpHandler.applyJump( transitionSourceNodeMap, syncTime1 );
					// assert( mSyncJumpSuccessorSets.size() == 1 && "findJumpSuccessors searches applies the jump for one transition." );
					if (mSyncJumpSuccessorSets.empty()) {
						// if the jump succecssors are empty (i.e. intersection of guardSatisfyingSet with common time is empty or intersection with invariant of target location ), the synchronization is not possible
						continue;
					}
					// update the ReachTree with the new successor nodes
					for ( const auto& transitionStatesPair : mSyncJumpSuccessorSets ) {
						assert( transitionStatesPair.second.size() == 1 && "In Rectangular Analysis a jump can only have one successor." );
						auto& childNode = task.addChild( transitionStatesPair.second.front(), carl::Interval<SegmentInd>( 0, 0 ), transitionStatesPair.first );
						assert( childNode.getDepth() == task.getDepth() + 1 );
						childNode.initializeSyncNodes( task.getSyncNodes().size() );
						// set syncNodes pointer to node
						childNode.setSyncNodeAtIndex( node, ptrToWorker->getVariablePoolIndex() );
						mSyncChildrenToRemove.insert( &childNode );
						auto resultTime = transitionStatesPair.second.front().getTimeProjection();
						syncNodeTimeMap.emplace( std::make_pair( &childNode, resultTime ) );
					}
				}
			}
		}
		return syncNodeTimeMap;
	}
}

template <typename State, typename Automaton>
std::multimap<ReachTreeNode<State, typename Automaton::LocationType>*, Transition<typename Automaton::LocationType>>
RectangularSyncWorker<State, Automaton>::getCandidateNodes( ReachTreeNode<State, LocationT>& syncNode, const std::vector<Label>& label ) {
	std::multimap<ReachTreeNode<State, LocationT>*, Transition<LocationT>> syncCandidates{};
	// recursively search for nodes that can synchronize, i.e. have a transition with the same label
	for ( auto child : syncNode.getChildren() ) {
		auto childCandidates = getCandidateNodes( *child, label );
		syncCandidates.insert( childCandidates.begin(), childCandidates.end() );
	}
	for ( auto& transition : syncNode.getLocation()->getTransitions() ) {
		if ( transition->getLabels() == label ) {
			// we assume that the two label vectors are the same in order to synchronize. The synchronizing analysis is implemented assuming the label vectors always contain one element.
			syncCandidates.emplace( std::make_pair( &syncNode, *transition ) );
		}
	}
	return syncCandidates;
}

template <typename State, typename Automaton>
void RectangularSyncWorker<State, Automaton>::initNonSyncLabels() {
	for ( auto label : mHybridAutomaton.getLabels() ) {
		if ( mSyncDict.at( label ).size() == 1 && mSyncDict.at( label ).count( this ) == 1 ) {
			mNonSyncLabels.insert( label );
		}
	}
}

template <typename State, typename Automaton>
const std::set<ReachTreeNode<State, typename Automaton::LocationType>*>
RectangularSyncWorker<State, Automaton>::getSyncJumpSuccessorTasks() {
	// this function deletes nodes that have been created for synchronization, but cannot synchronize with the other automata
	std::set<ReachTreeNode<State, LocationT>*> syncJumpSuccessorTasks{};
	for ( auto node : mSyncChildrenToRemove ) {
		bool isSyncNode = true;
		for ( auto syncNode : node->getSyncNodes() ) {
			if ( syncNode == nullptr ) {
				isSyncNode = false;
				break;
			}
		}
		if ( isSyncNode ) {
			syncJumpSuccessorTasks.insert( node );
		} else {
			/* each node with a isSyncNode=false is a node created while looking for synchronization nodes, 
				but it cannot synchronize with the other automata so it needs to be deleted from the tree.  */
			mSyncChildrenToRemove.erase( node );
			node->getParent()->eraseChild( node );
		}
	}
	return syncJumpSuccessorTasks;
}

template <typename State, typename Automaton>
void RectangularSyncWorker<State, Automaton>::clear() {
	mFlowpipe.clear();
	mJumpSuccessorSets.clear();
	mSyncJumpSuccessorSets.clear();
	mSyncChildrenToRemove.clear();
}
}  // namespace hypro
