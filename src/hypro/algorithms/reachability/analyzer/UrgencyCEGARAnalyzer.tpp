#include "UrgencyCEGARAnalyzer.h"


namespace hypro {

template <typename Representation>
auto UrgencyCEGARAnalyzer<Representation>::run() -> UrgencyCEGARResult {
    TimeTransformationCache<Number> transformationCache;
    LTIWorker<Representation> worker{
          *mHybridAutomaton,
          mParameters,
          mFixedParameters.localTimeHorizon,
          transformationCache };

    while ( !mWorkQueue.empty() ) {
        auto currentNode = mWorkQueue.back();
        mWorkQueue.pop_back();

        auto safetyResult = worker.computeTimeSuccessors(
            currentNode->getInitialSet(),
            currentNode->getLocation(),
            std::back_inserter( currentNode->getFlowpipe() ) );

        if ( safetyResult == REACHABILITY_RESULT::UNKNOWN ) {
            RefinePoint refine = findRefinementNode( currentNode );
            if ( refine.node == nullptr ) {
                return { Failure{ currentNode } };
            }
            Path<Number> currentPath = currentNode->getPath();
            bool verified;
            do {
                std::tie( verified, refine ) = refinePath( currentPath, refine );
                if ( refine.node == nullptr ) {
                    return { Failure{ currentNode } };
                }
            } while ( !verified );
        } else {
            //Do not perform discrete jump if jump depth was reached
            if ( currentNode->getDepth() == mFixedParameters.jumpDepth ) continue;
            // create jump successor tasks
            for ( const auto& [transition, timedValuationSets] : worker.computeJumpSuccessors( currentNode->getFlowpipe(), currentNode->getLocation() ) ) {
                for ( const auto jsucc : timedValuationSets ) {
                    // create Task
                    auto childNode = createChildNode( jsucc, transition, currentNode );
                    mWorkQueue.push_front( childNode );
                }
            }
        }

    }

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

template <typename Representation>
auto UrgencyCEGARAnalyzer<Representation>::findRefinementNode( const ReachTreeNode<Representation>* node )
    -> RefinePoint {
    assert( false && "findRefinementNode not implemented yet" );
    return RefinePoint{ nullptr, nullptr };
}


template <typename Representation>
ReachTreeNode<Representation>* UrgencyCEGARAnalyzer<Representation>::refineNode( const RefinePoint& refine ) {
    auto parent = refine.node->getParent();
    std::vector<Transition<Number>*> urgentTransitions = refine.node->getUrgent();
    urgentTransitions.push_back( refine.transition );
    // check if refined node already exists
    for ( auto sibling : parent->getChildren() ) {
        if ( refine.node->getTransition() == sibling->getTransition() &&
             refine.node->getTimings() == sibling->getTransition() &&
             sibling->getUrgent() == urgentTransitions &&
             refine.node->getInitialSet() == sibling->getInitialSet() ) {
            assert( sibling->getFlowpipe().size() > 0 );
            return sibling;
        }
    }
    // refined node does not exist, so it is created
    auto refinedNode = parent->addChild(
        refine.node->getInitialSet(),
        refine.node->getTimings(),
        refine.node->getTransition() );
    refinedNode->setUrgent( urgentTransitions );
    return refinedNode;
}

template <typename Representation>
auto UrgencyCEGARAnalyzer<Representation>::refinePath( const Path<Number>& path, const RefinePoint& refine )
  -> std::pair<bool, RefinePoint> {

    auto refinedNode = refineNode( refine );
    if ( refinedNode->getFlowpipe().empty() ) {
        // compute successors
        // todo: reuse cache and worker
        TimeTransformationCache<Number> transformationCache;
        UrgencyWorker<Representation> urgencyWorker{
              *mHybridAutomaton,
              mParameters,
              mFixedParameters.localTimeHorizon,
              transformationCache };

        auto safety = urgencyWorker.computeTimeSuccessors( *refinedNode );
        if ( safety != REACHABILITY_RESULT::SAFE ) {
            return std::make_pair( false, findRefinementNode( refinedNode ) );
        }
        // create children
        urgencyWorker.computeJumpSuccessors( *refinedNode );
        for ( const auto& [transition, timedValuationSets] : urgencyWorker.getJumpSuccessors() ) {
            for ( const auto jsucc : timedValuationSets ) {
                createChildNode( jsucc, transition, refinedNode );
            }
        }
    }

    // refined node is at the end of the path and it is safe
    if ( refinedNode->getPath().elements == path.elements ) {
        for ( auto childNode : refinedNode->getChildren() ) {
            mWorkQueue.push_front( childNode );
            return std::make_pair( true, refine );
        }
    }

    // check that the transition on path can be taken
    bool matched = false;
    for ( auto childNode : refinedNode->getChildren() ) {
        if ( childNode->getTransition() == path.elements.at( refinedNode->getDepth() ).second ) {
            matched = true;
            break;
        }
    }
    if ( !matched ) {
        // path is not reachable
        return std::make_pair( true, refine );
    }

    // refinementAnalyzer continues computation along the rest of the path, starting from refinedNode
    auto [pathPrefix, pathSuffix] = path.split( refinedNode->getDepth() );
    assert( pathPrefix.elements == refinedNode->getPath().elements );
    assert( pathSuffix.rootLocation == refinedNode->getLocation() );

    auto refinementAnalyzer = RefinementAnalyzer<Representation>{
        *mHybridAutomaton,
        mFixedParameters,
        mParameters };

    refinementAnalyzer.setRefinement( refinedNode, pathSuffix );
    auto res = refinementAnalyzer.run();
    if ( res.isSuccess() ) {
        // push unexplored node to the global queue
        for ( auto successor : res.success().pathSuccessors ) {
            mWorkQueue.push_front( successor );
            return std::make_pair ( true, refine );
        }
    } else {
        return std::make_pair( false, findRefinementNode( res.failure().conflictNode ) );
    }
}
} // namespace hypro