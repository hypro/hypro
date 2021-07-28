#include "UrgencyCEGARAnalyzer.h"


namespace hypro {

template <typename Representation>
auto UrgencyCEGARAnalyzer<Representation>::run() -> UrgencyCEGARResult {
    TimeTransformationCache<Number> transformationCache;
    UrgencyWorker<Representation> worker{
          *mHybridAutomaton,
          mParameters,
          mFixedParameters.localTimeHorizon,
          transformationCache };
    UrgencyRefinementAnalyzer<Representation> refinementAnalyzer( mHybridAutomaton, mFixedParameters, mParameters, mRoots );

    while ( !mWorkQueue.empty() ) {
        auto currentNode = mWorkQueue.back();
        mWorkQueue.pop_back();

        auto safetyResult = worker.computeTimeSuccessors( *currentNode );
        worker.insertFlowpipe( *currentNode );

        if ( safetyResult == REACHABILITY_RESULT::UNKNOWN ) {
            refinementAnalyzer.setRefinement( currentNode );
            auto refineResult = refinementAnalyzer.run();
            if ( refineResult.isSuccess() ) {
                for ( auto successor : refineResult.success().pathSuccessors ) {
                    mWorkQueue.push_front( successor );
                }
            } else {
                return { Failure{ refineResult.failure().conflictNode } };
            }
        } else {
            worker.insertFlowpipe( *currentNode );
            //Do not perform discrete jump if jump depth was reached
            if ( currentNode->getDepth() == mFixedParameters.jumpDepth ) continue;
            // create jump successor tasks
            for ( const auto& [transition, timedValuationSets] : worker.computeJumpSuccessors( *currentNode ) ) {
                for ( const auto jsucc : timedValuationSets ) {
                    // create Task
                    auto childNode = createChildNode( jsucc, transition, currentNode );
                    mWorkQueue.push_front( childNode );
                }
            }
        }

    }
    return { UrgencyCEGARSuccess{} };
}

template <typename Representation>
ReachTreeNode<Representation>* UrgencyCEGARAnalyzer<Representation>::createChildNode( 
        const TimedValuationSet<Representation>& jsucc, const Transition<Number>* transition, ReachTreeNode<Representation>* parent ) {
    carl::Interval<SegmentInd> const& initialSetDuration = parent->getTimings();
    // add one to upper to convert from segment indices to time points
    // multiply by timeStepFactor to convert from analyzer specific timeStep to fixedTimeStep
    carl::Interval<SegmentInd> enabledDuration{
        jsucc.time.lower() * mParameters.timeStepFactor,
        ( jsucc.time.upper() + 1 ) * mParameters.timeStepFactor };
    carl::Interval<TimePoint> globalDuration{
        initialSetDuration.lower() + enabledDuration.lower(),
        initialSetDuration.upper() + enabledDuration.upper() };

    ReachTreeNode<Representation>& childNode = parent->addChild( jsucc.valuationSet, globalDuration, transition );
    return &childNode;
}
} // namespace hypro