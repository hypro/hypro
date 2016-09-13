/**
 * The class which represents a box. A box is represented by two points, its maximal and its minimal vertex.
 *
 * @file Box.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since   2014-01-16
 * @version 2015-02-27
 */

#pragma once

#include "../../datastructures/Halfspace.h"
#include "../../datastructures/Point.h"
#include "../../util/Permutator.h"
#include "../../util/linearOptimization/Optimizer.h"
#include <carl/interval/Interval.h>
#include <cassert>
#include <map>
#include <set>
#include <vector>

namespace hypro {

template <typename Number>
class Vertex;

template<typename Number>
class Location;

template <typename Number, typename Converter>
class BoxT {
  private:
  public:
	/***************************************************************************
	 * Members
	 **************************************************************************/
  protected:
    mutable std::pair<Point<Number>, Point<Number>> mLimits;

  public:
	/***************************************************************************
	 * Constructors
	 **************************************************************************/

	/*
	 * Creates an unbounded box.
	 */
	BoxT() : mLimits(std::make_pair(Point<Number>(vector_t<Number>::Zero(0)), Point<Number>(vector_t<Number>::Zero(0)))) {}

	/*
	 * Copy constructor.
	 * @param orig The original box.
	 */
	BoxT( const BoxT& orig ) = default;
	BoxT( BoxT&& orig ) = default;

	/*
	 * Box constructor from one interval, results in a one-dimensional box.
	 * @param val Input interval.
	 */
	explicit BoxT( const carl::Interval<Number>& val ) {
        mLimits.first = Point<Number>({val.lower()});
        mLimits.second = Point<Number>({val.upper()});
	}

	/**
	 * @brief Box constructor from a pair of points.
	 * @details The given parameters are considered as the maximal and minimal point.
	 * The constructor does not check the order of points.
	 *
	 * @param limits Pair of points.
	 */
	explicit BoxT( const std::pair<Point<Number>, Point<Number>>& limits) :
			mLimits(limits)
	{
		assert(limits.first.dimension() == limits.second.dimension());
	}

	/**
	 * @brief Constructor from a vector of intervals.
	 * @details The vector is required to be sorted, i.e. the first interval maps to the first dimension etc..
	 *
	 * @param _intervals Vector of intervals.
	 */
	explicit BoxT( const std::vector<carl::Interval<Number>>& _intervals );

	/**
	 * @brief Constructor from a matrix and a vector.
	 * @details Constructs a box assuming each row of the matrix is the normal to a hyperplane and its corresponding
	 * entry in the given vector is the offset.
	 *
	 * @param _constraints A matrix representing the constraint normals.
	 * @param _constants A vector representing the offsets of the corresponting hyperplane.
	 */
	BoxT( const matrix_t<Number>& _constraints, const vector_t<Number>& _constants );

	/**
	 * @brief Constructor from a set of points.
	 * @details The constructor does not rely on the operator < of the point class, thus each point is considered
	 * for the construction of the maximal and minimal point.
	 *
	 * @param _points A set of points.
	 */
	explicit BoxT( const std::set<Point<Number>>& _points );

	/**
	 * @brief A constructor from a vector of points.
	 * @details Creates the maximal and minimal point by collecting all coordinates from all given points.
	 *
	 * @param _points A vector of points.
	 */
	explicit BoxT( const std::vector<Point<Number>>& _points );

	/**
	 * @brief Destructor.
	 */
	~BoxT() {}

	/***************************************************************************
	 * Getters & setters
	 **************************************************************************/

	 /**
	  * @brief Static method for the construction of an empty box of required dimension.
	  *
	  * @param dimension Required dimension.
	  * @return Empty box.
	  */
	static BoxT<Number,Converter> Empty(std::size_t dimension = 1) {
		return BoxT<Number,Converter>(std::make_pair(Point<Number>(vector_t<Number>::Ones(dimension)), Point<Number>(vector_t<Number>::Zero(dimension))));
	}

	/**
	 * @brief Getter for interval representation of the current box.
	 * @details Converts the two-points representation of the current box into a sorted vector of intervals.
	 * @return A vector of intervals.
	 */
	std::vector<carl::Interval<Number>> boundaries() const;

	/**
	 * @brief Getter for the limiting points.
	 * @return A pair of points.
	 */
	const std::pair<Point<Number>, Point<Number>>& limits() const { return mLimits; }

	matrix_t<Number> matrix() const;
	vector_t<Number> vector() const;

	/**
	 * @brief Getter for the hyperplanar representation of the current box.
	 * @details Converts the two-points representation into a hyperplanar representation, i.e. a H-polytope.
	 * @return A vector of hyperplanes.
	 */
	std::vector<Halfspace<Number>> constraints() const;

	/**
	 * @brief Extends the dimension of the current box by the given interval.
	 * @details Effectively extends the dimension of the current box.
	 *
	 * @param val An interval.
	 */
	void insert( const carl::Interval<Number>& val ) { mLimits.first.extend(val.lower()); mLimits.second.extend(val.upper());}

	/**
	 * @brief Getter for an interval representation of one specific dimension.
	 * @details Converts the d-th entries in the maximal and minimal point to an interval.
	 *
	 * @param d The queried dimension.
	 * @return An interval.
	 */
	carl::Interval<Number> interval( std::size_t d ) const;

	/**
	 * @brief Getter for an interval representation of one specific dimension.
	 * @details Converts the d-th entries in the maximal and minimal point to an interval.
	 *
	 * @param d The queried dimension.
	 * @return An interval.
	 */
	carl::Interval<Number> at( std::size_t _index ) const {
		if ( _index > mLimits.first.dimension() ) {
			return carl::Interval<Number>::emptyInterval();
		}
		return carl::Interval<Number>(mLimits.first.at(_index), mLimits.second.at(_index));
	}

	/**
	 * @brief Determines if the current box is empty.
	 * @details The method checks the dimension of the limit points and afterwards each interval for emptiness.
	 * @return True, if one interval is empty. False if the dimension is 0 or no interval is empty.
	 */
	bool empty() const {
		if ( mLimits.first.dimension() == 0 ) {
			return false;
		}
		for ( std::size_t d = 0; d < mLimits.first.dimension(); ++d ) {
			if ( mLimits.first.at(d) > mLimits.second.at(d) ) {
				return true;
			}
		}
		return false;
	}

	bool isSymmetric() const {
		if ( mLimits.first.dimension() == 0 ) {
			return true;
		}
		for ( std::size_t d = 0; d < mLimits.first.dimension(); ++d ) {
			if ( mLimits.first.at(d) != -mLimits.second.at(d) ) {
				return false;
			}
		}
		return true;
	}

	/**
	 * @brief Getter for the maximal point.
	 * @return A point.
	 */
	Point<Number> max() const {
		return mLimits.second;
	}

	/**
	 * @brief Getter for the maximal point.
	 * @return A point.
	 */
	Point<Number> min() const {
		return mLimits.first;
	}

	/**
	 * @brief Method returning the supremum point of the box, i.e. the maximal point.
	 * @return A point representing the supremum of the current box.
	 */
	Number supremum() const;

	/**
	 * @brief Getter for a vertex-representation of the current box.
	 * @details Converts the current box from its two-point representation into a vertex representation, i.e. a V-polytope.
	 * The representation is generated by creating all possible combinations of upper and lower bounds of the box.
	 * @return A vector of points.
	 */
	std::vector<Point<Number>> vertices( const Location<Number>* = nullptr ) const;

	/**
	 * @brief Checks if two boxes are equal.
	 * @param b1 Contains the first box.
	 * @param b2 Contains the second box.
	 * @return True, if they are equal.
	 */
	friend bool operator==( const BoxT<Number,Converter>& b1, const BoxT<Number,Converter>& b2 ) {
		if ( b1.dimension() != b2.dimension() ) {
			return false;
		}
		return ( b1.limits() == b2.limits());
	}

	/**
	 * @brief Determines inequality of two boxes.
	 *
	 * @param b1 A box.
	 * @param b2 A box.
	 * @return False, if both boxes are equal.
	 */
	friend bool operator!=( const BoxT<Number,Converter>& b1, const BoxT<Number,Converter>& b2 ) { return !( b1 == b2 ); }

	/**
	 * @brief Assignment operator.
	 *
	 * @param rhs A box.
	 */
	BoxT<Number,Converter>& operator=( const BoxT<Number,Converter>& rhs ) = default;

	/**
	 * @brief Move assignment operator.
	 *
	 * @param rhs A box.
	 */
	BoxT<Number,Converter>& operator=(BoxT<Number,Converter>&& rhs) = default;

	BoxT<Number,Converter> operator*(const Number& factor) const { return BoxT<Number,Converter>(std::make_pair(factor*mLimits.first, factor*mLimits.second));}

	/**
	 * @brief Outstream operator.
	 *
	 * @param ostr Outstream.
	 * @param b A box.
	 */
	friend std::ostream& operator<<( std::ostream& ostr, const BoxT<Number,Converter>& b ) {
		ostr << "{ ";
		ostr << b.min() << "; " << b.max() << std::endl;
		ostr << " }";
		return ostr;
	}

	/**
	 * @brief Access operator (const).
	 *
	 * @param i Dimension to access.
	 * @return An interval.
	 */
	carl::Interval<Number> operator[]( unsigned i ) const { return carl::Interval<Number>(mLimits.first.at(i), mLimits.second.at(i)); }

	/***************************************************************************
	 * General interface
	 **************************************************************************/

	std::size_t dimension() const { return mLimits.first.dimension(); }
	void removeRedundancy() {}
	std::size_t size() const;

	template<typename N = Number, carl::DisableIf< std::is_same<N, double> > = carl::dummy>
	void reduceNumberRepresentation(unsigned limit = fReach_DENOMINATOR) const {
		Number limit2 = Number(limit)*Number(limit);
		for(unsigned d = 0; d < this->dimension(); ++d) {
			//std::cout << "(Upper Bound) Number: " << mLimits.second.at(d) << std::endl;
			if(mLimits.second.at(d) != 0) {
				Number numerator = carl::getNum(mLimits.second.at(d));
				Number denominator = carl::getDenom(mLimits.second.at(d));
				Number largest = carl::abs(numerator) > carl::abs(denominator) ? carl::abs(numerator) : carl::abs(denominator);
				if(largest > limit2){
					Number dividend = largest / Number(limit);
					assert(largest/dividend == limit);
					Number val = Number(carl::ceil(numerator/dividend));
					Number newDenom;
					if(mLimits.second.at(d) > 0) {
						newDenom = Number(carl::floor(denominator/dividend));
					} else {
						newDenom = Number(carl::ceil(denominator/dividend));
					}
					if(newDenom != 0) {
						val = val / newDenom;
						assert(val >= mLimits.second.at(d));
						mLimits.second[d] = val;
					}
					//std::cout << "Assert: " << val << " >= " << mLimits.second.at(d) << std::endl;
					//std::cout << "(Upper bound) Rounding Error: " << carl::convert<Number,double>(val - mLimits.second.at(d)) << std::endl;
				}
			}

			//std::cout << "(Lower Bound) Number: " << mLimits.first.at(d) << std::endl;
			if(mLimits.first.at(d) != 0) {
				Number numerator = carl::getNum(mLimits.first.at(d));
				Number denominator = carl::getDenom(mLimits.first.at(d));
				Number largest = carl::abs(numerator) > carl::abs(denominator) ? carl::abs(numerator) : carl::abs(denominator);
				if(largest > limit2){
					Number dividend = largest / Number(limit);
					assert(largest/dividend == limit);
					Number val = Number(carl::floor(numerator/dividend));
					Number newDenom;
					if( mLimits.first.at(d) > 0) {
						newDenom = Number(carl::ceil(denominator/dividend));
					} else {
						newDenom = Number(carl::floor(denominator/dividend));
					}
					if(newDenom != 0) {
						val = val / newDenom;
						assert(val <= mLimits.first.at(d));
						mLimits.first[d] = val;
					}
					//std::cout << "Assert: " << val << " <= " << mLimits.first.at(d) << std::endl;
					//std::cout << "(Lower bound) Rounding Error: " << carl::convert<Number,double>(val - mLimits.first.at(d)) << std::endl;
				}
			}
		}
	}

	template<typename N = Number, carl::EnableIf< std::is_same<N,double> > = carl::dummy>
	void reduceNumberRepresentation(unsigned limit = fReach_DENOMINATOR) const {}


	BoxT<Number,Converter> makeSymmetric() const;
	std::pair<bool, BoxT> satisfiesHalfspace( const vector_t<Number>& normal, const Number& offset ) const;
	std::pair<bool, BoxT> satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const;
	BoxT<Number,Converter> linearTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const;
	BoxT<Number,Converter> minkowskiSum( const BoxT<Number,Converter>& rhs ) const;
	BoxT<Number,Converter> minkowskiDecomposition( const BoxT<Number,Converter>& rhs ) const;
	BoxT<Number,Converter> intersect( const BoxT<Number,Converter>& rhs ) const;
	BoxT<Number,Converter> intersectHalfspace( const Halfspace<Number>& hspace ) const;
	BoxT<Number,Converter> intersectHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const;
	bool contains( const Point<Number>& point ) const;
	bool contains( const BoxT<Number,Converter>& box ) const;
	BoxT<Number,Converter> unite( const BoxT<Number,Converter>& rhs ) const;
	BoxT<Number,Converter> unite( const std::vector<BoxT<Number,Converter>>& boxes ) const;

	void clear();
	void print() const;
};

template<typename Number,typename Converter>
BoxT<Number,Converter> operator*(Number factor, const BoxT<Number,Converter>& in) {
	return in*factor;
}

template<typename From, typename To, typename Converter>
BoxT<To,Converter> convert(const BoxT<From,Converter>& in) {
	std::pair<Point<From>, Point<From>> limits = in.limits();
	return BoxT<To,Converter>(std::make_pair(Point<To>(convert<From,To>(limits.first.rawCoordinates())), Point<To>(convert<From,To>(limits.second.rawCoordinates()))));
}


} // namespace hypro

#include "Box.tpp"
