/*
 * @file   HPolytope.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since 	2014-07-16
 * @version 	2015-03-16
 */

#pragma once

#include "util.h"
#include "../util.h"
#include "../../../util/convexHull.h"
#include "../../../util/vertexEnumeration.h"
#include "../../../util/Optimizer.h"
#include "../../../util/Permutator.h"

#include <cassert>

#define REDUCE_NUMBERS

namespace hypro {

template <typename Number, typename Converter>
class HPolytopeT {
public:
  	enum REDUCTION_STRATEGY {
                              DROP = 0,
                              DROP_SMOOTH,
                              UNITE,
                              UNITE_SMOOTH,
                              UNITE_CUT,
                              UNITE_NORM,
                              DIRECTED_SMALL,
                              DIRECTED_BIG,
                              DIRECTED_TEMPLATE
                            };

	typedef std::vector<Hyperplane<Number>> HyperplaneVector;

  private:
	mutable HyperplaneVector mHPlanes;
	bool mFanSet;
	mutable polytope::Fan<Number> mFan;
	unsigned mDimension;

	// State flags
	mutable State mEmpty;
	mutable bool mNonRedundant;


  public:
	HPolytopeT();
	HPolytopeT( const HPolytopeT& orig );
	HPolytopeT( const HyperplaneVector& planes );
	HPolytopeT( const matrix_t<Number>& A, const vector_t<Number>& b );
	HPolytopeT( const matrix_t<Number>& A );
	HPolytopeT( const std::vector<Point<Number>>& points );

	~HPolytopeT();

	/*
	 * Getters and setters
	 */
	double sizeOfHPolytopeT(){
		return sizeof(*this) + this->mHPlanes.size()*this->mHPlanes.at(0).sizeOfHyperplane();
	}

	bool empty() const;
	static HPolytopeT<Number, Converter> Empty();

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

  	void erase( const unsigned index);

	const HyperplaneVector& constraints() const;
	bool hasConstraint( const Hyperplane<Number>& hplane ) const;
	void removeRedundancy();

	HPolytopeT<Number, Converter> heuristic() const;
	HPolytopeT<Number, Converter> reduce(unsigned facet=1, unsigned facet2=0, REDUCTION_STRATEGY strat = REDUCTION_STRATEGY::DROP) const;
	HPolytopeT<Number, Converter> reduce_directed(std::vector<vector_t<Number>> directions, REDUCTION_STRATEGY strat = REDUCTION_STRATEGY::DIRECTED_SMALL) const;
	void reduceAssign(unsigned _steps = 1, REDUCTION_STRATEGY strat = REDUCTION_STRATEGY::DROP);

	bool isBounded(std::vector<vector_t<Number>>) const;
	//static std::vector<vector_t<Number>> computeTemplate(unsigned dimension, unsigned polytope);

	bool isExtremePoint( const vector_t<Number>& point ) const;
	bool isExtremePoint( const Point<Number>& point ) const;
	EvaluationResult<Number> evaluate( const vector_t<Number>& _direction ) const;

	std::vector<Point<Number>> vertexEnumeration() const;

	/*
	 * General interface
	 */

	std::pair<bool, HPolytopeT> satisfiesHyperplane( const vector_t<Number>& normal, const Number& offset ) const;
	std::pair<bool, HPolytopeT> satisfiesHyperplanes( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const;
	HPolytopeT linearTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const;
	HPolytopeT minkowskiSum( const HPolytopeT& rhs ) const;
	HPolytopeT intersect( const HPolytopeT& rhs ) const;
	HPolytopeT intersectHyperplane( const Hyperplane<Number>& rhs ) const;
	HPolytopeT intersectHyperplanes( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const;
	bool contains( const Point<Number>& point ) const;
	bool contains( const vector_t<Number>& vec ) const;
	bool contains( const HPolytopeT<Number, Converter>& rhs ) const;
	HPolytopeT unite( const HPolytopeT& rhs ) const;

	void clear();
	void print() const;

	/*
	 * Operators
	 */

	//const Hyperplane<Number>& operator[]( size_t i ) const;
	//Hyperplane<Number>& operator[]( size_t i ) ;
	HPolytopeT& operator=( const HPolytopeT<Number, Converter>& rhs );

	friend std::ostream& operator<<( std::ostream& lhs, const HPolytopeT<Number, Converter>& rhs ) {
		if ( rhs.constraints().size() > 0 ) {
			lhs << "[ ";
			for ( unsigned i = 0; i < rhs.constraints().size() - 1; ++i ) {
				lhs << rhs.constraints()[i] << "," << std::endl;
			}
			lhs << rhs.constraints()[rhs.constraints().size() - 1] << " ]";
		}
		return lhs;
	}

	friend void swap( HPolytopeT<Number, Converter>& a, HPolytopeT<Number, Converter>& b ) {
		unsigned tmpDim = a.mDimension;
		a.mDimension = b.mDimension;
		b.mDimension = tmpDim;
		swap( a.mHPlanes, b.mHPlanes );
	}

	void reduceNumberRepresentation(unsigned limit = fReach_DENOMINATOR) const;
  private:
	/*
	 * Auxiliary functions
	 */

	void calculateFan() const;


	std::vector<std::vector<unsigned>> getMembersOfVertices(std::vector<Point<Number>> vertices) const;
	std::vector<unsigned> getNeighborsOfIndex(unsigned facet, std::vector<std::vector<unsigned>> membersOfvertices) const;

	std::vector<Point<Number>> getVerticesOfIndex(unsigned a, std::vector<Point<Number>> vertices, std::vector<std::vector<unsigned>> membersOfvertices) const;
	std::vector<Point<Number>> getVerticesOf2Indices(unsigned a, unsigned b, std::vector<Point<Number>> vertices, std::vector<std::vector<unsigned>> membersOfvertices) const;
	std::vector<Point<Number>> getVerticesOf2IndicesAround(unsigned a, unsigned b, std::vector<Point<Number>> vertices, std::vector<std::vector<unsigned>> membersOfvertices) const;
	std::vector<std::vector<vector_t<Number>>> getVerticesPermutationForFacet(unsigned a, unsigned b, std::vector<Point<Number>> vertices) const;

	vector_t<Number> computeNormal(std::vector<vector_t<Number>> vertices, vector_t<Number> check) const;

	Point<Number> getVertexForVector(vector_t<Number> vector, std::vector<Point<Number>> vertices) const;

};

}  // namespace

#include "HPolytope.tpp"
#include "reduction.tpp"


