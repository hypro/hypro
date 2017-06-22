#include <iostream>
#include "gtest/gtest.h"
#include <antlr4-runtime.h>
#include "../../hypro/parser/antlr4-flowstar/FormulaLexer.h"
#include "../../hypro/parser/antlr4-flowstar/FormulaParser.h"

TEST(AntlrParserTest, OutputSmth){
	std::cout << "yeah it worked!" << std::endl;
}