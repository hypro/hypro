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
        
    };
    

    template<typename Number>
    class Cone 
    {
        public:
            typedef std::vector<const Hyperplane<Number>* > planes;
        private:
            planes     mVectors;
            unsigned    mDimension;
        public:
            Cone() :
            mVectors(),
            mDimension()
            {}
            
            ~Cone()
            {
                mVectors.clear();
            }
            
            Cone(const Cone& orig) :
            mVectors(orig.get()),
            mDimension(orig.dimension())
            {}
            
            Cone(unsigned dimension) :
            mVectors(dimension),
            mDimension()
            {
                assert(mVectors.max_size() == dimension);
            }
            
            /*
             * Getters & setters
             */
            
            const planes& get() const
            {
                return mVectors;
            }
            
            unsigned dimension() const
            {
                return mDimension;
            }
            
            unsigned size() const
            {
                return mVectors.size();
            }
            
            const Hyperplane<Number>* get(unsigned index) const
            {
                assert(index < mVectors.size());
                return mVectors.at(index);
            }
            
            const Hyperplane<Number>* get(typename planes::const_iterator pos) const
            {
                return *pos;
            }
            
            typename planes::const_iterator begin()
            {
                return mVectors.begin();
            }
            
            typename planes::const_iterator end()
            {
                return mVectors.end();
            }
            
            void add(const Hyperplane<Number>* plane)
            {
                mVectors.push_back(plane);
                mDimension = mDimension < plane->dimension() ? plane->dimension : mDimension;
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
                unsigned numVectors = vectors.size();
                unsigned elements = this->mDimension * numVectors;
                
                glp_add_cols(cones, numVectors);
                glp_add_rows(cones, this->mDimension);
                
                int ia[elements];
                int ja[elements];
                double ar[elements];
                unsigned pos = 1;
                
                for(unsigned i = 1; i <= this->mDimension; ++i)
                {
                    for(unsigned j = 1; j <= numVectors; ++j)
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

