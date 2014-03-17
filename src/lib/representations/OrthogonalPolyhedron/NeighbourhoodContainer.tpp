/** 
 * @file    NeighbourhoodContainer.tpp
 * @author  Sebastian Junges
 * @author  Benedikt Seidl
 *
 * @since   2014-03-17
 * @version 2014-03-17
 */

namespace hypro
{
    
    template<typename Number>
    NeighbourhoodContainer<Number>::NeighbourhoodContainer() {
        //mLogger = log4cplus::Logger::getInstance("reachLin.NeighbourhoodContainer");
    }
    
    template<typename Number>
    void NeighbourhoodContainer<Number>::moveVertices(const Point<Number>& p) {
        typename std::map<Point<Number>, vSet<Number> > tmp;
        vSet<Number> tmpSet;
        // TODO add suggestion that the point has to be added at the end.
        for(typename std::map<Point<Number>, vSet<Number> >::iterator it = neighbourhoods.begin(); it != neighbourhoods.end(); ++it) {
            tmpSet.clear();
            for(vSetIt<Number> vit = it->second.begin(); vit != it->second.end(); ++vit) {
                Vertex<Number> v = Vertex<Number>(*vit);
                v.move(p);
                tmpSet.insert(v);
            } 
            Point<Number> pt = Point<Number>(it->first);
            pt.move(p);
            tmp.insert(std::pair<Point<Number>, vSet<Number> >(p, tmpSet));
            
        }
        neighbourhoods = tmp; 
    }
    
    template<typename Number>
    vSetIt<Number> NeighbourhoodContainer<Number>::getNeighbourhoodBegin(const Point<Number>& p) {
        typename std::map<Point<Number>, vSet<Number> >::iterator it = neighbourhoods.find(p);
        /*if (it == neighbourhoods.end()) {
            LOG4CPLUS_FATAL(mLogger, "Point<Number> has no neighbourhood");
        }*/
        return it->second.begin();
    }
    
    template<typename Number>
    vSetIt<Number> NeighbourhoodContainer<Number>::getNeighbourhoodEnd(const Point<Number>& p) {
        typename std::map<Point<Number>, vSet<Number> >::iterator it = neighbourhoods.find(p);
        /*if (it == neighbourhoods.end()) {
            LOG4CPLUS_FATAL(mLogger, "Point<Number> has no neighbourhood");
        }*/
        return it->second.end();
    }
    
}//namespace
