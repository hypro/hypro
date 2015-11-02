/**
 * This example file shows the basic usage of the fileWriter.
 */

#include "../src/lib/config.h"
#include "../src/lib/representations/Polytope/Polytope.h"
#include "../src/lib/datastructures/Point.h"


int main(int argc, char** argv) {

	typedef carl::FLOAT_T<double> number_t;

    hypro::Point<number_t> p1;
    hypro::Point<number_t> p2;
    hypro::Point<number_t> p3;
    hypro::Point<number_t> p4;

    // p1
    p1 = hypro::Point<number_t>({4,4});

    // p2
    p2 = hypro::Point<number_t>({5,7});

    // p3
    p3 = hypro::Point<number_t>({7,7});

    // p4
    p4 = hypro::Point<number_t>({8,4});

    std::vector<hypro::Point<number_t>> pv;
    pv.push_back(p1);
    pv.push_back(p2);
    pv.push_back(p3);
    pv.push_back(p4);
    hypro::Polytope<number_t> polytope = hypro::Polytope<number_t>(pv);

    polytope.writeToFile("testPolytope.txt");

    return 0;
}