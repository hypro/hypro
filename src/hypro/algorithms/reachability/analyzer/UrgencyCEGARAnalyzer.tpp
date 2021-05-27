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
    UrgencyWorker<Representation> urgencyWorker{
          *mHybridAutomaton,
          mParameters,
          mFixedParameters.localTimeHorizon,
          transformationCache };
    mRefinementWorker = &urgencyWorker;

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

template <typename Representation>
auto UrgencyCEGARAnalyzer<Representation>::findRefinementNode( ReachTreeNode<Representation>* const node )
    -> RefinePoint {
    
    std::vector<ReachTreeNode<Representation>*> nodePath{ node };
    for ( auto currentNode = node; currentNode != nullptr; currentNode = currentNode->getParent() ) {
        nodePath.push_back( currentNode );
    }

    auto path = node->getPath();
    for ( auto it = nodePath.rbegin(); it != nodePath.rend(); ++it ) {
        for ( auto trans : mHybridAutomaton->getTransitions() ) {
            if ( trans->getSource() != ( *it )->getLocation() ) {
                continue;
            }
            // check if transition is urgent
            if ( !trans->isUrgent() ) {
                continue;
            }
            // check if transition is unrefined
            auto refined = ( *it )->getUrgent();
            if ( std::find( refined.begin(), refined.end(), trans ) != refined.end() ) {
                continue;
            }
            // check if guard intersection is unsafe on path to node
            if ( checkGuard( *it, trans, path ) == REACHABILITY_RESULT::UNKNOWN ) {
                return RefinePoint{ *it, trans };
            }
        }       
    }
    return RefinePoint{ nullptr, nullptr };
}

template <typename Representation>
REACHABILITY_RESULT UrgencyCEGARAnalyzer<Representation>::checkGuard(
        ReachTreeNode<Representation>* const node, Transition<Number>* trans, const Path<Number>& path ) {
    // path is from node to unsafe
    // check if flowpipe is fragmented, because in that case need to check timing of segments
    bool split = !node->getUrgent().empty();
    assert( ( !split || node->getFlowpipe().size() == node->getFpTimings().size() ) );

    // iterate over segments
    for ( std::size_t fpIndex = 0; fpIndex < node->getFlowpipe().size(); ++fpIndex ) {
        std::size_t segmentCount;
        std::size_t segmentIndex = split ? node->getFpTimings()[ fpIndex ] : fpIndex;
        assert( segmentIndex <= path.elements[ 0 ].first.lower() );
        segmentCount = mMaxSegments - segmentIndex;
        auto [containment, initialSet] = intersect( node->getFlowpipe()[ fpIndex ], trans->getGuard() );
        if ( containment == CONTAINMENT::NO ) {
            continue;
        } else if ( containment == CONTAINMENT::FULL ) {
            // segment is contained in guard. Since segment is unsafe on path, so is the guard.
            return REACHABILITY_RESULT::UNKNOWN;
        } else {
            ReachTreeNode<Representation> guardNode( node->getLocation(), initialSet, carl::Interval<SegmentInd>( 0 ) );
            mRefinementWorker->reset();
            auto safetyResult = mRefinementWorker->computeTimeSuccessors( guardNode, segmentCount );
            if ( safetyResult == REACHABILITY_RESULT::UNKNOWN ) {
                return REACHABILITY_RESULT::UNKNOWN;
            }
            Path guardPath = path;
            guardPath.elements[ 0 ].first -= carl::Interval<SegmentInd>( segmentIndex );
            mRefinementAnalyzer.setRefinement( &guardNode, guardPath );
            if ( !mRefinementAnalyzer.run().isSuccess() ) {
                return REACHABILITY_RESULT::UNKNOWN;
            }
        }
    }
    return REACHABILITY_RESULT::SAFE;
}

template <typename Representation>
ReachTreeNode<Representation>* UrgencyCEGARAnalyzer<Representation>::refineNode( const RefinePoint& refine ) {
    auto parent = refine.node->getParent();
    assert( parent != nullptr && "Parent of refine node is null" ); // todo: what if parent is null?
    std::set<Transition<Number>*> urgentTransitions = refine.node->getUrgent();
    urgentTransitions.insert( refine.transition );
    // check if refined node already exists
    for ( auto sibling : parent->getChildren() ) {
        if ( refine.node->getTransition() == sibling->getTransition() &&
             refine.node->getTimings() == sibling->getTimings() &&
             sibling->getUrgent() == urgentTransitions &&
             refine.node->getInitialSet() == sibling->getInitialSet() ) {
            assert( sibling->getFlowpipe().size() > 0 );
            return sibling;
        }
    }
    // refined node does not exist, so it is created
    ReachTreeNode<Representation>& refinedNode = parent->addChild(
        refine.node->getInitialSet(),
        refine.node->getTimings(),
        refine.node->getTransition() );
    refinedNode.setUrgent( urgentTransitions );
    return &refinedNode;
}

template <typename Representation>
auto UrgencyCEGARAnalyzer<Representation>::refinePath( const Path<Number>& path, const RefinePoint& refine )
  -> std::pair<bool, RefinePoint> {

    auto refinedNode = refineNode( refine );
    if ( refinedNode->getFlowpipe().empty() ) {
        // compute successors
        mRefinementWorker->reset();
        auto safety = mRefinementWorker->computeTimeSuccessors( *refinedNode );
        if ( safety != REACHABILITY_RESULT::SAFE ) {
            return std::make_pair( false, findRefinementNode( refinedNode ) );
        }
        // create children
        mRefinementWorker->computeJumpSuccessors( *refinedNode );
        for ( const auto& [transition, timedValuationSets] : mRefinementWorker->getJumpSuccessors() ) {
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

    mRefinementAnalyzer.setRefinement( refinedNode, pathSuffix );
    auto res = mRefinementAnalyzer.run();
    if ( res.isSuccess() ) {
        // push unexplored node to the global queue
        for ( auto successor : res.success().pathSuccessors ) {
            mWorkQueue.push_front( successor );
            return std::make_pair ( true, refine );
        }
    }
    return std::make_pair( false, findRefinementNode( res.failure().conflictNode ) );
}
} // namespace hypro