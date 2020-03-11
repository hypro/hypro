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
template <typename Number>
class GeometricObjectBase {
  protected:
	/**
	 * @brief
	 *
	 */
	~GeometricObjectBase() {}

	/**
	 * @brief      Determines, whether the set is empty.
	 * @return     True, if the set is empty, false otherwise.
	 */
	bool empty() const;
};

/** @} */

}  // namespace hypro

#include "conversion/Converter.h"

