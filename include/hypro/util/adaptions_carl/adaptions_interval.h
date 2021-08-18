#pragma once
#include <carl/interval/Interval.h>
#include <hypro/flags.h>

namespace hypro {

#ifdef CARL_OLD_INTERVALS
template <typename Number>
carl::Interval<Number> set_intersection( const carl::Interval<Number>& lhs, const carl::Interval<Number>& rhs ) {
	return lhs.intersect( rhs );
}
#endif

}  // namespace hypro
