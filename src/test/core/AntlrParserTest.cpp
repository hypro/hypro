#include "../../hypro/parser/antlr4-flowstar/HybridAutomatonLexer.h"
#include "../../hypro/parser/antlr4-flowstar/HybridAutomatonParser.h"
#include "../../hypro/parser/antlr4-flowstar/HyproHAListener.h"
#include <iostream>
#include <fstream>
#include "gtest/gtest.h"
#include "../defines.h"
#include <antlr4-runtime.h>

#include <unistd.h>		//getcwd()

using namespace antlr4;
//using namespace hypro;

template<typename Number>
class AntlrParserTest : public ::testing::Test {

	protected:

		AntlrParserTest(){}

		~AntlrParserTest(){}

		virtual void setUp(){}

		virtual void tearDown(){}

		void cwd(){
			char cwd[1024];
		   	if (getcwd(cwd, sizeof(cwd)) != NULL)
		       fprintf(stdout, "Current working dir: %s\n", cwd);
		   	else
		       std::cerr << "getcwd() error" << std::endl;
		}
};

TYPED_TEST(AntlrParserTest, ParseLocation){

	//Open examples.txt
	this->cwd();

	std::fstream ifs("../../../../src/test/core/example_location_parsing.txt");
	//std::fstream ifs("../src/test/core/example.txt"); The path from ../hypro/build

	//Create an AnTLRInputStream
	ANTLRInputStream input;
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
		FAIL();
	}

	std::cout << "input stream content:\n" << input.toString() << std::endl;

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
