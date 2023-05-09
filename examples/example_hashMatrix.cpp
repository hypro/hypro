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

#include <fstream>
#include <iostream>
#include <string>
#include <hypro/config.h>
#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/util/plotting/Plotter.h>

using namespace hypro;

typedef double Number;

int main() {
    // Just creates an empty Center
    vector_t<Number> vCenter = vector_t<Number>(3);
    vCenter(0) = 0;
    vCenter(1) = 0;
    vCenter(2) = 0;

    // Just creates the Generators (3 for now)
    matrix_t<Number> vGenerators = matrix_t<Number>(3, 4);

    vGenerators(0, 0) = 1;
    vGenerators(1, 0) = 0;
    vGenerators(2, 0) = 0;

    vGenerators(0, 1) = 0;
    vGenerators(1, 1) = 1;
    vGenerators(2, 1) = 0;

    vGenerators(0, 2) = 0;
    vGenerators(1, 2) = 0;
    vGenerators(2, 2) = 1;

    vGenerators(0, 3) = 1;
    vGenerators(1, 3) = 1;
    vGenerators(2, 3) = 1;

    // To test the uniteEqualVectors function!
    //
    // for (int i = 3; i < vGenerators.cols(); i++)
    //{
    //    vGenerators(0, i) = 1;
    //   vGenerators(1, i) = 0;
    //    vGenerators(2, i) = 0;
    //}

    Zonotope<Number> zonoExample(vCenter, vGenerators); // Creates an Zonotope

    // zonoExample = zonoExample.minkowskiSum(zonoExample); // Just debugging the
    // Minkowski Sum

    // All we want now is write to see the results
    std::ofstream results("example_zonotope.txt");

    results << "Dimension: " << zonoExample.dimension() << "\n\n\n"
            << "Center: " << vCenter << "\n\n\n"
            << "Generators: \n"
            << zonoExample.generators() << "\n\n\n";

    zonoExample.uniteEqualVectors();

    results << "Number of Generators: " << zonoExample.generators().size()
            << "\n\n\n"
            << "new Generators: \n"
            << zonoExample.generators() << "\n\n\n";

    // struct timeval t1, t2;
    // double elapsedTime;

    // start timer
    // gettimeofday(&t1, NULL);

    results << "Corners:\n"
            << zonoExample.vertices()
            << "\n\n\n"; // Here we unite equal vectors (for optimization), and
    // calculate (recursive) the corners!!

    // stop timer
    // gettimeofday(&t2, NULL);

    // compute and print the elapsed time in millisec
    // elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
    // elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms

    // results << "Time spent: " << elapsedTime << "ms\n";

    results.close(); // Just closes the file

    return 0;
}
