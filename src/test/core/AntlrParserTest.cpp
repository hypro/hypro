#include <iostream>
#include <fstream>
#include "gtest/gtest.h"
#include <antlr4-runtime.h>
#include "../defines.h"
#include "../../hypro/parser/antlr4-flowstar/HybridAutomatonLexer.h"
#include "../../hypro/parser/antlr4-flowstar/HybridAutomatonParser.h"
#include "../../hypro/parser/antlr4-flowstar/HyproHAListener.h"

using namespace antlr4;
//using namespace hypro;

template<typename Number>
class AntlrParserTest : public ::testing::Test {

	protected:		

		AntlrParserTest(){}

		~AntlrParserTest(){}

		virtual void setUp(){}

		virtual void tearDown(){}
};

TYPED_TEST(AntlrParserTest, ParseLocation){
	
	//Open examples.txt 
	//TODO: THIS DOES NOT WORK FIX IT BOYE
	std::ifstream ifs;											//
	ifs.seekg(0, ifs.end);										//
	int length = ifs.tellg();									//
	ifs.seekg(0, ifs.beg);										//
	char* buffer = new char[length];							//
	ifs.open("../../hypro/parser/antlr4-flowstar/example.txt");	//
	ifs.read(buffer, length);									//
	ifs.close();												//
	std::cout << "WE DID IT!" << std::endl;						//
	//Create an AnTLRInputStream 
	ANTLRInputStream input(ifs);								//
	delete buffer;												//

	//Create a Lexer and feed it with the input
	HybridAutomatonLexer lexer(&input);

	//Create an empty TokenStream obj
	CommonTokenStream tokens(&lexer);

	//Fill the TokenStream (and output it for demonstration)
	tokens.fill();
	for(auto token : tokens.getTokens()){
		std::cout << token->toString() << std::endl;
	}

	//Create a parser
	HybridAutomatonParser parser(&tokens);

	//Generate a parse tree from the parser.
	//The function on the right side is the rule within the parser we want to start with.
	tree::ParseTree* tree = parser.equation();

	//Output the tree
	std::cout << tree->toStringTree(&parser) << std::endl;

	//Let's create a listener
	hypro::HyproHAListener<TypeParam> listener; //= HyproHAListener::HyproHAListener<TypeParam>();

	tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);

	std::cout << listener << std::endl;

	SUCCEED();

}