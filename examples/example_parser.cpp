/**
 *
 */

#include <string>
#include "../src/lib/parser/Parser.h"
#include "../src/lib/config.h"
#include <mpfr.h>

int main(int argc, char** argv) {
    std::string filename = "../examples/input/simpleTest";
    
    hypro::parser::MainParser<number,hypro::valuation> parser;
    parser.parseInput(filename);
}