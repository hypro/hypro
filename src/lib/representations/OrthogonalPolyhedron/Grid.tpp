/** 
 * @file    Grid.tpp
 * @author  Benedikt Seidl
 *
 * @since   2014-04-14
 * @version 2014-04-14
 */

#include "Grid.h"


namespace hypro
{
    template<typename Number>
    void Grid<Number>::reserveInducedGrid()
    {
        std::vector<Number> v;
        for (auto it : variables()) {
            mInducedGridPoints.insert(std::pair<carl::Variable, std::vector<Number> >(it, v));
        }
    }
    
    template<typename Number>
    void Grid<Number>::insertVerticesInMap(const VertexContainer<Number>& vertexContainer)
    {
        for (auto it = vertexContainer.begin(); it != vertexContainer.end(); ++it) {
            Vertex<Number> vertex = *it;
            this->insert(vertex, vertex.color());
        }
    }
    
    template<typename Number>
    bool Grid<Number>::contains(const Point<Number>& point)
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
                neighbourColour = this->colourAt(neighbour);
                //Calculate its predecessor.
                Point<Number> neighbourPredecessor = Point<Number>(neighbour).getPredecessorInDimension(fixed);
                //And the color of this predecessor.
                neighbourPredecessorColor = this->colourAt(neighbourPredecessor);

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
                bool xPredecessorColor = this->colourAt(xPredecessor);

                //LOG4CPLUS_TRACE(mLogger, point << " is colored " << xPredecessorColor);
                return xPredecessorColor;
            }
        }
        //LOG4CPLUS_ERROR(mLogger, "Looped through all dimensions without outcome in Membership ");
        return false;
    }
    
    template<typename Number>
    bool Grid<Number>::colourAt(const Point<Number>& point)
    {
        //LOG4CPLUS_TRACE(mLogger, "Point checked: " << point);

        bool pColour = false;
        auto gridIt = mGrid.find(point);

        if (gridIt == mGrid.end()) { // not found
            if (!mBoundingBox.isEmpty() && !this->mBoundingBox.contains(point)) {
                // neighbor is out of box, so its definitely white
                pColour = false;
            } else {
                // we have to calculate this one
                pColour = contains(point);
            }
            // save it for later use
            this->insert(point, pColour);
        } else {
            // we already calculated this one.
            pColour = gridIt->second;
            //LOG4CPLUS_TRACE(mLogger, "We know this point!");
        }
        //LOG4CPLUS_TRACE(mLogger, "value: " << pColour);
        return pColour;
   }
    
    template<typename Number>
    void Grid<Number>::induceGrid(const vSet<Number>& vertices)
    {
        for (auto it : mInducedGridPoints) {
            it.second.push_back(Number(0));
        }

        // Projection of all points to the axes.
        for (auto vertex : vertices) {
            assert( vertex.hasDimensions(variables()));
            for (auto it : mInducedGridPoints) {
                it.second.push_back(vertex.coordinate(it.first));
            }
        }

        // Sort every dimension, erase duplicate entries.
        for (auto it : mInducedGridPoints) {
            std::sort(it.second.begin(), it.second.end());
            auto itr = std::unique(it.second.begin(), it.second.end());
            it.second.resize(itr - it.second.begin());
        }

        /*DEBUGoutput.
         * for (unsigned d = 0; d<mDimension; d++) {
           std::cout << "Dimension " << d << ":";
           for (unsigned i = 0; i<mInducedGridPoints[d].size(); i++) {
                   std::cout << mInducedGridPoints[d][i] << " ";
           }
           std::cout<<endl;
        }
         */

        /*
        for (it = mVertices.begin(); it != mVertices.end(); it++) {
            mInducedVertices.insert(calculateInduced(*it), it->getColor());
        }
        */

        clear();
        mInduced = true;
    }
    
    template<typename Number>
    Point<Number> Grid<Number>::calculateInduced(const Point<Number>& x) const
    {
        typename Point<Number>::vector_t coordinates;
        //typename std::vector<Number>::iterator it;
        for (auto & inducedGridPointsIt : mInducedGridPoints) {
            auto it = std::lower_bound(inducedGridPointsIt.second.begin(), inducedGridPointsIt.second.end(), x.coordinate(inducedGridPointsIt.first) + Number(1));
            // @todo typecast???
            coordinates.insert(std::pair<carl::Variable, Number>(inducedGridPointsIt.first,
                    Number(inducedGridPointsIt.second.at(it - 1 - inducedGridPointsIt.second.begin()))));
        }
        Point<Number> induced = Point<Number>(coordinates);
        //LOG4CPLUS_DEBUG(mLogger, "Calculating induced coordinates:" << x << " -> " << induced);
        return induced;
    }
        
}