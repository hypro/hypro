#include "../../hypro/parser/antlr4-cif/HybridCIFVisitor.h"
#include "../../hypro/parser/antlr4-cif/HybridSystemLexer.h"
#include "../../hypro/parser/antlr4-cif/HybridSystemParser.h"
#include "../defines.h"
#include "gtest/gtest.h"
#include <antlr4-runtime.h>
#include <fstream>
#include <iostream>

#include <unistd.h>	 //getcwd()

using namespace antlr4;
// using namespace hypro;

template <typename Number>
class AntlrParserCIFTest : public ::testing::Test {
  protected:
	AntlrParserCIFTest() {}

	~AntlrParserCIFTest() {}

	virtual void setUp() {}

	virtual void tearDown() {}

	void cwd() {
		char cwd[1024];
		if ( getcwd( cwd, sizeof( cwd ) ) != NULL )
			fprintf( stdout, "Current working dir: %s\n", cwd );
		else
			std::cerr << "getcwd() error" << std::endl;
	}
};

TYPED_TEST( AntlrParserCIFTest, ParseVariables ) {
	// Open examples.txt
	this->cwd();

	std::fstream ifs( "../src/test/core/ciftestautomat.txt" );

	// Create an AnTLRInputStream
	ANTLRInputStream input;
	input = ANTLRInputStream( ifs );

	/*	if(ifs.good()){
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
	*/

	// Create a Lexer and feed it with the input
	HybridSystemLexer lexer( &input );

	// Create an empty TokenStream obj
	CommonTokenStream tokens( &lexer );

	// Create a parser
	HybridSystemParser parser( &tokens );

	// Generate a parse tree from the parser.
	// The function on the right side is the rule within the parser we want to start with.
	tree::ParseTree* tree = parser.specification();

	// Let's create a visitor
	hypro::HybridCIFVisitor<TypeParam> visitor;
	visitor.visit( tree );

	// std::cout << visitor << std::endl;

	SUCCEED();
}
