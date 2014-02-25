/** 
 * @file   polyhedron_ort.h
 * Created on May 12, 2011
 * Last modified June 23, 2011
 * 
 * @author Sebastian Junges
 *
 *  
 */
#ifndef _POLYHEDRON_ORT_H
#define _POLYHEDRON_ORT_H

#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <fstream>
#include "settings.h"
#include "polyhedron.h"
#include "box.h"
#include "vertex.h"
#include "vertexContainer.h"
#include "neighbourhoodContainer.h"

// Log4cplus
#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <iomanip>

namespace reachLin {
    
    enum PolyhedronOrtRepresentation {
        VERTEX, NEIGHBOUR, EXTREMEVERTEX
    };

    class PolyhedronOrt : public Polyhedron {
    public:
        PolyhedronOrt();
        PolyhedronOrt(std::map<Point, bool>, Point bounds, unsigned dim);
        PolyhedronOrt(Vertex* vertices, unsigned nrVertices, unsigned dim, Point boundary);
        
        PolyhedronOrt(std::vector<Vertex> vertexList, unsigned dim);
        PolyhedronOrt(std::vector<Vertex> vertexList, unsigned dim, Point boundary);
        PolyhedronOrt(std::vector<Vertex> vertexList, unsigned dim, std::vector<Vertex> extremeVertexList);
        PolyhedronOrt(std::vector<Vertex> vertexList, unsigned dim, NeighbourhoodContainer neighbourhoods);

        virtual ~PolyhedronOrt();

        bool isEmpty();
        bool isUniversal();

        bool isMember(Point pX, bool useOrig = false);

        std::vector<Vertex> getVertices();
        bool isVertex(Point* pX);
        bool checkVertexCondition(const Point& p);

        PolyhedronOrt calculateIntersection(PolyhedronOrt& p2);
        PolyhedronOrt invert(Point boundary);
        PolyhedronOrt calculateUnion(PolyhedronOrt& p2);
        PolyhedronOrt calculateUnion(PolyhedronOrt& p2,const Point& boundary);

        void move(const Point& p);

        void translateToNeighbourhoodRepresentation(bool clean = true);
        void translateToExtremeVertexRepresentation(bool clean = true);
        void induceGrid();
        bool isInduced();

        void clear();

        PolyhedronOrtRepresentation getRepresentation();
        void printGrid(); 
        
        int  getNrVertices() const { return mNrVertices;}
        Point getBoundary() const; 
         
         friend std::ostream& operator<<(std::ostream& ostr, const PolyhedronOrt& pol);
        
        friend class PolyhedronParser;

    private:
        void preInit();
        void postInit();
        
        void insertVerticesInMap(VertexContainerIt begin, VertexContainerIt end, std::map<Point,bool>& map);
        
        //IsMembership helper-functions.
        bool checkAPoint(const Point& pX);
        std::vector<Vertex> calculateBoundaryBox(const Point& boundary);
        std::vector<Vertex> calculateBoundaryBoxRec(unsigned dim, std::vector<Vertex> & boundaryBox);
        bool calculateOriginColour();

        bool isMemberBox(const Point& pX);

        bool membershipRecursiveVertex(const Point& pX);
        bool membershipNeighbour(const Point& pX);
        bool membershipExtremeVertex(const Point& pX);

        VertexContainerIt getVerticesIteratorBegin(bool extreme = false);
        VertexContainerIt getVerticesIteratorEnd(bool extreme = false);

        void verticesOnBoundaryRec(const Point& pt, bool color, unsigned dim);
        void verticesOnBoundary(const Point& boundary);
        Point calculateInduced(const Point& x);
        Vertex calculateInduced(const Point& x, bool c);

        void ReserveInducedGrid();

        void setRepresentation(PolyhedronOrtRepresentation repr);
        void translateNeighbourToExtreme();
        void translateVertexToExtreme();



        std::list<Vertex> getSmallerVertices(const Point& p, bool extreme = false);

        unsigned mNrVertices;

        bool mOriginColour;
        VertexContainer mVertices;
        VertexContainer mInducedVertices;
        VertexContainer mExtremeVertices;

        NeighbourhoodContainer mNeighbourhood;

        bool mBoxUpToDate;
        Box mBox;

        bool mGridInitialized;
        std::map<Point, bool> mGrid;

        std::vector<Point> mBoundaryBox;
        Point mBoundary;
        bool boundaryIsVertex;

        PolyhedronOrtRepresentation mRepresentation;

        bool mInduced;
        std::vector< std::vector<int> > mInducedGridPoints;

        Logger mLogger;
    };
}
#endif