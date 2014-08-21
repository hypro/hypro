/* 
 * The class implementing the vertex representation of a convex polytope.
 * @file   VPolytope.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since   2014-02-25
 * @version 2014-02-25
 */
#pragma once

#include "../util.h"
#include "../../GeometricObject.h"
#include <carl/core/Variable.h>
#include <eigen3/Eigen/Geometry>
#include <set>
#include <cassert>

namespace hypro
{

template<typename Number>
class VPolytope : hypro::GeometricObject<Number>
{
    public: 
        typedef typename Point<Number>::pointSet verticeSet;
        typedef typename polytope::Cone<Number> Cone;
        typedef typename polytope::Fan<Number> Fan;
        /***************************************************************************
	 * Members
	 **************************************************************************/
    protected:
	verticeSet                          mVertices;
        unsigned                            mDimension;
        mutable Fan                                 mFan;
        bool                                mFanSet;
        bool                                mHasNoInternalPoints;
        
    public:
	/***************************************************************************
	 * Constructors
	 **************************************************************************/

        VPolytope() : 
            mVertices(),
            mDimension(0),
            mFan(),
            mFanSet(false),
            mHasNoInternalPoints(true)
        {}

        VPolytope(const Point<Number>& point)
        {
            mVertices.insert(point);
            mDimension = point.dimension();
            mFan = polytope::Fan<Number>();
            mFanSet = false;
            mHasNoInternalPoints = true;
        }
        
        VPolytope(const verticeSet& points)
        {
            mVertices.insert(points.begin(), points.end());
            if(!mVertices.empty())
                mDimension = mVertices.begin()->dimension();
            else
                mDimension = 0;
            mFan = polytope::Fan<Number>();
            mFanSet = false;
            mHasNoInternalPoints = true;
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
            mDimension = orig.dimension();
            mFan = orig.fan();
            mFanSet = true; // TODO: Include getter fpr this
            mHasNoInternalPoints = true; // TODO: Include getter fpr this
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
        
        const typename polytope::Fan<Number>& fan() const
        {
            if(!mFanSet)
            {
                calculateFan();
            }
            return mFan;
        }
        
        std::pair<typename verticeSet::iterator, bool> insert(const Point<Number>& i)
        {
            assert(mDimension == 0 || mDimension == i.dimension());
            return mVertices.insert(i);
        }
        
        void insert(const typename verticeSet::iterator begin, const typename verticeSet::iterator end)
        {
            assert(mDimension == 0 || mDimension == begin->dimension());
            mVertices.insert(begin,end);
        }
        
        const verticeSet& vertices() const
        {
            return mVertices;
        }
        
        bool hasVertex(const Point<Number>& vertex) const
        {
            return (mVertices.find(vertex) != mVertices.end());
        }
        
        typename verticeSet::iterator begin()
        {
            return mVertices.begin();
        }

        typename verticeSet::const_iterator begin() const
        {
            return mVertices.begin();
        }
        
        typename verticeSet::iterator end()
        {
            return mVertices.end();
        }

        typename verticeSet::const_iterator end() const
        {
            return mVertices.end();
        }
        
        private:
        /***************************************************************************
	 * Auxiliary functions
	 **************************************************************************/
        const Fan& calculateFan() const;
        const Cone& calculateCone(const Point<Number>& vertex);
        
        /***************************************************************************
	 * Operators
	 **************************************************************************/
        public:
        VPolytope<Number>& operator=(const VPolytope<Number>& rhs);
        bool operator==(const VPolytope<Number>& rhs);

};



}//namespace

#include "VPolytope.tpp"
