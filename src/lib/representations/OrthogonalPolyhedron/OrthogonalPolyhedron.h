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
        // the neighbourhood container which maps points to a set of vertices
        NeighbourhoodContainer<Number> mNeighbourhood;
        
        // the container of all vertices
        VertexContainer<Number> mVertices;
        
        // the cached boundary box
        bool mBoxUpToDate;
        Box<Number> mBox;

        /*
        bool mOriginColour;
        unsigned mNrVertices;
        
        VertexContainer<Number> mVertices;
        VertexContainer<Number> mInducedVertices;
        VertexContainer<Number> mExtremeVertices;

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
        */

        //Logger mLogger;
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
         * @param neighbourhood
         * @param vertices
         */
        OrthogonalPolyhedron(const NeighbourhoodContainer<Number>& neighbourhood, const VertexContainer<Number>& vertices)
                : mNeighbourhood(neighbourhood), mVertices(vertices) {}
        
        /**
         * Copy constructor
         * @param copy
         */
        OrthogonalPolyhedron(const OrthogonalPolyhedron<Number>& copy);
        
        /*********
         * ALT
         *********/
        //OrthogonalPolyhedron(std::map<Point<Number>&, bool>, Point<Number>& bounds, unsigned dim);
        //OrthogonalPolyhedron(const Vertex<Number>* vertices, unsigned nrVertices, unsigned dim/*, Point<Number>& boundary*/);
        
        //OrthogonalPolyhedron(const vVec<Number>& vertexList, unsigned dim);
        //OrthogonalPolyhedron(vVec<Number>& vertexList, unsigned dim, Point<Number>& boundary);
        //OrthogonalPolyhedron(const vVec<Number>& vertexList, unsigned dim, const vVec<Number>& extremeVertexList);
        //OrthogonalPolyhedron(const vVec<Number>& vertexList, unsigned dim, const NeighbourhoodContainer<Number>& neighbourhoods);
        
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
        bool isEmpty();
        bool isUniversal();

        bool isMember(Point<Number>& pX, bool useOrig = false);

        vVec<Number> getVertices();
        bool isVertex(Point<Number>* pX);
        bool checkVertexCondition(const Point<Number>& p);

        OrthogonalPolyhedron<Number> calculateIntersection(OrthogonalPolyhedron<Number>& p2);
        OrthogonalPolyhedron<Number> invert(Point<Number>& boundary);
        OrthogonalPolyhedron<Number> calculateUnion(OrthogonalPolyhedron<Number>& p2);
        OrthogonalPolyhedron<Number> calculateUnion(OrthogonalPolyhedron<Number>& p2, const Point<Number>& boundary);

        void move(const Point<Number>& p);

        void translateToNeighbourhoodRepresentation(bool clean = true);
        void translateToExtremeVertexRepresentation(bool clean = true);
        void induceGrid();
        bool isInduced();

        void clear();

        PolyhedronOrtRepresentation getRepresentation();
        void printGrid(); 
        
        inline unsigned getNrVertices() const { return mNrVertices; }
        inline unsigned getDimension() const { return mVertices.dimension(); }
        Point<Number> getBoundary() const; 
         
        friend std::ostream& operator<<(std::ostream& ostr, const OrthogonalPolyhedron<Number>& pol);
        
        //friend class PolyhedronParser;

    private:
        void preInit();
        void postInit();
        void calculateBox();
        void reserveInducedGrid();
        
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

        void setRepresentation(PolyhedronOrtRepresentation repr);
        void translateNeighbourToExtreme();
        void translateVertexToExtreme();

        vList<Number> getSmallerVertices(const Point<Number>& p, bool extreme = false);
    };
    
}//namespace

#include "OrthogonalPolyhedron.tpp"

