#include "ETC_util.h"

namespace hypro {

std::vector<carl::Interval<tNumber>> getEnabledTimings( const HierarchicalIntervalVector<CONTAINMENT, tNumber>& in ) {
	DEBUG( "hypro.datastructures.etc", "In: " << in );

	std::vector<carl::Interval<tNumber>> res;
	// iterate over the stored timings
	for ( auto eventIt = in.begin(); eventIt != in.end(); ++eventIt ) {
		// handle the first entry differently
		if ( eventIt == in.begin() &&
			 static_cast<int>( eventIt->type ) > 0 ) {
			res.emplace_back( carl::Interval<tNumber>( 0, eventIt->timePoint ) );
			TRACE( "hypro.datastructures.etc", "Found interval " << res.back() );
		}

		if ( eventIt != in.begin() ) {
			// consecutive interval
			if ( static_cast<int>( eventIt->type ) > 0 && static_cast<int>( std::prev( eventIt )->type ) > 0 ) {
				res[res.size() - 1] = res[res.size() - 1].convexHull( carl::Interval<tNumber>( std::prev( eventIt )->timePoint, eventIt->timePoint ) );
				TRACE( "hypro.datastructures.etc", "Extended interval " << res.back() );
			} else if ( static_cast<int>( eventIt->type ) > 0 ) {
				// add new interval
				assert( static_cast<int>( std::prev( eventIt )->type ) <= 0 );
				res.emplace_back( std::prev( eventIt )->timePoint, eventIt->timePoint );
				TRACE( "hypro.datastructures.etc", "Found interval " << res.back() );
			}
		}
	}
	DEBUG( "hypro.datastructures.etc", "Return " << res.size() << " intervals." );
	return res;
}

}  // namespace hypro
