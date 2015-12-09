/**
 * A simple example file to test the vertex enumeration algorithm.
 */

#include "../src/lib/representations/Polytopes/HPolytope/HPolytope.h"
#include "../src/lib/util/vertexEnumeration.h"
#include "../src/lib/util/Plotter.h"

int main(int argc, char** argv) {
	typedef carl::FLOAT_T<cln::cl_RA> Number;

    hypro::HPolytope<Number> poly;

    poly.insert(hypro::Hyperplane<Number>({1,3}, 4));
    poly.insert(hypro::Hyperplane<Number>({5,1}, 5));
    poly.insert(hypro::Hyperplane<Number>({3,2}, 2));
    poly.insert(hypro::Hyperplane<Number>({-1,-3}, 1));
    poly.insert(hypro::Hyperplane<Number>({-2,1}, 2));

    //std::cout << "Initial Polytope:" << std::endl;
    //std::cout << poly << std::endl;

    hypro::VertexEnumeration<Number> initial = hypro::VertexEnumeration<Number>(poly.matrix(), poly.vector());

    // std::cout << "After pivot(1,4)" << std::endl;
    // std::size_t i = 0;
    // std::size_t j = 1;
    // initial.pivot(i,j);
    // std::cout << initial << std::endl;

    //std::cout << "after rearranging: " << std::endl;
    //initial.insertRowAfterPosition(2,1);

    /*
    std::cout << "Check reversed criss cross pivot (1,4): " << initial.isReverseCrissCrossPivot(1,4) << std::endl;

    if(initial.isReverseCrissCrossPivot(1,4)) {
    	initial.pivot(1,4);
    	std::cout << "After pivot(1,4)" << std::endl;
    	std::cout << initial << std::endl;

    	std::size_t i;
    	std::size_t j;

    	// verify reverse pivot
    	initial.selectCrissCrossPivot(i,j);

    	std::cout << "Selected CrissCross pivot: " << i << ", " << j << std::endl;
    }
	*/

    //std::cout << "#######################" << std::endl;
    //initial.search();


	std::vector<hypro::Point<Number>> res = initial.search();
	std::cout << "Result: " << std::endl;
	for(const auto& point : res )
		std::cout << point << ", ";

	std::cout << std::endl;
	hypro::Plotter<Number>& p = hypro::Plotter<Number>::getInstance();
	p.addObject(res);
	p.addObject(hypro::Hyperplane<Number>({1,3}, 4));
    p.addObject(hypro::Hyperplane<Number>({5,1}, 5));
    p.addObject(hypro::Hyperplane<Number>({3,2}, 2));
    p.addObject(hypro::Hyperplane<Number>({-1,-3}, 1));
    p.addObject(hypro::Hyperplane<Number>({-2,1}, 2));
	p.addPoints(res);
	p.plot2d();
	exit(0);
}
