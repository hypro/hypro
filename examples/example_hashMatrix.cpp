/*
 * @file    example_zonotope.cpp
 * @author  Leonardo Winter Pereira
 * @since   2015-09-09
 * @version 2015-09-09
 */

#include <fstream>
#include <iostream>
#include <string>

#include "../src/hypro/config.h"
#include "../src/hypro/representations/GeometricObject.h"
#include "../src/hypro/util/plotting/Plotter.h"

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
