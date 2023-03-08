/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "LTIAnalyzer.h"

#include <algorithm>
#include <vector>

namespace hypro {

template <typename State, typename Automaton, typename Heuristics, typename Multithreading>
auto LTIAnalyzer<State, Automaton, Heuristics, Multithreading>::run() -> LTIResult {
	DEBUG( "hypro.reachability", "Start LTI Reachability Analysis." );
	if ( std::is_same_v<Multithreading, UseMultithreading> ) {
		mIdle = std::vector( mNumThreads, false );
		for ( int i = 0; i < mNumThreads; i++ ) {
			mThreads.push_back( std::thread( [this, i]() {
				TimeTransformationCache<LocationT> transformationCache;
				LTIWorker<State, Automaton> worker{
					  *mHybridAutomaton,
					  mParameters,
					  mFixedParameters.localTimeHorizon,
					  transformationCache };
				ReachTreeNode<State, LocationT>* currentNode;
				while ( !mTerminate ) {
					{
						std::unique_lock<std::mutex> lock( mQueueMutex );

						mQueueNonEmpty.wait( lock, [this]() {
							// TODO I am not sure, whether we need to lock here to access the queue
							return !mWorkQueue.empty() || mTerminate;
						} );
						{
							if ( mTerminate ) {
								break;
							}
							// TODO I do not think we need the idle lock, since we already have the queue lock
							std::unique_lock<std::mutex> idleLock{ mIdleWorkerMutex };
							mIdle[i] = false;
							std::cout << "Thread " << i << " is not idle." << std::endl;
						}
						currentNode = getNodeFromQueue();
						DEBUG( "hypro.reachability", "Processing node @" << currentNode << " with path " << currentNode->getPath() );
					}

					auto result = processNode( worker, currentNode, transformationCache );
					if ( result.isFailure() ) {
						std::cout << "Thread " << i << " declares analysis failed." << std::endl;
						mTerminate = true;
						break;
					}
					{
						std::unique_lock<std::mutex> idleLock{ mIdleWorkerMutex };
						std::cout << "Thread " << i << " is idle." << std::endl;
						mIdle[i] = true;
						mAllIdle.notify_all();
					}
				}
				std::cout << "Thread " << i << " terminates." << std::endl;
			} ) );
		}
		// wait();
		shutdown();
	} else {
		TimeTransformationCache<LocationT> transformationCache;
		LTIWorker<State, Automaton> worker{
			  *mHybridAutomaton,
			  mParameters,
			  mFixedParameters.localTimeHorizon,
			  transformationCache };
		while ( !mWorkQueue.empty() ) {
			auto* currentNode = getNodeFromQueue();
			DEBUG( "hypro.reachability", "Process node (@" << currentNode << ") with location " << currentNode->getLocation()->getName() << " with path " << currentNode->getTreePath() << " with heursitics value " << Heuristics{}.getValue( currentNode ) )
			auto result = processNode( worker, currentNode, transformationCache );
			if ( result.isFailure() ) {
				DEBUG( "hypro.reachability", "End LTI Reachability Analysis." );
				return result;
			}
		}
		DEBUG( "hypro.reachability", "End LTI Reachability Analysis." );
		return { LTISuccess{} };
	}
}

template <typename State, typename Automaton, typename Heuristics, typename Multithreading>
auto LTIAnalyzer<State, Automaton, Heuristics, Multithreading>::processNode( LTIWorker<State, Automaton>& worker, ReachTreeNode<State, LocationT>* node, TimeTransformationCache<LocationT>& transformationCache ) -> LTIResult {
	REACHABILITY_RESULT safetyResult;

	// set bounding box required for fixed-point test
	if ( mParameters.detectJumpFixedPoints && !node->getInitialBoundingBox() ) {
		node->setBoundingBox( Converter<Number>::toBox( node->getInitialSet() ).intervals() );
	}

	// bounded time evolution
	if ( mFixedParameters.globalTimeHorizon > 0 ) {
		// the number of required segments is the difference of the number of segments required to reach the global time horizon and the minimally current covered number of segments
		SegmentInd segmentsToCompute = std::ceil( std::nextafter( carl::convert<tNumber, double>( mFixedParameters.globalTimeHorizon / mParameters.timeStep ), std::numeric_limits<double>::infinity() ) ) - node->getTimings().lower();
		DEBUG( "hypro.reachability", "Start to compute " << segmentsToCompute << " segments." );
		if ( segmentsToCompute < 0 ) {
			segmentsToCompute = 0;
		}
		safetyResult = worker.computeTimeSuccessors( node->getInitialSet(), node->getLocation(), std::back_inserter( node->getFlowpipe() ), segmentsToCompute );
	} else {
		safetyResult = worker.computeTimeSuccessors( node->getInitialSet(), node->getLocation(), std::back_inserter( node->getFlowpipe() ) );
	}

	// check, whether the full time horizon has been exploited - if not, an invariant has bound the evolution and we might have a timelock
	bool timeElapseBoundedByModel = false;
	TRIBOOL timelock = TRIBOOL::NSET;  // is set to false if there is a transition that is enabled in the last segment
	if ( node->getFlowpipe().size() != worker.maxNumberSegments() ) {
		DEBUG( "hypro.reachability", "Node has a potential timelock as the time elapse was bounded by the model" );
		timeElapseBoundedByModel = true;
	} else {
		// we could compute as many segments as requested, but it is unclear, whether a timelock will happen in the future
		timelock = TRIBOOL::NSET;
	}

	// test containment of the first n (=2) segments against all other nodes' first m (=12) segments (with the same location)
	if ( mParameters.numberSetsForContinuousCoverage > 0 ) {
		detectContinuousFixedPoints( *node, mRoots, mParameters.numberSetsForContinuousCoverage );
		// if the previous fixed-point test was successful, skip computation
		if ( node->hasFixedPoint() == TRIBOOL::TRUE ) {
			DEBUG( "hypro.reachability", "Node has a fixed point, skip computation" );
			return { LTISuccess{} };
		}
	}

	if ( safetyResult == REACHABILITY_RESULT::UNKNOWN ) {
		DEBUG( "hypro.reachability", "Node is potentially unsafe" );
		node->flagUnsafe();
		return { Failure{ node } };
	}

	// Do not perform discrete jump if jump depth was reached
	if ( node->getDepth() == mFixedParameters.jumpDepth ) {
		DEBUG( "hypro.reachability", "Node is at maximal jump depth" );
		return { LTISuccess{} };
	}

	// collect potential Zeno transitions
	std::vector<const TransitionT*> ZenoTransitions{};
	if ( mParameters.detectZenoBehavior && node->getParent() != nullptr ) {
		// ZenoTransitions = getZenoTransitions( currentNode->getParent(), currentNode );
		ZenoTransitions = getZenoTransitions( node );
	}

	// create jump successor tasks
	for ( const auto& [transition, timedValuationSets] : worker.computeJumpSuccessors( node->getFlowpipe(), node->getLocation() ) ) {
		// Omit Zeno-transitions
		if ( mParameters.detectZenoBehavior && std::find( std::begin( ZenoTransitions ), std::end( ZenoTransitions ), transition ) != std::end( ZenoTransitions ) ) {
			DEBUG( "hypro.reachability", "Node-successor via transition " << transition->getSource()->getName() << " -> " << transition->getTarget()->getName() << " is on a Zeno-cycle" );
			continue;
		}

		for ( const auto [valuationSet, segmentsInterval] : timedValuationSets ) {
			// update reachTree
			// convert local time to global time
			carl::Interval<SegmentInd> const& initialSetDuration = node->getTimings();
			// add one to upper to convert from segment indices to time points
			// multiply by timeStepFactor to convert from analyzer specific timeStep to fixedTimeStep
			carl::Interval<SegmentInd> enabledDuration{ segmentsInterval.lower() * mParameters.timeStepFactor, ( segmentsInterval.upper() + 1 ) * mParameters.timeStepFactor };
			carl::Interval<TimePoint> globalDuration{ initialSetDuration.lower() + enabledDuration.lower(), initialSetDuration.upper() + enabledDuration.upper() };
			// if this transition is enabled in the last segment of a flowpipe which is bounded by an invariant, we do not have a timelock
			if ( timeElapseBoundedByModel && enabledDuration.upper() == node->getFlowpipe().size() ) {
				DEBUG( "hypro.reachability", "Node does not have a timelock" );
				timelock = TRIBOOL::FALSE;
			}
			// in any case add node to the search tree
			ReachTreeNode<State, LocationT>& childNode = node->addChild( valuationSet, globalDuration, transition );
			// if desired, try to detect fixed-point
			bool fixedPointReached = mParameters.detectJumpFixedPoints;
			auto boundingBox = std::vector<carl::Interval<Number>>{};
			if ( mParameters.detectJumpFixedPoints ) {
				boundingBox = Converter<Number>::toBox( childNode.getInitialSet() ).intervals();
				fixedPointReached = detectJumpFixedPoint( childNode, mRoots, mCallbacks.fixedPointCallback, mParameters.detectFixedPointsByCoverage, mParameters.numberSetsForContinuousCoverage );
			}

			// set bounding box to speed up search in case the option is enabled.
			// IMPORTANT: This has to be done *after* fp-detection to ensure that the node does not consider itself during fp-detection
			if ( mParameters.detectJumpFixedPoints ) {
				childNode.setBoundingBox( boundingBox );
			}
			// create Task, push only to queue, in case no fixed-point has been detected or detection is disabled
			if ( !fixedPointReached ) {
				DEBUG( "hypro.reachability", "Add node-successor (@ " << &childNode << ") to work-queue, path: " << childNode.getPath() );
				addToQueue( &childNode );
				// mWorkQueue.push_front( &childNode );
			} else {
				DEBUG( "hypro.reachability", "Fixed point detected in node-successor" );
				COUNT( "Finished branches (fixed-point)" );
			}
		}
	}

	// detect fixed points in continuous behavior (locally), only if the node does not have any child nodes. Otherwise, the detected fixed point can be evaded by taking a discrete jump.
	if ( mParameters.detectContinuousFixedPointsLocally && node->getChildren().empty() ) {
		for ( auto cur = std::begin( node->getFlowpipe() ); cur != std::end( node->getFlowpipe() ); ++cur ) {
			for ( auto succ = std::begin( node->getFlowpipe() ); succ != std::end( node->getFlowpipe() ); ++succ ) {
				if ( succ->contains( *cur ) ) {
					DEBUG( "hypro.reachability", "Detected continuous fixed point for current node" );
					node->setFixedPoint();
				}
			}
		}
	}
	// if the time elapse was bounded, but none of the outgoing transitions was enabled at the latest point of the time elapse, we encountered a timelock
	if ( timeElapseBoundedByModel && timelock == TRIBOOL::NSET ) {
		timelock = TRIBOOL::TRUE;
	}

	// set timelock flag
	node->flagTimelock( timelock );
	// if node has no children, the node can be flagged as having a fixed point
	if ( node->getChildren().empty() ) {
		node->setFixedPoint( true );
	}

	return { LTISuccess{} };
}

}  // namespace hypro
