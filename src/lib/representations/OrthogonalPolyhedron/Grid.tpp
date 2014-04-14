/** 
 * @file    Grid.tpp
 * @author  Benedikt Seidl
 *
 * @since   2014-04-14
 * @version 2014-04-14
 */

namespace hypro
{
    template<typename Number>
    void Grid<Number>::insertVerticesInMap(const VertexContainer<Number>& vertexContainer)
    {
        for (auto it = vertexContainer.begin(); it != vertexContainer.end(); ++it) {
            Vertex<Number> vertex = *it;
            mGrid.insert(std::pair<Point<Number>, bool>(vertex, vertex.color()));
        }
    }
    
    template<typename Number>
    bool Grid<Number>::contains(const Point<Number>& point) const
    {        
        // The point we are to check.
        //LOG4CPLUS_TRACE(mLogger, "Recursive Memberpoint check for: " << point);

        bool neighbourColour = false;
        bool neighbourPredecessorColor;

        // Lookup if the point is already in the map.
        auto gridIt = mGrid.find(point);
        if (gridIt != mGrid.end()) {
            //LOG4CPLUS_TRACE(mLogger, "Known:  " << gridIt->second);

            // Known point
            return gridIt->second;
        }

        // There exists a dimension
        for (auto coordinateIt : point.coordinates()) {
            auto fixed = coordinateIt.first;
            
            bool holdsforallneighbours = true;
            //LOG4CPLUS_TRACE(mLogger, "Fixed Dimension: " << fixed);
            // For all neighbours
            auto neighboursInFixed = point.getAllNeighborsForAFixedDimension(fixed);
            for (unsigned i = 0; i < neighboursInFixed.size(); i++) {
                Point<Number> neighbour = neighboursInFixed[i];
                // we now have the next neighbour we have to check.
                // Do we know the points' mColor already?
                neighbourColour = checkAPoint(neighbour);
                //Calculate its predecessor.
                Point<Number> neighbourPredecessor = Point<Number>(neighbour).getPredecessorInDimension(fixed);
                //And the color of this predecessor.
                neighbourPredecessorColor = checkAPoint(neighbourPredecessor);

                if (neighbourPredecessorColor != neighbourColour) {
                    // Since the condition has to hold for all neighbours for a fixed dimension,
                    // this fixed dimension wont bring a result.
                    //LOG4CPLUS_TRACE(mLogger, "Dimension: " << fixed << " will have no result");
                    holdsforallneighbours = false;
                    break;
                }
            }

            if (holdsforallneighbours) {
                // The condition neighbourPredecessorColor == neighbourColor did hold for all of them.
                // Therefore we are able to calculate the mColor of the point.
                Point<Number> xPredecessor = Point<Number>(point);
                xPredecessor.decrementInFixedDim(fixed);
                bool xPredecessorColor = checkAPoint(xPredecessor);

                //LOG4CPLUS_TRACE(mLogger, point << " is colored " << xPredecessorColor);
                return xPredecessorColor;
            }
        }
        //LOG4CPLUS_ERROR(mLogger, "Looped through all dimensions without outcome in Membership ");
        return false;
    }
    
    template<typename Number>
    bool Grid<Number>::checkAPoint(const Point<Number>& point) const
    {
        //LOG4CPLUS_TRACE(mLogger, "Point checked: " << point);

        bool pColour = false;
        auto gridIt = mGrid.find(point);

        if (gridIt == mGrid.end()) { // not found
            // @todo this optimization does not work now -.-
            /*if (!isMemberBox(point)) {
                // neighbor is out of box, so its definitely white
                pColour = false;
            } else*/ {
                // we have to calculate this one
                pColour = contains(point);
            }
            // save it for later use
            mGrid.insert(std::pair<Point<Number>, bool> (point, pColour));
        } else {
            // we already calculated this one.
            pColour = gridIt->second;
            //LOG4CPLUS_TRACE(mLogger, "We know this point!");
        }
        //LOG4CPLUS_TRACE(mLogger, "value: " << pColour);
        return pColour;
   }
        
}