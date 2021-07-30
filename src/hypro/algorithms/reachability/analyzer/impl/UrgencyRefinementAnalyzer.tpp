#include "UrgencyRefinementAnalyzer.h"

namespace hypro {

template <typename Representation>
struct UrgencyRefinementAnalyzer<Representation>::ChildNodeGen {
    std::vector<TimedValuationSet<Representation>> successors;
    ReachTreeNode<Representation>* parentNode;
    const Transition<typename Representation::NumberType>* transition;
    int timeStepFactor;
    UrgencyCEGARSettings refinementSettings;
    std::size_t successorIndex = 0;

    ReachTreeNode<Representation>* next() {
        if ( successorIndex >= successors.size() ) {
            return nullptr;
        }
        auto& [valuationSet, segmentsInterval] = successors[ successorIndex ];
        ++successorIndex;
        // convert local time to global time

        carl::Interval<TimePoint> const& initialSetDuration = parentNode->getTimings();
        // add one to upper to convert from segment indices to time points
        // multiply by timeStepFactor to convert from analyzer specific timeStep to fixedTimeStep
        carl::Interval<TimePoint> enabledDuration{ segmentsInterval.lower() * timeStepFactor, ( segmentsInterval.upper() + 1 ) * timeStepFactor };
        carl::Interval<TimePoint> globalDuration{ initialSetDuration.lower() + enabledDuration.lower(), initialSetDuration.upper() + enabledDuration.upper() };

        auto& child = parentNode->addChild( valuationSet, globalDuration, transition );
        // set minimal refinement level
        for ( auto const& trans : child.getLocation()->getTransitions() ) {
            if ( trans->isUrgent() ) {
                child.getUrgent()[ trans.get() ] = refinementSettings.minRefinementLevel();
            }
        }

        // refine urgent halfspaces fully
        if ( refinementSettings.refineHalfspaces ) {
            if ( refinementSettings.maxRefinementLevel() != refinementSettings.minRefinementLevel() ) {
                for ( auto const& trans : child.getLocation()->getTransitions() ) {
                    if ( trans->isUrgent() && trans->getJumpEnablingSet().getMatrix().size() == 1 ) {
                        child.getUrgent()[ trans.get() ] = refinementSettings.maxRefinementLevel();
                    }
                }
            }
        }
        return &child;
    }
};

template <typename Representation>
bool UrgencyRefinementAnalyzer<Representation>::matchesPathTiming( ReachTreeNode<Representation>* node ) {
    auto& timing = mPath.elements.at( node->getDepth() - 1 ).first;
    return node->getTimings().upper() >= timing.lower() && node->getTimings().lower() <= timing.upper();
}

template <typename Representation>
bool UrgencyRefinementAnalyzer<Representation>::matchesPathTransition( ReachTreeNode<Representation>* node ) {
    auto const* transition = mPath.elements.at( node->getDepth() - 1 ).second;
    return ( transition == node->getTransition() );
}

template <typename Representation>
auto UrgencyRefinementAnalyzer<Representation>::run() -> RefinementResult {
    //Setup settings for flowpipe construction in worker
    TimeTransformationCache<Number> transformationCache;
    UrgencyWorker<Representation> worker{
          *mHybridAutomaton,
          mParameters,
          mFixedParameters.localTimeHorizon,
          transformationCache };

    std::vector<ReachTreeNode<Representation>*> endOfPath{};
    std::vector<ReachTreeNode<Representation>*> refinedNodes{};

    RefinePoint refine = findRefinementNode( mFailureNode );
    if ( refine.node == nullptr ) {
        return { Failure{ mFailureNode } };
    }

    mWorkQueue.push_front( refineNode( refine ) );

    while ( !mWorkQueue.empty() ) {
        // pop node
        ReachTreeNode<Representation>* currentNode = mWorkQueue.back();
        mWorkQueue.pop_back();

        // skip descendants of refined nodes
        auto node = currentNode;
        bool ancestorRefined = false;
        while ( node != nullptr ) {
            if ( std::find( refinedNodes.begin(), refinedNodes.end(), node ) != refinedNodes.end() ) {
                ancestorRefined = true;
                break;
            }
            node = node->getParent();
        }
        if ( ancestorRefined ) continue;

        // if node is child of last node in path, collect it in return value
        if ( currentNode->getDepth() == mPath.elements.size() + 1 ) {
            endOfPath.push_back( currentNode );
            continue;
        }

        // compute flowpipe. if node was previously unsafe, flowpipe would not be empty
        if ( currentNode->getFlowpipe().empty() ) {
            REACHABILITY_RESULT safetyResult = worker.computeTimeSuccessors( *currentNode );
            worker.insertFlowpipe( *currentNode );
            currentNode->setSafety( safetyResult );
            worker.reset();
        }

        if ( currentNode->getSafety() == REACHABILITY_RESULT::UNKNOWN ) {
            refine = findRefinementNode( currentNode );
            if ( refine.node == nullptr ) {
                return { Failure{ currentNode } };
            }
            mWorkQueue.push_front( refineNode( refine ) );
            refinedNodes.push_back( currentNode );
            continue;
        }
        // do not perform discrete jump if jump depth was reached
        if ( currentNode->getDepth() == mFixedParameters.jumpDepth ) continue;

        // currentNode is last node in path, create and collect all children
        if ( currentNode->getDepth() == mPath.elements.size() ) {
            for ( const auto& successor : worker.computeJumpSuccessors( *currentNode ) ) {
                ChildNodeGen childGen{ successor.valuationSets, currentNode, successor.transition, mParameters.timeStepFactor, mRefinementSettings };
                while ( auto* child = childGen.next() ) {
                    endOfPath.push_back( child );
                }
            }
        } else {
            // continue along path

            // check if children already exist
            bool matchedOne = false;
            for ( auto* child : currentNode->getChildren() ) {
                if ( matchesPathTransition( child ) &&
                        std::all_of( child->getUrgent().begin(), child->getUrgent().end(), [this]( const auto& u ) {
                            return u.second == mRefinementSettings.minRefinementLevel(); } ) ) {
                    matchedOne = true;
                    // check against path
                    if ( matchesPathTiming( child ) ) {
                        mWorkQueue.push_front( child );
                    }
                }
            }

            if ( !matchedOne ) {
                for ( const auto& successor : worker.computeJumpSuccessors( *currentNode ) ) {
                    ChildNodeGen childGen{ successor.valuationSets, currentNode, successor.transition, mParameters.timeStepFactor, mRefinementSettings };
                    while ( auto* child = childGen.next() ) {
                        endOfPath.push_back( child );
                    }
                }
            }
        }
    }

    std::vector<ReachTreeNode<Representation>*> pathSuccessors{};
    for ( auto succ : endOfPath ) {
        bool ancestorRefined = false;
        auto node = succ;
        while ( node != nullptr ) {
            if ( std::find( refinedNodes.begin(), refinedNodes.end(), node ) != refinedNodes.end() ) {
                ancestorRefined = true;
                break;
            }
            node = node->getParent();
        }
        if ( !ancestorRefined ) {
            pathSuccessors.push_back( succ );
        }
    }

    return { UrgencyRefinementSuccess{ pathSuccessors } };
}

template <typename Representation>
auto UrgencyRefinementAnalyzer<Representation>::findRefinementNode( ReachTreeNode<Representation>* unsafeNode )
    -> RefinePoint {

    // collect ancestors of unsafe node
    std::vector<ReachTreeNode<Representation>*> nodePath( unsafeNode->getDepth() + 1 );
    for ( auto n = unsafeNode; n != nullptr; n = n->getParent() ) {
        nodePath[ n->getDepth() ] = n;
    }

    // for each node on the path, refine every transition to the next level (up to max level)
    // until the max level is reached or a suitable transition is found
    for ( auto nodeIt = nodePath.begin(); nodeIt != nodePath.end(); ++nodeIt ) {
        UrgencyRefinementLevel nextLevel = mRefinementSettings.maxRefinementLevel();
        do {
            // find next refinement level
            for ( auto const& trans : ( *nodeIt )->getLocation()->getTransitions() ) {
                if ( !trans->isUrgent() || ( *nodeIt )->getUrgent()[ trans.get() ] == mRefinementSettings.maxRefinementLevel() ) continue;
                auto nextLevelTrans = getNextLevel( ( *nodeIt )->getUrgent()[ trans.get() ] );
                nextLevel = nextLevelTrans < nextLevel ? nextLevelTrans : nextLevel;
            }

            // collect urgent outgoing transitions with refinementLevel < nextLevel
            std::vector<Transition<Number>*> candidateTransitions;
            for ( auto const& trans : ( *nodeIt )->getLocation()->getTransitions() ) {
                if ( trans->isUrgent() && ( *nodeIt )->getUrgent()[ trans.get() ] < nextLevel ) {
                    candidateTransitions.push_back( trans.get() );
                }
            }
            // sort by used heuristic
            std::sort( candidateTransitions.begin(), candidateTransitions.end(), [this, nodeIt]( auto t1, auto t2 ){
                return mRefinementSettings.heuristic == UrgencyRefinementHeuristic::CONSTRAINT_COUNT ?
                    computeHeuristic( t1, *nodeIt ) < computeHeuristic( t2, *nodeIt ) :
                    computeHeuristic( t1, *nodeIt ) > computeHeuristic( t2, *nodeIt ); } );

            // refine all transitions to next level
            for ( auto candidateTrans : candidateTransitions ) {
                RefinePoint candidate{ *nodeIt, candidateTrans, nextLevel };
                if ( suitableForRefinement( candidate, unsafeNode ) ) {
                    updateHeuristics( candidateTrans );
                    return candidate;
                }
            }
        // at this point, all transitions are refined to nextLevel, so we stop when maxLevel is reached
        } while ( nextLevel != mRefinementSettings.maxRefinementLevel() );
    }
    return RefinePoint{};
}

template <typename Representation>
UrgencyRefinementLevel UrgencyRefinementAnalyzer<Representation>::getNextLevel( const UrgencyRefinementLevel& level ) const {
    auto enabledLevels = mRefinementSettings.refinementLevels;
    switch ( level ) {
        case UrgencyRefinementLevel::FULL:
            if ( std::find( enabledLevels.begin(), enabledLevels.end(), UrgencyRefinementLevel::CUTOFF ) != enabledLevels.end() ) {
                return UrgencyRefinementLevel::CUTOFF;
            }
            [[fallthrough]];
        case UrgencyRefinementLevel::CUTOFF:
            if ( std::find( enabledLevels.begin(), enabledLevels.end(), UrgencyRefinementLevel::SETDIFF ) != enabledLevels.end() ) {
                return UrgencyRefinementLevel::SETDIFF;
            }
            [[fallthrough]];
        default:
            assert( false && "No next level for maximal refinement level" );
            return level;
    }
}

template <typename Representation>
ReachTreeNode<Representation>* UrgencyRefinementAnalyzer<Representation>::refineNode( const RefinePoint& refine ) {
    auto parent = refine.node->getParent();
    auto urgentTransitions = refine.node->getUrgent();
    urgentTransitions[ refine.transition ] = refine.level;
    // check if refined node already exists
    if ( parent == nullptr ) {
        for ( auto& sibling : *mRoots ) {
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
        refinedNode.getUrgent() = urgentTransitions;
        mRoots->push_back( std::move( refinedNode ) );
        return &( mRoots->back() );
    }
    ReachTreeNode<Representation>& refinedNode = parent->addChild(
        refine.node->getInitialSet(),
        refine.node->getTimings(),
        refine.node->getTransition() );
    refinedNode.getUrgent() = urgentTransitions;
    return &refinedNode;
}

template <typename Representation>
bool UrgencyRefinementAnalyzer<Representation>::suitableForRefinement(
        const RefinePoint& candidate, ReachTreeNode<Representation>* unsafeNode ) {

    /*
        + iterate over all segments of the candidate node
        + if segmentTiming > timeOfFirstJump: moved beyond jump, so further segments are ignored
        + intersect with jump enabling set of urgent jump
        + if containment is full and segmentTiming < timeOfFirstJump: suitable, because
            the jump is not reachable at all
        + if containment is partial, compute the path starting from the intersection
    */

    // path from candidate node to unsafe node
    auto path = unsafeNode->getPath().tail( unsafeNode->getDepth() - candidate.node->getDepth() );

    const auto& candidateTimings = candidate.node->getTimings();
    const auto& candidateFpTimings = candidate.node->getFpTimings();
    auto& candidateFlowpipe = candidate.node->getFlowpipe();
    // initial time horizon and initial tree node
    std::vector<std::pair<SegmentInd, ReachTreeNode<Representation>>> tasks;
    for ( std::size_t fpIndex = 0; fpIndex < candidateFlowpipe.size(); ++fpIndex ) {
        // moved beyond first jump:
        if ( path.elements.size() > 0 && candidateFpTimings[ fpIndex ] + candidateTimings.lower() > path.elements[0].first.upper() ) {
            break;
        }

        auto [containment, initial] = intersect( candidateFlowpipe[ fpIndex ], candidate.transition->getJumpEnablingSet() );
        if ( containment == CONTAINMENT::NO ) {
            continue;
        } else if ( containment == CONTAINMENT::FULL && path.elements.size() > 0 && 
                    candidateFpTimings[ fpIndex ] + candidateTimings.upper() < path.elements[0].first.lower() ) {
            // segment before jump is fully contained in jump enabling set
            return true;
        } else {
            // get time horizon for first task
            auto timeHorizon = mMaxSegments - candidateFpTimings[ fpIndex ];
            // create task node, todo: urgency?
            carl::Interval<SegmentInd> segmentOffset = candidateTimings.add( carl::Interval<SegmentInd>( candidateFpTimings[ fpIndex ] ) );
            ReachTreeNode<Representation> task( candidate.node->getLocation(), initial, segmentOffset );
            tasks.push_back( std::make_pair( timeHorizon, std::move( task ) ) );
        }
    }

    for ( auto& [timeHorizon, task] : tasks ) {
        if ( pathUnsafe( &task, path, timeHorizon ) ) {
            return true;
        }
    }
    return false;
}

template <typename Representation>
bool UrgencyRefinementAnalyzer<Representation>::pathUnsafe( ReachTreeNode<Representation>* initialNode, Path<Number> path, std::size_t initialTimeHorizon ) {
    // todo: reuse worker or at least transformationCache
    TimeTransformationCache<Number> transformationCache;
    UrgencyWorker<Representation> worker{
          *mHybridAutomaton,
          mParameters,
          mFixedParameters.localTimeHorizon,
          transformationCache };

    std::deque<ReachTreeNode<Representation>*> queue;
    queue.push_front( initialNode );
    while ( !queue.empty() ) {
        auto node = queue.back();
        queue.pop_back();
        if ( node->getDepth() == 0 ) {
            if ( worker.computeTimeSuccessors( *node, initialTimeHorizon ) == REACHABILITY_RESULT::UNKNOWN ) {
                return true;
            }
        } else {
            if ( worker.computeTimeSuccessors( *node ) == REACHABILITY_RESULT::UNKNOWN ) {
                return true;
            }
        }
        worker.insertFlowpipe( *node );
        worker.reset();
        if ( node->getDepth() < path.elements.size() ) {
            auto nextTransition = path.elements[ node->getDepth() ].second;
            auto successor = worker.computeJumpSuccessors( *node, nextTransition, path.elements[ node->getDepth() ].first );
            ChildNodeGen childGen{ successor, node, nextTransition, mParameters.timeStepFactor, mRefinementSettings };
            while ( auto* child = childGen.next() ) {
                queue.push_front( child );
            }
        }
    }
    return false;
}

template <typename Representation>
std::size_t UrgencyRefinementAnalyzer<Representation>::computeHeuristic( Transition<Number>* t, ReachTreeNode<Representation>* node ) {
    if ( mRefinementCache.find( t ) == mRefinementCache.end() ) {
        switch ( mRefinementSettings.heuristic ) {
            case UrgencyRefinementHeuristic::CONSTRAINT_COUNT: {
                mRefinementCache[ t ] = t->getJumpEnablingSet().getMatrix().rows();
                break;
            } case UrgencyRefinementHeuristic::VOLUME: {
                // todo: differentiate between representations where it is easier to compute intersection -> intersect each segment;
                // or union -> aggregate all segments and compute volume once
                std::size_t vol = 0;
                for ( auto segment : node->getFlowpipe() ) {
                    auto [containment, intersected] = intersect( segment, t->getJumpEnablingSet() );
                    if ( containment == CONTAINMENT::NO ) continue;
                    auto box = computeBoundingBox( intersected );
                    std::size_t boxVol = 1;
                    for ( const auto& interval : box.intervals() ) {
                        vol *= size_t( std::ceil( carl::convert<Number, double>( interval.upper() - interval.lower() ) ) );
                    }
                    vol += boxVol;
                }
                mRefinementCache[ t ] = vol;
                break;
            } case UrgencyRefinementHeuristic::COUNT: {
                mRefinementCache[ t ] = 0;
                break;
            } default:
                // no heuristic matched, return default value
                return 0;
        }
    }
    return mRefinementCache[ t ];
}

template <typename Representation>
void UrgencyRefinementAnalyzer<Representation>::updateHeuristics( Transition<Number>* t ) {
    if ( mRefinementSettings.heuristic == UrgencyRefinementHeuristic::COUNT ) {
        mRefinementCache[ t ] += 1;
    } else if ( mRefinementSettings.heuristic == UrgencyRefinementHeuristic::VOLUME ) {
        mRefinementCache.clear();
    }
}

} // namespace hypro