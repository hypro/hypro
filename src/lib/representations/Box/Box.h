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
class Box {
  private:
  public:
	/***************************************************************************
	 * Members
	 **************************************************************************/
  protected:
	std::vector<carl::Interval<Number>> mBoundaries;

  public:
	/***************************************************************************
	 * Constructors
	 **************************************************************************/

	/*
	 * Creates a box without any specifications
	 */
	Box() : mBoundaries() {}

	/*
	 * Creates a copy of a box?
	 * @param orig The box that's gonna be copied
	 */
	Box( const Box& orig ) : mBoundaries( orig.boundaries() ) {}

	/*
	 * Creates a box by
	 * @param var
	 * @param val
	 */
	Box( const carl::Interval<Number>& val ) {
		mBoundaries.push_back(val);
	}


	Box( const std::vector<carl::Interval<Number>>& _intervals ) { mBoundaries = _intervals; }
	Box( const matrix_t<Number>& _matrix, const vector_t<Number>& _constants )
		: Box( VPolytope<Number>( _matrix, _constants ).vertices() ) {}
	Box( const std::set<Point<Number>>& _points );
	Box( const std::vector<Point<Number>>& _points );
	Box( const std::set<Vertex<Number>>& _points );
	Box( const std::vector<Vertex<Number>>& _points );

	~Box() { mBoundaries.clear(); }

	/***************************************************************************
	 * Getters & setters
	 **************************************************************************/

	static Box<Number> Empty(std::size_t dimension = 1) {
		std::vector<carl::Interval<Number>> intervals(dimension, carl::Interval<Number>::emptyInterval());
		return Box<Number>(std::move(intervals));
	}

	std::vector<carl::Interval<Number>>& rBoundaries() { return mBoundaries; }
	const std::vector<carl::Interval<Number>>& boundaries() const { return mBoundaries; }
	std::vector<hypro::Hyperplane<Number>> constraints() const;

	void insert( const carl::Interval<Number>& val ) { mBoundaries.push_back(val); }
	void insert( const std::vector<carl::Interval<Number>>& boundaries ) { mBoundaries.insert(mBoundaries.end(), boundaries.begin(), boundaries.end()); }

	/*
	 * Checks if the box has the same dimension as the variable.
	 * @param var
	 * @return
	 */
	bool hasDimension( std::size_t d ) const {
		return (mBoundaries.size() >= d);
	}

	/**
	 * Checks if the box has the same dimensions as this box.
	 * The number of dimensions has to be equal as well as the actual
	 * variables used for those dimensions.
	 *
	 * @param p
	 * @return True, if all dimension variables are equal
	 */
	bool haveSameDimensions( const Box<Number>& b ) const {
		if ( dimension() != b.dimension() ) {
			return false;
		}
		return true;
	}

	carl::Interval<Number> interval( std::size_t d ) const;
	carl::Interval<Number>& rInterval( std::size_t d );

	carl::Interval<Number> at( std::size_t _index ) const {
		if ( _index > mBoundaries.size() ) return carl::Interval<Number>::emptyInterval();
		return mBoundaries[_index];
	}

	/*
	 * @return
	 */
	bool empty() const {
		if ( mBoundaries.size() == 0 ) return false;
		for ( auto interval : mBoundaries ) {
			if ( interval.isEmpty() ) {
				return true;
			}
		}
		return false;
	}

	/*
	 * @return
	 */
	Point<Number> max() const {
		vector_t<Number> coordinates = vector_t<Number>( mBoundaries.size() );
		for ( unsigned i = 0; i < mBoundaries.size(); ++i ) {
			coordinates( i ) = mBoundaries[i].upper();
		}
		return Point<Number>( coordinates );
	}

	/*
	 * @return
	 */
	Point<Number> min() const {
		vector_t<Number> coordinates = vector_t<Number>( mBoundaries.size() );
		for ( unsigned i = 0; i < mBoundaries.size(); ++i ) {
			coordinates( i ) = mBoundaries[i].lower();
		}
		return Point<Number>( coordinates );
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
		for ( unsigned i = 0; i < b1.boundaries().size(); ++i ) {
			if ( b1.at( i ) != b2.at( i ) ) return false;
		}
		return true;
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
			this->mBoundaries.clear();
			mBoundaries = rhs.boundaries();
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
		ostr << "{";
		for ( unsigned i = 0; i < b.dimension(); ++i ) {
			if ( i != 0 ) {
				ostr << ";";
			}
			ostr << " " << b.at( i );
		}
		ostr << " }";
		return ostr;
	}

	const carl::Interval<Number>& operator[]( unsigned i ) const { return mBoundaries.at(i); }

	carl::Interval<Number>& operator[]( unsigned i ) { return mBoundaries.at(i); }

	/***************************************************************************
	 * General interface
	 **************************************************************************/

	std::size_t dimension() const { return mBoundaries.size(); }

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
}
#include "Box.tpp"
