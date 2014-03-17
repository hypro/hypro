/** 
 * @file    OrthogonalPolyhedron.tpp
 * @author  Sebastian Junges
 * @author  Benedikt Seidl
 *
 * @since   2014-03-17
 * @version 2014-03-17
 */

#include "OrthogonalPolyhedron.h"


namespace hypro
{

    /***************************************************************************
     * Constructors
     ***************************************************************************/
    template<typename Number>
    OrthogonalPolyhedron<Number>::OrthogonalPolyhedron() {}
    
    template<typename Number>
    OrthogonalPolyhedron<Number>::OrthogonalPolyhedron(const Vertex<Number>* vertices, unsigned nrVertices, unsigned dim, Point<Number> boundary) :
        mRepresentation(VERTEX),
        mNrVertices(nrVertices),
        mGridInitialized(false),
        mBoxUpToDate(false),
        mBox(Box<Number>(dim)),
        mBoundary(boundary),
        mVertices(VertexContainer<Number>(dim))
    {
        preInit();
        for (unsigned i = 0; i < nrVertices; i++)
            mVertices.insert(vertices[i]);
        postInit();
    }
    
    template<typename Number>
    OrthogonalPolyhedron<Number>::OrthogonalPolyhedron(const vVec<Number>& vertexList, unsigned dim) :
        mRepresentation(VERTEX),
        mNrVertices(vertexList.size()),
        //mBox(Box(dim)),
        mVertices(VertexContainer<Number>(dim))
    {
        preInit();
        mVertices.insert(vertexList.begin(), vertexList.end());
        //mBox.calculateBox(mVertices.begin(), mVertices.end());
        //mBoxUpToDate = true;
        //mBoundary = mBox.getMax();
        postInit();
    }

    /**
     * A constructor where additionally the list of extreme Vertices can be passed. Should only be used if the list of EV
     * is complete.
     */
    template<typename Number>
    OrthogonalPolyhedron<Number>::OrthogonalPolyhedron(const vVec<Number>& vertexList, unsigned dim, const vVec<Number>& extremeVertexList) :
        mRepresentation(EXTREMEVERTEX),
        mNrVertices(vertexList.size()),
        //mBox(Box(dim)),
        mVertices(VertexContainer<Number>(dim))
    {
        preInit();
        mVertices.insert(vertexList.begin(), vertexList.end());
        mExtremeVertices.insert(extremeVertexList.begin(), extremeVertexList.end());

        if (mNrVertices != mVertices.size()) {
            assert( false );
            //LOG4CPLUS_WARN(mLogger, "Inputlenght is not equal to number of vertices.");
        }

        //TODO refactor
        //mBox.calculateBox(mVertices.begin(), mVertices.end());
        //mBoxUpToDate = true;
        //mBoundary = mBox.getMax();


        //LOG4CPLUS_INFO(mLogger, "Number of vertices is " << mNrVertices);
        postInit();
    }
    
    template<typename Number>
    OrthogonalPolyhedron<Number>::OrthogonalPolyhedron(const vVec<Number>& vertexList, unsigned dim, const NeighbourhoodContainer<Number>& neighbourhoods) :
        mRepresentation(NEIGHBOUR),
        mNrVertices(vertexList.size()),
        //mBox(Box(dim)),
        mVertices(VertexContainer<Number>(dim))
    {

        preInit();
        mVertices.insert(vertexList.begin(), vertexList.end());
        mNeighbourhood = neighbourhoods;
        
        if (mNrVertices != mVertices.size()) {
            assert( false );
            //LOG4CPLUS_WARN(mLogger, "Inputlenght is not equal to number of vertices.");
        }

        //TODO refactor
        //mBox.calculateBox(mVertices.begin(), mVertices.end());
        //mBoxUpToDate = true;
        //mBoundary = mBox.getMax();

        //LOG4CPLUS_INFO(mLogger, "Number of vertices is " << mNrVertices);
        postInit();
    }
    
    template<typename Number>
    void OrthogonalPolyhedron<Number>::preInit() {

        mInduced = false;
        mGridInitialized = false;
        //mBoxUpToDate = false;
        //mLogger = Logger::getInstance("reachLin.PolyhedronOrt");

        //LOG4CPLUS_INFO(mLogger, "New polyhedron created");
        reserveInducedGrid();
    }

    template<typename Number>
    void OrthogonalPolyhedron<Number>::postInit() {
        mNrVertices = mVertices.size();
        //LOG4CPLUS_INFO(mLogger, "Number of vertices is " << mNrVertices);
        mOriginColour = calculateOriginColour();
        //LOG4CPLUS_DEBUG(mLogger, "Origin is " << mOriginColour);

    }

    template<typename Number>
    void OrthogonalPolyhedron<Number>::reserveInducedGrid() {
        mInducedGridPoints.reserve(getDimension());
        std::vector<Number> v;
        for (unsigned d = 0; d < getDimension(); d++) {
            mInducedGridPoints.push_back(v);
        }
    }

    /***************************************************************************
     * Public methods
     ***************************************************************************/
    
    /**
     * @brief emptiness check.
     * @return true if number of vertices equals 0.
     */
    template<typename Number>
    bool OrthogonalPolyhedron<Number>::isEmpty() {
        return mNrVertices == 0;
    }

    /**
     * @brief universality check
     * For universality, only the cornerpoints are vertices, and the outermost corner has to be the boundary.
     * @return, true, if every point within boundary is a vertex. 
     */
    template<typename Number>
    bool OrthogonalPolyhedron<Number>::isUniversal() {
        if (mNrVertices != pow(getDimension(), 2)) return false;
        //return mVertices.isVertex(mBoundary).first; // @todo: mBoundary!
        /* only to make it compilable: */ return true; // REMOVE!
    }
    
    /**
     * @brief Test if a point lies within the polyhedron
     * @param pointX Pointer to the point.
     * @param useOrig Deprecated
     * @return: true if inside, false if not.
     */
    template<typename Number>
    bool OrthogonalPolyhedron<Number>::isMember(Point<Number>& pointX, bool useOrig) {
        bool result;
        //LOG4CPLUS_DEBUG(mLogger, "Membershiptest for " << pointX);
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
                    //LOG4CPLUS_TRACE(mLogger, "Out of Box");
                    return false;
                }
                if (mInduced) {
                    //LOG4CPLUS_DEBUG(mLogger, "Calculating on induced grid");

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
                //LOG4CPLUS_DEBUG(mLogger, result);
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
        //LOG4CPLUS_ERROR(mLogger, "No Representation set.");
        return false;
    }

    /***************************************************************************
     * Private methods
     ***************************************************************************/

    /**
     * Checks if the origin lies within the Polyhedron or not.
     * @return the color of the origin. (whether the origin is a member or not)
     */
    template<typename Number>
    bool OrthogonalPolyhedron<Number>::calculateOriginColour() {
        Point<Number> origin = Point<Number>();

        std::pair<bool, bool> v = mVertices.isVertex(origin);

        if (!v.first) {
            return false;
        }

        if (!v.second) {
            //LOG4CPLUS_WARN(mLogger, "Origin is white but a Vertex");
            mVertices.erase(origin);
            return false;
        }
        return true;
    }
}
