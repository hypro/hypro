/*
 * @file    example_zonotope.cpp
 * @author  Leonardo Winter Pereira
 * @since   2015-09-09
 * @version 2015-09-09
 */

#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <map>
#include <sys/time.h>

#include "../src/lib/config.h"
#include "../src/lib/util/Plotter.h"
#include "../src/lib/representations/GeometricObject.h"


typedef int Number;

int main(int argc, char** argv)
{
	typedef cln::cl_RA Number;

    // Just creates an empty Center
    hypro::vector_t<Number> vCenter = hypro::vector_t<Number>(2);
    vCenter << 3,3;

    // Just creates the Generators (3 for now)
    hypro::matrix_t<Number> vGenerators = hypro::matrix_t<Number>(2,3);
    vGenerators << 1, 0, 1,
                   1, 1, -2;

hypro::matrix_t<Number> vGenerators2 = hypro::matrix_t<Number>(2,2);
    vGenerators2 << 1, 0,
                   1, 1;

    //To test the uniteEqualVectors function!
    //
    //for (int i = 3; i < vGenerators.cols(); i++)
    //{
    //    vGenerators(0, i) = 1;
    //   vGenerators(1, i) = 0;
    //    vGenerators(2, i) = 0;
    //}

    hypro::Zonotope<Number> zonoExample(vCenter, vGenerators); // Creates an Zonotope
    hypro::Zonotope<Number> zonoExample2(vCenter, vGenerators2); // Creates an Zonotope
    hypro::Plotter<Number>& plotter = hypro::Plotter<Number>::getInstance();

    plotter.addObject(zonoExample.vertices());
    plotter.addObject(zonoExample2.vertices());
    plotter.plot2d();
    plotter.plotTex();

    // All we want now is write to see the results
    std::ofstream results("example_zonotope.txt");

    results << "Dimension: " << zonoExample.dimension() << "\n\n\n" << "Center: " << vCenter << "\n\n\n" << "Generators: \n" << zonoExample.generators() << "\n\n\n";

    zonoExample.uniteEqualVectors();

    results << "Number of Generators: " << zonoExample.numGenerators() << "\n\n\n" << "new Generators: \n" << zonoExample.generators() << "\n\n\n";

    struct timeval t1, t2;
    double elapsedTime;

    // start timer
    gettimeofday(&t1, NULL);

    results << "Corners:\n" << zonoExample.vertices() << "\n\n\n"; // Here we unite equal vectors (for optimization), and calculate (recursive) the corners!!

    // stop timer
    gettimeofday(&t2, NULL);

    // compute and print the elapsed time in millisec
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms

    results << "Time spent: " << elapsedTime << "ms\n";

    results.close(); // Just closes the file

    return 0;
}
