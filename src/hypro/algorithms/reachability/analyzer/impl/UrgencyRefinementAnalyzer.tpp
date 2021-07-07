#include "UrgencyRefinementAnalyzer.h"

namespace hypro {


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
        return { Failure{ failureNode } };
    }

    mWorkQueue.push_front( createRefinedNode( refine ) );

    while ( !mWorkQueue.empty() ) {
        // pop node
        ReachTreeNode<Representation>* currentNode = mWorkQueue.back();
        mWorkQueue.pop_back();

        // if node is child of last node in path, collect it in return value
        if ( currentNode->getDepth() == mPath.elements.size() + 1 ) {
            endOfPath.push_back( currentNode );
            continue;
        }

        REACHABILITY_RESULT safetyResult;

        // compute flowpipe
        if ( currentNode->getFlowpipe().empty() ) {
            safetyResult = worker.computeForwardReachability( currentNode );
        }

        if ( safetyResult == REACHABILITY_RESULT::UNKNOWN ) {
            refine = findRefinementNode( currentNode );
            if ( refine.node == nullptr ) {
                return { Failure{ currentNode } };
            }
            mWorkQueue.push_front( createRefinedNode( refine ) );
            refinedNodes.push_back( currentNode );
            continue;
        }

        // do not perform discrete jump if jump depth was reached
        if ( currentNode->getDepth() == mFixedParameters.jumpDepth ) continue;

        // currentNode is last node in path, create and collect all children
        // todo
        if ( currentNode->getDepth() == mPath.elements.size() ) {
            for ( auto const& transition : currentNode->getLocation()->getTransitions() ) {
                auto jumpSuccGen = worker.getJumpSuccessors( currentNode->getFlowpipe(), transition.get() );
                auto childGen = ChildNodeGen{ &jumpSuccGen, currentNode, mParameters.timeStepFactor };

                while ( auto* child = childGen.next() ) {
                    endOfPath.push_back( child );
                }
            }
        } else {
            // continue along path

            // check if children already exist
            bool matchedOne = false;
            for ( auto* child : currentNode->getChildren() ) {
                if ( matchesPathTransition( child ) && child.getUrgent().size() == 0 ) {
                    matchedOne = true;
                    // check against path
                    if ( matchesPathTiming( child ) ) {
                        mWorkQueue.push_front( child );
                    }
                }
            }

            if ( !matchedOne ) {
                // todo
                auto jumpSuccGen = worker.getJumpSuccessors( currentNode->getFlowpipe(), mPath.elements.at( currentNode->getDepth() ).second );
                auto childGen = ChildNodeGen{ &jumpSuccGen, currentNode, mParameters.timeStepFactor };

                while ( auto* child = childGen.next() ) {
                    if ( matchesPathTiming( child ) ) {
                        mWorkQueue.push_front( child );
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
auto UrgencyRefinementAnalyzer<Representation>::findRefinementNode( ReachTreeNode<Representation>* const unsafeNode )
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
ReachTreeNode<Representation>* UrgencyRefinementAnalyzer<Representation>::createRefinedNode( const RefinePoint& refine ) {
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
bool UrgencyRefinementAnalyzer<Representation>::guardUnsafe(
        ReachTreeNode<Representation>* const start, const Path<Number>& pathToUnsafe, Transition<Number>* refineJump ) {

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
            auto segmentIndex = start->getFpTimings()[ fpIndex ];
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

} // namespace hypro