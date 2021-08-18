#include "ContextBasedReachabilityWorker.h"

namespace hypro {

template <typename State>
void ContextBasedReachabilityWorker<State>::processTask( const TaskType& t,
														 const Strategy<State>& strat,
														 WorkQueue<TaskType>* localQueue,
														 WorkQueue<TaskType>* localCEXQueue,
														 Flowpipe<State>& localSegments ) {
	if ( isValidTask( t, localCEXQueue ) ) {
		computeForwardReachability( t, strat, localQueue, localCEXQueue, localSegments );
	}
}

template <typename State>
void ContextBasedReachabilityWorker<State>::computeForwardReachability( const TaskType& task,
																		const Strategy<State>& strat,
																		WorkQueue<TaskType>* localQueue,
																		WorkQueue<TaskType>* localCEXQueue,
																		Flowpipe<State>& localSegments ) {
	IContext* context = ContextFactory<State>::getInstance().createContext( task, strat, localQueue, localCEXQueue, localSegments, this->mSettings );

	try {
		// std::cout << "context->execOnStart()" << std::endl;
		context->execOnStart();

		// START_BENCHMARK_OPERATION(FIRST_SEGMENT);
		//  compute first segment
		// std::cout << "context->execBeforeFirstSegment()" << std::endl;
		context->execBeforeFirstSegment();
		// std::cout << "context->firstSegment()" << std::endl;
		context->firstSegment();
		// std::cout << "context->execAfterFirstSegment()" << std::endl;
		context->execAfterFirstSegment();
		// EVALUATE_BENCHMARK_RESULT(FIRST_SEGMENT);

		// START_BENCHMARK_OPERATION(CHECK_INVARIANT);
		//  intersect with invariant
		// std::cout << "context->execBeforeCheckInvariant()" << std::endl;
		context->execBeforeCheckInvariant();
		// std::cout << "context->checkInvariant()" << std::endl;
		context->checkInvariant();
		// std::cout << "context->execAfterCheckInvariant()" << std::endl;
		context->execAfterCheckInvariant();
		// EVALUATE_BENCHMARK_RESULT(CHECK_INVARIANT);

		// START_BENCHMARK_OPERATION(INTERSECT_BAD_STATES);
		//  intersect with bad states
		// std::cout << "context->execBeforeIntersectBadStates()" << std::endl;
		context->execBeforeIntersectBadStates();
		// std::cout << "context->intersectBadStates()" << std::endl;
		context->intersectBadStates();
		// std::cout << "context->execAfterIntersectBadStates()" << std::endl;
		context->execAfterIntersectBadStates();
		// EVALUATE_BENCHMARK_RESULT(INTERSECT_BAD_STATES);

		// std::cout << "context->execBeforeLoop()" << std::endl;
		context->execBeforeLoop();

		// while not done
		// std::cout << "context->doneCondition() ()" << std::endl;
		while ( !context->doneCondition() ) {
			// START_BENCHMARK_OPERATION(COMPUTE_TIMESTEP);
			// std::cout << "context->execOnLoopItEnter()" << std::endl;
			context->execOnLoopItEnter();

			// START_BENCHMARK_OPERATION(CHECK_TRANSITION);
			//  intersect with transition guards
			// std::cout << "context->execBeforeCheckTransition()" << std::endl;
			context->execBeforeCheckTransition();
			// std::cout << "context->checkTransition()" << std::endl;
			context->checkTransition();
			// std::cout << "context->execAfterCheckTransition()" << std::endl;
			context->execAfterCheckTransition();
			// EVALUATE_BENCHMARK_RESULT(CHECK_TRANSITION);

			// START_BENCHMARK_OPERATION(CONTINUOUS_EVOLUTION);
			//  apply continuous time step
			// std::cout << "context->execBeforeContinuousEvolution()" << std::endl;
			context->execBeforeContinuousEvolution();
			// std::cout << "context->applyContinuousEvolution()" << std::endl;
			context->applyContinuousEvolution();
			// std::cout << "context->execAfterContinuousEvolution()" << std::endl;
			context->execAfterContinuousEvolution();
			// EVALUATE_BENCHMARK_RESULT(CONTINUOUS_EVOLUTION);

			// START_BENCHMARK_OPERATION(CHECK_INVARIANT);
			//  intersect with invariant
			// std::cout << "context->execBeforeCheckInvariant()" << std::endl;
			context->execBeforeCheckInvariant();
			// std::cout << "context->checkInvariant()" << std::endl;
			context->checkInvariant();
			// std::cout << "context->execAfterCheckInvariant()" << std::endl;
			context->execAfterCheckInvariant();
			// EVALUATE_BENCHMARK_RESULT(CHECK_INVARIANT);

			// START_BENCHMARK_OPERATION(INTERSECT_BAD_STATES);
			//  intersect with bad states
			// std::cout << "context->execBeforeIntersectBadStates()" << std::endl;
			context->execBeforeIntersectBadStates();
			// std::cout << "context->intersectBadStates()" << std::endl;
			context->intersectBadStates();
			// std::cout << "context->execAfterIntersectBadStates()" << std::endl;
			context->execAfterIntersectBadStates();
			// EVALUATE_BENCHMARK_RESULT(INTERSECT_BAD_STATES);

			// std::cout << "context->execOnLoopItExit()" << std::endl;
			context->execOnLoopItExit();
			// EVALUATE_BENCHMARK_RESULT(COMPUTE_TIMESTEP);
		}

		// std::cout << "context->execAfterLoop()" << std::endl;
		context->execAfterLoop();

		// START_BENCHMARK_OPERATION(DISCRETE_SUCCESSORS);
		//  create discrete successor states
		// std::cout << "context->execBeforeProcessDiscreteBehavior()" << std::endl;
		context->execBeforeProcessDiscreteBehavior();
		// std::cout << "context->processDiscreteBehavior()" << std::endl;
		context->processDiscreteBehavior();
		// std::cout << "context->execBeforeProcessDiscreteBehavior()" << std::endl;
		// context->execBeforeProcessDiscreteBehavior();
		// EVALUATE_BENCHMARK_RESULT(DISCRETE_SUCCESSORS);
		// std::cout << "context->execOnEnd()" << std::endl;
		context->execOnEnd();
	} catch ( HardTerminateException& e1 ) {
		DEBUG( "hydra.worker", "" << e1.what() );
		return;
	} catch ( FinishWithDiscreteProcessingException& e2 ) {
		DEBUG( "hydra.worker", "" << e2.what() );
		// START_BENCHMARK_OPERATION(DISCRETE_SUCCESSORS);
		//  finish creating discrete successor states
		// std::cout << "context->execBeforeProcessDiscreteBehavior()" << std::endl;
		context->execBeforeProcessDiscreteBehavior();
		// std::cout << "context->processDiscreteBehavior()" << std::endl;
		context->processDiscreteBehavior();
		// EVALUATE_BENCHMARK_RESULT(DISCRETE_SUCCESSORS);
		// std::cout << "context->execOnEnd()" << std::endl;
		context->execOnEnd();
	}
}

template <typename State>
bool ContextBasedReachabilityWorker<State>::isValidTask( const TaskType& t, WorkQueue<TaskType>* localCEXQueue ) {
	if ( t->treeNode->getRefinements().at( t->btInfo.btLevel ).fullyComputed ) {
		// This node has already been computed for the required level. This can only happen during concurrent BT-runs.
		DEBUG( "hydra.worker", std::this_thread::get_id() << ": Got node which is already on the desired level." );
		assert( t->btInfo.btLevel > 0 );
		// Follow bt-path by creating new tasks
		// 1: Find correct transition.
		// 2: Fine correct potential child. Note: At least the children (their order and links) are updated already, so we can
		//    safely read those. Nonetheless they might be locked for computation.
		std::pair<hypro::Transition<Number>*, carl::Interval<tNumber>> transitionTimingPair = t->btInfo.btPath.getTransitionToJumpDepth( t->treeNode->getDepth() );
		// Transition is only nullptr, if the jump depth is zero (which cannot be here) or the queried jump depth is larger than
		// the path's length (which cannot be either, as there would have been a bt-run, which already computed the whole path).
		if ( transitionTimingPair.first == nullptr ) {
			// the whole path has been computed already.
			TRACE( "hydra.worker", "Do not continue refinement as the path has been computed already to full extend." );
			t->treeNode->getMutex().unlock();
			return false;
		}
		// iterate over all children to match the timings
		DEBUG( "hydra.worker", std::this_thread::get_id() << ": Search for next nodes on btPath: " << t->btInfo.btPath );
		DEBUG( "hydra.worker", std::this_thread::get_id() << ": Consider child nodes for transition " << *transitionTimingPair.first );
		for ( auto child : t->treeNode->getChildrenForTransition( transitionTimingPair.first ) ) {
			DEBUG( "hydra.worker", std::this_thread::get_id() << ": Consider child " << child );
			if ( child->getLatestBTLevel() >= t->btInfo.btLevel && carl::set_have_intersection( child->getTimestamp( t->btInfo.btLevel ), transitionTimingPair.second ) ) {
				DEBUG( "hydra.worker", std::this_thread::get_id() << ": Timestamp matches, create follow-up task." );
				TaskType newTask( new Task<State>( child ) );
				newTask->btInfo = t->btInfo;
				newTask->btInfo.currentBTPosition += 2;
				DEBUG( "hydra.worker", "Enqueue follow up child with tree node " << child << " to local CEX queue." );
				if ( !SettingsProvider<State>::getInstance().useGlobalQueuesOnly() ) {
					localCEXQueue->nonLockingEnqueue( std::move( newTask ) );
				} else {
					localCEXQueue->enqueue( std::move( newTask ) );
				}
			}
		}
		DEBUG( "hydra.worker", std::this_thread::get_id() << ": Local CEX-Queue size: " << localCEXQueue->nonLockingSize() << "localCEXQueue is now:\n"
														  << localCEXQueue );
		t->treeNode->getMutex().unlock();
		return false;
	}

	// If a node is set to empty, skip this node. This can happen, if the number of child-nodes has changed upon refinement - in this case
	// we do not erase subtrees but rather set the particular level to empty.
	if ( t->treeNode->getRefinements().at( t->btInfo.btLevel ).isEmpty ) {
		t->treeNode->getMutex().unlock();
		return false;
	}

	return true;
}
}  // namespace hypro
