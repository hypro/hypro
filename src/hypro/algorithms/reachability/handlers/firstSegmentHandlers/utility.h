#pragma once
#include "../../../../representations/GeometricObject.h"
#include "../../../../datastructures/HybridAutomaton/State.h"

namespace hypro {
    template <typename Number>
	State_t<Number> bloatBox( const State_t<Number>& in, const hypro::Box<Number>& bloatBox , size_t index) {
        State_t<Number> bloatState;
        switch(in.getSetType(index)) {
            case hypro::representation_name::box: {
                bloatState.setSet(hypro::Converter<Number>::toBox(bloatBox), index);
                break;
            }
            case hypro::representation_name::polytope_h: {
                bloatState.setSet(hypro::Converter<Number>::toHPolytope(bloatBox), index);
                break;
            }
            case hypro::representation_name::polytope_v: {
                bloatState.setSet(hypro::Converter<Number>::toVPolytope(bloatBox), index);
                break;
            }
            case hypro::representation_name::support_function: {
                bloatState.setSet(hypro::Converter<Number>::toSupportFunction(bloatBox), index);
                break;
            }
            case hypro::representation_name::zonotope: {
                bloatState.setSet(hypro::Converter<Number>::toZonotope(bloatBox), index);
                break;
            }
            default: {
                bloatState.setSet(hypro::Converter<Number>::toBox(bloatBox), index);
                break;
            }
        }
        return in.partiallyMinkowskiSum(bloatState, index);
    }
} // hypro