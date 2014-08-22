/* 
 * File:   util.h
 * Author: stefan
 *
 * Created on August 11, 2014, 4:15 PM
 */

#pragma once

#include <cassert>
#include "../../datastructures/Point.h"
#include <glpk.h>

namespace hypro
{
namespace polytope
{
    template<typename Number>
    class Hyperplane
    {
        private:
        Point<Number>   mNormal;
        Number          mScalar;
        unsigned        mDimension;
        
        public:
        Hyperplane() :
        mNormal(),
        mScalar(),
        mDimension()
        {}
        
        ~Hyperplane()
        {}
        
        Hyperplane(const Hyperplane<Number>& orig) :
        mNormal(orig.mNormal),
        mScalar(orig.mScalar),
        mDimension(orig.mDimension)
        {}
        
        Hyperplane(const Point<Number>& vector, const Number& scalar) :
        mNormal(vector),
        mScalar(scalar),
        mDimension(vector.dimension())
        {}
        
        unsigned dimension() const
        {
            return mNormal.dimension();
        }
        
        Point<Number> normal() const
        {
            return mNormal;
        }
        
        Number offset() const
        {
            return mScalar;
        }
        
    };
    

    template<typename Number>
    class Cone 
    {
        public:
            typedef std::vector<const Hyperplane<Number>* > planes;
        private:
            planes     mPlanes;
            unsigned    mDimension;
        public:
            Cone() :
            mPlanes(),
            mDimension()
            {}
            
            ~Cone()
            {
                mPlanes.clear();
            }
            
            Cone(const Cone& orig) :
            mPlanes(orig.get()),
            mDimension(orig.dimension())
            {}
            
            Cone(unsigned dimension) :
            mPlanes(dimension),
            mDimension()
            {
                assert(mPlanes.max_size() == dimension);
            }
            
            /*
             * Getters & setters
             */
            
            const planes& get() const
            {
                return mPlanes;
            }
            
            unsigned dimension() const
            {
                return mDimension;
            }
            
            unsigned size() const
            {
                return mPlanes.size();
            }
            
            const Hyperplane<Number>* get(unsigned index) const
            {
                assert(index < mPlanes.size());
                return mPlanes.at(index);
            }
            
            const Hyperplane<Number>* get(typename planes::const_iterator pos) const
            {
                return *pos;
            }
            
            typename planes::const_iterator begin()
            {
                return mPlanes.begin();
            }
            
            typename planes::const_iterator end()
            {
                return mPlanes.end();
            }
            
            void add(const Hyperplane<Number>* plane)
            {
                mPlanes.push_back(plane);
                mDimension = mDimension < plane->dimension() ? plane->dimension : mDimension;
            }
            
            Point<Number> getUnitAverageVector() const
            {
                assert(!mPlanes.empty());
                Point<Number> result;
                unsigned numberPlanes = mPlanes.size();
                for(auto& plane : mPlanes)
                {
                    result += (plane->normal()/numberPlanes);
                }
                return result;
            }
            
            bool contains(const Point<Number>* vector) const
            {
            	// Todo
                return false;
            }
            
            Cone<Number> operator=(const Cone<Number>& rhs)
            {
                if( this != &rhs )
                {
                    Cone<Number> tmp(rhs);
                    std::swap(*this,tmp);
                }
                return *this;
            }
    };
    
    template<typename Number>
    class Fan 
    {
        public:
            typedef std::vector<const Cone<Number>* > cones;
        private:
            cones       mCones;
            unsigned    mDimension;
        public:
            
            Fan() :
            mCones(),
            mDimension()
            {}
            
            ~Fan()
            {
                mCones.clear();
            }
            
            Fan(const Fan& orig) :
            mCones(orig.get()),
            mDimension(orig.dimension())
            {}
            
            /*
             * Getters & setters
             */
            
            const cones& get() const
            {
                return mCones;
            }
            
            const Cone<Number>* get(unsigned index) const
            {
                assert(index < mCones.size());
                return mCones.at(index);
            }
            
            unsigned dimension() const
            {
                return mDimension;
            }
            
            unsigned size() const
            {
                return mCones.size();
            }
            
            void add(const Cone<Number>* cone)
            {
                mCones.push_back(cone);
                mDimension = mDimension < cone->dimension() ? cone->dimension() : mDimension;
            }
            
            const Cone<Number>* containingCone(const Point<Number>& vector) const
            {
                // set up glpk
                glp_prob *cones;
                cones = glp_create_prob();
                glp_set_obj_dir(cones, GLP_MAX);
                
                typename polytope::Cone<Number>::vectors vectors;
                for(auto& cone : mCones)
                {
                    vectors.insert(vectors.end(), cone.begin(), cone.end());
                }             
                unsigned numPlanes = vectors.size();
                unsigned elements = this->mDimension * numPlanes;
                
                glp_add_cols(cones, numPlanes);
                glp_add_rows(cones, this->mDimension);
                
                int ia[elements];
                int ja[elements];
                double ar[elements];
                unsigned pos = 1;
                
                for(unsigned i = 1; i <= this->mDimension; ++i)
                {
                    for(unsigned j = 1; j <= numPlanes; ++j)
                    {
                        ia[pos] = i;
                        ja[pos] = j;
                        ar[pos] = vectors.at(j).at(i);
                        ++pos;
                    }
                }
                assert(pos <= elements);
                
                glp_load_matrix(cones, elements, ia, ja, ar);
                glp_simplex(cones, NULL);
                
                // TODO output & result interpretation
                
                glp_delete_prob(cones);
            }
            
            Fan<Number> operator=(const Fan<Number>& rhs)
            {
                if( this != &rhs )
                {
                    Fan<Number> tmp(rhs);
                    std::swap(*this,tmp);
                }
                return *this;
            }
    };
    
}
}

