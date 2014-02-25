/** 
 * @file   vertexContainer.cpp
 * Created on June 22, 2011
 * Last modified June 29, 2011
 * 
 * @author Sebastian Junges
 */
#include "neighbourhoodContainer.h"
using namespace log4cplus;

namespace reachLin {
    NeighbourhoodContainer::NeighbourhoodContainer() {
        mLogger = Logger::getInstance("reachLin.NeighbourhoodContainer");
    }
    
    /**
     * 
     * @param p
     */
    void NeighbourhoodContainer::moveVertices(const Point& p) {
        map<Point, set<Vertex> > tmp;
        set<Vertex> tmpSet;
        // TODO add suggestion that the point has to be added at the end.
        for(map<Point, set<Vertex> >::iterator it = neighbourhoods.begin(); it != neighbourhoods.end(); ++it) {
            tmpSet.clear();
            for(vSetIt vit = it->second.begin(); vit != it->second.end(); ++vit) {
                Vertex v = Vertex(*vit);
                v.move(p);
                tmpSet.insert(v);
            } 
            Point pt = Point(it->first);
            tmp.insert(std::pair<Point, set<Vertex> >(pt.move(p),tmpSet));
            
        }
        neighbourhoods = tmp; 
    }
    
    /**
     * 
     * @param p
     * @return 
     */
    vSetIt NeighbourhoodContainer::getNeighbourhoodBegin(const Point& p) {
        map<Point, set<Vertex> >::iterator it = neighbourhoods.find(p);
        if (it == neighbourhoods.end()) {
            LOG4CPLUS_FATAL(mLogger, "Point has no neighbourhood");
        }
        return it->second.begin();
    }
    
    /**
     * 
     * @param p
     * @return 
     */
    vSetIt NeighbourhoodContainer::getNeighbourhoodEnd(const Point& p) {
        map<Point, set<Vertex> >::iterator it = neighbourhoods.find(p);
        if (it == neighbourhoods.end()) {
            LOG4CPLUS_FATAL(mLogger, "Point has no neighbourhood");
        }
        return it->second.end();
    }
}