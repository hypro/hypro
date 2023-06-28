/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * @file    NeighborhoodContainer.h
 * @author  Benedikt Seidl
 */

#pragma once

#include "../../datastructures/Vertex.h"

#include <map>

namespace hypro {

/**
 * @brief      A neighborhood container which maps points
 * to their set of neighbor points.
 */
    class NeighborhoodContainer {
    public:
        using neighborhood = std::vector<Point<int> >;

    private:
        std::map<Point<int>, neighborhood> mNeighborhoods;

    public:
        NeighborhoodContainer() {}

        NeighborhoodContainer(const NeighborhoodContainer &copy) {
            mNeighborhoods.insert(copy.mNeighborhoods.begin(), copy.mNeighborhoods.end());
        }

        NeighborhoodContainer &operator=(const NeighborhoodContainer &orig) = default;

        NeighborhoodContainer &operator=(NeighborhoodContainer &&orig) = default;

        ~NeighborhoodContainer() {}

        void clear() { mNeighborhoods.clear(); }

        bool empty() const { return mNeighborhoods.empty(); }

        /**
         * Returns the points in the neighborhood.
         *
         * @param p the point
         * @param pointself point is optionally an element of the returned vector
         * @return Vector filled with neighbors in all dimensions
         */
        neighborhood getNeighborhood(const Point<int> &p, bool pointself = false);

        /**
         * Returns the points in the neighborhood, with one fixed dimension.
         *
         * @param p the point
         * @param dimension the fixed dimension
         * @param pointself point is optionally an element of the returned vector
         * @return
         */
        neighborhood getNeighborhoodForDimension(const Point<int> &p, const carl::Variable &dimension,
                                                 bool pointself = false);

        /**
         * Moves all neighbors.
         *
         * @param p the point by which the neighbors should be moved
         */
        // void moveNeighbors(const Point<int>& p);

    private:
        bool hasNeighborhood(const Point<int> &p) const { return mNeighborhoods.find(p) != mNeighborhoods.end(); }

        void calculateNeighborhood(const Point<int> &p);
    };

}  // namespace hypro
