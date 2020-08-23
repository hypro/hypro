#include "rectangularJumpHandler.h"

namespace hypro {

template <typename State>
auto rectangularJumpHandler<State>::applyJump( const TransitionStateMap& states, Transition<Number>* transition, const AnalysisParameters& strategy ) -> TransitionStateMap {
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

			auto& targetVec = toProcess[transitionPtr];
			targetVec.insert( targetVec.end(), statesVec.begin(), statesVec.end() );
		}
	}

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
		}
	}
	return processedStates;
}

template <typename State>
void rectangularJumpHandler<State>::applyReset( State& state, Transition<Number>* transitionPtr ) const {
	if ( !transitionPtr->getReset().empty() ) {
		if ( transitionPtr->getReset().getMatrix().size() > 0 ) {
			std::cout << "affine is  " << std::endl;
			state = State{ CarlPolytope<typename State::NumberType>{ transitionPtr->getReset().getMatrix(), transitionPtr->getReset().getVector() } };
		} else {
			for ( size_t i = 0; i < state.getNumberSets(); i++ ) {
				IntervalAssignment<Number> intervalReset = transitionPtr->getReset().getIntervalReset( i );
				state = state.partialIntervalAssignment( intervalReset.mIntervals, i );
			}
		}
	}
}

template <typename State>
void rectangularJumpHandler<State>::applyReduction( State& state ) const {
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
auto rectangularJumpHandler<State>::applyReverseJump( const TransitionStateMap& states, Transition<Number>* transition, const AnalysisParameters& strategy ) -> TransitionStateMap {
	// holds a mapping of transitions to states which are ready to apply the reset function and the intersection with the invariant
	TransitionStateMap toProcess;
	// holds a mapping of transitions to already processed (i.e. aggregated, resetted and reduced) states
	TransitionStateMap processedStates;
	for ( const auto& [transitionPtr, statesVec] : states ) {
		// only handle sets related to the passed transition, in case any is passed.
		if ( transition == nullptr || transitionPtr == transition ) {
			auto& targetVec = toProcess[transitionPtr];
			targetVec.insert( targetVec.end(), statesVec.begin(), statesVec.end() );
		}
	}

	DEBUG( "hydra.worker", "Apply jump on " << toProcess.size() << " transitions." );

	for ( const auto& [transitionPtr, statesVec] : toProcess ) {
		DEBUG( "hydra.worker", "Apply jump on " << statesVec.size() << " states." );
		for ( const auto& state : statesVec ) {
			// copy state - as there is no aggregation, the containing set and timestamp is already valid
			// TODO: Why copy?
			assert( !state.getTimestamp().isEmpty() );
			State newState( state );

			// apply guard function
			applyGuard( newState, transitionPtr );

			// set target location in state set
			newState.setLocation( transitionPtr->getSource() );

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
		}
	}
	return processedStates;
}

template <typename State>
void rectangularJumpHandler<State>::applyGuard( State& state, Transition<Number>* transitionPtr ) const {
	if ( !transitionPtr->getGuard().empty() ) {
		state.setSet( typename State::template nth_representation<0>{ transitionPtr->getGuard().getMatrix(), transitionPtr->getGuard().getVector() } );
	}
}
}  // namespace hypro
