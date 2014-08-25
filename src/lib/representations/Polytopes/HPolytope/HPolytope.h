/* 
 * File:   HPolytope.h
 * Author: stefan
 *
 * Created on July 16, 2014, 4:23 PM
 */

#pragma once

#include "util.h"
#include "simplex.h"

namespace hypro
{
    template<typename Number>
    class HPolytope
    {
        public:
            typedef std::vector<polytope::Hyperplane<Number> > HyperplaneVector;
        
        private:
            HyperplaneVector mHPlanes;
            bool mFanSet;
            mutable polytope::Fan<Number> mFan;
            unsigned mDimension;

    public:
        HPolytope();
        HPolytope(const HPolytope& orig);
        HPolytope(const polytope::Hyperplane<Number>& plane);
        HPolytope(unsigned dimension);
        HPolytope(const matrix& A, const vector& b);
        HPolytope(const matrix& A);
        ~HPolytope();
        
        /*
         * Getters and setters
         */
        
        unsigned int dimension() const
	{
            assert(!mHPlanes.empty());
            return mDimension;
	}
        
        const typename polytope::Fan<Number>& fan() const
        {
            if(!mFanSet)
            {
                calculateFan();
            }
            return mFan;
        }
        
        void addConstraint(const polytope::Hyperplane<Number>& plane)
        {
            assert(mDimension == 0 || mDimension == plane.dimension());
            if(mDimension == 0)
            {
                mDimension = plane.dimension();
            }
            return mHPlanes.push_back(plane);
        }
        
        void addConstraints(const typename HyperplaneVector::iterator begin, const typename HyperplaneVector::iterator end)
        {
            assert(mDimension == 0 || mDimension == begin->dimension());
            if(mDimension == 0)
            {
                mDimension = begin->dimension();
            }
            mHPlanes.insert(begin,end);
        }
        
        const HyperplaneVector& vertices() const
        {
            return mHPlanes;
        }
        
        bool hasConstraint(const polytope::Hyperplane<Number>& hplane) const
        {
            return (mHPlanes.find(hplane) != mHPlanes.end());
        }
        
        typename HyperplaneVector::iterator begin()
        {
            return mHPlanes.begin();
        }

        typename HyperplaneVector::const_iterator begin() const
        {
            return mHPlanes.begin();
        }
        
        typename HyperplaneVector::iterator end()
        {
            return mHPlanes.end();
        }

        typename HyperplaneVector::const_iterator end() const
        {
            return mHPlanes.end();
        }
        
        /*
         * Operators
         */
        
        HPolytope<Number>& operator= (const HPolytope<Number>& rhs);
        
    private:
        /*
         * Auxiliary functions
         */
        void calculateFan() const;
        matrix getOptimalDictionary(const matrix A) const;
        std::vector<Point<Number> > vertexEnumeration() const;
    };

} //namespace

#include "HPolytope.tpp"
