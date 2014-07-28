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
        typedef typename Point<Number>::pointSet vertices;
        /***************************************************************************
	 * Members
	 **************************************************************************/
    protected:
	vertices mVertices;
        unsigned mDimension;
    public:
	/***************************************************************************
	 * Constructors
	 **************************************************************************/

        VPolytope() : 
            mVertices(),
            mDimension(0)
        {}

        VPolytope(const Point<Number>& point)
        {
            mVertices.insert(point);
            mDimension = point.dimension();
        }
        
        VPolytope(const vertices& points)
        {
            mVertices.insert(points.begin(), points.end());
            if(!mVertices.empty())
                mDimension = mVertices.begin()->dimension();
            else
                mDimension = 0;
        }
        
        VPolytope(unsigned dimension)
        {
            mDimension = dimension;
        }
      
        VPolytope(const typename std::vector<Eigen::Matrix<carl::FLOAT_T<Number>,Eigen::Dynamic,1>>& points);
        
        VPolytope(const matrix& A, const vector& b);
        
        VPolytope(const matrix& A);
        
        VPolytope(const VPolytope& orig)
        {
            mVertices.insert(orig.begin(), orig.end());
        }

        virtual ~VPolytope()
        {}
        
        /***************************************************************************
	 * General interface
	 **************************************************************************/
	
	bool linearTransformation(VPolytope& result /*, ... */) const;
	bool minkowskiSum(VPolytope& result, const VPolytope& rhs) const;
	bool intersect(VPolytope& result, const VPolytope& rhs) const;
	bool hull(VPolytope& result) const;
	bool contains(const Point<Number>& point) const;
	bool unite(VPolytope& result, const VPolytope& rhs) const;
	
	void clear();
        
        /***************************************************************************
	 * Getters, Setters, Iterators
	 **************************************************************************/
        
	unsigned int dimension() const
	{
            assert(!mVertices.empty());
            return mVertices.begin()->dimension();
	}
        
        std::pair<typename vertices::iterator, bool> insert(const Point<Number>& i)
        {
            assert(mDimension == 0 || mDimension == i.dimension());
            return mVertices.insert(i);
        }
        
        void insert(const typename vertices::iterator begin, const typename vertices::iterator end)
        {
            assert(mDimension == 0 || mDimension == begin->dimension());
            mVertices.insert(begin,end);
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