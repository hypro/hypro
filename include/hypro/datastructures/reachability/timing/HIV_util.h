#pragma once
#include "HierarchicalIntervalVector.h"

namespace hypro {

template <typename T, typename N>
static HierarchicalIntervalVector<T, N> merge( std::initializer_list<HierarchicalIntervalVector<T, N>> l ) {
	assert( l.size() != 0 );
	auto lIt = l.begin();
	HierarchicalIntervalVector<T, N> res = ( *lIt );
	TRACE( "hypro.datastructures.hiv", "Res initialized: " << res );
	lIt++;
	for ( ; lIt != l.end(); ++lIt ) {
		N prevTimepoint = N( 0 );
		for ( auto& endPoint : ( *lIt ).getIntervals() ) {
			res.insertInterval( endPoint.type, carl::Interval<N>( prevTimepoint, endPoint.timePoint ) );
			prevTimepoint = endPoint.timePoint;
		}
		TRACE( "hypro.datastructures.hiv", "Intermediate res: " << res );
	}
	TRACE( "hypro.datastructures.hiv", "Final res: " << res );
	return res;
}

template <typename T, typename N>
static HierarchicalIntervalVector<T, N> unite( std::initializer_list<HierarchicalIntervalVector<T, N>> l ) {
	assert( l.size() != 0 );
	auto lIt = l.begin();
	HierarchicalIntervalVector<T, N> res = *lIt++;
	auto originalOrder = res.getTypeOrder();
	auto reversedOrder = originalOrder;
	std::reverse( reversedOrder.begin(), reversedOrder.end() );
	res.setTypeOrder( reversedOrder );

	for ( ; lIt != l.end(); ++lIt ) {
		N prevTimepoint = N( 0 );
		for ( auto& endPoint : ( *lIt ).getIntervals() ) {
			res.insertInterval( endPoint.type, carl::Interval<N>( prevTimepoint, endPoint.timePoint ) );
			prevTimepoint = endPoint.timePoint;
		}
	}
	res.setTypeOrder( originalOrder );

	return res;
}

template <typename T, typename N>
static std::optional<HierarchicalIntervalVector<T, N>> intersect( std::initializer_list<HierarchicalIntervalVector<T, N>> l ) {
	if ( l.size() == 0 ) {
		return std::nullopt;
	}
	// debatable
	return merge( l );
}

template <typename T, typename N>
static bool fullCover( const HierarchicalIntervalVector<T, N>& in, const carl::Interval<N>& intv, T type ) {
#ifndef NDEBUG
	bool verifiedRes = false;
	// get all intervals that satisfy bot criteria: Intersection interval-wise and correct type.
	auto intervals = in.getIntersectionIntervals( intv, type );
	// we assume the intervals returned are pairwise-disjunct.
	if ( intervals.size() == 1 ) {
		DEBUG( "hypro.datastructures.hiv", "Intersecting interval: " << intervals[0] );
		if ( intervals[0] == intv ) {
			verifiedRes = true;
		}
	}
#endif

	if ( in.coversEntry( intv, type ) ) {
		assert( verifiedRes );
		return true;
	}
	assert( !verifiedRes );
	return false;
}

template <typename T, typename N>
static std::optional<std::size_t> smallestFullCover( const std::vector<HierarchicalIntervalVector<T, N>>& hivs, const carl::Interval<N>& intv, T type ) {
	bool hasFullCover = false;
	std::size_t res = 0;
	carl::Interval<N> smallest = createUnboundedInterval<N>();
	for ( std::size_t i = 0; i < hivs.size(); ++i ) {
		// get all intervals that satisfy bot criteria: Intersection interval-wise and correct type.
		auto intervals = hivs[i].getIntersectingIntervals( intv, type );
		// we assume the intervals returned are pairwise-disjunct.
		if ( intervals.size() == 1 ) {
			DEBUG( "hypro.datastructures.hiv", "Intersecting interval: " << intervals[0] );
			if ( smallest.contains( intervals[0] ) && intervals[0].contains( intv ) ) {
				smallest = intervals[0];
				res = i;
				hasFullCover = true;
			}
		}
	}

	// if none of the hivs covers the interval, return invalid.
	if ( !hasFullCover ) {
		return std::nullopt;
	}
	return res;
}

}  // namespace hypro
