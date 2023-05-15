/*
 * Copyright (c) 2023-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * \example example_converter.cpp
 * This example shows how to use the provided converter. We start by creating a
 * support function representing some polytope. The resulting set is converted
 * to a box representation. The same conversion is afterwards performed with a
 * freshly created V-polytope and a zonotope.
 */

#include "hypro/representations/GeometricObjectBase.h"

using namespace hypro;

int main() {

    // create a matrix and a vector describing a H-polytope.
    matrix_t<double> matrix2 = matrix_t<double>(3, 2);
    vector_t<double> distances2 = vector_t<double>(3);
    matrix2 << 1, 1, -1, 1, 0, -1, distances2 << 1, 1, 0;

    // create a support function.
    SupportFunction<double> poly2 = SupportFunction<double>(matrix2, distances2);

    // conversion of the support function to a box by using templated evaluation.
    hypro::Box<double> res = Converter<double>::toBox(poly2);

    // creation of a vector of points to define a V-polytope.
    vector_t<double> p1 = vector_t<double>(2);
    p1(0) = 1;
    p1(1) = 2;
    vector_t<double> p2 = vector_t<double>(2);
    p2(0) = 3;
    p2(1) = 2;
    vector_t<double> p3 = vector_t<double>(2);
    p3(0) = 3;
    p3(1) = 4;
    vector_t<double> p4 = vector_t<double>(2);
    p4(0) = 1;
    p4(1) = 4;
    std::vector<hypro::Point<double>> points;
    points.emplace_back(p1);
    points.emplace_back(p2);
    points.emplace_back(p3);
    points.emplace_back(p4);

    // construction of a V-polytope.
    VPolytope<double> poly1 = VPolytope<double>(points);

    // conversion of the V-polytope to a box.
    res = Converter<double>::toBox(poly1);

    // creation of a center and a set of generators for a zonotope.
    vector_t<double> center = vector_t<double>(2);
    center << 2.0, 2.0;

    matrix_t<double> generators = matrix_t<double>(2, 2);
    generators << 0.0, 1.0, 1.0, -1.0;

    // creation of a zonotope from a center vector and a set of generators.
    Zonotope<double> zono1 = Zonotope<double>(center, generators);

    // convert the zonotope to a box.
    res = Converter<double>::toBox(zono1);
}
