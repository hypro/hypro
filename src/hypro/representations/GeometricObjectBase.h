/**
 * @file GeometricObjectBase.h
 * \defgroup geoState State set representations
 * Most state set representations conform to a unified interface, which is defined in GeometricObjectBase.h.
 * Furthermore some of the representations have additional functionality, which is documented separately.
 */

#pragma once

#define INCL_FROM_GOHEADER true

#include "../config.h"
#include "../flags.h"
#include "types.h"

#ifdef HYPRO_STATISTICS
#include "../util/statistics/statistics.h"
#endif

namespace hypro {

template <typename Number>
class Point;

template <typename Number>
class Halfspace;

template <typename Number>
class Location;

/**
 * @brief      Purely virtual class defining a common interface for geometric objects.
 * \ingroup geoState @{
 */

class GeometricObjectBase {
  protected:
	mutable SETSTATE mEmptyState = SETSTATE::UNKNOWN;

	GeometricObjectBase() = default;
	GeometricObjectBase( const GeometricObjectBase& in ) = default;
	GeometricObjectBase( GeometricObjectBase&& in ) = default;

	GeometricObjectBase& operator=( const GeometricObjectBase& in ) = default;
	GeometricObjectBase& operator=( GeometricObjectBase&& in ) = default;

	GeometricObjectBase( SETSTATE state )
		: mEmptyState( state ) {}

	/**
	 * @brief      Determines, whether the set is empty.
	 * @return     True, if the set is empty, false otherwise.
	 */
	SETSTATE getEmptyState() const { return mEmptyState; }

	/**
	 * @brief Set the Empty State member - only to be used if you know what you are doing.
	 * @param state The state the member is set to.
	 */
	void setEmptyState( SETSTATE state ) { mEmptyState = state; }
};

/** @} */

}  // namespace hypro

#include "conversion/Converter.h"
