/**
 * A simple example file to test the vertex enumeration algorithm.
 */

#include "../src/lib/representations/Polytopes/HPolytope/HPolytope.h"
#include "../src/lib/util/vertexEnumeration.h"

int main(int argc, char** argv) {
	typedef carl::FLOAT_T<cln::cl_RA> Number;

    hypro::HPolytope<Number> poly(hypro::Hyperplane<Number>(hypro::Point<Number>({1,3}), 4));

    poly.insert(hypro::Hyperplane<Number>(hypro::Point<Number>({5,1}), 5));
    poly.insert(hypro::Hyperplane<Number>(hypro::Point<Number>({3,2}), 2));
    poly.insert(hypro::Hyperplane<Number>(hypro::Point<Number>({-1,-3}), 1));
    poly.insert(hypro::Hyperplane<Number>(hypro::Point<Number>({-2,1}), 2));

    //std::cout << "Initial Polytope:" << std::endl;
    //std::cout << poly << std::endl;

    hypro::Dictionary<Number> initial = hypro::Dictionary<Number>(poly.matrix(), poly.vector());

    std::cout << "Dictionary: " << std::endl;
    std::cout << initial << std::endl;

    std::cout << "After pivot(1,4)" << std::endl;
    initial.pivot(1,4);
    std::cout << initial << std::endl;
}
