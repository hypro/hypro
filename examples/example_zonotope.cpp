/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * @file    example_zonotope.cpp
 * @author  Leonardo Winter Pereira
 * @since   2015-09-09
 * @version 2015-09-09
 */

#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/util/plotting/Plotter.h>
#include <sys/time.h>

typedef int Number;

int main() {
    typedef double Number;

    // Just creates an empty Center
    hypro::vector_t<Number> vCenter1 = hypro::vector_t<Number>(2);
    vCenter1 << 3, 3;
    hypro::vector_t<Number> vCenter2 = hypro::vector_t<Number>(2);
    vCenter2 << 1, 1;

    // Just creates the Generators (3 for now)
    hypro::matrix_t<Number> vGenerators = hypro::matrix_t<Number>(2, 3);
    vGenerators << 1, 0, 1, 1, 1, -2;

    hypro::matrix_t<Number> vGenerators2 = hypro::matrix_t<Number>(2, 2);
    vGenerators2 << 1, 0, 1, 1;

    // To test the uniteEqualVectors function!
    //
    // for (int i = 3; i < vGenerators.cols(); i++)
    //{
    //    vGenerators(0, i) = 1;
    //   vGenerators(1, i) = 0;
    //    vGenerators(2, i) = 0;
    //}

    hypro::Zonotope<Number> zonoExample(vCenter1.rows(), vCenter1,
                                        vGenerators); // Creates an Zonotope
    hypro::Zonotope<Number> zonoExample2(vCenter2.rows(), vCenter2,
                                         vGenerators2); // Creates an Zonotope
    hypro::Plotter<Number> &plotter = hypro::Plotter<Number>::getInstance();

    std::cout << "Zonotope: " << zonoExample2 << std::endl;
    std::cout << "Vertices:" << std::endl;
    std::vector<hypro::Point<Number>> vertices = zonoExample2.vertices();
    for (const auto &vertex: vertices) {
        std::cout << vertex << std::endl;
    }

    unsigned z1 = plotter.addObject(zonoExample.vertices());
    plotter.setObjectColor(z1, hypro::plotting::colors[hypro::plotting::red]);
    unsigned z2 = plotter.addObject(zonoExample2.vertices());
    plotter.setObjectColor(z2, hypro::plotting::colors[hypro::plotting::orange]);
    unsigned z3 = plotter.addObject(zonoExample.unite(zonoExample2).vertices());
    plotter.setObjectColor(z3, hypro::plotting::colors[hypro::plotting::green]);

    hypro::vector_t<Number> d = hypro::vector_t<Number>(2);
    d << 0, -1;

    hypro::Zonotope<Number> intersectionResult =
            zonoExample2.intersectHalfspace(hypro::Halfspace<Number>(d, -2));
    unsigned z4 = plotter.addObject(intersectionResult.vertices());
    plotter.setObjectColor(z4, hypro::plotting::colors[hypro::plotting::lila]);

    // Provoke intersection with a line by intersecting with two halfspaces.
    hypro::matrix_t<Number> constraints = hypro::matrix_t<Number>(2, 2);
    constraints << 0, -1, 0, 1;
    hypro::vector_t<Number> constants = hypro::vector_t<Number>(2);
    constants << -6, 6;
    hypro::Zonotope<Number> intersectionResult2 =
            zonoExample.unite(zonoExample2)
                    .intersectHalfspaces(constraints, constants);
    unsigned z5 = plotter.addObject(intersectionResult2.vertices());
    plotter.setObjectColor(z5, hypro::plotting::colors[hypro::plotting::petrol]);

    hypro::matrix_t<Number> A = hypro::matrix_t<Number>(2, 2);
    A << 1, 0.01, 0, 1;
    hypro::vector_t<Number> b = hypro::vector_t<Number>(2);
    b << -3, 3;
    std::cout << "A: " << A << " and b: " << b << std::endl;

    hypro::Zonotope<Number> linearTrafoResult =
            zonoExample.affineTransformation(A, b);
    unsigned z6 = plotter.addObject(linearTrafoResult.vertices());
    plotter.setObjectColor(z6, hypro::plotting::colors[hypro::plotting::blue]);

    plotter.plot2d();

    // All we want now is write to see the results
    std::ofstream results("example_zonotope.txt");

    results << "Dimension: " << zonoExample.dimension() << "\n\n\n"
            << "Center: " << vCenter1 << "\n\n\n"
            << "Generators: \n"
            << zonoExample.generators() << "\n\n\n";

    zonoExample.uniteEqualVectors();

    results << "Number of Generators: " << zonoExample.size() << "\n\n\n"
            << "new Generators: \n"
            << zonoExample.generators() << "\n\n\n";

    struct timeval t1, t2;
    double elapsedTime;

    // start timer
    gettimeofday(&t1, NULL);

    results << "Corners:\n"
            << zonoExample.vertices()
            << "\n\n\n"; // Here we unite equal vectors (for optimization), and
    // calculate (recursive) the corners!!

    // stop timer
    gettimeofday(&t2, NULL);

    // compute and print the elapsed time in millisec
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;    // sec to ms
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0; // us to ms

    results << "Time spent: " << elapsedTime << "ms\n";

    results.close(); // Just closes the file

    return 0;
}
