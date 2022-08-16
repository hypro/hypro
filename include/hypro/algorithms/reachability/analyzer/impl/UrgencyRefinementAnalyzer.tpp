/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "UrgencyRefinementAnalyzer.h"

namespace hypro {
namespace detail {

template <typename Transition>
UrgencyRefinementLevel getInitialRefinementLevel( Transition* transition, const UrgencyCEGARSettings& refinementSettings ) {
	assert( transition->isUrgent() );
	// refine halfspaces to max level if demanded
	if ( refinementSettings.refineHalfspaces && getMinRefinementLevel( refinementSettings ) != getMaxRefinementLevel( refinementSettings ) &&
		 ( transition->getJumpEnablingSet().isTrue() ||
		   transition->getJumpEnablingSet().isFalse() ||
		   transition->getJumpEnablingSet().getMatrix().size() == 1 ) ) {
		return getMaxRefinementLevel( refinementSettings );
	}
	return getMinRefinementLevel( refinementSettings );
}

inline UrgencyRefinementLevel getNextRefinementLevel( const UrgencyRefinementLevel& level, const UrgencyCEGARSettings& refinementSettings ) {
	auto enabledLevels = refinementSettings.refinementLevels;
	switch ( level ) {
		case UrgencyRefinementLevel::FULL:
			if ( std::find( enabledLevels.begin(), enabledLevels.end(), UrgencyRefinementLevel::CUTOFF ) != enabledLevels.end() ) {
				return UrgencyRefinementLevel::CUTOFF;
			}
			[[fallthrough]];
		case UrgencyRefinementLevel::CUTOFF:
			if ( std::find( enabledLevels.begin(), enabledLevels.end(), UrgencyRefinementLevel::SETDIFF ) != enabledLevels.end() ) {
				return UrgencyRefinementLevel::SETDIFF;
			}
			[[fallthrough]];
		default:
			assert( false && "No next level for maximal refinement level" );
			return level;
	}
}

inline UrgencyRefinementLevel getMinRefinementLevel( const UrgencyCEGARSettings& refinementSettings ) {
	auto refinementLevels = refinementSettings.refinementLevels;
	assert( refinementLevels.size() > 0 );
	if ( std::find( refinementLevels.begin(), refinementLevels.end(), UrgencyRefinementLevel::FULL ) != refinementLevels.end() ) {
		return UrgencyRefinementLevel::FULL;
	} else if ( std::find( refinementLevels.begin(), refinementLevels.end(), UrgencyRefinementLevel::CUTOFF ) != refinementLevels.end() ) {
		return UrgencyRefinementLevel::CUTOFF;
	} else {
		return UrgencyRefinementLevel::SETDIFF;
	}
}

inline UrgencyRefinementLevel getMaxRefinementLevel( const UrgencyCEGARSettings& refinementSettings ) {
	auto refinementLevels = refinementSettings.refinementLevels;
	assert( refinementLevels.size() > 0 );
	if ( std::find( refinementLevels.begin(), refinementLevels.end(), UrgencyRefinementLevel::SETDIFF ) != refinementLevels.end() ) {
		return UrgencyRefinementLevel::SETDIFF;
	} else if ( std::find( refinementLevels.begin(), refinementLevels.end(), UrgencyRefinementLevel::CUTOFF ) != refinementLevels.end() ) {
		return UrgencyRefinementLevel::CUTOFF;
	} else {
		return UrgencyRefinementLevel::FULL;
	}
}
}  // namespace detail

template <typename Representation, typename Automaton>
struct UrgencyRefinementAnalyzer<Representation, Automaton>::ChildNodeGen {
	using LocationT = typename Automaton::LocationType;
	std::vector<TimedValuationSet<Representation>> successors;
	ReachTreeNode<Representation, LocationT>* parentNode;
	const Transition<typename Representation::NumberType, LocationT>* transition;
	int timeStepFactor;
	UrgencyCEGARSettings refinementSettings;
	std::size_t successorIndex = 0;	 // index for iterating over successor segments

	ReachTreeNode<Representation, LocationT>* next() {
		if ( successorIndex >= successors.size() ) {
			return nullptr;
		}
		auto& [valuationSet, segmentsInterval] = successors[successorIndex];
		++successorIndex;

		// convert local time to global time
		carl::Interval<TimePoint> const& initialSetDuration = parentNode->getTimings();
		// add one to upper to convert from segment indices to time points
		// multiply by timeStepFactor to convert from analyzer specific timeStep to fixedTimeStep
		carl::Interval<TimePoint> enabledDuration{ segmentsInterval.lower() * timeStepFactor, ( segmentsInterval.upper() + 1 ) * timeStepFactor };
		carl::Interval<TimePoint> globalDuration{ initialSetDuration.lower() + enabledDuration.lower(), initialSetDuration.upper() + enabledDuration.upper() };

		auto& child = parentNode->addChild( valuationSet, globalDuration, transition );
		for ( auto const& trans : child.getLocation()->getTransitions() ) {
			if ( trans->isUrgent() ) {
				child.getUrgencyRefinementLevels()[trans.get()] = detail::getInitialRefinementLevel( trans.get(), refinementSettings );
			}
		}
		return &child;
	}
};

template <typename Representation, typename Automaton>
bool UrgencyRefinementAnalyzer<Representation, Automaton>::matchesPathTiming( ReachTreeNode<Representation, LocationT>* node ) {
	auto& timing = mPath.elements.at( node->getDepth() - 1 ).first;
	return node->getTimings().upper() >= timing.lower() && node->getTimings().lower() <= timing.upper();
}

template <typename Representation, typename Automaton>
bool UrgencyRefinementAnalyzer<Representation, Automaton>::matchesPathTransition( ReachTreeNode<Representation, LocationT>* node ) {
	auto const* transition = mPath.elements.at( node->getDepth() - 1 ).second;
	return ( transition == node->getTransition() );
}

template <typename Representation, typename Automaton>
auto UrgencyRefinementAnalyzer<Representation, Automaton>::run() -> RefinementResult {
	// Setup settings for flowpipe construction in worker
	TimeTransformationCache<LocationT> transformationCache;
	UrgencyCEGARWorker<Representation, Automaton> worker{
		  *mHybridAutomaton,
		  mParameters,
		  mFixedParameters.localTimeHorizon,
		  transformationCache };
	COUNT( "Refinement iteration" );

	std::vector<ReachTreeNode<Representation, LocationT>*> endOfPath{};		// potential successor nodes
	std::vector<ReachTreeNode<Representation, LocationT>*> refinedNodes{};	// nodes that were chosen as refinement node

	START_BENCHMARK_OPERATION( "Find refinement node" );
	RefinementCandidate refine = findRefinementCandidate( mFailureNode );
	STOP_BENCHMARK_OPERATION( "Find refinement node" );
	if ( refine.node == nullptr ) {
		return { Failure{ mFailureNode } };
	}

	mWorkQueue.push_front( createRefinedNode( refine ) );

	while ( !mWorkQueue.empty() ) {
		// pop node
		auto* currentNode = mWorkQueue.front();
		mWorkQueue.pop_front();
		// std::cout << "CEGAR Node at depth " << currentNode->getDepth() << "\n";

		// skip descendants of refined nodes
		auto node = currentNode;
		bool ancestorRefined = false;
		while ( node != nullptr ) {
			if ( std::find( refinedNodes.begin(), refinedNodes.end(), node ) != refinedNodes.end() ) {
				ancestorRefined = true;
				COUNT( "Skip descendant of refined" );
				break;
			}
			node = node->getParent();
		}
		if ( ancestorRefined ) continue;

		// if node is child of last node in path, collect it in endOfPath
		if ( currentNode->getDepth() == mPath.elements.size() + 1 ) {
			endOfPath.push_back( currentNode );
			continue;
		}

		// compute flowpipe. if node was previously unsafe, flowpipe would not be empty
		worker.reset();
		if ( currentNode->getFlowpipe().empty() ) {
			COUNT( "Computed refinement flowpipes" );
			START_BENCHMARK_OPERATION( "Refinement time successors" );
			REACHABILITY_RESULT safetyResult = worker.computeTimeSuccessors( *currentNode, mRefinementSettings.pruneUrgentSegments );
			worker.insertFlowpipe( *currentNode );
			currentNode->setSafety( safetyResult );
			STOP_BENCHMARK_OPERATION( "Refinement time successors" );
		} else {
			COUNT( "Reuse flowpipe computation" );
		}

		if ( currentNode->getSafety() == REACHABILITY_RESULT::UNKNOWN ) {
			START_BENCHMARK_OPERATION( "Find refinement node" );
			refine = findRefinementCandidate( currentNode );
			STOP_BENCHMARK_OPERATION( "Find refinement node" );
			if ( refine.node == nullptr ) {
				return { Failure{ currentNode } };
			}
			COUNT( "Nested refinement" );
			mWorkQueue.push_front( createRefinedNode( refine ) );
			refinedNodes.push_back( currentNode );
			continue;
		}
		// do not perform discrete jump if jump depth was reached
		if ( currentNode->getDepth() == mFixedParameters.jumpDepth ) continue;

		// currentNode is last node in path, create and collect all children
		if ( currentNode->getDepth() == mPath.elements.size() ) {
			for ( const auto& successor : worker.computeJumpSuccessors( *currentNode ) ) {
				ChildNodeGen childGen{ successor.valuationSets, currentNode, successor.transition, mParameters.timeStepFactor, mRefinementSettings };
				while ( auto* child = childGen.next() ) {
					endOfPath.push_back( child );
				}
			}
		} else {
			// continue along path
			// check if children already exist
			if ( !currentNode->getChildren().empty() ) {
				COUNT( "Reuse children" );
				for ( auto* child : currentNode->getChildren() ) {
					// get correct child node. Match transition, jump time and initial refinement level for all transitions
					if ( matchesPathTransition( child ) &&
						 matchesPathTiming( child ) &&
						 std::all_of(
							   child->getUrgencyRefinementLevels().begin(),
							   child->getUrgencyRefinementLevels().end(),
							   [this]( const auto& u ) { return u.second == detail::getInitialRefinementLevel( u.first, mRefinementSettings ); } ) ) {
						mWorkQueue.push_front( child );
					}
				}
			} else {
				COUNT( "Compute children" );
				for ( const auto& successor : worker.computeJumpSuccessors( *currentNode ) ) {
					ChildNodeGen childGen{ successor.valuationSets, currentNode, successor.transition, mParameters.timeStepFactor, mRefinementSettings };
					while ( auto* child = childGen.next() ) {
						if ( matchesPathTransition( child ) && matchesPathTiming( child ) ) {
							mWorkQueue.push_front( child );
						}
					}
				}
			}
		}
	}

	// increase counter for most recent refined transition if refinement was successful
	if ( mRefinementSettings.heuristic == UrgencyRefinementHeuristic::SUCCESSCOUNT ) mHeuristicCache[mLastRefine] += 1;
	std::vector<ReachTreeNode<Representation, LocationT>*> pathSuccessors{};
	for ( auto succ : endOfPath ) {
		// filter out descendants of refinement nodes
		bool ancestorRefined = false;
		auto node = succ;
		while ( node != nullptr ) {
			if ( std::find( refinedNodes.begin(), refinedNodes.end(), node ) != refinedNodes.end() ) {
				ancestorRefined = true;
				COUNT( "Skip descendant of refined as path successor" );
				break;
			}
			node = node->getParent();
		}
		if ( !ancestorRefined ) {
			pathSuccessors.push_back( succ );
		}
	}

	return { UrgencyRefinementSuccess{ pathSuccessors } };
}

template <typename Representation, typename Automaton>
auto UrgencyRefinementAnalyzer<Representation, Automaton>::findRefinementCandidate( ReachTreeNode<Representation, LocationT>* unsafeNode )
	  -> RefinementCandidate {
	// get minimal refinement level of nodes on path to unsafe node
	UrgencyRefinementLevel currentLevel = detail::getMaxRefinementLevel( mRefinementSettings );
	for ( auto n = unsafeNode; n != nullptr; n = n->getParent() ) {
		for ( const auto& uTrans : n->getLocation()->getTransitions() ) {
			if ( uTrans->isUrgent() && n->getUrgencyRefinementLevels().at( uTrans.get() ) != detail::getMaxRefinementLevel( mRefinementSettings ) ) {
				auto transitionLevel = n->getUrgencyRefinementLevels().at( uTrans.get() );
				currentLevel = transitionLevel < currentLevel ? transitionLevel : currentLevel;
			}
		}
	}
	// while not all nodes are totally refined
	while ( currentLevel != detail::getMaxRefinementLevel( mRefinementSettings ) ) {
		auto nextLevel = detail::getNextRefinementLevel( currentLevel, mRefinementSettings );
		// collect transitions with current refinement level
		std::vector<RefinementCandidate> candidates;
		for ( auto n = unsafeNode; n != nullptr; n = n->getParent() ) {
			for ( const auto& uTrans : n->getLocation()->getTransitions() ) {
				if ( uTrans->isUrgent() && n->getUrgencyRefinementLevels().at( uTrans.get() ) == currentLevel ) {
					candidates.push_back( RefinementCandidate{ n, uTrans.get(), nextLevel } );
				}
			}
		}

		// go from top to bottom by default
		std::reverse( candidates.begin(), candidates.end() );

		// sort by heuristic
		START_BENCHMARK_OPERATION( "Sort by heuristic" );
		std::stable_sort( candidates.begin(), candidates.end(),
						  [this]( auto c1, auto c2 ) {
							  if ( mRefinementSettings.heuristic == UrgencyRefinementHeuristic::CONSTRAINT_COUNT ) {
								  return evaluateHeuristic( c1.transition, c1.node ) < evaluateHeuristic( c2.transition, c2.node );
							  } else {
								  return evaluateHeuristic( c1.transition, c1.node ) > evaluateHeuristic( c2.transition, c2.node );
							  }
						  } );
		STOP_BENCHMARK_OPERATION( "Sort by heuristic" );

		// check candidates and update heuristic for chosen transition
		for ( auto candidate : candidates ) {
			// if candidate was previously suitable then we don't check again
			if ( candidate.node->getUrgencyRefinementLevels().at( candidate.transition ) != detail::getMinRefinementLevel( mRefinementSettings ) ||
				 isSuitableForRefinement( candidate, unsafeNode ) ) {
				COUNT( "Refinement transition found" );
				updateHeuristics( candidate.transition );
				return candidate;
			}
			COUNT( "Transition is not suitable for refinement" );
		}

		// all suitable transitions are now refined to nextLevel
		currentLevel = nextLevel;
	}
	// no suitable candidate for refinement found
	return RefinementCandidate{};
}

template <typename Representation, typename Automaton>
ReachTreeNode<Representation, typename Automaton::LocationType>* UrgencyRefinementAnalyzer<Representation, Automaton>::createRefinedNode( const RefinementCandidate& refine ) {
	auto parent = refine.node->getParent();
	std::map<Transition<Number, LocationT>*, UrgencyRefinementLevel> urgentTransitions( refine.node->getUrgencyRefinementLevels() );
	urgentTransitions[refine.transition] = refine.level;
	// check if refined node already exists
	if ( parent == nullptr ) {
		for ( auto& sibling : *mRoots ) {
			if ( refine.node->getTimings() == sibling.getTimings() &&
				 urgentTransitions == sibling.getUrgencyRefinementLevels() &&
				 refine.node->getInitialSet() == sibling.getInitialSet() ) {
				COUNT( "Reuse refinement node" );
				return &sibling;
			}
		}
	} else {
		for ( auto sibling : parent->getChildren() ) {
			if ( refine.node->getTransition() == sibling->getTransition() &&
				 refine.node->getTimings() == sibling->getTimings() &&
				 urgentTransitions == sibling->getUrgencyRefinementLevels() &&
				 refine.node->getInitialSet() == sibling->getInitialSet() ) {
				assert( sibling->getFlowpipe().size() > 0 );
				COUNT( "Reuse refinement node" );
				return sibling;
			}
		}
	}

	// refined node does not exist, so it is created
	if ( parent == nullptr ) {
		ReachTreeNode<Representation, LocationT> refinedNode(
			  refine.node->getLocation(),
			  refine.node->getInitialSet(),
			  refine.node->getTimings() );
		refinedNode.getUrgencyRefinementLevels() = urgentTransitions;
		mRoots->push_back( std::move( refinedNode ) );
		return &( mRoots->back() );
	}
	ReachTreeNode<Representation, LocationT>& refinedNode = parent->addChild(
		  refine.node->getInitialSet(),
		  refine.node->getTimings(),
		  refine.node->getTransition() );
	refinedNode.getUrgencyRefinementLevels() = urgentTransitions;
	return &refinedNode;
}

template <typename Representation, typename Automaton>
bool UrgencyRefinementAnalyzer<Representation, Automaton>::isSuitableForRefinement(
	  const RefinementCandidate& candidate, ReachTreeNode<Representation, LocationT>* unsafeNode ) {
	START_BENCHMARK_OPERATION( "Check refinement candidate" );

	/*
		+ iterate over all segments of the candidate node
		+ if segmentTiming > timeOfFirstJump: moved beyond jump, so further segments are ignored
		+ intersect with jump enabling set of urgent jump
		+ if containment is full and segmentTiming < timeOfFirstJump: suitable, because
			the jump is not reachable at all
		+ if containment is partial, compute the path starting from the intersection
	*/

	// used for aggregation of initial set if demanded
	TimedValuationSet<Representation> aggregatedInitial{ Representation::Empty(), carl::Interval<SegmentInd>::emptyInterval() };

	// path from candidate node to unsafe node
	auto path = unsafeNode->getPath().tail( unsafeNode->getDepth() - candidate.node->getDepth() );

	const auto& candidateTimings = candidate.node->getTimings();
	const auto& candidateFpTimings = candidate.node->getFpTimings();
	auto& candidateFlowpipe = candidate.node->getFlowpipe();
	// initial time horizon and initial tree node
	std::vector<std::pair<SegmentInd, ReachTreeNode<Representation, LocationT>>> tasks;

	for ( std::size_t fpIndex = 0; fpIndex < candidateFlowpipe.size(); ++fpIndex ) {
		// moved beyond first jump:
		if ( path.elements.size() > 0 && candidateFpTimings[fpIndex] + candidateTimings.lower() > path.elements[0].first.upper() ) {
			break;
		}

		auto [containment, initial] = intersect( candidateFlowpipe[fpIndex], candidate.transition->getJumpEnablingSet() );
		if ( containment == CONTAINMENT::NO ) {
			continue;
		} else if ( containment == CONTAINMENT::FULL && path.elements.size() > 0 &&
					candidateFpTimings[fpIndex] + candidateTimings.upper() < path.elements[0].first.lower() ) {
			// segment before jump is fully contained in jump enabling set
			STOP_BENCHMARK_OPERATION( "Check refinement candidate" );
			return true;
		} else {
			if ( mRefinementSettings.aggregatedRefine ) {
				aggregatedInitial.valuationSet = aggregatedInitial.valuationSet.unite( initial );
				if ( aggregatedInitial.time.isEmpty() ) {
					aggregatedInitial.time = carl::Interval<SegmentInd>( candidateFpTimings[fpIndex] );
				} else {
					aggregatedInitial.time.setUpper( candidateFpTimings[fpIndex] );
				}
			} else {
				// get time horizon for first task
				auto timeHorizon = mMaxSegments - candidateFpTimings[fpIndex];
				// create task node, todo: urgency?
				carl::Interval<SegmentInd> segmentOffset = candidateTimings.add( carl::Interval<SegmentInd>( candidateFpTimings[fpIndex] ) );
				ReachTreeNode<Representation, LocationT> task( candidate.node->getLocation(), initial, segmentOffset );
				tasks.push_back( std::make_pair( timeHorizon, std::move( task ) ) );
			}
		}
	}

	if ( mRefinementSettings.aggregatedRefine ) {
		if ( !aggregatedInitial.valuationSet.empty() ) {
			ReachTreeNode<Representation, LocationT> node( candidate.node->getLocation(),
														   aggregatedInitial.valuationSet,
														   candidateTimings + aggregatedInitial.time );
			tasks.push_back( std::make_pair( mMaxSegments, std::move( node ) ) );
		}
	}
	for ( auto& [timeHorizon, task] : tasks ) {
		if ( isPathUnsafe( &task, path, timeHorizon ) ) {
			STOP_BENCHMARK_OPERATION( "Check refinement candidate" );
			return true;
		}
	}
	STOP_BENCHMARK_OPERATION( "Check refinement candidate" );
	return false;
}

template <typename Representation, typename Automaton>
bool UrgencyRefinementAnalyzer<Representation, Automaton>::isPathUnsafe( ReachTreeNode<Representation, LocationT>* initialNode, Path<Number, LocationT> path, std::size_t initialTimeHorizon ) {
	// todo: reuse worker or at least transformationCache
	TimeTransformationCache<LocationT> transformationCache;
	UrgencyCEGARWorker<Representation, Automaton> worker{
		  *mHybridAutomaton,
		  mParameters,
		  mFixedParameters.localTimeHorizon,
		  transformationCache };

	std::deque<ReachTreeNode<Representation, LocationT>*> queue;
	queue.push_front( initialNode );
	while ( !queue.empty() ) {
		auto node = queue.back();
		queue.pop_back();
		worker.reset();
		if ( node->getDepth() == 0 ) {
			if ( worker.computeTimeSuccessors( *node, initialTimeHorizon, false ) == REACHABILITY_RESULT::UNKNOWN ) {
				return true;
			}
		} else {
			if ( worker.computeTimeSuccessors( *node, false ) == REACHABILITY_RESULT::UNKNOWN ) {
				return true;
			}
		}
		worker.insertFlowpipe( *node );
		if ( node->getDepth() < path.elements.size() ) {
			auto nextTransition = path.elements[node->getDepth()].second;
			auto successor = worker.computeJumpSuccessors( *node, nextTransition, path.elements[node->getDepth()].first );
			ChildNodeGen childGen{ successor, node, nextTransition, mParameters.timeStepFactor, mRefinementSettings };
			while ( auto* child = childGen.next() ) {
				queue.push_front( child );
			}
		}
	}
	return false;
}

template <typename Representation, typename Automaton>
std::size_t UrgencyRefinementAnalyzer<Representation, Automaton>::evaluateHeuristic( Transition<Number, LocationT>* t, ReachTreeNode<Representation, LocationT>* node ) {
	if ( mHeuristicCache.count( t ) == 0 ) {
		switch ( mRefinementSettings.heuristic ) {
			case UrgencyRefinementHeuristic::CONSTRAINT_COUNT: {
				mHeuristicCache[t] = t->getJumpEnablingSet().getMatrix().rows();
				break;
			}
			case UrgencyRefinementHeuristic::VOLUME: {
				// get relevant dimensions
				std::vector<std::size_t> relevantDimensions;
				for ( std::size_t i = 0; i < (std::size_t)t->getJumpEnablingSet().getMatrix().rows(); ++i ) {
					for ( std::size_t d = 0; d < (std::size_t)t->getJumpEnablingSet().getMatrix().cols(); ++d ) {
						if ( t->getJumpEnablingSet().getMatrix()( i, d ) != 0 ) {
							relevantDimensions.push_back( d );
						}
					}
				}
				std::size_t vol = 0;
				for ( auto segment : node->getFlowpipe() ) {
					auto [containment, intersected] = intersect( segment, t->getJumpEnablingSet() );
					if ( containment == CONTAINMENT::NO ) continue;
					auto box = computeBoundingBox( intersected );
					std::size_t boxVol = 1;
					for ( auto dimIndex : relevantDimensions ) {
						boxVol *= size_t( std::ceil( carl::convert<Number, double>( box.intervals()[dimIndex].upper() - box.intervals()[dimIndex].lower() ) ) );
					}
					vol += boxVol;
				}
				mHeuristicCache[t] = vol;
				break;
			}
			case UrgencyRefinementHeuristic::SUCCESSCOUNT:
				[[fallthrough]];
			case UrgencyRefinementHeuristic::COUNT: {
				mHeuristicCache[t] = 0;
				break;
			}
			default:
				// no heuristic matched, return default value
				return 0;
		}
	}
	return mHeuristicCache[t];
}

template <typename Representation, typename Automaton>
void UrgencyRefinementAnalyzer<Representation, Automaton>::updateHeuristics( Transition<Number, LocationT>* t ) {
	if ( mRefinementSettings.heuristic == UrgencyRefinementHeuristic::COUNT ) {
		mHeuristicCache[t] += 1;
	} else if ( mRefinementSettings.heuristic == UrgencyRefinementHeuristic::VOLUME ) {
		mHeuristicCache.clear();
	} else if ( mRefinementSettings.heuristic == UrgencyRefinementHeuristic::SUCCESSCOUNT ) {
		mLastRefine = t;
	}
}

}  // namespace hypro