/**
 * Abstract representation of a geometric object.
 * All representations of geometric objects should implement this abstract class.
 * @author Benedikt Seidl
 * @version 2013-09-01
 */

#pragma once
#include "../datastructures/Point.h"
#include "../config.h"

namespace hypro
{
    template<class Number>
    class GeometricObject
    {
    public:
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
        bool linearTransformation(GeometricObject<Number>& result/*, matrix transformation*/);
		
		/**
		 * Applies the Minkowskisum of the given stateset and a second stateset.
		 * @param result The resulting stateset.
		 * @param rhs The other righthand-side stateset.
		 * @return True if the operation has been successfully applied.
		 */
        bool minkowskiSum(GeometricObject<Number>& result, const GeometricObject<Number>& rhs);
		
		/**
		 * Intersects the given stateset with a second one.
		 * @param result The resulting stateset of the intersection.
		 * @param rhs The righthand-side stateset.
		 * @return ç
		 */
        bool intersect(GeometricObject<Number>& result, const GeometricObject<Number>& rhs);
		
		/**
		 * Computes the convex hull of the stateset.
		 * @param result The resulting stateset.
		 * @return True if the operation has been successfully applied.
		 */
        bool hull(GeometricObject<Number>& result);
		
		/**
		 * Checks the membership of a point.
		 * @param point The point which is to be checked for membership.
		 * @return True if the point is contained in the stateset.
		 */
        bool contains(const Point<Number>& point);
		
		/**
		 * Computes the union of the given stateset with a second one. Note that
		 * the convex hull is applied, if the representations are not closed under
		 * this computation.
		 * @param result The resulting stateset.
		 * @param rhs The righthand-side stateset.
		 * @return True if the operation has been successfully applied.
		 */
        bool unite(GeometricObject<Number>& result, const GeometricObject<Number>& rhs);
        
        // virtual bool empty() const = 0;
    };
}