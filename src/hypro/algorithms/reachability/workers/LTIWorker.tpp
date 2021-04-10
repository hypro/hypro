#include "LTIWorker.h"

namespace hypro {

template <typename Representation>
template <typename OutputIt>
REACHABILITY_RESULT LTIWorker<Representation>::computeTimeSuccessors( const Representation& initialSet, Location<Number> const* loc, OutputIt out ) const {
	Representation firstSegment = constructFirstSegment( initialSet, loc->getLinearFlow(), mTrafoCache.transformationMatrix( loc, mSettings.timeStep ), mSettings.timeStep );

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
		segment = applyTimeEvolution( segment, mTrafoCache.transformationMatrix( loc, mSettings.timeStep ) );
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

template <class Representation>
auto LTIWorker<Representation>::getJumpSuccessors( std::vector<Representation> const& flowpipe, Transition<Number> const* transition ) const -> JumpSuccessorGen {
	std::size_t blockSize = 1;
	if ( mSettings.aggregation == AGG_SETTING::AGG ) {
		if ( mSettings.clustering > 0 ) {
			blockSize = ( flowpipe.size() + mSettings.clustering ) / mSettings.clustering;	//division rounding up
		} else {
			blockSize = flowpipe.size();
		}

	} else if ( mSettings.aggregation == AGG_SETTING::MODEL && transition->getAggregation() != Aggregation::none ) {
		if ( transition->getAggregation() == Aggregation::clustering ) {
			blockSize = ( blockSize + transition->getClusterBound() ) / transition->getClusterBound();	//division rounding up
		}
	}
	return JumpSuccessorGen{ flowpipe, transition, blockSize };
}

template <class Representation>
struct LTIWorker<Representation>::EnabledSegmentsGen {
	std::vector<Representation> const* flowpipe;
	Transition<Number> const* transition;
	std::size_t current = 0;

	EnabledSegmentsGen( std::vector<Representation> const* flowpipe, Transition<Number> const* transition )
		: flowpipe( flowpipe )
		, transition( transition ) {}

	std::optional<std::pair<std::vector<Representation>, SegmentInd>> next() {
		std::vector<Representation> enabledSegments{};

		SegmentInd firstEnabled{};

		// find next enabled segment
		for ( ; current < flowpipe->size(); ++current ) {
			auto [containment, intersected] = intersect( ( *flowpipe )[current], transition->getGuard() );
			if ( containment != CONTAINMENT::NO ) {
				enabledSegments.push_back( intersected );
				firstEnabled = SegmentInd( current );
				break;
			}
		}

		// collect enabled segments
		for ( current += 1; current < flowpipe->size(); ++current ) {
			auto [containment, intersected] = intersect( ( *flowpipe )[current], transition->getGuard() );
			if ( containment == CONTAINMENT::NO ) break;
			enabledSegments.push_back( intersected );
		}

		if ( enabledSegments.empty() ) return std::nullopt;
		return std::pair{ enabledSegments, firstEnabled };
	}
};

template <class Representation>
struct LTIWorker<Representation>::AggregatedGen {
	size_t segmentsPerBlock{};
	std::vector<Representation>* enabled{};
	std::size_t firstEnabled{};
	std::size_t current = 0;

	AggregatedGen( size_t segmentsPerBlock, std::vector<Representation>& enabled, SegmentInd firstEnabled )
		: segmentsPerBlock( segmentsPerBlock )
		, enabled( &enabled )
		, firstEnabled( firstEnabled ) {}

	AggregatedGen( size_t segmentsPerBlock, std::pair<std::vector<Representation>, SegmentInd>& p )
		: AggregatedGen( segmentsPerBlock, p.first, p.second ) {}

	std::optional<std::pair<Representation, carl::Interval<SegmentInd>>> next() {
		if ( current == enabled->size() ) return std::nullopt;
		Representation aggregated = ( *enabled )[current];
		SegmentInd indexFirst = SegmentInd( firstEnabled + current );  // flowpipe ind of first aggregated segment
		current += 1;
		for ( size_t inBlock = 1; inBlock < segmentsPerBlock && current < enabled->size(); ++inBlock, ++current ) {
			aggregated.unite( ( *enabled )[current] );
		}
		return std::pair{ aggregated, carl::Interval<SegmentInd>{ indexFirst, SegmentInd( firstEnabled + current ) } };
	}
};

template <class Representation>
struct LTIWorker<Representation>::JumpSuccessorGen {
	std::optional<std::pair<std::vector<Representation>, SegmentInd>> mEnabledRange = std::pair<std::vector<Representation>, SegmentInd>{};

	size_t mSegmentsPerBlock{};
	Transition<Number> const* mTransition;

	EnabledSegmentsGen mEnabled;
	AggregatedGen mAggregated;

  public:
	JumpSuccessorGen( std::vector<Representation> const& flowpipe, Transition<Number> const* transition, size_t segmentsPerBlock )
		: mSegmentsPerBlock( segmentsPerBlock )
		, mTransition( transition )
		, mEnabled( &flowpipe, transition )
		, mAggregated( segmentsPerBlock, *mEnabledRange ) {}

	std::optional<std::pair<Representation, carl::Interval<SegmentInd>>> next() {
		while ( true ) {
			auto agg = mAggregated.next();

			while ( !agg ) {
				mEnabledRange = mEnabled.next();
				if ( !mEnabledRange ) return std::nullopt;
				mAggregated = AggregatedGen{ mSegmentsPerBlock, *mEnabledRange };
				agg = mAggregated.next();
			}

			agg->first = applyReset( agg->first, mTransition->getReset() );
			CONTAINMENT containment;
			std::tie( containment, agg->first ) = intersect( agg->first, mTransition->getTarget()->getInvariant() );

			if ( containment != CONTAINMENT::NO ) {
				agg->first.reduceRepresentation();
				return agg;
			}
		}
	}
};

template <typename Representation>
std::string print( std::vector<EnabledSets<Representation>> const& pipes ) {
	std::stringstream str{};

	for ( auto& pipe : pipes ) {
		for ( auto& indSet : pipe.valuationSets ) {
			str << "[" << indSet.index << "] " << indSet.valuationSet.vertices() << " ";
		}
		str << "\n";
	}
	str << "\n";

	return str.str();
}

template <typename Representation>
std::string print( std::vector<Representation> const& sets ) {
	std::stringstream str{};

	for ( auto& set : sets ) {
		str << set.vertices() << " ";
	}
	str << "\n";
	return str.str();
}

template <typename Representation>
std::vector<JumpSuccessor<Representation>> LTIWorker<Representation>::computeJumpSuccessors( std::vector<Representation> const& flowpipe, Location<Number> const* loc ) const {
	TRACE( "hypro", "flowpipe: " << print( flowpipe ) );

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

	TRACE( "hypro", "enabledSegments: " << print( enabledSegments ) );

	std::vector<JumpSuccessor<Representation>> successors{};

	// aggregation
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
			TRACE( "hypro", "valSet: " << it->valuationSet.vertices() );
			it->valuationSet = applyReset( it->valuationSet, transition->getReset() );
			TRACE( "hypro", "Reset is: " << transition->getReset() );
			TRACE( "hypro", "Reset: " << it->valuationSet.vertices() );
			CONTAINMENT containment;
			std::tie( containment, it->valuationSet ) = intersect( it->valuationSet, transition->getTarget()->getInvariant() );
			TRACE( "hypro", "Intersect: " << it->valuationSet.vertices() );
			if ( containment == CONTAINMENT::NO ) {
				it = valuationSets.erase( it );
			} else {
				it->valuationSet.reduceRepresentation();
				TRACE( "hypro", "Reduce: " << it->valuationSet.vertices() );
				++it;
			}
		}
	}

	return successors;
}

}  // namespace hypro
