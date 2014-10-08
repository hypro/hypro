/**
 * A simple example file to test the vertex enumeration algorithm.
 */

#include "../src/lib/representations/Polytopes/HPolytope/HPolytope.h"

using namespace std;
using namespace hypro;



int main(int argc, char** argv) {
    HPolytope<double> poly(polytope::Hyperplane<double>(Point<double>({1,3}), 4));
    
    poly.addConstraint(polytope::Hyperplane<double>(Point<double>({5,1}), 5));
    poly.addConstraint(polytope::Hyperplane<double>(Point<double>({3,2}), 2));
    poly.addConstraint(polytope::Hyperplane<double>(Point<double>({-1,-3}), 1));
    poly.addConstraint(polytope::Hyperplane<double>(Point<double>({-2,1}), 2));
    
    //std::cout << "Initial Polytope:" << std::endl;
    //std::cout << poly << std::endl;
    
    poly.vertexEnumeration();
}
