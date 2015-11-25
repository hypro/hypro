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
#include "../../../util/vertexEnumeration.h"
#include "../../../util/smtrat/SimplexSolver.h"
#include "util.h"


namespace hypro {

enum SOLUTION { FEAS = 0, INFEAS, INFTY };

template <typename Number>
class HPolytope {
public:
  	enum REDUCTION_STRATEGY {
                              DROP = 0,
                              DROP_SMOOTH,
                              UNITE,
                              UNITE_SMOOTH,
                              UNITE_CUT,
                              UNITE_NORM,
                              DIRECTED_SMALL,
                              DIRECTED_BIG
                            };

	typedef std::vector<Hyperplane<Number>> HyperplaneVector;

  private:
	HyperplaneVector mHPlanes;
	bool mFanSet;
	mutable polytope::Fan<Number> mFan;
	unsigned mDimension;

	// glpk members
	mutable glp_prob* lp;
	mutable int* ia;
	mutable int* ja;
	mutable double* ar;
	mutable bool mInitialized;

  public:
	HPolytope();
	HPolytope( const HPolytope& orig );
	HPolytope( const HyperplaneVector& planes );
	HPolytope( const matrix_t<Number>& A, const vector_t<Number>& b );
	HPolytope( const matrix_t<Number>& A );

	// conversion constructors
	HPolytope( const VPolytope<Number>& alien );

	~HPolytope();

	/*
	 * Getters and setters
	 */

	bool empty() const;
	static HPolytope<Number> Empty();

	std::size_t dimension() const;
	std::size_t size() const;

	matrix_t<Number> matrix() const;
	vector_t<Number> vector() const;
	std::pair<matrix_t<Number>, vector_t<Number>> inequalities() const;

	const typename polytope::Fan<Number>& fan() const;
	typename std::vector<Point<Number>> vertices() const;
	Number supremum() const;

	void insert( const Hyperplane<Number>& plane );
	void insert( const typename HyperplaneVector::iterator begin, const typename HyperplaneVector::iterator end );

	const HyperplaneVector& constraints() const;
	bool hasConstraint( const Hyperplane<Number>& hplane ) const;
	void removeRedundantPlanes();

  HPolytope<Number> reduce_nd(unsigned facet=1, unsigned facet2=0, REDUCTION_STRATEGY strat = REDUCTION_STRATEGY::DROP) const;
  HPolytope<Number> reduce_directed(std::vector<vector_t<Number>> directions, REDUCTION_STRATEGY strat = REDUCTION_STRATEGY::DIRECTED_SMALL) const;
  void reduceAssign(unsigned _steps = 1, REDUCTION_STRATEGY strat = REDUCTION_STRATEGY::DROP);

  // Help functions by Igor Bongartz
  std::vector<std::vector<unsigned>> getMembersOfVertices(std::vector<Point<Number>> vertices) const;
  std::vector<unsigned> getNeighborsOfIndex(unsigned facet, std::vector<std::vector<unsigned>> membersOfvertices) const;

  std::vector<Point<Number>> getVerticesOfIndex(unsigned a, std::vector<Point<Number>> vertices, std::vector<std::vector<unsigned>> membersOfvertices) const;
  std::vector<Point<Number>> getVerticesOf2Indices(unsigned a, unsigned b, std::vector<Point<Number>> vertices, std::vector<std::vector<unsigned>> membersOfvertices) const;
  std::vector<Point<Number>> getVerticesOf2IndicesAround(unsigned a, unsigned b, std::vector<Point<Number>> vertices, std::vector<std::vector<unsigned>> membersOfvertices) const;
  std::vector<std::vector<vector_t<Number>>> getVerticesPermutationForFacet(unsigned a, unsigned b, std::vector<Point<Number>> vertices) const;

  vector_t<Number> computeNormal(std::vector<vector_t<Number>> vertices, vector_t<Number> check) const;

  Point<Number> getVertexForVector(vector_t<Number> vector, std::vector<Point<Number>> vertices) const;

  bool isBounded(std::vector<vector_t<Number>>) const;
  // End Help funcions


	bool isExtremePoint( vector_t<Number> point ) const;
	bool isExtremePoint( const Point<Number>& point ) const;
	std::pair<Number, SOLUTION> evaluate( const vector_t<Number>& _direction ) const;

	typename HyperplaneVector::iterator begin();
	typename HyperplaneVector::const_iterator begin() const;
	typename HyperplaneVector::iterator end();
	typename HyperplaneVector::const_iterator end() const;

	std::vector<Point<Number>> vertexEnumeration() const;

	/*
	 * General interface
	 */

	HPolytope linearTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const;
	HPolytope minkowskiSum( const HPolytope& rhs ) const;
	HPolytope intersect( const HPolytope& rhs ) const;
	HPolytope<Number> intersectHyperplane( const Hyperplane<Number>& rhs ) const;
	HPolytope<Number> intersectHyperplanes( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const;
	bool contains( const Point<Number>& point ) const;
	bool contains( const vector_t<Number>& vec ) const;
	bool contains( const HPolytope<Number>& rhs ) const;
	HPolytope unite( const HPolytope& rhs ) const;

	matrix_t<Number> getConstaintsMatrix() const;

	void clear();
	void print() const;

	/*
	 * Operators
	 */

	const Hyperplane<Number>& operator[]( size_t i ) const;
	Hyperplane<Number>& operator[]( size_t i ) ;
	HPolytope<Number>& operator=( const HPolytope<Number>& rhs );

	friend std::ostream& operator<<( std::ostream& lhs, const HPolytope<Number>& rhs ) {
		if ( rhs.constraints().size() > 0 ) {
			lhs << "[ ";
			for ( unsigned i = 0; i < rhs.constraints().size() - 1; ++i ) {
				lhs << rhs[i] << "," << std::endl;
			}
			lhs << rhs[rhs.constraints().size() - 1] << " ]";
		}
		return lhs;
	}

	friend void swap( HPolytope<Number>& a, HPolytope<Number>& b ) {
		/*
		a.printArrays();
		b.printArrays();
		std::cout << "a: " << a << std::endl;
		std::cout << "b: " << b << std::endl;
		*/
		if ( a.mInitialized ) {
			glp_prob* tmpLp = glp_create_prob();
			glp_copy_prob(tmpLp, a.lp, GLP_OFF);
			if ( b.mInitialized ) {
				glp_copy_prob(a.lp, b.lp, GLP_OFF);
				glp_copy_prob(b.lp, tmpLp, GLP_OFF);
				glp_delete_prob(tmpLp);
			} else {
				glp_delete_prob(a.lp);
				b.lp = glp_create_prob();
				glp_copy_prob(b.lp, tmpLp, GLP_OFF);
				a.mInitialized = false;
				b.mInitialized = true;
			}
		} else {
			if ( b.mInitialized ) {
				a.lp = glp_create_prob();
				glp_copy_prob(a.lp, b.lp, GLP_OFF);
				glp_delete_prob(b.lp);
				a.mInitialized = true;
				b.mInitialized = false;
			}
		}
		if ( a.mFanSet ) {
			polytope::Fan<Number> tmp = a.mFan;
			if ( b.mFanSet ) {
				a.mFan = b.mFan;
			} else {
				a.mFanSet = false;
			}
			b.mFan = tmp;
		} else {
			if ( b.mFanSet ) {
				a.mFan = b.mFan;
				a.mFanSet = true;
				b.mFanSet = false;
			}
		}
		unsigned tmpDimension = a.mDimension;
		a.mDimension = b.mDimension;
		b.mDimension = tmpDimension;
		swap( a.mHPlanes, b.mHPlanes );

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

	void createArrays( unsigned size ) const;
	void deleteArrays();
	void printArrays();
	void initialize() const;

	void calculateFan() const;

};

}  // namespace
/*
namespace std {

	template<typename Number>
	void swap(hypro::HPolytope<Number> lhs, hypro::HPolytope<Number> rhs) {
		hypro::HPolytope<Number>::swap(lhs,rhs);
	}

}
*/
#include "HPolytope.tpp"
