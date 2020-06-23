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
			auto containmentStateSetPair = ltiIntersectInvariant( newState );
			if ( containmentStateSetPair.first == CONTAINMENT::NO ) {
				continue;
			}

			// reduce if possible (Currently only for support functions)
			applyReduction( containmentStateSetPair.second );

			DEBUG( "hydra.worker.discrete", "State after reduction: " << containmentStateSetPair.second );

			// Note: Here we misuse the state's timestamp to carry the transition timing to the next stage -> just don't reset
			// the timestamp in case no aggregation happens.

			if ( processedStates.find( transitionPtr ) == processedStates.end() ) {
				processedStates[transitionPtr] = std::vector<State>();
			}
			processedStates[transitionPtr].emplace_back( containmentStateSetPair.second );
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
void ltiJumpHandler<State>::applyReduction( State& state ) const {
	// TODO why does the reduction visitor not work for multi sets?
	for ( size_t i = 0; i < state.getNumberSets(); i++ ) {
		if ( state.getSetType( i ) == representation_name::support_function ) {
			state.partiallyReduceRepresentation( i );
		}
		if ( state.getSetType( i ) == representation_name::SFN ) {
			//Cut off the subtrees from the root of the supportfunction by overapproximating the representation with a hpolytope (or possibly a box)
			//and set it as the leaf of a new tree
			auto tmpSFN = std::visit( genericConvertAndGetVisitor<SupportFunctionNew<typename State::NumberType>>(), state.getSet( i ) );
			if ( tmpSFN.getSettings().DETECT_BOX ) {
				//if(!tmpSFN.empty()){
				tmpSFN.reduceRepresentation();
				auto isHPolyBox = isBox( tmpSFN.matrix(), tmpSFN.vector() );
				if ( std::get<0>( isHPolyBox ) ) {
					Box<Number> tmpBox( std::get<1>( isHPolyBox ) );
					tmpSFN = SupportFunctionNew<Number>( tmpBox );
				} else {
					HPolytopeT<Number, hypro::Converter<Number>, HPolytopeOptimizerCaching> tmpHPoly( tmpSFN.matrix(), tmpSFN.vector() );
					tmpSFN = SupportFunctionNew<Number>( tmpHPoly );
				}
				state.setSet( std::visit( genericInternalConversionVisitor<typename State::repVariant, SupportFunctionNew<Number>>( tmpSFN ), state.getSet( i ) ), i );
				//}
			}
		}
	}
}

template <typename State>
void ltiJumpHandler<State>::aggregate( TransitionStateMap& processedStates, const TransitionStateMap& toAggregate, const AnalysisParameters& strategy ) const {
	// Aggregation
	DEBUG( "hydra.worker.discrete", "Number of transitions to aggregate: " << toAggregate.size() << std::endl );
	for ( const auto& transitionStatePair : toAggregate ) {
		assert( !transitionStatePair.second.empty() );
		TRACE( "hydra.worker.discrete", transitionStatePair.second.size() << " sets to aggregate for transition " << transitionStatePair.first->getSource()->getName() << " -> " << transitionStatePair.first->getTarget()->getName() );
		std::vector<State> aggregatedStates;
		// Aggregate sets by using sequential unite operations (TODO: Implement and make use of multi-unite).
		State aggregatedState( *transitionStatePair.second.begin() );
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
		carl::Interval<tNumber> aggregatedTimestamp = ( *transitionStatePair.second.begin() ).getTimestamp();
		//START_BENCHMARK_OPERATION(AGGREGATE);
		for ( auto stateIt = ++transitionStatePair.second.begin(); stateIt != transitionStatePair.second.end(); ++stateIt ) {
			TRACE( "hydra.worker.discrete", "Agg. aggState and set " << setCnt );
			// actual aggregation.
			for ( std::size_t i = 0; i < aggregatedState.getNumberSets(); i++ ) {
				//START_BENCHMARK_OPERATION(UNION);
				currentSets[i] = std::visit( genericUniteVisitor<typename State::repVariant>(), currentSets[i], stateIt->getSet( i ) );
				//EVALUATE_BENCHMARK_RESULT(UNION);
			}

			// timestamp handling
			assert( !( *stateIt ).getTimestamp().isEmpty() );
			aggregatedTimestamp = aggregatedTimestamp.convexHull( ( *stateIt ).getTimestamp() );

			leftovers = true;
			++setCnt;
			++clusterCnt;
#ifdef CLUSTERING_NUMBER_LIMITS_SUCESSORS
			if ( strategy.clustering > 0 && clusterCnt == std::ceil( double( transitionStatePair.second.size() ) / double( strategy.clustering ) ) ) {
				TRACE( "hydra.worker.discrete", "Clustering." );
				aggregatedStates.emplace_back( aggregatedState );
				leftovers = false;
				if ( stateIt + 1 != transitionStatePair.second.end() ) {
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
				if ( stateIt + 1 != transitionStatePair.second.end() ) {
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
		//EVALUATE_BENCHMARK_RESULT(AGGREGATE);

		// set timestamps accordingly
		aggregatedState.setTimestamp( aggregatedTimestamp );

		if ( strategy.clustering < 1 || leftovers ) {
			TRACE( "hydra.worker.discrete", "No clustering." );
			aggregatedStates.emplace_back( aggregatedState );
		}

		// add to final mapping.
		for ( auto& state : aggregatedStates ) {
			processedStates[transitionStatePair.first].emplace_back( state );
		}
	}
}

}  // namespace hypro
