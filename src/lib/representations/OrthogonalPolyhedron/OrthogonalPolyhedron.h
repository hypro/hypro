/* 
 * @file    OrthogonalPolyhedron.h
 * @author  Sebastian Junges
 * @author  Benedikt Seidl
 *
 * @since   2014-03-17
 * @version 2014-05-28
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
    class OrthogonalPolyhedron : hypro::GeometricObject<Number>
    {
    private:
        
        // the container of all vertices
        VertexContainer<Number> mVertices;
        
        // the induced vertices connected to the grid
        //VertexContainer<Number> mInducedVertices;
        
        // the grid the polyhedron is defined on
        Grid<Number> mGrid;
        
        // the color of the origin
        //bool mOriginColor = false;
        
        // the neighborhood container which maps points to a set of vertices
        mutable NeighborhoodContainer<Number> mNeighborhood;
        
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
         * Empty constructor
         */
        OrthogonalPolyhedron() {}
        
        /**
         * Constructor getting a list of vertices which represent an orthogonal polyhedron.
         * 
         * @todo does it really make sense to make induceGrid optional?
         * @todo actually validate the vertices
         * 
         * @param vertices a non-empty VertexContainer
         * @param induceGrid true by default
         */
        OrthogonalPolyhedron(const VertexContainer<Number>& vertices, const bool induceGrid = true) : mVertices(vertices) {
            //mOriginColor = vertices.originIsVertex();
            mVariables = vertices.variables();
            mGrid.reserveInducedGrid(mVariables);
            if (induceGrid)
            {
                    mGrid.induceGrid(vertices.vertices());
                    mGrid.insertVerticesInMap(vertices.vertices());
                    //vSet<Number> inducedVertices = mGrid.translateToInduced(vertices.vertices());
                    //mInducedVertices = VertexContainer<Number>(inducedVertices);
            }
        }

        /**
         * Constructor getting a list of points which should be contained in the orthogonal polyhedron.
         *
         * @param points
         */
        OrthogonalPolyhedron(const std::set<Point<Number> >& points) {
            // TODO compute the orthogonal polyhedron around the convex hull of all points
        }
        
        /**
         * Copy constructor
         * @param copy
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
        bool linearTransformation(OrthogonalPolyhedron<Number>& result, const matrix& A, const vector& b = vector()) const;
        bool minkowskiSum(OrthogonalPolyhedron<Number>& result, const OrthogonalPolyhedron<Number>& rhs) const;
        bool intersect(OrthogonalPolyhedron<Number>& result, const OrthogonalPolyhedron<Number>& rhs) const;
        bool hull(OrthogonalPolyhedron<Number>& result) const;
        bool contains(const Point<Number>& point) const;
        bool unite(OrthogonalPolyhedron<Number>& result, const OrthogonalPolyhedron<Number>& rhs) const;
        
        /***********************************************************************
         * Other functions
         ***********************************************************************/
        
        bool empty() const;
        std::vector<carl::Variable> variables() const;
        Box<Number> boundaryBox() const;
        
        /***********************************************************************
         * Operators
         ***********************************************************************/

        friend bool operator==(const OrthogonalPolyhedron<Number>& op1, const OrthogonalPolyhedron<Number>& op2) {
            return op1.mVertices == op2.mVertices;
        }

        friend bool operator!=(const OrthogonalPolyhedron<Number>& op1, const OrthogonalPolyhedron<Number>& op2) {
            return op1.mVertices != op2.mVertices;
        }
        
        friend std::ostream& operator<<(std::ostream& ostr, const OrthogonalPolyhedron<Number>& p) {
            return ostr << p.mVertices;
        }

    private:
        
        void updateBoundaryBox() const;
        bool containsInduced(const Point<Number>& inducedPoint) const;
        void calculatePotentialVertices(vSet<Number>& potentialVertices, const vSet<Number>& vertices1, const vSet<Number>& vertices2) const;
        bool checkVertexCondition(const Vertex<Number>& vertex, const std::map<Point<Number>, bool>& coloring) const;
        
    };
    
}//namespace

#include "OrthogonalPolyhedron.tpp"

