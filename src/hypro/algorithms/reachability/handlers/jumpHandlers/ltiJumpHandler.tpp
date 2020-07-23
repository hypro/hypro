#include "ltiJumpHandler.h"

namespace hypro {

/*
template <typename State>
void ltiJumpHandler<State>::handle() {
	std::size_t currentTargetLevel = mTask->btInfo.btLevel;
	bool wasRefinementTask = mTask->btInfo.btPath.size() > 0;  // TODO: This flag is used in the wrong way later

	// State stage
	// This stage deals with aggregation and set handling. Only valid states (i.e. non-empty) will be forwarded to the node stage.

	//START_BENCHMARK_OPERATION(FULL_AGGREGATION);
	TransitionStateMap processedStates = applyJump( *( mSuccessorBuffer ), mTransition, mStrategy );
	//EVALUATE_BENCHMARK_RESULT(FULL_AGGREGATION);

	// At this point the state level processing is complete. Set up nodes. Note that each states timestamp corresponds to the enabled
	// transition time, i.e. use this time to update the path. After that, reset it to zero (if not using global time).

	// Node Stage
	// This stage creates tree nodes and adds them to the tree. The relevant nodes which require further processing will be added as
	// tasks to the corresponding queue.
	TRACE( "hydra.worker.discrete", "Process " << processedStates.size() << " aggregated transitions." );
	for ( const auto& transitionStatePair : processedStates ) {
		// we need to determine the time interval during which the transition was enabled.
		// The covered time interval is required for the timing updates and spans the time interval the transition was enabled
		// irregardless of aggregation settings (that is, why this is not computed during state stage)
		carl::Interval<tNumber> coveredTimeInterval = stateSets.begin()->getTimestamp();

		// children holds the nodes which need to be added,
		// also writes to the coveredTimeInterval to obtain the time the transition was enabled.
		typename ReachTreeNode<State>::NodeList_t children = createNodesFromStates( transition, stateSets, currentTargetLevel, coveredTimeInterval, mTask->treeNode );

		TRACE( "hydra.worker.discrete", "Transition covers time " << coveredTimeInterval );
		TRACE( "hydra.worker.discrete", "Created " << children.size() << " new nodes which have to be added to the tree." );

		// Update timing tree - add node for each child
		auto& tProvider = EventTimingProvider<typename State::NumberType>::getInstance();
		EventTimingNode<typename State::NumberType>* timingNode = nullptr;
		if ( SettingsProvider<State>::getInstance().useAnyTimingInformation() ) {
			timingNode = tProvider.rGetNode( mTask->treeNode->getPath(), mTask->btInfo.timingLevel );
		}
		for ( const auto& child : children ) {
			if ( SettingsProvider<State>::getInstance().useAnyTimingInformation() ) {
				auto newNode = tProvider.addChildToNode( timingNode, SettingsProvider<State>::getInstance().getGlobalTimeHorizon() );
				newNode->setEntryTransition( transition );
				newNode->setEntryTimestamp( child->getTimestamp( currentTargetLevel ) );
				newNode->setLocation( transition->getTarget() );
				newNode->setLevel( currentTargetLevel );
			}
		}

		// Update reach tree
		// Note: At this point we have a fresh node with only the refinement set for the dedicated level. In case of a backtrack
		// run, we need to match the node to existing children. In case of a fresh run (no childen), I think we can simply create
		// a new task (depending on the settings, i.e. reset to level 0, we have to modify the node).

		// regular, tree-extending (depth) case, i.e. no backtracking
		// Note: There might be children, but for a different transition, so catch this by the second condition.
		// Note: There can also be children for this transition, but with a whole different timestamp (wavy trajectories).
		// Note: This branch is only taken, if the bt-path is empty and there do not exist child-nodes for this transition.
		// TODO: Pass the time interval to isTreeExtension and check for the time intervals the transition was enabled.
		if ( !wasRefinementTask && isTreeExtension<State>( mTask->treeNode, transition ) ) {
			TRACE( "hydra.worker.discrete", "Regular tree extension." );
			for ( const auto& child : children ) {
				// if the following is set, copy the refinement to any other refinement level.
#ifdef RESET_REFINEMENTS_ON_CONTINUE_AFTER_BT_RUN
				if ( currentTargetLevel > 0 ) {	 // I think this branch can never be reached, as wasRefinementTask prevents this.
					for ( auto i = 0; i < currentTargetLevel; ++i ) {
						if ( child->getRefinements()[i].isDummy ) {
							TRACE( "hydra.worker.discrete", "Add refinement for level " << i );
							//child->convertRefinement(currentTargetLevel, i, SettingsProvider<State>::getInstance().getStrategy().at(i));
							SettingsProvider<State>::getInstance().getStrategy().advanceToLevel( child->rGetRefinements()[i].initialSet, i );
						}
					}
				}
#endif

				// add child to current reach tree.
				mTask->treeNode->addChild( child );
				TRACE( "hydra.worker.discrete", "Add node " << child << " as child to node " << mTask->treeNode << " which has " << mTask->treeNode->getRefinements().size() << " refinements." );
				TRACE( "hydra.worker.discrete", "Child entry timestamp: " << child->getTimestamp( currentTargetLevel ) );
				assert( child->getParent() == mTask->treeNode );

				// create tasks
				INFO( "hydra.worker.discrete", "Enqueue Tree node " << child << " in local queue." );
				std::shared_ptr<Task<State>> newTask = std::make_shared<Task<State>>( child );
				// if we do not reset to level 0, set refinementLevel of task
#ifndef RESET_REFINEMENTS_ON_CONTINUE_AFTER_BT_RUN
				newTask->btInfo.btLevel = currentTargetLevel;
#endif
				newTask->btInfo.timingLevel = mTask->btInfo.timingLevel;

				// the first property has to be true already while the second never can be satisfied (wasREfinementTask demands NO bt-path)
				if ( !wasRefinementTask || mTask->btInfo.currentBTPosition == mTask->btInfo.btPath.size() ) {
#ifdef SINGLE_THREAD_FIXED_POINT_TEST
					if ( !child->getPath().hasChatteringZeno() ) {
						if ( !SettingsProvider<State>::getInstance().useGlobalQueuesOnly() ) {
							mLocalQueue->nonLockingEnqueue( newTask );
						} else {
							mLocalQueue->enqueue( newTask );
						}
					}
#else
					if ( !SettingsProvider<State>::getInstance().useGlobalQueuesOnly() ) {
						mLocalQueue->nonLockingEnqueue( std::move( newTask ) );
					} else {
						mLocalQueue->enqueue( std::move( newTask ) );
					}
#endif
				}
			}
			//INFO("hydra.worker.discrete","No backtracking. localQueue is now:\n" << *(mLocalQueue) << "localCEXQueue is now:\n" << *(mLocalCEXQueue));
		} else {
			// there are already children, which need to be mapped. This is irregardless, whether the current task was a
			// refinement task or not. Upon queuing we decide, whether the new task will be a refinement task or not.
			// Edit: It is not irregardless of backtracking. If there are already children, but it is not a bt-task, these children might
			// be due to some "wavy" trajectory, i.e. the transition can be enabled multiple times with breaks in between.
			// This goes towards chattering behavior.

			TRACE( "hydra.worker.discrete", "Current->treeNode is: " << mTask->treeNode );

			typename ReachTreeNode<State>::NodeList_t oldChildren = mTask->treeNode->getChildrenForTransition( transition );

			// collect the time-spans where the transition to existing child nodes was enabled to map new child nodes (update).
			std::vector<carl::Interval<tNumber>> oldTimespans;
			collectTimespansForRefinementLevel<State>( oldTimespans, oldChildren, currentTargetLevel );

			DEBUG( "hydra.worker.refinement", "For transition " << *transition << " there are " << oldChildren.size() << " existing relevant children and we attempt to add " << children.size() << " new ones." );

			// now we need to map the children via their timestamp.
			// Note: All this relies on the child-nodes to be sorted ascending in their transition timestamps.
			if ( !oldChildren.empty() ) {
				assert( !oldTimespans.empty() );
				// modifies children-list: all potential child nodes are removed which do not intersect oldTimespans
				preProcess<State>( children, oldTimespans );
				// node updater matches new nodes (children) to existing nodes and creates new Tasks.
				nodeUpdater<State> nu( mTask, mLocalQueue, mLocalCEXQueue, currentTargetLevel );
				nu( children, oldChildren, transition );
			}  // not old children empty

			// at this point either oldChildren or children should be empty (or both).
			assert( oldChildren.empty() || children.empty() );

			// in case there are old children left to map (i.e. we had too many old children and already mapped all new ones)
			// set the remaining old children for the target level to dummy.
			if ( !oldChildren.empty() ) {
				RefinementSetting<State> dummyRefinement;
				dummyRefinement.isDummy = true;
				for ( auto oldChildIt = oldChildren.begin(); oldChildIt != oldChildren.end(); ++oldChildIt ) {
					TRACE( "hydra.worker.refinement", "Old child " << *oldChildIt << " not required. Set level " << mTask->btInfo.btLevel << " to dummy." );
					( *oldChildIt )->setNewRefinement( mTask->btInfo.btLevel, dummyRefinement );
				}
			}

			// in case there are more new children than old children have been, add new ones as fresh nodes.
			DEBUG( "hydra.worker.refinement", "Process " << children.size() << " leftover child nodes." );
			insertAndCreateTask( children, mTask, mLocalQueue, mLocalCEXQueue, currentTargetLevel );

		}  // case when there are already children in the tree which need to be updated and mapped.
	}	   // loop over processed states
	// When all sets are processed clear _newInitialSets
	if ( mTransition == nullptr ) {
		mSuccessorBuffer->clear();
	} else {
		// in case only one transition was processed, only delete its nodes.
		// Todo: Attention, can it happen, that the transition is already in that set due to previous reasons?
		for ( auto tupleIt = mSuccessorBuffer->begin(); tupleIt != mSuccessorBuffer->end(); ) {
			if ( std::get<0>( *tupleIt ) == mTransition ) {
				tupleIt = mSuccessorBuffer->erase( tupleIt );
			} else {
				++tupleIt;
			}
		}
	}
}
*/

template <typename State>
auto ltiJumpHandler<State>::applyJump( const TransitionStateMap& states, Transition<Number>* transition, const AnalysisParameters& strategy ) -> TransitionStateMap {
	// holds a mapping of transitions to states which need to be aggregated
	TransitionStateMap toAggregate;
	// holds a mapping of transitions to states which are ready to apply the reset function and the intersection with the invariant
	TransitionStateMap toProcess;
	// holds a mapping of transitions to already processed (i.e. aggregated, resetted and reduced) states
	TransitionStateMap processedStates;
	for ( const auto& [transitionPtr, statesVec] : states ) {
		// only handle sets related to the passed transition, in case any is passed.
		if ( transition == nullptr || transitionPtr == transition ) {
			// check aggregation settings

			if ( ( strategy.aggregation == AGG_SETTING::NO_AGG && strategy.clustering == -1 ) ||
				 ( strategy.aggregation == AGG_SETTING::MODEL && transitionPtr->getAggregation() == Aggregation::none ) ) {
				// just copy the states to the toProcess map.

				auto& targetVec = toProcess[transitionPtr];
				targetVec.insert( targetVec.end(), statesVec.begin(), statesVec.end() );
			} else {  // store for aggregation
				auto& targetVec = toAggregate[transitionPtr];
				targetVec.insert( targetVec.end(), statesVec.begin(), statesVec.end() );
			}
		}
	}

	// aggregate all sets marked for aggregation
	aggregate( toProcess, toAggregate, strategy );

	DEBUG( "hydra.worker", "Apply jump on " << toProcess.size() << " transitions." );

	for ( const auto& [transitionPtr, statesVec] : toProcess ) {
		DEBUG( "hydra.worker", "Apply jump on " << statesVec.size() << " states." );
		for ( const auto& state : statesVec ) {
			// copy state - as there is no aggregation, the containing set and timestamp is already valid
			// TODO: Why copy?
			assert( !state.getTimestamp().isEmpty() );
			State newState( state );

			// apply reset function
			applyReset( newState, transitionPtr );

			// set target location in state set
			newState.setLocation( transitionPtr->getTarget() );

			// check invariant in new location
			auto containmentStateSetPair = ltiIntersectInvariant( newState );
			if ( containmentStateSetPair.first == CONTAINMENT::NO ) {
				continue;
			}

			// reduce if possible (Currently only for support functions)
			applyReduction( containmentStateSetPair.second );

			DEBUG( "hydra.worker.discrete", "State after reduction: " << containmentStateSetPair.second );

			// Note: Here we misuse the state's timestamp to carry the transition timing to the next stage -> just don't reset
			// the timestamp in case no aggregation happens.

			if ( processedStates.find( transitionPtr ) == processedStates.end() ) {
				processedStates[transitionPtr] = std::vector<State>();
			}
			processedStates[transitionPtr].emplace_back( containmentStateSetPair.second );
		}
	}
	return processedStates;
}

template <typename State>
void ltiJumpHandler<State>::applyReset( State& state, Transition<Number>* transitionPtr ) const {
	if ( !transitionPtr->getReset().empty() ) {
		for ( size_t i = 0; i < state.getNumberSets(); i++ ) {
			if ( state.getSetType( i ) == representation_name::carl_polytope ) {
				IntervalAssignment<Number> intervalReset = transitionPtr->getReset().getIntervalReset( i );
				state = state.partialIntervalAssignment( intervalReset.mIntervals, i );
			} else {
				AffineTransformation<Number> reset = transitionPtr->getReset().getAffineReset( i );
				state = state.partiallyApplyTransformation( reset.mTransformation, i );
			}
		}
	}
}

template <typename State>
void ltiJumpHandler<State>::applyReduction( State& state ) const {
	for ( size_t i = 0; i < state.getNumberSets(); i++ ) {
		if ( state.getSetType( i ) == representation_name::support_function ) {
			state.partiallyReduceRepresentation( i );
		}
		if ( state.getSetType( i ) == representation_name::SFN ) {
			//Cut off the subtrees from the root of the supportfunction by overapproximating the representation with a hpolytope (or possibly a box)
			//and set it as the leaf of a new tree
			auto tmpSFN = std::visit( genericConvertAndGetVisitor<SupportFunctionNew<typename State::NumberType>>(), state.getSet( i ) );
			if ( tmpSFN.getSettings().DETECT_BOX ) {
				//if(!tmpSFN.empty()){
				tmpSFN.reduceRepresentation();
				auto isHPolyBox = isBox( tmpSFN.matrix(), tmpSFN.vector() );
				if ( std::get<0>( isHPolyBox ) ) {
					Box<Number> tmpBox( std::get<1>( isHPolyBox ) );
					tmpSFN = SupportFunctionNew<Number>( tmpBox );
				} else {
					HPolytopeT<Number, hypro::Converter<Number>, HPolytopeOptimizerCaching> tmpHPoly( tmpSFN.matrix(), tmpSFN.vector() );
					tmpSFN = SupportFunctionNew<Number>( tmpHPoly );
				}
				state.setSet( std::visit( genericInternalConversionVisitor<typename State::repVariant, SupportFunctionNew<Number>>( tmpSFN ), state.getSet( i ) ), i );
				//}
			}
		}
	}
}

template <typename State>
void ltiJumpHandler<State>::aggregate( TransitionStateMap& processedStates, const TransitionStateMap& toAggregate, const AnalysisParameters& strategy ) const {
	// Aggregation
	DEBUG( "hydra.worker.discrete", "Number of transitions to aggregate: " << toAggregate.size() << std::endl );
	for ( const auto& [transition, stateSets] : toAggregate ) {
		assert( !stateSets.empty() );
		TRACE( "hydra.worker.discrete", stateSets.size() << " sets to aggregate for transition " << transitionStatePair.first->getSource()->getName() << " -> " << transition->getTarget()->getName() );
		std::vector<State> aggregatedStates;
		// Aggregate sets by using sequential unite operations (TODO Implement and make use of multi-unite).
		State aggregatedState( *stateSets.begin() );
		// counts the number of processed sets - just for debugging.
		unsigned setCnt = 1;
		// counts the number of sets in the current cluster.
		std::size_t clusterCnt = 1;
		// determines whether there are still sets to be clustered together.
		bool leftovers = true;

		TRACE( "hydra.worker.discrete", "Find subspace mapping for loc " << aggregatedState.getLocation()->getName() << " (" << aggregatedState.getLocation() << ")" );

		// perform union directly on the current set vector to avoid an extreme amount of consistency checks
		std::vector<typename State::repVariant> currentSets = aggregatedState.getSets();
		// contains the aggregated timestamp, initialized with the first timestamp
		carl::Interval<tNumber> aggregatedTimestamp = ( *stateSets.begin() ).getTimestamp();
		//START_BENCHMARK_OPERATION(AGGREGATE);
		for ( auto stateIt = ++stateSets.begin(); stateIt != stateSets.end(); ++stateIt ) {
			TRACE( "hydra.worker.discrete", "Agg. aggState and set " << setCnt );
			// actual aggregation.
			for ( std::size_t i = 0; i < aggregatedState.getNumberSets(); i++ ) {
				//START_BENCHMARK_OPERATION(UNION);
				currentSets[i] = std::visit( genericUniteVisitor<typename State::repVariant>(), currentSets[i], stateIt->getSet( i ) );
				//EVALUATE_BENCHMARK_RESULT(UNION);
			}

			// timestamp handling
			assert( !( *stateIt ).getTimestamp().isEmpty() );
			aggregatedTimestamp = aggregatedTimestamp.convexHull( ( *stateIt ).getTimestamp() );

			leftovers = true;
			++setCnt;
			++clusterCnt;
#ifdef CLUSTERING_NUMBER_LIMITS_SUCESSORS
			if ( strategy.clustering > 0 && clusterCnt == std::ceil( double( stateSets.size() ) / double( strategy.clustering ) ) ) {
				TRACE( "hydra.worker.discrete", "Clustering." );
				aggregatedStates.emplace_back( aggregatedState );
				leftovers = false;
				if ( stateIt + 1 != stateSets.end() ) {
					aggregatedState = *( ++stateIt );
					aggregatedTimestamp = aggregatedState.getTimestamp();
					clusterCnt = 1;
				} else {
					break;
				}
			}
#else
			if ( strategy.clustering > 0 && clusterCnt == std::size_t( strategy.clustering ) ) {
				TRACE( "hydra.worker.discrete", "Clustering." );
				aggregatedStates.emplace_back( aggregatedState );
				leftovers = false;
				if ( stateIt + 1 != stateSets.end() ) {
					aggregatedState = *( ++stateIt );
					aggregatedTimestamp = aggregatedState.getTimestamp();
					clusterCnt = 1;
				} else {
					break;
				}
			}
#endif
		}
		aggregatedState.setSets( currentSets );
		//EVALUATE_BENCHMARK_RESULT(AGGREGATE);

		// set timestamps accordingly
		aggregatedState.setTimestamp( aggregatedTimestamp );

		if ( strategy.clustering < 1 || leftovers ) {
			TRACE( "hydra.worker.discrete", "No clustering." );
			aggregatedStates.emplace_back( aggregatedState );
		}

		// add to final mapping.
		for ( auto& state : aggregatedStates ) {
			if ( processedStates.find( transition ) == processedStates.end() ) {
				processedStates[transition] = std::vector<State>();
			}
			processedStates[transition].emplace_back( state );
		}
	}
}

// template <typename State>
// typename ReachTreeNode<State>::NodeList_t ltiJumpHandler<State>::createNodesFromStates(
// 	  Transition<Number>* transition,
// 	  const std::vector<State>& states,
// 	  std::size_t currentTargetLevel,
// 	  carl::Interval<tNumber>& coveredTimeInterval,
// 	  typename ReachTreeNode<State>::Node_t parent ) {
// 	typename ReachTreeNode<State>::NodeList_t children;
// 	for ( const auto& state : states ) {
// 		TRACE( "hydra.worker.discrete", "Consider " << states.size() << " states." );
// 		assert( state.getLocation() != nullptr );

// 		// TODO: This fixed-point test should only consider the current refinement level.
// 		//fix point test does not seem to work in full timed context
// 		/*
// 			if(!SettingsProvider<State>::getInstance().isFullTimed() && SettingsProvider<State>::getInstance().getLocationTypeMap().find(transition->getSource())->second != LOCATIONTYPE::TIMEDLOC){
// 				bool reachedFixedPoint = false;
// 				if(SettingsProvider<State>::getInstance().useFixedPointTest()) {
// 					for(const auto n : NodeManager<State>::getInstance().getTree().getRoot()->getChildren()) {
// 						reachedFixedPoint = n->hasFixedPoint(state,parent);
// 						if(reachedFixedPoint){
// 							std::cout << "Detected fixed point." << std::endl;
// 							TRACE("hydra.worker.discrete", "Do not create successor nodes as fixed-point has been detected.");
// 							break;
// 						}
// 					}
// 				}

// 				if(reachedFixedPoint) {
// 					continue;
// 				}
// 			}
// 			*/

// 		typename ReachTreeNode<State>::Node_t newNode = new ReachTreeNode<State>( state, currentTargetLevel, parent );

// 		// collect covered time interval
// 		coveredTimeInterval = coveredTimeInterval.convexHull( state.getTimestamp() );

// 		// invariant timings
// 		auto invariantTimings = getEnabledTimings( mObtainedTimings.getInvariantTimings() );
// 		if ( invariantTimings.size() == 1 ) {
// 			newNode->addTimeStepToPath( invariantTimings[0] );
// 		} else {
// 			// Attention, this is a dummy setting.
// 			newNode->addTimeStepToPath( coveredTimeInterval );
// 		}

// 		// set up node properties

// 		newNode->addTransitionToPath( transition, state.getTimestamp() );
// 		newNode->setDepth( parent->getDepth() + 1 );
// 		newNode->setTimestamp( currentTargetLevel, state.getTimestamp() );

// 		// If no global timing is used, reset time intervals to zero
// 		RefinementSetting<State> tmpRefinement = newNode->getRefinements().at( currentTargetLevel );
// 		assert( tmpRefinement.initialSet.getLocation() != nullptr );
// 		if ( SettingsProvider<State>::getInstance().useLocalTiming() ) {
// 			tmpRefinement.initialSet.setTimestamp( carl::Interval<tNumber>( 0 ) );
// 		}

// 		tmpRefinement.isDummy = false;
// 		newNode->setNewRefinement( currentTargetLevel, tmpRefinement );
// 		assert( !newNode->getTimestamp( currentTargetLevel ).isEmpty() );

// 		DEBUG( "hydra.worker.discrete", "New node path: " << newNode->getPath() );
// 		DEBUG( "hydra.worker.discrete", "new jump depth: " << newNode->getDepth() );
// 		DEBUG( "hydra.worker.discrete", "new refinements size: " << newNode->getRefinements().size() );
// 		children.emplace_back( newNode );
// 	}
// 	return children;
// }

}  // namespace hypro
