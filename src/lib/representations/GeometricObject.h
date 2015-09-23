/**
 * Abstract representation of a geometric object.
 * All representations of geometric objects should implement this abstract class.
 * @author Benedikt Seidl
 * @version 2013-09-01
 */

#pragma once
#include "../datastructures/Point.h"
#include "../config.h"

namespace hypro {
template <class Number>
class GeometricObject {
  public:
	typedef Number type;
	/**
	 * Returns the dimension of this object.
	 *
	 * @return  the dimension
	 */
	unsigned int dimension();

	/**
	 * Applies a linear transformation on the given stateset.
	 * @param result The resulting stateset.
	 * @return True if the operation has been successfully applied.
	 */
	GeometricObject<Number> linearTransformation( const matrix_t<Number>& A, const vector_t<Number>& b );

	/**
	 * Applies the Minkowskisum of the given stateset and a second stateset.
	 * @param result The resulting stateset.
	 * @param rhs The other righthand-side stateset.
	 * @return True if the operation has been successfully applied.
	 */
	GeometricObject<Number> minkowskiSum( const GeometricObject<Number>& rhs );

	/**
	 * Intersects the given stateset with a second one.
	 * @param result The resulting stateset of the intersection.
	 * @param rhs The righthand-side stateset.
	 * @return ç
	 */
	GeometricObject<Number> intersect( const GeometricObject<Number>& rhs );

	/**
	 * Checks the membership of a point.
	 * @param point The point which is to be checked for membership.
	 * @return True if the point is contained in the stateset.
	 */
	bool contains( const Point<Number>& point );

	/**
	 * Computes the union of the given stateset with a second one. Note that
	 * the convex hull is applied, if the representations are not closed under
	 * this computation.
	 * @param result The resulting stateset.
	 * @param rhs The righthand-side stateset.
	 * @return True if the operation has been successfully applied.
	 */
	GeometricObject<Number> unite( const GeometricObject<Number>& rhs );

	// virtual bool empty() const = 0;
};
}