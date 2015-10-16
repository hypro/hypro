/**
 * A simple example file to test the vertex enumeration algorithm.
 */

#include "../src/lib/representations/Polytopes/HPolytope/HPolytope.h"

int main(int argc, char** argv) {
    hypro::HPolytope<double> poly(hypro::Hyperplane<double>(hypro::Point<double>({1,3}), 4));

    poly.insert(hypro::Hyperplane<double>(hypro::Point<double>({5,1}), 5));
    poly.insert(hypro::Hyperplane<double>(hypro::Point<double>({3,2}), 2));
    poly.insert(hypro::Hyperplane<double>(hypro::Point<double>({-1,-3}), 1));
    poly.insert(hypro::Hyperplane<double>(hypro::Point<double>({-2,1}), 2));

    //std::cout << "Initial Polytope:" << std::endl;
    //std::cout << poly << std::endl;

    poly.vertexEnumeration();
}
