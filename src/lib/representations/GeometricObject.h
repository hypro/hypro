/**
 * Abstract representation of a geometric object.
 * All representations of geometric objects should implement this abstract class.
 * @author Benedikt Seidl
 * @version 2013-09-01
 */

#pragma once
#include "../datastructures/Point.h"

namespace hypro
{
    template<class T, class number>
    class GeometricObject
    {
    public:
        virtual unsigned int get_dimension() const = 0;
		
		/**
		 * Applies a linear transformation on the given stateset.
		 * @param result The resulting stateset.
		 * @return True if the operation has been successfully applied.
		 */
        virtual bool linear_transformation(T& result /*, ... */) const = 0;
		
		/**
		 * Applies the Minkowskisum of the given stateset and a second stateset.
		 * @param result The resulting stateset.
		 * @param rhs The other righthand-side stateset.
		 * @return True if the operation has been successfully applied.
		 */
        virtual bool minkowski_sum(T& result, const T& rhs) const = 0;
		
		/**
		 * Intersects the given stateset with a second one.
		 * @param result The resulting stateset of the intersection.
		 * @param rhs The righthand-side stateset.
		 * @return ç
		 */
        virtual bool intersect(T& result, const T& rhs) const = 0;
		
		/**
		 * Computes the convex hull of the stateset.
		 * @param result The resulting stateset.
		 * @return * @return True if the operation has been successfully applied.
		 */
        virtual bool hull(T& result) const = 0;
		
		/**
		 * Checks the membership of a point.
		 * @param point The point which is to be checked for membership.
		 * @return True if the point is contained in the stateset.
		 */
        virtual bool contains(const Point<number>& point) const = 0;
		
		/**
		 * Computes the union of the given stateset with a second one. Note that
		 * the convex hull is applied, if the representations are not closed under
		 * this computation.
		 * @param result The resulting stateset.
		 * @param rhs The righthand-side stateset.
		 * @return True if the operation has been successfully applied.
		 */
		virtual bool unite(T& result, const T& rhs) const = 0;
        // virtual bool empty() const = 0;
    };
}