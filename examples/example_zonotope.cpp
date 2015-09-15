/*
 * @file    example_zonotope.cpp
 * @author  Leonardo Winter Pereira
 * @since   2015-09-09
 * @version 2015-09-09
 */

#include <iostream>
#include <fstream>
#include <string>

#include "../src/lib/config.h"
#include "../src/lib/util/Plotter.h"
#include "../src/lib/representations/Zonotope/Zonotope.h"

using namespace hypro;
using namespace carl;

typedef FLOAT_T<double> Number;

int main(int argc, char** argv)
{
    vector_t<Number> vCenter = vector_t<Number>(3);
    
    vCenter(0) = 0.0d;
    vCenter(1) = 0.0d;
    vCenter(2) = 0.0d;
    
    matrix_t<Number> vGenerators = matrix_t<Number>(3,3);
    
    vGenerators(0, 0) = 1.0d;
    vGenerators(0, 1) = 0.0d;
    vGenerators(0, 2) = 0.0d;
    
    vGenerators(1, 0) = 0.0d;
    vGenerators(1, 1) = 1.0d;
    vGenerators(1, 2) = 0.0d;
    
    vGenerators(2, 0) = 0.0d;
    vGenerators(2, 1) = 0.0d;
    vGenerators(2, 2) = 1.0d;
    
    Zonotope<Number> zonoExample(vCenter, vGenerators);
    
    // Just for test purposes!! Let's see the corner's points       
    //std::vector<vector_t<Number> > vCorners = zonoExample.corners();
    
    // All we want now is write to see the results
    std::ofstream results("example_zonotope.txt");
 
    results << zonoExample.dimension() << "\n" << zonoExample.generators() << "\n\n\n";
    
    results << zonoExample.corners();
    
    results.close(); // Just close the file 
    
    return 0;
}