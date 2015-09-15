/* 
 * @file   HPolytope.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since 	2014-07-16
 * @version 	2015-03-16
 */

#pragma once

#include "../util.h"
#include <cassert>
#include <glpk.h>
#include "../VPolytope/VPolytope.h"
#include "../../../util/convexHull.h"

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
		HPolytope(const matrix_t<Number>& A, const vector_t<Number>& b);
		HPolytope(const matrix_t<Number>& A);
		
		// conversion constructors
		HPolytope(const VPolytope<Number>& alien);
		
		~HPolytope();
		
		/*
		 * Getters and setters
		 */
		
		bool empty() const;

		unsigned dimension() const;
		unsigned size() const;
		
		const typename polytope::Fan<Number>& fan() const;
		typename std::vector<Point<Number>> vertices() const;
		Number supremum() const;
		
		void insert(const Hyperplane<Number>& plane);
		void insert(const typename HyperplaneVector::iterator begin, const typename HyperplaneVector::iterator end);
		
		const HyperplaneVector& constraints() const;
		bool hasConstraint(const Hyperplane<Number>& hplane) const;
		void reduce();
		
		matrix_t<Number> peter() const;
		vector_t<Number> getConstraintsOffsetVector() const;
		
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

		HPolytope linearTransformation(const matrix_t<Number>& A, const vector_t<Number>& b) const;
		HPolytope minkowskiSum(const HPolytope& rhs) const;
		HPolytope intersect(const HPolytope& rhs) const;
		bool contains(const Point<Number>& point) const;
		bool contains(const vector_t<Number>& vec) const;
		bool contains(const HPolytope<Number>& rhs) const;
		HPolytope unite(const HPolytope& rhs) const;

		matrix_t<Number> getConstaintsMatrix() const;

		void clear();
		void print() const;
		
		/*
		 * Operators
		 */
		
		Hyperplane<Number> operator[](unsigned i) const;
		HPolytope<Number>& operator= (const HPolytope<Number>& rhs);

		friend std::ostream& operator<<(std::ostream& lhs, const HPolytope<Number>& rhs){
			if(rhs.constraints().size() > 0) {
				lhs << "[ ";
				for(unsigned i = 0; i < rhs.constraints().size()-1; ++i)
				{
					lhs << rhs[i] << "," << std::endl;
				}
				lhs << rhs[rhs.constraints().size()-1] << " ]";
			}
			return lhs;
		}

		friend void swap(HPolytope<Number>& a, HPolytope<Number>& b) {
			/*
			a.printArrays();
			b.printArrays();
			std::cout << "a: " << a << std::endl;
			std::cout << "b: " << b << std::endl;
			*/
			if(a.mInitialized){
				int* tmpIa = a.ia;
				int* tmpJa= a.ia;
				double* tmpAr = a.ar;
				glp_prob* tmpLp = a.lp;
				if(b.mInitialized){
					a.ia = b.ia;
					a.ja = b.ja;
					a.ar=b.ar;
					a.lp = b.lp;
				} else {
					a.ia = nullptr;
					a.ja = nullptr;
					a.ar = nullptr;
					a.lp = nullptr;
					a.mInitialized = false;
					b.mInitialized = true;
				}
				b.ia = tmpIa;
				b.ja = tmpJa;
				b.ar=tmpAr;
				b.lp= tmpLp;
			} else {
				if(b.mInitialized) {
					a.ia = b.ia;
					a.ja = b.ja;
					a.ar=b.ar;
					a.lp = b.lp;
					a.mInitialized = true;
					b.mInitialized = false;
					b.ia = nullptr;
					b.ja = nullptr;
					b.ar = nullptr;
					b.lp = nullptr;
				}
			}
			if(a.mFanSet) {
				polytope::Fan<Number> tmp = a.mFan;
				if(b.mFanSet) {
					a.mFan = b.mFan;
				} else {
					a.mFanSet = false;
				}
				b.mFan = tmp;
			} else {
				if(b.mFanSet) {
					a.mFan = b.mFan;
					a.mFanSet = true;
					b.mFanSet = false;
				}
			}
			unsigned tmpDimension = a.mDimension;
			a.mDimension = b.mDimension;
			b.mDimension = tmpDimension;
			swap(a.mHPlanes, b.mHPlanes);

			/*
			std::cout << " HPOLY SWAP " << std::endl;
			a.printArrays();
			b.printArrays();
			std::cout << "a: " << a << std::endl;
			std::cout << "b: " << b << std::endl;
			*/
		}

	private:
		/*
		 * Auxiliary functions
		 */

		void createArrays(unsigned size) const;
		void deleteArrays();
		void printArrays();
		void initialize() const;

		void calculateFan() const;

		/*
		Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, Eigen::Dynamic> getOptimalDictionary(const Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, Eigen::Dynamic> A, unsigned dimension, std::vector<unsigned>& B, std::vector<unsigned>& N) const;
		*/
	};

} //namespace
/*
namespace std {

	template<typename Number>
	void swap(hypro::HPolytope<Number> lhs, hypro::HPolytope<Number> rhs) {
		hypro::HPolytope<Number>::swap(lhs,rhs);
	}

}
*/
#include "HPolytope.tpp"
