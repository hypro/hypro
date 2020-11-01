#include "stochasticRectangularBadStateHandler.h"

namespace hypro {
template <typename State>
std::vector<std::pair<CONTAINMENT, State>> stochasticRectangularIntersectBadStates( const State& stateSet, const HybridAutomaton<typename State::NumberType>& automaton ) {
	TRACE( "hydra.worker.continuous", "Having a total of " << automaton.getLocalBadStates().size() << " local bad states." );
    std::vector<std::pair<CONTAINMENT, State>> results;
    bool isBad = false;
	auto localBadState = automaton.getLocalBadStates().find( stateSet.getLocation() );
	if ( localBadState != automaton.getLocalBadStates().end() ) {
		TRACE( "hydra.worker.continuous", "Checking local bad state: " << localBadState->second );

		State badState( stateSet );

		// create constraints for invariant. Note that we need to properly match dimension indices with variable names at some point.
		// create carlPolytope, as intersection is defined for those
		badState = State{ CarlPolytope<typename State::NumberType>{ localBadState->second.getMatrix(), localBadState->second.getVector() } };

		// intersect
		auto resultingSet = stateSet.intersect( badState );

		// reduction
		resultingSet.removeRedundancy();

		// process containment information
		if ( resultingSet != stateSet ) {
            results.emplace_back( std::make_pair( CONTAINMENT::YES, resultingSet ) );
            isBad = true;
			CarlPolytope<typename State::NumberType> badStateConstraints{ localBadState->second.getMatrix(), localBadState->second.getVector() };
            for ( size_t i = 0 ; i < badStateConstraints.getFormula().size() ; i++ ) {
                CarlPolytope<typename State::NumberType> badStateNegationConstraints( !badStateConstraints.getFormula().subformulas().at(i) );
                std::vector<ConstraintT<tNumber>> newConstraints;
                for ( size_t j = 0 ; j < i ; j++ ) {
                    badStateConstraints.getFormula().subformulas().at(j).getConstraints( newConstraints );
                }
                badStateNegationConstraints.addConstraints(newConstraints);
                auto newStateSet = std::get<CarlPolytope<typename State::NumberType>>( stateSet.getSet() ).intersect( badStateNegationConstraints );
                newStateSet.removeRedundancy();
				State newState(stateSet);
				newState.setSet( newStateSet);
                results.emplace_back( std::make_pair( CONTAINMENT::NO, newState ) );
            }
			DEBUG( "hydra.worker", "Intersection with local bad states." );
			// return std::make_pair( CONTAINMENT::YES, resultingSet );
		}
	}

	TRACE( "hydra.worker.continuous", "No intersection with local, continuous bad states" );

	// check global bad states
	for ( const auto& badState : automaton.getGlobalBadStates() ) {
		if ( badState.getMatrix().rows() != 0 ) {
			// at least one global bad state in this subspace
			State badState( stateSet );

			// create constraints for invariant. Note that we need to properly match dimension indices with variable names at some point.
			// create carlPolytope, as intersection is defined for those
			badState = State{ CarlPolytope<typename State::NumberType>{ localBadState->second.getMatrix(), localBadState->second.getVector() } };

			// intersect
			auto resultingSet = stateSet.intersect( badState );

			// reduction
			resultingSet.removeRedundancy();

			// process containment information
			if ( resultingSet != stateSet ) {
				results.emplace_back( std::make_pair( CONTAINMENT::YES, resultingSet ) );
				isBad = true;
				CarlPolytope<typename State::NumberType> badStateConstraints{ localBadState->second.getMatrix(), localBadState->second.getVector() };
				for ( size_t i = 0 ; i < badStateConstraints.getFormula().size() ; i++ ) {
					CarlPolytope<typename State::NumberType> badStateNegationConstraints( !badStateConstraints.getFormula().subformulas().at(i) );
					std::vector<ConstraintT<tNumber>> newConstraints;
					for ( size_t j = 0 ; j < i ; j++ ) {
						badStateConstraints.getFormula().subformulas().at(j).getConstraints( newConstraints );
					}
					badStateNegationConstraints.addConstraints(newConstraints);
					auto newStateSet = std::get<CarlPolytope<typename State::NumberType>>( stateSet.getSet() ).intersect( badStateNegationConstraints );
					newStateSet.removeRedundancy();
					State newState(stateSet);
					newState.setSet( newStateSet);
					results.emplace_back( std::make_pair( CONTAINMENT::NO, newState ) );
				}
				DEBUG( "hydra.worker", "Intersection with local bad states." );
				// return std::make_pair( CONTAINMENT::YES, resultingSet );
			}
		}
	}

    if ( !isBad ) {
        results.emplace_back( std::make_pair( CONTAINMENT::NO, stateSet ) );
    }

	return results;
}

}  // namespace hypro
