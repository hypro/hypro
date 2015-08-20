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
		std::vector<carl::Variable> mVariables; // the variables
		
	public:
		
		/***********************************************************************
		 * Constructors
		 ***********************************************************************/
		
		OrthogonalPolyhedron();
		OrthogonalPolyhedron(const Vertex<Number>& _vertex);
		OrthogonalPolyhedron(const VertexContainer<Number>& vertices);
		OrthogonalPolyhedron(const std::set<Vertex<Number> >& points);
		OrthogonalPolyhedron(const OrthogonalPolyhedron<Number, Type>& copy);
		
		/***********************************************************************
		 * Getter, Setter
		 ***********************************************************************/

		std::vector<carl::Variable> variables() const;
		std::vector<Vertex<Number>> vertices() const;
		Box<Number> boundaryBox() const;
		void addVertex(const Vertex<Number>& _vertex);
		void addVertices(const std::vector<Vertex<Number>>& _vertices);
		unsigned int dimension() const;

		/***********************************************************************
		 * Geometric Object functions
		 ***********************************************************************/
		
		OrthogonalPolyhedron<Number, Type> linearTransformation(const matrix_t<Number>& A, const vector_t<Number>& b = vector_t<Number>()) const;
		OrthogonalPolyhedron<Number, Type> minkowskiSum(const OrthogonalPolyhedron<Number, Type>& rhs) const;
		OrthogonalPolyhedron<Number, Type> intersect(const OrthogonalPolyhedron<Number, Type>& rhs) const;
		OrthogonalPolyhedron<Number, Type> hull() const;
		bool contains(const Point<Number>& point) const;
		OrthogonalPolyhedron<Number, Type> unite(const OrthogonalPolyhedron<Number, Type>& rhs) const;
		
		/***********************************************************************
		 * Other functions
		 ***********************************************************************/
		
		bool empty() const;
		
		
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
		bool containsInduced(const Point<int>& inducedPoint) const;
		void calculatePotentialVertices(vSet<Number>& potentialVertices, const vSet<Number>& vertices1, const vSet<Number>& vertices2) const;
		bool checkVertexCondition(const Vertex<int>& vertex, const std::map<Point<int>, bool>& coloring) const;
		
	};
	
}//namespace

#include "OrthogonalPolyhedron.tpp"

