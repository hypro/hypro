/* 
 * @file   HPolytope.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since 	2014-07-16
 * @version 	2015-03-16
 */

#pragma once

#include "../util.h"
#include "../../../datastructures/Hyperplane.h"
#include <cassert>
#include <glpk.h>
#include "simplex.h"
#include "../VPolytope/VPolytope.h"
#include "../../../util/convexHull.h"
#include "../../../datastructures/Facet.h"

namespace hypro
{
	template<typename Number>
	class HPolytope
	{
		public:
			typedef std::vector<Hyperplane<Number> > HyperplaneVector;
		
		private:
			HyperplaneVector mHPlanes;
			bool mFanSet;
			mutable polytope::Fan<Number> mFan;
			unsigned mDimension;

			// glpk members
			mutable glp_prob *lp;
			mutable int* ia;
			mutable int* ja;
			mutable double* ar;
			mutable bool mInitialized;

	public:
		HPolytope();
		HPolytope(const HPolytope& orig);
		HPolytope(const Hyperplane<Number>& plane);
		HPolytope(const HyperplaneVector& planes);
		HPolytope(unsigned dimension);
		HPolytope(const matrix_t<Number>& A, const vector_t<Number>& b);
		HPolytope(const matrix_t<Number>& A);
		
		// conversion constructors
		// HPolytope(const VPolytope<Number>& alien);
		
		~HPolytope();
		
		/*
		 * Getters and setters
		 */
		
		unsigned dimension() const;
		unsigned size() const;
		
		const typename polytope::Fan<Number>& fan() const;
		typename VPolytope<Number>::pointVector vertices() const;
		
		void insert(const Hyperplane<Number>& plane);
		void insert(const typename HyperplaneVector::iterator begin, const typename HyperplaneVector::iterator end);
		
		const HyperplaneVector& constraints() const;
		bool hasConstraint(const Hyperplane<Number>& hplane) const;
		bool isExtremePoint(vector_t<Number> point, const Number& tolerance = 0) const;
		bool isExtremePoint(const Point<Number>& point, const Number& tolerance = 0) const;
		Number evaluate(const vector_t<Number>& _direction) const;
		
		typename HyperplaneVector::iterator begin();
		typename HyperplaneVector::const_iterator begin() const;
		typename HyperplaneVector::iterator end();
		typename HyperplaneVector::const_iterator end() const;
		
		std::vector<Point<Number> > vertexEnumeration() const;

		/*
		 * General interface
		 */

		HPolytope linearTransformation(const matrix_t<Number>& A) const;
		HPolytope minkowskiSum(const HPolytope& rhs) const;
		HPolytope intersect(const HPolytope& rhs) const;
		bool contains(const Point<Number>& point) const;
		bool contains(const vector_t<Number>& vec) const;
		HPolytope unite(const HPolytope& rhs) const;

		void clear();
		
		/*
		 * Operators
		 */
		
		Hyperplane<Number> operator[](unsigned i) const;
		HPolytope<Number>& operator= (const HPolytope<Number>& rhs);
		std::ostream& operator<<(std::ostream& lhs);
		
	private:
		/*
		 * Auxiliary functions
		 */

		void createArrays(unsigned size) const;
		void deleteArrays();
		void initialize() const;

		void calculateFan() const;
		Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, Eigen::Dynamic> getOptimalDictionary(const Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, Eigen::Dynamic> A, unsigned dimension, std::vector<unsigned>& B, std::vector<unsigned>& N) const;
		
	};

} //namespace

#include "HPolytope.tpp"
