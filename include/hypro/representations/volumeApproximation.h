
/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "../config.h"

namespace hypro {

/**
 * Approximate volume by creating a grid of points and update the total volume if the point is inside.
 */
    template<typename Number, typename Representation>
    static Number approximateVolume(Representation _in) {
        Number pointCount = 0;

        std::vector<Point<Number>> vertices = _in.vertices();

        unsigned dimension = vertices[0].dimension();
        std::vector<std::pair<Number, Number>> bounderies;
        std::vector<bool> count_help;
        vector_t<Number> count_point = vector_t<Number>::Zero(dimension);
        std::vector<Number> resolution;
        bool running = true;
        Number volumeUnit = 1;

        // TODO, also figure out, if we need Number as a template parameter (I guess not)
        // TODO: where do we set the initial resolution? As a parameter with a default value specified as a constant in config.h maybe.

        // init
        for (unsigned i = 0; i < dimension; i++) {
            bounderies.push_back(std::pair<Number, Number>(0, 0));
            count_help.push_back(false);
            resolution.push_back(0);
        }

        // Compute bounderies
        for (Point<Number> vertex: vertices) {
            for (unsigned i = 0; i < dimension; i++) {
                if (bounderies.at(i).first > vertex.coordinate(i)) {    // min
                    bounderies.at(i).first = vertex.coordinate(i);
                } else if (bounderies.at(i).second < vertex.coordinate(i)) {    // max
                    bounderies.at(i).second = vertex.coordinate(i);
                }
            }
        }

        // Post-init with bounderies-info: compute resolution, volumeUnit and init count_point
        for (unsigned i = 0; i < dimension; i++) {
            // std::cout << "bound." << i << " : " << bounderies[i].first << " till " << bounderies[i].second << std::endl;
            resolution[i] = (bounderies[i].second - bounderies[i].first) /
                            3;     // 100 for 2D, 50 for 3D, 12 for 4D - if to high -> might be very slow
            if (!carl::AlmostEqual2sComplement(resolution[i] + (Number) 1, (Number) 1)) {
                volumeUnit *= resolution[i];
            }
            count_point(i) = bounderies[i].first;
        }

        // Create a grid from bounderies and decide (count) for each point if _in contains it - recursive?
        while (running) {
            for (unsigned i = 0; i < dimension; i++) {
                if (i == 0 || count_help[i]) {
                    count_point(i) += resolution[i];
                    count_help[i] = false;
                    if (count_point(i) > bounderies[i].second && i < dimension - 1) {
                        count_point(i) = bounderies[i].first;
                        count_help[i + 1] = true;
                    } else if (count_point(i) > bounderies[i].second && i == dimension - 1) {
                        running = false;
                    }
                }
            }
            if (_in.contains(Point<Number>(count_point))) {
                pointCount += volumeUnit;
            }
        }

        return pointCount;
    }

}  // namespace hypro
