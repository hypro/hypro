/**
 * A simple example file to test the vertex enumeration algorithm.
 */

#include "../src/lib/representations/Polytopes/HPolytope/HPolytope.h"

using namespace std;
using namespace hypro;



int main(int argc, char** argv) {
    HPolytope<double> poly(polytope::Hyperplane<double>(Point<double>({-1,-1}), 3));
    
    poly.addConstraint(polytope::Hyperplane<double>(Point<double>({1,-1}), 0));
    poly.addConstraint(polytope::Hyperplane<double>(Point<double>({1/3,-1}), 3));
    poly.addConstraint(polytope::Hyperplane<double>(Point<double>({-3,-1}), 17));
    poly.addConstraint(polytope::Hyperplane<double>(Point<double>({0,-1}), 2));
}
