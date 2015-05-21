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
#include <glpk.h>
#include <set>
#include <cassert>
#include "../../../util/convexHull.h"
#include "../../../datastructures/Facet.h"

namespace hypro
{

template<typename Number>
class VPolytope : public hypro::GeometricObject<Number>
{
	public:
		typedef typename std::set<vector_t<Number>> vertexSet;
		typedef typename hypro::polytope::Cone<Number> Cone;
		typedef typename hypro::polytope::Fan<Number> Fan;
		/***************************************************************************
	 * Members
	 **************************************************************************/
	private:
		vertexSet                      mVertices;
		Cone 						mCone;
		mutable Fan                    mFan;
		bool                           mFanSet;
		bool                           mReduced;
		
		// GLPK members
		mutable bool							mInitialized;
		mutable glp_prob*						mLp;
		mutable glp_smcp						mOptions;
		mutable int*							mIa;
		mutable int*							mJa;
		mutable double*							mAr;
		
	public:
	/***************************************************************************
	 * Constructors
	 **************************************************************************/

	 	// constructors for bounded v-polyhedra -> v-polytopes
		VPolytope();
		VPolytope(const Point<Number>& point);
		VPolytope(const vertexSet& points);
		VPolytope(const std::vector<Point<Number>> points);

		VPolytope(const VPolytope& orig);
		VPolytope(VPolytope&& _orig) = default;

		~VPolytope()
		{
			if(mInitialized){
				// cleanup
				//glp_delete_prob(mLp);
				//delete[] mIa;
				//delete[] mJa;
				//delete[] mAr;
			}
		}
		
	/***************************************************************************
	* General interface
	**************************************************************************/

		VPolytope linearTransformation(const matrix_t<Number>& A) const;
		VPolytope minkowskiSum(const VPolytope& rhs) const;
		VPolytope intersect(const VPolytope& rhs) const;
		bool contains(const Point<Number>& point) const;
		bool contains(const vector_t<Number>& vec) const;
		VPolytope unite(const VPolytope& rhs) const;

		void clear();
		
	/***************************************************************************
	 * Getters, Setters, Iterators
	 **************************************************************************/
		
		unsigned int dimension() const
		{
			if(mVertices.empty())
				return 0;
			return mVertices.begin()->rows();
		}
		
		unsigned size() const {
			return mVertices.size();
		}
		
		bool reduced() const {
			return mReduced;
		}
		
		const typename polytope::Fan<Number>& fan() const {
			if(!mFanSet)
			{
				calculateFan();
			}
			return mFan;
		}

		const Cone& cone() const {
			return mCone;
		}

		void setCone(const Cone& _cone) {
			mCone = _cone;
		}
		
		std::pair<typename vertexSet::iterator, bool> insert(const Point<Number>& i)
		{
			assert(dimension() == 0 || dimension() == i.dimension());
			mReduced = false;
			return mVertices.insert(i.rawCoordinates());
		}

		std::pair<typename vertexSet::iterator, bool> insert(const vector_t<Number>& _coord) {
			assert(dimension() == 0 || dimension() == _coord.rows());
			mReduced = false;
			return mVertices.insert(_coord);
		}
		
		void insert(const typename vertexSet::iterator begin, const typename vertexSet::iterator end)
		{
			assert(dimension() == 0 || dimension() == begin->rows());
			mVertices.insert(begin,end);
			mReduced = false;
		}
		
		const vertexSet& vertices() const
		{
			return mVertices;
		}
		
		bool hasVertex(const Point<Number>& vertex) const
		{
			return (mVertices.find(vertex.rawCoordinates()) != mVertices.end());
		}

		bool hasVertex(const vector_t<Number>& vertex) const
		{
			return (mVertices.find(vertex) != mVertices.end());
		}
		
		typename vertexSet::iterator begin()
		{
			return mVertices.begin();
		}

		typename vertexSet::const_iterator begin() const
		{
			return mVertices.begin();
		}
		
		typename vertexSet::iterator end()
		{
			return mVertices.end();
		}

		typename vertexSet::const_iterator end() const
		{
			return mVertices.end();
		}
		
		private:
	/***************************************************************************
	 * Auxiliary functions
	 **************************************************************************/
	 	void initGLPK() const;
		const Fan& calculateFan() const;
		const Cone& calculateCone(const Point<Number>& vertex);
		
	/***************************************************************************
	 * Operators
	 **************************************************************************/
		public:
		VPolytope<Number>& operator=(const VPolytope<Number>& rhs);
		VPolytope<Number>& operator=(VPolytope<Number>&& rhs) = default;
		bool operator==(const VPolytope<Number>& rhs);
};

template<typename Number>
std::ostream& operator<<(std::ostream& out, const hypro::VPolytope<Number>& lhs) {
	out << "{ ";
	for(const auto& vector : lhs) {
		out << vector << " ";
	}
	out << "}";
	return out;
}

}//namespace

#include "VPolytope.tpp"
