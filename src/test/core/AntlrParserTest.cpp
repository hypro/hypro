#include "../../hypro/parser/antlr4-flowstar/HybridAutomatonLexer.h"
#include "../../hypro/parser/antlr4-flowstar/HybridAutomatonParser.h"
#include "../../hypro/parser/antlr4-flowstar/HyproHAListener.h"
#include <iostream>
#include <fstream>
#include "gtest/gtest.h"
#include "../defines.h"
#include <antlr4-runtime.h>

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


	ANTLRInputStream input;
	//std::string path = "example.txt";
	std::string path = "../../src/test/core/blub.txt"; 
	//std::string path = "../../../../../../src/test/core/example.txt"; 
	//std::ifstream ifs(path);

	std::fstream ifs(path);
	//ifs.open(path);
	//ifs.open("../../hypro/parser/antlr4-flowstar/example.txt", std::ifstream::in);

	//Create an AnTLRInputStream 
	// TODO: STILL DOES NOT WORK
	if(ifs.good()){
		input = ANTLRInputStream(ifs);									
	} else {
		std::cerr << "InputStream was bad." << std::endl;
		if(ifs.fail()){
			std::cerr << "Failbit was set" << std::endl;
		}
		if(ifs.eof()){
			std::cerr << "EOFbit was set" << std::endl;
		}
		if(ifs.bad()){
			std::cerr << "Badbit was set" << std::endl;
		}
		FAIL();
	}
	
	if(!ifs.is_open()){
		std::cout << "ifs hasn't opened anything" << std::endl;
		//std::cout << "path is: " << path << std::endl;
		FAIL();
	}
	
	std::cout << "input stream content: " << input.toString() << std::endl;

	//ANTLRInputStream input("hybrid reachability { state var x,c1,c2 modes { rod1 { poly ode 1 { x' = 4 c1' = 34*23 c2' = 18 } inv { x >= 510 } } } }");
	//2*x + -56*y + 

	//Create a Lexer and feed it with the input
	HybridAutomatonLexer lexer(&input);

	//Create an empty TokenStream obj
	CommonTokenStream tokens(&lexer);

	//Fill the TokenStream (and output it for demonstration)
	tokens.fill();
	//for(auto token : tokens.getTokens()){
	//	std::cout << token->toString() << std::endl;
	//}

	//Create a parser
	HybridAutomatonParser parser(&tokens);

	//Generate a parse tree from the parser.
	//The function on the right side is the rule within the parser we want to start with.
	tree::ParseTree* tree = parser.start();

	//Output the tree
	//std::cout << tree->toStringTree(&parser) << std::endl;

	//Let's create a listener
	hypro::HyproHAListener<TypeParam> listener; //= HyproHAListener::HyproHAListener<TypeParam>();

	tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);

	std::cout << listener << std::endl;

	SUCCEED();

}