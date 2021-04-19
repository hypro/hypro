#include "DecompositionalAnalyzer.h"

namespace hypro {

template <typename Representation>
auto DecompositionalAnalyzer<Representation>::run() -> DecompositionalResult {
    auto workers = initializeWorkers();

    while ( !mWorkQueue.empty() ) {
        auto nextInQueue = mWorkQueue.front();
        mWorkQueue.pop_front();
        NodeVector currentNodes = nextInQueue.nodes;
        Condition<Number> dependencies = nextInQueue.dependencies;
        std::size_t clockIndex = nextInQueue.clockIndex;
        const Location<Number>* currentLoc = currentNodes[ 0 ]->getLocation();

        std::for_each( workers.begin(), workers.end(), []( WorkerVariant& worker ) {
            std::visit( detail::resetWorkerVisitor<Representation>{}, worker );
        } );

        // Time successors
        TimeInformation<Number> invariantSatisfyingTime = computeTimeSuccessorsGetEnabledTime( currentNodes, workers );
        resetClocks( currentNodes, clockIndex );
        intersectSubspacesWithClock( currentNodes, invariantSatisfyingTime );

        // Check safety
        for ( auto badState : detail::collectBadStates( mHybridAutomaton, currentLoc ) ) {
            if ( !isSafe( currentNodes, dependencies, badState ) ) {
                return { Failure { currentNodes[ 0 ] } };
            }
        }

        // Check jump depth
        if ( currentNodes[ 0 ]->getDepth() == mFixedParameters.jumpDepth ) {
            continue;
        }

        for ( auto subspace : mSingularSubspaces ) {
            // compute jump successors independently for singular subspaces
            std::visit( detail::computeSingularJumpSuccessorVisitor<Representation>{ currentNodes[ subspace ] }, workers[ subspace ] );
        }

        for ( const auto& transition : currentLoc->getTransitions() ) {
            // get jump successors
            auto [transitionEnabledTime, singularJumpSuccessors] = getSingularJumpSuccessors( workers, transition.get() );
            if ( singularJumpSuccessors.empty() && mSingularSubspaces.size() > 0 ) {
                continue;
            }

            // create child nodes
            if ( clockIndex < mClockCount - 1 ) {
                auto childNodes = makeChildrenForClockValues( currentNodes, transition.get(), transitionEnabledTime, singularJumpSuccessors );
                mWorkQueue.push_back( detail::decompositionalQueueEntry<Representation>{ clockIndex + 1, dependencies, childNodes } );
            } else {
                // complexity reduction
                auto newDependencies = detail::composeSubspaces( singularJumpSuccessors, dependencies, mClockCount );
                singularJumpSuccessors = detail::decomposeInitial( Representation( newDependencies.getMatrix(), newDependencies.getVector() ), mClockCount );
                auto childNodes = makeChildrenForClockValues( currentNodes, transition.get(), transitionEnabledTime, singularJumpSuccessors );
                mWorkQueue.push_back( detail::decompositionalQueueEntry<Representation>{ 0, newDependencies, childNodes } );
            }

        }
    }
    return { DecompositionalSuccess{} };
}


template <typename Representation>
auto DecompositionalAnalyzer<Representation>::initializeWorkers() -> std::vector<WorkerVariant> {
    std::vector<WorkerVariant> workers;
    for ( std::size_t subspace = 0; subspace < mDecomposition.subspaces.size(); ++subspace ) {
        switch( mDecomposition.subspaceTypes[ subspace ] ) {
            case DynamicType::timed:
                [[fallthrough]];
            case DynamicType::singular:
                workers.push_back( SingularWorker<Representation>{ *mHybridAutomaton,
                                                                    mFixedParameters,
                                                                    subspace } );
                break;
            default:
                assert( false && "Only singular decompositional analysis supported" );
                break;
        }
    }
    return workers;
}

template <typename Representation>
bool DecompositionalAnalyzer<Representation>::checkConsistency( NodeVector& currentNodes ) {
    if ( std::any_of( currentNodes.begin(), currentNodes.end(), []( const auto& node ) {
                return node->getInitialSet().empty(); } ) ) {
        return false;
    }
    return true;
}

template <typename Representation>
auto DecompositionalAnalyzer<Representation>::computeTimeSuccessorsGetEnabledTime(
  NodeVector& currentNodes, std::vector<WorkerVariant>& workers ) -> TimeInformation<Number> {
    TimeInformation<Number> invariantSatTime( mClockCount, Number( 0 ), carl::convert<tNumber, Number>( mGlobalTimeHorizon ) );
    for ( std::size_t subspace = 0; subspace < mDecomposition.subspaces.size(); ++subspace ) {
        TimeInformation<Number> invariantSatTimeSubspace = std::visit( detail::computeTimeSuccessorVisitor<Representation>{
            currentNodes[ subspace ], mClockCount }, workers[ subspace ] );
        invariantSatTime = invariantSatTime.intersect( invariantSatTimeSubspace );
    }
    return invariantSatTime;
}

template <typename Representation>
void DecompositionalAnalyzer<Representation>::resetClocks( NodeVector& currentNodes, std::size_t clockIndex ) {
    for ( auto subspace : mSingularSubspaces ) {
        for ( auto& segment : currentNodes[ subspace ]->getFlowpipe() ) {
            std::vector<std::size_t> nonZeroDimensions( segment.dimension() - mClockCount + clockIndex + 1 );
            for ( std::size_t i = 0; i < nonZeroDimensions.size(); ++i ) {
                nonZeroDimensions[ i ] = i;
            }
            segment = segment.projectOn( nonZeroDimensions );
        }
    }
}

template <typename Representation>
void DecompositionalAnalyzer<Representation>::intersectSubspacesWithClock(
  NodeVector& currentNodes, TimeInformation<Number>& clock ) {
    for ( auto subspace : mSingularSubspaces ) {
        // intersect each segment with the valid time interval
        for ( auto& segment : currentNodes[ subspace ]->getFlowpipe() ) {
            segment = detail::intersectSegmentWithClock( segment, clock, mClockCount );
        }
    }
}

template <typename Representation>
bool DecompositionalAnalyzer<Representation>::isSafe(
  const NodeVector& currentNodes, const Condition<Number>& dependencies, const Condition<Number>& badState ) {
    // todo: implement with simplex
    return true;
}

template <typename Representation>
auto DecompositionalAnalyzer<Representation>::getSingularJumpSuccessors(
  std::vector<WorkerVariant>& workers, Transition<Number>* transition ) -> std::pair<TimeInformation<Number>, RepVector> {
    TimeInformation<Number> enabledTime( mClockCount, Number( 0 ), carl::convert<tNumber, Number>( mGlobalTimeHorizon ) );
    RepVector singularSuccessors( mSingularSubspaces.size() );
    for ( auto subspace : mSingularSubspaces ) {
        auto subspaceSuccessorSet = std::visit( detail::getSingularJumpSuccessorVisitor<Representation>{ transition }, workers[ subspace ] );
        singularSuccessors[ subspace ] = subspaceSuccessorSet;
        enabledTime = enabledTime.intersect( detail::getClockValues( subspaceSuccessorSet, mClockCount ) );
    }
    return std::make_pair( enabledTime, singularSuccessors );
}


template <typename Representation>
std::vector<ReachTreeNode<Representation>*> DecompositionalAnalyzer<Representation>::makeChildrenForClockValues(
  NodeVector& currentNodes, const Transition<Number>* transition, const TimeInformation<Number>& clockValues, const RepVector& singularSuccessors ) {
    if ( clockValues.empty() ) {
        return NodeVector{};
    }
    NodeVector child( mDecomposition.subspaces.size() );
    for ( auto subspace : mSingularSubspaces ) {
        auto subspaceSuccessor = detail::intersectSegmentWithClock(
            singularSuccessors[ subspace ], clockValues, mClockCount );
        auto& subspaceChild = currentNodes[ subspace ]->addChild( subspaceSuccessor, carl::Interval<SegmentInd>( 0, 0 ), transition );
        child[ subspace ] = &subspaceChild;
    }
    return child;
}
} // namespace hypro
