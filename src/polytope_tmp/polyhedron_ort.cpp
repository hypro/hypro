/** 
 * @file   polyhedron_ort.cpp
 * Created on Mar 12, 2011
 * Last modified June 23, 2011
 * 
 * @author Sebastian Junges
 */
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <math.h>
#include <list>
#include <vector>
#include <boost/detail/container_fwd.hpp>
#include "defines.h"
#include <boost/foreach.hpp>

#include "polyhedron_ort.h"

using namespace std;
using namespace log4cplus;

namespace reachLin {

    PolyhedronOrt::PolyhedronOrt() : Polyhedron(4), mBox(Box(4)) {
        ;

    }

    /**
     * @brief: A new Orthogonal Polyhedron.
     */
    PolyhedronOrt::PolyhedronOrt(Vertex* vertices, unsigned nrVertices, unsigned dim, Point boundary) :
    Polyhedron(dim),
    mRepresentation(VERTEX),
    mNrVertices(nrVertices),
    mGridInitialized(false),
    mBoxUpToDate(false),
    mBoundary(boundary),
    mVertices(VertexContainer(dim)),
    mBox(Box(dim)) {
        preInit();
        for (unsigned i = 0; i < nrVertices; i++)
            mVertices.insert(vertices[i]);
        postInit();
    }

    /**
     *
     * @param vertexList
     * @param dim
     * @return
     */
    PolyhedronOrt::PolyhedronOrt(std::vector<Vertex> vertexList, unsigned dim) :
    Polyhedron(dim),
    mRepresentation(VERTEX),
    mNrVertices(vertexList.size()),
    mVertices(VertexContainer(dim)),
    mBox(Box(dim)) {
        preInit();
        mVertices.insert(vertexList.begin(), vertexList.end());
        mBox.calculateBox(mVertices.begin(), mVertices.end());
        mBoxUpToDate = true;
        mBoundary = mBox.getMax();
        postInit();
    }

    /*
    PolyhedronOrt::PolyhedronOrt(vVecIt vertexListBegin, vVecIt vertexListEnd, vVecIt neighbourListBegin, vVecIt neighbourListEnd, unsigned dim) :
    Polyhedron(dim),
    mRepresentation(VERTEX),
            mVertices(VertexContainer(dim)), 
            mBox(Box(dim))
    {
        preInit();
        mVertices.insert(vertexListBegin,vertexListEnd);
        mNrVertices = mVertices.size();
        mBoxUpToDate = true;
        mBoundary = mBox.getMax();
        postInit();
    }
     */

    /**
     *
     * @param vertexList
     * @param dim
     * @param boundary
     * @return
     */
    PolyhedronOrt::PolyhedronOrt(std::vector<Vertex> vertexList, unsigned dim, Point boundary) :
    Polyhedron(dim),
    mRepresentation(VERTEX),
    mNrVertices(vertexList.size()),
    mBoundary(boundary),
    mVertices(VertexContainer(dim)),
    mBox(Box(dim)) {
        preInit();
        mVertices.insert(vertexList.begin(), vertexList.end());
        postInit();
    }

    /**
     * A constructor where additionally the list of extreme Vertices can be passed. Should only be used if the list of EV
     * is complete.
     * 
     * @param vertexList
     * @param extremeVertexList
     * @param dim
     * @return
     */
    PolyhedronOrt::PolyhedronOrt(std::vector<Vertex> vertexList, unsigned dim, std::vector<Vertex> extremeVertexList) :
    Polyhedron(dim),
    mRepresentation(EXTREMEVERTEX),
    mNrVertices(vertexList.size()),
    mVertices(VertexContainer(dim)),
    mBox(Box(dim)) {
        preInit();
        mVertices.insert(vertexList.begin(), vertexList.end());
        mExtremeVertices.insert(extremeVertexList.begin(), extremeVertexList.end());

        if (mNrVertices != mVertices.size()) {
            LOG4CPLUS_WARN(mLogger, "Inputlenght is not equal to number of vertices.");
        }

        //TODO refactor
        mBox.calculateBox(mVertices.begin(), mVertices.end());
        mBoxUpToDate = true;
        mBoundary = mBox.getMax();


        LOG4CPLUS_INFO(mLogger, "Number of vertices is " << mNrVertices);
        postInit();
    }

    PolyhedronOrt::PolyhedronOrt(std::vector<Vertex> vertexList, unsigned dim, NeighbourhoodContainer neighbourhoods) :
    Polyhedron(dim),
    mRepresentation(NEIGHBOUR),
    mNrVertices(vertexList.size()),
    mVertices(VertexContainer(dim)),
    mBox(Box(dim)) {

        preInit();
        mVertices.insert(vertexList.begin(), vertexList.end());
        mNeighbourhood = neighbourhoods;
        
        if (mNrVertices != mVertices.size()) {
            LOG4CPLUS_WARN(mLogger, "Inputlenght is not equal to number of vertices.");
        }

        //TODO refactor
        mBox.calculateBox(mVertices.begin(), mVertices.end());
        mBoxUpToDate = true;
        mBoundary = mBox.getMax();


        LOG4CPLUS_INFO(mLogger, "Number of vertices is " << mNrVertices);
        postInit();


    }

    PolyhedronOrt::PolyhedronOrt(std::map<Point, bool> grid, Point bounds, unsigned dim) :
    Polyhedron(dim),
    mGridInitialized(false),
    mVertices(VertexContainer(dim)),
    mBox(Box(bounds.getCoordinates())) {
        mLogger = Logger::getInstance("reachLin.PolyhedronOrt");
        mGrid = grid;
        mDimension = dim;
        mBoxUpToDate = true;
        mInduced = false;
        mRepresentation = VERTEX;
        mOriginColour = grid.begin()->second;
        Point p(dim);
        map<Point, bool>::iterator it;
        map<Point, bool>::iterator end = mGrid.end();
        if (mOriginColour) {
            mVertices.insert(p, true);
        }
        it = mGrid.begin();
        while (p != bounds) {
            p.nextPointOnGrid(bounds);
            it++;
            if (it == end) {
                mGrid.insert(std::pair<Point, bool>(p, false));
                if (checkVertexCondition(p)) mVertices.insert(p, false);
                while (p != bounds) {
                    p.nextPointOnGrid(bounds);
                    mGrid.insert(std::pair<Point, bool>(p, false));
                    if (checkVertexCondition(p)) mVertices.insert(p, false);
                }
                break;
            }

            if (it->first != p) {
                mGrid.insert(std::pair<Point, bool>(p, false));
                it--;
            }

            if (checkVertexCondition(p)) {
                mVertices.insert(p, it->second);
            }
        }
        postInit();
        /*for (it = mVertices.begin(); it != mVertices.end(); it++) {
            std::cout << it->first.toString(true) << endl;
        }*/
    }

    void PolyhedronOrt::preInit() {

        mInduced = false;
        mGridInitialized = false;
        mBoxUpToDate = false;
        mLogger = Logger::getInstance("reachLin.PolyhedronOrt");

        LOG4CPLUS_INFO(mLogger, "New polyhedron created");
        ReserveInducedGrid();
    }

    void PolyhedronOrt::postInit() {
        mNrVertices = mVertices.size();
        LOG4CPLUS_INFO(mLogger, "Number of vertices is " << mNrVertices);
        mOriginColour = calculateOriginColour();
        LOG4CPLUS_DEBUG(mLogger, "Origin is " << mOriginColour);

    }

    PolyhedronOrt::~PolyhedronOrt() {
    }

    void PolyhedronOrt::ReserveInducedGrid() {
        mInducedGridPoints.reserve(mDimension);
        std::vector<int> v;
        for (unsigned d = 0; d < mDimension; d++) {
            mInducedGridPoints.push_back(v);
        }
    }

    /**
     * @param p2
     * @return
     */
    PolyhedronOrt PolyhedronOrt::calculateIntersection(PolyhedronOrt& p2) {
        vector<Vertex> p1Vertices = getVertices();
        vector<Vertex> p2Vertices = p2.getVertices();
        set<Point> potentialVertices;

        //Push all vertices of Polyhedron 1 in the list of potential vertices for the intersection.
        for (unsigned i = 0; i < p1Vertices.size(); i++) {
            // Only after a quick check if they could be in the intersection.
            if (p2.isMemberBox(p1Vertices[i])) {
                potentialVertices.insert(p1Vertices[i]);
            }
        }

        //Push all the vertices of Polyhedron 2 in the list of potential vertices for the intersection
        for (unsigned i = 0; i < p2Vertices.size(); i++) {
            // Only after a quick check if they could be in the intersection.
            if (isMemberBox(p2Vertices[i])) {
                potentialVertices.insert(p2Vertices[i]);
            }
        }

        // Extend the list of potential vertices by the coordinate-wise maximum of all pairs of vertices.
        for (unsigned i = 0; i < p1Vertices.size(); i++) {
            for (unsigned j = 0; j < p2Vertices.size(); j++) {
                Point potential = Point::coordinateMax(p1Vertices[i], p2Vertices[j]);
                // Quick checks
                if (!isMemberBox(potential))
                    continue;
                if (!p2.isMemberBox(potential))
                    continue;

                potentialVertices.insert(potential);
            }
        }

        LOG4CPLUS_DEBUG(mLogger, "Potential points");

        foreach(Point p, potentialVertices) {
            LOG4CPLUS_DEBUG(mLogger, p.toString(true));
        }
        LOG4CPLUS_DEBUG(mLogger, "--------------");

        vector<Vertex> vertexList;
        // We have all potential Vertices in the set (without duplicates, its a set)
        // Now we check for all of them
        for (set<Point>::iterator it = potentialVertices.begin(); it != potentialVertices.end(); ++it) {
            // Output
            LOG4CPLUS_DEBUG(mLogger, "Point we check" << *it);
            bool couldBeAVertex = true;

            for (unsigned fixed = 0; fixed < mDimension; fixed++) {
                vector<Point> neighborsInFixed = it->getAllNeighborsForAFixedDimension(fixed);
                neighborsInFixed.push_back(*it);
                bool allEqual = true;

                Point neighbor;
                Point neighborPredecessor;
                bool neighborColor;
                bool neighborPredecessorColor;

                //Compare the neighborhoodcolours.
                //TODO change order of membershiptests if the one is smaller than the other.
                for (unsigned i = 0; i < neighborsInFixed.size(); i++) {
                    neighbor = neighborsInFixed[i];
                    neighborPredecessor = Point(neighbor).getPredecessorInDimension(fixed);

                    neighborColor = (isMember(neighbor) && p2.isMember(neighbor));
                    neighborPredecessorColor = (isMember(neighborPredecessor) && p2.isMember(neighborPredecessor));

                    if (neighborColor != neighborPredecessorColor) {
                        allEqual = false;
                        break;
                    }
                }
                // Point is not a vertex
                if (allEqual) {
                    LOG4CPLUS_DEBUG(mLogger, "Point is not a vertex");
                    LOG4CPLUS_TRACE(mLogger, "For fixed " << fixed);
                    couldBeAVertex = false;
                    //        fixed = mDimension;
                    break;
                }
            }
            // if couldBeAVertex is true here, *it is a vertex for sure.
            // Therefore we add it to the vertexList.
            if (couldBeAVertex) {
                Vertex v = Vertex(*it, false);
                v.setColor((isMember(v) && p2.isMember(v)));
                vertexList.push_back(v);
            }
        }

        // Output, all vertices
        cout << "Vertices: " << endl;
        for (unsigned i = 0; i < vertexList.size(); i++) {
            std::cout << vertexList[i].toString() << endl;
        }
        std::cout << "End vertices";

        // The resulting Polyhedron.
        // TODO improve boundary
        return PolyhedronOrt(vertexList, mDimension, mBoundary);
    }

    PolyhedronOrt PolyhedronOrt::calculateUnion(PolyhedronOrt& p2) {
        Point boundary = Point::coordinateMax(mBoundary, p2.mBoundary);
        return calculateUnion(p2, boundary);
    }

    /**
     *  @brief Calculates the Union of this Polyhedron and Polyhedron p2, and return a new Polyhedron representing the union.
     * Uses deMorgans Rules.
     * @param p2 Polyhedron
     * @param boundary boundary
     * @return The union of this an p2.
     *
     */
    PolyhedronOrt PolyhedronOrt::calculateUnion(PolyhedronOrt& p2, const Point& boundary) {
        LOG4CPLUS_INFO(mLogger, "Calculate Union");
        LOG4CPLUS_INFO(mLogger, "Invert p1");
        PolyhedronOrt inv1 = invert(boundary);
        LOG4CPLUS_INFO(mLogger, "Invert p2");
        PolyhedronOrt inv2 = p2.invert(boundary);
        LOG4CPLUS_INFO(mLogger, "Calculate Intersection");
        PolyhedronOrt invresult = inv1.calculateIntersection(inv2);
        LOG4CPLUS_INFO(mLogger, "Invert intersection");
        return invresult.invert(boundary);
    }

    /**
     * @brief emptiness check.
     * @return true if number of vertices equals 0.
     */
    bool PolyhedronOrt::isEmpty() {
        if (mNrVertices == 0) return true;
        return false;
    }

    /**
     * @brief universality check
     * For universality, only the cornerpoints are vertices, and the outermost corner has to be the boundary.
     * @return, true, if every point within boundary is a vertex. 
     */
    bool PolyhedronOrt::isUniversal() {
        if (mNrVertices != pow(mDimension, 2)) return false;
        return mVertices.isVertex(mBoundary).first;
    }

    /**
     *
     * @param boundary The point giving the maximal boundary.
     * @return A polyhedron representing the complement of the original. 
     */
    PolyhedronOrt PolyhedronOrt::invert(Point boundary) {
        vector<Vertex> vertices = getVertices();
        for (unsigned i = 0; i < vertices.size(); i++) {
            //Vertices on the outer boundary are always white.
            if (!vertices[i].haveEqualCoordinate(boundary)) {
                vertices[i].invertColor();
            }
            LOG4CPLUS_TRACE(mLogger, "vertices " << vertices[i]);
        }

        // Now we can calculate the colour of all the vertices on the boundary.
        //PolyhedronOrt inverted = PolyhedronOrt(vertices, mDimension);
        //inverted.verticesOnBoundary(boundary);
        vector<Vertex> boundPoints = calculateBoundaryBox(boundary);
        LOG4CPLUS_DEBUG(mLogger, "calculated Boundarybox");
        for (unsigned i = 0; i < boundPoints.size(); i++) {
            LOG4CPLUS_DEBUG(mLogger, "vertices " << boundPoints[i]);
        }

        vector<Vertex>::iterator it;
        //prepare the vector with enough size.
        vector<Vertex> inverted(boundPoints.size() + vertices.size());
        //symmetric difference needs to sorted lists/vectors.
        sort(vertices.begin(), vertices.end());
        sort(boundPoints.begin(), boundPoints.end());
        // All inner vertices + those points on the boundarybox that weren't vertices.
        it = set_symmetric_difference(vertices.begin(), vertices.end(), boundPoints.begin(), boundPoints.end(), inverted.begin());
        // shorten the vector.
        inverted.erase(it, inverted.end());
        // If this Polyhedron has a white origin, the inverted one has a black origin.
        LOG4CPLUS_DEBUG(mLogger, "Origin is " << mOriginColour);
        if (!mOriginColour) {
            inverted.front().setColor(true);
            LOG4CPLUS_DEBUG(mLogger, "Origin is vertex");
        }

        LOG4CPLUS_DEBUG(mLogger, "calculated vertices");
        for (unsigned i = 0; i < inverted.size(); i++) {
            LOG4CPLUS_DEBUG(mLogger, "vertices " << inverted[i]);
        }

        return PolyhedronOrt(inverted, mDimension, boundary);
    }

    /**
     * @brief Test if a point lies within the polyhedron
     * @param pointX Pointer to the point.
     * @param useOrig Deprecated
     * @return: true if inside, false if not.
     */
    bool PolyhedronOrt::isMember(Point pointX, bool useOrig) {
        bool result;
        LOG4CPLUS_DEBUG(mLogger, "Membershiptest for " << pointX);
        // Okay, it could be a member
        // For non-vertices we have to check neighbors.
        // Since we reuse a lot of information, we save it temporarily

        // Because we have far more points than vertices it is more efficient to copy the vertexmap in a workingmap,
        // than checking every point for being a vertex or not.
        // Than afterwards, we can just check if the point is already known. Thereby, we check the point for being a vertex implicitly.
        switch (mRepresentation) {
            case VERTEX:

                if (mInduced) pointX = calculateInduced(pointX);

                // Is it in the box?
                if (!isMemberBox(pointX)) {
                    LOG4CPLUS_TRACE(mLogger, "Out of Box");
                    return false;
                }
                if (mInduced) {
                    LOG4CPLUS_DEBUG(mLogger, "Calculating on induced grid");

                    //TODO reserve sufficient space so we dont need to reallocate the Grid all the time.
                    //copy (linear)
                    if (!mGridInitialized) {
                        insertVerticesInMap(mInducedVertices.begin(), mInducedVertices.end(), mGrid);
                        mGridInitialized = true;
                    }
                } else {
                    //TODO reserve sufficient space so we dont need to reallocate the Grid all the time.
                    //copy (linear)
                    if (!mGridInitialized) {
                        insertVerticesInMap(mVertices.begin(), mVertices.end(), mGrid);
                        mGridInitialized = true;
                    }
                }
                result = membershipRecursiveVertex(pointX);
                LOG4CPLUS_DEBUG(mLogger, result);
                return result;
                break;
            case NEIGHBOUR:
                return membershipNeighbour(pointX);
                break;
            case EXTREMEVERTEX:
                return membershipExtremeVertex(pointX);
                break;
        }


        /*TODO Should not be here, throw an error.*/
        LOG4CPLUS_ERROR(mLogger, "No Representation set.");
        return false;
    }

    /**
     * @brief Fast check if a point lies within a boxed boundary of the polyhedron
     * Updates the box if it isn't up to date.
     */
    bool PolyhedronOrt::isMemberBox(const Point& point) {
        if (!mBoxUpToDate) {
            //TODO fix
            if (mInduced) {
                mBox.calculateBox(mInducedVertices.begin(), mInducedVertices.end());
            } else {
                mBox.calculateBox(mVertices.begin(), mVertices.end());
            }
            mBoxUpToDate = true;
            std::cout << mBox;
        }

        return mBox.isMember(point);
    }

    /**
     *@brief Calculates the coordinates of the induced grid.
     */
    void PolyhedronOrt::induceGrid() {
        set<Vertex>::iterator it;

        for (unsigned d = 0; d < mDimension; d++) {
            mInducedGridPoints[d].push_back(0);
        }

        // Projection of all points to the axes.
        for (it = mVertices.begin(); it != mVertices.end(); it++) {
            for (unsigned d = 0; d < mDimension; d++) {
                mInducedGridPoints[d].push_back(it->getCoordinate(d));
            }
        }

        // Sort every dimension, erase duplicate entries.
        for (unsigned d = 0; d < mDimension; d++) {
            std::sort(mInducedGridPoints[d].begin(), mInducedGridPoints[d].end());
            vector<int>::iterator itr = std::unique(mInducedGridPoints[d].begin(), mInducedGridPoints[d].end());
            mInducedGridPoints[d].resize(itr - mInducedGridPoints[d].begin());
        }

        /*DEBUGoutput.
         * for (unsigned d = 0; d<mDimension; d++) {
           std::cout << "Dimension " << d << ":";
           for (unsigned i = 0; i<mInducedGridPoints[d].size(); i++) {
                   std::cout << mInducedGridPoints[d][i] << " ";
           }
           std::cout<<endl;
        }
         */

        for (it = mVertices.begin(); it != mVertices.end(); it++) {
            mInducedVertices.insert(calculateInduced(*it), it->getColor());
        }

        clear();
        mInduced = true;
    }

    /**
     * Translate a point into its coordinates on the induced grid.
     */
    Point PolyhedronOrt::calculateInduced(const Point& x) {
        vector<int> coordinates;
        coordinates.reserve(mDimension);
        vector<int>::iterator it;
        for (unsigned d = 0; d < mDimension; d++) {
            it = std::lower_bound(mInducedGridPoints[d].begin(), mInducedGridPoints[d].end(), x[d] + 1);
            coordinates.push_back((int) (it - 1 - mInducedGridPoints[d].begin()));
        }
        Point induced = Point(coordinates);
        LOG4CPLUS_DEBUG(mLogger, "Calculating induced coordinates:" << x << " -> " << induced);
        return induced;
    }

    /**
     * 
     * @param x The point to be induced
     * @param c The colour of the induced point
     * @return The induced vertex with colour c
     */
    Vertex PolyhedronOrt::calculateInduced(const Point& x, bool c) {
        return Vertex(calculateInduced(x), c);
    }

    /**
     * Moves the whole polyhedron.
     * @param p Point which describes the movement.
     * Clears the grid.
     */
    void PolyhedronOrt::move(const Point& p) {
        LOG4CPLUS_INFO(mLogger, "Moving " << p);
        // Create a temporary map.
        VertexContainer temp = VertexContainer(mDimension);
        VertexContainerIt tempIt = temp.begin();
        Vertex tmp;
        // Copy the moved points to the temporary map. Should go linear, because of fast insertion.
        for (vSetIt it = mVertices.begin(); it != mVertices.end(); it++) {
            tmp = Vertex(*it);
            tmp.move(p);
            temp.insert(tmp, tempIt);
            tempIt++;
        }
        mVertices = temp;
        mNeighbourhood.moveVertices(p);
        mBoundary.move(p);
        mOriginColour = calculateOriginColour();
        clear();

    }

    /**
     * 
     * @return The boundary as it is saved. This has nothing to do with the box.
     */
    Point PolyhedronOrt::getBoundary() const {
        return mBoundary;
    }

    /**
     * Resets the box and the grid.
     */
    void PolyhedronOrt::clear() {
        mBox.clear();
        mBoxUpToDate = false;
        mGrid.clear();
        mGridInitialized = false;
    }

    /**
     * Function to translate  into Neighborhood-Representation
     */
    void PolyhedronOrt::translateToNeighbourhoodRepresentation(bool clean) {
        LOG4CPLUS_INFO(mLogger, "Translating to Neighbourhood representation");
        vSetCIt it;

        switch (mRepresentation) {
            case VERTEX:
            case EXTREMEVERTEX:
                for (VertexContainerIt it = mVertices.begin(); it != mVertices.end(); ++it) {
                    vector<Point> neighbours = it->getAllNeighbours(true);
                    vector<Vertex> neighbourvert;
                    for (pVecIt nit = neighbours.begin(); nit != neighbours.end(); ++nit) {
                        neighbourvert.push_back(Vertex(*nit, isMember(*nit)));
                    }
                    mNeighbourhood.insertVertexAndNeighbours(*it, neighbourvert.begin(), neighbourvert.end());

                }
                if (clean)
                    mGrid.clear();

                break;
            case NEIGHBOUR:
                // nothing to do.
                break;

            default:
                // TODO throw error.
                break;
        }
        setRepresentation(NEIGHBOUR);
    }

    /**
     * 
     */
    void PolyhedronOrt::translateVertexToExtreme() {
        for (VertexContainerIt it = mVertices.begin(); it != mVertices.end(); ++it) {
            unsigned count = 0;
            pVec neighbours = it->getAllNeighbours();
            for (pVecIt nit = neighbours.begin(); nit != neighbours.end(); ++nit) {
                if (isMember(*nit)) count++;
            }
            if (it->getColor()) count++;
            if (count % 2 == 1) mExtremeVertices.insertAtBack(*it);
        }
    }

    /**
     * 
     */
    void PolyhedronOrt::translateNeighbourToExtreme() {
        for (VertexContainerIt it = mVertices.begin(); it != mVertices.end(); ++it) {
            unsigned count = 0;
            for (vSetIt nit = mNeighbourhood.getNeighbourhoodBegin(*it); nit != mNeighbourhood.getNeighbourhoodEnd(*it); ++nit) {
                if (nit->getColor()) count++;
            }
            if (it->getColor()) count++;
            if (count % 2 == 1) mExtremeVertices.insertAtBack(*it);
        }
    }

    /**
     * Method to transform the polyhedron-object to be in Extreme-Vertex Representation.
     * @param clean If true, then remove data of former representation.
     */
    void PolyhedronOrt::translateToExtremeVertexRepresentation(bool clean) {
        LOG4CPLUS_INFO(mLogger, "Translating into ExtremeVertex Representation");

        switch (mRepresentation) {
            case VERTEX:
                translateVertexToExtreme();
                break;
            case NEIGHBOUR:
                translateNeighbourToExtreme();
                break;
            case EXTREMEVERTEX:
                //nothing to be done
                return;
        }

        setRepresentation(EXTREMEVERTEX);
    }

    /**
     * Checks if the origin lies within the Polyhedron or not.
     * @return the color of the origin. (whether the origin is a member or not)
     */
    bool PolyhedronOrt::calculateOriginColour() {
        Point origin = Point(mDimension);

        std::pair<bool, bool> v = mVertices.isVertex(origin);

        if (!v.first) {
            return false;
        }

        if (!v.second) {
            LOG4CPLUS_WARN(mLogger, "Origin is white but a Vertex");
            mVertices.erase(origin);
            return false;
        }
        return true;
    }

    /**
     * @brief Used within membershipRecursiveVertex.
     *
     * @param point
     * @return the colour of the point
     */
    bool PolyhedronOrt::checkAPoint(const Point& point) {
        LOG4CPLUS_TRACE(mLogger, "Point checked: " << point);

        map<Point, bool>::iterator gridIt;
        bool pColour = false;
        gridIt = mGrid.find(point);

        if (gridIt == mGrid.end()) { // not found
            if (!isMemberBox(point)) {
                // neighbor is out of box, so its definitely white
                pColour = false;
            } else {
                // we have to calculate this one
                pColour = membershipRecursiveVertex(point);
            }
            // save it for later use
            mGrid.insert(pair<Point, bool> (point, pColour));
        } else {
            // we already calculated this one.
            pColour = gridIt->second;
            LOG4CPLUS_TRACE(mLogger, "We know this point!");
        }
        LOG4CPLUS_TRACE(mLogger, "value: " << pColour);
        return pColour;
    }

    // TODO use this in intersect..
    // TODO move this to grid.

    /**
     * Calculates on the grid whether a point should be a vertex
     * @param p A point on the grid.
     * @return Whether p should be a Vertex according to the grid.
     */
    bool PolyhedronOrt::checkVertexCondition(const Point& p) {
        // Output
        LOG4CPLUS_INFO(mLogger, "Point we check" << p);
        for (unsigned fixed = 0; fixed < mDimension; fixed++) {
            vector<Point> neighborsInFixed = p.getAllNeighborsForAFixedDimension(fixed);
            neighborsInFixed.push_back(p);
            bool allEqual = true;

            for (unsigned i = 0; i < neighborsInFixed.size(); i++) {
                Point neighbor = neighborsInFixed[i];
                Point neighborPredecessor = Point(neighbor).getPredecessorInDimension(fixed);
                bool neighborColor = false;
                bool neighborPredecessorColor = false;

                LOG4CPLUS_DEBUG(mLogger, "Neighbor" << neighbor << "NeighborPred" << neighborPredecessor);
                if (isMember(neighbor)) {
                    LOG4CPLUS_TRACE(mLogger, "NeighborC true");

                    neighborColor = true;
                }
                if (isMember(neighborPredecessor)) {
                    LOG4CPLUS_TRACE(mLogger, "NeighborPredC true");
                    neighborPredecessorColor = true;
                }
                if (neighborColor != neighborPredecessorColor) {
                    allEqual = false;
                    break;
                }
            }
            // Point is not a vertex
            if (allEqual) {
                LOG4CPLUS_DEBUG(mLogger, "Point is not a vertex");
                LOG4CPLUS_TRACE(mLogger, "For fixed " << fixed);
                return false;
            }
        }
        LOG4CPLUS_DEBUG(mLogger, "Point is a vertex");
        return true;
    }

    /**
     * Recursive function to check if a point is within the polyhedron.
     * For the membership
     *
     * @param point
     * @return true, if the point lies within the polyhedron.
     */
    bool PolyhedronOrt::membershipRecursiveVertex(const Point& point) {
        // The point we are to check.
        LOG4CPLUS_TRACE(mLogger, "Recursive Memberpoint check for: " << point);

        map<Point, bool>::iterator gridIt;
        bool neighborColour = false;
        bool neighborPredecessorColor;

        // Lookup if the point is already in the map.
        gridIt = mGrid.find(point);
        if (gridIt != mGrid.end()) {
            LOG4CPLUS_TRACE(mLogger, "Known:  " << gridIt->second);

            // Known point
            return gridIt->second;
        }

        // There exists a dimension
        for (unsigned fixed = 0; fixed < mDimension; fixed++) {
            bool holdsforallneighbors = true;
            LOG4CPLUS_TRACE(mLogger, "Fixed Dimension: " << fixed);
            // For all neighbors
            vector<Point> neighborsInFixed = point.getAllNeighborsForAFixedDimension(fixed);
            for (unsigned i = 0; i < neighborsInFixed.size(); i++) {
                Point neighbor = neighborsInFixed[i];
                // we now have the next neighbor we have to check.
                // Do we know the points' mColor already?
                neighborColour = checkAPoint(neighbor);
                //Calculate its predecessor.
                Point neighborPredecessor = Point(neighbor).getPredecessorInDimension(fixed);
                //And the color of this predecessor.
                neighborPredecessorColor = checkAPoint(neighborPredecessor);

                if (neighborPredecessorColor != neighborColour) {
                    // Since the condition has to hold for all neighbors for a fixed dimension,
                    // this fixed dimension wont bring a result.
                    LOG4CPLUS_TRACE(mLogger, "Dimension: " << fixed << " will have no result");
                    holdsforallneighbors = false;
                    break;
                }
            }

            if (holdsforallneighbors) {
                // The condition neighborPredecessorColor == neighborColor did hold for all of them.
                // Therefore we are able to calculate the mColor of the point.
                Point xPredecessor = Point(point);
                xPredecessor.DecrementInFixedDim(fixed);
                bool xPredecessorColor = checkAPoint(xPredecessor);

                LOG4CPLUS_TRACE(mLogger, point << " is colored " << xPredecessorColor);
                return xPredecessorColor;
            }
        }
        LOG4CPLUS_ERROR(mLogger, "Looped through all dimensions without outcome in Membership ");
        return false;
    }

    /**
     * Membership calculation based on the neighborhoodrepresentation.
     * @param pX
     * @return true, if pX is a member.
     */
    bool PolyhedronOrt::membershipNeighbour(const Point& pX) {
        // First of all, we can create a list of vertices which are of any interest.
        // Vertices are of interest, if every coordinate of them is within the interval [0, pX(d)].
        // This way, we can make sure that the working grid will not grow unnecessarily large.
        std::list<Vertex> verticesInBoundary = getSmallerVertices(pX);

        // If we use a dynamic heuristic, elimination order of the dimensions may change.
        // In that case, we need to sort the vertices according to that scheme.
        //TODO implement dynamic heuristics.
        if (DYNAMICHEURISTIC) {

        }
        // Otherwise, a static heuristic is used and the ordering reflects the order of eliminating already.

        std::list<Vertex>::iterator listIt;
        std::list<Vertex>::iterator lookAheadIt;
        vVec neighbourhood;
        vVec neighbourhoodD;

        // @todo investigate why the order is for(d) { for(v) }
        for (unsigned d = mDimension - 1; d > 0; d--) {
            LOG4CPLUS_DEBUG(mLogger, "Dimension is currently" << d);
            for (listIt = verticesInBoundary.begin(); listIt != verticesInBoundary.end(); listIt++) {
                // Look ahead for points nearer.
                LOG4CPLUS_TRACE(mLogger, "listIt: " << listIt->toString(true));
                lookAheadIt = listIt;
                while (lookAheadIt != verticesInBoundary.end() && listIt->CompareReducedDimension(*lookAheadIt, d)) {
                    lookAheadIt++;
                }
                lookAheadIt--;

                // Delete points between lookAhead and listIt.
                while (listIt != lookAheadIt && listIt != verticesInBoundary.end()) {
                    LOG4CPLUS_TRACE(mLogger, "delete " << listIt->toString(true));
                    listIt = verticesInBoundary.erase(listIt);
                }
                // Nearest point found.
                LOG4CPLUS_DEBUG(mLogger, "Nearest: " << listIt->toString(true));
                unsigned dValue = listIt->getCoordinate(d);
                // Check Vertex-of-a-Section-condition.
                // Therefore we need all neighbors with dim d fixed.
                neighbourhood.insert(neighbourhood.begin(), mNeighbourhood.getNeighbourhoodBegin(*listIt), mNeighbourhood.getNeighbourhoodEnd(*listIt));

                for (vVecIt neighbourIt = neighbourhood.begin(); neighbourIt != neighbourhood.end(); ++neighbourIt) {
                    if (neighbourIt->getDimension() == dValue) {
                        neighbourhoodD.insert(neighbourhoodD.end(), *neighbourIt);
                    }
                }

                // for all other dimensions:
                for (unsigned j = 0; j < d; j++) {
                    if (j == d) continue;
                    LOG4CPLUS_TRACE(mLogger, "j = " << j);
                    bool conditionHold = false;
                    for (vVecIt neighbourDIt = neighbourhoodD.begin(); neighbourDIt != neighbourhoodD.end(); neighbourDIt++) {
                        Vertex vert = *neighbourDIt;
                        Point ptPred = vert.getPredecessorInDimension(j);
                        //TODO is already sorted, so we could use a faster algorithm here.
                        Vertex vertPred = *std::find(neighbourhoodD.begin(), neighbourhoodD.end(), ptPred);

                        LOG4CPLUS_TRACE(mLogger, "Point in Neighborhood " << vert);

                        //select the points that are in the intersection with the neighborhood with fixed dim j.
                        bool skip = false;
                        for (unsigned i = mDimension - 1; i >= d; i--) {
                            if (vert[i] != listIt->getCoordinate(i)) {
                                LOG4CPLUS_TRACE(mLogger, "skip ");
                                // not in the neighborhood with fixed dim j.
                                skip = true;
                                break;
                            }
                        }
                        if (vert[j] != listIt->getCoordinate(j)) {
                            LOG4CPLUS_TRACE(mLogger, "skip ");
                            // not in the neighborhood with fixed dim j.
                            skip = true;
                        }
                        if (skip) continue;

                        LOG4CPLUS_TRACE(mLogger, "Pt colour " << vert.getColor());
                        LOG4CPLUS_TRACE(mLogger, "PtPred colour " << vertPred.getColor());

                        // And check for each of them if its color in the neighborhoodmap equals the color of its predecessor in the neighborhoodmap.
                        if (vert.getColor() != vertPred.getColor()) {
                            conditionHold = true;
                            break;
                        }
                    }
                    // Point is not a vertex on the section.
                    if (!conditionHold) {
                        LOG4CPLUS_DEBUG(mLogger, "Not a vertex on the section");
                        listIt = verticesInBoundary.erase(listIt);
                        listIt--;
                        break;
                    }
                }
                // If in every dimension there was a point that held the condition, the point is on the section. We do not remove it.
                // And continue with other points.
            }
        }

        //1-dimension left. Last vertex determines color. If there is no vertex-predecessor the color is white.
        if (verticesInBoundary.begin() != verticesInBoundary.end()) {
            LOG4CPLUS_DEBUG(mLogger, "Determining Vertex " << verticesInBoundary.back().toString());
            return verticesInBoundary.back().getColor();
        } else {
            LOG4CPLUS_INFO(mLogger, "No Vertices left. Result = 0");
            return false;
        }
    }

    /**
     * Calculates membership on extreme Vertexrepresentations
     * @param pX
     * @return The colour of the point
     */
    bool PolyhedronOrt::membershipExtremeVertex(const Point& pX) {
        // First of all, we can create a list of vertices which are of any interest.
        // Vertices are of interest, if every coordinate of them is within the interval [0, pX(d)].
        // This way, we can make sure that the working grid will not grow unnecessarily large.
        std::list<Vertex> verticesInBoundary = getSmallerVertices(pX, true);

        // If we use a dynamic heuristic, elimination order of the dimensions may change.
        // In that case, we need to sort the vertices according to that scheme.
        //TODO implement dynamic heuristics.
        if (DYNAMICHEURISTIC) {

        }
        // Otherwise, a static heuristic is used and the ordering reflects the order of eliminating already.

        std::list<Vertex>::iterator listIt;
        std::list<Vertex>::iterator lookAheadIt;
        for (unsigned d = mDimension - 1; d > 0; d--) {
            for (listIt = verticesInBoundary.begin(); listIt != verticesInBoundary.end(); listIt++) {
                // Look ahead for points nearer.
                LOG4CPLUS_TRACE(mLogger, "listIt: " << listIt->toString(true));
                lookAheadIt = listIt;
                unsigned count = 0;
                // count the vertices 
                while (lookAheadIt != verticesInBoundary.end() && listIt->CompareReducedDimension(*lookAheadIt, d)) {
                    lookAheadIt++;
                    count++;
                }
                lookAheadIt--;

                // clean up this dimension.
                while (listIt != lookAheadIt && listIt != verticesInBoundary.end()) {
                    LOG4CPLUS_TRACE(mLogger, "listIt: " << listIt->toString(true));
                    listIt = verticesInBoundary.erase(listIt);
                }

                // It is not a vertex.
                if (count % 2 == 0) {
                    listIt = verticesInBoundary.erase(listIt);
                    listIt--;
                }
            }
        }

        //1-dimension left. Last vertex determines color. If there is no vertex-predecessor the color is white.
        if (verticesInBoundary.begin() != verticesInBoundary.end()) {
            return verticesInBoundary.back().getColor();
        } else {
            return false;
        }
    }

    /**
     *
     * @return the "best" iterator to the start of the vertex-list.
     */
    VertexContainerIt PolyhedronOrt::getVerticesIteratorBegin(bool extreme) {
        if (extreme) {
            if (mRepresentation == EXTREMEVERTEX) {
                return mExtremeVertices.begin();
            } else {
                // TODO handle this.
            }
        }
        if (mInduced) {
            return mInducedVertices.begin();
        } else {
            return mVertices.begin();
        }
    }

    /**
     *
     * @return the "best" iterator to the end of the vertex-list.
     */
    VertexContainerIt PolyhedronOrt::getVerticesIteratorEnd(bool extreme) {
        if (extreme) {
            if (mRepresentation == EXTREMEVERTEX) {
                return mExtremeVertices.end();
            } else {
                // TODO handle this.
            }
        }
        if (mInduced) {
            return mInducedVertices.end();
        } else {
            return mVertices.end();
        }
    }

     /**
     * calculates all the points that describe the box between origin and boundary.
     * @param boundary
     * @return 
     */
    vector<Vertex> PolyhedronOrt::calculateBoundaryBox(const Point& boundary) {
        vector<Vertex> boundaryBox;
        boundaryBox.push_back(Vertex(boundary, false));

        return calculateBoundaryBoxRec(mDimension - 1, boundaryBox);
    }

    /**
     * 
     * @param dim
     * @param boundaryBox
     * @return 
     */
    vector<Vertex> PolyhedronOrt::calculateBoundaryBoxRec(unsigned dim, vector<Vertex> & boundaryBox) {
        LOG4CPLUS_DEBUG(mLogger, "Dimension " << dim);
        unsigned size = boundaryBox.size();
        for (unsigned i = 0; i < size; i++) {
            Vertex boxPoint = Vertex(boundaryBox[i]);
            boxPoint[dim] = 0;
            boxPoint.setColor(false);
            boundaryBox.push_back(boxPoint);
        }

        if (dim == 0) return boundaryBox;
        return calculateBoundaryBoxRec(dim - 1, boundaryBox);
    }

    /**
     * @return: returns a vector with the vertices of the polyhedron.
     */
    vector<Vertex> PolyhedronOrt::getVertices() {
        vector<Vertex> vList;
        vList.reserve(mVertices.size());
        vList.insert(vList.begin(), mVertices.begin(), mVertices.end());
        return vList;
    }

    /**
     * @param p
     * @param extreme
     */
    list<Vertex> PolyhedronOrt::getSmallerVertices(const Point& p, bool extreme) {
        if (extreme) mExtremeVertices.getSmallerVertices(p);
        return mVertices.getSmallerVertices(p);
    }

    /**
     * Returns the set representation.
     */
    PolyhedronOrtRepresentation PolyhedronOrt::getRepresentation() {
        return mRepresentation;
    }

    /**
     * Sets the internal flag which representation is active.Does not actually change the representation.
     * Use Translate if you want to change the representation.
     */
    void PolyhedronOrt::setRepresentation(PolyhedronOrtRepresentation repr) {
        mRepresentation = repr;
    }

    //TODO move

    /**
     * Method to copy from a VertexContainer to a map.
     * @param begin
     * @param end
     * @param map
     */
    void PolyhedronOrt::insertVerticesInMap(VertexContainerIt begin, VertexContainerIt end, std::map<Point, bool>& map) {
        VertexContainerIt it = begin;
        while (it != end) {
            map.insert(std::pair<Point, bool>(*it, (Vertex*) it->getColor()));
            ++it;
        }
    }

    /**
     * Outputs if the polyhedron is induced and the vertices.
     * @param ostr
     * @param pol
     * @return 
     */
    std::ostream& operator<<(std::ostream& ostr, const PolyhedronOrt& pol) {
        ostr << "Induced" << pol.mInduced << std::endl;
        ostr << "Vertices: \n";
        return ostr << pol.mVertices;
    }

} // end namespace
