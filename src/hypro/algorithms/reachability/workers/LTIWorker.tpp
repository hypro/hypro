#include "LTIWorker.h"

namespace hypro {

template <typename Representation>
REACHABILITY_RESULT LTIWorker<Representation>::computeForwardReachability( Location<Number> const* loc, const Representation& initialSet ) {
	if ( computeTimeSuccessors( loc, initialSet ) == REACHABILITY_RESULT::UNKNOWN ) {
		return REACHABILITY_RESULT::UNKNOWN;
	}
	computeJumpSuccessors();
	return REACHABILITY_RESULT::SAFE;
}

template <typename Representation>
REACHABILITY_RESULT LTIWorker<Representation>::computeTimeSuccessors( Location<Number> const* loc, const Representation& initialSet ) {
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
std::vector<JumpSuccessor<Representation>> LTIWorker<Representation>::computeJumpSuccessors( Location<Number> const* loc, AnalysisParameters settings ) {
	//transition x enabled segments, segment ind
	std::vector<EnabledSets<Representation>> enabledSegments{};

	for ( const auto& transition : loc->getTransitions() ) {
		auto& currentSucc = enabledSegments.emplace_back( &transition );

		SegmentInd cnt = 0;
		for ( auto& valuationSet : mFlowpipe ) {
			CONTAINMENT containment;
			std::tie( containment, valuationSet ) = intersect( valuationSet, transition->getGuard() );

			if ( containment != CONTAINMENT::NO ) {
				currentSucc.emplace_back( valuationSet, cnt );
			}
			++cnt;
		}
	}

	std::vector<JumpSuccessor<Representation>> successors{};

	// aggregation, keep track of segInd
	// Entscheidung: AGG zusammenhängende Sequenzen von Segmenten.
	// for each transition
	for ( auto& [transition, valuationSets] : enabledSegments ) {
		// no aggregation
		std::size_t blockSize = 1;
		if ( settings.aggregation == AGG_SETTING::AGG ) {
			if ( settings.clustering > 0 ) {
				size_t blockSize = ( valuationSets.size() + settings.clustering ) / settings.clustering;  //division rounding up
			} else {
				size_t blockSize = valuationSets.size();
			}

		} else if ( settings.aggregation == AGG_SETTING::MODEL && transition.getAggregation() != Aggregation::none ) {
			if ( transition.getAggregation() == Aggregation::clustering ) {
				blockSize = ( blockSize + transition->getClusterBound() ) / transition->getClusterBound();	//division rounding up
			}
		}
		successors.emplace_back( transition, aggregate( blockSize, valuationSets ) );
	}

	// applyReset
	for ( auto& [transition, valuationSets] : successors ) {
		valuationSets = applyReset( transition, valuationSets );
		for ( auto setIt = valuationSets.begin(); setIt != valuationSets.end(); ) {
			CONTAINMENT containment;
			std::tie( containment, *setIt ) = intersect( *setIt, transition->getTarget()->getInvariant() );
			if ( containment == CONTAINMENT::NO ) {
				setIt = valuationSets.erase( setIt );
			} else {
				++setIt;
			}
		}
	}

	return successors;
}

}  // namespace hypro
