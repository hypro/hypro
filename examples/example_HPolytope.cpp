#include "../src/lib/util/convexHull.h"
#include "../src/lib/config.h"
#include "../src/lib/representations/Polytopes/HPolytope/HPolytope.h"
#include "../src/lib/representations/Polytope/Polytope.h"

#include <iostream>
#include <fstream>

typedef float Number;

int main()
{
    hypro::matrix_t<Number> HPolyEquations = hypro::matrix_t<Number>(4,6);
    HPolyEquations << 1.0, 1.0, 2/3.0, -2/3.0,     0.0,     0.0,
                      0.0, 0.0,  0.0,     0.0,     1.0,    -1.0,
                      0.0, 0.0,  1.0,    -1.0,   2/3.0,  -2/3.0,
                      7.0, 5.0,  9.5,    -9.5,  13/3.0, -13/3.0;
    
    // All we want now is write to see the results
    std::ofstream results("example_HPolytope.txt");
   
    results << HPolyEquations; 
    
    results.close(); // Just closes the file
    
    return 0;
}

/*
 * x <= 7
 * x >= 5
 * z + 2/3 x <= 9,5
 * -z - 2/3 x <= -9,5
 * y + 2/3 z <= 4 1/3
 * -y - 2/3 z <= -4 1/3 
 */