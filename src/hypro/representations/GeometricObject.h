/**
 * @file GeometricObject.h
 * \defgroup geoState State set representations
 * This is the description.
 */

#pragma once

#define INCL_FROM_GOHEADER true

#include "types.h"
#include "../flags.h"
#include "../config.h"
#include "../util/adaptions_eigen/adaptions_eigen.h"
#include "../util/logging/Logger.h"

namespace hypro {

/**
 * @brief      Forward declaration of class Point.
 * @tparam     Number  The used number type.
 */
template<typename Number>
class Point;

/**
 * @brief      Forward declaration of class Halfspace.
 * @tparam     Number  The used number type.
 */
template<typename Number>
class Halfspace;

/**
 * @brief      Forward declaration of class Location.
 * @tparam     Number  The used number type.
 */
template<typename Number>
class Location;

/**
 * @brief      Purely virtual class defining a common interface for geometric objects.
 * @tparam     Number  The used number type.
 * \ingroup geoState @{
 */
template<typename Number, typename DerivedShape>
class GeometricObject {

public:
	/**
	 * @brief      Destroys the object.
	 */
	virtual ~GeometricObject(){}

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
	virtual std::vector<Point<Number>> vertices( const Location<Number>* = nullptr ) const = 0;

	/**
	 * @brief      Method combining the intersection of the set with a halfspace and a test for emptiness of the resulting set.
	 * @param[in]  rhs   The halfspace. Note that this check is at least as fast as
	 * 			   performing the intersection and testing for emptiness, but in general we encourage to use this method instead.
	 * @return     A pair of a Boolean stating whether the resulting set is empty and the resulting set.
	 */
	virtual std::pair<bool, DerivedShape> satisfiesHalfspace( const Halfspace<Number>& rhs ) const = 0;

	/**
	 * @brief      Method combining the intersection of the set with a set of halfspaces and a test for emptiness of the resulting set.
	 * @details    The halfspaces are given as a matrix A and a vector b such that the resulting intersection of the set S with the set
	 * 			   of halfspaces is the set R = \f$ \{ x | x \in S \land A\cdot x \leq b \} \f$. Note that this check is at least as fast as
	 * 			   performing the intersection and testing for emptiness, but in general we encourage to use this method instead.
	 * @param[in]  _mat  The matrix.
	 * @param[in]  _vec  The vector.
	 * @return     A pair of a Boolean stating whether the resulting set is empty and the resulting set.
	 */
	virtual std::pair<bool, DerivedShape> satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const = 0;

	/**
	 * @brief      Projects the set on the ordered set of given dimensions.
	 * @param[in]  dimensions  The dimensions.
	 * @return     The resulting set.
	 */
	virtual DerivedShape project(const std::vector<unsigned>& dimensions) const = 0;

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
	//virtual bool contains( const DerivedShape& rhs ) const = 0;

	/**
	 * @brief      Computes the convex hull of the union of the set and the passed set.
	 * @param[in]  rhs   The passed set.
	 * @return     The resulting set.
	 */
	virtual DerivedShape unite( const DerivedShape& rhs ) const = 0;

};

/** @} */

} // namespace hypro

#include "conversion/Converter.h"
