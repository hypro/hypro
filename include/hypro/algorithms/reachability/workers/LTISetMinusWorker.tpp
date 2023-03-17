/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "LTISetMinusWorker.h"

namespace hypro {

template <typename Representation, typename Automaton>
template <typename OutputIt>
REACHABILITY_RESULT LTISetMinusWorker<Representation, Automaton>::computeTimeSuccessors( const Representation& initialSet, LocationT const* loc, OutputIt out ) const {
	// constructing the first segment
	Representation firstSegment = constructFirstSegment( initialSet, loc->getLinearFlow(), mTrafoCache.transformationMatrix( loc, mSettings.timeStep ), mSettings.timeStep );
	// vector for result of setminus
	std::vector<Representation> result;
	// vector of urgent transitions in current location
	std::vector<const Transition<LocationT>*> urgent_trans;
	// vector of flowpipe segments
	std::vector<Representation> segments;
	// variables used to keep track of the computation
	std::vector<Representation> tmpsegments;
	int lower = 0;
	int tmplower = 0;
	int urgentlower = 0;
	int tmpurgentlower = 0;
	int upper = 1;
	int tmpupper = 1;
	int urgentupper = 1;
	int tmpurgentupper = 1;
	// intersect with invariant
	auto [containment, segment] = intersect( firstSegment, loc->getInvariant() );
	// If the first segment did not fulfill the invariant of the location, the jump here should not have been made
	assert( containment != CONTAINMENT::NO );
	segments.push_back( segment );
	// getting all urgent actions
	for ( const auto& transition : loc->getTransitions() ) {
		if ( transition.get()->isUrgent() ) {
			urgent_trans.push_back( transition.get() );
		}
	}
	// check if urgent jump is enabled
	for ( unsigned long int i = 0; i < urgent_trans.size(); i++ ) {
		for ( int ut = tmplower; ut < tmpupper; ut++ ) {
			segment = segments[ut];
			// check if transition is enabled
			auto [containment, testsegment] = intersect( segment, urgent_trans.at( i )->getGuard() );
			// if guard is satisfied, perform setminus
			if ( !testsegment.empty() ) {
				Representation guard( urgent_trans.at( i )->getGuard().getMatrix(), urgent_trans.at( i )->getGuard().getVector() );
				result = segment.setMinus2( guard );
			}
			// insert segments into flowpipe
			if ( result.size() > 0 ) {
				for ( unsigned long int i = 0; i < result.size(); i++ ) {
					if ( !( result.at( i ).empty() ) ) {
						if ( i == 0 && urgentlower == tmplower ) {
							urgentlower = tmpupper;
						}
						urgentupper++;
						segments.push_back( result.at( i ) );
					}
				}
			} else {
				if ( !segment.empty() ) {
					if ( urgentlower == tmplower ) {
						urgentlower = tmpupper;
					}
					segments.push_back( segment );
					urgentupper++;
				}
			}
		}
		tmplower = urgentlower;
		tmpupper = urgentupper;
	}
	lower = tmplower;
	upper = tmpupper;
	for ( int i = tmplower; i < tmpupper; i++ ) {
		// add to flowpipe of node
		*out = segments[i];
		++out;
		// intersect with badstates
		std::tie( containment, std::ignore ) = ltiIntersectBadStates( segments[i], loc, mHybridAutomaton );
		if ( containment != CONTAINMENT::NO ) {
			// Todo: memorize the intersecting state set and keep state.
			return REACHABILITY_RESULT::UNKNOWN;
		}
	}
	urgentlower = 0;
	urgentupper = 1;
	tmpurgentlower = urgentlower;
	tmpurgentupper = urgentupper;
	// while timebound not reached
	for ( size_t segmentCount = 1; segmentCount < mNumSegments; ++segmentCount ) {
		// for all segments of previous timeevolutionstep
		for ( unsigned long int anz = lower; anz < upper; anz++ ) {
			// let time elapse
			segment = applyTimeEvolution( segments[anz], mTrafoCache.transformationMatrix( loc, mSettings.timeStep ) );
			result.resize( 0 );
			// check invariant
			std::tie( containment, segment ) = intersect( segment, loc->getInvariant() );
			if ( containment == CONTAINMENT::NO ) {
				return REACHABILITY_RESULT::SAFE;
			}
			tmpsegments.resize( 0 );
			tmpsegments.push_back( segment );
			urgentlower = 0;
			urgentupper = 1;
			tmpurgentlower = urgentlower;
			tmpurgentupper = urgentupper;
			// check if urgent jump is enabled
			// for all urgent transitions
			for ( unsigned long int i = 0; i < urgent_trans.size(); i++ ) {
				// for all parts of the current segment
				for ( int ut = urgentlower; ut < urgentupper; ut++ ) {
					segment = tmpsegments[ut];
					auto [containment, testsegment] = intersect( segment, urgent_trans.at( i )->getGuard() );
					// if guard is enabled perform setminus
					if ( containment != CONTAINMENT::NO ) {
						Representation guard( urgent_trans.at( i )->getGuard().getMatrix(), urgent_trans.at( i )->getGuard().getVector() );
						result = segment.setMinus2( guard );
						// insert segment
						if ( result.size() > 0 ) {
							for ( unsigned long int i = 0; i < result.size(); i++ ) {
								if ( tmpurgentlower == urgentlower ) {
									tmpurgentlower = urgentupper;
								}
								tmpurgentupper++;
								tmpsegments.push_back( result.at( i ) );
							}
						} else {
							if ( tmpurgentlower == urgentlower ) {
								tmpurgentlower = urgentupper;
							}
							tmpurgentupper++;
							tmpsegments.push_back( segment );
						}
					}
				}
				urgentlower = tmpurgentlower;
				urgentupper = tmpurgentupper;
			}
			// insert segments to flowpipe of node, if its not empty
			for ( int i = urgentlower; i < urgentupper; i++ ) {
				auto seg = tmpsegments[i];
				if ( !seg.empty() ) {
					segments.push_back( seg );
					*out = seg;
					++out;
					if ( tmplower == lower ) {
						tmplower = upper;
					}
					tmpupper++;
					// intersect with badstates
					std::tie( containment, std::ignore ) = ltiIntersectBadStates( seg, loc, mHybridAutomaton );
					if ( containment != CONTAINMENT::NO ) {
						// Todo: memorize the intersecting state set and keep state.
						return REACHABILITY_RESULT::UNKNOWN;
					}
				}
			}
		}
		lower = tmplower;
		upper = tmpupper;
	}
	return REACHABILITY_RESULT::SAFE;
}

template <typename Representation, typename Automaton>
auto LTISetMinusWorker<Representation, Automaton>::getJumpSuccessors( std::vector<Representation> const& flowpipe, Transition<LocationT> const* transition ) const -> JumpSuccessorGen {
	std::size_t blockSize = 1;
	if ( mSettings.aggregation == AGG_SETTING::AGG ) {
		if ( mSettings.clustering > 0 ) {
			blockSize = ( flowpipe.size() + mSettings.clustering ) / mSettings.clustering;	// division rounding up
		} else {
			blockSize = flowpipe.size();
		}

	} else if ( mSettings.aggregation == AGG_SETTING::MODEL && transition->getAggregation() != Aggregation::none ) {
		if ( transition->getAggregation() == Aggregation::clustering ) {
			blockSize = ( blockSize + transition->getClusterBound() ) / transition->getClusterBound();	// division rounding up
		}
	}
	return JumpSuccessorGen{ flowpipe, transition, blockSize };
}

template <typename Representation, typename Automaton>
struct LTISetMinusWorker<Representation, Automaton>::EnabledSegmentsGen {
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

template <typename Representation, typename Automaton>
struct LTISetMinusWorker<Representation, Automaton>::AggregatedGen {
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

template <typename Representation, typename Automaton>
struct LTISetMinusWorker<Representation, Automaton>::JumpSuccessorGen {
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

/*template <typename Representation>
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
}*/

template <typename Representation, typename Automaton>
std::vector<JumpSuccessor<Representation, typename Automaton::LocationType>> LTISetMinusWorker<Representation, Automaton>::computeJumpSuccessors( std::vector<Representation> const& flowpipe, LocationT const* loc ) const {
	// transition x enabled segments, segment ind
	std::vector<EnabledSets<Representation, typename Automaton::LocationType>> enabledSegments{};

	for ( const auto& transition : loc->getTransitions() ) {
		auto& currentSucc = enabledSegments.emplace_back( EnabledSets<Representation, typename Automaton::LocationType>{ transition.get() } );
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
	std::vector<JumpSuccessor<Representation, typename Automaton::LocationType>> successors{};

	// aggregation
	// for each transition
	for ( auto& [transition, valuationSets] : enabledSegments ) {
		// no aggregation
		std::size_t blockSize = 1;
		// temporary not used
		// TODO: decide if it is usefull for analysis using setminus
		if ( mSettings.aggregation == AGG_SETTING::AGG ) {
			if ( mSettings.clustering > 0 ) {
				// blockSize = ( valuationSets.size() + mSettings.clustering ) / mSettings.clustering;	 //division rounding up
			} else {
				// blockSize = valuationSets.size();
			}

		} else if ( mSettings.aggregation == AGG_SETTING::MODEL && transition->getAggregation() != Aggregation::none ) {
			if ( transition->getAggregation() == Aggregation::clustering ) {
				// blockSize = ( blockSize + transition->getClusterBound() ) / transition->getClusterBound();	//division rounding up
			}
		}
		successors.emplace_back( JumpSuccessor<Representation, typename Automaton::LocationType>{ transition, aggregate( blockSize, valuationSets ) } );
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
