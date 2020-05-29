#include "rectangularBadStateHandler.h"

namespace hypro {
template <typename State>
CONTAINMENT rectangularBadStateHandler<State>::operator()( State& currentStateSet ) {
	auto& vpool = hypro::VariablePool::getInstance();
	auto& automaton = SettingsProvider<State>::getInstance().getHybridAutomaton();

	TRACE( "hydra.worker.continuous", "Having a total of " << automaton.getLocalBadStates().size() << " local bad states." );
	auto localBadState = automaton.getLocalBadStates().find( currentStateSet.getLocation() );
	if ( localBadState != automaton.getLocalBadStates().end() ) {
		TRACE( "hydra.worker.continuous", "Checking local bad state: " << localBadState->second );

		// create constraints for invariant. Note that we need to properly match dimension indices with variable names at some point.
		// create carlPolytope, as intersection is defined for those
		CarlPolytope<typename State::NumberType> badStateConstraints{localBadState->second.getMatrix( mIndex ), localBadState->second.getVector( mIndex )};
		// substitute variables in the formulas by the correct ones in the subspace of the state
		// 1. Determine offset
		std::size_t dimensionOffset = currentStateSet.getDimensionOffset( mIndex );
		// 2. substitute
		for ( std::size_t i = 0; i < currentStateSet.getDimension( mIndex ); ++i ) {
			badStateConstraints.substituteVariable( vpool.carlVarByIndex( i ), vpool.carlVarByIndex( i + dimensionOffset ) );
		}

		// intersect
		auto resultingSet = std::get<CarlPolytope<typename State::NumberType>>( currentStateSet.getSet( mIndex ) ).intersect( badStateConstraints );

		// reduction
		resultingSet.removeRedundancy();

		// set containment information
		if ( resultingSet.empty() ) {
			mContainment = CONTAINMENT::NO;
		} else {
			mContainment = CONTAINMENT::YES;
		}

		if ( mContainment != hypro::CONTAINMENT::NO ) {
			DEBUG( "hydra.worker", "Intersection with local bad states. (intersection type " << mContainment << ")" );
			return mContainment;
		}
	}

	TRACE( "hydra.worker.continuous", "No intersection with local, continuous bad states" );

	// check global bad states
	for ( const auto& badState : automaton.getGlobalBadStates() ) {
		if ( badState.getMatrix( mIndex ).rows() != 0 ) {
			// at least one global bad state in this subspace
			// create constraints for invariant. Note that we need to properly match dimension indices with variable names at some point.
			// create carlPolytope, as intersection is defined for those
			CarlPolytope<typename State::NumberType> badStateConstraints{badState.getMatrix( mIndex ), badState.getVector( mIndex )};
			// substitute variables in the formulas by the correct ones in the subspace of the state
			// 1. Determine offset
			std::size_t dimensionOffset = currentStateSet.getDimensionOffset( mIndex );
			// 2. substitute
			for ( std::size_t i = 0; i < currentStateSet.getDimension( mIndex ); ++i ) {
				badStateConstraints.substituteVariable( vpool.carlVarByIndex( i ), vpool.carlVarByIndex( i + dimensionOffset ) );
			}

			// intersect
			auto resultingSet = std::get<CarlPolytope<typename State::NumberType>>( currentStateSet.getSet( mIndex ) ).intersect( badStateConstraints );

			// reduction
			resultingSet.removeRedundancy();

			// set containment information
			if ( resultingSet.empty() ) {
				mContainment = CONTAINMENT::NO;
			} else {
				mContainment = CONTAINMENT::YES;
			}

			if ( mContainment != hypro::CONTAINMENT::NO ) {
				DEBUG( "hydra.worker", "Intersection with global bad states." );
				return mContainment;
			}
		}
	}
	mContainment = CONTAINMENT::NO;
	return mContainment;
}

}  // namespace hypro
