/*
 * Copyright (c) 2021.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "LTIAnalyzer.h"

#include <algorithm>
#include <vector>

namespace hypro {

template <typename State>
auto LTIAnalyzer<State>::run() -> LTIResult {
	// Setup settings for flowpipe construction in worker
	TimeTransformationCache<Number> transformationCache;
	LTIWorker<State> worker{
		  *mHybridAutomaton,
		  mParameters,
		  mFixedParameters.localTimeHorizon,
		  transformationCache };

	while ( !mWorkQueue.empty() ) {
		ReachTreeNode<State>* currentNode = mWorkQueue.back();
		mWorkQueue.pop_back();
		REACHABILITY_RESULT safetyResult;

		// set bounding box required for fixed-point test
		if ( mParameters.detectJumpFixedPoints && !currentNode->getInitialBoundingBox() ) {
			currentNode->setBoundingBox( Converter<Number>::toBox( currentNode->getInitialSet() ).intervals() );
		}

		// bounded time evolution
		safetyResult = worker.computeTimeSuccessors( currentNode->getInitialSet(), currentNode->getLocation(), std::back_inserter( currentNode->getFlowpipe() ) );

		// test containment of the first n (=2) segments against all other nodes' first m (=12) segments (with the same location)
		if ( mParameters.numberSetsForContinuousCoverage > 0 ) {
			detectContinuousFixedPoints( *currentNode, mRoots, mParameters.numberSetsForContinuousCoverage );
			// if the previous fixed-point test was successful, skip computation
			if ( currentNode->hasFixedPoint() == TRIBOOL::TRUE ) {
				continue;
			}
		}

		if ( safetyResult == REACHABILITY_RESULT::UNKNOWN ) {
			return { Failure{ currentNode } };
		}

		// Do not perform discrete jump if jump depth was reached
		if ( currentNode->getDepth() == mFixedParameters.jumpDepth ) {
			continue;
		}

		// collect potential Zeno transitions
		std::vector<const Transition<typename State::NumberType>*> ZenoTransitions{};
		if ( mParameters.detectZenoBehavior && currentNode->getParent() != nullptr ) {
			ZenoTransitions = getZenoTransitions( currentNode->getParent(), currentNode );
		}

		// create jump successor tasks
		for ( const auto& [transition, timedValuationSets] : worker.computeJumpSuccessors( currentNode->getFlowpipe(), currentNode->getLocation() ) ) {
			// Omit Zeno-transitions
			if ( mParameters.detectZenoBehavior && std::find( std::begin( ZenoTransitions ), std::end( ZenoTransitions ), transition ) != std::end( ZenoTransitions ) ) {
				continue;
			}

			for ( const auto [valuationSet, segmentsInterval] : timedValuationSets ) {
				// update reachTree

				// convert local time to global time
				carl::Interval<SegmentInd> const& initialSetDuration = currentNode->getTimings();
				// add one to upper to convert from segment indices to time points
				// multiply by timeStepFactor to convert from analyzer specific timeStep to fixedTimeStep
				carl::Interval<SegmentInd> enabledDuration{ segmentsInterval.lower() * mParameters.timeStepFactor, ( segmentsInterval.upper() + 1 ) * mParameters.timeStepFactor };
				carl::Interval<TimePoint> globalDuration{ initialSetDuration.lower() + enabledDuration.lower(), initialSetDuration.upper() + enabledDuration.upper() };

				// in any case add node to the search tree
				ReachTreeNode<State>& childNode = currentNode->addChild( valuationSet, globalDuration, transition );
				// if desired, try to detect fixed-point
				bool fixedPointReached = mParameters.detectJumpFixedPoints;
				auto boundingBox = std::vector<carl::Interval<Number>>{};
				if ( mParameters.detectJumpFixedPoints ) {
					boundingBox = Converter<Number>::toBox( childNode.getInitialSet() ).intervals();
					fixedPointReached = detectJumpFixedPoint( childNode, mRoots, mParameters.detectFixedPointsByCoverage );
				}

				// set bounding box to speed up search in case the option is enabled.
				// IMPORTANT: This has to be done *after* fp-detection to ensure that the node does not consider itself during fp-detection
				if ( mParameters.detectJumpFixedPoints ) {
					childNode.setBoundingBox( boundingBox );
				}
				// create Task, push only to queue, in case no fixed-point has been detected or detection is disabled
				if ( !fixedPointReached ) {
					mWorkQueue.push_front( &childNode );
				} else {
					COUNT( "Finished branches (fixed-point)" );
				}
			}
		}

		// detect fixed points in continuous behavior (locally), only if the node does not have any child nodes. Otherwise, the detected fixed point can be evaded by taking a discrete jump.
		if ( mParameters.detectContinuousFixedPointsLocally && currentNode->getChildren().empty() ) {
			for ( auto cur = std::begin( currentNode->getFlowpipe() ); cur != std::end( currentNode->getFlowpipe() ); ++cur ) {
				for ( auto succ = std::begin( currentNode->getFlowpipe() ); succ != std::end( currentNode->getFlowpipe() ); ++succ ) {
					if ( succ->contains( *cur ) ) {
						currentNode->setFixedPoint();
					}
				}
			}
		}
	}

	return { LTISuccess{} };
}

}  // namespace hypro
