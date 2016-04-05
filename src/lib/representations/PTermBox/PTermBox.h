/**
 * The class which represents a box.
 *
 * @file PTermBox.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since   2014-01-16
 * @version 2015-02-27
 */

#pragma once

#include <map>
#include <cassert>
#include <carl/interval/Interval.h>
#include "../../datastructures/Halfspace.h"

namespace hypro {

template <typename Number>
class PTermBox {
  private:
  public:
	/***************************************************************************
	 * Members
	 **************************************************************************/
  protected:


  public:
	/***************************************************************************
	 * Constructors
	 **************************************************************************/


	PTermBox();
	PTermBox( const PTermBox& orig );
	PTermBox( const carl::Interval<Number>& val );
	PTermBox( const std::vector<carl::Interval<Number>>& _intervals );
	PTermBox( const std::set<Point<Number>>& _points );
	PTermBox( const std::vector<Point<Number>>& _points );

	~PTermBox();

	/***************************************************************************
	 * Getters & setters
	 **************************************************************************/

	/**
	 * @brief Creates an empty box of dimension d.
	 *
	 * @param dimension The required dimension.
	 * @return The box.
	 */
	static PTermBox<Number> Empty(std::size_t dimension = 1);

	/**
	 * @brief Inserts an interval into the box - effectively increases the dimension of the box by 1.
	 *
	 * @param val The interval.
	 */
	void insert( const carl::Interval<Number>& val );
	void insert( const std::vector<carl::Interval<Number>>& boundaries );

	/**
	 * @brief Returns the current dimension of the box.
	 * @return
	 */
	std::size_t dimension() const;

	/**
	 * @brief Checks, if the box is empty.
	 * @return True, if the box is empty.
	 */
	bool empty() const;

	/**
	 * @brief Returns the maximal corner of the box (i.e. the corner with the largest coordinates per dimension).
	 * @return
	 */
	Point<Number> max() const;

	/**
	 * @brief Returns the minimal corner of the box (i.e. the corner with the smallest coordinates per dimension).
	 * @return
	 */
	Point<Number> min() const;

	/**
	 * @brief Returns a vector of all corners of the box.
	 * @return
	 */
	std::vector<Point<Number>> vertices() const;

	/**
	 * @brief Returns a vector of intervals defining the box.
	 * @return
	 */
	std::vector<carl::Interval<Number>> boundaries() const;

	PTermBox<Number>& operator=( const PTermBox<Number>& rhs );

	friend bool operator==( const PTermBox<Number>& b1, const PTermBox<Number>& b2 ) { return false; }
	friend bool operator!=( const PTermBox<Number>& b1, const PTermBox<Number>& b2 ) { return !( b1 == b2 ); }

	friend std::ostream& operator<<( std::ostream& ostr, const PTermBox<Number>& b ) { return ostr; }
	void print() const;

	/**
	 * @brief Allows access to a specific dimension i and get its boundaries.
	 * @param i Dimension
	 */
	const carl::Interval<Number>& operator[]( std::size_t i ) const;
	carl::Interval<Number>& operator[]( std::size_t i );

	/**
	 * @brief Clears the box - same as reconstructing the box with the empty default constructor.
	 */
	void clear();

	/***************************************************************************
	 * General interface
	 **************************************************************************/

	PTermBox<Number> linearTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const;
	PTermBox<Number> minkowskiSum( const PTermBox<Number>& rhs ) const;
	PTermBox<Number> intersect( const PTermBox<Number>& rhs ) const;
	bool contains( const Point<Number>& point ) const;
	bool contains( const PTermBox<Number>& box ) const;
	PTermBox<Number> unite( const PTermBox<Number>& rhs ) const;
};
}
#include "PTermBox.tpp"
