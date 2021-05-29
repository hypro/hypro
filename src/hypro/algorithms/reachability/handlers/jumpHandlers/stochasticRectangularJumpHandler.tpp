#include "stochasticRectangularJumpHandler.h"

namespace hypro {

template <typename State>
auto stochasticRectangularJumpHandler<State>::applyJump( const TransitionStateMap& states, StochasticTransition<Number>* transition, const AnalysisParameters& strategy ) -> TransitionStateMap {
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
	// aggregate( toProcess, toAggregate, strategy );

	DEBUG( "hydra.worker", "Apply jump on " << toProcess.size() << " transitions." );

	for ( const auto& [transitionPtr, statesVec] : toProcess ) {
		DEBUG( "hydra.worker", "Apply jump on " << statesVec.size() << " states." );
		for ( const auto& state : statesVec ) {
			// copy state - as there is no aggregation, the containing set and timestamp is already valid
			// TODO: Why copy?

			// std::cout<<"before apply: " << &state <<", " << state.getLocation() << std::endl;
			assert( !state.getTimestamp().isEmpty() );
			State newState( state );
			// std::cout << "new state set: " << newState << std::endl;

			// apply reset function
			applyReset( newState, transitionPtr );
			newState.removeRedundancy();
			// std::cout << "new state set after reset: " << newState << std::endl;

			// set target location in state set
			newState.setLocation( transitionPtr->getTarget() );

			// check invariant in new location
			auto [containment, stateSet] = rectangularIntersectInvariant( newState );
			if ( containment == CONTAINMENT::NO ) {
				continue;
			}

			// reduce if possible (Currently only for support functions)
			applyReduction( stateSet );

			DEBUG( "hydra.worker.discrete", "State after reduction: " << stateSet );

			// Note: Here we misuse the state's timestamp to carry the transition timing to the next stage -> just don't reset
			// the timestamp in case no aggregation happens.

			if ( processedStates.find( transitionPtr ) == processedStates.end() ) {
				processedStates[transitionPtr] = std::vector<State>();
			}
			processedStates[transitionPtr].emplace_back( stateSet );
			// std::cout<<"after apply: " <<&stateSet <<", " << stateSet.getLocation() << std::endl;

			// std::cout << "new state set add to processed: " << stateSet << std::endl;

			mPredecessor.emplace_back( std::make_pair( stateSet, state ) );
			// if (state == stateSet) {
			// 	std::cout << "operator == is true!" <<std::endl;
			// }
		}
	}
	return processedStates;
}

template <typename State>
void stochasticRectangularJumpHandler<State>::applyReset( State& state, StochasticTransition<Number>* transitionPtr ) const {
	if ( !transitionPtr->getReset().empty() ) {
		if ( transitionPtr->getReset().getMatrix().size() > 0 ) {
			state = State{ CarlPolytope<typename State::NumberType>{ transitionPtr->getReset().getMatrix(), transitionPtr->getReset().getVector() } };
		} else if( !transitionPtr->getReset().getIntervalResets().empty() ){
			std::cout << "interval reset not empty" << std::endl;
			for ( size_t i = 0; i < state.getNumberSets(); i++ ) {
				IntervalAssignment<Number> intervalReset = transitionPtr->getReset().getIntervalReset( i );
				state = state.partialIntervalAssignment( intervalReset.mIntervals, i );
			}
		}
	}
}

template <typename State>
void stochasticRectangularJumpHandler<State>::applyReduction( State& state ) const {
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
void stochasticRectangularJumpHandler<State>::aggregate( TransitionStateMap& processedStates, const TransitionStateMap& toAggregate, const AnalysisParameters& strategy ) const {
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
		//START_BENCHMARK_OPERATION(AGGREGATE);
		for ( auto stateIt = ++stateSets.begin(); stateIt != stateSets.end(); ++stateIt ) {
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
		//EVALUATE_BENCHMARK_RESULT(AGGREGATE);

		// set timestamps accordingly
		aggregatedState.setTimestamp( aggregatedTimestamp );

		if ( strategy.clustering < 1 || leftovers ) {
			TRACE( "hydra.worker.discrete", "No clustering." );
			aggregatedStates.emplace_back( aggregatedState );
		}

		// add to final mapping.
		for ( auto& state : aggregatedStates ) {
			if ( processedStates.find( transition ) == processedStates.end() ) {
				processedStates[transition] = std::vector<State>();
			}
			processedStates[transition].emplace_back( state );
		}
	}
}

template <typename State>
State stochasticRectangularJumpHandler<State>::applyReverseJump( State& state, StochasticTransition<Number>* transitionPtr, const AnalysisParameters& strategy ) {
	
	assert( !state.getTimestamp().isEmpty() );
	State newState( state );

	// apply guard function
	applyGuard( newState, transitionPtr );

	// set target location in state set
	newState.setLocation( transitionPtr->getSource() );

	// check invariant in new location
	auto [containment, stateSet] = rectangularIntersectInvariant( newState );
	// if ( containment == CONTAINMENT::NO ) {
	// 	continue;
	// }

	// reduce if possible (Currently only for support functions)
	applyReduction( stateSet );

	DEBUG( "hydra.worker.discrete", "State after reduction: " << stateSet );
	
	return stateSet;
}

template <typename State>
void stochasticRectangularJumpHandler<State>::applyGuard( State& state, StochasticTransition<Number>* transitionPtr ) const {
	if ( !transitionPtr->getGuard().empty() ) {
		// std::cout << "guard is not empty" << std::endl;
		state.setSet( typename State::template nth_representation<0>{ transitionPtr->getGuard().getMatrix(), transitionPtr->getGuard().getVector() } );
	}
}
}  // namespace hypro
