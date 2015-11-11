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

    initial.print(true);
    std::size_t i,j,op;
    while(true) {
    	std::cout << "------------------------------------------------------" << std::endl;
    	std::cout << "Choose operation: \n\t [1] pivot\n\t [2] check reverse pivot\n\t [3] select pivot\n\t [4] print current dictionary\n\t [5] run whole algorithm \n\t [0] quit\nOperation: ";
    	std::cin >> op;
    	switch(op) {
    		case 1: {
    			std::cout << "Pivot row: ";
		    	std::cin >> i;
		    	std::cout << "Pivot col: ";
		    	std::cin >> j;
		    	initial.pivot(i,j);
		    	initial.print(true);
		    	break;
    		}
    		case 2: {
    			std::cout << "Pivot row: ";
		    	std::cin >> i;
		    	std::cout << "Pivot col: ";
		    	std::cin >> j;
		    	if(initial.isReverseCrissCrossPivot(i,j))
		    		std::cout << "True." << std::endl;
		    	else
		    		std::cout << "False." << std::endl;

		    	break;
    		}
    		case 3: {
    			std::cout << "Pivot row: ";
		    	std::cin >> i;
		    	std::cout << "Pivot col: ";
		    	std::cin >> j;
		    	initial.selectCrissCrossPivot(i,j);
		    	std::cout << "Selected pivot: " << i << ", " << j << std::endl;

		    	break;
    		}
    		case 4: {
    			initial.print(true);
    			break;
    		}
    		case 5: {
    			std::vector<hypro::Point<Number>> res = initial.search();
    			std::cout << "Result: " << std::endl;
    			for(const auto& point : res )
    				std::cout << point << ", ";

    			std::cout << std::endl;
    			exit(0);
    			break;
    		}
    		case 0: {
    			exit(0);
    		}
    		default:
    			break;
    	}


    }

}
