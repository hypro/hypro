/** 
 * @file   vertexContainer.cpp
 * Created on June 8, 2011
 * Last modified June 23, 2011
 * 
 * @author Sebastian Junges
 */

#include "vertexContainer.h"
#include "defines.h"
#include <boost/foreach.hpp>

using std::list;

namespace reachLin {
VertexContainer::VertexContainer(unsigned dimension) : mDimension(dimension) {
   
}

VertexContainer::VertexContainer(const VertexContainer& orig) : mDimension(orig.mDimension){
    vertices = orig.vertices;
}

VertexContainer::~VertexContainer() {
}

/**
 * @param p 
 * @return A list with all vertices v where the condition "v leq p"  holds.
 */
list<Vertex> VertexContainer::getSmallerVertices(const Point& p)
{
    list<Vertex> verticesInBoundary;
    foreach(Vertex v, vertices ) {
        if(v.isInBoundary(p)) verticesInBoundary.push_back(v);
    }
    return verticesInBoundary;
}

}
