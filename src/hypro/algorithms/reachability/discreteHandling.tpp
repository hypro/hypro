
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

	for ( const auto& [transition, stateSet] : _newInitialSets ) {
		if ( transition->getAggregation() == Aggregation::none ) {
			TRACE( "hypro.reacher", "No aggregation." );
			// copy state - as there is no aggregation, the containing set and timestamp is already valid
			State s = stateSet;
			assert( !s.getTimestamp().isUnbounded() );
			s.setLocation( transition->getTarget() );

			s = applyReset( s, transition->getReset() );
			auto [invariantContainment, invariantSatisfyingSet] = s.satisfies( transition->getTarget()->getInvariant() );
			if ( invariantContainment != CONTAINMENT::NO ) {
				TRACE( "hypro.reacher", "Enqueue " << invariantSatisfyingSet << " for level " << mCurrentLevel + 1 << ", current queue size (before) is " << mWorkingQueue.size() );
				ReachTreeNode<State>* newChild = new ReachTreeNode<State>( invariantSatisfyingSet );
				newChild->setParent( currentTreeNode );
				currentTreeNode->addChild( newChild );
				mWorkingQueue.enqueue( std::make_unique<TaskType>( std::make_pair( mCurrentLevel + 1, newChild ) ) );
			}
		} else {  // aggregate all or use clustering
			// TODO: Note that all sets are collected for one transition, i.e. currently, if we intersect the guard for one transition twice with
			// some sets in between not satisfying the guard, we still collect all guard satisfying sets for that transition.
			if ( toAggregate.find( transition ) == toAggregate.end() ) {
				toAggregate[transition] = std::vector<State>();
			}
			toAggregate[transition].push_back( stateSet );
		}
	}

	// aggregation or clustering
	for ( const auto& [transition, stateSetVector] : toAggregate ) {
		INFO( "hypro.reacher", "-- Entered aggregation/clustering loop" );

		assert( !stateSetVector.empty() && "Nothing to aggregate" );
		assert( transition->getClusterBound() != 0 && "Clusterbound cannot be zero" );
		assert( ( !transition->getAggregation() || transition->getClusterBound() > 0 ) && "Clusterbound not properly set (is less or equal to zero)" );
		std::vector<std::size_t> segmentsPerCluster;
		if ( transition->getAggregation() == Aggregation::clustering ) {
			std::size_t clusterCount = min( transition->getClusterBound(), stateSetVector.size() );
			segmentsPerCluster = reachability::clusterDistribution( clusterCount, stateSetVector.size() );
		} else {
			// aggregation: one cluster with all segments
			segmentsPerCluster.emplace_back( stateSetVector.size() );
		}

		INFO( "hypro.reacher", "Aggregate/cluster " << stateSetVector.size() << " segments into " << segmentsPerCluster.size() << " cluster(s) with each " << segmentsPerCluster << " segment(s) per cluster." )
		std::size_t segmentCount = 0;
		for ( std::size_t clusterIdx = 0; clusterIdx < segmentsPerCluster.size(); ++clusterIdx ) {
			assert( segmentCount != stateSetVector.size() );

			TRACE( "hypro.reacher", "SegmentCount before loop: " << segmentCount );

			carl::Interval<tNumber> aggregatedTimestamp = stateSetVector[segmentCount].getTimestamp();
			State collectedSets = stateSetVector[segmentCount];
			++segmentCount;
#ifdef HYPRO_LOGGING
			std::size_t currentClusterCount = 1;
#endif
			for ( std::size_t segmentIdx = 1; segmentIdx < segmentsPerCluster[clusterIdx]; ++segmentIdx, ++segmentCount ) {
				assert( segmentCount != stateSetVector.size() );
				assert( !stateSetVector[segmentCount].getTimestamp().isUnbounded() );
				aggregatedTimestamp = aggregatedTimestamp.convexHull( stateSetVector[segmentCount].getTimestamp() );
				collectedSets = collectedSets.unite( stateSetVector[segmentCount] );
#ifdef HYPRO_LOGGING
				++currentClusterCount;
				TRACE( "hypro.reacher", "SegmentCount: " << segmentCount << ", CCC: " << currentClusterCount );
#endif
			}  // end loop over segments for a single cluster

#ifdef HYPRO_LOGGING
			auto convertedInterval = convert<tNumber, double>( aggregatedTimestamp );
			INFO( "hypro.reacher", "Unified " << currentClusterCount << " sets for aggregation. Aggregated timestamp: " << convertedInterval );
#endif

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
			State tmp = applyReset( collectedSets, transition->getReset() );

			auto [invariantContainment, invariantSatisfyingSet] = tmp.satisfies( transition->getTarget()->getInvariant() );
			INFO( "hypro.reacher", "does resetted satisfy invariant? " << invariantContainment );

			if ( invariantContainment != CONTAINMENT::NO ) {
				invariantSatisfyingSet.setLocation( transition->getTarget() );
				// set entry timestamp.
				invariantSatisfyingSet.setTimestamp( aggregatedTimestamp );

				TRACE( "hypro.reacher", "Enqueue state for level " << mCurrentLevel + 1 << ", current queue size (before) is " << mWorkingQueue.size() );
				// add new node to reach tree.
				auto* newChild = new ReachTreeNode<State>( invariantSatisfyingSet );
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
