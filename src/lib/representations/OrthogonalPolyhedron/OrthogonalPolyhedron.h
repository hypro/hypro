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

    private:
        void preInit();
        void postInit();
        
        void insertVerticesInMap(VertexContainerIt<Number> begin, VertexContainerIt<Number> end, std::map<Point<Number>, bool>& map);
        
        //IsMembership helper-functions.
        bool checkAPoint(const Point<Number>& pX);
        vVec<Number> calculateBoundaryBox(const Point<Number>& boundary);
        vVec<Number> calculateBoundaryBoxRec(unsigned dim, vVec<Number> & boundaryBox);
        bool calculateOriginColour();

        bool isMemberBox(const Point<Number>& pX);

        bool membershipRecursiveVertex(const Point<Number>& pX);
        bool membershipNeighbour(const Point<Number>& pX);
        bool membershipExtremeVertex(const Point<Number>& pX);

        VertexContainerIt<Number> getVerticesIteratorBegin(bool extreme = false);
        VertexContainerIt<Number> getVerticesIteratorEnd(bool extreme = false);

        void verticesOnBoundaryRec(const Point<Number>& pt, bool color, unsigned dim);
        void verticesOnBoundary(const Point<Number>& boundary);
        Point<Number> calculateInduced(const Point<Number>& x);
        Vertex<Number> calculateInduced(const Point<Number>& x, bool c);

        void ReserveInducedGrid();

        void setRepresentation(PolyhedronOrtRepresentation repr);
        void translateNeighbourToExtreme();
        void translateVertexToExtreme();

        vList<Number> getSmallerVertices(const Point<Number>& p, bool extreme = false);
    };
    
}//namespace

#include "OrthogonalPolyhedron.tpp"

