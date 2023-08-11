/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "util.h"

#include <algorithm>
#include <cassert>
#include <numeric>

namespace hypro {
    namespace reachability {

        std::vector <std::size_t> clusterDistribution(std::size_t numberClusters, std::size_t numberStateSets) {
            if (numberClusters >= numberStateSets) {
                return std::vector<std::size_t>(numberStateSets, 1);
            }
            std::vector <std::size_t> clusterDistribution;
            std::size_t minSegmentsPerCluster = numberStateSets / numberClusters;
            std::size_t largerClusterCount = numberStateSets - minSegmentsPerCluster * numberClusters;

            assert(minSegmentsPerCluster > 0);
            assert(largerClusterCount <= numberClusters);

            clusterDistribution = std::vector<std::size_t>(numberClusters, minSegmentsPerCluster);
            for (std::size_t i = 0; i < largerClusterCount; ++i) {
                clusterDistribution[i] += 1;
            }

            assert(std::all_of(clusterDistribution.begin(), clusterDistribution.end(),
                               [](std::size_t cnt) { return cnt > 0; }) && "Will have empty clusters");
            assert(std::accumulate(clusterDistribution.begin(), clusterDistribution.end(), std::size_t(0)) ==
                   numberStateSets);
            return clusterDistribution;
        }

    }  // namespace reachability
}  // namespace hypro
