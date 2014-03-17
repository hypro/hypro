/* 
 * @file    OrthogonalPolyhedron.h
 * @author  Sebastian Junges
 * @author  Benedikt Seidl
 *
 * @since   2014-03-17
 * @version 2014-03-17
 */

#pragma once

#include "../../datastructures/Point.h"
#include "../../datastructures/Vertex.h"
#include "../../datastructures/VertexContainer.h"
#include "../Box/Box.h"
#include "../GeometricObject.h"
#include "NeighbourhoodContainer.h"

#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <fstream>

namespace hypro
{

    enum PolyhedronOrtRepresentation {
        VERTEX, NEIGHBOUR, EXTREMEVERTEX
    };
    
    
    template<typename Number>
    class OrthogonalPolyhedron : hypro::GeometricObject<Number>
    {
    private:
        unsigned mNrVertices;

        bool mOriginColour;
        VertexContainer<Number> mVertices;
        VertexContainer<Number> mInducedVertices;
        VertexContainer<Number> mExtremeVertices;

        NeighbourhoodContainer<Number> mNeighbourhood;

        bool mBoxUpToDate;
        Box<Number> mBox;

        bool mGridInitialized;
        std::map<Point<Number>, bool> mGrid;

        std::vector<Point<Number> > mBoundaryBox;
        Point<Number> mBoundary;
        bool boundaryIsVertex;

        PolyhedronOrtRepresentation mRepresentation;

        bool mInduced;
        std::vector< std::vector<Number> > mInducedGridPoints;

        //Logger mLogger;
    public:
        OrthogonalPolyhedron();
        OrthogonalPolyhedron(std::map<Point<Number>, bool>, Point<Number> bounds, unsigned dim);
        OrthogonalPolyhedron(Vertex<Number>* vertices, unsigned nrVertices, unsigned dim, Point<Number> boundary);
        
        OrthogonalPolyhedron(vVec<Number> vertexList, unsigned dim);
        OrthogonalPolyhedron(vVec<Number> vertexList, unsigned dim, Point<Number> boundary);
        OrthogonalPolyhedron(vVec<Number> vertexList, unsigned dim, vVec<Number> extremeVertexList);
        OrthogonalPolyhedron(vVec<Number> vertexList, unsigned dim, NeighbourhoodContainer<Number> neighbourhoods);
    };
    
}//namespace

#include "OrthogonalPolyhedron.tpp"

