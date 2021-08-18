#pragma once
#include "../../../../datastructures/HybridAutomaton/State.h"
#include "../../../../representations/GeometricObjectBase.h"

namespace hypro {
template <typename State>
State bloatBox( const State& in, const hypro::Box<typename State::NumberType>& bloatBox, size_t index ) {
	DEBUG( "hypro.worker", "For index " << index );
	State bloatState{in};  // Todo: this is clumsy, as we just require SOME state set in the state.

	bloatState.setSet( std::visit( genericInternalConversionVisitor<typename State::repVariant, hypro::Box<typename State::NumberType>>( bloatBox ), bloatState.rGetSet( index ) ), index );
	DEBUG( "hypro.worker", "Used box for bloating: " << bloatState );
	return in.partiallyMinkowskiSum( bloatState, index );
}
}  // namespace hypro
