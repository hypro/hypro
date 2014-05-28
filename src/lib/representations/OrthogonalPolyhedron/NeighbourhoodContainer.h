/* 
 * @file    NeighbourhoodContainer.h
 * @author  Sebastian Junges
 * @author  Benedikt Seidl
 *
 * @since   2014-03-17
 * @version 2014-03-17
 */

#pragma once

#include "../../datastructures/Point.h"
#include "../../datastructures/Vertex.h"
#include <map>
#include <utility>

// Log4cplus
//#include <log4cplus/logger.h>
//#include <log4cplus/configurator.h>

namespace hypro
{
    /**
     * A neighbourhood container which maps points
     * to their set of neighbour vertices.
     */
    template<typename Number>
    class NeighbourhoodContainer {
        
    private:
        std::map<Point<Number>, vSet<Number> > neighbourhoods;
        
    public:
        NeighbourhoodContainer() {}
       
        void insertVertexAndNeighbours(const Point<Number>& p, vSetIt<Number> neighbourBegin, vSetIt<Number> neighbourEnd) {
            vSet<Number> neighbourhood(neighbourBegin, neighbourEnd);
            neighbourhoods.insert(std::make_pair(p, neighbourhood));
        }
        
        void insertVertexAndNeighbours(const Point<Number>& p, vSet<Number>& neighbourhood)
        {
            neighbourhoods.insert(std::make_pair(p, neighbourhood));
        }
        
        void clear()
        {
            neighbourhoods.clear();
        }
        
        bool empty()
        {
            return neighbourhoods.empty();
        }
        
        vSetIt<Number> getNeighbourhoodBegin(const Point<Number>& p)
        {
            return neighbourhoods.find(p)->second.begin();
        }
        
        vSetIt<Number> getNeighbourhoodEnd(const Point<Number>& p)
        {
            return neighbourhoods.find(p)->second.end();
        }
        
        vSet<Number> getNeighbourhood(const Point<Number>& p)
        {
            return neighbourhoods.find(p)->second;
        }
        
        bool hasNeighbourhood(const Point<Number>& p)
        {
            return neighbourhoods.find(p) != neighbourhoods.end();
        }

        void moveVertices(const Point<Number>& p);
        
    };
    
}//namespace

#include "NeighbourhoodContainer.tpp"

