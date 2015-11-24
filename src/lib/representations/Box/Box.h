/**
 * The class which represents a box.
 *
 * @file Box.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since   2014-01-16
 * @version 2015-02-27
 */

#pragma once

#include <map>
#include <cassert>
#include <carl/interval/Interval.h>
#include "../../datastructures/Hyperplane.h"
#include "../Polytopes/VPolytope/VPolytope.h"
#include "../Polytopes/HPolytope/HPolytope.h"

namespace hypro {

template <typename Number>
class Vertex;

template <typename Number>
class VPolytope;

template <typename Number>
class Box : public hypro::GeometricObject<Number>{
  private:
  public:
	/***************************************************************************
	 * Members
	 **************************************************************************/
  protected:
    std::pair<hypro::Point<Number>, hypro::Point<Number>> mLimits;

  public:
	/***************************************************************************
	 * Constructors
	 **************************************************************************/

	/*
	 * Creates a box without any specifications
	 */
	Box() : mLimits(std::make_pair(Point<Number>(vector_t<Number>::Zero(0)), Point<Number>(vector_t<Number>::Zero(0)))) {}

	/*
	 * Creates a copy of a box?
	 * @param orig The box that's gonna be copied
	 */
	Box( const Box& orig ) : mLimits( orig.limits() ) {}

	/*
	 * Creates a box by
	 * @param var
	 * @param val
	 */
	Box( const carl::Interval<Number>& val ) {
        mLimits.first = hypro::Point<Number>({val.lower()});
        mLimits.second = hypro::Point<Number>({val.upper()});
	}

	Box( const std::pair<Point<Number>, Point<Number>>& limits) :
			mLimits(limits)
	{
		assert(limits.first.dimension() == limits.second.dimension());
	}

	Box( const std::vector<carl::Interval<Number>>& _intervals );
	Box( const matrix_t<Number>& _matrix, const vector_t<Number>& _constants );
	Box( const std::set<Point<Number>>& _points );
	Box( const std::vector<Point<Number>>& _points );
	//Box( const std::set<Vertex<Number>>& _points );
	//Box( const std::vector<Vertex<Number>>& _points );

	~Box() {}

	/***************************************************************************
	 * Getters & setters
	 **************************************************************************/

	static Box<Number> Empty(std::size_t dimension = 1) {
		return Box<Number>(std::make_pair(Point<Number>(vector_t<Number>::Ones(dimension)), Point<Number>(vector_t<Number>::Zero(dimension))));
	}

	std::vector<carl::Interval<Number>> boundaries() const;
	const std::pair<Point<Number>, Point<Number>>& limits() const { return mLimits; }
	std::vector<hypro::Hyperplane<Number>> constraints() const;

	void insert( const carl::Interval<Number>& val ) { mLimits.first.extend(val.lower()); mLimits.second.extend(val.upper());}
	//void insert( const std::vector<carl::Interval<Number>>& boundaries );

	carl::Interval<Number> interval( std::size_t d ) const;

	carl::Interval<Number> at( std::size_t _index ) const {
		if ( _index > mLimits.first.dimension() ) return carl::Interval<Number>::emptyInterval();
		return carl::Interval<Number>(mLimits.first.at(_index), mLimits.second.at(_index));
	}

	/*
	 * @return
	 */
	bool empty() const {
		if ( mLimits.first.dimension() == 0 ) return false;
		for ( std::size_t d = 0; d < mLimits.first.dimension(); ++d ) {
			if ( mLimits.first.at(d) > mLimits.second.at(d) ) {
				return true;
			}
		}
		return false;
	}

	/*
	 * @return
	 */
	Point<Number> max() const {
		return mLimits.second;
	}

	/*
	 * @return
	 */
	Point<Number> min() const {
		return mLimits.first;
	}

	Number supremum() const;

	std::vector<Point<Number>> vertices() const;

	/**
	 * Checks if two boxes are equal
	 * @param b1 Contains the first box
	 * @param b2 Contains the second box
	 * @return true, if they are equal.
	 */
	friend bool operator==( const Box<Number>& b1, const Box<Number>& b2 ) {
		if ( b1.dimension() != b2.dimension() ) return false;

		return ( b1.limits() == b2.limits());
	}

	/**
	 * @param b1
	 * @param b2
	 * @return true. if they are not equal
	 */
	friend bool operator!=( const Box<Number>& b1, const Box<Number>& b2 ) { return !( b1 == b2 ); }

	/*
	 *@param rhs
	 *@return
	 */
	Box<Number>& operator=( const Box<Number>& rhs ) {
		if ( *this != rhs ) {
			mLimits = rhs.limits();
		}
		return *this;
	}

	/**
	 *
	 * @param ostr
	 * @param b
	 * @return
	 */
	friend std::ostream& operator<<( std::ostream& ostr, const Box<Number>& b ) {
		ostr << "{ ";
		ostr << b.min() << "; " << b.max() << std::endl;
		ostr << " }";
		return ostr;
	}

	carl::Interval<Number> operator[]( unsigned i ) const { return carl::Interval<Number>(mLimits.first.at(i), mLimits.second.at(i)); }

	/***************************************************************************
	 * General interface
	 **************************************************************************/

	std::size_t dimension() const { return mLimits.first.dimension(); }

	Box<Number> linearTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const;
	Box<Number> minkowskiSum( const Box<Number>& rhs ) const;
	Box<Number> intersect( const Box<Number>& rhs ) const;
	Box<Number> intersectHyperplane( const Hyperplane<Number>& rhs ) const;
	bool contains( const Point<Number>& point ) const;
	bool contains( const Box<Number>& box ) const;
	Box<Number> unite( const Box<Number>& rhs ) const;

	void clear();
	void print() const;
};

    #ifdef EXTERNALIZE_CLASSES_ONLY_TO_TEST
    extern template class Box<double>;

    #ifdef USE_MPFR_FLOAT
    extern template class Box<carl::FLOAT_T<mpfr_t>>;
    #endif

    extern template class Box<carl::FLOAT_T<double>>;
    #endif

}
#include "Box.tpp"