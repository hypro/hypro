/**
 *
 */

#include <string>
#include "../src/lib/parser/Parser.h"

int main(int argc, char** argv) {
    std::string filename = "../examples/input/simpleTest";
    
    hypro::parser::MainParser<double,hypro::valuation> parser;
    parser.parseInput(filename);
}