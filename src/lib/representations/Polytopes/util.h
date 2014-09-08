/* 
 * File:   util.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since   2014-08-11
 * @version 2014-08-22
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
        vector		        mNormal;
        carl::FLOAT_T<Number>   mScalar;
        unsigned                mDimension;
        
        public:
        Hyperplane() :
        mNormal(),
        mScalar(),
        mDimension()
        {}
        
        ~Hyperplane()
        {}
        
        Hyperplane(const Hyperplane<Number>& _orig) :
        mNormal(_orig.mNormal),
        mScalar(_orig.mScalar),
        mDimension(_orig.mDimension)
        {}
        
        /**
         * Constructor from a Point - shpuld not be used.
         * @param vector
         * @param _off
         */
        Hyperplane(const Point<Number>& _vector, const carl::FLOAT_T<Number>& _off)
        {
            mNormal = vector(_vector.dimension());
            unsigned pos = 0;
            for(auto& coordinate : _vector)
            {
                mNormal(pos) = coordinate.second;
                ++pos;
            }
            mScalar = _off;
            mDimension = pos;
        }
        
        Hyperplane(const Point<Number>& _vector, const Number& _off)
        {
            mNormal = vector(_vector.dimension());
            unsigned pos = 0;
            for(auto& coordinate : _vector)
            {
                mNormal(pos) = coordinate.second;
                ++pos;
            }
            mScalar = carl::FLOAT_T<Number>(_off);
            mDimension = pos;
        }
        
        Hyperplane(std::initializer_list<Number> _coordinates, const Number& _off)
        {
            mNormal = vector(_coordinates.size());
            unsigned pos = 0;
            for(auto& coordinate : _coordinates)
            {
                mNormal(pos) = coordinate;
                ++pos;
            }
            mScalar = carl::FLOAT_T<Number>(_off);
            mDimension = pos;
        }
        
        Hyperplane(std::initializer_list<Number> _coordinates, const carl::FLOAT_T<Number>& _off)
        {
            mNormal = vector(_coordinates.size());
            unsigned pos = 0;
            for(auto& coordinate : _coordinates)
            {
                mNormal(pos) = coordinate;
                ++pos;
            }
            mScalar = _off;
            mDimension = pos;
        }
        
        Hyperplane(const vector& _vector, const Number& _off) :
        mNormal(_vector),
        mScalar(carl::FLOAT_T<Number>(_off)),
        mDimension(_vector.rows())
        {}
        
        Hyperplane(const vector& _vector, const carl::FLOAT_T<Number>& _off) :
        mNormal(_vector),
        mScalar(_off),
        mDimension(_vector.rows())
        {}
        
        Hyperplane(const vector& _vec, const std::vector<vector>& _vectorSet)
        {
        	//here: hyperplane given in parameterform is converted to normalform
        	assert(_vectorSet.size() == 2);
        	//the normal vector of the hyperplane is the cross product of both directions
        	vector vec1 = _vectorSet.at(0);
        	vector vec2 = _vectorSet.at(1);
        	//TODO .cross() doesnt work
        	//mNormal = vec1.cross(vec2);

        	//the scalar is just the scalarproduct of the normal vector & a point in the hyperplane
        	mScalar = mNormal.dot(_vec);

        	mDimension = _vec.rows();
        }

        unsigned dimension() const
        {
            return mNormal.rows();
        }
        
        vector normal() const
        {
            return mNormal;
        }
        
        void setNormal(const vector& _normal)
        {
            mNormal = _normal;
            mDimension = _normal.rows();
        }
        
        Number offset() const
        {
            return mScalar.value();
        }
        
        void setOffset(Number _offset)
        {
            mScalar = carl::FLOAT_T<Number>(_offset);
        }
        
        void setOffset(const carl::FLOAT_T<Number>& _offset)
        {
            mScalar = _offset;
        }
        
        bool intersection(carl::FLOAT_T<Number>& _result, const vector& _vector) const
        {
        	bool intersect = false;
        	carl::FLOAT_T<Number> factor;
            carl::FLOAT_T<Number> dotProduct = (mNormal.dot(_vector));
            if (dotProduct != 0) {
            	intersect = true;
            	factor = mScalar / dotProduct;
            }
            _result = factor;
            //note: to get the intersection point -> _vector *= factor;
            return intersect;
        }
        
        bool intersection(Number _result, const vector& _vector) const
        {
        	bool intersect = false;
        	carl::FLOAT_T<Number> factor;
            carl::FLOAT_T<Number> dotProduct = (mNormal.dot(_vector));
            if (dotProduct != 0) {
            	intersect = true;
            	factor = mScalar / dotProduct;
            }
            _result = factor.value();
            //note: to get the intersection point -> _vector *= factor;
            return intersect;
        }
        
        bool intersection(carl::FLOAT_T<Number>& _result, const Point<Number>& _vector) const
        {
            // TODO
        }
        
        private:
            const carl::FLOAT_T<Number>& internalOffset() const
            {
                return mScalar;
            }
    };
    
    template<typename Number>
    std::ostream& operator<<(std::ostream& _lhs, const hypro::polytope::Hyperplane<Number>& _rhs)
    {
        _lhs << "( " << _rhs.normal() << ", " << carl::FLOAT_T<Number>(_rhs.offset()) << " )";
        return _lhs;
    }

    template<typename Number>
    class Cone 
    {
        public:
            typedef std::vector<const Hyperplane<Number>* > planes;
        private:
            planes     mPlanes;
            unsigned    mDimension;
            Point<Number> mOrigin;
        public:
            Cone() :
            mPlanes(),
            mDimension(),
            mOrigin()
            {}
            
            ~Cone()
            {
                mPlanes.clear();
            }
            
            Cone(const Cone& _orig) :
            mPlanes(_orig.get()),
            mDimension(_orig.dimension()),
            mOrigin(_orig.mOrigin)
            {}
            
            Cone(unsigned _dimension) :
            mPlanes(_dimension),
            mDimension(),
            mOrigin()
            {
                assert(mPlanes.max_size() == _dimension);
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
            
            const Point<Number>& origin() const
			{
            	return mOrigin;
			}

            void setOrigin(const Point<Number>& _origin)
            {
            	mOrigin = _origin;
            	mDimension = _origin.dimension();
            }

            const Hyperplane<Number>* get(unsigned _index) const
            {
                assert(_index < mPlanes.size());
                return mPlanes.at(_index);
            }
            
            const Hyperplane<Number>* get(typename planes::const_iterator _pos) const
            {
                return *_pos;
            }
            
            typename planes::const_iterator begin()
            {
                return mPlanes.begin();
            }
            
            typename planes::const_iterator end()
            {
                return mPlanes.end();
            }
            
            void add(const Hyperplane<Number>* _plane)
            {
                mPlanes.push_back(_plane);
                mDimension = mDimension < _plane->dimension() ? _plane->dimension() : mDimension;
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
            
            bool contains(const Point<Number>* _vector) const
            {
            	// Todo
                return false;
            }
            
            Cone<Number> operator=(const Cone<Number>& _rhs)
            {
                if( this != &_rhs )
                {
                    Cone<Number> tmp(_rhs);
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
            
            Fan(const Fan& _orig) :
            mCones(_orig.get()),
            mDimension(_orig.dimension())
            {}
            
            /*
             * Getters & setters
             */
            
            const cones& get() const
            {
                return mCones;
            }
            
            const Cone<Number>* get(unsigned _index) const
            {
                assert(_index < mCones.size());
                return mCones.at(_index);
            }
            
            unsigned dimension() const
            {
                return mDimension;
            }
            
            unsigned size() const
            {
                return mCones.size();
            }
            
            void add(const Cone<Number>* _cone)
            {
                mCones.push_back(_cone);
                mDimension = mDimension < _cone->dimension() ? _cone->dimension() : mDimension;
            }
            
            const Cone<Number>* containingCone(const Point<Number>& _vector) const
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
            
            Fan<Number> operator=(const Fan<Number>& _rhs)
            {
               /* if( this != &rhs )
                {
                    Fan<Number> tmp(rhs);
                    std::swap(*this,tmp);
                }
                return *this;
                */
            	this->mCones = _rhs.get();
            	this->mDimension = _rhs.dimension();
            	return *this;
            }
    };
    
}
}

