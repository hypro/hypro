#include "ltiJumpHandler.h"

namespace hypro {

template <typename State>
auto ltiJumpHandler<State>::applyJump( const TransitionStateMap& states, Transition<Number>* transition, const AnalysisParameters& strategy ) -> TransitionStateMap {
	// holds a mapping of transitions to states which need to be aggregated
	TransitionStateMap toAggregate;
	// holds a mapping of transitions to states which are ready to apply the reset function and the intersection with the invariant
	TransitionStateMap toProcess;
	// holds a mapping of transitions to already processed (i.e. aggregated, resetted and reduced) states
	TransitionStateMap processedStates;
	for ( const auto& [transitionPtr, statesVec] : states ) {
		// only handle sets related to the passed transition, in case any is passed.
		if ( transition == nullptr || transitionPtr == transition ) {
			// check aggregation settings

			if ( ( strategy.aggregation == AGG_SETTING::NO_AGG && strategy.clustering == -1 ) ||
				 ( strategy.aggregation == AGG_SETTING::MODEL && transitionPtr->getAggregation() == Aggregation::none ) ) {
				// just copy the states to the toProcess map.

				auto& targetVec = toProcess[transitionPtr];
				targetVec.insert( targetVec.end(), statesVec.begin(), statesVec.end() );
			} else {  // store for aggregation
				auto& targetVec = toAggregate[transitionPtr];
				targetVec.insert( targetVec.end(), statesVec.begin(), statesVec.end() );
			}
		}
	}

	// aggregate all sets marked for aggregation
	aggregate( toProcess, toAggregate, strategy );

	DEBUG( "hydra.worker", "Apply jump on " << toProcess.size() << " transitions." );

	for ( const auto& [transitionPtr, statesVec] : toProcess ) {
		DEBUG( "hydra.worker", "Apply jump on " << statesVec.size() << " states." );
		for ( const auto& state : statesVec ) {
			// copy state - as there is no aggregation, the containing set and timestamp is already valid
			// TODO: Why copy?
			assert( !state.getTimestamp().isEmpty() );
			State newState( state );

			// apply reset function
			applyReset( newState, transitionPtr );

			// set target location in state set
			newState.setLocation( transitionPtr->getTarget() );

			// check invariant in new location
			auto [containment, stateSet] = ltiIntersectInvariant( newState );
			if ( containment == CONTAINMENT::NO ) {
				continue;
			}

			// reduce if possible (Currently only for support functions)
			stateSet.reduceRepresentation();

			DEBUG( "hydra.worker.discrete", "State after reduction: " << stateSet );

			// Note: Here we misuse the state's timestamp to carry the transition timing to the next stage -> just don't reset
			// the timestamp in case no aggregation happens.

			if ( processedStates.find( transitionPtr ) == processedStates.end() ) {
				processedStates[transitionPtr] = std::vector<State>();
			}
			processedStates[transitionPtr].emplace_back( stateSet );
		}
	}
	return processedStates;
}

template <typename State>
void ltiJumpHandler<State>::applyReset( State& state, Transition<Number>* transitionPtr ) const {
	if ( !transitionPtr->getReset().empty() ) {
		for ( size_t i = 0; i < state.getNumberSets(); i++ ) {
			if ( state.getSetType( i ) == representation_name::carl_polytope ) {
				IntervalAssignment<Number> intervalReset = transitionPtr->getReset().getIntervalReset( i );
				state = state.partialIntervalAssignment( intervalReset.mIntervals, i );
			} else {
				AffineTransformation<Number> reset = transitionPtr->getReset().getAffineReset( i );
				state = state.partiallyApplyTransformation( reset.mTransformation, i );
			}
		}
	}
}

template <typename State>
void ltiJumpHandler<State>::aggregate( TransitionStateMap& processedStates, const TransitionStateMap& toAggregate, const AnalysisParameters& strategy ) const {
	// Aggregation
	DEBUG( "hydra.worker.discrete", "Number of transitions to aggregate: " << toAggregate.size() << std::endl );
	for ( const auto& [transition, stateSets] : toAggregate ) {
		assert( !stateSets.empty() );
		TRACE( "hydra.worker.discrete", stateSets.size() << " sets to aggregate for transition " << transition->getSource()->getName() << " -> " << transition->getTarget()->getName() );
		std::vector<State> aggregatedStates;
		// Aggregate sets by using sequential unite operations (TODO Implement and make use of multi-unite).
		State aggregatedState( *stateSets.begin() );
		// counts the number of processed sets - just for debugging.
		unsigned setCnt = 1;
		// counts the number of sets in the current cluster.
		std::size_t clusterCnt = 1;
		// determines whether there are still sets to be clustered together.
		bool leftovers = true;

		TRACE( "hydra.worker.discrete", "Find subspace mapping for loc " << aggregatedState.getLocation()->getName() << " (" << aggregatedState.getLocation() << ")" );

		// perform union directly on the current set vector to avoid an extreme amount of consistency checks
		std::vector<typename State::repVariant> currentSets = aggregatedState.getSets();
		// contains the aggregated timestamp, initialized with the first timestamp
		carl::Interval<tNumber> aggregatedTimestamp = ( *stateSets.begin() ).getTimestamp();
		// START_BENCHMARK_OPERATION(AGGREGATE);
		for ( auto stateIt = ++stateSets.begin(); stateIt != stateSets.end(); ++stateIt ) {
			TRACE( "hydra.worker.discrete", "Agg. aggState and set " << setCnt );
			// actual aggregation.
			for ( std::size_t i = 0; i < aggregatedState.getNumberSets(); i++ ) {
				// START_BENCHMARK_OPERATION(UNION);
				currentSets[i] = std::visit( genericUniteVisitor<typename State::repVariant>(), currentSets[i], stateIt->getSet( i ) );
				// EVALUATE_BENCHMARK_RESULT(UNION);
			}

			// timestamp handling
			assert( !( *stateIt ).getTimestamp().isEmpty() );
			aggregatedTimestamp = aggregatedTimestamp.convexHull( ( *stateIt ).getTimestamp() );

			leftovers = true;
			++setCnt;
			++clusterCnt;
#ifdef CLUSTERING_NUMBER_LIMITS_SUCESSORS
			if ( strategy.clustering > 0 && clusterCnt == std::ceil( double( stateSets.size() ) / double( strategy.clustering ) ) ) {
				TRACE( "hydra.worker.discrete", "Clustering." );
				aggregatedStates.emplace_back( aggregatedState );
				leftovers = false;
				if ( stateIt + 1 != stateSets.end() ) {
					aggregatedState = *( ++stateIt );
					aggregatedTimestamp = aggregatedState.getTimestamp();
					clusterCnt = 1;
				} else {
					break;
				}
			}
#else
			if ( strategy.clustering > 0 && clusterCnt == std::size_t( strategy.clustering ) ) {
				TRACE( "hydra.worker.discrete", "Clustering." );
				aggregatedStates.emplace_back( aggregatedState );
				leftovers = false;
				if ( stateIt + 1 != stateSets.end() ) {
					aggregatedState = *( ++stateIt );
					aggregatedTimestamp = aggregatedState.getTimestamp();
					clusterCnt = 1;
				} else {
					break;
				}
			}
#endif
		}
		aggregatedState.setSets( currentSets );
		// EVALUATE_BENCHMARK_RESULT(AGGREGATE);

		// set timestamps accordingly
		aggregatedState.setTimestamp( aggregatedTimestamp );

		if ( strategy.clustering < 1 || leftovers ) {
			TRACE( "hydra.worker.discrete", "No clustering." );
			aggregatedStates.emplace_back( aggregatedState );
		}

		// add to final mapping.
		for ( auto& state : aggregatedStates ) {
			processedStates[transition].emplace_back( state );
		}
	}
}

}  // namespace hypro
