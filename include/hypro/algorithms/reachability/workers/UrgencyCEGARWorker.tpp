/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "UrgencyCEGARWorker.h"

namespace hypro {

template <typename Representation, typename Automaton>
REACHABILITY_RESULT UrgencyCEGARWorker<Representation, Automaton>::computeTimeSuccessors( const ReachTreeNode<Representation, LocationT>& task, std::size_t timeHorizon, bool pruneUrgentSegments ) {
	START_BENCHMARK_OPERATION( "Time successor computation" );
	assert( mFlowpipe.size() == 0 );
	reset();
	auto* loc = task.getLocation();
	Representation initialSet = task.getInitialSet();

	// initial set should not consider urgent guards, so it is treated separately
	auto [containmentInitial, constraintedInitial] = intersect( initialSet, loc->getInvariant() );
	assert( containmentInitial != CONTAINMENT::NO );
	addSegment( constraintedInitial, 0 );
	if ( ltiIntersectBadStates( constraintedInitial, loc, mHybridAutomaton ).first != CONTAINMENT::NO ) {
		STOP_BENCHMARK_OPERATION( "Time successor computation" );
		return REACHABILITY_RESULT::UNKNOWN;
	}

	// first segment
	Representation firstSegment = constructFirstSegment(
		  initialSet,
		  loc->getLinearFlow(),
		  mTrafoCache.transformationMatrix( loc, mSettings.timeStep ),
		  mSettings.timeStep );

	REACHABILITY_RESULT firstSegmentSafety = handleSegment( task, firstSegment, 0, pruneUrgentSegments );
	if ( firstSegmentSafety != REACHABILITY_RESULT::SAFE ) {
		STOP_BENCHMARK_OPERATION( "Time successor computation" );
		return REACHABILITY_RESULT::UNKNOWN;
	}

	// time elapse
	// note: if some segment is empty after handling, it will not be written in the flowpipe.
	// since time elapse only looks at segments with previous segment index, flowpipe computation will
	// stop once some segment is empty.
	std::size_t flowpipeIndex = 1;	// iterate over flowpipe to get previous segment. index 0 is initial set
	for ( std::size_t segmentIndex = 1; segmentIndex < timeHorizon && flowpipeIndex < mFlowpipe.size(); ++segmentIndex ) {
		auto previousSegment = mFlowpipe.at( flowpipeIndex );
		while ( previousSegment.index == (int)segmentIndex - 1 ) {
			auto nextSegment = applyTimeEvolution(
				  previousSegment.valuationSet, mTrafoCache.transformationMatrix( loc, mSettings.timeStep ) );
			REACHABILITY_RESULT safety = handleSegment( task, nextSegment, segmentIndex, pruneUrgentSegments );
			if ( safety != REACHABILITY_RESULT::SAFE ) {
				STOP_BENCHMARK_OPERATION( "Time successor computation" );
				return REACHABILITY_RESULT::UNKNOWN;
			}
			flowpipeIndex += 1;
			if ( flowpipeIndex >= mFlowpipe.size() ) {
				break;
			}
			previousSegment = mFlowpipe.at( flowpipeIndex );
		}
	}

	STOP_BENCHMARK_OPERATION( "Time successor computation" );
	return REACHABILITY_RESULT::SAFE;
}

template <typename Representation, typename Automaton>
REACHABILITY_RESULT UrgencyCEGARWorker<Representation, Automaton>::handleSegment(
	  const ReachTreeNode<Representation, LocationT>& task, const Representation& segment, SegmentInd timing, bool pruneUrgentSegments ) {
	const Location<Number>* loc = task.getLocation();
	ltiUrgencyHandler<Representation> urgencyHandler;

	// invariant
	auto [containment, constrainedSegment] = intersect( segment, loc->getInvariant() );
	if ( containment == CONTAINMENT::NO ) {
		return REACHABILITY_RESULT::SAFE;
	}

	if ( pruneUrgentSegments ) {
		for ( const auto& uTrans : task.getLocation()->getTransitions() ) {
			if ( uTrans->isUrgent() && task.getUrgencyRefinementLevels().at( uTrans.get() ) == UrgencyRefinementLevel::FULL ) {
				START_BENCHMARK_OPERATION( "Prune segment" );
				START_BENCHMARK_OPERATION( "Prune with guard" );
				auto [jumpPredCon, jumpPredSet] = intersect( constrainedSegment, uTrans->getGuard() );
				if ( mJumpPredecessors.find( uTrans.get() ) == mJumpPredecessors.end() ) {
					mJumpPredecessors[uTrans.get()] = std::vector<IndexedValuationSet<Representation>>();
				}
				if ( jumpPredCon == CONTAINMENT::PARTIAL ) {
					mJumpPredecessors[uTrans.get()].push_back( { jumpPredSet, timing } );
				}
				STOP_BENCHMARK_OPERATION( "Prune with guard" );
				CONTAINMENT jesCon = CONTAINMENT::NO;
				if ( jumpPredCon == CONTAINMENT::FULL ) {
					jesCon = intersect( jumpPredSet, uTrans->getJumpEnablingSet() ).first;
				}
				STOP_BENCHMARK_OPERATION( "Prune segment" );
				if ( jesCon == CONTAINMENT::FULL ) {
					COUNT( "Pruned urgent segment" );
					return REACHABILITY_RESULT::SAFE;
				} else {
					STOP_BENCHMARK_OPERATION( "Intersection non pruned" );
					COUNT( "Intersection for non pruned segment" );
				}
			}
		}
	}

	for ( const auto& transRefinement : task.getUrgencyRefinementLevels() ) {
		if ( transRefinement.second == UrgencyRefinementLevel::CUTOFF ) {
			COUNT( "Cutoff" );
			START_BENCHMARK_OPERATION( "Cutoff computation" );
			constrainedSegment = urgencyHandler.cutoff( constrainedSegment, transRefinement.first );
			STOP_BENCHMARK_OPERATION( "Cutoff computation" );
		}
	}

	// urgent guards
	std::vector<Representation> nonUrgentEnabled{ constrainedSegment };
	for ( const auto& transRefinement : task.getUrgencyRefinementLevels() ) {
		if ( transRefinement.second == UrgencyRefinementLevel::SETDIFF ) {
			COUNT( "Set difference" );
			START_BENCHMARK_OPERATION( "Set difference computation" );
			nonUrgentEnabled = urgencyHandler.urgentSetDifference( nonUrgentEnabled, transRefinement.first );
			STOP_BENCHMARK_OPERATION( "Set difference computation" );
		}
	}
	addSegment( nonUrgentEnabled, timing );

	// safety check
	if ( std::any_of( nonUrgentEnabled.begin(), nonUrgentEnabled.end(), [loc, this]( const auto& splitSegment ) {
            if ( splitSegment.empty() ) return false;
            return ltiIntersectBadStates( splitSegment, loc, mHybridAutomaton ).first != CONTAINMENT::NO; } ) ) {
		return REACHABILITY_RESULT::UNKNOWN;
	}
	return REACHABILITY_RESULT::SAFE;
}

template <typename Representation, typename Automaton>
auto UrgencyCEGARWorker<Representation, Automaton>::computeJumpSuccessors( const ReachTreeNode<Representation, LocationT>& task, const Transition<LocationT>* transition, const carl::Interval<SegmentInd>& timeOfJump )
	  -> std::vector<TimedValuationSet<Representation>> {
	START_BENCHMARK_OPERATION( "Jump successor computation" );
	assert( transition->getSource() == task.getLocation() );
	assert( task.getFlowpipe().size() == task.getFpTimings().size() );

	if ( mJumpPredecessors.find( transition ) == mJumpPredecessors.end() ) {
		mJumpPredecessors[transition] = std::vector<IndexedValuationSet<Representation>>();
		for ( std::size_t i = 0; i < task.getFlowpipe().size(); ++i ) {
			if ( isUnbounded( timeOfJump ) ||
				 ( task.getTimings().lower() + task.getFpTimings()[i] <= timeOfJump.upper() && task.getTimings().upper() + task.getFpTimings()[i] >= timeOfJump.lower() ) ) {
				auto [containment, intersected] = intersect( task.getFlowpipe()[i], transition->getGuard() );
				if ( containment != CONTAINMENT::NO ) {
					mJumpPredecessors[transition].push_back( { intersected, task.getFpTimings()[i] } );
				}
			}
		}
	} else {
		COUNT( "Precomputed jump predecessors" );
	}

	// aggregation
	std::size_t blockSize = 1;
	if ( mSettings.aggregation == AGG_SETTING::AGG ) {
		if ( mSettings.clustering > 0 ) {
			blockSize = ( mJumpPredecessors[transition].size() + mSettings.clustering ) / mSettings.clustering;	 // division rounding up
		} else {
			blockSize = mJumpPredecessors[transition].size();
		}

	} else if ( mSettings.aggregation == AGG_SETTING::MODEL && transition->getAggregation() != AGG_SETTING::NO_AGG ) {
		if ( transition->getAggregation() == AGG_SETTING::CLUSTERING ) {
			blockSize = ( blockSize + transition->getClusterBound() ) / transition->getClusterBound();	// division rounding up
		}
	}

	std::vector<TimedValuationSet<Representation>> successors = aggregate( blockSize, mJumpPredecessors[transition] );

	for ( auto it = successors.begin(); it != successors.end(); ) {
		TRACE( "hypro", "valSet: " << it->valuationSet.vertices() );
		it->valuationSet = applyReset( it->valuationSet, transition->getReset() );
		TRACE( "hypro", "Reset is: " << transition->getReset() );
		TRACE( "hypro", "Reset: " << it->valuationSet.vertices() );
		CONTAINMENT containment;
		std::tie( containment, it->valuationSet ) = intersect( it->valuationSet, transition->getTarget()->getInvariant() );
		TRACE( "hypro", "Intersect: " << it->valuationSet.vertices() );
		if ( containment == CONTAINMENT::NO ) {
			it = successors.erase( it );
		} else {
			it->valuationSet.reduceRepresentation();
			TRACE( "hypro", "Reduce: " << it->valuationSet.vertices() );
			++it;
		}
	}
	STOP_BENCHMARK_OPERATION( "Jump successor computation" );
	return successors;
}

template <typename Representation, typename Automaton>
auto UrgencyCEGARWorker<Representation, Automaton>::computeJumpSuccessors( const ReachTreeNode<Representation, LocationT>& task )
	  -> std::vector<JumpSuccessor<Representation, LocationT>> {
	auto* loc = task.getLocation();
	std::vector<JumpSuccessor<Representation, LocationT>> successors{};
	for ( const auto& transition : loc->getTransitions() ) {
		successors.push_back( { transition.get(), computeJumpSuccessors( task, transition.get() ) } );
	}
	return successors;
}

template <typename Representation, typename Automaton>
void UrgencyCEGARWorker<Representation, Automaton>::addSegment( const Representation& segment, SegmentInd timing ) {
	mFlowpipe.push_back( IndexedValuationSet<Representation>{ segment, timing } );
}

template <typename Representation, typename Automaton>
void UrgencyCEGARWorker<Representation, Automaton>::addSegment( const std::vector<Representation>& segment, SegmentInd timing ) {
	for ( auto splitSegment : segment ) {
		if ( !splitSegment.empty() ) {
			mFlowpipe.push_back( IndexedValuationSet<Representation>{ splitSegment, timing } );
		}
	}
}

template <typename Representation, typename Automaton>
void UrgencyCEGARWorker<Representation, Automaton>::insertFlowpipe( ReachTreeNode<Representation, LocationT>& node ) const {
	for ( auto [segment, index] : mFlowpipe ) {
		node.getFlowpipe().push_back( segment );
		node.getFpTimings().push_back( index );
	}
}

}  // namespace hypro
