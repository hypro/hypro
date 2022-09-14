#pragma once
#include "adaptions_includes.h"

#include <hypro/flags.h>

namespace hypro {

#ifdef CARL_OLD_INTERVALS
template <typename Number>
carl::Interval<Number> set_intersection( const carl::Interval<Number>& lhs, const carl::Interval<Number>& rhs ) {
	return lhs.intersect( rhs );
}
#endif

template <typename Number>
carl::BoundType lowerBoundType( const carl::Interval<Number>& in ) {
#ifdef CARL_OLD_STRUCTURE
	return in.lowerBoundType();
#else
	return in.lower_bound_type();
#endif
}

template <typename Number>
carl::BoundType upperBoundType( const carl::Interval<Number>& in ) {
#ifdef CARL_OLD_STRUCTURE
	return in.upperBoundType();
#else
	return in.upper_bound_type();
#endif
}

template <typename Number>
void setUpperBound( carl::Interval<Number>& in, Number bound ) {
#ifdef CARL_OLD_STRUCTURE
	in.setUpper( bound );
#else
	in.set_upper( bound );
#endif
}

template <typename Number>
void setLowerBound( carl::Interval<Number>& in, Number bound ) {
#ifdef CARL_OLD_STRUCTURE
	in.setLower( bound );
#else
	in.set_lower( bound );
#endif
}

template <typename Number>
void setUpperBoundType( carl::Interval<Number>& in, carl::BoundType bound ) {
#ifdef CARL_OLD_STRUCTURE
	in.setUpperBoundType( bound );
#else
	in.set_upper_bound_type( bound );
#endif
}

template <typename Number>
void setLowerBoundType( carl::Interval<Number>& in, carl::BoundType bound ) {
#ifdef CARL_OLD_STRUCTURE
	in.setLowerBoundType( bound );
#else
	in.set_lower_bound_type( bound );
#endif
}

template <typename Number>
bool isEmpty( const carl::Interval<Number>& in ) {
#ifdef CARL_OLD_STRUCTURE
	return in.isEmpty();
#else
	return in.is_empty();
#endif
}

template <typename Number>
bool isUnbounded( const carl::Interval<Number>& in ) {
#ifdef CARL_OLD_STRUCTURE
	return in.isUnbounded();
#else
	return in.is_unbounded();
#endif
}

template <typename Number>
carl::Interval<Number> createEmptyInterval() {
#ifdef CARL_OLD_STRUCTURE
	return carl::Interval<Number>::emptyInterval();
#else
	return carl::Interval<Number>::empty_interval();
#endif
}

template <typename Number>
carl::Interval<Number> createUnboundedInterval() {
#ifdef CARL_OLD_STRUCTURE
	return carl::Interval<Number>::unboundedInterval();
#else
	return carl::Interval<Number>::unbounded_interval();
#endif
}

template <typename Number>
std::vector<carl::Interval<Number>> split_homogeneously_weak_bounds( const carl::Interval<Number>& in, std::size_t splits ) {
	std::vector<carl::Interval<Number>> result;
	if ( splits == 0 ) {
		assert( false );
		result.emplace_back( createEmptyInterval<Number>() );
		return result;
	} else if ( splits == 1 ) {
		result.push_back( in );
		return result;
	}
	Number diameter = in.diameter();
	diameter /= Number( splits );

	carl::Interval<Number> tmp;
	tmp.set( in.lower(), in.lower() + diameter );
	setLowerBoundType( tmp, lowerBoundType( in ) );
	setUpperBoundType( tmp, carl::BoundType::WEAK );
	result.push_back( tmp );

	setLowerBoundType( tmp, carl::BoundType::WEAK );
	for ( unsigned i = 1; i < ( splits - 1 ); ++i ) {
		tmp += diameter;
		result.push_back( tmp );
	}

	tmp += diameter;
	setUpperBoundType( tmp, upperBoundType( in ) );
	result.push_back( tmp );
	return result;
}

}  // namespace hypro
