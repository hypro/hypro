/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * \example example_plot.cpp This file shows how to use the plotter.
 */

#include <hypro/datastructures/Point.h>
#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/util/plotting/Plotter.h>

#include <random>

using namespace hypro;

int main() {
    typedef double Number;

    // get reference to singleton plotter
    Plotter<Number> &plotter = Plotter<Number>::getInstance();

    double lower_bound = 0;
    double upper_bound = 0.2;
    std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
    std::default_random_engine re;
    // double a_random_double = unif(re);

    // define starting point(s)
    int samples = 2;
    std::vector<hypro::Point<Number>> points;
    points.push_back(hypro::Point<Number>{0, 0.1, 1, 0.1, 1});
    points.push_back(hypro::Point<Number>{0, 0, 1, 0.1, 1});
    points.push_back(hypro::Point<Number>{0, 0.2, 1, 0.1, 1});

    while (samples > 0) {
        points.push_back(hypro::Point<Number>{0, unif(re), 1, 0.1, 1});
        --samples;
    }

    hypro::matrix_t<Number> A = hypro::matrix_t<Number>(5, 5);
    A << 1, 0, 0.001, 0, 0, 0, 1, 0, 0.001, 0.000000375, 0, 0, 1, 0, 0, 0, -0.001,
            0, 1, 0.00075, 0, 0, 0, 0, 1;

    for (int i = 0; i < 8000; ++i) {
        for (auto &p: points) {
            auto t = p.linearTransformation(A);
            plotter.addObject({p.projectOn({0, 1}), t.projectOn({0, 1})});
            p = std::move(t);
        }
    }

    // we may adjust the output file name (default out.XYZ), the file type is
    // determined by the used plot function (see below) the filename also
    // determines the title of the plot
    plotter.setFilename("plotTest");

    // write plot files - gnuplot files with different output terminals are
    // supported: pdf (plot2d), tex (plotTex), and eps (plotEps). plain gnuplot
    // files (*.gen) may also be created via plotGen().
    plotter.plot2d();
    plotter.plotTex();
    plotter.plotEps();

    return 0;
}
