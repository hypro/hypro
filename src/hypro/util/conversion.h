#pragma once
#include <carl/interval/Interval.h>

namespace hypro {
template <typename From, typename To>
carl::Interval<To> convert( const carl::Interval<From>& original ) {
	return carl::Interval<To>( carl::convert<From, To>( original.lower() ), original.getLowerBoundType(), carl::convert<From, To>( original.upper() ), original.getUpperBoundType() );
}
}  // namespace hypro
