/**
 * The point class is the basis for all implementation. It consists of a vector
 * of coordinates which forms a point in a n-dimensional space.
 * @file   Point.h
 *
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @author Sebastian Junges
 * @author Benedikt Seidl
 *
 *
 * @since	2011-01-17
 * @version	2015-08-27
 */
#pragma once

#include "../types.h"
#include "../config.h"
#include "../util/VariablePool.h"
#include <set>
#include <vector>

namespace hypro {
/*
 *  Class to store points in a MAXIMAL_DIMENSION space.
 */
template <class Number>
class Point {
  public:
	using pointSet = std::set<Point<Number>>;
	using coordinateMap = std::map<carl::Variable, Number>;

  private:
	vector_t<Number> mCoordinates;
	mutable std::size_t mHash;

	// Adjacency List of this Point (if applicable)
	// std::vector<Point<Number>> mNeighbors;
	// Minkowsi Decompositon of this point (if applicable)
	std::vector<Point<Number>> mComposedOf;

  public:
	static const int POINT_RAND_MAX = 100;

	/**
	 * Constructors & Destructor
	 */

	Point();

	/**
	 * Constructs a point with the passed dimension and sets the coordinates to the initial value.
	 * @param dim
	 * @param initialValue
	 */
	explicit Point( const Number& _value );
	explicit Point( std::initializer_list<Number> _coordinates );

	//@author Chris K. (for Minkowski Sum Test)
	explicit Point( std::vector<Number> _coordinates );

	/**
	 * Constructs a point with the passed coordinates
             * @param coordinates
	 */
	explicit Point( const vector_t<Number>& _vector );
	explicit Point( vector_t<Number>&& _vector );

	/**
	 * Copy constructor
	 * @param p
	 */
	Point( const Point<Number>& _p );
	Point( Point<Number>&& _p );

	template <typename F, carl::DisableIf<std::is_same<F, Number>> = carl::dummy>
	explicit Point( const Point<F>& _p ) {
		mCoordinates = vector_t<Number>( _p.coordinates().size() );
		for ( unsigned pos = 0; pos < _p.dimension(); ++pos ) {
			mCoordinates( pos ) = Number( _p.at( pos ) );
		}
		mHash = 0;
	}

	virtual ~Point() {}

	/**
	 * Getter & Setter
	 */

	std::size_t hash() const {
		if(mHash == 0) {
			mHash = std::hash<vector_t<Number>>()(mCoordinates);
		}
		return mHash;
	}

	void extend(const Number& val) {
		mCoordinates.conservativeResize(mCoordinates.rows() +1);
		mCoordinates(mCoordinates.rows()-1) = val;
        mHash = 0;
	}

	std::vector<Point<Number>> composedOf() const;
	void setComposition( const std::vector<Point<Number>>& _elements );
	void addToComposition( const Point<Number>& _element );

	static Point<Number> Zero( unsigned _dim = 0 ) { return Point<Number>( vector_t<Number>::Zero( _dim )); }

	Point<Number> origin() const;

	/**
	 * Returns the value of mCoordinates[dim].
	 * @param  dim the dimension we want to get the value from.
	 * @return
	 */
	Number coordinate( const carl::Variable& _var ) const;
	Number coordinate( unsigned _dimension ) const;

	coordinateMap coordinates() const;
	const vector_t<Number>& rawCoordinates() const;
	void setCoordinate( const carl::Variable& _dim, const Number& _value );

	void swap( Point<Number>& _rhs );

	/**
	 * Sets the coordinates from the given vector
	 */
	void setCoordinates(const vector_t<Number> &vector);
	unsigned dimension() const;
	void reduceDimension( unsigned _dimension );
	Point<Number> reduceToDimensions( std::vector<unsigned> _dimensions ) const;

	std::vector<carl::Variable> variables() const;

	Point<Number> extAdd( const Point<Number>& _rhs ) const;
	Number distance( const Point<Number>& _rhs ) const;
	std::vector<Number> polarCoordinates( const Point<Number>& _origin, bool _radians = true ) const;

	/**
	 * Creates a new empty point (origin) with the same dimensions
	 * as this point.
	 *
	 * @return new empty point
	 */
	Point<Number> newEmpty() const;

	/**
	 * Method to move the point
	 * @param p Point with coordinates describing the move.
	 * @return true, if the result has a negative coordinate.
	 */
	bool move( const Point<Number>& _p );

	/**
	 * Makes a linear transformation, ie A * p + b
	 */
	Point<Number> linearTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const;

	/**
	 * @return the sum of all coordinates (solved via dot product)
	 */
	Number sum() const;

	/**
	 *
	 * @param p1 One point
	 * @param p2 Other point
	 * @return A point with the coordinate-wise maximum of p1 and p2.
	 */
	static Point<Number> coeffWiseMax(const Point<Number> &_p1, const Point<Number> &_p2) {
		assert( _p1.dimension() == _p2.dimension() );
		vector_t<Number> coordinates = vector_t<Number>( _p1.dimension() );
		for ( unsigned i = 0; i < _p1.dimension(); ++i ) {
			coordinates( i ) = _p1.at( i ) >= _p2.at( i ) ? _p1.at( i ) : _p2.at( i );
		}
		return Point<Number>( coordinates );
	}

	static Point<Number> coeffWiseMin(const Point<Number> &_p1, const Point<Number> &_p2) {
		assert( _p1.dimension() == _p2.dimension() );
		vector_t<Number> coordinates = vector_t<Number>( _p1.dimension() );
		for ( unsigned i = 0; i < _p1.dimension(); ++i ) {
			coordinates( i ) = _p1.at( i ) <= _p2.at( i ) ? _p1.at( i ) : _p2.at( i );
		}
		return Point<Number>( coordinates );
	}

	static Number inftyNorm( const Point<Number> _p ) {
		Number res = 0;
		vector_t<Number> coord = _p.rawCoordinates();
		for ( unsigned i = 0; i < _p.dimension(); ++i ) {
			Number absolute = abs( coord( i ) );
			res = res > absolute ? res : absolute;
		}
		return res;
	}

	/**
	 * removes any duplicate points in a given PointVector
	 * @author Simon Froitzheim
	 * @param PointVec the point vector which should get checked for duplicates
	 * @return A point vector that is just PointVec without duplicates
	 */

	static std::vector<Point<Number>> removeDuplicatePoints( const std::vector<Point<Number>>& pointVec){
		  std::set<Point<Number>> pointSet;
		  //writes all the point entries into a set (set removes duplicates)
		  for (unsigned i = 0; i<pointVec.size(); ++i){
			  pointSet.insert(pointVec.at(i));
		  }
		  //write all the set entries into the return vector
		  std::vector<Point<Number>> res;
		  for (const auto& point : pointSet){
			  res.push_back(point);
		  }

		  //std::copy(pointSet.begin(), pointSet.end(), res.begin());
		  return res;
	}


	/**
	 * Change the coordinates of the point. Moving the point one step in a given dimension.
	 * @param d Dimension in which the coordinate is increased.
	 */
	void incrementInFixedDim( const carl::Variable& _d );
	void incrementInFixedDim( unsigned _d );

	/**
	 *
	 * @param val The value to be added to each coordinate
	 */
	void incrementInAllDim( const Number& _val = 1 );

	/**
	 * Change the point's coordinates. Moving the point one step in a given dimension.
	 * @param d Dimension in which the coordinate is decreased.
	 */
	void decrementInFixedDim( const carl::Variable& _d );
	void decrementInFixedDim( unsigned _d );

	/**
	 *
	 * @param d
	 * @return The point with coordinates [x(1), .., x(d-1), x(d)-1, x(d+1), ..., x(n) ]
	 */
	Point getPredecessorInDimension( const carl::Variable& _d ) const;
	Point getPredecessorInDimension( unsigned _d ) const;

	/**
	 * @brief Check if in range.
	 * @param boundary Point with coordinates that may not be exceeded in positive direction.
	 * @return true, if every coordinate is within boundary[i] and 0.
	 */
	bool isInBoundary( const Point<Number>& _boundary ) const;

	/**
	 * Operators & Comparison functions
	 */

	bool hasDimension( const carl::Variable& _i ) const;
	bool hasDimensions( const std::vector<carl::Variable>& _variables ) const;

	static std::vector<bool> lesserDimensionPattern( const Point<Number>& _p1, const Point<Number>& _p2 );

	bool haveEqualCoordinate( const Point<Number>& _p2 ) const;

	/**
	 * Checks if the point has the same dimensions as this point.
	 * The Number of dimensions has to be equal as well as the actual
	 * variables used for those dimensions.
	 *
	 * @param p
	 * @return True, if all dimension variables are equal
	 */
	bool haveSameDimensions( const Point<Number>& _p ) const;

	/**
	 * Comparison operator for the map.
	 * This is not true for lesser distance to the origin.
	 * It simply compares the entries for every dimension
	 * As soon as they are different the method returns
	 *
	 * @param p1
	 * @param p2
	 * @return
	 */
	bool operator<( const Point<Number>& _p2 ) const { return ( mCoordinates < _p2.rawCoordinates() ); }
	bool operator<=( const Point<Number>& _p2 ) const { return ( mCoordinates <= _p2.rawCoordinates() ); }
	bool operator>( const Point<Number>& _p2 ) const { return _p2 < *this; }
	bool operator>=( const Point<Number>& _p2 ) const { return _p2 <= *this; }

	bool operator==( const Point<Number>& _p2 ) const {
		assert( dimension() == _p2.dimension() );
		if (this->hash() != _p2.hash()) {
			return false;
		}

		return ( this->rawCoordinates() == _p2.rawCoordinates() );
	}

	template <typename F, carl::DisableIf<std::is_same<F, Number>> = carl::dummy>
	bool operator==( const Point<F>& _p2 ) const {
		assert( dimension() == _p2.dimension() );
		if (this->hash() != _p2.hash()) {
			return false;
		}
		for ( unsigned d = 0; d < this->dimension(); ++d ) {
			if ( this->at( d ) != Number( _p2.at( d ) ) ) {
				return false;
			}
		}
		return true;
	}

	bool operator!=( const Point<Number>& _p2 ) const { return !( *this == _p2 ); }

	Point<Number>& operator+=( const Point<Number>& _rhs );
	Point<Number>& operator+=( const vector_t<Number>& _rhs );
	Point<Number>& operator-=( const Point<Number>& _rhs );
	Point<Number>& operator-=( const vector_t<Number>& _rhs );
	Point<Number> operator-() const;
	Point<Number>& operator/=( unsigned _quotient );
	Point<Number>& operator*=( const Number _factor );
	Point<Number>& operator=( const Point<Number>& _in );
	Point<Number>& operator=( Point<Number>&& _in );
	Point<Number>& operator=( const vector_t<Number>& _in );
	Point<Number>& operator=( vector_t<Number>&& _in );

	/**
	 *
	 * @param i
	 * @return
	 */
	Number& operator[]( const carl::Variable& _i );
	Number& operator[]( std::size_t _i );

	const Number& at( const carl::Variable& _i ) const;
	const Number& at( unsigned _index ) const;

	/**
	 *
	 * @param ostr
	 * @param p
	 * @return
	 */
	friend std::ostream& operator<<( std::ostream& _ostr, const Point<Number>& _p ) {
		_ostr << "( ";
		for ( unsigned i = 0; i < _p.rawCoordinates().rows() - 1; ++i ) {
			_ostr << _p.at( i ) << "[" << i  << "] , ";
		}
		_ostr << _p.at( _p.rawCoordinates().rows() - 1 ) << "[" << _p.rawCoordinates().rows() - 1 << "]";
		_ostr << ")";
		return _ostr;
	}

	explicit operator vector_t<Number>() const { return mCoordinates; }
};

template <typename Number>
void swap( Point<Number>& _lhs, Point<Number>& _rhs ) {
	_lhs.swap( _rhs );
}

template <typename Number>
const Point<Number> operator+( const Point<Number>& _lhs, const Point<Number>& _rhs ) {
	assert( _lhs.dimension() == _rhs.dimension() );
	vector_t<Number> resCoord = vector_t<Number>( _lhs.dimension() );
	vector_t<Number> p1Coord = _lhs.rawCoordinates();
	vector_t<Number> p2Coord = _rhs.rawCoordinates();
	;
	resCoord = p1Coord + p2Coord;
	return Point<Number>( resCoord );
}

template <typename Number>
const Point<Number> operator-( const Point<Number>& _lhs, const Point<Number>& _rhs ) {
	assert( _lhs.dimension() == _rhs.dimension() );
	vector_t<Number> resCoord = vector_t<Number>( _lhs.dimension() );
	vector_t<Number> p1Coord = _lhs.rawCoordinates();
	vector_t<Number> p2Coord = _rhs.rawCoordinates();
	;
	resCoord = p1Coord - p2Coord;
	return Point<Number>( resCoord );
}

template <typename Number>
const Point<Number> operator/( const Point<Number>& _lhs, unsigned _quotient ) {
	vector_t<Number> resCoord = vector_t<Number>( _lhs.dimension() );
	vector_t<Number> p1Coord = _lhs.rawCoordinates();
	resCoord = p1Coord / _quotient;
	return Point<Number>( resCoord );
}

template <typename Number>
Number operator*( const Point<Number>& _lhs, const Point<Number>& _rhs ) {
	vector_t<Number> p1Coord = _lhs.rawCoordinates();
	vector_t<Number> p2Coord = _rhs.rawCoordinates();
	;
	return p1Coord.dot( p2Coord );
}

template <typename Number>
const Point<Number> operator*( const Point<Number>& _lhs, const Number& _factor ) {
	vector_t<Number> resCoord = vector_t<Number>( _lhs.dimension() );
	vector_t<Number> p1Coord = _lhs.rawCoordinates();
	resCoord = p1Coord * _factor;
	return Point<Number>( resCoord );
}

template <typename Number>
const Point<Number> operator*( const Number& _factor, const Point<Number>& _rhs ) {
	return ( _rhs * _factor );
}

template<typename Number>
int effectiveDimension(const std::vector<Point<Number>>& vertices) {
	if(!vertices.empty()){
		if(vertices.size() == 1) {
			return 0;
		}
		unsigned maxDim = vertices.begin()->rawCoordinates().rows();
		matrix_t<Number> matr = matrix_t<Number>(vertices.size()-1, maxDim);
		// use first vertex as origin, start at second vertex
		unsigned rowIndex = 0;
		for(auto vertexIt = ++vertices.begin(); vertexIt != vertices.end(); ++vertexIt, ++rowIndex) {
			matr.row(rowIndex) = (vertexIt->rawCoordinates() - vertices.begin()->rawCoordinates()).transpose();
		}
		return matr.fullPivLu().rank();
	}
	return -1;
}

template<typename Number>
int effectiveDimension(const std::set<Point<Number>>& vertices) {
	if(!vertices.empty()){
		if(vertices.size() == 1) {
			return 0;
		}
		unsigned maxDim = vertices.begin()->rawCoordinates().rows();
		matrix_t<Number> matr = matrix_t<Number>(vertices.size()-1, maxDim);
		// use first vertex as origin, start at second vertex
		unsigned rowIndex = 0;
		for(auto vertexIt = ++vertices.begin(); vertexIt != vertices.end(); ++vertexIt, ++rowIndex) {
			matr.row(rowIndex) = (vertexIt->rawCoordinates() - vertices.begin()->rawCoordinates()).transpose();
		}
		return matr.fullPivLu().rank();
	}
	return -1;
}

template<typename From, typename To>
Point<To> convert(const Point<From>& in) {
	return Point<To>(convert<From,To>(in.rawCoordinates()));
}


}  // namespace hypro

namespace std{
    template<class Number>
    struct hash<hypro::Point<Number>> {
        std::size_t operator()(hypro::Point<Number> const& point) const
        {
            return std::hash<hypro::vector_t<Number>>()(point.rawCoordinates());
        }
    };
} //namespace std

#include "Point.tpp"
