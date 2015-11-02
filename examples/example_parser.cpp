/**
 *
 */

#include <string>
#include "../src/lib/config.h"
#include "../src/lib/representations/Polytope/Polytope.h"
#include "../src/lib/parser/Parser.h"
#include <mpfr.h>

int main(int argc, char** argv) {
	typedef double number;
	typedef hypro::Polytope<number> valuation;

    std::string filename = "../examples/input/simpleTest";

    hypro::parser::MainParser<number,valuation> parser;
    parser.parseInput(filename);
}