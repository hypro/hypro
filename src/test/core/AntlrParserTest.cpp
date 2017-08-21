#include "../../hypro/parser/antlr4-flowstar/HybridAutomatonLexer.h"
#include "../../hypro/parser/antlr4-flowstar/HybridAutomatonParser.h"
#include "../../hypro/parser/antlr4-flowstar/HyproHAVisitor.h"
#include "../../hypro/datastructures/HybridAutomaton/HybridAutomaton.h"
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

		//The one visitor to rule them all
		//hypro::HyproHAVisitor<Number> visitor;

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

		HybridAutomatonParser generateParser(std::string path){
			//Tell current path - /home/ptse/hiwi/hypro/build/src/test/core
			this->cwd();

			//std::fstream ifs("../../../../src/test/core/example_location_parsing.txt");
			std::fstream ifs(path);

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
				//FAIL();
			}
			if(!ifs.is_open()){
				std::cout << "ifs hasn't opened anything" << std::endl;
				//FAIL();
			}
			std::cout << "input stream content:\n" << input.toString() << std::endl;

			//Create a Lexer and feed it with the input
			HybridAutomatonLexer lexer(&input);

			//Create an empty TokenStream obj
			CommonTokenStream tokens(&lexer);

			//Fill the TokenStream (and output it for demonstration)
			tokens.fill();

			//Create a parser
			HybridAutomatonParser parser(&tokens);

			return parser;
		}
};

TYPED_TEST(AntlrParserTest, JustTesting){

	//std::string path("../../../../src/test/core/examples/example_init_parsing.txt");
	std::string path("../examples/input/bouncing_ball.model");

	//Tell current path - /home/ptse/hiwi/hypro/build/src/test/core
	this->cwd();

	//std::fstream ifs("../../../../src/test/core/example_location_parsing.txt");
	std::fstream ifs(path);

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
		//FAIL();
	}
	if(!ifs.is_open()){
		std::cout << "ifs hasn't opened anything" << std::endl;
		//FAIL();
	}
	std::cout << "input stream content:\n" << input.toString() << std::endl;

	//Create a Lexer and feed it with the input
	HybridAutomatonLexer lexer(&input);

	//Create an empty TokenStream obj
	CommonTokenStream tokens(&lexer);

	//Fill the TokenStream (and output it for demonstration)
	tokens.fill();

	//Create a parser
	HybridAutomatonParser parser(&tokens);

	tree::ParseTree* tree = parser.start();

	hypro::HyproHAVisitor<TypeParam> visitor;

	hypro::HybridAutomaton<TypeParam> h = (visitor.visit(tree)).antlrcpp::Any::as<hypro::HybridAutomaton<TypeParam>>();
	std::cout << "I RETURNED FROM VISITING" << std::endl;

	SUCCEED();

}

/*
TYPED_TEST(AntlrParserTest, EmptyFile){

	tree::ParseTree* tree = this->generateParseTree("../../../../src/test/core/examples/example_empty_file.txt");
	this->visitor.visit(tree);
	SUCCEED();

}
*/
