/*
 * @file    Grid.h
 * @author 	Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @author  Benedikt Seidl
 *
 * @since   2014-04-14
 * @version 2015-08-26
 */

#pragma once

#include "../../datastructures/Point.h"
#include "../../datastructures/Vertex.h"
#include <carl/core/Variable.h>
#include <vector>
#include <map>
#include <bitset>

namespace hypro {
template <typename Number>
struct pointIt {
	typename std::vector<std::vector<Number>> v;
	std::vector<typename std::vector<Number>::const_iterator> it;
	bool end = false;

	pointIt( const std::vector<std::vector<Number>>& _v ) : v( _v ) {
		for ( unsigned i = 0; i < v.size(); ++i ) it.push_back( v.at( i ).begin() );

		end = false;
	}

	// prefix
	Point<Number> operator++() {
		if ( end ) return std::move( current() );
		++it.back();
		unsigned i = it.size() - 1;
		while ( it.at( i ) == v.at( i ).end() ) {
			it[i] = v.at( i ).begin();
			if ( i == 0 ) {
				end = true;
				return std::move( current() );
			}
			--i;
			it[i]++;
		}
		return std::move( current() );
	}

	// postfix
	Point<Number> operator++( int ) { return ++( *this ); }

	Point<Number> current() {
		assert( v.size() == it.size() );
		Point<Number> res;
		for ( unsigned i = 0; i < v.size(); ++i ) res[i] = *it.at( i );

		return std::move( res );
	}
};

/**
 * Represents a grid which maps points to its color.
 */
template <typename Number>
class Grid {
  public:
	typedef std::map<Point<unsigned>, bool> gridMap;  // store calculated colors
	typedef std::map<unsigned, std::vector<Number>> gridPoints;

  private:
	std::set<Vertex<unsigned>> mVertices;
	mutable gridMap mGridMap;  // is mutable to allow storing of intermediate results
	mutable gridPoints mInducedGridPoints;

  public:
	/**
	 * Constructor
	 */
	Grid();
	Grid( const vSet<Number>& vertices );
	Grid( const std::vector<Vertex<Number>>& _vertices );
	Grid( const Grid<Number>& copy );

	Grid<Number>& operator=( const Grid<Number>& ) = default;
	Grid<Number>& operator=( Grid<Number>&& ) = default;

	/**
	 * Returns the size ie. the number of points saved in this grid.
	 *
	 * @return
	 */
	unsigned size() const;
	unsigned dimension() const;
	std::vector<carl::Variable> variables() const;
	std::vector<Vertex<Number>> vertices() const;
	std::vector<Number> inducedDimensionAt( unsigned dimension ) const;
	bool empty() const;

	/**
	 * Returns the color of the given point.
	 *
	 * @param point
	 * @return the color of the point
	 */
	bool colorAt( const Point<Number>& point ) const;
	bool colorAtInduced( const Point<unsigned>& inducedPoint ) const;
	std::vector<Point<Number>> allBlack() const;
	void colorAll() const;

	Point<unsigned> iPredecessorInduced( const Point<unsigned>& _point, unsigned _dimension ) const;
	Point<Number> iPredecessor( const Point<Number>& _point, unsigned _dimension ) const;
	Point<unsigned> iSuccessorInduced( const Point<unsigned>& _point, unsigned _dimension ) const;
	Point<Number> iSuccessor( const Point<Number>& _point, unsigned _dimension ) const;
	Point<unsigned> directPredecessorInduced( const Point<unsigned>& _point ) const;
	Point<Number> directPredecessor( const Point<Number>& _point ) const;
	Point<unsigned> directSuccessorInduced( const Point<unsigned>& _point ) const;
	Point<Number> directSuccessor( const Point<Number>& _point ) const;

	std::vector<Point<unsigned>> iSliceInduced( unsigned i, int pos ) const;
	std::vector<Point<Number>> iSlice( unsigned i, Number pos ) const;
	std::vector<Point<unsigned>> iNeighborhoodInduced( const Point<unsigned>& _inducedPoint,
													   unsigned _dimension ) const;
	std::vector<Point<Number>> iNeighborhood( const Point<Number>& _point, unsigned _dimension ) const;
	std::vector<Point<unsigned>> neighborhoodInduced( const Point<unsigned>& _inducedPoint ) const;
	std::vector<Point<Number>> neighborhood( const Point<Number>& _point ) const;

	bool isVertex( const Point<Number>& _point ) const;
	bool isOnIFacet( const Point<Number>& _point, unsigned i ) const;
	bool isOnFacet( const Point<Number>& _point ) const;
	bool isOutside( const Point<Number>& _point ) const;

	/**
	 * Inserts the value for the point.
	 *
	 * @param point
	 * @param color
	 */
	void insert( const Point<Number>& point, bool color );
	void insertInduced( const Point<unsigned>& inducedPoint, bool color );

	void addCoordinate( Number value, unsigned dimension );
	static Grid<Number> combine( const Grid<Number>& a, const Grid<Number>& b );

	void clear();

	typename gridMap::const_iterator find( const Point<Number>& point ) const;
	typename gridMap::const_iterator findInduced( const Point<unsigned>& inducedPoint ) const;
	typename gridMap::const_iterator end() const;

	/**
	 * Clears the grid, induces it and sets up the vertices.
	 *
	 * @param vertices
	 */
	void induceGrid( const vSet<Number>& vertices );

	/**
	 * Calculates the coordinates of this point on the induced grid.
	 *
	 * @param point
	 * @return induced point
	 */
	std::pair<Point<unsigned>, bool> calculateInduced( const Point<Number>& point ) const;

	/**
	 * Calculates the original coordinates of this induced point.
	 * @param inducedPoint
	 * @return original point
	 */
	Point<Number> calculateOriginal( const Point<unsigned>& inducedPoint ) const;

	/**
	 * Translates the points to induced points.
	 *
	 * @param vertices
	 * @return induced vertices
	 */
	vSet<unsigned> translateToInduced( const vSet<Number>& vertices ) const;

	/**
	 * Translates the induced points to original points.
	 *
	 * @param inducedVertices
	 * @return original vertices
	 */
	vSet<Number> translateToOriginal( const vSet<unsigned>& inducedVertices ) const;

	friend bool operator==( const Grid<Number>& op1, const Grid<Number>& op2 ) {
		return op1.mInducedGridPoints == op2.mInducedGridPoints;
	}

	friend bool operator!=( const Grid<Number>& op1, const Grid<Number>& op2 ) {
		return op1.mInducedGridPoints != op2.mInducedGridPoints;
	}

	friend std::ostream& operator<<( std::ostream& out, const Grid<Number>& grid ) {
		out << "[";
		for ( unsigned d = 0; d < grid.mInducedGridPoints.size(); ++d ) {
			out << std::endl << d << ": ";
			for ( unsigned p = 0; p < grid.mInducedGridPoints.at( d ).size(); ++p )
				out << grid.mInducedGridPoints.at( d ).at( p ) << " ";
		}
		out << std::endl << "]" << std::endl;
		return out;
	}
};
}

#include "Grid.tpp"
