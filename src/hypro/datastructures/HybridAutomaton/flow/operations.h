#pragma once
#include "../../../types.h"
#include "affine.h"
#include "linear.h"
#include "rectangular.h"
#include "typetraits.h"
#include "visitors.h"

namespace hypro {

template <typename T>
DynamicType getFlowType( const T& f ) {
	return std::visit( flowTypeVisitor(), f );
}

template <typename T>
std::size_t getFlowDimension( const T& f ) {
	return std::visit( flowDimensionVisitor(), f );
}

template <typename T>
bool isTimed( const T& f ) {
#ifdef HYPRO_LOGGING
	bool timed = std::visit( flowIsTimedVisitor(), f );
	DEBUG( "hypro.flow", ": " << timed );
	return timed;
#else
	return std::visit( flowIsTimedVisitor(), f );
#endif
}

template <typename T>
bool isSingular( const T& f ) {
#ifdef HYPRO_LOGGING
	bool singular = std::visit( flowIsSingularVisitor(), f );
	DEBUG( "hypro.flow", ": " << singular );
	return singular;
#else
	return std::visit( flowIsSingularVisitor(), f );
#endif
}

template <typename T>
bool isDiscrete( const T& f ) {
#ifdef HYPRO_LOGGING
	bool discrete = std::visit( flowIsDiscreteVisitor(), f );
	DEBUG( "hypro.flow", ": " << discrete );
	return discrete;
#else
	return std::visit( flowIsDiscreteVisitor(), f );
#endif
}

}  // namespace hypro
