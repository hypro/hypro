/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * This file shows how to use the plotter.
 * @file example_plot.cpp
 *
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since	2015-03-01
 * @version	2015-03-01
 */

#include <hypro/config.h>
#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/util/plotting/Plotter.h>

using namespace hypro;
using namespace carl;

int main() {

    VertexContainer<double> container;
    container.insert(Point<double>({3, 0}), true);
    container.insert(Point<double>({5, 0}), false);
    container.insert(Point<double>({5, 2}), true);
    container.insert(Point<double>({7, 2}), true);
    container.insert(Point<double>({7, 0}), true);
    container.insert(Point<double>({9, 0}), false);
    container.insert(Point<double>({9, 2}), true);
    container.insert(Point<double>({11, 2}), false);
    container.insert(Point<double>({11, 4}), false);
    container.insert(Point<double>({9, 4}), false);
    container.insert(Point<double>({9, 7}), false);
    container.insert(Point<double>({7, 6}), true);
    container.insert(Point<double>({7, 4}), true);
    container.insert(Point<double>({5, 4}), false);
    container.insert(Point<double>({5, 6}), true);
    container.insert(Point<double>({3, 7}), false);

    // container.insert(Point<double>({2,0}), true);
    // container.insert(Point<double>({6,0}), false);
    // container.insert(Point<double>({2,6}), false);
    // container.insert(Point<double>({6,6}), false);

    VertexContainer<double> container2;
    container2.insert(Point<double>({4, 2}), true);
    container2.insert(Point<double>({4, 8}), false);
    container2.insert(Point<double>({8, 2}), false);
    container2.insert(Point<double>({8, 8}), false);

    OrthogonalPolyhedron<double> test(container);
    OrthogonalPolyhedron<double> test2(container2);

    // std::cout << "Color Test:" << std::endl;
    // Point<double> p1({6,4});
    // Point<double> p2({2,4});
    // Point<double> p3({4,6});
    // Point<double> p4({4,2});
    // Point<double> p5({5.9,4});
    // assert(test.contains(p1));
    // assert(test.contains(p2));
    // assert(test.contains(p3));
    // assert(test.contains(p4));
    // assert(test.contains(p5));
    // std::cout << "Color Test End." << std::endl;

    std::vector<Point<double>> neighborhood =
            test.neighborhood(Point<double>({20, 40}));
    std::cout << "neighborhood: " << std::endl;
    for (const auto &point: neighborhood) {
        std::cout << point << std::endl;
    }

    std::vector<Point<double>> islice = test.iSlice(0, 2);
    std::cout << "0-3-slice: " << std::endl;
    for (const auto &point: islice) {
        std::cout << point << std::endl;
    }

    // plot
    std::cout << "Plotting." << std::endl;
    hypro::Plotter<double> &plotter = hypro::Plotter<double>::getInstance();
    plotter.setFilename("ortho");
    plotting::gnuplotSettings settings;
    settings.fill = true;
    plotter.updateSettings(settings);

    // OrthogonalPolyhedron<double> united = test.unite(test2);
    // for(const auto& vertex : united.vertices()) {
    // 	std::cout << vertex << std::endl;
    // }

    OrthogonalPolyhedron<double> intersection = test.intersect(test2);
    for (const auto &vertex: intersection.vertices()) {
        std::cout << vertex << std::endl;
    }

    // TODO: Fix plotter to allow direct object adding.
    // unsigned test2Id = plotter.addObject(test2.preparePlot(0,1), false);
    // unsigned testId = plotter.addObject(test.preparePlot(0,1), false);
    for (const auto &set: intersection.preparePlot(0, 1)) {
        unsigned intersectionObject = plotter.addObject(set);
        plotter.setObjectColor(intersectionObject,
                               plotting::colors[plotting::orange]);
    }

    // unsigned unionObject = plotter.addObject(united.preparePlot(0,1), false);

    // plotter.setObjectColor(unionObject, plotting::colors[plotting::orange]);

    plotter.plot2d();

    return 0;
}
