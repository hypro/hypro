/*
 * @file    OrthogonalPolyhedron.h
 * @author  Sebastian Junges
 * @author	Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @author  Benedikt Seidl
 *
 * @since   2014-03-17
 * @version 2015-07-09
 */

#pragma once

#include "../../datastructures/Point.h"
#include "../../datastructures/Vertex.h"
#include "../../datastructures/VertexContainer.h"
#include "../Box/Box.h"
#include "../GeometricObject.h"
#include "NeighborhoodContainer.h"
#include "Grid.h"

#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <fstream>

#include <carl/core/Variable.h>

namespace hypro
{
	enum ORTHO_TYPE { VERTEX, NEIGHBORHOOD, EXTREME_VERTEX };

	template<typename Number, ORTHO_TYPE Type = ORTHO_TYPE::VERTEX>
	class OrthogonalPolyhedron
	{
	private:
		//VertexContainer<Number> mVertices; // the container of all vertices
		Grid<Number> mGrid; // the grid the polyhedron is defined on
		mutable Box<Number> mBoundaryBox; // the cached boundary box (mutable to allow performance optimization)
		mutable bool mBoxUpToDate = false;

	public:

		/***********************************************************************
		 * Constructors
		 ***********************************************************************/

		OrthogonalPolyhedron();
		OrthogonalPolyhedron(const Vertex<Number>& _vertex);
		OrthogonalPolyhedron(const VertexContainer<Number>& vertices);
		OrthogonalPolyhedron(const std::set<Vertex<Number> >& points);
		OrthogonalPolyhedron(const std::vector<Vertex<Number> >& points);
		OrthogonalPolyhedron(const OrthogonalPolyhedron<Number, Type>& copy);
		OrthogonalPolyhedron(const OrthogonalPolyhedron<Number, Type>&& move);

		/***********************************************************************
		 * Getter, Setter
		 ***********************************************************************/

		std::vector<carl::Variable> variables() const;
		std::vector<Vertex<Number>> vertices() const;
		Box<Number> boundaryBox() const;
		void addVertex(const Vertex<Number>& _vertex);
		void addVertices(const std::vector<Vertex<Number>>& _vertices);

		bool empty() const;
		unsigned size() const;
		bool isVertex(const Point<Number>& _point) const;
		bool isOnIEdge(const Point<Number>& _point, unsigned i) const;
		bool isInternal(const Point<Number>& _point) const;
		bool isExternal(const Point<Number>& _point) const;
		bool color(const Point<Number>& _point) const;

		std::vector<Point<Number>> iNeighborhood(const Point<Number>& _point, unsigned i) const;
		std::vector<Point<Number>> iNegNeighborhood(const Point<Number>& _point, unsigned i) const;
		std::vector<Point<Number>> neighborhood(const Point<Number>& _point) const;

		std::vector<Point<Number>> iSlice(unsigned i, Number pos) const;
		OrthogonalPolyhedron<Number,Type> iProjection(unsigned i) const;

		/***********************************************************************
		 * Geometric Object functions
		 ***********************************************************************/
		unsigned int dimension() const;
		OrthogonalPolyhedron<Number, Type> linearTransformation(const matrix_t<Number>& A, const vector_t<Number>& b) const;
		OrthogonalPolyhedron<Number, Type> minkowskiSum(const OrthogonalPolyhedron<Number, Type>& rhs) const;
		OrthogonalPolyhedron<Number, Type> intersect(const OrthogonalPolyhedron<Number, Type>& rhs) const;
		OrthogonalPolyhedron<Number, Type> hull() const;
		bool contains(const Point<Number>& point) const;
		bool contains(const OrthogonalPolyhedron<Number,Type>& _other) const;
		OrthogonalPolyhedron<Number, Type> unite(const OrthogonalPolyhedron<Number, Type>& rhs) const;

		/***********************************************************************
		 * Auxiliary functions
		 ***********************************************************************/
		std::vector<std::vector<Point<Number>>> preparePlot(unsigned _xDim=0, unsigned _yDim=1) const;

		/***********************************************************************
		 * Operators
		 ***********************************************************************/

		OrthogonalPolyhedron<Number, Type>& operator= ( const OrthogonalPolyhedron<Number, Type>& _in ) = default;
		OrthogonalPolyhedron<Number, Type>& operator= ( OrthogonalPolyhedron<Number, Type>&& ) = default;

		friend bool operator==(const OrthogonalPolyhedron<Number, Type>& op1, const OrthogonalPolyhedron<Number, Type>& op2) {
			return op1.mGrid == op2.mGrid;
		}

		friend bool operator!=(const OrthogonalPolyhedron<Number, Type>& op1, const OrthogonalPolyhedron<Number, Type>& op2) {
			return op1.mGrid != op2.mGrid;
		}

		friend std::ostream& operator<<(std::ostream& ostr, const OrthogonalPolyhedron<Number, Type>& p) {
			ostr << "(";
			for(const auto& vertex : p.mGrid.vertices())
				ostr << vertex << ", ";
			ostr << ")";
			return ostr;
		}

	private:
		void updateBoundaryBox() const;

	};

}//namespace

#include "OrthogonalPolyhedron.tpp"
