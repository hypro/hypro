#include "HierarchicalIntervalVector.h"

namespace hypro {

template <typename T, typename Number>
void HierarchicalIntervalVector<T, Number>::initialize( const T& baseElement, Number endTime ) {
	if ( !mIntervals.empty() ) {
		this->clear();
	}
	mIntervals.emplace_back( endPoint<T, Number>( baseElement, endTime ) );
	assert( this->isSane() );
}

template <typename T, typename Number>
void HierarchicalIntervalVector<T, Number>::insertInterval( const T& type, const carl::Interval<Number>& timespan ) {
	assert( this->isSane() );
	carl::Interval<Number> copy = timespan;
#ifdef HYPRO_LOGGING
	carl::Interval<double> tmp = carl::Interval<double>( carl::convert<Number, double>( copy.lower() ), carl::convert<Number, double>( copy.upper() ) );
	DEBUG( "hypro.datastructures.hiv", "Insert interval " << tmp << " of type " << type << " into: " << *this );
#endif

	for ( auto it = mIntervals.begin(); it != mIntervals.end(); ++it ) {
#ifdef HYPRO_LOGGING
		double tmptp = carl::convert<Number, double>( it->timePoint );
		TRACE( "hypro.datastructures.hiv", "Consider " << tmptp << ", " << it->type );
#endif
		if ( it->timePoint <= copy.lower() ) {
			TRACE( "hypro.datastructures.hiv", "Area not reached, skip." );
			continue;
		}
		if ( ( it != mIntervals.begin() && std::prev( it )->timePoint >= copy.upper() ) ) {
			TRACE( "hypro.datastructures.hiv", "Done." );
			break;
		}

		if ( copy.upper() >= it->timePoint && ( ( it == mIntervals.begin() && copy.lower() == Number( 0 ) ) || ( it != mIntervals.begin() && std::prev( it )->timePoint >= copy.lower() ) ) && isLess( it->type, type ) ) {
			TRACE( "hypro.datastructures.hiv", "Simple override." );
			it->type = type;
		}
		if ( copy.lower() <= it->timePoint && ( it == mIntervals.begin() || std::prev( it )->timePoint < copy.lower() ) && isLess( it->type, type ) ) {
			if ( copy.lower() > Number( 0 ) ) {
				it = mIntervals.insert( it, endPoint<T, Number>( it->type, copy.lower() ) );
				TRACE( "hypro.datastructures.hiv", "Left split, it now considers: " << it->timePoint << ", type " << it->type );
			}
		}
		if ( copy.upper() < it->timePoint && ( it == mIntervals.begin() || std::prev( it )->timePoint < copy.upper() ) && isLess( it->type, type ) ) {
			it = mIntervals.insert( it, endPoint<T, Number>( type, copy.upper() ) );
			TRACE( "hypro.datastructures.hiv", "Right split." );
			++it;
		}
	}

	TRACE( "hypro.datastructures.hiv", "After plain insertion: " << *this );

	// sanitize
	for ( auto it = mIntervals.begin(); it != mIntervals.end(); ) {
		if ( std::next( it ) != mIntervals.end() && std::next( it )->type == it->type ) {
			it = mIntervals.erase( it );
		} else {
			++it;
		}
	}

	DEBUG( "hypro.datastructures.hiv", "After insertion: " << *this );
	assert( this->isSane() );
}

template <typename T, typename Number>
void HierarchicalIntervalVector<T, Number>::fill( const T& type, Number startingPoint ) {
	// only do something, if the startingPoint lies in the covered interval.
	if ( startingPoint <= mIntervals.back().timePoint ) {
		// store old endpoint, it will be deleted for once.
		auto oldEndpoint = mIntervals.back();
		// iterate until starting point insertion point.
		for ( auto it = mIntervals.begin(); it != mIntervals.end(); ) {
			// proceed.
			if ( it->timePoint < startingPoint ) {
				TRACE( "hypro.datastructures.hiv", "Area not reached, skip." );
				++it;
				continue;
			}

			// at this point we found the correct entry point.
			assert( it->timePoint >= startingPoint );
			assert( it != mIntervals.end() );
			// set new boundary, if not already set
			if ( it->type != type ) {
				it->timePoint = startingPoint;
				++it;
			}

			// override all following ones -> delete.
			while ( it != mIntervals.end() ) {
				it = mIntervals.erase( it );
			}
		}
		// insert new endpoint
		oldEndpoint.type = type;
		mIntervals.emplace_back( oldEndpoint );
		// verify result
		assert( this->hasEntry( carl::Interval<Number>( startingPoint, oldEndpoint.timePoint ), type ) );
	}
}

template <typename T, typename Number>
bool HierarchicalIntervalVector<T, Number>::hasEntry( const T& type ) const {
	assert( this->isSane() );
	for ( const auto& item : mIntervals ) {
		if ( item.type == type )
			return true;
	}
	return false;
}

template <typename T, typename Number>
bool HierarchicalIntervalVector<T, Number>::hasEntry( const carl::Interval<Number>& timeInterval ) const {
	assert( this->isSane() );
	for ( auto t : mOrder ) {
		if ( hasEntry( timeInterval, t ) ) {
			return true;
		}
	}
	return false;
}

template <typename T, typename Number>
bool HierarchicalIntervalVector<T, Number>::hasEntry( const carl::Interval<Number>& timeInterval, const T& type ) const {
	assert( this->isSane() );
	DEBUG( "hypro.datastructures.hiv", "hasEntry: " << timeInterval << ", type " << type );
	return getIntersectionIntervals( timeInterval, type ).size() > 0;
}

template <typename T, typename Number>
bool HierarchicalIntervalVector<T, Number>::intersectsEntry( const carl::Interval<Number>& timeInterval, const T& type ) const {
	assert( this->isSane() );
	DEBUG( "hypro.datastructures.hiv", "This: " << *this << " intersects: " << timeInterval << ", type " << type );

	auto it = mIntervals.begin();
	while ( it != mIntervals.end() ) {
		TRACE( "hypro.datastructures.hiv", "Current it points to " << *it );
		// handle first interval differently
		if ( it == mIntervals.begin() && it->timePoint >= timeInterval.upper() && it->type == type ) {
			TRACE( "hypro.datastructures.hiv", "Begin and match." );
			assert( getIntersectionIntervals( timeInterval, type ).size() > 0 );
			return true;
		} else if ( it == mIntervals.begin() ) {
			++it;
			continue;
		}

		if ( it->timePoint >= timeInterval.lower() && std::prev( it )->timePoint <= timeInterval.upper() && it->type == type ) {
			assert( getIntersectionIntervals( timeInterval, type ).size() > 0 );
			return true;
		}

		if ( it->timePoint > timeInterval.upper() ) {
			assert( getIntersectionIntervals( timeInterval, type ).size() == 0 );
			return false;
		}

		++it;
	}
	TRACE( "hypro.datastructures.hiv", "Not found." );
	assert( getIntersectionIntervals( timeInterval, type ).size() == 0 );
	return false;
}

template <typename T, typename Number>
bool HierarchicalIntervalVector<T, Number>::coversEntry( const carl::Interval<Number>& timeInterval, const T& type ) const {
	DEBUG( "hypro.datastructures.hiv", "This: " << *this << " covers entry: " << timeInterval << ", type " << type );
	assert( this->isSane() );
	auto it = mIntervals.begin();
	while ( it != mIntervals.end() ) {
		TRACE( "hypro.datastructures.hiv", "Current it points to " << *it );
		// handle first interval differently
		if ( it == mIntervals.begin() && it->timePoint >= timeInterval.upper() && it->type == type ) {
			TRACE( "hypro.datastructures.hiv", "Begin and match." );
			return true;
		} else if ( it == mIntervals.begin() ) {
			++it;
			continue;
		}

		// check for containment and matching type - only case in which we return true.
		if ( ( it->timePoint >= timeInterval.upper() && std::prev( it )->timePoint <= timeInterval.lower() ) && it->type == type ) {
			TRACE( "hypro.datastructures.hiv", "Intermediate and match." );
			return true;
		}

		if ( std::prev( it )->timePoint > timeInterval.upper() ) {
			TRACE( "hypro.datastructures.hiv", "Too large." );
			return false;
		}

		++it;
	}
	TRACE( "hypro.datastructures.hiv", "Not found." );
	return false;
}

template <typename T, typename Number>
std::vector<carl::Interval<Number>> HierarchicalIntervalVector<T, Number>::getIntersectionIntervals( const carl::Interval<Number>& timeInterval, const T& type ) const {
	std::vector<carl::Interval<Number>> res;
	DEBUG( "hypro.datastructures.hiv", "In: " << timeInterval << ", type " << type << ", this: " << *this );
	// synthesize intervals which intersect the passed interval
	for ( auto it = mIntervals.begin(); it != mIntervals.end(); ++it ) {
		TRACE( "hypro.datastructures.hiv", "Current interval: " << *it );
		if ( it->timePoint < timeInterval.lower() ) {
			continue;
		}

		// first time point requires special care.
		if ( it == mIntervals.begin() ) {
			TRACE( "hypro.datastructures.hiv", "First interval" );
			if ( timeInterval.lower() <= it->timePoint ) {
				TRACE( "hypro.datastructures.hiv", "Bounds match" );
				if ( it->type == type ) {
					DEBUG( "hypro.datastructures.hiv", "Types match (first interval) - return true." );
					res.emplace_back( carl::Interval<Number>( timeInterval.lower(), std::min( it->timePoint, timeInterval.upper() ) ) );
				}
			}
		}

		if ( it != mIntervals.begin() && carl::set_have_intersection( timeInterval, carl::Interval<Number>( std::prev( it, 1 )->timePoint, it->timePoint ) ) && it->type == type ) {
			DEBUG( "hypro.datastructures.hiv", "Bound and type match - return true." );
			res.emplace_back( carl::set_intersection( carl::Interval<Number>( std::prev( it, 1 )->timePoint, it->timePoint ), timeInterval ) );
		}

		// too far.
		if ( it != mIntervals.begin() && std::prev( it, 1 )->timePoint > timeInterval.upper() ) {
			DEBUG( "hypro.datastructures.hiv", "No matching time interval found - return false." );
			break;
		}
	}
	// assert that all intervals are pairwise disjunct -- similar to sanity check.
#ifndef NDEBUG
	for ( auto it = res.begin(); it != res.end(); ++it ) {
		assert( it == res.begin() || !carl::set_have_intersection( *it, *std::prev( it ) ) );
	}
#endif
	DEBUG( "hypro.datastructures.hiv", "Found " << res.size() << " intersecting intervals." );
	return res;
}

template <typename T, typename Number>
std::vector<carl::Interval<Number>> HierarchicalIntervalVector<T, Number>::getIntersectingIntervals( const carl::Interval<Number>& timeInterval, const T& type ) const {
	std::vector<carl::Interval<Number>> res;
	DEBUG( "hypro.datastructures.hiv", "In: " << timeInterval << ", type " << type << ", this: " << *this );
	// synthesize intervals which intersect the passed interval
	for ( auto it = mIntervals.begin(); it != mIntervals.end(); ++it ) {
		TRACE( "hypro.datastructures.hiv", "Current interval: " << *it );
		if ( it->timePoint < timeInterval.lower() ) {
			continue;
		}

		// first time point requires special care.
		if ( it == mIntervals.begin() ) {
			TRACE( "hypro.datastructures.hiv", "First interval" );
			if ( timeInterval.lower() <= it->timePoint ) {
				TRACE( "hypro.datastructures.hiv", "Bounds match" );
				if ( it->type == type ) {
					DEBUG( "hypro.datastructures.hiv", "Types match (first interval) - return true." );
					res.emplace_back( carl::Interval<Number>( timeInterval.lower(), it->timePoint ) );
				}
			}
		}

		if ( it != mIntervals.begin() && carl::set_have_intersection( timeInterval, carl::Interval<Number>( std::prev( it, 1 )->timePoint, it->timePoint ) ) && it->type == type ) {
			DEBUG( "hypro.datastructures.hiv", "Bound and type match - return true." );
			res.emplace_back( carl::Interval<Number>( std::prev( it, 1 )->timePoint, it->timePoint ) );
		}

		// too far.
		if ( it != mIntervals.begin() && std::prev( it, 1 )->timePoint > timeInterval.upper() ) {
			DEBUG( "hypro.datastructures.hiv", "No matching time interval found - return false." );
			break;
		}
	}
	// assert that all intervals are pairwise disjunct -- similar to sanity check.
#ifndef NDEBUG
	for ( auto it = res.begin(); it != res.end(); ++it ) {
		assert( it == res.begin() || !carl::set_have_intersection( *it, *std::prev( it ) ) );
	}
#endif
	DEBUG( "hypro.datastructures.hiv", "Found " << res.size() << " intersecting intervals." );
	return res;
}

template <typename T, typename Number>
void HierarchicalIntervalVector<T, Number>::merge( const HierarchicalIntervalVector<T, Number>& rhs ) {
	Number prevTimepoint = Number( 0 );
	for ( auto& endPoint : rhs.getIntervals() ) {
		this->insertInterval( endPoint.type, carl::Interval<Number>( prevTimepoint, endPoint.timePoint ) );
		prevTimepoint = endPoint.timePoint;
	}
}

template <typename T, typename Number>
const endPoint<T, Number>& HierarchicalIntervalVector<T, Number>::back() const {
	assert( this->isSane() );
	assert( !mIntervals.empty() );
	return mIntervals.back();
}

template <typename T, typename Number>
std::size_t HierarchicalIntervalVector<T, Number>::size() const {
	assert( this->isSane() );
	return mIntervals.size();
}

template <typename T, typename Number>
bool HierarchicalIntervalVector<T, Number>::empty() const {
	assert( this->isSane() );
	return mIntervals.empty();
}

template <typename T, typename Number>
Number HierarchicalIntervalVector<T, Number>::getTimeHorizon() const {
	assert( !mIntervals.empty() );
	assert( this->isSane() );
	return mIntervals.back().timePoint;
}

template <typename T, typename Number>
bool HierarchicalIntervalVector<T, Number>::isLess( const T& lhs, const T& rhs ) const {
	// TRACE("hypro.datastructures.hiv","Compare " << lhs << " and " << rhs << ", for this: " << *this << " with order ");
	// for(auto i : mOrder){
	//	TRACE("hypro.datastructures.hiv",i);
	// }
	assert( std::find( mOrder.begin(), mOrder.end(), lhs ) != mOrder.end() );
	assert( std::find( mOrder.begin(), mOrder.end(), rhs ) != mOrder.end() );
	for ( std::size_t p = 0; p < mOrder.size(); ++p ) {
		if ( mOrder.at( p ) == rhs ) {
			return false;
		}
		if ( mOrder.at( p ) == lhs ) {
			return true;
		}
	}
	// none of the items is in the order.
	assert( false );
	FATAL( "hypro.datastructures.hiv", "This should not be reachable! Error: the queried items are not in the passed order vector." );
	std::cout << "HierarchicalIntervalVector." << __func__ << ": THIS SHOULD NOT BE REACHABLE!" << std::endl;
	return false;
}

template <typename T, typename Number>
std::size_t HierarchicalIntervalVector<T, Number>::getOrderIndex( const T& type ) const {
	for ( std::size_t p = 0; p < mOrder.size(); ++p ) {
		if ( mOrder.at( p ) == type ) {
			return p;
		}
	}
	return mOrder.size();
}

template <typename T, typename Number>
bool HierarchicalIntervalVector<T, Number>::isSane() const {
	if ( mIntervals.size() <= 1 ) return true;

	for ( auto it = mIntervals.begin(); it != mIntervals.end(); ++it ) {
		if ( it != mIntervals.begin() ) {
			if ( it->type == std::prev( it, 1 )->type ) {
				DEBUG( "hypro.datastructures.timing", "Is not sane: " << *this );
				return false;
			}
		}
	}
	return true;
}

}  // namespace hypro
