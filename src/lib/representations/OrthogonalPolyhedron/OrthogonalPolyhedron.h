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
#include "NeighbourhoodContainer.h"
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
        
        // the grid the polyhedron is defined on
        Grid<Number> mGrid;
        
        // the neighbourhood container which maps points to a set of vertices
        NeighbourhoodContainer<Number> mNeighbourhood;
        
        // the cached boundary box
        Box<Number> mBoundaryBox;
        bool mBoxUpToDate = false;
        
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
         * Constructor initialising values.
         * @param vertices
         * @param induceGrid
         */
        OrthogonalPolyhedron(const VertexContainer<Number>& vertices, const bool induceGrid = true)
                : mVertices(vertices), mVariables(vertices.variables())
        {
            mGrid.reserveInducedGrid(mVariables);
            if (induceGrid)
            {
                mGrid.induceGrid(vertices.vertices());
            }
        }
        
        /**
         * Copy constructor
         * @param copy
         */
        OrthogonalPolyhedron(const OrthogonalPolyhedron<Number>& copy)
        {
            mVertices = copy.mVertices;
            mGrid = copy.mGrid;
            mNeighbourhood = copy.mNeighbourhood;
            mBoundaryBox = copy.mBoundaryBox;
            mBoxUpToDate = copy.mBoxUpToDate;
        }
        
        /***********************************************************************
         * Geometric Object functions
         ***********************************************************************/
        
        unsigned int dimension();		
        bool linearTransformation(OrthogonalPolyhedron<Number>& result);
        bool minkowskiSum(OrthogonalPolyhedron<Number>& result, const OrthogonalPolyhedron<Number>& rhs);
        bool intersect(OrthogonalPolyhedron<Number>& result, const OrthogonalPolyhedron<Number>& rhs);
        bool hull(OrthogonalPolyhedron<Number>& result);
        bool contains(const Point<Number>& point);
        bool unite(OrthogonalPolyhedron<Number>& result, const OrthogonalPolyhedron<Number>& rhs);
        
        /***********************************************************************
         * Other functions
         ***********************************************************************/
        
        bool empty() const;
        std::vector<carl::Variable> variables() const;
        Box<Number> boundaryBox();
        
        /***********************************************************************
         * Operators
         ***********************************************************************/

        friend bool operator==(const OrthogonalPolyhedron<Number> & op1, const OrthogonalPolyhedron<Number> & op2)
        {
            return op1.mVertices == op2.mVertices;
        }

        friend bool operator!=(const OrthogonalPolyhedron<Number> & op1, const OrthogonalPolyhedron<Number> & op2)
        {
            return op1.mVertices != op2.mVertices;
        }
        
    private:
        
        void updateBoundaryBox();
        
    };
    
}//namespace

#include "OrthogonalPolyhedron.tpp"

