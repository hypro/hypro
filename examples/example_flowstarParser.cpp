/**
 *
 */

#include <string>
#include "../src/lib/config.h"
#include "../src/lib/representations/GeometricObject.h"
#include "../src/lib/parser/flowstar/flowstarParser.h"

int main(int argc, char** argv) {
	typedef double number;
	typedef hypro::HPolytope<number> valuation;

    std::string filename = "../examples/input/test.model";

    hypro::parser::flowstarParser<number,valuation> parser;
    parser.parseInput(filename);
    parser.printModes();
}