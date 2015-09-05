/**
 * The point class is the basis for all implementation. It consists of a vector
 * of coordinates which forms a point in a n-dimensional space.
 * @file   Point.h
 *
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @author Sebastian Junges
 * @author Benedikt Seidl
 *
 * @since	2011-01-17
 * @version	2015-08-27
 */
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <assert.h>
#include "../config.h"


namespace hypro {

	/**
	 * @class Point
	 */
	/*
	class Point;
	typedef std::vector<Point> pVec;
	typedef std::vector<Point>::iterator pVecIt;
	*/


	/*
	 *  Class to store points in a MAXIMAL_DIMENSION space.
	 */
	template<class Number>
	class Point {
		public:
			typedef std::set<Point<Number> > pointSet;
			typedef std::map<carl::Variable, Number > coordinateMap;

		private:
			vector_t<Number> mCoordinates;

			//Adjacency List of this Point (if applicable)
			std::vector<Point<Number>> mNeighbors;
			//Minkowsi Decompositon of this point (if applicable)
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
			Point(const Number& _value);
			Point(std::initializer_list<Number> _coordinates);

			template<typename F, carl::DisableIf< std::is_same<F, Number> > = carl::dummy>
			Point(std::initializer_list<F> _coordinates) {
				unsigned count = 0;
				mCoordinates = vector_t<Number>(_coordinates.size());
				for(auto& coordinate : _coordinates) {
					mCoordinates(count) = Number(coordinate);
					++count;
				}
			}

			//@author Chris K. (for Minkowski Sum Test)
			Point(std::vector<Number> _coordinates);

			/**
			 * Constructs a point with the passed coordinates
			 * @param coordinates
			 */
			Point(const coordinateMap& _coordinates);
			Point(const vector_t<Number>& _vector);

			/**
			 * Copy constructor
			 * @param p
			 */
			Point(const Point<Number>& _p);
			Point(Point<Number>&& _p);

			template<typename F, carl::DisableIf< std::is_same<F, Number> > = carl::dummy>
			Point(const Point<F>& _p) {
				mCoordinates = vector_t<Number>(_p.coordinates().size());
				for(unsigned pos = 0; pos < _p.dimension(); ++pos)
				{
					mCoordinates(pos) = Number(_p.at(pos));
				}
			}

			virtual ~Point()
			{}

			/**
			 * Getter & Setter
			 */

			std::vector<Point<Number>> neighbors() const;

			void setNeighbors(const std::vector<Point<Number> >& _neighbors);
			void joinNeighbors(const std::vector<Point<Number> >& _neighbors);
			void addNeighbor(const Point<Number>& _neighbor);
			void removeNeighbor(const Point<Number>& _neighbor);
			bool isNeighbor(const Point<Number>& _neighbor);


			std::vector<Point<Number>> composedOf() const;
			void setComposition(const std::vector<Point<Number> >& _elements);
			void addToComposition(const Point<Number>& _element);

			static Point<Number> zero(unsigned _dim = 0) {
				return Point<Number>(vector_t<Number>::Zero(_dim));
			}

			Point<Number> origin() const;

			/**
			 * Returns the value of mCoordinates[dim].
			 * @param  dim the dimension we want to get the value from.
			 * @return
			 */
			Number coordinate(const carl::Variable& _var) const;
			Number coordinate(unsigned _dimension) const;

			coordinateMap coordinates() const;
			const vector_t<Number>& rawCoordinates() const;
			void setCoordinate(const carl::Variable& _dim, const Number& _value);

			void swap(Point<Number>& _rhs);

			/**
			 * Sets the coordinates from the given vector
			 */
			void coordinatesFromVector(const vector_t<Number>& vector);
			unsigned dimension() const;
			void reduceDimension(unsigned _dimension);
			void reduceToDimensions(std::vector<unsigned> _dimensions);

			std::vector<carl::Variable> variables() const;

			Point<Number> extAdd(const Point<Number>& _rhs) const;
			Number distance(const Point<Number>& _rhs) const;
			std::vector<Number> polarCoordinates( const Point<Number>& _origin,  bool _radians = true ) const;

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
			bool move(const Point<Number>& _p);

			/**
			 * Makes a linear transformation, ie A * p + b
			 */
			Point<Number> linearTransformation(const matrix_t<Number>& A, const vector_t<Number>& b) const;

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
			static Point<Number> coordinateMax(const Point<Number>& _p1, const Point<Number>& _p2) {
				assert(_p1.dimension() == _p2.dimension());
				vector_t<Number> coordinates = vector_t<Number>(_p1.dimension());
				vector_t<Number> p1Coord = _p1.rawCoordinates();
				vector_t<Number> p2Coord = _p2.rawCoordinates();
				for (unsigned i = 0; i < _p1.dimension(); ++i) {
					coordinates(i) = p1Coord(i) >= p2Coord(i) ? p1Coord(i) : p2Coord(i);
				}
				return Point<Number>(coordinates);
			}

			static Number inftyNorm(const Point<Number> _p) {
				Number res = 0;
				vector_t<Number> coord = _p.rawCoordinates();
				for (unsigned i = 0; i < _p.dimension(); ++i) {
					Number absolute = abs(coord(i));
					res = res > absolute ? res : absolute;
				}
				return res;
			}

			/**
			 * Change the coordinates of the point. Moving the point one step in a given dimension.
			 * @param d Dimension in which the coordinate is increased.
			 */
			void incrementInFixedDim(const carl::Variable& _d);
			void incrementInFixedDim(unsigned _d);

			/**
			 *
			 * @param val The value to be added to each coordinate
			 */
			void incrementInAllDim(const Number& _val = 1);

			/**
			 * Change the point's coordinates. Moving the point one step in a given dimension.
			 * @param d Dimension in which the coordinate is decreased.
			 */
			void decrementInFixedDim(const carl::Variable& _d);
			void decrementInFixedDim(unsigned _d);

			/**
			 *
			 * @param d
			 * @return The point with coordinates [x(1), .., x(d-1), x(d)-1, x(d+1), ..., x(n) ]
			 */
			Point getPredecessorInDimension(const carl::Variable& _d) const;
			Point getPredecessorInDimension(unsigned _d) const;

			/**
			 * @brief Check if in range.
			 * @param boundary Point with coordinates that may not be exceeded in positive direction.
			 * @return true, if every coordinate is within boundary[i] and 0.
			 */
			bool isInBoundary(const Point<Number>& _boundary) const;

			/**
			 * Operators & Comparison functions
			 */

			bool hasDimension(const carl::Variable& _i) const;
			bool hasDimensions(const std::vector<carl::Variable>& _variables) const;

			static std::vector<bool> lesserDimensionPattern(const Point<Number>& _p1, const Point<Number>& _p2);

			bool haveEqualCoordinate(const Point<Number>& _p2) const;

			/**
			 * Checks if the point has the same dimensions as this point.
			 * The Number of dimensions has to be equal as well as the actual
			 * variables used for those dimensions.
			 *
			 * @param p
			 * @return True, if all dimension variables are equal
			 */
			bool haveSameDimensions(const Point<Number>& _p) const;

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
			bool operator<(const Point<Number>& _p2) const{
				return (mCoordinates < _p2.rawCoordinates());
			}

			bool operator>(const Point<Number> & _p2) const{
				return _p2 < *this;
			}

			bool operator==(const Point<Number> & _p2) const{
				return (mCoordinates == _p2.rawCoordinates());
			}

			bool operator!=(const Point<Number> & _p2) const{
				return !(*this == _p2);
			}

			Point<Number>& operator+=(const Point<Number>& _rhs);
			Point<Number>& operator-=(const Point<Number>& _rhs);
			Point<Number>& operator/=(unsigned _quotient);
			Point<Number>& operator*=(const Number _factor);
			Point<Number>& operator= ( const Point<Number>& _in );
			Point<Number>& operator= ( Point<Number>&& _in);

			/**
			 *
			 * @param i
			 * @return
			 */
			Number& operator[] (const carl::Variable& _i);
			Number& operator[] (unsigned _i);

			Number at(const carl::Variable& _i) const;
			Number at(unsigned _index) const;

			/**
			 *
			 * @param ostr
			 * @param p
			 * @return
			 */
			friend std::ostream & operator<< (std::ostream& _ostr, const Point<Number>& _p) {
				_ostr << "( ";
				for (unsigned i = 0 ; i < _p.rawCoordinates().rows()-1; ++i) {
					_ostr << _p.at(i) << ", ";
				}
				_ostr << _p.at(_p.rawCoordinates().rows()-1);
				_ostr << ")";
				return _ostr;
			}

			explicit operator vector_t<Number>() const {
				return mCoordinates;
			}
	};

	template<typename Number>
	void swap(Point<Number>& _lhs, Point<Number>& _rhs) {
		_lhs.swap(_rhs);
	}

	template<typename Number>
	const Point<Number> operator+( const Point<Number>& _lhs, const Point<Number>& _rhs )
	{
		assert(_lhs.dimension() == _rhs.dimension());
		vector_t<Number> resCoord = vector_t<Number>(_lhs.dimension());
		vector_t<Number> p1Coord = _lhs.rawCoordinates();
		vector_t<Number> p2Coord = _rhs.rawCoordinates();;
		resCoord = p1Coord + p2Coord;
		return Point<Number>(resCoord);
	}

	template<typename Number>
	const Point<Number> operator-( const Point<Number>& _lhs, const Point<Number>& _rhs )
	{
		assert(_lhs.dimension() == _rhs.dimension());
		vector_t<Number> resCoord = vector_t<Number>(_lhs.dimension());
		vector_t<Number> p1Coord = _lhs.rawCoordinates();
		vector_t<Number> p2Coord = _rhs.rawCoordinates();;
		resCoord = p1Coord - p2Coord;
		return Point<Number>(resCoord);
	}

	template<typename Number>
	const Point<Number> operator/( const Point<Number>& _lhs, unsigned _quotient )
	{
		vector_t<Number> resCoord = vector_t<Number>(_lhs.dimension());
		vector_t<Number> p1Coord = _lhs.rawCoordinates();
		resCoord = p1Coord / _quotient;
		return Point<Number>(resCoord);
	}

	template<typename Number>
	Number operator*( const Point<Number>& _lhs, const Point<Number>& _rhs )
	{
		vector_t<Number> p1Coord = _lhs.rawCoordinates();
		vector_t<Number> p2Coord = _rhs.rawCoordinates();;
		return p1Coord.dot(p2Coord);
	}

	template<typename Number>
	const Point<Number> operator*( const Point<Number>& _lhs, const Number& _factor)
	{
		vector_t<Number> resCoord = vector_t<Number>(_lhs.dimension());
		vector_t<Number> p1Coord = _lhs.rawCoordinates();
		resCoord = p1Coord * _factor;
		return Point<Number>(resCoord);
	}

	template<typename Number>
	const Point<Number> operator*( const Number& _factor, const Point<Number>& _rhs)
	{
		return (_rhs*_factor);
	}

} // namespace

#include "Point.tpp"
