/** 
 * @file    OrthogonalPolyhedron.tpp
 * @author  Sebastian Junges
 * @author  Benedikt Seidl
 *
 * @since   2014-03-17
 * @version 2014-03-17
 */

namespace hypro
{
    template<typename Number>
    OrthogonalPolyhedron<Number>::OrthogonalPolyhedron() {}
    
    template<typename Number>
    OrthogonalPolyhedron<Number>::OrthogonalPolyhedron(Vertex<Number>* vertices, unsigned nrVertices, unsigned dim/*, Point<Number> boundary*/) :
        mRepresentation(VERTEX),
        mNrVertices(nrVertices),
        mGridInitialized(false),
        //mBoxUpToDate(false),
        //mBox(Box<Number>(dim)),
        //mBoundary(boundary),
        mVertices(VertexContainer<Number>(dim))
    {
        preInit();
        for (unsigned i = 0; i < nrVertices; i++)
            mVertices.insert(vertices[i]);
        postInit();
    }
    
    template<typename Number>
    OrthogonalPolyhedron<Number>::OrthogonalPolyhedron(vVec<Number> vertexList, unsigned dim) :
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
    OrthogonalPolyhedron<Number>::OrthogonalPolyhedron(vVec<Number> vertexList, unsigned dim, vVec<Number> extremeVertexList) :
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
    OrthogonalPolyhedron<Number>::OrthogonalPolyhedron(vVec<Number> vertexList, unsigned dim, NeighbourhoodContainer<Number> neighbourhoods) :
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
}
