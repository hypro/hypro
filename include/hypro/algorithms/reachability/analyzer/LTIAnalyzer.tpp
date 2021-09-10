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

		if ( mParameters.detectJumpFixedPoints && !currentNode->getInitialBoundingBox() ) {
			currentNode->setBoundingBox( Converter<Number>::toBox( currentNode->getInitialSet() ).intervals() );
		}

		// bounded time evolution
		safetyResult = worker.computeTimeSuccessors( currentNode->getInitialSet(), currentNode->getLocation(), std::back_inserter( currentNode->getFlowpipe() ) );

		if ( safetyResult == REACHABILITY_RESULT::UNKNOWN ) {
			return { Failure{ currentNode } };
		}

		// Do not perform discrete jump if jump depth was reached
		if ( currentNode->getDepth() == mFixedParameters.jumpDepth ) {
			COUNT( "Unfinished branches" );
			continue;
		}

		// create jump successor tasks
		for ( const auto& [transition, timedValuationSets] : worker.computeJumpSuccessors( currentNode->getFlowpipe(), currentNode->getLocation() ) ) {
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
					fixedPointReached = detectJumpFixedPoint( childNode, mRoots );
				}

				// set bounding box to speed up search in case the option is enabled
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
