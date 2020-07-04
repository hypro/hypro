#include "LTIWorker.h"

namespace hypro {

template <typename Representation>
template <typename OutputIt>
REACHABILITY_RESULT LTIWorker<Representation>::computeTimeSuccessors( const Representation& initialSet, Location<Number> const* loc, OutputIt out ) const {
	auto timeStep = mSettings.timeStep;
	Representation firstSegment = constructFirstSegment( initialSet, loc->getLinearFlow(), mTrafoCache.transformationMatrix( loc, timeStep ), timeStep );

	auto [containment, segment] = intersect( firstSegment, loc->getInvariant() );
	//If the first segment did not fulfill the invariant of the location, the jump here should not have been made
	assert( containment != CONTAINMENT::NO );

	// insert segment
	*out = segment;
	++out;

	// intersect with badstates
	std::tie( containment, std::ignore ) = ltiIntersectBadStates( segment, loc, mHybridAutomaton );
	if ( containment != CONTAINMENT::NO ) {
		// Todo: memorize the intersecting state set and keep state.
		return REACHABILITY_RESULT::UNKNOWN;
	}

	// while not done
	for ( size_t segmentCount = 1; segmentCount < mNumSegments; ++segmentCount ) {
		segment = applyTimeEvolution( segment, mTrafoCache.transformationMatrix( loc, timeStep ) );
		std::tie( containment, segment ) = intersect( segment, loc->getInvariant() );
		if ( containment == CONTAINMENT::NO ) {
			return REACHABILITY_RESULT::SAFE;
		}

		*out = segment;
		++out;

		// intersect with badstates
		std::tie( containment, std::ignore ) = ltiIntersectBadStates( segment, loc, mHybridAutomaton );
		if ( containment != CONTAINMENT::NO ) {
			// Todo: memorize the intersecting state set and keep state.
			return REACHABILITY_RESULT::UNKNOWN;
		}
	}
	return REACHABILITY_RESULT::SAFE;
}

template <typename Representation>
std::vector<JumpSuccessor<Representation>> LTIWorker<Representation>::computeJumpSuccessors( std::vector<Representation> const& flowpipe, Location<Number> const* loc ) const {
	//transition x enabled segments, segment ind
	std::vector<EnabledSets<Representation>> enabledSegments{};

	for ( const auto& transition : loc->getTransitions() ) {
		auto& currentSucc = enabledSegments.emplace_back( EnabledSets<Representation>{ transition.get() } );

		SegmentInd cnt = 0;
		for ( auto const& valuationSet : flowpipe ) {
			auto [containment, intersected] = intersect( valuationSet, transition->getGuard() );

			if ( containment != CONTAINMENT::NO ) {
				currentSucc.valuationSets.push_back( { intersected, cnt } );
			}
			++cnt;
		}
	}

	std::vector<JumpSuccessor<Representation>> successors{};

	//aggregation
	// for each transition
	for ( auto& [transition, valuationSets] : enabledSegments ) {
		// no aggregation
		std::size_t blockSize = 1;
		if ( mSettings.aggregation == AGG_SETTING::AGG ) {
			if ( mSettings.clustering > 0 ) {
				blockSize = ( valuationSets.size() + mSettings.clustering ) / mSettings.clustering;	 //division rounding up
			} else {
				blockSize = valuationSets.size();
			}

		} else if ( mSettings.aggregation == AGG_SETTING::MODEL && transition->getAggregation() != Aggregation::none ) {
			if ( transition->getAggregation() == Aggregation::clustering ) {
				blockSize = ( blockSize + transition->getClusterBound() ) / transition->getClusterBound();	//division rounding up
			}
		}
		successors.emplace_back( JumpSuccessor<Representation>{ transition, aggregate( blockSize, valuationSets ) } );
	}

	// applyReset
	for ( auto& [transition, valuationSets] : successors ) {
		for ( auto it = valuationSets.begin(); it != valuationSets.end(); ) {
			it->valuationSet = applyReset( it->valuationSet, transition->getReset() );
			CONTAINMENT containment;
			std::tie( containment, it->valuationSet ) = intersect( it->valuationSet, transition->getTarget()->getInvariant() );
			if ( containment == CONTAINMENT::NO ) {
				it = valuationSets.erase( it );
			} else {
				++it;
			}
		}
	}

	return successors;
}

}  // namespace hypro
