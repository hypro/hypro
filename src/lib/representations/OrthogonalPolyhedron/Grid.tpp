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
    void Grid<Number>::reserveInducedGrid()
    {
        std::vector<carl::FLOAT_T<Number> > v;
        for (auto it : variables()) {
            mInducedGridPoints.insert(std::make_pair(it, v));
        }
    }
    
    template<typename Number>
    void Grid<Number>::insertVerticesInMap(const vSet<Number>& vertices)
    {
        for (auto it : vertices) {
            this->insert(it, it.color());
        }
    }
    
    template<typename Number>
    void Grid<Number>::induceGrid(const vSet<Number>& vertices)
    {
        for (auto it : mInducedGridPoints) {
            // insert origin as vertex
            it.second.push_back(Number(0));
            
            // Projection of all points to the axes.
            for (auto vertex : vertices) {
                assert( vertex.hasDimensions(variables()));
                it.second.push_back(vertex.coordinate(it.first));
            }
            
            // Sort every dimension, erase duplicate entries.
            std::sort(it.second.begin(), it.second.end());
            auto itr = std::unique(it.second.begin(), it.second.end());
            it.second.resize(itr - it.second.begin());
            mInducedGridPoints[it.first] = it.second;
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
        insertVerticesInMap(vertices);
        mInduced = true;
    }
    
    template<typename Number>
    Point<Number> Grid<Number>::calculateInduced(const Point<Number>& x) const
    {
        typename Point<Number>::coordinateMap coordinates;
        
        // if not induced, calculate the integer part of each coordinate
        if (!mInduced) {
            for (auto coordinateIt : x.coordinates()) {
                coordinateIt.second.floor(coordinates[coordinateIt.first]);
            }
        } else {
            //typename std::vector<Number>::iterator it;
            for (auto inducedGridPointsIt : mInducedGridPoints) {
        
                auto fixed = inducedGridPointsIt.first;
                auto inducedGridPoints = inducedGridPointsIt.second;
        
                std::cout << inducedGridPoints << std::endl;
                
                // get the position of the first element greater then the coordinate + 1
                auto it = std::lower_bound(inducedGridPoints.begin(), inducedGridPoints.end(),
                        x.coordinate(fixed) + 1);
                
                // insert the element one before the element found above
                coordinates.insert(std::make_pair(fixed,
                        inducedGridPoints.at(it - 1 - inducedGridPoints.begin())));
            }
            //LOG4CPLUS_DEBUG(mLogger, "Calculating induced coordinates:" << x << " -> " << induced);
        }
        
        Point<Number> induced = Point<Number>(coordinates);
        return induced;
    }
        
}