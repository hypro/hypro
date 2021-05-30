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
            Path<Number> currentPath = currentNode->getPath();
            auto failureNode = currentNode;
            while( true ) {
                RefinePoint refine = findRefinementNode( failureNode );
                if ( refine.node == nullptr ) {
                    return { Failure{ currentNode } };
                } else {
                    auto refinedNode = createRefinedNode( refine );
                    auto refineResult = refinePath( refinedNode, currentPath, mMaxSegments );
                    if ( refineResult.isSuccess() ) {
                        // push unexplored node to the global queue
                        for ( auto successor : refineResult.success().pathSuccessors ) {
                            mWorkQueue.push_front( successor );
                        }
                        break;
                    } else {
                        failureNode = refineResult.failure().conflictNode;
                    }
                }
            }
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
auto UrgencyCEGARAnalyzer<Representation>::findRefinementNode( ReachTreeNode<Representation>* const unsafeNode )
    -> RefinePoint {

    // collect nodes on path
    std::vector<ReachTreeNode<Representation>*> nodePath( unsafeNode->getDepth() + 1 );
    auto n = unsafeNode;
    for ( int depth = unsafeNode->getDepth(); depth >= 0; --depth ) {
        assert( n != nullptr );
        nodePath[ depth ] = n;
        n = n->getParent();
    }

    auto path = unsafeNode->getPath();
    for ( auto it = nodePath.begin(); it != nodePath.end(); ++it ) {
        for ( auto trans : mHybridAutomaton->getTransitions() ) {
            // check all urgent, outgoing and unrefined transitions
            auto candidate = *it;
            if ( trans->getSource() != candidate->getLocation() ) {
                continue;
            }
            if ( !trans->isUrgent() ) {
                continue;
            }
            auto urgent = candidate->getUrgent();
            if ( std::find( urgent.begin(), urgent.end(), trans ) != urgent.end() ) {
                continue;
            }
            // check if guard intersection is unsafe on path to node
            if ( guardUnsafe( candidate, path.tail( unsafeNode->getDepth() - candidate->getDepth() ), trans ) ) {
                return RefinePoint{ candidate, trans };
            }
        }       
    }
    return RefinePoint{ nullptr, nullptr };
}

template <typename Representation>
bool UrgencyCEGARAnalyzer<Representation>::guardUnsafe(
        ReachTreeNode<Representation>* const start, const Path<Number>& pathToUnsafe, Transition<Number>* refineJump ) {
    // flowpipe can be fragmented from earlier refinement (multiple simultaneous segments)
    bool splitFp = !start->getUrgent().empty();
    assert( ( !splitFp || start->getFlowpipe().size() == start->getFpTimings().size() ) );

    // collect intersection of segments with guard and number of timesteps to compute for each segment
    std::vector<ReachTreeNode<Representation>> tasks;
    for ( std::size_t fpIndex = 0; fpIndex < start->getFlowpipe().size(); ++fpIndex ) {
        // todo: intersect with preimage of invariant in new location
        auto [containment, initial] = intersect( start->getFlowpipe()[ fpIndex ], refineJump->getGuard() );
        if ( containment == CONTAINMENT::NO ) {
            continue;
        } else if ( containment == CONTAINMENT::FULL ) {
            return true;
        } else {
            // timing offset
            auto segmentIndex = splitFp ? start->getFpTimings()[ fpIndex ] : fpIndex;
            carl::Interval<SegmentInd> segmentOffset(
                start->getTimings().lower() + segmentIndex, start->getTimings().upper() + segmentIndex );
            // todo: set urgency?
            ReachTreeNode<Representation> task( start->getLocation(), initial, segmentOffset );
            tasks.push_back( std::move( task ) );
        }
    }

    for ( auto& task : tasks ) {
        auto timeHorizon = mMaxSegments - ( task.getTimings().lower() - start->getTimings().lower() );
        if ( !refinePath( &task, pathToUnsafe, timeHorizon ).isSuccess() ) {
            return true;
        }
    }
    return false;
}

template <typename Representation>
ReachTreeNode<Representation>* UrgencyCEGARAnalyzer<Representation>::createRefinedNode( const RefinePoint& refine ) {
    auto parent = refine.node->getParent();
    std::set<Transition<Number>*> urgentTransitions = refine.node->getUrgent();
    urgentTransitions.insert( refine.transition );
    // check if refined node already exists
    if ( parent == nullptr ) {
        for ( auto& sibling : mRoots ) {
            if ( refine.node->getTimings() == sibling.getTimings() &&
                    urgentTransitions == sibling.getUrgent() &&
                    refine.node->getInitialSet() == sibling.getInitialSet() ) {
                return &sibling;
            }
        }
    } else {
        for ( auto sibling : parent->getChildren() ) {
            if ( refine.node->getTransition() == sibling->getTransition() &&
                    refine.node->getTimings() == sibling->getTimings() &&
                    urgentTransitions == sibling->getUrgent() &&
                    refine.node->getInitialSet() == sibling->getInitialSet() ) {
                    assert( sibling->getFlowpipe().size() > 0 );
                return sibling;
            }
        }
    }

    // refined node does not exist, so it is created
    if ( parent == nullptr ) {
        ReachTreeNode<Representation> refinedNode(
            refine.node->getLocation(),
            refine.node->getInitialSet(),
            refine.node->getTimings() );
        refinedNode.setUrgent( urgentTransitions );
        mRoots.push_back( std::move( refinedNode ) );
        return &mRoots.back();
    }
    ReachTreeNode<Representation>& refinedNode = parent->addChild(
        refine.node->getInitialSet(),
        refine.node->getTimings(),
        refine.node->getTransition() );
    refinedNode.setUrgent( urgentTransitions );
    return &refinedNode;
}

template <typename Representation>
auto UrgencyCEGARAnalyzer<Representation>::refinePath(
        ReachTreeNode<Representation>* refinedNode, const Path<Number>& path, std::size_t initialTimeHorizon )
        -> RefinementResult {

    if ( refinedNode->getFlowpipe().empty() ) {
        auto safety = mRefinementWorker->computeForwardReachability( *refinedNode, initialTimeHorizon );
        std::vector<Representation>& flowpipe = refinedNode->getFlowpipe();
        auto& timings = refinedNode->getFpTimings();
        for ( auto& timedSegment : mRefinementWorker->getFlowpipe() ) {
            flowpipe.push_back( timedSegment.valuationSet );
            timings.push_back( timedSegment.index );
        }
        if ( safety == REACHABILITY_RESULT::UNKNOWN ) {
            return { Failure<Representation>{ refinedNode } };
        } else {
            for ( const auto& [transition, timedValuationSets] : mRefinementWorker->getJumpSuccessors() ) {
                for ( const auto jsucc : timedValuationSets ) {
                    createChildNode( jsucc, transition, refinedNode );
                }
            }
        }
    }

    // refined node is at the end of the path and it is safe
    if ( refinedNode->getPath().elements == path.elements ) {
        std::vector<ReachTreeNode<Representation>*> successors;
        for ( auto succ : refinedNode->getChildren() ) {
            successors.push_back( succ );
        }
        return { RefinementSuccess{ successors } };
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
        return { RefinementSuccess<Representation>{} };
    }

    // refinementAnalyzer continues computation along the rest of the path, starting from refinedNode
    auto pathTail = path.tail( path.elements.size() - refinedNode->getDepth() );

    RefinementAnalyzer<Representation> refinementAnalyzer( *mHybridAutomaton, mFixedParameters, mParameters );
    refinementAnalyzer.setRefinement( refinedNode, pathTail );
    return refinementAnalyzer.run();
}
} // namespace hypro