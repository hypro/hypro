/**
 * @file GeometricObject.h
 * \defgroup geoState State set representations
 * Most state set representations conform to a unified interface, which is defined in GeometricObject.h.
 * Furthermore some of the representations have additional functionality, which is documented separately.
 */

#pragma once

#define INCL_FROM_GOHEADER true

#include "../config.h"
#include "../flags.h"
#include "../util/adaptions_eigen/adaptions_eigen.h"
#include "../util/logging/Logger.h"
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
 * @tparam     Number  The used number type.
 * \ingroup geoState @{
 */
template <typename Number, typename DerivedShape>
class GeometricObject {
  public:
	typedef Number NumberType;

	/**
	 * @brief      Destroys the object.
	 */
	virtual ~GeometricObject() {}

	/**
	 * @brief      Returns the space dimension of the object.
	 * @return     The dimension.
	 */
	virtual std::size_t dimension() const = 0;

	/**
	 * @brief      Determines, whether the set is empty.
	 * @return     True, if the set is empty, false otherwise.
	 */
	virtual bool empty() const = 0;

	/**
	 * @brief      Computes the set of extreme vertices, whose convex hull is the smallest convex set containing this set.
	 * @return     A set of extreme vertices.
	 */
	virtual std::vector<Point<Number>> vertices( const matrix_t<Number>& = matrix_t<Number>::Zero( 0, 0 ) ) const = 0;

	/**
	 * @brief      Method combining the intersection of the set with a halfspace and a test for emptiness of the resulting set.
	 * @param[in]  rhs   The halfspace. Note that this check is at least as fast as
	 * 			   performing the intersection and testing for emptiness, but in general we encourage to use this method instead.
	 * @return     A pair of a CONTAINMENT type stating whether the resulting set is empty and the resulting set.
	 */
	virtual std::pair<CONTAINMENT, DerivedShape> satisfiesHalfspace( const Halfspace<Number>& rhs ) const = 0;

	/**
	 * @brief      Method combining the intersection of the set with a set of halfspaces and a test for emptiness of the resulting set.
	 * @details    The halfspaces are given as a matrix A and a vector b such that the resulting intersection of the set S with the set
	 * 			   of halfspaces is the set R = \f$ \{ x | x \in S \land A\cdot x \leq b \} \f$. Note that this check is at least as fast as
	 * 			   performing the intersection and testing for emptiness, but in general we encourage to use this method instead.
	 * @param[in]  _mat  The matrix.
	 * @param[in]  _vec  The vector.
	 * @return     A pair of a CONTAINMENT type stating whether the resulting set is empty and the resulting set.
	 */
	virtual std::pair<CONTAINMENT, DerivedShape> satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const = 0;

	/**
	 * @brief      Projects the set on the ordered set of given dimensions.
	 * @param[in]  dimensions  The dimensions.
	 * @return     The resulting set.
	 */
	virtual DerivedShape project( const std::vector<std::size_t>& dimensions ) const = 0;

	/**
	 * @brief Function to set a variable to an interval.
	 * @detail This is a meta-function which consists of projecting out the respective dimension, resulting in a lower-dimensional state set. 
	 * Afterwards the state set is lifted to the original state space, i.e., unconstrained dimensions are added and finally, the interval constraints as given are added.
	 *
	 * @param assignments A map from dimension index to interval.
	 * @return DerivedShape
	 */
	virtual DerivedShape assignIntervals( const std::map<std::size_t, carl::Interval<Number>>& assignments ) const = 0;

	/**
	 * @brief      Applies a linear transformation with the matrix A to the set.
	 * @details    The resulting set R is the result of the linear transformation of the set S with A such that \f$ R = \{ x | x \in A\cdot S \} \f$
	 * @param[in]  A     The matrix.
	 * @return     The resulting set.
	 */
	virtual DerivedShape linearTransformation( const matrix_t<Number>& A ) const = 0;

	/**
	 * @brief      Applies an affine transformation with the matrix A and the translation vector b to the set.
	 * @details    The resulting set R is the result of the affine transformation of the set S with A and b such that \f$ R = \{ x | x \in A\cdot S + b \} \f$
	 * @param[in]  A     The matrix.
	 * @param[in]  b     The vector.
	 * @return     The resulting set.
	 */
	virtual DerivedShape affineTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const = 0;

	/**
	 * @brief      Computes Minkowski's sum of the current set and the passed set.
	 * @param[in]  rhs   The other passed set.
	 * @return     The resulting set.
	 */
	virtual DerivedShape minkowskiSum( const DerivedShape& rhs ) const = 0;
	// virtual DerivedShape intersect( const DerivedShape& rhs ) const = 0;

	/**
	 * @brief      Computes the intersection of the set with the given halfspace.
	 * @param[in]  rhs   The halfspace.
	 * @return     The resulting set.
	 */
	virtual DerivedShape intersectHalfspace( const Halfspace<Number>& rhs ) const = 0;

	/**
	 * @brief      Computes the intersection of the set with a set of halfspaces.
	 * @details    The halfspaces are given as a matrix A and a vector b such that the resulting intersection of the set S with the set
	 * 			   of halfspaces is the set R = \f$ \{ x | x \in S \land A\cdot x \leq b \} \f$.
	 * @param[in]  _mat  The matrix.
	 * @param[in]  _vec  The vector.
	 * @return     The resulting set.
	 */
	virtual DerivedShape intersectHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const = 0;

	/**
	 * @brief      Checks, whether the set contains the passed point.
	 * @param[in]  point  The point.
	 * @return     True, if the point lies inside the set, false otherwise.
	 */
	virtual bool contains( const Point<Number>& point ) const = 0;
	//virtual bool contains( const vector_t<Number>& vec ) const = 0;
	virtual bool contains( const DerivedShape& rhs ) const = 0;

	/**
	 * @brief      Computes the convex hull of the union of the set and the passed set.
	 * @param[in]  rhs   The passed set.
	 * @return     The resulting set.
	 */
	virtual DerivedShape unite( const DerivedShape& rhs ) const = 0;

	/**
	 * @brief      Function called to reduce the representation - implementation is dependent on the actual
	 * representation and might affect number representations as well as reducing the complexity of the set
	 * at the cost of precision - the actual implementation should be settings-dependent.
	 */
	virtual void reduceRepresentation() = 0;

	/**
	 * @brief      Outstream operator.
	 * @param      out   The outstream.
	 * @param[in]  obj   The object.
	 * @return     Reference to the passed outstream.
	 */
	friend std::ostream& operator<<( std::ostream& out, const GeometricObject<Number, DerivedShape>& in ) {
		return out << static_cast<DerivedShape>( in );
	}
};

/** @} */

}  // namespace hypro

#include "conversion/Converter.h"
