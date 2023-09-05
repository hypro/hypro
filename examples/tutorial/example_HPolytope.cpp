/*
 * Copyright (c) 2023-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/** \example example_HPolytope.cpp
 * 	This is an example file showing how to create and modify a polytope in
 * H-representation.
 */

#include "hypro/representations/GeometricObjectBase.h"
#include "hypro/util/plotting/Plotter.h"

using Number = double;

int main() {
    // we create the constraints and constants defining a 2D-unit box.
    hypro::matrix_t<Number> HPolyConstraints = hypro::matrix_t<Number>(4, 2);
    HPolyConstraints << 1, 0, -1, 0, 0, 1, 0, -1;
    hypro::vector_t<Number> HPolyConstants = hypro::vector_t<Number>(4);
    HPolyConstants << 1, 1, 1, 1;

    // create the actual polytope and add its vertices to the global plotter
    // (singleton).
    hypro::HPolytope<Number> poly(HPolyConstraints, HPolyConstants);
    hypro::Plotter<Number>::getInstance().addObject(poly.vertices());

    // create rotation matrix for +45 degrees (corresponds to ~0.785398 radians).
    hypro::matrix_t<Number> rotation = hypro::matrix_t<Number>(2, 2);
    rotation << std::cos(0.785398), -std::sin(0.785398), std::sin(0.785398),
            std::cos(0.785398);

    // perform linear transformation (rotation) and plot the new object in green
    // (default = blue).
    poly = poly.linearTransformation(rotation);
    unsigned obj2 =
            hypro::Plotter<Number>::getInstance().addObject(poly.vertices(),
                                                            hypro::plotting::colors[hypro::plotting::green]);

    // create a *.plt file (gnuplot).
    hypro::Plotter<Number>::getInstance().plot2d();

    return 0;
}
