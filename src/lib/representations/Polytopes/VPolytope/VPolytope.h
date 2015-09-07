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
//#include <eigen3/Eigen/Geometry>
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
		typedef typename std::vector<Point<Number>> pointVector;
		typedef typename hypro::polytope::Cone<Number> Cone;
		typedef typename hypro::polytope::Fan<Number> Fan;
		/***************************************************************************
	 * Members
	 **************************************************************************/
	private:
		pointVector                 mPoints;
		Cone 						mCone;
		mutable Fan                 mFan;
		bool                        mFanSet;
		bool                        mReduced;
		
		std::vector<std::set<unsigned>> mNeighbors;

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
		VPolytope(const pointVector& points);
		VPolytope(const matrix_t<Number>& _constraints, const vector_t<Number> _constants);

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

		VPolytope linearTransformation(const matrix_t<Number>& A, const vector_t<Number>& b) const;
		VPolytope minkowskiSum(const VPolytope& rhs) const;
		VPolytope intersect(const VPolytope& rhs) const;
		bool contains(const Point<Number>& point) const;
		bool contains(const vector_t<Number>& vec) const;
		bool contains(const VPolytope<Number>& _other) const;
		VPolytope unite(const VPolytope& rhs) const;

		void clear();
		
	/***************************************************************************
	 * Getters, Setters, Iterators
	 **************************************************************************/
		
		unsigned int dimension() const {
			if(mPoints.empty())
				return 0;
			return mPoints[0].dimension();
		}
		
		unsigned size() const {
			return mPoints.size();
		}
		
		bool reduced() const {
			return mReduced;
		}

		Number supremum() const;
		
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

		void setNeighbors(const Point<Number>& _point, const std::set<Point<Number>>& _neighbors) {
			unsigned pos = 0;
			while(pos < mPoints.size() && (mPoints[pos] != _point) ) ++pos;

			if(mPoints[pos] == _point) {
				for(const auto& neighbor : _neighbors) {
					unsigned nPos = 0;
					while(nPos < mPoints.size() && (mPoints[nPos] != neighbor) ) ++nPos;

					if(mPoints[nPos] == neighbor) {
						mNeighbors[pos].insert(nPos);
						mNeighbors[nPos].insert(pos);
					}
				}
			}
		}

		void unsafeSetNeighbors(const std::vector<std::set<unsigned>>& _neighbors) {
			mNeighbors = _neighbors;
		}

		std::vector<Point<Number>> neighbors(const Point<Number>& _point) const {
			std::vector<Point<Number>> result;
			unsigned pos = 0;
			while(pos < mPoints.size() && (mPoints[pos] != _point) ) ++pos;

			if(mPoints[pos] == _point) {
				for(unsigned nPos : mNeighbors[pos])
					result.emplace_back(mPoints[nPos]);
			}
			return std::move(result);
		}
		
		typename pointVector::iterator insert(const Point<Number>& i) {
			assert(dimension() == 0 || dimension() == i.dimension());
			mReduced = false;
			auto res = mPoints.insert(mPoints.end(), i);
			mNeighbors.push_back(std::set<unsigned>());
			return res;
		}

		typename pointVector::iterator insert(const vector_t<Number>& _coord) {
			assert(dimension() == 0 || dimension() == _coord.rows());
			mReduced = false;
			mNeighbors.push_back(std::set<unsigned>());
			return mPoints.insert(mPoints.end(), Point<Number>(_coord));
		}
		
		typename pointVector::iterator insert(const typename pointVector::const_iterator begin, const typename pointVector::const_iterator end) {
			assert(dimension() == 0 || dimension() == begin->dimension());
			mReduced = false;
			mNeighbors.push_back(std::set<unsigned>());
			return mPoints.insert(mPoints.end(),begin,end);
		}
		
		const pointVector& vertices() const {
			return mPoints;
		}
		
		bool hasVertex(const Point<Number>& vertex) const {
			for(const auto point : mPoints) {
				if(point == vertex)
					return true;
			}
			return false;
		}

		bool hasVertex(const vector_t<Number>& vertex) const {
			return (mPoints.find(vertex) != mPoints.end());
		}
		
		typename pointVector::iterator begin() {
			return mPoints.begin();
		}

		typename pointVector::const_iterator begin() const {
			return mPoints.begin();
		}
		
		typename pointVector::iterator end() {
			return mPoints.end();
		}

		typename pointVector::const_iterator end() const {
			return mPoints.end();
		}

		void print() const {
			std::cout << *this << std::endl;
		}
		
		void reduce();
		void updateNeighbors();

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
