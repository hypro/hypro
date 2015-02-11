/* 
 * File:   util.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since   2014-08-11
 * @version 2014-08-22
 */

#pragma once

#include <cassert>
#include <glpk.h>

#include "../../datastructures/Point.h"

namespace hypro
{
namespace polytope
{
    template<typename Number>
    class Hyperplane
    {
        private:
        vector_t<Number>        mNormal;
        Number   mScalar;
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
        
        Hyperplane(const Point<Number>& _vector, const Number& _off)
        {
            mNormal = vector_t<Number>(_vector.dimension());
            unsigned pos = 0;
            for(auto& coordinate : _vector)
            {
                mNormal(pos) = coordinate.second;
                ++pos;
            }
            mScalar = _off;
            mDimension = pos;
        }
        
        Hyperplane(std::initializer_list<Number> _coordinates, const Number& _off)
        {
            mNormal = vector_t<Number>(_coordinates.size());
            unsigned pos = 0;
            for(auto& coordinate : _coordinates)
            {
                mNormal(pos) = coordinate;
                ++pos;
            }
            mScalar = _off;
            mDimension = pos;
        }
        
        Hyperplane(const vector_t<Number>& _vector, const Number& _off) :
        mNormal(_vector),
        mScalar(_off),
        mDimension(_vector.rows())
        {}
        
        Hyperplane(const vector_t<Number>& _vec, const std::vector<vector_t<Number>>& _vectorSet)
        {
        	//here: hyperplane given in parameterform is converted to normalform
        	//the normal vector of the hyperplane is computed by solving a system of equations
        	mNormal = computePlaneNormal(_vectorSet);
#ifdef fukuda_DEBUG
        	std::cout<< "computed Plane Normal: " << mNormal << std::endl;
#endif

        	//the scalar is just the scalar product of the normal vector & a point in the hyperplane
        	mScalar = mNormal.dot(_vec);
#ifdef fukuda_DEBUG
        	std::cout<< "computed Offset: " << mScalar << std::endl;
#endif

        	mDimension = _vec.rows();
        }

        unsigned dimension() const
        {
            return mNormal.rows();
        }
        
        vector_t<Number> normal() const
        {
            return mNormal;
        }
        
        void setNormal(const vector_t<Number>& _normal)
        {
            mNormal = _normal;
            mDimension = _normal.rows();
        }
        
        Number offset() const
        {
            return mScalar;
        }
        
        void setOffset(Number _offset)
        {
            mScalar = _offset;
        }
		
		Number signedDistance(const vector_t<Number>& _point) const {
			return (_point.dot(mNormal) - mScalar);
		}
        
        bool intersection(Number& _result, const vector_t<Number>& _vector) const
        {
        	bool intersect = false;
        	Number factor = 0;
#ifdef fukuda_DEBUG
        	std::cout << "mNormal: " << mNormal << std::endl;
#endif
            Number dotProduct = (mNormal.dot(_vector));
#ifdef fukuda_DEBUG
        	std::cout << "dotProduct: " << dotProduct << std::endl;
#endif
            if (dotProduct != 0) {
            	intersect = true;
            	factor = mScalar / dotProduct;
            }
            _result = factor;
            //note: to get the intersection point -> _vector *= factor;
            return intersect;
        }
        
        bool intersection(Number& _result, const Point<Number>& _vector) const
        {
            // TODO
        	return false;
        }
        
        private:
            const Number& internalOffset() const
            {
                return mScalar;
            }

           /**
            * @author: Chris K
            * Method to compute the normal of a plane based on two direction vectors
            * simply computing the cross product does not work since the dimension is not necessarily 3
            */
            vector_t<Number> computePlaneNormal(const std::vector<vector_t<Number>>& _edgeSet) {

            	/*
        		 * Setup LP with GLPK
        		 */
        		glp_prob *normal;
        		normal = glp_create_prob();
        		glp_set_obj_dir(normal, GLP_MAX);

        		//we have one row for each edge in our set
        		glp_add_rows(normal, _edgeSet.size());

        		//constraints of auxiliary variables (bounds for rows)
        		for (unsigned i=1; i <= _edgeSet.size(); ++i) {
        			glp_set_row_bnds(normal, i, GLP_FX, 0.0, 0.0);
        		}

        		//each column corresponds to one dimension of a vector in our edgeSet
        		//TODO consider p1 & p2 of different dimensions? (-> two edge sets)
        		glp_add_cols(normal, _edgeSet.at(0).rows());

        		//coefficients of objective function:
        		for (unsigned i=1; i <= _edgeSet.at(0).rows(); ++i) {
        			glp_set_obj_coef(normal, i, 1.0);
        		}

        		//constraints for structural variables
        		for (unsigned i=1; i<= _edgeSet.at(0).rows(); ++i) {
        			glp_set_col_bnds(normal, i, GLP_DB, -1.0, 1.0);
        		}

        		//setup matrix coefficients
        		unsigned elements = (_edgeSet.size()) * (_edgeSet.at(0).rows());
        		int ia[1+elements];
        		int ja[1+elements];
        		double ar[1+elements];
        		unsigned pos = 1;

                //to prevent bugs
                ia[0] = 0;
                ja[0] = 0;
                ar[0] = 0;

        		for (unsigned i=1; i <= _edgeSet.size(); ++i) {

        			for (unsigned j=1; j <= _edgeSet.at(0).rows(); ++j) {
        				ia[pos] = i;
        				ja[pos] = j;
        				vector_t<Number> tmpVec = _edgeSet.at(i-1);
        				ar[pos] = tmpVec(j-1);
#ifdef fukuda_DEBUG
        				std::cout << "Coeff. at (" << i << "," << j << "): " << ar[pos] << std::endl;
#endif
        				++pos;
        			}
        		}
        		assert(pos-1 <= elements);

        		glp_load_matrix(normal, elements, ia, ja, ar);
        		glp_simplex(normal, NULL);

        		vector_t<Number> result = vector_t<Number>(_edgeSet.at(0).rows(),1);

        		//fill the result vector based on the optimal solution returned by the LP
        		for (unsigned i=1; i <= _edgeSet.at(0).rows(); ++i) {
        			result(i-1) = glp_get_col_prim(normal, i);
        		}

        		glp_delete_prob(normal);

        		return result;
            }
    };
    
    template<typename Number>
    std::ostream& operator<<(std::ostream& _lhs, const hypro::polytope::Hyperplane<Number>& _rhs)
    {
        _lhs << "( " << _rhs.normal() << ", " << Number(_rhs.offset()) << " )";
        return _lhs;
    }

    template<typename Number>
    class Cone 
    {
        public:
            typedef std::vector<Hyperplane<Number>* > planes;
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
                assert(mPlanes.size() == _dimension);
            }
            
            /*
             * Getters & setters
             */
            
            const planes& get() const
            {
                return mPlanes;
            }

            planes& rGet()
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
            
            void add(Hyperplane<Number>* _plane)

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
					
