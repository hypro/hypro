/**
 *
 */

#include <string>
#include "../src/lib/parser/Parser.h"
#include <mpfr.h>

int main(int argc, char** argv) {
    std::string filename = "../examples/input/simpleTest";
    
    hypro::parser::MainParser<carl::FLOAT_T<mpfr_t>,hypro::valuation> parser;
    parser.parseInput(filename);
}