/* 
 * The class implementing the vertex representation of a convex polytope.
 * @file   VPolytope.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since   2014-02-25
 * @version 2014-02-25
 */
#pragma once

#include "../../datastructures/Point.h"
#include "../GeometricObject.h"
#include <carl/core/Variable.h>
#include <set>
#include <cassert>

namespace hypro
{

template<typename Number>
class VPolytope : hypro::GeometricObject<Number>
{
    public: 
        typedef std::set<Point<Number> > vertices;
        /***************************************************************************
	 * Members
	 **************************************************************************/
    protected:
	vertices mVertices;
    public:
	/***************************************************************************
	 * Constructors
	 **************************************************************************/

        VPolytope() : mVertices()
        {}

        VPolytope(const Point<Number>& point)
        {
            mVertices.insert(point);
        }
        
        VPolytope(const vertices& points)
        {
            mVertices.insert(points.begin(), points.end());
        }
        
        VPolytope(const VPolytope& orig)
        {
            mVertices.insert(orig.begin(), orig.end());
        }

        ~VPolytope()
        {}
        
        /***************************************************************************
	 * General interface
	 **************************************************************************/
	
	unsigned int dimension() const
	{
            assert(!mVertices.empty());
            return mVertices.begin()->size();
	}
	
	bool linear_transformation(VPolytope& result /*, ... */) const;
	bool minkowski_sum(VPolytope& result, const VPolytope& rhs) const;
	bool intersect(VPolytope& result, const VPolytope& rhs) const;
	bool hull(VPolytope& result) const;
	bool contains(const Point<Number>& point) const;
	bool unite(VPolytope& result, const VPolytope& rhs) const;
	
	void clear();
        
        /***************************************************************************
	 * Getters, Setters, Iterators
	 **************************************************************************/
        
        std::pair<typename vertices::iterator, bool> insert(const Point<Number>& i)
        {
            return mVertices.insert(i);
        }
        
        typename vertices::iterator begin()
        {
            return mVertices.begin();
        }

        typename vertices::const_iterator begin() const
        {
            return mVertices.begin();
        }
        
        typename vertices::iterator end()
        {
            return mVertices.end();
        }

        typename vertices::const_iterator end() const
        {
            return mVertices.end();
        }
};

}//namespace

#include "VPolytope.tpp"