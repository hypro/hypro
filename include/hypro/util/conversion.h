#pragma once
#include "../types.h"

namespace hypro {
template <typename From, typename To>
carl::Interval<To> convert( const carl::Interval<From>& original ) {
	return carl::Interval<To>( carl::convert<From, To>( original.lower() ), lowerBoundType( original ), carl::convert<From, To>( original.upper() ), upperBoundType( original ) );
}
}  // namespace hypro
