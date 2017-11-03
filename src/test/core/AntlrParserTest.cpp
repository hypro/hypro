#include "../../hypro/parser/antlr4-flowstar/ParserWrapper.h"
#include "../../hypro/datastructures/HybridAutomaton/HybridAutomaton.h"
#include <iostream>
#include <fstream>
#include "gtest/gtest.h"
#include "../defines.h"

#include <unistd.h>		//getcwd()

using namespace antlr4;

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


///////////// Unit Tests - Do subvisitors work properly? //////////////
/*
TYPED_TEST(AntlrParserTest, SettingVEmptySettings){

	//Create a parser for the empty settings string
	std::ifstream ifs("setting { }");
	ANTLRInputStream input(ifs);
	HybridAutomatonLexer lexer(&input);
	CommonTokenStream tokens(&lexer);
	tokens.fill();
	HybridAutomatonParser parser(&tokens);
	tree::ParseTree* tree = parser.setting();

	//Create a visitor
	std::vector<std::string> vars;
	std::vector<std::string>& varVec = vars;
	hypro::HyproSettingVisitor<TypeParam> visitor(varVec);
	hypro::ReachabilitySettings<TypeParam> r = visitor.visitSetting(tree).antlrcpp::Any::as<hypro::ReachabilitySettings<TypeParam>>();

	//Test
	EXPECT_EQ(r.timeBound, TypeParam(0));
	EXPECT_EQ(r.jumpDepth, (int)0);
	EXPECT_EQ(r.timeStep, TypeParam(0));
	EXPECT_EQ(r.fileName, "out");
	EXPECT_EQ(r.pplDenomimator, (unsigned long)0);
	EXPECT_TRUE(r.plotDimensions.size() == 0);
	EXPECT_FALSE(r.uniformBloating);
}
*/
TYPED_TEST(AntlrParserTest, JustTesting){

	//std::string path("../examples/input/bouncing_ball.model");
	std::string path("../../../../src/test/core/examples/test_bouncing_ball.txt");
	this->cwd();
	//std::string path("../src/test/core/examples/test_bouncing_ball.txt");
	try{
		boost::tuple<hypro::HybridAutomaton<TypeParam>, hypro::ReachabilitySettings<TypeParam>> h = hypro::parseFlowstarFile<TypeParam>(path);
	}catch (const std::runtime_error& e){
		std::cout << e.what() << std::endl;
		FAIL();
	}
	SUCCEED();
}

TYPED_TEST(AntlrParserTest, EmptyFile){

	this->cwd();
	std::string path("../src/test/core/examples/test_empty_file.txt");

	try{
		boost::tuple<hypro::HybridAutomaton<TypeParam>, hypro::ReachabilitySettings<TypeParam>> h = hypro::parseFlowstarFile<TypeParam>(path);
		FAIL();
	} catch(const std::runtime_error& e){
		std::cout << e.what() << std::endl;
		SUCCEED();
	}
}

TYPED_TEST(AntlrParserTest, OnlyStart){

	std::string path("../src/test/core/examples/test_only_start.txt");
	try{
		boost::tuple<hypro::HybridAutomaton<TypeParam>, hypro::ReachabilitySettings<TypeParam>> h = hypro::parseFlowstarFile<TypeParam>(path);
		FAIL();
	} catch(const std::runtime_error& e){
		std::cout << e.what() << std::endl;
		SUCCEED();
	}

}
