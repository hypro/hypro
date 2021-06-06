#include "LTIAnalyzer.h"

namespace hypro {

template <typename State>
auto LTIAnalyzer<State>::run() -> LTIResult {
	//Setup settings for flowpipe construction in worker
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

		safetyResult = worker.computeTimeSuccessors( currentNode->getInitialSet(), currentNode->getLocation(), std::back_inserter( currentNode->getFlowpipe() ) );

		if ( safetyResult == REACHABILITY_RESULT::UNKNOWN ) {
			return { Failure{ currentNode } };
		}

		//Do not perform discrete jump if jump depth was reached
		if ( currentNode->getDepth() == mFixedParameters.jumpDepth ) continue;

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

				ReachTreeNode<State>& childNode = currentNode->addChild( valuationSet, globalDuration, transition );

				// create Task
				mWorkQueue.push_front( &childNode );
			}
		}
	}

	return { LTISuccess{} };
}

}  // namespace hypro
