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
	template<typename Number>
	class OrthogonalPolyhedron
	{
	private:
		
		// the container of all vertices
		VertexContainer<Number> mVertices;
		
		// the induced vertices connected to the grid
		//VertexContainer<Number> mInducedVertices;
		
		// the grid the polyhedron is defined on
		mutable Grid<Number> mGrid;
		
		// the color of the origin
		//bool mOriginColor = false;
		
		// the neighborhood container which maps points to a set of vertices
		mutable NeighborhoodContainer mNeighborhood;
		
		// the cached boundary box (mutable to allow performance optimization)
		mutable Box<Number> mBoundaryBox;
		mutable bool mBoxUpToDate = false;
		
		// the variables
		std::vector<carl::Variable> mVariables;
		
	public:
		
		/***********************************************************************
		 * Constructors
		 ***********************************************************************/
		
		/**
		 * @brief Default constructor.
		 */
		OrthogonalPolyhedron() {}
		
		/**
		 * @brief Constructor for a list of vertices.
		 * @details The vertices represent an orthogonal polyhedron. The constructor extracts the variables and induces a grid according to
		 * the vertices given.
		 * 
		 * @param vertices A non-empty VertexContainer
		 */
		OrthogonalPolyhedron(const VertexContainer<Number>& vertices) : mVertices(vertices) {
			//mOriginColor = vertices.originIsVertex();
			mVariables = vertices.variables();
			mGrid.induceGrid(vertices.vertices());
			//vSet<Number> inducedVertices = mGrid.translateToInduced(vertices.vertices());
			//mInducedVertices = VertexContainer<Number>(inducedVertices);
		}

		/**
		 * Constructor getting a list of points which should be contained in the orthogonal polyhedron.
		 * @todo implement
		 * @param points
		 */
		OrthogonalPolyhedron(const std::set<Point<Number> >& points) {
			// TODO compute the orthogonal polyhedron around the convex hull of all points
		}
		
		/**
		 * @brief Copy constructor.
		 * @details Copy constructor which (should) makes a deep copy of the passed original.
		 * 
		 * @param copy The original orthogonal polyhedron to be copied.
		 */
		OrthogonalPolyhedron(const OrthogonalPolyhedron<Number>& copy) :
			mVertices(copy.mVertices),
			//mInducedVertices(copy.mInducedVertices),
			mGrid(copy.mGrid),
			//mOriginColor(copy.mOriginColor),
			mNeighborhood(copy.mNeighborhood),
			mBoundaryBox(copy.mBoundaryBox),
			mBoxUpToDate(copy.mBoxUpToDate),
			mVariables(copy.mVariables)
		{}
		
		/***********************************************************************
		 * Geometric Object functions
		 ***********************************************************************/
		
		unsigned int dimension() const;
		OrthogonalPolyhedron<Number> linearTransformation(const matrix_t<Number>& A, const vector_t<Number>& b = vector_t<Number>()) const;
		OrthogonalPolyhedron<Number> minkowskiSum(const OrthogonalPolyhedron<Number>& rhs) const;
		OrthogonalPolyhedron<Number> intersect(const OrthogonalPolyhedron<Number>& rhs) const;
		OrthogonalPolyhedron<Number> hull() const;
		bool contains(const Point<Number>& point) const;
		OrthogonalPolyhedron<Number> unite(const OrthogonalPolyhedron<Number>& rhs) const;
		
		/***********************************************************************
		 * Other functions
		 ***********************************************************************/
		
		bool empty() const;
		std::vector<carl::Variable> variables() const;
		Box<Number> boundaryBox() const;
		
		/***********************************************************************
		 * Operators
		 ***********************************************************************/

		OrthogonalPolyhedron<Number>& operator= ( const OrthogonalPolyhedron<Number>& _in ) = default;
		OrthogonalPolyhedron<Number>& operator= ( OrthogonalPolyhedron<Number>&& ) = default;

		friend bool operator==(const OrthogonalPolyhedron<Number>& op1, const OrthogonalPolyhedron<Number>& op2) {
			return op1.mVertices == op2.mVertices;
		}

		friend bool operator!=(const OrthogonalPolyhedron<Number>& op1, const OrthogonalPolyhedron<Number>& op2) {
			return op1.mVertices != op2.mVertices;
		}
		
		friend std::ostream& operator<<(std::ostream& ostr, const OrthogonalPolyhedron<Number>& p) {
			ostr << "(";
			for(const auto& vertex : p.mVertices)
				ostr << vertex << ", ";
			ostr << ")";
			return ostr;
		}

	private:
		void updateBoundaryBox() const;
		bool containsInduced(const Point<int>& inducedPoint) const;
		void calculatePotentialVertices(vSet<Number>& potentialVertices, const vSet<Number>& vertices1, const vSet<Number>& vertices2) const;
		bool checkVertexCondition(const Vertex<int>& vertex, const std::map<Point<int>, bool>& coloring) const;
		
	};
	
}//namespace

#include "OrthogonalPolyhedron.tpp"

