/** 
 * @file    NeighborhoodContainer.cpp
 * @author  Benedikt Seidl
 *
 * @since   2014-03-17
 * @version 2014-03-17
 */

#include "NeighborhoodContainer.h"

namespace hypro
{
    
    NeighborhoodContainer::neighborhood NeighborhoodContainer::getNeighborhood(const Point<int>& p, bool pointself)
    {
        if (!hasNeighborhood(p)) {
            calculateNeighborhood(p);
        }

        NeighborhoodContainer::neighborhood neighbors = mNeighborhoods.at(p);

        if (pointself) {
            neighbors.push_back(p);
        }

        return neighbors;
    }

    NeighborhoodContainer::neighborhood NeighborhoodContainer::getNeighborhoodForDimension(const Point<int>& p, const carl::Variable& dimension, bool pointself)
    {
        if (!hasNeighborhood(p)) {
            calculateNeighborhood(p);
        }

        NeighborhoodContainer::neighborhood neighbors = mNeighborhoods.at(p);
        int coordinate = p.coordinate(dimension);

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

    void NeighborhoodContainer::calculateNeighborhood(const Point<int>& p)
    {
        std::vector<Point<int> > neighbors;
        unsigned dim = p.dimension();

        // the number of neighbors is 2^(dimension) - 1
        int nrofNeighbors = (pow(2, dim) - 1);

        Point<int>::coordinateMap coordinates, pointCoordinates = p.coordinates();

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
            Point<int> neighbor = Point<int>(coordinates);
            neighbors.push_back(neighbor);
        }

        mNeighborhoods.insert(std::make_pair(p, neighbors));
    }
    
}//namespace
