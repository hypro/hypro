#include "LTIWorker.h"

namespace hypro {

template <typename Representation>
REACHABILITY_RESULT LTIWorker<Representation>::computeForwardReachability( Location<Number> const* loc, const Representation& initialSet, const matrix_t<Number>& transformation ) {
	if ( computeTimeSuccessors( loc, initialSet, transformation ) == REACHABILITY_RESULT::UNKNOWN ) {
		return REACHABILITY_RESULT::UNKNOWN;
	}
	computeJumpSuccessors();
	return REACHABILITY_RESULT::SAFE;
}

template <typename Representation>
REACHABILITY_RESULT LTIWorker<Representation>::computeTimeSuccessors( Location<Number> const* loc, const Representation& initialSet, const matrix_t<Number>& transformation ) {
	auto timeStep = mSettings.timeStep;
	Representation firstSegment = constructFirstSegment( initialSet, loc->getLinearFlow(), mTrafoCache.transformationMatrix( loc, timeStep ), timeStep );

	auto [containment, segment] = intersect( firstSegment, loc->getInvariant() );
	if ( containment == CONTAINMENT::NO ) {
		return REACHABILITY_RESULT::SAFE;
	}

	// add state to flowpipe
	mFlowpipe.emplace_back( segment );

	std::tie( containment, segment ) = ltiIntersectBadStates( segment, loc, mHybridAutomaton );
	if ( containment != CONTAINMENT::NO ) {
		// Todo: memorize the intersecting state set and keep state.
		return REACHABILITY_RESULT::UNKNOWN;
	}

	// while not done
	size_t segmentCounter = 1;
	while ( requireTimeSuccessorComputation( segmentCounter ) ) {
		auto currentSegment = applyTimeEvolution( segment, mTrafoCache.transformationMatrix( loc, timeStep ) );
		std::tie( containment, segment ) = intersect( currentSegment, loc->getInvariant() );
		if ( containment == CONTAINMENT::NO ) {
			return REACHABILITY_RESULT::SAFE;
		}

		// add state to flowpipe
		mFlowpipe.emplace_back( segment );
		++segmentCounter;

		std::tie( containment, segment ) = ltiIntersectBadStates( segment, loc, mHybridAutomaton );
		if ( containment != CONTAINMENT::NO ) {
			// Todo: memorize the intersecting state set and keep state.
			return REACHABILITY_RESULT::UNKNOWN;
		}
	}
	return REACHABILITY_RESULT::SAFE;
}

template <typename Representation>
void LTIWorker<Representation>::computeJumpSuccessors( Location<Number> const* loc, AnalysisParameters settings ) {
	JumpSuccessors succ;
	SegmentInd cnt = 0;

	// timing information
	std::map<Transition<Number>*, HierarchicalIntervalVector<CONTAINMENT, SegmentInd>> timings;
	std::vector<CONTAINMENT> order{CONTAINMENT::BOT, CONTAINMENT::PARTIAL, CONTAINMENT::FULL, CONTAINMENT::NO};

	for ( auto& valuationSet : mFlowpipe ) {
		for ( const auto& transition : loc->getTransitions() ) {
			auto [containment, valuationSet] = intersect( valuationSet, transition->getGuard() );

			if ( containment != CONTAINMENT::NO ) {
				succ[transition.get()].emplace_back( {valuationSet, cnt} );

				// prepare timing information
				auto it = timings.find( transition );
				if ( transition == timings.end() ) {
					timings.emplace( std::make_pair( transition, {order} ) );
				}
				timings[transition].insertInterval( containment, carl::Interval<SegmentInd>( cnt, cnt + 1 ) );
			}
		}
		++cnt;
	}

	// aggregation, keep track of segInd
	// Entscheidung: AGG zusammenhängende Sequenzen von Segmenten.
	for ( auto& [transition, segments] : succ ) {
		// no aggregation
		if ( settings.aggregation == AGG_SETTING::AGG ) {
			if ( settings.clustering > 0 ) {
				size_t blockSize = ( segments.size() + 1 ) / settings.clusterSize;	//division rounding up
				succ[transition] = aggregate( blockSize, segments );
			} else {
				size_t blockSize = segments.size();
				succ[transition] = aggregate( blockSize, segments );
			}

		} else if ( settings.aggregation == AGG_SETTING::MODEL && transition.getAggregation() != Aggregation::none ) {
			size_t blockSize = segments.size();
			if ( transition.getAggregation() == Aggregation::clustering ) {
				blockSize = ( blockSize + 1 ) / transition->getClusterBound();	//division rounding up
			}
			succ[transition] = aggregate( blockSize, segments );
		}
	}

	// return val: std::map<Transition<Number>*, std::vector<std::pair<Representation, carl::Interval<SegmentInd>>>>
	// applyReset
}

template <typename Representation>
void LTIWorker<Representation>::postProcessJumpSuccessors( const JumpSuccessors& guardSatisfyingSets ) {
	ltiJumpHandler<Representation> jmpHandler;
	mJumpSuccessorSets = jmpHandler.applyJump( guardSatisfyingSets, nullptr, mSettings );
}

}  // namespace hypro
