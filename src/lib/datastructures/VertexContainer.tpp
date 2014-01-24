/**
 * The implementation of the VertexContainer.
 * @file   vertexContainer.cpp
 *
 * @author Sebastian Junges
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since	2011-06-08
 * @version 2014-01-17
 */

#include "VertexContainer.h"

using std::list;

namespace hypro {
	template<typename Number>
	VertexContainer<Number>::VertexContainer(unsigned dimension) : mDimension(dimension)
	{}
	
	template<typename Number>
	VertexContainer<Number>::VertexContainer(const VertexContainer<Number>& orig) : mDimension(orig.mDimension)
	{
		vertices = orig.vertices;
	}
	
	/**
	 * @param p
	 * @return A list with all vertices v where the condition "v leq p"  holds.
	 */
	template<typename Number>
	list<Vertex<Number>> VertexContainer<Number>::getSmallerVertices(const Point<Number>& p)
	{
		list<Vertex<Number>> verticesInBoundary;
		for(auto vertexIt = vertices.begin(); vertexIt != vertices.end(); ++vertexIt)
		{
			if((*vertexIt).isInBoundary(p)) verticesInBoundary.push_back(*vertexIt);
		}
		return verticesInBoundary;
	}
	
}
