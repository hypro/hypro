/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "LTIWorker.h"

namespace hypro {

template <typename Representation, typename HybridAutomaton>
template <typename OutputIt>
REACHABILITY_RESULT LTIWorker<Representation, HybridAutomaton>::computeTimeSuccessors( const Representation& initialSet, LocationT const* loc, OutputIt out, long int segmentsToCompute, bool checkSafety ) const {
	if ( segmentsToCompute < 0 ) {
		segmentsToCompute = mNumSegments;
	} else if ( segmentsToCompute == 0 ) {
		DEBUG( "hypro.reachability", "No segments to compute (reached global time horizon, segmentsToCompute == 0), return." );
		return REACHABILITY_RESULT::SAFE;
	}
	Representation firstSegment = constructFirstSegment( initialSet, loc->getLinearFlow( mSubspace ), mTrafoCache.transformationMatrix( loc, mSettings.timeStep, mSubspace ), mSettings.timeStep );

	auto [containment, segment] = intersect( firstSegment, loc->getInvariant(), mSubspace );
	// If the first segment did not fulfill the invariant of the location, the jump here should not have been made
	if ( containment == CONTAINMENT::NO ) {
		DEBUG( "hypro.reachability", "First segment is not contained in the invariant, abort time successor computation." );
		return REACHABILITY_RESULT::SAFE;
	}

	// insert segment
	*out = segment;
	++out;

	// intersect with badstates
	if ( checkSafety ) {
		std::tie( containment, std::ignore ) = ltiIntersectBadStates( segment, loc, mHybridAutomaton, mSubspace );
		if ( containment != CONTAINMENT::NO ) {
			// Todo: memorize the intersecting state set and keep state.
			DEBUG( "hypro.reachability", "First segment intersects the set of bad states, terminate." );
			return REACHABILITY_RESULT::UNKNOWN;
		}
	}

	// while not done
	for ( size_t segmentCount = 1; segmentCount < (std::size_t)segmentsToCompute; ++segmentCount ) {
		segment = applyTimeEvolution( segment, mTrafoCache.transformationMatrix( loc, mSettings.timeStep, mSubspace ) );
#ifdef HYPRO_LOGGING
		auto tmp = segment;
#endif
		std::tie( containment, segment ) = intersect( segment, loc->getInvariant(), mSubspace );
		if ( containment == CONTAINMENT::NO ) {
#ifdef HYPRO_LOGGING
			DEBUG( "hypro.reachability", "Segment no " << segmentCount << ", which is " << tmp << " invalidates the invariant condition." );
			DEBUG( "hypro.reachability", "Compute time successor states done." );
#endif
			return REACHABILITY_RESULT::SAFE;
		}

		*out = segment;
		++out;

		// intersect with badstates
		if ( checkSafety ) {
			std::tie( containment, std::ignore ) = ltiIntersectBadStates( segment, loc, mHybridAutomaton, mSubspace );
			if ( containment != CONTAINMENT::NO ) {
				// Todo: memorize the intersecting state set and keep state.
				DEBUG( "hypro.reachability", "Segment " << segment << " intersects the set of bad states, terminate." );
				DEBUG( "hypro.reachability", "Compute time successor states done." );
				return REACHABILITY_RESULT::UNKNOWN;
			}
		}
	}
	DEBUG( "hypro.reachability", "Compute time successor states done." );
	return REACHABILITY_RESULT::SAFE;
}

template <typename Representation, typename HybridAutomaton>
auto LTIWorker<Representation, HybridAutomaton>::getJumpSuccessors( std::vector<Representation> const& flowpipe, Transition<LocationT> const* transition ) const -> JumpSuccessorGen {
	std::size_t blockSize = 1;
	if ( mSettings.aggregation == AGG_SETTING::AGG || ( mSettings.aggregation == AGG_SETTING::MODEL && transition->getAggregation() == AGG_SETTING::AGG ) ) {
		if ( mSettings.clustering > 0 ) {
			blockSize = ( flowpipe.size() + mSettings.clustering ) / mSettings.clustering;	// division rounding up
		} else {
			blockSize = flowpipe.size();
		}

	} else if ( mSettings.aggregation == AGG_SETTING::MODEL && transition->getAggregation() != AGG_SETTING::NO_AGG ) {
		if ( transition->getAggregation() == AGG_SETTING::CLUSTERING ) {
			blockSize = ( blockSize + transition->getClusterBound() ) / transition->getClusterBound();	// division rounding up
		}
	}
	return JumpSuccessorGen{ flowpipe, transition, blockSize };
}

template <typename Representation, typename HybridAutomaton>
struct LTIWorker<Representation, HybridAutomaton>::EnabledSegmentsGen {
	std::vector<Representation> const* flowpipe;
	Transition<LocationT> const* transition;
	std::size_t current = 0;

	EnabledSegmentsGen( std::vector<Representation> const* flowpipe, Transition<LocationT> const* transition )
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

template <typename Representation, typename HybridAutomaton>
struct LTIWorker<Representation, HybridAutomaton>::AggregatedGen {
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

template <typename Representation, typename HybridAutomaton>
struct LTIWorker<Representation, HybridAutomaton>::JumpSuccessorGen {
	std::optional<std::pair<std::vector<Representation>, SegmentInd>> mEnabledRange = std::pair<std::vector<Representation>, SegmentInd>{};

	size_t mSegmentsPerBlock{};
	Transition<LocationT> const* mTransition;

	EnabledSegmentsGen mEnabled;
	AggregatedGen mAggregated;

  public:
	JumpSuccessorGen( std::vector<Representation> const& flowpipe, Transition<LocationT> const* transition, size_t segmentsPerBlock )
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

template <typename Representation, typename Location>
std::string print( std::vector<EnabledSets<Representation, Location>> const& pipes ) {
	std::stringstream str{};

	for ( auto& pipe : pipes ) {
		for ( auto& indSet : pipe.valuationSets ) {
			str << "[" << indSet.index << "] " << indSet.valuationSet << " ";
		}
		str << "\n";
	}
	str << "\n";

	return str.str();
}

template <typename Representation, typename Location>
std::string print( std::vector<JumpSuccessor<Representation, Location>> const& pipes ) {
	std::stringstream str{};

	for ( auto& pipe : pipes ) {
		if ( !pipe.valuationSets.empty() ) {
			for ( auto& indSet : pipe.valuationSets ) {
				str << "[" << indSet.time << "] " << indSet.valuationSet << " ";
			}
			str << "\n";
		}
	}
	str << "\n";

	return str.str();
}

template <typename Representation, typename HybridAutomaton>
std::string print( std::vector<Representation> const& sets ) {
	std::stringstream str{};
	for ( auto& set : sets ) {
		if ( !set.empty() ) {
			str << set << "; ";
		}
	}
	auto resultString = str.str();
	str.str( "" );
	return resultString;
}

template <typename Representation, typename HybridAutomaton>
std::vector<JumpSuccessor<Representation, typename HybridAutomaton::LocationType>> LTIWorker<Representation, HybridAutomaton>::computeJumpSuccessors( std::vector<Representation> const& flowpipe, LocationT const* loc ) const {
	// TRACE( "hypro.reachability", "flowpipe: " << print( flowpipe ) );

	// transition x enabled segments, segment ind
	std::vector<EnabledSets<Representation, typename HybridAutomaton::LocationType>> enabledSegments{};

	TRACE( "hypro.reachability", "Find non-empty guard intersections" );
	for ( const auto& transition : loc->getTransitions() ) {
		TRACE( "hypro.reachability", "Consider transition " << ( *transition.get() ) );
		auto& currentSucc = enabledSegments.emplace_back( EnabledSets<Representation, typename HybridAutomaton::LocationType>{ transition.get() } );

		SegmentInd cnt = 0;
		for ( auto const& valuationSet : flowpipe ) {
			auto [containment, intersected] = intersect( valuationSet, transition->getGuard() );

			if ( containment != CONTAINMENT::NO ) {
				currentSucc.valuationSets.push_back( { intersected, cnt } );
			}
			++cnt;
		}
	}

	TRACE( "hypro.reachability", "Guard-enabling segments: " << print( enabledSegments ) );

	std::vector<JumpSuccessor<Representation, typename HybridAutomaton::LocationType>> successors{};

	// aggregation
	// for each transition
	for ( auto& [transition, valuationSets] : enabledSegments ) {
		// no aggregation
		std::size_t blockSize = 1;
		if ( mSettings.aggregation == AGG_SETTING::AGG || ( mSettings.aggregation == AGG_SETTING::MODEL && transition->getAggregation() == AGG_SETTING::AGG ) ) {
			if ( mSettings.clustering > 0 ) {
				blockSize = ( valuationSets.size() + mSettings.clustering ) / mSettings.clustering;	 // division rounding up
			} else {
				blockSize = valuationSets.size();
			}

		} else if ( mSettings.aggregation == AGG_SETTING::MODEL && transition->getAggregation() != AGG_SETTING::NO_AGG ) {
			if ( transition->getAggregation() == AGG_SETTING::CLUSTERING ) {
				blockSize = ( blockSize + transition->getClusterBound() ) / transition->getClusterBound();	// division rounding up
			}
		}
		successors.emplace_back( JumpSuccessor<Representation, typename HybridAutomaton::LocationType>{ transition, aggregate( blockSize, valuationSets ) } );
		// TRACE( "hypro.reachability", transition->getSource()->getName() << " -> " << transition->getTarget()->getName() << ", " << transition->getReset() << ":\nenabledSegments after aggregation: " << print( successors ) << "\n" );
	}
	// DEBUG( "hypro.reachability", "All enabledSegments after aggregation: " << print( successors ) );

	// applyReset
	for ( auto& [transition, valuationSets] : successors ) {
		for ( auto it = valuationSets.begin(); it != valuationSets.end(); ) {
			it->valuationSet = applyReset( it->valuationSet, transition->getReset() );
			TRACE( "hypro.reachability", "Set after reset " << it->valuationSet );
			TRACE( "hypro.reachability", transition->getSource()->getName() << " -> " << transition->getTarget()->getName() << ": Reset is: " << transition->getReset() );
			CONTAINMENT containment;
			std::tie( containment, it->valuationSet ) = intersect( it->valuationSet, transition->getTarget()->getInvariant() );
			TRACE( "hypro.reachability", "Set after reset and intersection with invariant " << it->valuationSet );
			if ( containment == CONTAINMENT::NO ) {
				it = valuationSets.erase( it );
			} else {
				it->valuationSet.reduceRepresentation();
				++it;
			}
		}
	}

	return successors;
}

template <typename Representation, typename HybridAutomaton>
std::vector<TimedValuationSet<Representation>> LTIWorker<Representation, HybridAutomaton>::computeJumpSuccessorsForGuardEnabled( std::vector<IndexedValuationSet<Representation>>& predecessors, Transition<LocationT> const* transition ) const {
	std::size_t blockSize = 1;
	if ( mSettings.aggregation == AGG_SETTING::AGG || ( mSettings.aggregation == AGG_SETTING::MODEL && transition->getAggregation() == AGG_SETTING::AGG ) ) {
		if ( mSettings.clustering > 0 ) {
			blockSize = ( predecessors.size() + mSettings.clustering ) / mSettings.clustering;	// division rounding up
		} else {
			blockSize = predecessors.size();
		}

	} else if ( mSettings.aggregation == AGG_SETTING::MODEL && transition->getAggregation() != AGG_SETTING::NO_AGG ) {
		if ( transition->getAggregation() == AGG_SETTING::CLUSTERING ) {
			blockSize = ( blockSize + transition->getClusterBound() ) / transition->getClusterBound();	// division rounding up
		}
	}
	auto valuationSets = aggregate<Representation>( blockSize, predecessors );

	// applyReset
	// for ( auto& valuationSets : successors ) {
	for ( auto it = valuationSets.begin(); it != valuationSets.end(); ) {
		it->valuationSet = applyReset( it->valuationSet, transition->getReset(), mSubspace );
		CONTAINMENT containment;
		std::tie( containment, it->valuationSet ) = intersect( it->valuationSet, transition->getTarget()->getInvariant(), mSubspace );
		if ( containment == CONTAINMENT::NO ) {
			it = valuationSets.erase( it );
		} else {
			it->valuationSet.reduceRepresentation();
			++it;
		}
	}
	//}

	return valuationSets;
}

}  // namespace hypro
