/**
 *  Class that holds the implementation of a hyperplane.
 *  @file Hyperplane.h
 *
 *  @author Stefan Schupp 	<stefan.schupp@cs.rwth-aachen.de>
 *
 *  @since 	2015-03-16
 *  @version 	2015-03-16
 */

#pragma once

#include <cassert>
#include <glpk.h>

//#include "Point.h"
#include "../util/VariablePool.h"
#include <carl/formula/Constraint.h>

namespace hypro {

template <typename Number>
using polynomial_t = carl::MultivariatePolynomial<Number>;

template <typename Number>
class HPolytope;

template <typename Number>
class Hyperplane {
  private:
	vector_t<Number> mNormal;
	Number mScalar;

  public:
	Hyperplane();
	Hyperplane( const Hyperplane<Number>& _orig );
	Hyperplane( const Point<Number>& _vector, const Number& _off );
	Hyperplane( std::initializer_list<Number> _coordinates, const Number& _off );
	Hyperplane( const vector_t<Number>& _vector, const Number& _off );
	Hyperplane( const carl::Constraint<polynomial_t<Number>>& _constraint );
	Hyperplane( const vector_t<Number>& _vec, const std::vector<vector_t<Number>>& _vectorSet );

	~Hyperplane();

	unsigned dimension() const;
	void reduceDimension( unsigned _dimension );
	void reduceToDimensions( std::vector<unsigned> _dimensions );

	const vector_t<Number>& normal() const;
  vector_t<Number>& rNormal();
	void setNormal( const vector_t<Number>& _normal );

	Number offset() const;
	void setOffset( Number _offset );

	Number signedDistance( const vector_t<Number>& _point ) const;
	Number evaluate( const vector_t<Number>& _direction ) const;

	bool intersection( Number& _result, const vector_t<Number>& _vector ) const;
	bool intersection( Number& _result, const Point<Number>& _vector ) const;

	Hyperplane<Number> linearTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const;
	HPolytope<Number> intersection( const Hyperplane<Number>& _rhs ) const;
	vector_t<Number> intersectionVector( const Hyperplane<Number>& _rhs ) const;

	bool contains( const vector_t<Number> _vector ) const;
	bool holds( const vector_t<Number> _vector ) const;

	friend void swap( Hyperplane<Number>& a, Hyperplane<Number>& b ) {
		swap( a.mNormal, b.mNormal );
		swap( a.mScalar, b.mScalar );
	}

  private:
	const Number& internalOffset() const;

	/**
	 * @author: Chris K
	 * Method to compute the normal of a plane based on two direction vectors
	 * simply computing the cross product does not work since the dimension is not necessarily 3
	 */
	vector_t<Number> computePlaneNormal( const std::vector<vector_t<Number>>& _edgeSet );
};

template <typename Number>
std::ostream& operator<<( std::ostream& _lhs, const hypro::Hyperplane<Number>& _rhs ) {
	_lhs << "( " << _rhs.normal() << "; " << Number( _rhs.offset() ) << " )";
	return _lhs;
}

template <typename Number>
bool operator==( const Hyperplane<Number>& lhs, const Hyperplane<Number>& rhs ) {
	return ( lhs.normal() == rhs.normal() && lhs.offset() == rhs.offset() );
}

template <typename Number>
bool operator<( const Hyperplane<Number>& lhs, const Hyperplane<Number>& rhs ) {
	return ( lhs.normal() < rhs.normal() || ( lhs.normal() == rhs.normal() && lhs.offset() < rhs.offset() ) );
}

}  // namespace

#include "Hyperplane.tpp"
