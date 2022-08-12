#include "EventTimingProvider.h"

namespace hypro {

template <typename Number>
EventTimingProvider<Number>::EventTimingProvider()
	: mRoot( new EventTimingNode<Number>() ) {
	TRACE( "hypro.datastructures.timing", "Root is " << mRoot );
#ifndef NDEBUG
	writeTree();
#endif
}

template <typename Number>
void EventTimingProvider<Number>::initialize( const HybridAutomaton<Number>& ha, tNumber globalTimeHorizon ) {
	if ( !mRoot->getChildren().empty() ) {
		this->clear();
	}

	for ( const auto& state : ha.getInitialStates() ) {
		EventTimingNode<Number>* child = new EventTimingNode<Number>( EventTimingContainer<Number>( globalTimeHorizon ) );
		child->addParent( mRoot );
		child->setLocation( state.first );
		child->setEntryTimestamp( carl::Interval<tNumber>( 0 ) );
		mRoot->addChild( child );
		TRACE( "hypro.datastructures.timing", "Add initial node " << child << ": " << *child );
	}

	/*
		ReachabilitySettings& settings = SettingsProvider<State>::getInstance().getReachabilitySettings();
		EventTimingContainer empty = EventTimingContainer(settings.timeBound*settings.jumpDepth);
		empty.insertBadState(std::make_pair(CONTAINMENT::BOT, carl::Interval<tNumber>(Number(0),settings.timeBound*settings.jumpDepth)));
		for(auto locationPtr : ha.getLocations()) {
			mLocationTimings[locationPtr] = empty;
			for(auto transitionPtr : ha.getTransitions()) {
				if(transitionPtr->getSource() == locationPtr) {
					mLocationTimings[locationPtr].insertTransition(transitionPtr, std::make_pair(CONTAINMENT::BOT, carl::Interval<tNumber>(Number(0),settings.timeBound*settings.jumpDepth)));
				}
			}
		}
		*/

#ifndef NDEBUG
	writeTree();
#endif
}

template <typename Number>
void EventTimingProvider<Number>::initialize( const Location<Number>* loc, tNumber globalTimeHorizon ) {
	if ( !mRoot->getChildren().empty() ) {
		this->clear();
	}

	EventTimingNode<Number>* child = new EventTimingNode<Number>( EventTimingContainer<Number>( globalTimeHorizon ) );
	child->addParent( mRoot );
	child->setLocation( loc );
	child->setEntryTimestamp( carl::Interval<tNumber>( 0 ) );
	mRoot->addChild( child );
	TRACE( "hypro.datastructures.timing", "Add initial node " << child );

#ifndef NDEBUG
	writeTree();
#endif
}

template <typename Number>
const EventTimingNode<Number>* EventTimingProvider<Number>::getTimingNode( const Path<Number, tNumber>& path, std::size_t level ) const {
	return findNode( path, level );
}

template <typename Number>
EventTimingNode<Number>* EventTimingProvider<Number>::rGetNode( const Path<Number, tNumber>& path, std::size_t level ) const {
	return findNode( path, level );
}

template <typename Number>
std::optional<EventTimingContainer<Number>> EventTimingProvider<Number>::getTimings( const Path<Number, tNumber>& path ) const {
	TRACE( "hypro.datastructures.timing", "Path: " << path );

	// abort if we do not have a tree yet
	if ( mRoot->getChildren().size() == 0 ) {
		TRACE( "hypro.datastructures.timing", "No child nodes, abort." );
		return std::nullopt;
	}

	// pointers to nodes on the path
	std::vector<std::set<EventTimingNode<Number>*>> workingSets;
	// stores candidates which match the timeStep
	std::vector<std::set<EventTimingNode<Number>*>> transitionCandidates;

	// fill working set with initial nodes
	for ( const auto nPtr : mRoot->getChildren() ) {
		workingSets.emplace_back( std::set<EventTimingNode<Number>*>{} );
		workingSets.back().emplace( nPtr );
		// prepare structure of 2nd set
		transitionCandidates.emplace_back( std::set<EventTimingNode<Number>*>{} );
	}

	// iterate over path / follow the path
	auto pathIt = path.begin();
	while ( pathIt != path.end() ) {
		assert( workingSets.size() == transitionCandidates.size() );
		TRACE( "hypro.datastructures.timing", "Follow time step, have " << workingSets.size() << " path-candidates." );
		// remove all nodes from working set whose invariant timings do not contain the time interval in the path
		assert( !pathIt->isDiscreteStep() );
		// verify against invariant timings.
		// Two-phase approach: Collect all which satisfy the invariant somehow,
		// then merge invariant intervals and check whether the invariant was satisfied the whole time.

		// use flag to exit loop early
		bool allEmpty = true;

		for ( std::size_t setIndex = 0; setIndex < workingSets.size(); ++setIndex ) {
			TRACE( "hypro.datastructures.timing", "Set " << setIndex );
			for ( auto nodeIt = workingSets[setIndex].begin(); nodeIt != workingSets[setIndex].end(); ) {
				allEmpty = false;
				// check for full containment
				if ( ( *nodeIt )->getTimings().satisfiedInvariant( pathIt->getTimestamp() ) ) {
					TRACE( "hypro.datastructures.timing", "Time step matching node " << *nodeIt );
					transitionCandidates[setIndex].insert( *nodeIt );
					nodeIt = workingSets[setIndex].erase( nodeIt );
				} else if ( ( *nodeIt )->getTimings().getInvariantTimings().intersectsEntry( pathIt->getTimestamp(), CONTAINMENT::FULL ) ||
							( *nodeIt )->getTimings().getInvariantTimings().intersectsEntry( pathIt->getTimestamp(), CONTAINMENT::PARTIAL ) ||
							( *nodeIt )->getTimings().getInvariantTimings().intersectsEntry( pathIt->getTimestamp(), CONTAINMENT::YES ) ) {
					// check for partial containment
					TRACE( "hypro.datastructures.timing", "Time step matching node (partial) " << *nodeIt );
					transitionCandidates[setIndex].insert( *nodeIt );
					nodeIt = workingSets[setIndex].erase( nodeIt );
				} else {
					assert( !( *nodeIt )->getTimings().hasInvariantEvent( pathIt->getTimestamp(), CONTAINMENT::YES ) );
					assert( !( *nodeIt )->getTimings().hasInvariantEvent( pathIt->getTimestamp(), CONTAINMENT::PARTIAL ) );
					assert( !( *nodeIt )->getTimings().hasInvariantEvent( pathIt->getTimestamp(), CONTAINMENT::FULL ) );
					// the node does not satisfy the invariant, erase
					nodeIt = workingSets[setIndex].erase( nodeIt );
				}
			}
			assert( workingSets[setIndex].empty() );
		}

		assert( workingSets.size() == transitionCandidates.size() );

		if ( allEmpty ) {
			return std::nullopt;
		}

		// merge invariant intervals to detect whether the invariant interval is fully covered
		for ( auto& subset : transitionCandidates ) {
			if ( !subset.empty() ) {
				TRACE( "hypro.datastructures.timing", "Merge invariant intervals of " << subset.size() << " candidates." );
				TRACE( "hypro.datastructures.timing", "Merge invariant of node " << ( *subset.begin() ) );
				// we want to unify the intervals - this is realized by reversing the order.
				auto currentOrder = ( *subset.begin() )->getTimings().getInvariantTimings().getTypeOrder();
				auto reversedOrder = currentOrder;
				// reverse order to obtain weakest information by using merge(..)
				std::reverse( ++reversedOrder.end(), reversedOrder.end() );

				HierarchicalIntervalVector<CONTAINMENT, tNumber> mergedHIV( ( *subset.begin() )->getTimings().getInvariantTimings() );
				mergedHIV.setTypeOrder( reversedOrder );
				// merge all invariant information
				for ( auto it = ++subset.begin(); it != subset.end(); ++it ) {
					TRACE( "hypro.datastructures.timing", "Merge invariant of node " << ( *it ) );
					auto tmp = ( *it )->getTimings().getInvariantTimings();
					tmp.setTypeOrder( reversedOrder );
					mergedHIV = merge( { mergedHIV, tmp } );
				}
				// restore order
				mergedHIV.setTypeOrder( currentOrder );

				TRACE( "hypro.datastructures.timing", "Invariant HIV after merge: " << mergedHIV );

				// if the invariant cannot be fully covered (information missing), remove subset (clear).
				if ( !positiveCover( mergedHIV, pathIt->getTimestamp() ) ) {
					subset.clear();
					TRACE( "hypro.datastructures.timing", "Clear subset, no full cover detected." );
					assert( subset.empty() );
				}
			}
		}

		assert( workingSets.size() == transitionCandidates.size() );

		// follow the discrete jump, if applicable
		++pathIt;
		if ( pathIt != path.end() ) {
			// set up new working set
			TRACE( "hypro.datastructures.timing", "Follow discrete step, have " << transitionCandidates.size() << " sets." );

			// try to follow the transition
			assert( pathIt->isDiscreteStep() );
			for ( std::size_t setIndex = 0; setIndex < transitionCandidates.size(); ++setIndex ) {
				assert( workingSets[setIndex].empty() );
				TRACE( "hypro.datastructures.timing", "Consider " << transitionCandidates[setIndex].size() << " nodes." );
				for ( const auto nPtr : transitionCandidates[setIndex] ) {
					TRACE( "hypro.datastructures.timing", "Search children of node " << nPtr );
					for ( const auto chPtr : nPtr->getChildren() ) {
						if ( chPtr->getEntryTransition() == pathIt->transition && carl::set_have_intersection( chPtr->getEntryTimestamp(), pathIt->getTimestamp() ) ) {
							workingSets[setIndex].insert( chPtr );
							TRACE( "hypro.datastructures.timing", "Disrete step matching node " << chPtr << "(now have " << workingSets[setIndex].size() << ")." );
						}
					}
				}
				// prepare for next iteration.
				transitionCandidates[setIndex].clear();
			}
			// increase pathIt to the next time step or the end of the path
			++pathIt;
		} else {
			// the last element in the path was a time step, move nodes to workingSet
			TRACE( "hypro.datastructures.timing", "Copy transitionCandidates to workingSet." );
			workingSets = transitionCandidates;
		}
	}
	assert( workingSets.size() == transitionCandidates.size() );
	assert( workingSets.size() == mRoot->getChildren().size() );

	TRACE( "hypro.datastructures.timing", "After loop, have " << workingSets.size() << " subsets." );

	// at this point workingSet should contain all nodes which can be reached following the path. Merge/intersect those and get the most precise.
	bool allEmpty = true;
	std::vector<EventTimingContainer<Number>> candidates;
	for ( const auto& set : workingSets ) {
		if ( !set.empty() ) {
			TRACE( "hypro.datastructures.timing", "Unite timings of " << set.size() << " containers." );
			allEmpty = false;
			auto nodeIt = set.begin();
			EventTimingContainer<Number> res = ( *nodeIt )->getTimings();
			++nodeIt;
			for ( ; nodeIt != set.end(); ++nodeIt ) {
				res = unite( { res, ( *nodeIt )->getTimings() } );
			}
			TRACE( "hypro.datastructures.timing", "Merge result: " << res );
			candidates.emplace_back( std::move( res ) );
		}
	}

	if ( allEmpty ) {
		TRACE( "hypro.datastructures.timing", "All sets are empty, return nullopt." );
		return std::nullopt;
	}

	TRACE( "hypro.datastructures.timing", "Intersect candidates." );
	return intersect( candidates );
}

template <typename Number>
void EventTimingProvider<Number>::updateTimings( const Path<Number, tNumber>& path, const EventTimingContainer<Number>& update ) {
	auto toUpdate = this->rGetNode( path );
	std::lock_guard<std::mutex> lock( toUpdate->rGetTimings().getMutex() );

	toUpdate->rGetTimings().merge( update );
#ifndef NDEBUG
	writeTree();
#endif
}

template <typename Number>
typename EventTimingNode<Number>::Node_t EventTimingProvider<Number>::addChildToNode( typename EventTimingNode<Number>::Node_t parent, tNumber timeHorizon ) {
	typename EventTimingNode<Number>::Node_t newChild = new EventTimingNode<Number>( EventTimingContainer<Number>{ timeHorizon } );
	TRACE( "hypro.datastructures.timing", "Add child " << newChild << " to node " << parent );

	// set up tree
	newChild->addParent( parent );
	parent->addChild( newChild );
#ifndef NDEBUG
	writeTree();
#endif
	return newChild;
}

template <typename Number>
std::string EventTimingProvider<Number>::getDotRepresentation() const {
	std::string nodes = "digraph structs \n { node [shape=record];\n";
	std::string transitions = "";
	std::string endDelimiter = "}\n";
	std::vector<unsigned> levels;

	mRoot->getDotRepresentation( 0, nodes, transitions );

	return nodes + transitions + endDelimiter;
}

template <typename Number>
EventTimingNode<Number>* EventTimingProvider<Number>::findNode( const Path<Number, tNumber>& path, std::size_t level ) const {
	TRACE( "hypro.datastructures.timing", "Get timings for path " << path << ", level " << level );

	// find the first initial node separately, since the root-node is not part of the path
	// Todo: We ignore several initial states for once.
	if ( mRoot->getChildren().size() == 0 ) {
		TRACE( "hypro.datastructures.timing", "No child nodes, abort." );
		return nullptr;
	}

	// stores the node candidates for the current step.
	std::vector<EventTimingNode<Number>*> workingSet;
	// initialize working set with nodes from the passed level
	for ( const auto nPtr : mRoot->getChildren() ) {
		if ( nPtr->getLevel() == level ) {
			TRACE( "hypro.datastructures.timing", "Initialize working set with node " << nPtr );
			workingSet.emplace_back( nPtr );
		}
	}

	auto pathIt = path.begin();
	while ( pathIt != path.end() ) {
		assert( !pathIt->isDiscreteStep() );
		// time step
		for ( auto nodeIt = workingSet.begin(); nodeIt != workingSet.end(); ) {
			if ( !positiveCover( ( *nodeIt )->getTimings().getInvariantTimings(), pathIt->timeInterval ) ) {
				nodeIt = workingSet.erase( nodeIt );
			} else {
				++nodeIt;
			}
		}

		TRACE( "hypro.datastructures.timing", "Have " << workingSet.size() << " nodes which match the invariant timings." );

		++pathIt;

		if ( pathIt != path.end() ) {
			assert( pathIt->isDiscreteStep() );
			// discrete step
			std::vector<EventTimingNode<Number>*> transitionCandidates;
			for ( auto nodeIt = workingSet.begin(); nodeIt != workingSet.end(); ++nodeIt ) {
				if ( ( *nodeIt )->getTimings().hasTransition( pathIt->transition ) && positiveCover( ( *nodeIt )->getTimings().getTransitionTimings( pathIt->transition ), pathIt->timeInterval ) ) {
					for ( const auto chPtr : ( *nodeIt )->getChildren() ) {
						if ( chPtr->getEntryTransition() == pathIt->transition && chPtr->getEntryTimestamp() == pathIt->timeInterval ) {
							transitionCandidates.emplace_back( chPtr );
						}
					}
				}
			}
			workingSet = transitionCandidates;

			TRACE( "hypro.datastructures.timing", "Have " << workingSet.size() << " nodes which match the transition timings." );
			++pathIt;
		}
	}

	TRACE( "hypro.datastructures.timing", "Have " << workingSet.size() << " potential nodes, return node " << workingSet.front() );
	assert( workingSet.size() == 1 );
	return workingSet.front();
}

template <typename Number>
void EventTimingProvider<Number>::writeTree() const {
	auto file = LockedFileWriter{ mName + ".gv" };
	file << getDotRepresentation();
}

}  // namespace hypro
