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

#include "../src/hypro/config.h"
#include "../src/hypro/util/Plotter.h"
#include "../src/hypro/representations/GeometricObject.h"


typedef int Number;

int main()
{
	typedef double Number;

    // Just creates an empty Center
    hypro::vector_t<Number> vCenter1 = hypro::vector_t<Number>(2);
    vCenter1 << 3,3;
    hypro::vector_t<Number> vCenter2 = hypro::vector_t<Number>(2);
    vCenter2 << 1,1;

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

    hypro::Zonotope<Number> zonoExample(vCenter1, vGenerators); // Creates an Zonotope
    hypro::Zonotope<Number> zonoExample2(vCenter2, vGenerators2); // Creates an Zonotope
    hypro::Plotter<Number>& plotter = hypro::Plotter<Number>::getInstance();

    std::cout << "Zonotope: " << zonoExample2 << std::endl;
    std::cout << "Vertices:" << std::endl;
    std::vector<hypro::Point<Number>> vertices = zonoExample2.vertices();
    for(const auto& vertex : vertices){
    	std::cout << vertex << std::endl;
    }

    unsigned z1 = plotter.addObject(zonoExample.vertices());
    plotter.setObjectColor(z1, hypro::colors[hypro::red]);
    unsigned z2 = plotter.addObject(zonoExample2.vertices());
    plotter.setObjectColor(z2, hypro::colors[hypro::orange]);
    unsigned z3 = plotter.addObject(zonoExample.unite(zonoExample2).vertices());
    plotter.setObjectColor(z3, hypro::colors[hypro::green]);

    hypro::vector_t<Number> d = hypro::vector_t<Number>(2);
    d << 0, -1;

    hypro::Zonotope<Number> intersectionResult = zonoExample2.intersectHalfspace(hypro::Halfspace<Number>(d, -2));
    unsigned z4 = plotter.addObject(intersectionResult.vertices());
	plotter.setObjectColor(z4, hypro::colors[hypro::lila]);

	// Provoke intersection with a line by intersecting with two halfspaces.
	hypro::matrix_t<Number> constraints = hypro::matrix_t<Number>(2,2);
	constraints << 0,-1,0,1;
	hypro::vector_t<Number> constants = hypro::vector_t<Number>(2);
	constants << -6,6;
	hypro::Zonotope<Number> intersectionResult2 = zonoExample.unite(zonoExample2).intersectHalfspaces(constraints,constants);
    unsigned z5 = plotter.addObject(intersectionResult2.vertices());
	plotter.setObjectColor(z5, hypro::colors[hypro::petrol]);

	hypro::matrix_t<Number> A = hypro::matrix_t<Number>(2,2);
	A << 1,0.01,0,1;
	hypro::vector_t<Number> b = hypro::vector_t<Number>(2);
	b << -3,3;
	std::cout << "A: " << A << " and b: " << b << std::endl;

	hypro::Zonotope<Number> linearTrafoResult = zonoExample.affineTransformation(A,b);
	unsigned z6 = plotter.addObject(linearTrafoResult.vertices());
	plotter.setObjectColor(z6, hypro::colors[hypro::blue]);

    plotter.plot2d();
    plotter.plotTex();


    // All we want now is write to see the results
    std::ofstream results("example_zonotope.txt");

    results << "Dimension: " << zonoExample.dimension() << "\n\n\n" << "Center: " << vCenter1 << "\n\n\n" << "Generators: \n" << zonoExample.generators() << "\n\n\n";

    zonoExample.uniteEqualVectors();

    results << "Number of Generators: " << zonoExample.size() << "\n\n\n" << "new Generators: \n" << zonoExample.generators() << "\n\n\n";

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
