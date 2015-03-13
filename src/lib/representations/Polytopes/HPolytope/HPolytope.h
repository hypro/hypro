/* 
 * File:   HPolytope.h
 * Author: stefan
 *
 * Created on July 16, 2014, 4:23 PM
 */

#pragma once

#include "../util.h"
#include <cassert>
#include "simplex.h"
#include "../VPolytope/VPolytope.h"

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
		
		// conversion constructors
		HPolytope(const VPoltope<Number>& alien);
		
		~HPolytope();
		
		/*
		 * Getters and setters
		 */
		
		unsigned dimension() const;
		
		const typename polytope::Fan<Number>& fan() const;
		
		void addConstraint(const polytope::Hyperplane<Number>& plane);
		void addConstraints(const typename HyperplaneVector::iterator begin, const typename HyperplaneVector::iterator end);
		
		const HyperplaneVector& constraints() const;
		bool hasConstraint(const polytope::Hyperplane<Number>& hplane) const;
		
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
		
		polytope::Hyperplane<Number> operator[](unsigned i) const;
		HPolytope<Number>& operator= (const HPolytope<Number>& rhs);
		std::ostream& operator<<(std::ostream& lhs);
		
	private:
		/*
		 * Auxiliary functions
		 */
		void calculateFan() const;
		Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, Eigen::Dynamic> getOptimalDictionary(const Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, Eigen::Dynamic> A, unsigned dimension, std::vector<unsigned>& B, std::vector<unsigned>& N) const;
		
	};

} //namespace

#include "HPolytope.tpp"
