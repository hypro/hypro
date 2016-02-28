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

namespace hypro {

template <typename Number>
class Vertex;

template <typename Number, typename Converter>
class BoxT {
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
	BoxT() : mLimits(std::make_pair(Point<Number>(vector_t<Number>::Zero(0)), Point<Number>(vector_t<Number>::Zero(0)))) {}

	/*
	 * Creates a copy of a box
	 * @param orig The box that's gonna be copied
	 */
	BoxT( const BoxT& orig ) : mLimits( orig.limits() ) {}

	BoxT( BoxT&& orig ) : mLimits( std::move(orig.mLimits )) {}

	/*
	 * Creates a box by
	 * @param var
	 * @param val
	 */
	BoxT( const carl::Interval<Number>& val ) {
        mLimits.first = hypro::Point<Number>({val.lower()});
        mLimits.second = hypro::Point<Number>({val.upper()});
	}

	BoxT( const std::pair<Point<Number>, Point<Number>>& limits) :
			mLimits(limits)
	{
		assert(limits.first.dimension() == limits.second.dimension());
	}

	BoxT( const std::vector<carl::Interval<Number>>& _intervals );
	BoxT( const matrix_t<Number>& _matrix, const vector_t<Number>& _constants );
	BoxT( const std::set<Point<Number>>& _points );
	BoxT( const std::vector<Point<Number>>& _points );
	//BoxT( const std::set<Vertex<Number>>& _points );
	//BoxT( const std::vector<Vertex<Number>>& _points );

	~BoxT() {}

	/***************************************************************************
	 * Getters & setters
	 **************************************************************************/

	static BoxT<Number,Converter> Empty(std::size_t dimension = 1) {
		return BoxT<Number,Converter>(std::make_pair(Point<Number>(vector_t<Number>::Ones(dimension)), Point<Number>(vector_t<Number>::Zero(dimension))));
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
	friend bool operator==( const BoxT<Number,Converter>& b1, const BoxT<Number,Converter>& b2 ) {
		if ( b1.dimension() != b2.dimension() ) return false;

		return ( b1.limits() == b2.limits());
	}

	/**
	 * @param b1
	 * @param b2
	 * @return true. if they are not equal
	 */
	friend bool operator!=( const BoxT<Number,Converter>& b1, const BoxT<Number,Converter>& b2 ) { return !( b1 == b2 ); }

	/*
	 *@param rhs
	 *@return
	 */
	BoxT<Number,Converter>& operator=( const BoxT<Number,Converter>& rhs ) {
		if ( *this != rhs ) {
			BoxT<Number,Converter> tmp(rhs);
			std::swap(*this, tmp);
		}
		return *this;
	}

	BoxT<Number,Converter>& operator=(BoxT<Number,Converter>&& rhs) {
		if ( *this != rhs ) {
			mLimits = std::move(rhs.limits());
		}
		return *this;
	}

	/**
	 *
	 * @param ostr
	 * @param b
	 * @return
	 */
	friend std::ostream& operator<<( std::ostream& ostr, const BoxT<Number,Converter>& b ) {
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

	BoxT<Number,Converter> linearTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const;
	BoxT<Number,Converter> minkowskiSum( const BoxT<Number,Converter>& rhs ) const;
	BoxT<Number,Converter> intersect( const BoxT<Number,Converter>& rhs ) const;
	BoxT<Number,Converter> intersectHyperplane( const Hyperplane<Number>& rhs ) const;
	bool contains( const Point<Number>& point ) const;
	bool contains( const BoxT<Number,Converter>& box ) const;
	BoxT<Number,Converter> unite( const BoxT<Number,Converter>& rhs ) const;

	void clear();
	void print() const;
};

    #ifdef EXTERNALIZE_CLASSES_ONLY_TO_TEST
    extern template class BoxT<double>;

    #ifdef USE_MPFR_FLOAT
    extern template class BoxT<carl::FLOAT_T<mpfr_t>>;
    #endif

    extern template class BoxT<carl::FLOAT_T<double>>;
    #endif

}

#include "Box.tpp"