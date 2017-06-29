#include <iostream>
#include "gtest/gtest.h"
#include <antlr4-runtime.h>
#include "../../hypro/parser/antlr4-flowstar/FormulaLexer.h"
#include "../../hypro/parser/antlr4-flowstar/FormulaParser.h"
#include "../../hypro/parser/antlr4-flowstar/HyproHAListener.h"

using namespace antlr4;

TEST(AntlrParserTest, ParseFormulaEquation){
	
	//Create an AnTLRInputStream 
	ANTLRInputStream input("x = 4*y + 2");

	//Create a Lexer and feed it with the input
	FormulaLexer lexer(&input);

	//Create an empty TokenStream obj
	CommonTokenStream tokens(&lexer);

	//Fill the TokenStream (and output it for demonstration)
	tokens.fill();
	for(auto token : tokens.getTokens()){
		std::cout << token->toString() << std::endl;
	}

	//Create a parser
	FormulaParser parser(&tokens);

	//Generate a parse tree from the parser.
	//The function on the right side is the rule within the parser we want to start with.
	tree::ParseTree* tree = parser.equation();

	//Output the tree
	std::cout << tree->toStringTree(&parser) << std::endl;

	//Let's create a listener


	SUCCEED();

}