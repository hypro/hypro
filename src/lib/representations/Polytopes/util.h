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
 #include "../../datastructures/Hyperplane.h"
 #include "../../util/VariablePool.h"
 #include <carl/formula/Constraint.h>

namespace hypro
{
namespace polytope
{
	template<typename Number>
	class Cone 
	{
		public:
			typedef std::vector<Hyperplane<Number>* > planeVector;
		private:
			planeVector     mPlanes;

		public:
			Cone() :
			mPlanes()
			{}

			Cone(const Cone& _orig) :
			mPlanes(_orig.planes())
			{}

			Cone(const planeVector& _planes) :
			mPlanes(_planes)
			{}
			
			~Cone()
			{
				mPlanes.clear();
			}

			/*
			 * Getters & setters
			 */
			
			const planeVector& planes() const {
				return mPlanes;
			}

			planeVector& rPlanes() {
				return mPlanes;
			}

			unsigned dimension() const {
				if(!mPlanes.empty())
					return mPlanes[0].dimension();

				return 0;
			}
			
			unsigned size() const {
				return mPlanes.size();
			}

			const Hyperplane<Number>* planes(unsigned _index) const {
				assert(_index < mPlanes.size());
				return mPlanes.at(_index);
			}
			
			const Hyperplane<Number>* planes(typename planeVector::const_iterator _pos) const {
				return *_pos;
			}
			
			typename planeVector::const_iterator begin() {
				return mPlanes.begin();
			}
			
			typename planeVector::const_iterator end() {
				return mPlanes.end();
			}
			
			void add(Hyperplane<Number>* _plane) {
				mPlanes.push_back(_plane);
			}

			void add(vector_t<Number> _vector) {

			}

			Cone<Number> linearTransformation(const matrix_t<Number> A) const {
				Cone<Number> result;
				for(const auto& plane : mPlanes) {
					result.add(new Hyperplane<Number>(plane->linearTransformation(A)));
				}
				return result;
			}

			Cone<Number> minkowskiSum(const Cone& _rhs) const {
				Cone<Number> result;
				return result;
			}
			
			Point<Number> getUnitAverageVector() const {
				assert(!mPlanes.empty());
				Point<Number> result;
				unsigned numberPlanes = mPlanes.size();
				for(auto& plane : mPlanes)
				{
					result += (plane->normal()/numberPlanes);
				}
				return result;
			}
			
			bool contains(const vector_t<Number>& _vector) const {
				for(const auto& plane : mPlanes) {
					if(_vector.dot(plane->normal()) > 0)
						return false;
				}
				return true;
			}

			bool contains(const Point<Number>* _vector) const {
				return this->contains(_vector->rawCoordinates());
			}
			
			Cone<Number> operator=(const Cone<Number>& _rhs) {
				/*
				if( this != &_rhs )
				{
					Cone<Number> tmp(_rhs);
					std::swap(*this,tmp);
				}*/
				mPlanes.clear();
				mPlanes = _rhs.planes();
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

} // namespace polytope
} // namespace hypro

					
