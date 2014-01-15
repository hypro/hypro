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

        virtual void linear_transformation(T& result /*, ... */) const = 0;
        virtual void minkowski_sum(T& result, const T& rhs) const = 0;
        virtual bool intersect(T& result, const T& rhs) const = 0;
        virtual void hull(T& result, const T& rhs) const = 0;
        virtual bool contains(const Point<number> point) const = 0;
		virtual void unite(T& result, const T& rhs) const = 0;
        // virtual bool empty() const = 0;
    };
}