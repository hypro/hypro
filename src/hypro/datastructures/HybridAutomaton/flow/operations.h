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
bool isTimed( const T& f) {
#ifdef HYPRO_LOGGING
    bool timed = boost::apply_visitor( flowIsTimedVisitor(), f);
    DEBUG("hypro.flow",": "<< timed);
    return timed;
#else
    return boost::apply_visitor( flowIsTimedVisitor(), f);
#endif
}

template<typename T>
bool isDiscrete( const T& f) {
#ifdef HYPRO_LOGGING
    bool discrete = boost::apply_visitor( flowIsDiscreteVisitor(), f);
    DEBUG("hypro.flow",": "<< discrete);
    return discrete;
#else
    return boost::apply_visitor( flowIsDiscreteVisitor(), f);
#endif
}

} //
