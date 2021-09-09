/*
 * @file    OrthogonalPolyhedron.h
 * @author  Sebastian Junges
 * @author	Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @author  Benedikt Seidl
 */

#pragma once

#include "../../datastructures/Point.h"
#include "../../datastructures/Vertex.h"
#include "../../datastructures/VertexContainer.h"
#include "../Box/Box.h"
#include "Grid.h"
#include "NeighborhoodContainer.h"

#include <carl/core/Variable.h>
#include <fstream>
#include <iosfwd>
#include <list>
#include <map>
#include <string>
#include <vector>

namespace hypro {

/**
 * @brief      Enum holding the type identification of the different representations of orthogonal polyhedra.
 */
enum ORTHO_TYPE { VERTEX,
				  NEIGHBORHOOD,
				  EXTREME_VERTEX };

/**
 * @brief      Class for orthogonal polyhedra.
 *
 * @tparam     Number     The used number type.
 * @tparam     Converter  The used converter.
 * @tparam     Type       The internal representation type.
 */
template <typename Number, typename Converter, class Setting, ORTHO_TYPE Type = ORTHO_TYPE::VERTEX>
class OrthogonalPolyhedronT {
  private:
	// VertexContainer<Number> mVertices; // the container of all vertices
	Grid<Number> mGrid;										// the grid the polyhedron is defined on
	mutable BoxT<Number, Converter, Setting> mBoundaryBox;	// the cached boundary box (mutable to allow performance optimization)
	mutable bool mBoxUpToDate = false;

  public:
	/***********************************************************************
	 * Constructors
	 ***********************************************************************/

	OrthogonalPolyhedronT();
	OrthogonalPolyhedronT( const Vertex<Number>& _vertex );
	OrthogonalPolyhedronT( const VertexContainer<Number>& vertices );
	OrthogonalPolyhedronT( const std::set<Vertex<Number>>& points );
	OrthogonalPolyhedronT( const std::vector<Vertex<Number>>& points );
	OrthogonalPolyhedronT( const OrthogonalPolyhedronT<Number, Converter, Setting, Type>& copy );
	OrthogonalPolyhedronT( const OrthogonalPolyhedronT<Number, Converter, Setting, Type>&& move );

	template <class SettingRhs, carl::DisableIf<std::is_same<Setting, SettingRhs>> = carl::dummy>
	OrthogonalPolyhedronT( const OrthogonalPolyhedronT<Number, Converter, SettingRhs, Type>& copy )
		: mGrid( copy.vertices() )
		, mBoundaryBox()
		, mBoxUpToDate( false ) {
	}

	/***********************************************************************
	 * Getter, Setter
	 ***********************************************************************/

	std::vector<carl::Variable> variables() const;
	std::vector<Vertex<Number>> vertices() const;
	BoxT<Number, Converter, Setting> boundaryBox() const;
	const Grid<Number>& grid() const;
	void addVertex( const Vertex<Number>& _vertex );
	void addVertices( const std::vector<Vertex<Number>>& _vertices );

	bool empty() const;
	std::size_t size() const;
	std::size_t dimension() const;
	Number supremum() const;
	bool isVertex( const Point<Number>& _point ) const;
	bool isOnIEdge( const Point<Number>& _point, std::size_t i ) const;
	bool isInternal( const Point<Number>& _point ) const;
	bool isExternal( const Point<Number>& _point ) const;
	bool color( const Point<Number>& _point ) const;

	std::vector<Point<Number>> iNeighborhood( const Point<Number>& _point, std::size_t i ) const;
	std::vector<Point<Number>> iNegNeighborhood( const Point<Number>& _point, std::size_t i ) const;
	std::vector<Point<Number>> neighborhood( const Point<Number>& _point ) const;

	std::vector<Point<Number>> iSlice( std::size_t i, Number pos ) const;
	OrthogonalPolyhedronT iProjection( std::size_t i ) const;

	/***********************************************************************
	 * Geometric Object functions
	 ***********************************************************************/
	OrthogonalPolyhedronT linearTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const;
	OrthogonalPolyhedronT minkowskiSum( const OrthogonalPolyhedronT& rhs ) const;
	OrthogonalPolyhedronT intersect( const OrthogonalPolyhedronT& rhs ) const;
	OrthogonalPolyhedronT hull() const;
	bool contains( const Point<Number>& point ) const;
	bool contains( const OrthogonalPolyhedronT& _other ) const;
	OrthogonalPolyhedronT unite( const OrthogonalPolyhedronT& rhs ) const;

	/***********************************************************************
	 * Auxiliary functions
	 ***********************************************************************/
	std::vector<std::vector<Point<Number>>> preparePlot( std::size_t _xDim = 0, std::size_t _yDim = 1 ) const;

	/***********************************************************************
	 * Operators
	 ***********************************************************************/

	OrthogonalPolyhedronT<Number, Converter, Setting, Type>& operator=( const OrthogonalPolyhedronT<Number, Converter, Setting, Type>& _in ) = default;
	OrthogonalPolyhedronT<Number, Converter, Setting, Type>& operator=( OrthogonalPolyhedronT<Number, Converter, Setting, Type>&& ) = default;

	template <typename SettingRhs>
	friend bool operator==( const OrthogonalPolyhedronT<Number, Converter, Setting, Type>& op1, const OrthogonalPolyhedronT<Number, Converter, SettingRhs, Type>& op2 ) {
		// return op1.mGrid == op2.mGrid;
		return op1.grid() == op2.grid();
	}

	template <typename SettingRhs>
	friend bool operator!=( const OrthogonalPolyhedronT<Number, Converter, Setting, Type>& op1, const OrthogonalPolyhedronT<Number, Converter, Setting, Type>& op2 ) {
		// return op1.mGrid != op2.mGrid;
		return op1.grid() != op2.grid();
	}

	friend std::ostream& operator<<( std::ostream& ostr, const OrthogonalPolyhedronT<Number, Converter, Setting, Type>& p ) {
		ostr << "(";
		for ( const auto& vertex : p.mGrid.vertices() ) ostr << vertex << ", ";
		ostr << ")";
		return ostr;
	}

  private:
	void updateBoundaryBox() const;
};

}  // namespace hypro

#include "OrthogonalPolyhedron.tpp"
