/**
 *  Class that holds the implementation of a Halfspace.
 *  @file Halfspace.h
 *
 *  @author Stefan Schupp 	<stefan.schupp@cs.rwth-aachen.de>
 *
 *  @since 	2015-03-16
 *  @version 	2015-03-16
 */

#pragma once
#include "Point.h"
#include "../util/VariablePool.h"
#include "../util/linearSolving.h"
#include <carl/formula/Constraint.h>
#include <cassert>
#include <glpk.h>

namespace hypro {

template <typename Number>
class Halfspace {
  private:
	vector_t<Number> mNormal;
	Number mScalar;
    size_t mHash = 0;
    bool mIsInteger;

  public:
	Halfspace();
	Halfspace( const Halfspace<Number>& _orig );
	Halfspace( const Point<Number>& _vector, const Number& _off );
	Halfspace( std::initializer_list<Number> _coordinates, const Number& _off );
	Halfspace( const vector_t<Number>& _vector, const Number& _off );
	Halfspace( const vector_t<Number>& _vec, const std::vector<vector_t<Number>>& _vectorSet );

	~Halfspace();

	double sizeOfHalfspace(){
	return sizeof(*this) + this->mNormal.size()* sizeof(Number);
	}

	unsigned dimension() const;
	void reduceDimension( unsigned _dimension );
	void reduceToDimensions( std::vector<unsigned> _dimensions );

	template<typename N = Number, carl::DisableIf< std::is_same<N,double> > = carl::dummy>
	void makeInteger() {
		if(!mIsInteger){
			Number scaling = Number(carl::getDenom(mScalar));
			for(unsigned i = 0; i < mNormal.rows(); ++i) {
				scaling = scaling * Number(carl::getDenom(mNormal(i)));
			}

			mScalar = mScalar*scaling;
			assert(carl::isInteger(mScalar));

			for(unsigned i = 0; i < mNormal.rows(); ++i) {
				mNormal(i) = mNormal(i)*scaling;
				assert(carl::isInteger(mNormal(i)));
			}
			mIsInteger = true;
		}
	}

	template<typename N = Number, carl::EnableIf< std::is_same<N,double> > = carl::dummy>
	void makeInteger() {
		mIsInteger = true;
		// TODO: As this function is currently only used for number reduction, do nothing for doubles -> fix!
	}

	bool isInteger() const { return mIsInteger; }

	const vector_t<Number>& normal() const;
	void setNormal( const vector_t<Number>& _normal );
	void invert();

	Number offset() const;
	void setOffset( Number _offset );

	Number signedDistance( const vector_t<Number>& _point ) const;
	Number evaluate( const vector_t<Number>& _direction ) const;
	Point<Number> project( const Point<Number> ) const;

	bool intersection( Number& _result, const vector_t<Number>& _vector ) const;
	bool intersection( Number& _result, const Point<Number>& _vector ) const;

	Halfspace<Number> linearTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const;
	//HPolytope<Number> intersection( const Halfspace<Number>& _rhs ) const; /////////// TRAC
	vector_t<Number> intersectionVector( const Halfspace<Number>& _rhs ) const;

	static vector_t<Number> fastIntersect( const std::vector<Halfspace<Number>>& _planes );
	static vector_t<Number> saveIntersect( const std::vector<Halfspace<Number>>& _planes, Number threshold = 0);

	bool contains( const vector_t<Number> _vector ) const;
	bool contains( const Point<Number> _vector ) const;
	bool contains( const std::vector<Point<Number>>& _points) const;
	bool holds( const vector_t<Number> _vector ) const;

    Number scalar() const { return mScalar; }
    size_t hash() {
        if (this->mHash == 0) {
            this->mHash = std::hash<Halfspace<Number>>()(*this);
        }
        return mHash;
    }

	friend void swap( Halfspace<Number>& a, Halfspace<Number>& b ) {
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
	vector_t<Number> computePlaneNormal( const std::vector<vector_t<Number>>& _edgeSet ) const;
};

template<typename From, typename To>
Halfspace<To> convert(const Halfspace<From>& in) {
	return Halfspace<To>(convert<From,To>(in.normal()), carl::convert<From,To>(in.offset()));
}

template <typename Number>
std::ostream& operator<<( std::ostream& _lhs, const Halfspace<Number>& _rhs ) {
	_lhs << "( " << _rhs.normal() << "; " << Number( _rhs.offset() ) << " )";
	return _lhs;
}

template <typename Number>
bool operator==( const Halfspace<Number>& lhs, const Halfspace<Number>& rhs ) {
	return ( lhs.normal() == rhs.normal() && lhs.offset() == rhs.offset() );
}

template <typename Number>
bool operator<( const Halfspace<Number>& lhs, const Halfspace<Number>& rhs ) {
	return ( lhs.normal() < rhs.normal() || ( lhs.normal() == rhs.normal() && lhs.offset() < rhs.offset() ) );
}

template <typename Number>
Halfspace<Number> operator-( const Halfspace<Number>& _in ) {
	return Halfspace<Number>(_in).invert();
}

    #ifdef EXTERNALIZE_CLASSES
    extern template class Halfspace<double>;

    #ifdef USE_MPFR_FLOAT
    extern template class Halfspace<carl::FLOAT_T<mpfr_t>>;
    #endif

    extern template class Halfspace<carl::FLOAT_T<double>>;
    #endif
}  // namespace hypro

namespace std{
    template<class Number>
    struct hash<hypro::Halfspace<Number>> {
        std::size_t operator()(hypro::Halfspace<Number> const& Halfspace) const
        {
            size_t seed = 0;
            hypro::vector_t<Number> normal = Halfspace.normal();
            Number scalar = Halfspace.scalar();
            std::hash<hypro::vector_t<Number>> vectorHasher;
            std::hash<Number> numberHasher;
            seed = vectorHasher(normal);
            boost::hash_combine(seed, numberHasher(scalar));
            return seed;
        }
    };
} //namespace std

#include "Halfspace.tpp"
