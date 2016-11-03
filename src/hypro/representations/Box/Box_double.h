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

#include "Box.h"

namespace hypro {

template <typename Converter>
class BoxT<double,Converter> : public GeometricObject<double, BoxT<double,Converter>> {
  private:
  public:
	/***************************************************************************
	 * Members
	 **************************************************************************/
  protected:
    mutable std::pair<Point<double>, Point<double>> mLimits; /*!< Pair of points describing the minimal and the maximal point of the box.*/

  public:
	/***************************************************************************
	 * Constructors
	 **************************************************************************/

	/**
	 * @brief      Creates an empty box.
	 * @details   The empty box is represented by a zero-dimensional point pair.
	 */
	BoxT() : mLimits(std::make_pair(Point<double>(vector_t<double>::Zero(0)), Point<double>(vector_t<double>::Zero(0)))) {}

	/**
	 * @brief      Copy constructor.
	 * @param[in]  orig  The original.
	 */
	BoxT( const BoxT& orig ) = default;

	/**
	 * @brief      Move constructor.
	 * @param[in]  orig  The move-copyable original.
	 */
	BoxT( BoxT&& orig ) = default;

	 /**
	  * @brief      Box constructor from one interval, results in a one-dimensional box.
	  * @param[in]  val   An interval.
	  */
	explicit BoxT( const carl::Interval<double>& val ) {
        mLimits.first = Point<double>({val.lower()});
        mLimits.second = Point<double>({val.upper()});
	}

	/**
	 * @brief Box constructor from a pair of points.
	 * @details The given parameters are considered as the maximal and minimal point.
	 * The constructor does not check the order of points.
	 * @param limits Pair of points.
	 */
	explicit BoxT( const std::pair<Point<double>, Point<double>>& limits) :
			mLimits(limits)
	{
		assert(limits.first.dimension() == limits.second.dimension());
	}

	/**
	 * @brief Constructor from a vector of intervals.
	 * @details The vector is required to be sorted, i.e. the first interval maps to the first dimension etc..
	 * @param _intervals A vector of intervals.
	 */
	explicit BoxT( const std::vector<carl::Interval<double>>& _intervals );

	/**
	 * @brief Constructor from a matrix and a vector.
	 * @details Constructs a box assuming each row of the matrix is the normal to a hyperplane and its corresponding
	 * entry in the given vector is the offset.
	 * @param _constraints A matrix representing the constraint normals.
	 * @param _constants A vector representing the offsets of the corresponting hyperplane.
	 */
	BoxT( const matrix_t<double>& _constraints, const vector_t<double>& _constants );

	/**
	 * @brief Constructor from a set of points.
	 * @details The constructor does not rely on the operator < of the point class, thus each point is considered
	 * for the construction of the maximal and minimal point.
	 * @param _points A set of points.
	 */
	explicit BoxT( const std::set<Point<double>>& _points );

	/**
	 * @brief A constructor from a vector of points.
	 * @details Creates the maximal and minimal point by collecting all coordinates from all given points.
	 * @param _points A vector of points.
	 */
	explicit BoxT( const std::vector<Point<double>>& _points );

	/**
	 * @brief Destructor.
	 */
	~BoxT() {}

	/***************************************************************************
	 * Getters & setters
	 **************************************************************************/

	 /**
	  * @brief Static method for the construction of an empty box of required dimension.
	  * @param dimension Required dimension.
	  * @return Empty box.
	  */
	static BoxT<double,Converter> Empty(std::size_t dimension = 1) {
		return BoxT<double,Converter>(std::make_pair(Point<double>(vector_t<double>::Ones(dimension)), Point<double>(vector_t<double>::Zero(dimension))));
	}

	/**
	 * @brief Getter for interval representation of the current box.
	 * @details Converts the two-points representation of the current box into a sorted vector of intervals.
	 * @return A vector of intervals.
	 */
	std::vector<carl::Interval<double>> boundaries() const;

	/**
	 * @brief Getter for the limiting points.
	 * @return A pair of points.
	 */
	const std::pair<Point<double>, Point<double>>& limits() const { return mLimits; }

	matrix_t<double> matrix() const;
	vector_t<double> vector() const;

	/**
	 * @brief Getter for the hyperplanar representation of the current box.
	 * @details Converts the two-points representation into a hyperplanar representation, i.e. a H-polytope.
	 * @return A vector of hyperplanes.
	 */
	std::vector<Halfspace<double>> constraints() const;

	/**
	 * @brief Extends the dimension of the current box by the given interval.
	 * @details Effectively extends the dimension of the current box.
	 * @param val An interval.
	 */
	void insert( const carl::Interval<double>& val ) { mLimits.first.extend(val.lower()); mLimits.second.extend(val.upper());}

	/**
	 * @brief Getter for an interval representation of one specific dimension.
	 * @details Converts the d-th entries in the maximal and minimal point to an interval.
	 * @param d The queried dimension.
	 * @return An interval.
	 */
	carl::Interval<double> interval( std::size_t d ) const;

	/**
	 * @brief Getter for an interval representation of one specific dimension.
	 * @details Converts the d-th entries in the maximal and minimal point to an interval.
	 * @param d The queried dimension.
	 * @return An interval.
	 */
	carl::Interval<double> at( std::size_t _index ) const {
		if ( _index > mLimits.first.dimension() ) {
			return carl::Interval<double>::emptyInterval();
		}
		return carl::Interval<double>(mLimits.first.at(_index), mLimits.second.at(_index));
	}

	/**
	 * @brief Determines if the current box is empty.
	 * @details The method checks the dimension of the limit points and afterwards each interval for emptiness.
	 * @return True, if one interval is empty. False if the dimension is 0 or no interval is empty.
	 */
	bool empty() const {
		assert(mLimits.first.dimension() == mLimits.second.dimension());
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

	/**
	 * @brief      Determines if the current box is symmetric.
	 * @details    A box is symmetric, if its centroid is the origin in the respective space, i.e. if the center of each interval in each
	 * dimension is zero.
	 * @return     True if symmetric, False otherwise.
	 */
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
	Point<double> max() const {
		return mLimits.second;
	}

	/**
	 * @brief Getter for the maximal point.
	 * @return A point.
	 */
	Point<double> min() const {
		return mLimits.first;
	}

	/**
	 * @brief Method returning the supremum point of the box, i.e. the maximal point.
	 * @return A point representing the supremum of the current box.
	 */
	double supremum() const;

	/**
	 * @brief Getter for a vertex-representation of the current box.
	 * @details Converts the current box from its two-point representation into a vertex representation, i.e. a V-polytope.
	 * The representation is generated by creating all possible combinations of upper and lower bounds of the box.
	 * @return A vector of points.
	 */
	std::vector<Point<double>> vertices( const Location<double>* = nullptr ) const;

	/**
	 * @brief Checks if two boxes are equal.
	 * @param b1 Contains the first box.
	 * @param b2 Contains the second box.
	 * @return True, if they are equal.
	 */
	friend bool operator==( const BoxT<double,Converter>& b1, const BoxT<double,Converter>& b2 ) {
		if ( b1.dimension() != b2.dimension() ) {
			return false;
		}
		return ( b1.limits() == b2.limits());
	}

	/**
	 * @brief Determines inequality of two boxes.
	 * @param b1 A box.
	 * @param b2 A box.
	 * @return False, if both boxes are equal.
	 */
	friend bool operator!=( const BoxT<double,Converter>& b1, const BoxT<double,Converter>& b2 ) { return !( b1 == b2 ); }

	/**
	 * @brief Assignment operator.
	 * @param rhs A box.
	 */
	BoxT<double,Converter>& operator=( const BoxT<double,Converter>& rhs ) = default;

	/**
	 * @brief Move assignment operator.
	 * @param rhs A box.
	 */
	BoxT<double,Converter>& operator=(BoxT<double,Converter>&& rhs) = default;

	/**
	 * @brief      Scaling operator.
	 * @param[in]  factor  The scaling factor.
	 * @return     The scaled box.
	 */
	BoxT<double,Converter> operator*(const double& factor) const { return BoxT<double,Converter>(std::make_pair(factor*mLimits.first, factor*mLimits.second));}

	/**
	 * @brief Outstream operator.
	 * @param ostr Outstream.
	 * @param b A box.
	 */
	friend std::ostream& operator<<( std::ostream& ostr, const BoxT<double,Converter>& b ) {
		ostr << "{ ";
		ostr << b.min() << "; " << b.max() << std::endl;
		ostr << " }";
		return ostr;
	}

	/**
	 * @brief Access operator (const).
	 * @param i Dimension to access.
	 * @return An interval.
	 */
	carl::Interval<double> operator[]( unsigned i ) const { return carl::Interval<double>(mLimits.first.at(i), mLimits.second.at(i)); }

	/***************************************************************************
	 * General interface
	 **************************************************************************/

	 /**
	  * @brief      Getter for the space dimension.
	  * @return     The dimension of the space.
	  */
	std::size_t dimension() const { return mLimits.first.dimension(); }

	static representation_name type() { return representation_name::box; }

	/**
	 * @brief      Removes redundancy (part of the general interface. Does nothing for boxes.)
	 */
	void removeRedundancy() {}

	/**
	 * @brief      Storage size determination.
	 * @return     Size of the required memory.
	 */
	std::size_t size() const;

	/**
	 * @brief Empty function for number size reduction, which is omitted when using native double numbers.
	 * @param limit Parameter for a length estimation.
	 */
	void reducedoubleRepresentation(unsigned limit = fReach_DENOMINATOR) const {}

	/**
	 * @brief      Makes a symmetric box from the current box.
	 * @details    The symmetry is obtained by dimension-wise extension of the boundaries. The resulting boundaries for each dimension
	 * are the maximal absolute values of the original boundaries mirrored positive and negative.
	 * @return     The resulting symmetric box.
	 */
	BoxT<double,Converter> makeSymmetric() const;

	/**
	 * @brief      Checks, if the box lies inside the given halfspace.
	 * @details    This function combines the intersection with a given halfspace along with the emptiness test on the result, which is
	 * often faster than the sequential execution of both commands.
	 * @param[in]  rhs  The halfspace.
	 * @return     A pair of a Boolean value and a box. The Boolean is true in case the resulting box is not empty and false otherwise.
	 */
	std::pair<bool, BoxT> satisfiesHalfspace( const Halfspace<double>& rhs ) const;

	/**
	 * @brief      Checks, if the box lies inside the given set of halfspaces.
	 * @details    This function combines the intersection with a given set of halfspaces along with the emptiness test on the result, which is
	 * often faster than the sequential execution of both commands.
	 * @param[in]  _mat  The normals of the halfspaces.
	 * @param[in]  _vec  The offsets of the halfspaces.
	 * @return     A pair of a Boolean value and a box. The Boolean is true in case the resulting box is not empty and false otherwise.
	 */
	std::pair<bool, BoxT> satisfiesHalfspaces( const matrix_t<double>& _mat, const vector_t<double>& _vec ) const;

	/**
	 * @brief      Projects the box onto the given dimensions.
	 * @param[in]  dimensions  The dimensions.
	 * @return     The projected box.
	 */
	BoxT<double,Converter> project(const std::vector<unsigned>& dimensions) const;

	/**
	 * @brief      Applies a linear transformation to the box.
	 * @details    The transformation is done on the two limit points directly. TODO: Add more extensive description here.
	 * @param[in]  A     A matrix for the linear transformation.
	 * @return     The resulting box.
	 */
	BoxT<double,Converter> linearTransformation( const matrix_t<double>& A ) const;

	/**
	 * @brief      Applies an affine transformation to the box.
	 * @details    The transformation is done on the two limit points directly. TODO: Add more extensive description here.
	 * @param[in]  A     A matrix for the affine transformation.
	 * @param[in]  b     A vector for the offset.
	 * @return     The resulting box.
	 */
	BoxT<double,Converter> affineTransformation( const matrix_t<double>& A, const vector_t<double>& b ) const;

	/**
	 * @brief      Computes the Minkowski sum of two boxes.
	 * @param[in]  rhs   The right hand side box.
	 * @return     The resulting box.
	 */
	BoxT<double,Converter> minkowskiSum( const BoxT<double,Converter>& rhs ) const;

	/**
	 * @brief      Computes the Minkowski decomposition of the current box by the given box.
	 * @param[in]  rhs   The right hand side box.
	 * @return     The resulting box.
	 */
	BoxT<double,Converter> minkowskiDecomposition( const BoxT<double,Converter>& rhs ) const;

	/**
	 * @brief      Computes the intersection of two boxes.
	 * @param[in]  rhs   The right hand side box.
	 * @return     The resulting box.
	 */
	BoxT<double,Converter> intersect( const BoxT<double,Converter>& rhs ) const;

	/**
	 * @brief      Computes the intersection of the current box with a given halfspace.
	 * @param[in]  hspace  The halfspace.
	 * @return     The resulting box.
	 */
	BoxT<double,Converter> intersectHalfspace( const Halfspace<double>& hspace ) const;

	/**
	 * @brief      Computes the intersection of the current box with a set of halfspaces.
	 * @param[in]  _mat  The matrix representing the normal vectors.
	 * @param[in]  _vec  The vector representing the offsets.
	 * @return     The resulting box.
	 */
	BoxT<double,Converter> intersectHalfspaces( const matrix_t<double>& _mat, const vector_t<double>& _vec ) const;

	/**
	 * @brief      Containment check for a point.
	 * @param[in]  point  The point.
	 * @return     True, if the point is contained inside the current box, false otherwise.
	 */
	bool contains( const Point<double>& point ) const;

	/**
	 * @brief      Containment check for a box.
	 * @param[in]  box   The box.
	 * @return     True, if the given box is contained in the current box, false otherwise.
	 */
	bool contains( const BoxT<double,Converter>& box ) const;

	/**
	 * @brief      Computes the union of two boxes.
	 * @param[in]  rhs   The right hand side box.
	 * @return     The resulting box.
	 */
	BoxT<double,Converter> unite( const BoxT<double,Converter>& rhs ) const;

	/**
	 * @brief      Computes the union of the current box with a set of boxes.
	 * @param[in]  boxes  The boxes.
	 * @return     The resulting box.
	 */
	BoxT<double,Converter> unite( const std::vector<BoxT<double,Converter>>& boxes ) const;

	/**
	 * @brief      Makes this box the empty box.
	 */
	void clear();

	/**
	 * @brief      A deprecated print method. Use the outstream operator.
	 */
	void print() const;
};

} // namespace hypro

#include "Box_double.tpp"
