/*
 * Copyright (c) 2021.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * @file   Point.h
 *
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @author Sebastian Junges
 * @author Benedikt Seidl
 */
#pragma once

#include "../config.h"
#include "../types.h"
#include "../util/VariablePool.h"

#include <set>
#include <vector>

namespace hypro {

/**
 * @brief      Class for a point.
 * @details    The point class is the basis for all implementation. It consists of a vector
 * of coordinates which forms a point in a n-dimensional space.
 * @tparam     Number  The used number type.
 */
template <class Number>
class Point {
  public:
	using pointSet = std::set<Point<Number>>;
	using coordinateMap = std::map<carl::Variable, Number>;

  private:
	vector_t<Number> mCoordinates;

  public:
	/**
	 * @brief      Default constructor.
	 */
	Point();

	/**
	 * @brief      Constructs a one dimensional point at the given coordinate.
	 * @param[in]  _value  The coordinate.
	 */
	explicit Point( const Number& _value );

	/**
	 * @brief      Constructor from an initializer list.
	 * @param[in]  _coordinates  The coordinates.
	 */
	explicit Point( std::initializer_list<Number> _coordinates );

	/**
	 * @brief      Constructor from a std::vector.
	 * @param[in]  _coordinates  The coordinates.
	 */
	explicit Point( std::vector<Number> _coordinates );

	/**
	 * @brief      Constructor from the internal vector type.
	 * @param[in]  _vector  The vector.
	 */
	explicit Point( const vector_t<Number>& _vector );

	/**
	 * @brief      Move constructor from the internal vector type.
	 * @param[in]  _vector  The vector.
	 */
	explicit Point( vector_t<Number>&& _vector );

	/**
	 * @brief      Copy constructor.
	 * @param[in]  _p    The original.
	 */
	Point( const Point<Number>& _p ) = default;

	/**
	 * @brief      Move-copy constructor.
	 * @param[in]  _p  The original.
	 */
	Point( Point<Number>&& _p ) = default;

	/**
	 * @brief 	Copy constructor with number type conversion.
	 */
	template <typename F, carl::DisableIf<std::is_same<F, Number>> = carl::dummy>
	explicit Point( const Point<F>& _p ) {
		mCoordinates = vector_t<Number>( _p.coordinates().size() );
		for ( unsigned pos = 0; pos < _p.dimension(); ++pos ) {
			mCoordinates( pos ) = Number( _p.at( pos ) );
		}
	}

	/**
	 * @brief      Destroys the object.
	 */
	virtual ~Point() {}

	/**
	 * @brief      Hash function.
	 * @return     The hash.
	 */
	std::size_t hash() const {
		return std::hash<vector_t<Number>>()( mCoordinates );
	}

	/**
	 * @brief      Extends the space the point lies in by one dimension and sets its coordinate.
	 * @param[in]  val   The new coordinate.
	 */
	void extend( const Number& val ) {
		mCoordinates.conservativeResize( mCoordinates.rows() + 1 );
		mCoordinates( mCoordinates.rows() - 1 ) = val;
	}

	/**
	 * @brief      Creates the origin point of the given space dimension.
	 * @param[in]  _dim  The dimension.
	 * @return     The origin point.
	 */
	static Point<Number> Zero( std::size_t _dim = 0 ) { return Point<Number>( vector_t<Number>::Zero( Eigen::Index( _dim ) ) ); }

	/**
	 * @brief      Returns the origin of the current space.
	 * @return     The origin.
	 */
	Point<Number> origin() const;

	/**
	 * @brief      Returns the coordinate of the dimension mapped to the given variable.
	 * @param[in]  _var  The variable.
	 * @return     The coordinate.
	 */
	Number coordinate( const carl::Variable& _var ) const;

	/**
	 * @brief      Returns the coordinate at the given dimension.
	 * @param[in]  _dimension  The dimension.
	 * @return     The coordinate.
	 */
	Number coordinate( std::size_t _dimension ) const;

	/**
	 * @brief      Returns a mapping from variables to coordinates for the current point.
	 * @return     The mapping.
	 */
	coordinateMap coordinates() const;

	/**
	 * @brief      Returns the coordinates as a vector representation.
	 * @return     The coordinate vector.
	 */
	const vector_t<Number>& rawCoordinates() const;

	/**
	 * @brief      Sets the coordinate mapped to the given variable to the given value.
	 * @param[in]  _dim    The variable.
	 * @param[in]  _value  The value.
	 */
	void setCoordinate( const carl::Variable& _dim, const Number& _value );

	/**
	 * @brief      Sets the coordinate for the passed dimension.
	 * @param[in]  _dim    The dimension.
	 * @param[in]  _value  The value.
	 */
	void setCoordinate( std::size_t dimension, const Number& _value );

	/**
	 * @brief      Swap operator.
	 * @param      _rhs  The right hand side.
	 */
	void swap( Point<Number>& _rhs );

	/**
	 * @brief      Sets the coordinates.
	 * @param[in]  vector  The vector.
	 */
	void setCoordinates( const vector_t<Number>& vector );

	/**
	 * @brief      Returns the space dimension.
	 * @return     The dimension.
	 */
	unsigned dimension() const;

	/**
	 * @brief      Reduces the space dimension by dropping the additional coordinates.
	 * @param[in]  _dimension  The target dimension.
	 */
	void reduceDimension( unsigned _dimension );

	/**
	 * @brief      Projects the point onto the given set of dimensions.
	 * @param[in]  _dimensions  The dimensions.
	 * @return     The resulting point.
	 */
	Point<Number> reduceToDimensions( std::vector<std::size_t> _dimensions ) const;

	/**
	 * @brief      Returns the variables (ordered), which are assigned to the space dimensions.
	 * @return     A vector of variables.
	 */
	std::vector<carl::Variable> variables() const;

	/**
	 * @brief      Adds the coordinated of the passed point to this point.
	 * @param[in]  _rhs  The right hand side.
	 * @return     The resulting point.
	 */
	Point<Number> extAdd( const Point<Number>& _rhs ) const;

	/**
	 * @brief      Returns the euclidean distance between the current and the passed point.
	 * @param[in]  _rhs  The right hand side.
	 * @return     The distance.
	 */
	Number distance( const Point<Number>& _rhs ) const;

	/**
	 * @brief      Returns the polar coordinates of the current point according to the passed origin.
	 * @param[in]  _origin   The origin.
	 * @param[in]  _radians  If true, use radians.
	 * @return     A vector of polar coordinates.
	 */
	std::vector<Number> polarCoordinates( const Point<Number>& _origin, bool _radians = true ) const;

	/**
	 * @brief      Creates an empty origin point with the same dimensions as the current point.
	 * @return     The empty point.
	 */
	Point<Number> newEmpty() const;

	/**
	 * @brief      Projects the point on the given dimensions.
	 * @param[in]  dimensions  The dimensions.
	 * @return     The projected point.
	 */
	Point<Number> projectOn( const std::vector<std::size_t>& dimensions ) const;

	/**
	 * @brief      Projects out the given dimensions from the point.
	 * @param[in]  dimensions  The dimensions.
	 * @return     The projected point.
	 */
	Point<Number> projectOut( const std::vector<std::size_t>& dimensions ) const;

	/**
	 * @brief      Applies an affine transformation on the current point.
	 * @param[in]  A     The transformation matrix.
	 * @param[in]  b     The transformation vector.
	 * @return     The resulting point.
	 */
	Point<Number> linearTransformation( const matrix_t<Number>& A ) const;

	/**
	 * @brief      Applies an affine transformation on the current point.
	 * @param[in]  A     The transformation matrix.
	 * @param[in]  b     The transformation vector.
	 * @return     The resulting point.
	 */
	Point<Number> affineTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const;

	/**
	 * @brief      Returns the sum of all coordinates.
	 * @return     The sum.
	 */
	Number sum() const;

	/**
	 * @brief      Returns a point representing the coefficient-wise maximum of two points.
	 * @param[in]  _p1   The first point.
	 * @param[in]  _p2   The second point.
	 * @return     The resulting point.
	 */
	static Point<Number> coeffWiseMax( const Point<Number>& _p1, const Point<Number>& _p2 ) {
		assert( _p1.dimension() == _p2.dimension() );
		vector_t<Number> coordinates = vector_t<Number>( _p1.dimension() );
		for ( unsigned i = 0; i < _p1.dimension(); ++i ) {
			coordinates( i ) = _p1.at( i ) >= _p2.at( i ) ? _p1.at( i ) : _p2.at( i );
		}
		return Point<Number>( coordinates );
	}

	/**
	 * @brief      Returns a point representing the coefficient-wise minimum of two points.
	 * @param[in]  _p1   The first point.
	 * @param[in]  _p2   The second point.
	 * @return     The resulting point.
	 */
	static Point<Number> coeffWiseMin( const Point<Number>& _p1, const Point<Number>& _p2 ) {
		assert( _p1.dimension() == _p2.dimension() );
		vector_t<Number> coordinates = vector_t<Number>( _p1.dimension() );
		for ( unsigned i = 0; i < _p1.dimension(); ++i ) {
			coordinates( i ) = _p1.at( i ) <= _p2.at( i ) ? _p1.at( i ) : _p2.at( i );
		}
		return Point<Number>( coordinates );
	}

	/**
	 * @brief      Returns the infinity norm of the point.
	 * @param[in]  _p    The point.
	 * @return     The infinity norm.
	 */
	static Number inftyNorm( const Point<Number> _p ) {
		Number res = 0;
		vector_t<Number> coord = _p.rawCoordinates();
		for ( unsigned i = 0; i < _p.dimension(); ++i ) {
			Number absolute = coord( i ) < 0 ? Number( -1 ) * coord( i ) : coord( i );	// workaround for abs
			res = res > absolute ? res : absolute;
		}
		return res;
	}

	/**
	 * @brief Removes any duplicate points in a given set of points.
	 * @author Simon Froitzheim
	 * @param[in] PointVec the point vector which should get checked for duplicates.
	 * @return A point vector that is duplicate-free.
	 */
	static std::vector<Point<Number>> removeDuplicatePoints( const std::vector<Point<Number>>& pointVec ) {
		std::set<Point<Number>> pointSet;
		// writes all the point entries into a set (set removes duplicates)
		for ( unsigned i = 0; i < pointVec.size(); ++i ) {
			pointSet.insert( pointVec.at( i ) );
		}
		// write all the set entries into the return vector
		std::vector<Point<Number>> res;
		for ( const auto& point : pointSet ) {
			res.push_back( point );
		}

		// std::copy(pointSet.begin(), pointSet.end(), res.begin());
		return res;
	}

	/**
	 * @brief      Increments the coordinate according to the passed dimension by 1.
	 * @param[in]  _d    The dimension.
	 */
	void incrementInFixedDim( const carl::Variable& _d );

	/**
	 * @brief      Increments the coordinate according to the passed dimension by 1.
	 * @param[in]  _d    The dimension.
	 */
	void incrementInFixedDim( unsigned _d );

	/**
	 * @brief      Increments all coordinates by the passed value.
	 * @param[in]  _val  The value.
	 */
	void incrementInAllDim( const Number& _val = 1 );

	/**
	 * @brief      Decrements the coordinate according to the passed dimension by 1.
	 * @param[in]  _d    The dimension.
	 */
	void decrementInFixedDim( const carl::Variable& _d );

	/**
	 * @brief      Decrements the coordinate according to the passed dimension by 1.
	 * @param[in]  _d    The dimension.
	 */
	void decrementInFixedDim( unsigned _d );

	/**
	 * @brief      Gets the predecessor in the passed dimension.
	 * @param[in]  _d    The dimension.
	 * @return     The predecessor in dimension.
	 */
	Point getPredecessorInDimension( const carl::Variable& _d ) const;

	/**
	 * @brief      Gets the predecessor in the passed dimension.
	 * @param[in]  _d    The dimension.
	 * @return     The predecessor in dimension.
	 */
	Point getPredecessorInDimension( unsigned _d ) const;

	/**
	 * @brief Check if the current point is coefficient-wise smaller than the given point and larger than the origin.
	 * @param boundary Point with coordinates that may not be exceeded in positive direction.
	 * @return True, if every coordinate is within boundary[i] and the origin, false otherwise.
	 */
	bool isInBoundary( const Point<Number>& _boundary ) const;

	/**
	 * @brief      Determines if the point has the passed dimension.
	 * @param[in]  _i    The dimension.
	 * @return     True if has the passed dimension, false otherwise.
	 */
	bool hasDimension( const carl::Variable& _i ) const;

	/**
	 * @brief      Determines if the point has the passed dimensions.
	 * @param[in]  _i    The vector of dimensions.
	 * @return     True if has all passed dimensions, false otherwise.
	 */
	bool hasDimensions( const std::vector<carl::Variable>& _variables ) const;

	/**
	 * @brief      Creates a bitvector holding a 1 at pos i, if _p1(i) < _p2(i) holds.
	 * @param[in]  _p1   The first point.
	 * @param[in]  _p2   The second point.
	 * @return     The resulting bitvector.
	 */
	static std::vector<bool> lesserDimensionPattern( const Point<Number>& _p1, const Point<Number>& _p2 );

	/**
	 * @brief      Determines, if the current and the passed point have at lease one shared coordinate.
	 * @param[in]  _p2   The point.
	 * @return     True, if at least one coordinate is equal.
	 */
	bool haveEqualCoordinate( const Point<Number>& _p2 ) const;

	/**
	 * @brief      Compares the space dimension for two points.
	 * @param[in]  _p    The second point.
	 * @return     True, if the space dimensions are equal, false otherwise.
	 */
	bool haveSameDimensions( const Point<Number>& _p ) const;

	/**
	 * @brief      Coordinate-wise comparison of two points.
	 * @param[in]  _p2   The second point.
	 * @return     True, if for all coordinates the comparison holds.
	 */
	bool operator<( const Point<Number>& _p2 ) const { return ( mCoordinates < _p2.rawCoordinates() ); }

	/**
	 * @brief      Coordinate-wise comparison of two points.
	 * @param[in]  _p2   The second point.
	 * @return     True, if for all coordinates the comparison holds.
	 */
	bool operator<=( const Point<Number>& _p2 ) const { return ( mCoordinates <= _p2.rawCoordinates() ); }

	/**
	 * @brief      Coordinate-wise comparison of two points.
	 * @param[in]  _p2   The second point.
	 * @return     True, if for all coordinates the comparison holds.
	 */
	bool operator>( const Point<Number>& _p2 ) const { return _p2 < *this; }

	/**
	 * @brief      Coordinate-wise comparison of two points.
	 * @param[in]  _p2   The second point.
	 * @return     True, if for all coordinates the comparison holds.
	 */
	bool operator>=( const Point<Number>& _p2 ) const { return _p2 <= *this; }

	/**
	 * @brief      Coordinate-wise comparison of two points.
	 * @param[in]  _p2   The second point.
	 * @return     True, if for all coordinates the comparison holds.
	 */
	bool operator==( const Point<Number>& _p2 ) const {
		assert( dimension() == _p2.dimension() );
		if ( this->hash() != _p2.hash() ) {
			return false;
		}

		return ( is_approx_equal( this->rawCoordinates(), _p2.rawCoordinates() ) );
	}

	/**
	 * @brief      Coordinate-wise comparison of two points.
	 * @param[in]  _p2   The second point.
	 * @return     True, if for all coordinates the comparison holds.
	 */
	template <typename F, carl::DisableIf<std::is_same<F, Number>> = carl::dummy>
	bool operator==( const Point<F>& _p2 ) const {
		assert( dimension() == _p2.dimension() );
		for ( unsigned d = 0; d < this->dimension(); ++d ) {
			if ( this->at( d ) != Number( _p2.at( d ) ) ) {
				return false;
			}
		}
		return true;
	}

	/**
	 * @brief      Coordinate-wise comparison of two points.
	 * @param[in]  _p2   The second point.
	 * @return     True, if for all coordinates the comparison holds.
	 */
	bool operator!=( const Point<Number>& _p2 ) const { return !( *this == _p2 ); }

	//@{
	/**
	 * @brief      Arithmetic assignment operator.
	 * @param[in]  The right hand side.
	 * @return     The reference to the current point modified by the operation.
	 */
	Point<Number>& operator+=( const Point<Number>& _rhs );
	Point<Number>& operator+=( const vector_t<Number>& _rhs );
	Point<Number>& operator-=( const Point<Number>& _rhs );
	Point<Number>& operator-=( const vector_t<Number>& _rhs );
	Point<Number> operator-() const;
	Point<Number>& operator/=( unsigned _quotient );
	Point<Number>& operator*=( const Number _factor );
	Point<Number>& operator=( const Point<Number>& _in ) = default;
	Point<Number>& operator=( Point<Number>&& _in ) = default;
	Point<Number>& operator=( const vector_t<Number>& _in );
	Point<Number>& operator=( vector_t<Number>&& _in );
	//@}

	//@{
	/**
	 * @brief      Access operator to the respective dimension coefficient.
	 * @param[in]  _i    The dimension.
	 * @return     The coefficient.
	 */
	Number& operator[]( const carl::Variable& _i );
	Number& operator[]( std::size_t _i );
	const Number& operator[]( const carl::Variable& _i ) const;
	const Number& operator[]( std::size_t _i ) const;

	Number& at( const carl::Variable& _i );
	Number& at( std::size_t _index );
	const Number& at( const carl::Variable& _i ) const;
	const Number& at( std::size_t _index ) const;
	//@}

	/**
	 * @brief      Outstream operator.
	 * @param      _ostr  The outstream
	 * @param[in]  _p     The point.
	 * @return     A reference to the outstream.
	 */
	friend std::ostream& operator<<( std::ostream& _ostr, const Point<Number>& _p ) {
		_ostr << "( ";
		for ( unsigned i = 0; i < _p.rawCoordinates().rows() - 1; ++i ) {
			_ostr << _p.at( i ) << "; ";  // << "[" << i << "] , ";
		}
		_ostr << _p.at( unsigned( _p.rawCoordinates().rows() ) - 1 );  // << "[" << _p.rawCoordinates().rows() - 1 << "]";
		_ostr << " )";
		return _ostr;
	}

	/**
	 * @brief      Conversion operator to the internal vector type.
	 */
	explicit operator vector_t<Number>() const { return mCoordinates; }
};

/**
 * @brief      Swap operator.
 * @param      _lhs    The left hand side.
 * @param      _rhs    The right hand side.
 * @tparam     Number  The number type.
 */
template <typename Number>
void swap( Point<Number>& _lhs, Point<Number>& _rhs ) {
	_lhs.swap( _rhs );
}

//@{
/**
 * @brief      Arithmetic operator returning a new point.
 * @param[in]  _lhs    The left hand side.
 * @param[in]  _rhs    The right hand side.
 * @tparam     Number  The number type.
 * @return     The resulting point.
 */
template <typename Number>
const Point<Number> operator+( const Point<Number>& _lhs, const Point<Number>& _rhs ) {
	assert( _lhs.dimension() == _rhs.dimension() );
	vector_t<Number> resCoord = vector_t<Number>( _lhs.dimension() );
	vector_t<Number> p1Coord = _lhs.rawCoordinates();
	vector_t<Number> p2Coord = _rhs.rawCoordinates();
	resCoord = p1Coord + p2Coord;
	return Point<Number>( resCoord );
}

template <typename Number>
const Point<Number> operator+( const Point<Number>& _lhs, const vector_t<Number>& _rhs ) {
	assert( _lhs.dimension() == _rhs.rows() );
	vector_t<Number> resCoord = vector_t<Number>( _lhs.dimension() );
	vector_t<Number> p1Coord = _lhs.rawCoordinates();
	resCoord = p1Coord + _rhs;
	return Point<Number>( resCoord );
}

template <typename Number>
const Point<Number> operator-( const Point<Number>& _lhs, const Point<Number>& _rhs ) {
	assert( _lhs.dimension() == _rhs.dimension() );
	vector_t<Number> resCoord = vector_t<Number>( _lhs.dimension() );
	vector_t<Number> p1Coord = _lhs.rawCoordinates();
	vector_t<Number> p2Coord = _rhs.rawCoordinates();
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
//@}

/**
 * @brief      Determines the dimension of the affine space spanned by the given set of points.
 * @param[in]  vertices  The set of points.
 * @tparam     Number    The number type.
 * @return     The spanned dimension.
 */
template <typename Number>
int effectiveDimension( const std::vector<Point<Number>>& vertices ) {
	if ( !vertices.empty() ) {
		if ( vertices.size() == 1 ) {
			return 0;
		}
		long maxDim = vertices.begin()->rawCoordinates().rows();
		matrix_t<Number> matr = matrix_t<Number>( vertices.size() - 1, maxDim );
		// use first vertex as origin, start at second vertex
		long rowIndex = 0;
		for ( auto vertexIt = ++vertices.begin(); vertexIt != vertices.end(); ++vertexIt, ++rowIndex ) {
			matr.row( rowIndex ) = ( vertexIt->rawCoordinates() - vertices.begin()->rawCoordinates() ).transpose();
		}
		return int( matr.fullPivLu().rank() );
	}
	return -1;
}

/**
 * @brief      Determines the dimension of the affine space spanned by the given set of points.
 * @param[in]  vertices  The set of points.
 * @tparam     Number    The number type.
 * @return     The spanned dimension.
 */
template <typename Number>
int effectiveDimension( const std::set<Point<Number>>& vertices ) {
	if ( !vertices.empty() ) {
		if ( vertices.size() == 1 ) {
			return 0;
		}
		long maxDim = vertices.begin()->rawCoordinates().rows();
		matrix_t<Number> matr = matrix_t<Number>( vertices.size() - 1, maxDim );
		// use first vertex as origin, start at second vertex
		long rowIndex = 0;
		for ( auto vertexIt = ++vertices.begin(); vertexIt != vertices.end(); ++vertexIt, ++rowIndex ) {
			matr.row( rowIndex ) = ( vertexIt->rawCoordinates() - vertices.begin()->rawCoordinates() ).transpose();
		}
		return int( matr.fullPivLu().rank() );
	}
	return -1;
}

/**
 * @brief      Conversion operator for the number type.
 * @param[in]  in    The point.
 * @tparam     From  The original number type.
 * @tparam     To    The target number type.
 * @return     A point in the targeted number type.
 */
template <typename From, typename To>
Point<To> convert( const Point<From>& in ) {
	return Point<To>( convert<From, To>( in.rawCoordinates() ) );
}

#ifdef EXTERNALIZE_CLASSES
extern template class Point<double>;
extern template class Point<mpq_class>;
#endif

}  // namespace hypro

namespace std {
/**
 * @brief      A hash operator for fast comparison.
 * @tparam     Number  The number type.
 */
template <class Number>
struct hash<hypro::Point<Number>> {
	std::size_t operator()( hypro::Point<Number> const& point ) const {
		return std::hash<hypro::vector_t<Number>>()( point.rawCoordinates() );
	}
};
}  // namespace std

#include "Point.tpp"
