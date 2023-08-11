/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * @file    NeighborhoodContainer.cpp
 * @author  Benedikt Seidl
 *
 * @since   2014-03-17
 * @version 2014-03-17
 */

#include "hypro/representations/OrthogonalPolyhedron/NeighborhoodContainer.h"

namespace hypro {

    NeighborhoodContainer::neighborhood NeighborhoodContainer::getNeighborhood(const Point<int> &p, bool pointself) {
        if (!hasNeighborhood(p)) {
            calculateNeighborhood(p);
        }

        NeighborhoodContainer::neighborhood neighbors = mNeighborhoods.at(p);

        if (pointself) {
            neighbors.push_back(p);
        }

        return neighbors;
    }

    NeighborhoodContainer::neighborhood
    NeighborhoodContainer::getNeighborhoodForDimension(const Point<int> &p, const carl::Variable &dimension,
                                                       bool pointself) {
        if (!hasNeighborhood(p)) {
            calculateNeighborhood(p);
        }

        NeighborhoodContainer::neighborhood neighbors = mNeighborhoods.at(p);
        int coordinate = p.coordinate(dimension);

        // remove all neighbors which do not have the same value in that dimension as the original point
        for (auto it = neighbors.begin(); it != neighbors.end();) {
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

    void NeighborhoodContainer::calculateNeighborhood(const Point<int> &p) {
        std::vector<Point<int> > neighbors;
        unsigned dim = p.dimension();

        // the number of neighbors is 2^(dimension) - 1
        int nrofNeighbors = (int(pow(2, dim)) - 1);

        vector_t<int> coordinates = p.rawCoordinates();
        vector_t<int> pointCoordinates = p.rawCoordinates();
        assert(coordinates.rows() == dim);

        // iterate through all neighbors
        for (int neighborNr = 1; neighborNr <= nrofNeighbors; neighborNr++) {
            // then iterate through all dimensions
            int i = 0;
            for (unsigned d = 0; d < dim; ++d) {
                // look if the bit of the current coordinate is set
                // thus the first point will have 1 less in every second dimension,
                // the second point will have 1 less in every fourth dimension etc.
                if ((neighborNr >> i++) & 1) {
                    coordinates(d) = pointCoordinates(d) - 1;
                } else {
                    coordinates(d) = pointCoordinates(d);
                }
            }
            Point<int> neighbor = Point<int>(coordinates);
            neighbors.push_back(neighbor);
        }
        mNeighborhoods.insert(std::make_pair(p, neighbors));
    }

}  // namespace hypro
