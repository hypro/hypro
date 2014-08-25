/**
 * A simple example file to test the vertex enumeration algorithm.
 */

#include "../src/lib/representations/Polytopes/HPolytope/HPolytope.h"

using namespace std;
using namespace hypro;



int main(int argc, char** argv) {
    HPolytope<double> poly(polytope::Hyperplane<double>(Point<double>({-1,-1}), 3));
    
}
