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

template <typename Number>
std::vector<carl::Interval<Number>> split_homogeneously_weak_bounds( const carl::Interval<Number>& in, std::size_t splits ) {
	std::vector<carl::Interval<Number>> result;
	if ( splits == 0 ) {
		assert( false );
		result.emplace_back( carl::Interval<Number>::emptyInterval() );
		return result;
	} else if ( splits == 1 ) {
		result.push_back( in );
		return result;
	}
	Number diameter = in.diameter();
	diameter /= Number( splits );

	carl::Interval<Number> tmp;
	tmp.set( in.lower(), in.lower() + diameter );
	tmp.setLowerBoundType( in.lowerBoundType() );
	tmp.setUpperBoundType( carl::BoundType::WEAK );
	result.push_back( tmp );

	tmp.setLowerBoundType( carl::BoundType::WEAK );
	for ( unsigned i = 1; i < ( splits - 1 ); ++i ) {
		tmp += diameter;
		result.push_back( tmp );
	}

	tmp += diameter;
	tmp.setUpperBoundType( in.upperBoundType() );
	result.push_back( tmp );
	return result;
}

}  // namespace hypro
