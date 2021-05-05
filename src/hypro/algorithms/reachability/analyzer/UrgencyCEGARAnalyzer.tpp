#include "UrgencyCEGARAnalyzer.h"


namespace hypro {

template <typename Representation>
auto UrgencyCEGARAnalyzer<Representation>::run() -> UrgencyCEGARResult {
    TimeTransformationCache<Number> transformationCache;
    UrgencyWorker<State> worker{
          *mHybridAutomaton,
          mParameters,
          mFixedParameters.localTimeHorizon,
          transformationCache };

    while ( !mWorkQueue.empty() ) {
        auto currentNode = mWorkQueue.back();
        mWorkQueue.pop_back();

        auto safetyResult = worker.computeTimeSuccessors( *currentNode );

        if ( safetyResult == REACHABILITY_RESULT::UNKNOWN ) {
            Path<Number> currentPath = currentNode->getPath();
            auto [refineNode, refineTransition] = findRefinementNode( currentNode );
            if ( refineNode == nullptr ) {
                return { Failure{ currentNode } };
            }
            do {
                // todo: struct for {refineNode, refineTransition}
                auto [verified, refineNode, refineTransition] = refinePath( currentPath, refineNode, refineTransition );
                if ( refineNode == nullptr ) {
                    return {Failure{ currentNode } };
                }
            } while ( !verified );
        } else {
            //Do not perform discrete jump if jump depth was reached
            if ( currentNode->getDepth() == mFixedParameters.jumpDepth ) continue;
            // create jump successor tasks
            for ( const auto& [transition, timedValuationSets] : worker.computeJumpSuccessors( *currentNode ) ) {
                for ( const auto [valuationSet, segmentsInterval] : timedValuationSets ) {
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

    }

}

template <typename Representation>
auto UrgencyCEGARAnalyzer<Representation>::findRefinementNode( ReachTreeNode<Representation>* node )
    -> std::pair<ReachTreeNode<Representation>*, Transition<Number>*> {
    return std::make_pair( nullptr, nullptr );
}


template <typename Representation>
auto UrgencyCEGARAnalyzer<Representation>::refinePath( Path<Number> path, ReachTreeNode<Representation>* refineNode, Transition<Number>* refineTrans )
  -> std::tuple<bool, ReachTreeNode<Representation>*, Transition<Number>*> {
    return std::tuple( false, refineNode, refineTrans );
}
} // namespace hypro