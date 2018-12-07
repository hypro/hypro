#pragma once
#include "../../../../representations/GeometricObject.h"
#include "../../../../datastructures/HybridAutomaton/State.h"

namespace hypro {
    template <typename State>
	State bloatBox( const State& in, const hypro::Box<typename State::NumberType>& bloatBox , size_t index) {
        DEBUG("hypro.datastructures","For index " << index);
        State bloatState{in}; // Todo: this is clumsy, as we just require SOME state set in the state.

        bloatState.setSet(boost::apply_visitor(genericInternalConversionVisitor<typename State::repVariant,hypro::Box<typename State::NumberType>>(bloatBox), bloatState.rGetSet(index)));
        return in.partiallyMinkowskiSum(bloatState, index);
    }
} // hypro
