#pragma once
#include "affine.h"
#include "linear.h"
#include "rectangular.h"
#include "visitors.h"
#include "typetraits.h"
#include "../../../types.h"

namespace hypro {

template<typename T>
DynamicType getFlowType( const T& f) {
    return boost::apply_visitor( flowTypeVisitor(), f);
}

template<typename T>
std::size_t getFlowDimension( const T& f) {
    return boost::apply_visitor( flowDimensionVisitor(), f);
}

template<typename T>
std::size_t isTimed( const T& f) {
    return boost::apply_visitor( flowIsTimedVisitor(), f);
}

template<typename T>
std::size_t isDiscrete( const T& f) {
    return boost::apply_visitor( flowIsDiscreteVisitor(), f);
}

} //