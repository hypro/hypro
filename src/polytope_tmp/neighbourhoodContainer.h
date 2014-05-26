/** 
 * @file   vertexContainer.h
 * Created on June 22, 2011
 * Last modified June 29, 2011
 * 
 * @author Sebastian Junges
 */
#ifndef NEIGHBORHOODCONTAINER_H
#define	NEIGHBORHOODCONTAINER_H

#include "vertex.h"


// Log4cplus
#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>


using std::map;
using std::set;


namespace reachLin {
    
    class NeighbourhoodContainer {
    public:
        NeighbourhoodContainer();
       
        void insertVertexAndNeighbours(const Point& p, vVecIt neighbourBegin, vVecIt neighbourEnd) {
            set<Vertex> neighbourhood = set<Vertex>(neighbourBegin, neighbourEnd);
            neighbourhoods.insert(std::pair<Point, set<Vertex> >(p,neighbourhood));
        }
        void moveVertices(const Point& p);
        
        inline void clear() {
            neighbourhoods.clear();
        }
        
        
        vSetIt getNeighbourhoodBegin(const Point& p);
        vSetIt getNeighbourhoodEnd(const Point& p);
        
        
        
    private:
        map<Point,set<Vertex> > neighbourhoods;
        log4cplus::Logger mLogger;
        
    };

}

#endif	/* NEIGHBORHOODCONTAINER_H */

