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
    OrthogonalPolyhedron<Number>::OrthogonalPolyhedron(Vertex<Number>* vertices, unsigned nrVertices, unsigned dim, Point<Number> boundary) :
        mRepresentation(VERTEX),
        mNrVertices(nrVertices),
        mGridInitialized(false),
        mBoxUpToDate(false),
        mBoundary(boundary),
        mVertices(VertexContainer<Number>(dim)),
        mBox(Box<Number>(dim))
    {
        preInit();
        for (unsigned i = 0; i < nrVertices; i++)
            mVertices.insert(vertices[i]);
        postInit();
    }
}
