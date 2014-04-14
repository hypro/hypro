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

    template<typename Number>
    class NeighbourhoodContainer {
    public:
        NeighbourhoodContainer();
       
        void insertVertexAndNeighbours(const Point<Number>& p, vVecIt<Number> neighbourBegin, vVecIt<Number> neighbourEnd) {
            vSet<Number> neighbourhood = vSet<Number>(neighbourBegin, neighbourEnd);
            neighbourhoods.insert(std::pair<Point<Number>, vSet<Number> >(p, neighbourhood));
        }

        void moveVertices(const Point<Number>& p);
        
        inline void clear() {
            neighbourhoods.clear();
        }
        
        vSetIt<Number> getNeighbourhoodBegin(const Point<Number>& p);
        vSetIt<Number> getNeighbourhoodEnd(const Point<Number>& p);
        
    private:
        std::map<Point<Number>, vSet<Number> > neighbourhoods;
        //log4cplus::Logger mLogger;
        
    };
    
}//namespace

#include "NeighbourhoodContainer.tpp"

