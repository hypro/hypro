/** 
 * @file    NeighborhoodContainer.tpp
 * @author  Sebastian Junges
 * @author  Benedikt Seidl
 *
 * @since   2014-03-17
 * @version 2014-03-17
 */

namespace hypro
{
    
    template<typename Number>
    typename NeighborhoodContainer<Number>::neighborhood NeighborhoodContainer<Number>::getNeighborhood(const Point<Number>& p, bool pointself)
    {
        if (!hasNeighborhood(p)) {
            calculateNeighborhood(p);
        }

        auto neighbors = mNeighborhoods.at(p);

        if (pointself) {
            neighbors.push_back(p);
        }

        return neighbors;
    }

    template<typename Number>
    typename NeighborhoodContainer<Number>::neighborhood NeighborhoodContainer<Number>::getNeighborhoodForDimension(const Point<Number>& p, const carl::Variable& dimension, bool pointself)
    {
        if (!hasNeighborhood(p)) {
            calculateNeighborhood(p);
        }

        auto neighbors = mNeighborhoods.at(p);
        Number coordinate = p.coordinate(dimension);

        // remove all neighbors which do not have the same value in that dimension as the original point
        for (auto it = neighbors.begin(); it != neighbors.end(); ) {
            if (it->coordinate(dimension) != coordinate) {
                neighbors.erase(it);
            } else {
                it++;
            }
        }

        if (pointself) {
            neighbors.push_back(p);
        }

        return neighbors;
    }

    template<typename Number>
    void NeighborhoodContainer<Number>::calculateNeighborhood(const Point<Number>& p)
    {
        std::vector<Point<Number> > neighbors;
        unsigned dim = p.dimension();

        // the number of neighbors is 2^(dimension) - 1
        int nrofNeighbors = (pow(2, dim) - 1);

        typename Point<Number>::coordinateMap coordinates, pointCoordinates = p.coordinates();

        // iterate through all neighbors
        for (int neighborNr = 1; neighborNr <= nrofNeighbors; neighborNr++) {
            // then iterate through all dimensions
            int i = 0;
            for (auto& pointIt : pointCoordinates) {
                // look if the bit of the current coordinate is set
                // thus the first point will have 1 less in every second dimension,
                // the second point will have 1 less in every fourth dimension etc.
                if ((neighborNr >> i++) & 1) {
                    coordinates[pointIt.first] = pointIt.second - 1;
                }
                else {
                    coordinates[pointIt.first] = pointIt.second;
                }
            }
            Point<Number> neighbor = Point<Number>(coordinates);
            neighbors.push_back(neighbor);
        }

        mNeighborhoods.insert(std::make_pair(p, neighbors));
    }
    
}//namespace
