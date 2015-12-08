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

#include "Point.h"
#include "../util/VariablePool.h"
 #include "../util/linearSolving.h"
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
    size_t mHash = 0;

  public:
	Hyperplane();
	Hyperplane( const Hyperplane<Number>& _orig );
	Hyperplane( const Point<Number>& _vector, const Number& _off );
	Hyperplane( std::initializer_list<Number> _coordinates, const Number& _off );
	Hyperplane( const vector_t<Number>& _vector, const Number& _off );
	//Hyperplane( const carl::Constraint<polynomial_t<Number>>& _constraint ); /////////////////////// TRAC
	Hyperplane( const vector_t<Number>& _vec, const std::vector<vector_t<Number>>& _vectorSet );

	~Hyperplane();

  double sizeOfHyperplane(){
    return sizeof(*this) + this->mNormal.size()* sizeof(Number);
  }

	unsigned dimension() const;
	void reduceDimension( unsigned _dimension );
	void reduceToDimensions( std::vector<unsigned> _dimensions );

	const vector_t<Number>& normal() const;
    vector_t<Number>& rNormal();
	void setNormal( const vector_t<Number>& _normal );
	void invert();

	Number offset() const;
	void setOffset( Number _offset );

	Number signedDistance( const vector_t<Number>& _point ) const;
	Number evaluate( const vector_t<Number>& _direction ) const;

	bool intersection( Number& _result, const vector_t<Number>& _vector ) const;
	bool intersection( Number& _result, const Point<Number>& _vector ) const;

	Hyperplane<Number> linearTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const;
	//HPolytope<Number> intersection( const Hyperplane<Number>& _rhs ) const; /////////// TRAC
	vector_t<Number> intersectionVector( const Hyperplane<Number>& _rhs ) const;

	static vector_t<Number> fastIntersect( const std::vector<Hyperplane<Number>>& _planes );
	static vector_t<Number> saveIntersect( const std::vector<Hyperplane<Number>>& _planes, Number threshold = 0);

	bool contains( const vector_t<Number> _vector ) const;
	bool holds( const vector_t<Number> _vector ) const;

    vector_t<Number> normal() { return mNormal; };
    Number scalar() { return mScalar; };
    size_t hash() {

        //TODO review line 79
        /*
        if (this->mHash = 0) {
        if (this->mHash == 0) {
            this->mHash = std::hash<hypro::Hyperplane<Number>>(*this);
        } else {
            return mHash;
        }*/

        return mHash;
    }

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

template <typename Number>
Hyperplane<Number> operator-( const Hyperplane<Number>& _in ) {
	return Hyperplane(_in).invert();
}

    #ifdef EXTERNALIZE_CLASSES
    extern template class Hyperplane<double>;

    #ifdef USE_MPFR_FLOAT
    extern template class Hyperplane<carl::FLOAT_T<mpfr_t>>;
    #endif

    extern template class Hyperplane<carl::FLOAT_T<double>>;
    #endif
}  // namespace

namespace std{
    template<class Number>
    struct hash<hypro::Hyperplane<Number>> {
        std::size_t operator()(hypro::Hyperplane<Number> const& hyperplane) const
        {
            size_t seed = 0;
            hypro::vector_t<Number> normal = hyperplane.normal();
            Number scalar = hyperplane.scalar();
            std::hash<hypro::vector_t<Number>> vectorHasher;
            std::hash<Number> numberHasher;
            seed = vectorHasher(normal);
            boost::hash_combine(seed, numberHasher(scalar));
            return seed;
        }
    };
} //namespace

#include "Hyperplane.tpp"
