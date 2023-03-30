/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "DecompositionalAnalyzer.h"

namespace hypro {

template <typename LTIRep, typename SingularRep, typename DiscreteRep, typename RectangularRep, typename Automaton>
auto DecompositionalAnalyzer<LTIRep, SingularRep, DiscreteRep, RectangularRep, Automaton>::run() -> DecompositionalResult {
	std::vector<TimeTransformationCache<LocationT>> cache( mDecomposition.subspaces.size(), TimeTransformationCache<LocationT>() );
	auto workers = initializeWorkers( cache );

	while ( !mWorkQueue.empty() ) {
		COUNT( "Nodes" );
		auto nextInQueue = mWorkQueue.front();
		mWorkQueue.pop_front();
		NodeVector currentNodes = nextInQueue.nodes;
		ReachTreeNode<Condition<Number>, LocationT>* depNode = nextInQueue.dependencyNode;
		Condition<Number> dependencies = depNode->getInitialSet();
		std::size_t clockIndex = nextInQueue.clockIndex;
		const Location<Number>* currentLoc = currentNodes[0]->getLocation();

		if ( !checkConsistency( currentNodes ) ) {
			// empty initial set
			continue;
		}

		std::for_each( workers.begin(), workers.end(), []( WorkerVariant& worker ) {
			std::visit( resetWorkerVisitor{}, worker );
		} );

		START_BENCHMARK_OPERATION( "TimeSuccessors" );
		// Time successors
		TimeInformation<Number> invariantSatisfyingTime = computeTimeSuccessorsGetEnabledTime( currentNodes, workers, clockIndex );
		removeRedundantSegments( currentNodes );
		intersectSubspacesWithClock( currentNodes, invariantSatisfyingTime );
		STOP_BENCHMARK_OPERATION( "TimeSuccessors" );

		START_BENCHMARK_OPERATION( "SafetyCheck" );
		// Check safety
		for ( auto badState : detail::collectBadStates( mHybridAutomaton, currentLoc ) ) {
			if ( !isSafe( currentNodes, dependencies, badState ) ) {
				STOP_BENCHMARK_OPERATION( "SafetyCheck" );
				return { Failure{ currentNodes[0] } };
			}
		}
		STOP_BENCHMARK_OPERATION( "SafetyCheck" );

		// Check jump depth
		if ( currentNodes[0]->getDepth() == mFixedParameters.jumpDepth ) {
			continue;
		}

		for ( const auto& transition : currentLoc->getTransitions() ) {
			START_BENCHMARK_OPERATION( "JumpSuccessors" );
			std::vector<SubspaceJumpSuccessors<ComposedRep>> jumpSuccessors = getJumpSuccessors( currentNodes, workers, transition.get(), clockIndex );
			STOP_BENCHMARK_OPERATION( "JumpSuccessors" );
			for ( auto& timedSuccessor : jumpSuccessors ) {
				std::size_t nextIndex = clockIndex + 1;
				// todo: return as vector, not as map
				RepVector subspaceSets( mDecomposition.subspaces.size() );
				for ( std::size_t subspace = 0; subspace < subspaceSets.size(); ++subspace ) {
					subspaceSets[subspace] = std::move( timedSuccessor.subspaceSets[subspace] );
				}
				if ( std::any_of( subspaceSets.begin(), subspaceSets.end(), []( auto const& state ) { return state.empty(); } ) ) {
					continue;
				}
				if ( mClockCount > 0 && nextIndex >= mClockCount ) {
					COUNT( "ComplexityReductionSteps" );
					START_BENCHMARK_OPERATION( "ComplexityReduction" );
					nextIndex = 0;
					std::tie( dependencies, subspaceSets ) = synchronizeAndResetClocks( subspaceSets, dependencies );
					STOP_BENCHMARK_OPERATION( "ComplexityReduction" );
					if ( subspaceSets.size() == 0 ) continue;
				}

				// create child nodes and push to queue
				NodeVector childNodes( mDecomposition.subspaces.size() );
				for ( std::size_t subspace = 0; subspace < mDecomposition.subspaces.size(); ++subspace ) {
					auto& subspaceChild = currentNodes[subspace]->addChild( subspaceSets[subspace], currentNodes[subspace]->getTimings() + timedSuccessor.time, transition.get() );
					childNodes[subspace] = &subspaceChild;
				}
				mWorkQueue.push_back( detail::decompositionalQueueEntry<ComposedRep, LocationT>{
					  nextIndex,
					  childNodes,
					  &( depNode->addChild( dependencies, depNode->getTimings() + timedSuccessor.time, transition.get() ) ) } );
			}
		}
	}
	return { DecompositionalSuccess{} };
}

template <typename LTIRep, typename SingularRep, typename DiscreteRep, typename RectangularRep, typename Automaton>
auto DecompositionalAnalyzer<LTIRep, SingularRep, DiscreteRep, RectangularRep, Automaton>::initializeWorkers( std::vector<TimeTransformationCache<LocationT>>& cache ) -> std::vector<WorkerVariant> {
	std::vector<WorkerVariant> workers;
	for ( std::size_t subspace = 0; subspace < mDecomposition.subspaces.size(); ++subspace ) {
		switch ( mDecomposition.subspaceTypes[subspace] ) {
			case DynamicType::discrete:
				workers.push_back( DiscreteWorker<DiscreteRep, Automaton>{ *mHybridAutomaton,
																		   mParameters,
																		   subspace } );
				break;
			case DynamicType::timed:
				[[fallthrough]];
			case DynamicType::singular:
				workers.push_back( SingularWorker<SingularRep, Automaton>{ *mHybridAutomaton,
																		   mFixedParameters,
																		   subspace } );
				break;
			default:
				workers.push_back( LTIWorker<LTIRep, Automaton>{
					  *mHybridAutomaton,
					  mParameters,
					  mFixedParameters.localTimeHorizon,
					  cache[subspace],
					  subspace } );
		}
	}
	return workers;
}

template <typename LTIRep, typename SingularRep, typename DiscreteRep, typename RectangularRep, typename Automaton>
bool DecompositionalAnalyzer<LTIRep, SingularRep, DiscreteRep, RectangularRep, Automaton>::checkConsistency( NodeVector& currentNodes ) {
	if ( std::any_of( currentNodes.begin(), currentNodes.end(), []( const auto& node ) { return node->getInitialSet().isEmpty(); } ) ) {
		return false;
	}
	return true;
}

template <typename LTIRep, typename SingularRep, typename DiscreteRep, typename RectangularRep, typename Automaton>
auto DecompositionalAnalyzer<LTIRep, SingularRep, DiscreteRep, RectangularRep, Automaton>::computeTimeSuccessorsGetEnabledTime(
	  NodeVector& currentNodes, std::vector<WorkerVariant>& workers, std::size_t clockIndex ) -> TimeInformation<Number> {
	// start with maximal time interval and shrink it after each subspace computation
	TimeInformation<Number> invariantSatTime = mGlobalTimeInterval;
	// start with discrete and singular subspaces to get a bound on the time horizon for lit analysis
	for ( auto subspace : mDiscreteSubspaces ) {
		std::visit( computeTimeSuccessorVisitor{
						  currentNodes[subspace], mClockCount },
					workers[subspace] );
	}
	for ( auto subspace : mSingularSubspaces ) {
		TimeInformation<Number> invariantSatTimeSubspace = std::visit( computeTimeSuccessorVisitor{
																			 currentNodes[subspace], mClockCount },
																	   workers[subspace] );
		invariantSatTime = invariantSatTime.intersect( invariantSatTimeSubspace );
	}
	// get the number of segments to compute from the time interval in which invariant is satisfied across subspaces
	long segmentHorizon = -1;  // unbounded
	if ( mClockCount > 0 ) {
		std::ceil( carl::convert<tNumber, double>( invariantSatTime.getTimeInterval( clockIndex ).upper() / mParameters.timeStep ) );
	}
	for ( auto subspace : mSegmentedSubspaces ) {
		TimeInformation<Number> invariantSatTimeSubspace = std::visit( computeTimeSuccessorVisitor{
																			 currentNodes[subspace], mClockCount, segmentHorizon },
																	   workers[subspace] );
		invariantSatTime = invariantSatTime.intersect( invariantSatTimeSubspace );
		// reduce segmentHorizon based on how many segments were computed in subspace
		// this can be done no matter whether we use clocks or not
		segmentHorizon = currentNodes[subspace]->getFlowpipe().size();
	}
	return invariantSatTime;
}

template <typename LTIRep, typename SingularRep, typename DiscreteRep, typename RectangularRep, typename Automaton>
void DecompositionalAnalyzer<LTIRep, SingularRep, DiscreteRep, RectangularRep, Automaton>::intersectSubspacesWithClock(
	  NodeVector& currentNodes, TimeInformation<Number>& clock ) {
	for ( std::size_t subspace = 0; subspace < currentNodes.size(); ++subspace ) {
		// discrete subspaces have no clocks
		if ( mDecomposition.subspaceTypes[subspace] == DynamicType::discrete ) continue;
		// intersect each segment with the valid time interval
		auto& flowpipe = currentNodes[subspace]->getFlowpipe();
		for ( std::size_t segmentIndex = 0; segmentIndex < flowpipe.size(); ++segmentIndex ) {
			auto constraintedSegment = detail::intersectSegmentWithClock( flowpipe[segmentIndex], clock, mClockCount );
			if ( constraintedSegment.empty() ) {
				// delete all further segments, because they have higher clock values
				flowpipe.resize( segmentIndex );
			} else {
				flowpipe[segmentIndex] = constraintedSegment;
			}
		}
	}
}

template <typename LTIRep, typename SingularRep, typename DiscreteRep, typename RectangularRep, typename Automaton>
void DecompositionalAnalyzer<LTIRep, SingularRep, DiscreteRep, RectangularRep, Automaton>::removeRedundantSegments( NodeVector& currentNodes ) {
	if ( mSegmentedSubspaces.size() == 0 ) {
		return;
	}
	// get minimum number of segments that a subspace has
	std::vector<std::size_t> segmentCount( mSegmentedSubspaces );
	std::size_t i = 0;
	for ( auto subspace : mSegmentedSubspaces ) {
		segmentCount[i] = currentNodes[subspace]->getFlowpipe().size();
		++i;
	}
	std::size_t minSegments = *( std::min_element( segmentCount.begin(), segmentCount.end() ) );
	// remove segments beyond reachable time horizon
	for ( auto subspace : mSegmentedSubspaces ) {
		currentNodes[subspace]->getFlowpipe().resize( minSegments );
	}
}

template <typename LTIRep, typename SingularRep, typename DiscreteRep, typename RectangularRep, typename Automaton>
bool DecompositionalAnalyzer<LTIRep, SingularRep, DiscreteRep, RectangularRep, Automaton>::isSafe(
	  const NodeVector& nodes, const Condition<Number>& dependencies, const Condition<Number>& badState ) {
	// first check if all discrete subspaces contain bad states. In that case they can be disregarded
	// for the rest of the synchronization process
	for ( auto subspace : mDiscreteSubspaces ) {
		auto [containment, set] = intersect( nodes[subspace]->getFlowpipe()[0], badState, subspace );
		if ( containment == CONTAINMENT::NO ) {
			// no bad state intersection in some subspace
			return true;
		}
	}

	// time interval where all subspaces can be bad
	TimeInformation<Number> badTimeInterval = mGlobalTimeInterval;
	// Synchronize segmented subspaces and intersect them with the bad state
	// we ignore discrete subspaces, because they are already unsafe
	std::vector<HPolytope<Number>> subspacePolytopes;
	RepVector subspaceSets( mDecompositionWithoutDiscrete.subspaces.size() );
	std::size_t subspaceSetsIndex = 0;
	// each segment is paired with the single segment from each singular subspace
	for ( std::size_t subspace = 0; subspace < mDecomposition.subspaces.size(); ++subspace ) {
		if ( std::find( mSingularSubspaces.begin(), mSingularSubspaces.end(), subspace ) != mSingularSubspaces.end() ) {
			auto [containment, set] = intersect( nodes[subspace]->getFlowpipe()[0], badState, subspace );
			if ( containment == CONTAINMENT::NO ) {
				// no bad state intersection in some subspace
				return true;
			} else {
				set = detail::intersectSegmentWithClock( set, badTimeInterval, mClockCount );
				badTimeInterval = badTimeInterval.intersect( detail::getClockValues( set, mClockCount ) );
				if ( badTimeInterval.empty() ) {
					return true;
				}
				subspaceSets[subspaceSetsIndex] = set;
			}
		}
		// count non-discrete subspaces
		if ( mDecomposition.subspaceTypes[subspace] != DynamicType::discrete ) {
			subspaceSetsIndex += 1;
		}
	}

	if ( mSegmentedSubspaces.size() == 0 ) {
		if ( mClockCount == 0 ) {
			// all subspaces unsafe at some point. without synchronization we cannot tell if they are unsafe at the same time or not.
			return false;
		}
		// compose subspaces and check if synchronized set is non empty
		std::vector<HPolytope<Number>> hpols;
		std::transform( subspaceSets.begin(), subspaceSets.end(), std::back_inserter( hpols ), [=]( auto& state ) {
			return std::visit( genericConvertAndGetVisitor<HPolytope<Number>>(), state.getSet() );
		} );

		HPolytope<Number> composedPolytope = detail::composeSubspaceConstraints( hpols, dependencies, mDecompositionWithoutDiscrete, mClockCount );
		if ( !composedPolytope.empty() ) {
			return false;
		}
	}
	// note: only segments that have non-empty intersection with bad state in all subspaces are returned by generator
	LtiSegmentGen segments{ nodes, mDecomposition, badState, badTimeInterval, mSegmentedSubspaces };
	// iterate over each synchronized segment and check if composition is non empty
	for ( auto badSegment = segments.next().second; badSegment.size() > 0; badSegment = segments.next().second ) {
		subspaceSetsIndex = 0;
		if ( mClockCount == 0 ) {
			// all subspaces unsafe at some point. without synchronization we cannot tell if they are unsafe at the same time or not.
			return false;
		}
		for ( std::size_t subspace = 0; subspace < mDecomposition.subspaces.size(); ++subspace ) {
			if ( std::find( mSegmentedSubspaces.begin(), mSegmentedSubspaces.end(), subspace ) != mSegmentedSubspaces.end() ) {
				subspaceSets[subspaceSetsIndex] = badSegment[subspace];
			}
			if ( mDecomposition.subspaceTypes[subspace] != DynamicType::discrete ) {
				subspaceSetsIndex += 1;
			}
		}
		std::vector<HPolytope<Number>> hpols;
		std::transform( subspaceSets.begin(), subspaceSets.end(), std::back_inserter( hpols ), [=]( auto& state ) {
			return std::visit( genericConvertAndGetVisitor<HPolytope<Number>>(), state.getSet() );
		} );
		HPolytope<Number> composedPolytope = detail::composeSubspaceConstraints( hpols, dependencies, mDecompositionWithoutDiscrete, mClockCount );
		if ( !composedPolytope.empty() ) {
			return false;
		}
	}
	return true;
}

template <typename LTIRep, typename SingularRep, typename DiscreteRep, typename RectangularRep, typename Automaton>
void DecompositionalAnalyzer<LTIRep, SingularRep, DiscreteRep, RectangularRep, Automaton>::resetUnusedClocks( ComposedRep& segment, std::size_t clockIndex ) {
	assert( !segment.empty() && "Clock reset called on empty segment" );
	if ( mClockCount == 0 ) {
		return;
	}
	assert( mClockCount > clockIndex );
	// reset clocks with higher index than clockIndex to 0
	std::vector<std::size_t> nonZeroDimensions( segment.dimension() - mClockCount + clockIndex + 1 );
	for ( std::size_t i = 0; i < nonZeroDimensions.size(); ++i ) {
		nonZeroDimensions[i] = i;
	}
	segment.projectOn( nonZeroDimensions );
}

template <typename LTIRep, typename SingularRep, typename DiscreteRep, typename RectangularRep, typename Automaton>
auto DecompositionalAnalyzer<LTIRep, SingularRep, DiscreteRep, RectangularRep, Automaton>::getJumpSuccessors(
	  const NodeVector& nodes, std::vector<WorkerVariant> workers,
	  Transition<LocationT>* trans,
	  std::size_t clockIndex )
	  -> std::vector<SubspaceJumpSuccessors<ComposedRep>> {
	// res holds all synchronized jump successors
	std::vector<SubspaceJumpSuccessors<ComposedRep>> res;
	// Collect single successor set (per subspace) for singular subspaces and synchronize them
	START_BENCHMARK_OPERATION( "JumpSuccessorsSingular" );
	auto [singularEnabledTime, singularSuccessors] = getSingularJumpSuccessors( nodes, workers, trans, clockIndex );
	STOP_BENCHMARK_OPERATION( "JumpSuccessorsSingular" );
	if ( singularEnabledTime.empty() ) {
		return {};
	}
	START_BENCHMARK_OPERATION( "JumpSuccessorsDiscrete" );
	auto discreteSuccessors = getDiscreteJumpSuccessors( nodes, workers, trans );
	if ( mSegmentedSubspaces.size() == 0 ) {
		// no segmented subspace, so the segment indexes are ignored -> set them to 0
		SubspaceJumpSuccessors<ComposedRep> succ{ carl::Interval<SegmentInd>( 0 ), singularSuccessors };
		for ( auto subspace : mDiscreteSubspaces ) {
			succ.subspaceSets[subspace] = discreteSuccessors[subspace];
		}
		STOP_BENCHMARK_OPERATION( "JumpSuccessorsDiscrete" );
		return { succ };
	}
	STOP_BENCHMARK_OPERATION( "JumpSuccessorsDiscrete" );
	START_BENCHMARK_OPERATION( "JumpSuccessorsLTI" );
	// collect synchronized successors for segmented subspaces
	std::vector<SubspaceJumpSuccessors<ComposedRep>> segmentedSuccessors = getSegmentedJumpSuccessors( nodes, workers, trans, singularEnabledTime, clockIndex );
	STOP_BENCHMARK_OPERATION( "JumpSuccessorsLTI" );

	START_BENCHMARK_OPERATION( "JumpSuccessorsSynchronization" );
	// synchronize segmented subspaces with singular
	for ( auto timedSucc : segmentedSuccessors ) {
		SubspaceJumpSuccessors<ComposedRep> nextRes;
		auto enabledTime = singularEnabledTime;
		for ( auto subspace : mSegmentedSubspaces ) {
			enabledTime = enabledTime.intersect( detail::getClockValues( timedSucc.subspaceSets[subspace], mClockCount ) );
		}
		if ( enabledTime.empty() ) continue;
		for ( auto subspace : mSegmentedSubspaces ) {
			nextRes.subspaceSets[subspace] = detail::intersectSegmentWithClock( timedSucc.subspaceSets[subspace], enabledTime, mClockCount );
		}
		for ( auto subspace : mSingularSubspaces ) {
			nextRes.subspaceSets[subspace] = detail::intersectSegmentWithClock( singularSuccessors[subspace], enabledTime, mClockCount );
		}
		for ( auto subspace : mDiscreteSubspaces ) {
			nextRes.subspaceSets[subspace] = discreteSuccessors[subspace];
		}
		// get time interval of jump
		nextRes.time = timedSucc.time;
		res.push_back( nextRes );
	}
	STOP_BENCHMARK_OPERATION( "JumpSuccessorsSynchronization" );
	return res;
}

template <typename LTIRep, typename SingularRep, typename DiscreteRep, typename RectangularRep, typename Automaton>
auto DecompositionalAnalyzer<LTIRep, SingularRep, DiscreteRep, RectangularRep, Automaton>::getSingularJumpSuccessors(
	  const NodeVector& nodes, std::vector<WorkerVariant>& workers, Transition<LocationT>* trans, std::size_t clockIndex ) -> std::pair<TimeInformation<Number>, SubspaceSets> {
	// compute jump successors independently
	for ( auto subspace : mSingularSubspaces ) {
		std::visit( computeSingularJumpSuccessorVisitor{ nodes[subspace] }, workers[subspace] );
	}
	// synchronize by getting the time interval where the jump is enabled across subspaces
	TimeInformation<Number> enabledTime = mGlobalTimeInterval;
	SubspaceSets singularSuccessors;
	for ( auto subspace : mSingularSubspaces ) {
		auto timedSucc = std::visit( getJumpSuccessorVisitor{ trans }, workers[subspace] );
		// we should always get a set, which may be empty
		assert( timedSucc.size() == 1 );
		if ( timedSucc[0].valuationSet.empty() ) {
			return std::make_pair( TimeInformation<Number>( mClockCount ), SubspaceSets() );
		}
		auto subspaceSuccessorSet = timedSucc[0].valuationSet;
		resetUnusedClocks( subspaceSuccessorSet, clockIndex );
		singularSuccessors[subspace] = subspaceSuccessorSet;
		enabledTime = enabledTime.intersect( detail::getClockValues( subspaceSuccessorSet, mClockCount ) );
	}
	// intersect each successor with the obtained enabled time interval
	for ( auto subspace : mSingularSubspaces ) {
		singularSuccessors[subspace] = detail::intersectSegmentWithClock( singularSuccessors[subspace], enabledTime, mClockCount );
	}
	return std::make_pair( enabledTime, singularSuccessors );
}

template <typename LTIRep, typename SingularRep, typename DiscreteRep, typename RectangularRep, typename Automaton>
auto DecompositionalAnalyzer<LTIRep, SingularRep, DiscreteRep, RectangularRep, Automaton>::getDiscreteJumpSuccessors(
	  const NodeVector& nodes, std::vector<WorkerVariant>& workers, Transition<LocationT>* trans ) -> SubspaceSets {
	SubspaceSets succ;
	bool empty = false;
	for ( auto subspace : mDiscreteSubspaces ) {
		if ( empty ) {
			succ[subspace] = ComposedRep::Empty();
			continue;
		}
		auto [containment, predecessor] = intersect( nodes[subspace]->getFlowpipe()[0], trans->getGuard(), subspace );
		if ( containment == CONTAINMENT::NO ) {
			empty = true;
			succ[subspace] = ComposedRep::Empty();
		} else {
			succ[subspace] = std::visit( getJumpSuccessorVisitor{ trans, { { predecessor, 0 } } }, workers[subspace] )[0].valuationSet;
		}
	}
	return succ;
}

template <typename LTIRep, typename SingularRep, typename DiscreteRep, typename RectangularRep, typename Automaton>
auto DecompositionalAnalyzer<LTIRep, SingularRep, DiscreteRep, RectangularRep, Automaton>::getSegmentedJumpSuccessors(
	  const NodeVector& nodes, std::vector<WorkerVariant>& workers, Transition<LocationT>* trans, const TimeInformation<Number>& enabledTime, std::size_t clockIndex ) -> std::vector<SubspaceJumpSuccessors<ComposedRep>> {
	// generator synchronized segments by index and intersects with the guard
	LtiSegmentGen segments{ nodes, mDecomposition, trans->getGuard(), enabledTime, mSegmentedSubspaces };
	// get predecessors by intersecting with guard
	std::map<std::size_t, std::vector<IndexedValuationSet<ComposedRep>>> predecessors;
	for ( auto subspace : mSegmentedSubspaces ) {
		predecessors[subspace] = std::vector<IndexedValuationSet<ComposedRep>>();
	}
	for ( auto indexedSegments = segments.next(); indexedSegments.second.size() > 0; indexedSegments = segments.next() ) {
		for ( auto subspace : mSegmentedSubspaces ) {
			// reset unused clocks to 0
			resetUnusedClocks( indexedSegments.second[subspace], clockIndex );
			predecessors[subspace].push_back( { indexedSegments.second[subspace], indexedSegments.first } );
		}
	}
	std::map<std::size_t, std::vector<TimedValuationSet<ComposedRep>>> subspaceSuccessors;
	for ( auto subspace : mSegmentedSubspaces ) {
		subspaceSuccessors[subspace] = std::visit( getJumpSuccessorVisitor{ trans, predecessors[subspace] }, workers[subspace] );
		if ( subspaceSuccessors[subspace].size() == 0 ) return {};
	}
	// synchronize via the time interval of the jump
	// note: every subspace has the same enabled segments and same aggregation settings, so the time intervals are the same
	if ( std::any_of( subspaceSuccessors.begin(), subspaceSuccessors.end(), []( const auto& s ) { return s.second.empty(); } ) ) return {};
	LtiJumpSuccessorGen synchronizedSuccessors{ subspaceSuccessors, mSegmentedSubspaces };
	std::vector<SubspaceJumpSuccessors<ComposedRep>> res;
	for ( auto succ = synchronizedSuccessors.next(); succ.subspaceSets.size() > 0; succ = synchronizedSuccessors.next() ) {
		res.push_back( succ );
	}
	return res;
}

template <typename LTIRep, typename SingularRep, typename DiscreteRep, typename RectangularRep, typename Automaton>
struct DecompositionalAnalyzer<LTIRep, SingularRep, DiscreteRep, RectangularRep, Automaton>::LtiSegmentGen {
	NodeVector const nodes;
	SegmentInd segmentIndex = 0;
	Decomposition decomposition;
	Condition<Number> cond = Condition<Number>( ConstraintSetT<Number>() );
	TimeInformation<Number> enabledTime;
	std::vector<std::size_t> subspaces;

	LtiSegmentGen( NodeVector const& nodes, Decomposition const& decomposition, const std::vector<std::size_t>& subspaces )
		: nodes( nodes )
		, decomposition( decomposition )
		, subspaces( subspaces ) {}
	LtiSegmentGen( NodeVector const& nodes, Decomposition const& decomposition, Condition<Number> const& cond, const TimeInformation<Number>& enabledTime, const std::vector<std::size_t>& subspaces )
		: nodes( nodes )
		, decomposition( decomposition )
		, cond( cond )
		, enabledTime( enabledTime )
		, subspaces( subspaces ) {}
	std::pair<SegmentInd, SubspaceSets> next() {
		// check if more segments are available
		for ( auto subspace : subspaces ) {
			if ( segmentIndex >= (SegmentInd)nodes[subspace]->getFlowpipe().size() ) {
				return {};
			}
		}
		SubspaceSets res;
		for ( auto subspace : subspaces ) {
			auto& flowpipe = nodes[subspace]->getFlowpipe();
			assert( (SegmentInd)flowpipe.size() > segmentIndex );
			auto [containment, set] = intersect( flowpipe[segmentIndex], cond, subspace );
			set = detail::intersectSegmentWithClock( set, enabledTime, enabledTime.clockCount() );
			if ( containment == CONTAINMENT::NO || set.empty() ) {
				segmentIndex += 1;
				return next();
			}
			res[subspace] = { set };
		}
		segmentIndex += 1;
		return std::make_pair( segmentIndex, res );
	}
};

template <typename LTIRep, typename SingularRep, typename DiscreteRep, typename RectangularRep, typename Automaton>
struct DecompositionalAnalyzer<LTIRep, SingularRep, DiscreteRep, RectangularRep, Automaton>::LtiJumpSuccessorGen {
	const std::map<std::size_t, std::vector<TimedValuationSet<ComposedRep>>> subspaceSuccessors;
	std::vector<std::size_t> subspaces;

	std::size_t firstIndex = 0;
	LtiJumpSuccessorGen( const std::map<std::size_t, std::vector<TimedValuationSet<ComposedRep>>>& subspaceSuccessors, const std::vector<std::size_t>& subspaces )
		: subspaceSuccessors( subspaceSuccessors )
		, subspaces( subspaces ) {}
	SubspaceJumpSuccessors<ComposedRep> next() {
		if ( subspaces.size() == 0 ) {
			return {};
		} else if ( firstIndex >= subspaceSuccessors.at( subspaces[0] ).size() ) {
			return {};
		} else {
			const auto nextInterval = subspaceSuccessors.at( subspaces[0] )[firstIndex].time;
			SubspaceSets res;
			for ( auto subspace : subspaces ) {
				bool found = false;
				for ( const auto succ : subspaceSuccessors.at( subspace ) ) {
					if ( nextInterval == succ.time ) {
						res[subspace] = succ.valuationSet;
						found = true;
					}
				}
				if ( !found ) {
					firstIndex += 1;
					return next();
				}
			}
			firstIndex += 1;
			return SubspaceJumpSuccessors<ComposedRep>{ nextInterval, res };
		}
	}
};

template <typename LTIRep, typename SingularRep, typename DiscreteRep, typename RectangularRep, typename Automaton>
auto DecompositionalAnalyzer<LTIRep, SingularRep, DiscreteRep, RectangularRep, Automaton>::synchronizeAndResetClocks( const RepVector& sets, const Condition<Number>& dependencies ) -> std::pair<Condition<Number>, RepVector> {
	assert( std::all_of( sets.begin(), sets.end(), []( auto const& s ) { return !s.empty(); } ) );
	// get sets for non-discrete subspaces
	RepVector res( sets.size() );
	std::vector<HPolytope<Number>> subspacePolytopes;
	for ( std::size_t subspace = 0; subspace < mDecomposition.subspaces.size(); ++subspace ) {
		if ( mDecomposition.subspaceTypes[subspace] != DynamicType::discrete ) {
			subspacePolytopes.push_back( std::visit( genericConvertAndGetVisitor<HPolytope<Number>>(), sets[subspace].getSet() ) );
		}
	}
	START_BENCHMARK_OPERATION( "ComplexityReductionCompose" );
	HPolytope<Number> composedSuccessors = detail::composeSubspaces( subspacePolytopes, dependencies, mDecompositionWithoutDiscrete, mClockCount );
	STOP_BENCHMARK_OPERATION( "ComplexityReductionCompose" );
	if ( composedSuccessors.empty() ) {
		return std::make_pair( Condition<Number>( ConstraintSetT<Number>() ), res );
	}
	auto newDependencies = detail::getDependencies( composedSuccessors, mDecompositionWithoutDiscrete );
	START_BENCHMARK_OPERATION( "ComplexityReductionDecompose" );
	subspacePolytopes = detail::decompose( composedSuccessors, mDecompositionWithoutDiscrete, mClockCount );
	STOP_BENCHMARK_OPERATION( "ComplexityReductionDecompose" );
	std::size_t newDecompIndex = 0;
	for ( std::size_t originalDecompIndex = 0; originalDecompIndex < sets.size(); ++originalDecompIndex ) {
		if ( mDecomposition.subspaceTypes[originalDecompIndex] == DynamicType::discrete ) {
			res[originalDecompIndex] = sets[originalDecompIndex];
			continue;
		}
		ComposedRep segment;
		switch ( mDecomposition.subspaceTypes[originalDecompIndex] ) {
			case DynamicType::timed:
				[[fallthrough]];
			case DynamicType::singular:
				segment.setSet( SingularRep{ subspacePolytopes[newDecompIndex].matrix(), subspacePolytopes[newDecompIndex].vector() } );
				break;
			case DynamicType::rectangular:
				segment.setSet( RectangularRep{ subspacePolytopes[newDecompIndex].matrix(), subspacePolytopes[newDecompIndex].vector() } );
				break;
			default:
				segment.setSet( LTIRep{ subspacePolytopes[newDecompIndex].matrix(), subspacePolytopes[newDecompIndex].vector() } );
		}
		res[originalDecompIndex] = segment;
		newDecompIndex += 1;
	}
	return std::make_pair( newDependencies, res );
}

}  // namespace hypro
