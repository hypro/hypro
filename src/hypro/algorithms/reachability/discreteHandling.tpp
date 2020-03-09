
namespace hypro {
namespace reachability {
template <typename Number, typename ReacherSettings, typename State>
bool Reach<Number, ReacherSettings, State>::intersectGuard( Transition<Number>* _trans, const State& _state,
															State& result ) const {
	assert( !_state.getTimestamp().isUnbounded() );
	result = _state;

	// check for continuous set guard intersection
	std::pair<CONTAINMENT, State> guardSatisfyingSet = _state.satisfies( _trans->getGuard() );

	INFO( "hypro.reacher", "------ guard satisfied? " << guardSatisfyingSet.first );

	// check if the intersection is empty
	if ( guardSatisfyingSet.first != CONTAINMENT::NO ) {
#ifdef REACH_DEBUG
		INFO( "hypro.reacher", "Transition enabled at timestamp " << _state.getTimestamp() << "!" );
#endif

		result.setSets( guardSatisfyingSet.second.getSets() );
		return true;
	} else {
#ifdef REACH_DEBUG
		INFO( "hypro.reacher", "Continuous guard invalidated." );
#endif
		return false;
	}
}

template <typename Number, typename ReacherSettings, typename State>
void Reach<Number, ReacherSettings, State>::processDiscreteBehaviour( const std::vector<std::tuple<Transition<Number>*, State>>& _newInitialSets, NodePtr currentTreeNode ) {
	std::map<Transition<Number>*, std::vector<State>> toAggregate;

	for ( const auto& tuple : _newInitialSets ) {
		if ( std::get<0>( tuple )->getAggregation() == Aggregation::none ) {
			TRACE( "hypro.reacher", "No aggregation." );
			// copy state - as there is no aggregation, the containing set and timestamp is already valid
			State s = std::get<1>( tuple );
			assert( !s.getTimestamp().isUnbounded() );
			s.setLocation( std::get<0>( tuple )->getTarget() );

			s = applyReset( s, std::get<0>( tuple )->getReset() );
			std::pair<CONTAINMENT, State> invariantPair = s.satisfies( std::get<0>( tuple )->getTarget()->getInvariant() );
			if ( invariantPair.first != CONTAINMENT::NO ) {
				TRACE( "hypro.reacher", "Enqueue " << invariantPair.second << " for level " << mCurrentLevel + 1 << ", current queue size (before) is " << mWorkingQueue.size() );
				ReachTreeNode<State>* newChild = new ReachTreeNode<State>( invariantPair.second );
				newChild->setParent( currentTreeNode );
				currentTreeNode->addChild( newChild );
				mWorkingQueue.enqueue( std::make_unique<TaskType>( std::make_pair( mCurrentLevel + 1, newChild ) ) );
			}
		} else {  // aggregate all or use clustering
			// TODO: Note that all sets are collected for one transition, i.e. currently, if we intersect the guard for one transition twice with
			// some sets in between not satisfying the guard, we still collect all guard satisfying sets for that transition.
			if ( toAggregate.find( std::get<0>( tuple ) ) == toAggregate.end() ) {
				toAggregate[std::get<0>( tuple )] = std::vector<State>();
			}
			toAggregate[std::get<0>( tuple )].push_back( std::get<1>( tuple ) );
		}
	}

	// aggregation or clustering
	for ( const auto& aggregationPair : toAggregate ) {
		INFO( "hypro.reacher", "-- Entered aggregation/clustering loop" );

		assert( !aggregationPair.second.empty() );
		assert( aggregationPair.first->getClusterBound() != 0 );
		std::size_t clusterCount = min( aggregationPair.first->getClusterBound(), aggregationPair.second.size() );
		std::size_t segmentsPerCluster = aggregationPair.first->getAggregation() == Aggregation::clustering ? ceil( double( aggregationPair.second.size() ) / double( clusterCount ) ) : aggregationPair.second.size();
		INFO( "hypro.reacher", "Aggregate/cluster " << aggregationPair.second.size() << " segments into " << clusterCount << " cluster(s) with each " << segmentsPerCluster << " segment(s) per cluster." )
		std::size_t segmentCount = 0;
		for ( std::size_t clusterIdx = 0; clusterIdx < clusterCount; ++clusterIdx ) {
			assert( segmentCount != aggregationPair.second.size() );

			TRACE( "hypro.reacher", "SegmentCount before loop: " << segmentCount );

			carl::Interval<tNumber> aggregatedTimestamp = aggregationPair.second[segmentCount].getTimestamp();
			State collectedSets = aggregationPair.second[segmentCount];
			++segmentCount;
#ifdef HYPRO_LOGGING
			std::size_t currentClusterCount = 1;
#endif
			for ( std::size_t segmentIdx = 1; segmentIdx < segmentsPerCluster; ++segmentIdx ) {
				if ( segmentCount == aggregationPair.second.size() ) {
					break;
				}
				assert( !aggregationPair.second[segmentCount].getTimestamp().isUnbounded() );
				aggregatedTimestamp = aggregatedTimestamp.convexHull( aggregationPair.second[segmentCount].getTimestamp() );
				collectedSets = collectedSets.unite( aggregationPair.second[segmentCount] );
				++segmentCount;
#ifdef HYPRO_LOGGING
				++currentClusterCount;
				TRACE( "hypro.reacher", "SegmentCount: " << segmentCount << ", CCC: " << currentClusterCount );
#endif

			}  // end loop over segments for a single cluster

#ifdef HYPRO_LOGGING
			auto convertedInterval = convert<tNumber, double>( aggregatedTimestamp );
			INFO( "hypro.reacher", "Unified " << currentClusterCount << " sets for aggregation. Aggregated timestamp: " << convertedInterval );
#endif

			State s;
			s.setLocation( aggregationPair.first->getTarget() );

			// reduce new initial sets.
			//collectedSets.removeRedundancy();
#ifdef USE_SMART_AGGREGATION
			collectedSets.removeRedundancy();
			if ( collectedSets.getSetType( 0 ) == representation_name::support_function ) {
				// Forced reduction to a box template.
				collectedSets.reduceRepresentation();
			}
#endif

			// Perform resets.
			INFO( "hypro.reacher", "Apply reset." );
			State tmp = applyReset( collectedSets, aggregationPair.first->getReset() );

			std::pair<CONTAINMENT, State> invariantSatisfyingSet = tmp.satisfies( aggregationPair.first->getTarget()->getInvariant() );
			INFO( "hypro.reacher", "does resetted satisfy invariant? " << invariantSatisfyingSet.first );

			if ( invariantSatisfyingSet.first != CONTAINMENT::NO ) {
				s.setSetsSave( invariantSatisfyingSet.second.getSets() );
				// set entry timestamp.
				s.setTimestamp( aggregatedTimestamp );

				TRACE( "hypro.reacher", "Enqueue state for level " << mCurrentLevel + 1 << ", current queue size (before) is " << mWorkingQueue.size() );
				// add new node to reach tree.
				ReachTreeNode<State>* newChild = new ReachTreeNode<State>( s );
				newChild->setParent( currentTreeNode );
				currentTreeNode->addChild( newChild );
				mWorkingQueue.enqueue( std::make_unique<TaskType>( std::make_pair( mCurrentLevel + 1, newChild ) ) );
			} else {
				continue;
			}
		}  // end loop over clusters
	}

	INFO( "hypro.reacher", "--- After aggregation loop" );
}

template <typename Number, typename ReacherSettings, typename State>
bool Reach<Number, ReacherSettings, State>::checkTransitions( const State& state, const carl::Interval<tNumber>&, std::vector<std::tuple<Transition<Number>*, State>>& nextInitialSets ) const {
	State guardSatisfyingState;
	bool transitionEnabled = false;
	//std::cout << "------ how many transitions do we have? " << state.getLocation()->getTransitions().size() << std::endl;
	for ( auto& transition : state.getLocation()->getTransitions() ) {
		// handle time-triggered transitions
		if ( intersectGuard( transition.get(), state, guardSatisfyingState ) ) {
			INFO( "hypro.reacher", "hybrid transition enabled" );
			assert( guardSatisfyingState.getTimestamp() == state.getTimestamp() );
			// when a guard is satisfied here, as we do not have dynamic behaviour, avoid calculation of flowpipe
			assert( !guardSatisfyingState.getTimestamp().isUnbounded() );
#ifdef USE_FORCE_REDUCTION
			applyReduction( guardSatisfyingState );
#endif
			nextInitialSets.emplace_back( transition.get(), guardSatisfyingState );
			transitionEnabled = true;
		}
	}

	return transitionEnabled;
}

}  // namespace reachability
}  // namespace hypro
