#include "DecompositionalAnalyzer.h"

namespace hypro {

template <typename LTIRep, typename SingularRep, typename DiscreteRep, typename RectangularRep>
auto DecompositionalAnalyzer<LTIRep, SingularRep, DiscreteRep, RectangularRep>::run() -> DecompositionalResult {
	std::vector<TimeTransformationCache<Number>> cache( mDecomposition.subspaces.size(), TimeTransformationCache<Number>() );
	auto workers = initializeWorkers( cache );

	while ( !mWorkQueue.empty() ) {
		COUNT( "Nodes" );
		auto nextInQueue = mWorkQueue.front();
		mWorkQueue.pop_front();
		NodeVector currentNodes = nextInQueue.nodes;
		ReachTreeNode<Condition<Number>>* depNode = nextInQueue.dependencyNode;
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

		START_BENCHMARK_OPERATION("TimeSuccessors");
		// Time successors
		TimeInformation<Number> invariantSatisfyingTime = computeTimeSuccessorsGetEnabledTime( currentNodes, workers, clockIndex );
		removeRedundantSegments( currentNodes );
		intersectSubspacesWithClock( currentNodes, invariantSatisfyingTime );
		STOP_BENCHMARK_OPERATION("TimeSuccessors");

		START_BENCHMARK_OPERATION("SafetyCheck");
		// Check safety
		for ( auto badState : detail::collectBadStates( mHybridAutomaton, currentLoc ) ) {
			if ( !isSafe( currentNodes, dependencies, badState ) ) {
				return { Failure{ currentNodes[0] } };
			}
		}
		STOP_BENCHMARK_OPERATION("SafetyCheck");

		// Check jump depth
		if ( currentNodes[0]->getDepth() == mFixedParameters.jumpDepth ) {
			continue;
		}

		for ( const auto& transition : currentLoc->getTransitions() ) {
			START_BENCHMARK_OPERATION("JumpSuccessors");
			std::vector<SubspaceJumpSuccessors<Rep>> jumpSuccessors = getJumpSuccessors( currentNodes, workers, transition.get(), clockIndex );
			STOP_BENCHMARK_OPERATION("JumpSuccessors");
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
					COUNT("ComplexityReductionSteps");
					START_BENCHMARK_OPERATION("ComplexityReduction");
					nextIndex = 0;
					std::tie( dependencies, subspaceSets ) = complexityReduction( subspaceSets, dependencies );
					STOP_BENCHMARK_OPERATION("ComplexityReduction");
					if ( subspaceSets.size() == 0 ) continue;
				}

				// create child nodes and push to queue
				NodeVector childNodes( mDecomposition.subspaces.size() );
				for ( std::size_t subspace = 0; subspace < mDecomposition.subspaces.size(); ++subspace ) {
					auto& subspaceChild = currentNodes[subspace]->addChild( subspaceSets[subspace], currentNodes[subspace]->getTimings() + timedSuccessor.time, transition.get() );
					childNodes[subspace] = &subspaceChild;
				}
				mWorkQueue.push_back( detail::decompositionalQueueEntry<Rep>{
					  nextIndex,
					  childNodes,
					  &( depNode->addChild( dependencies, depNode->getTimings() + timedSuccessor.time, transition.get() ) ) } );
			}
		}
	}
	return { DecompositionalSuccess{} };
}

template <typename LTIRep, typename SingularRep, typename DiscreteRep, typename RectangularRep>
auto DecompositionalAnalyzer<LTIRep, SingularRep, DiscreteRep, RectangularRep>::initializeWorkers( std::vector<TimeTransformationCache<Number>>& cache ) -> std::vector<WorkerVariant> {
	std::vector<WorkerVariant> workers;
	for ( std::size_t subspace = 0; subspace < mDecomposition.subspaces.size(); ++subspace ) {
		switch ( mDecomposition.subspaceTypes[subspace] ) {
			case DynamicType::discrete:
				workers.push_back( DiscreteWorker<DiscreteRep>{ *mHybridAutomaton,
																mParameters,
																subspace } );
				break;
			case DynamicType::timed:
				[[fallthrough]];
			case DynamicType::singular:
				workers.push_back( SingularWorker<SingularRep>{ *mHybridAutomaton,
																mFixedParameters,
																subspace } );
				break;
			default:
				workers.push_back( LTIWorker<LTIRep>{
					  *mHybridAutomaton,
					  mParameters,
					  mFixedParameters.localTimeHorizon,
					  cache[subspace],
					  subspace } );
		}
	}
	return workers;
}

template <typename LTIRep, typename SingularRep, typename DiscreteRep, typename RectangularRep>
bool DecompositionalAnalyzer<LTIRep, SingularRep, DiscreteRep, RectangularRep>::checkConsistency( NodeVector& currentNodes ) {
	if ( std::any_of( currentNodes.begin(), currentNodes.end(), []( const auto& node ) { return node->getInitialSet().isEmpty(); } ) ) {
		return false;
	}
	return true;
}

template <typename LTIRep, typename SingularRep, typename DiscreteRep, typename RectangularRep>
auto DecompositionalAnalyzer<LTIRep, SingularRep, DiscreteRep, RectangularRep>::computeTimeSuccessorsGetEnabledTime(
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
	for ( auto subspace : mSegmentedSubspaces ) {
		carl::Interval<Number> currentTimeInterval = mClockCount > 0 ? invariantSatTime.getTimeInterval( clockIndex ) : carl::Interval<Number>::unboundedInterval();
		int timeHorizon = currentTimeInterval.isUnbounded() ? -1 : std::ceil( carl::convert<Number, double>( currentTimeInterval.upper()  / mParameters.timeStep ) );
		TimeInformation<Number> invariantSatTimeSubspace = std::visit( computeTimeSuccessorVisitor{
																			 currentNodes[subspace], mClockCount, timeHorizon },
																	   workers[subspace] );
		invariantSatTime = invariantSatTime.intersect( invariantSatTimeSubspace );
	}
	return invariantSatTime;
}

template <typename LTIRep, typename SingularRep, typename DiscreteRep, typename RectangularRep>
void DecompositionalAnalyzer<LTIRep, SingularRep, DiscreteRep, RectangularRep>::intersectSubspacesWithClock(
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

template <typename LTIRep, typename SingularRep, typename DiscreteRep, typename RectangularRep>
void DecompositionalAnalyzer<LTIRep, SingularRep, DiscreteRep, RectangularRep>::removeRedundantSegments( NodeVector& currentNodes ) {
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

template <typename LTIRep, typename SingularRep, typename DiscreteRep, typename RectangularRep>
bool DecompositionalAnalyzer<LTIRep, SingularRep, DiscreteRep, RectangularRep>::isSafe(
	  const NodeVector& nodes, const Condition<Number>& dependencies, const Condition<Number>& badState ) {
	// time interval where all subspaces can be bad
	TimeInformation<Number> badTimeInterval = mGlobalTimeInterval;
	// Synchronize segmented subspaces and intersect them with the bad state
	RepVector subspaceSets( mDecomposition.subspaces.size() );
	// each segment is paired with the single segment from each singular subspace
	for ( auto subspace : mSingularSubspaces ) {
		if ( badTimeInterval.empty() ) {
			return true;
		}
		auto [containment, set] = intersect( nodes[subspace]->getFlowpipe()[0], badState, subspace );
		if ( containment == CONTAINMENT::NO ) {
			// no bad state intersection in some subspace
			return true;
		} else {
			set = detail::intersectSegmentWithClock( set, badTimeInterval, mClockCount );
			badTimeInterval = badTimeInterval.intersect( detail::getClockValues( set, mClockCount ) );
			subspaceSets[subspace] = set;
		}
	}
	for ( auto subspace : mDiscreteSubspaces ) {
		auto [containment, set] = intersect( nodes[subspace]->getFlowpipe()[0], badState, subspace );
		if ( containment == CONTAINMENT::NO ) {
			// no bad state intersection in some subspace
			return true;
		} else {
			subspaceSets[subspace] = set;
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

		HPolytope<Number> composedPolytope = detail::composeSubspaceConstraints( hpols, dependencies, mDecomposition, mClockCount );
		if ( !composedPolytope.empty() ) {
			return false;
		}
	}
	// note: only segments that have non-empty intersection with bad state in all subspaces are returned by generator
	LtiSegmentGen segments{ nodes, mDecomposition, badState, badTimeInterval, mSegmentedSubspaces };
	// iterate over each synchronized segment and check if composition is non empty
	for ( auto badSegment = segments.next().second; badSegment.size() > 0; badSegment = segments.next().second ) {
		if ( mClockCount == 0 ) {
			// all subspaces unsafe at some point. without synchronization we cannot tell if they are unsafe at the same time or not.
			return false;
		}
		for ( auto subspace : mSegmentedSubspaces ) {
			subspaceSets[subspace] = badSegment[subspace];
		}
		std::vector<HPolytope<Number>> hpols;
		std::transform( subspaceSets.begin(), subspaceSets.end(), std::back_inserter( hpols ), [=]( auto& state ) {
			return std::visit( genericConvertAndGetVisitor<HPolytope<Number>>(), state.getSet() );
		} );
		HPolytope<Number> composedPolytope = detail::composeSubspaceConstraints( hpols, dependencies, mDecomposition, mClockCount );
		if ( !composedPolytope.empty() ) {
			return false;
		}
	}
	return true;
}

template <typename LTIRep, typename SingularRep, typename DiscreteRep, typename RectangularRep>
void DecompositionalAnalyzer<LTIRep, SingularRep, DiscreteRep, RectangularRep>::resetClock( Rep& segment, std::size_t clockIndex ) {
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

template <typename LTIRep, typename SingularRep, typename DiscreteRep, typename RectangularRep>
auto DecompositionalAnalyzer<LTIRep, SingularRep, DiscreteRep, RectangularRep>::getJumpSuccessors(
	  const NodeVector& nodes, std::vector<WorkerVariant> workers,
	  Transition<Number>* trans,
	  std::size_t clockIndex )
	  -> std::vector<SubspaceJumpSuccessors<Rep>> {
	// res holds all synchronized jump successors
	std::vector<SubspaceJumpSuccessors<Rep>> res;
	// Collect single successor set (per subspace) for singular subspaces and synchronize them
	START_BENCHMARK_OPERATION("JumpSuccessorsSingular");
	auto [singularEnabledTime, singularSuccessors] = getSingularJumpSuccessors( nodes, workers, trans, clockIndex );
	STOP_BENCHMARK_OPERATION("JumpSuccessorsSingular");
	if ( singularEnabledTime.empty() ) {
		return {};
	}
	START_BENCHMARK_OPERATION("JumpSuccessorsDiscrete");
	auto discreteSuccessors = getDiscreteJumpSuccessors( nodes, workers, trans );
	if ( mSegmentedSubspaces.size() == 0 ) {
		// no segmented subspace, so the segment indexes are ignored -> set them to 0
		SubspaceJumpSuccessors<Rep> succ{ carl::Interval<SegmentInd>( 0 ), singularSuccessors };
		for ( auto subspace : mDiscreteSubspaces ) {
			succ.subspaceSets[subspace] = discreteSuccessors[subspace];
		}
		STOP_BENCHMARK_OPERATION("JumpSuccessorsDiscrete");
		return { succ };
	}
	STOP_BENCHMARK_OPERATION("JumpSuccessorsDiscrete");
	START_BENCHMARK_OPERATION("JumpSuccessorsLTI");
	// collect synchronized successors for segmented subspaces
	std::vector<SubspaceJumpSuccessors<Rep>> segmentedSuccessors = getSegmentedJumpSuccessors( nodes, workers, trans, singularEnabledTime, clockIndex );
	STOP_BENCHMARK_OPERATION("JumpSuccessorsLTI");

	START_BENCHMARK_OPERATION("JumpSuccessorsSynchronization");
	// synchronize segmented subspaces with singular
	for ( auto timedSucc : segmentedSuccessors ) {
		SubspaceJumpSuccessors<Rep> nextRes;
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
	STOP_BENCHMARK_OPERATION("JumpSuccessorsSynchronization");
	return res;
}

template <typename LTIRep, typename SingularRep, typename DiscreteRep, typename RectangularRep>
auto DecompositionalAnalyzer<LTIRep, SingularRep, DiscreteRep, RectangularRep>::getSingularJumpSuccessors(
	  const NodeVector& nodes, std::vector<WorkerVariant>& workers, Transition<Number>* trans, std::size_t clockIndex ) -> std::pair<TimeInformation<Number>, SubspaceSets> {
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
		if ( timedSucc[ 0 ].valuationSet.empty() ) {
			return std::make_pair( TimeInformation<Number>( mClockCount ), SubspaceSets() );
		}
		auto subspaceSuccessorSet = timedSucc[0].valuationSet;
		resetClock( subspaceSuccessorSet, clockIndex );
		singularSuccessors[subspace] = subspaceSuccessorSet;
		enabledTime = enabledTime.intersect( detail::getClockValues( subspaceSuccessorSet, mClockCount ) );
	}
	// intersect each successor with the obtained enabled time interval
	for ( auto subspace : mSingularSubspaces ) {
		singularSuccessors[subspace] = detail::intersectSegmentWithClock( singularSuccessors[subspace], enabledTime, mClockCount );
	}
	return std::make_pair( enabledTime, singularSuccessors );
}

template <typename LTIRep, typename SingularRep, typename DiscreteRep, typename RectangularRep>
auto DecompositionalAnalyzer<LTIRep, SingularRep, DiscreteRep, RectangularRep>::getDiscreteJumpSuccessors(
	  const NodeVector& nodes, std::vector<WorkerVariant>& workers, Transition<Number>* trans ) -> SubspaceSets {
	SubspaceSets succ;
	bool empty = false;
	for ( auto subspace : mDiscreteSubspaces ) {
		if ( empty ) {
			succ[subspace] = Rep::Empty();
			continue;
		}
		auto [containment, predecessor] = intersect( nodes[subspace]->getFlowpipe()[0], trans->getGuard(), subspace );
		if ( containment == CONTAINMENT::NO ) {
			empty = true;
			succ[subspace] = Rep::Empty();
		} else {
			succ[subspace] = std::visit( getJumpSuccessorVisitor{ trans, { { predecessor, 0 } } }, workers[subspace] )[0].valuationSet;
		}
	}
	return succ;
}

template <typename LTIRep, typename SingularRep, typename DiscreteRep, typename RectangularRep>
auto DecompositionalAnalyzer<LTIRep, SingularRep, DiscreteRep, RectangularRep>::getSegmentedJumpSuccessors(
	  const NodeVector& nodes, std::vector<WorkerVariant>& workers, Transition<Number>* trans, const TimeInformation<Number>& enabledTime, std::size_t clockIndex ) -> std::vector<SubspaceJumpSuccessors<Rep>> {
	// generator synchronized segments by index and intersects with the guard
	LtiSegmentGen segments{ nodes, mDecomposition, trans->getGuard(), enabledTime, mSegmentedSubspaces };
	// get predecessors by intersecting with guard
	std::map<std::size_t, std::vector<IndexedValuationSet<Rep>>> predecessors;
	for ( auto subspace : mSegmentedSubspaces ) {
		predecessors[subspace] = std::vector<IndexedValuationSet<Rep>>();
	}
	for ( auto indexedSegments = segments.next(); indexedSegments.second.size() > 0; indexedSegments = segments.next() ) {
		for ( auto subspace : mSegmentedSubspaces ) {
			// reset unused clocks to 0
			resetClock( indexedSegments.second[subspace], clockIndex );
			predecessors[subspace].push_back( { indexedSegments.second[subspace], indexedSegments.first } );
		}
	}
	std::map<std::size_t, std::vector<TimedValuationSet<Rep>>> subspaceSuccessors;
	for ( auto subspace : mSegmentedSubspaces ) {
		subspaceSuccessors[subspace] = std::visit( getJumpSuccessorVisitor{ trans, predecessors[subspace] }, workers[subspace] );
		if ( subspaceSuccessors[subspace].size() == 0 ) return {};
	}
	// synchronize via the time interval of the jump
	// note: every subspace has the same enabled segments and same aggregation settings, so the time intervals are the same
	if ( std::any_of( subspaceSuccessors.begin(), subspaceSuccessors.end(), []( const auto& s ) { return s.second.empty(); } ) ) return {};
	LtiJumpSuccessorGen synchronizedSuccessors{ subspaceSuccessors, mSegmentedSubspaces };
	std::vector<SubspaceJumpSuccessors<Rep>> res;
	for ( auto succ = synchronizedSuccessors.next(); succ.subspaceSets.size() > 0; succ = synchronizedSuccessors.next() ) {
		res.push_back( succ );
	}
	return res;
}

template <typename LTIRep, typename SingularRep, typename DiscreteRep, typename RectangularRep>
struct DecompositionalAnalyzer<LTIRep, SingularRep, DiscreteRep, RectangularRep>::LtiSegmentGen {
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

template <typename LTIRep, typename SingularRep, typename DiscreteRep, typename RectangularRep>
struct DecompositionalAnalyzer<LTIRep, SingularRep, DiscreteRep, RectangularRep>::LtiJumpSuccessorGen {
	const std::map<std::size_t, std::vector<TimedValuationSet<Rep>>> subspaceSuccessors;
	std::vector<std::size_t> subspaces;

	std::size_t firstIndex = 0;
	LtiJumpSuccessorGen( const std::map<std::size_t, std::vector<TimedValuationSet<Rep>>>& subspaceSuccessors, const std::vector<std::size_t>& subspaces )
		: subspaceSuccessors( subspaceSuccessors )
		, subspaces( subspaces ) {}
	SubspaceJumpSuccessors<Rep> next() {
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
			return SubspaceJumpSuccessors<Rep>{ nextInterval, res };
		}
	}
};

template <typename LTIRep, typename SingularRep, typename DiscreteRep, typename RectangularRep>
auto DecompositionalAnalyzer<LTIRep, SingularRep, DiscreteRep, RectangularRep>::complexityReduction( const RepVector& sets, const Condition<Number>& dependencies ) -> std::pair<Condition<Number>, RepVector> {
	RepVector res( sets.size() );
	std::vector<HPolytope<Number>> subspacePolytopes;
	std::transform( sets.begin(), sets.end(), std::back_inserter( subspacePolytopes ), [=]( auto& segment ) {
		return std::visit( genericConvertAndGetVisitor<HPolytope<Number>>(), segment.getSet() );
	} );
	START_BENCHMARK_OPERATION("ComplexityReductionCompose");
	HPolytope<Number> composedSuccessors = detail::composeSubspaces( subspacePolytopes, dependencies, mDecomposition, mClockCount );
	STOP_BENCHMARK_OPERATION("ComplexityReductionCompose");
	if ( composedSuccessors.empty() ) {
		return std::make_pair( Condition<Number>( ConstraintSetT<Number>() ), res );
	}
	auto newDependencies = detail::getDependencies( composedSuccessors, mDecomposition );
	START_BENCHMARK_OPERATION("ComplexityReductionDecompose");
	subspacePolytopes = detail::decompose( composedSuccessors, mDecomposition, mClockCount );
	STOP_BENCHMARK_OPERATION("ComplexityReductionDecompose");
	for ( std::size_t subspace = 0; subspace < sets.size(); ++subspace ) {
		auto pol = subspacePolytopes[subspace];
		Rep segment;
		switch ( mDecomposition.subspaceTypes[subspace] ) {
			case DynamicType::timed:
				[[fallthrough]];
			case DynamicType::singular:
				segment.setSet( SingularRep{ pol.matrix(), pol.vector() } );
				break;
			case DynamicType::discrete:
				segment.setSet( DiscreteRep{ pol.matrix(), pol.vector() } );
				break;
			case DynamicType::rectangular:
				segment.setSet( RectangularRep{ pol.matrix(), pol.vector() } );
				break;
			default:
				segment.setSet( LTIRep{ pol.matrix(), pol.vector() } );
		}
		res[subspace] = segment;
	}
	return std::make_pair( newDependencies, res );
}

}  // namespace hypro
