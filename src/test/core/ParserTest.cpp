#include "datastructures/HybridAutomaton/HybridAutomaton.h"
#include "datastructures/reachability/Settings.h"
#include "parser/antlr4-flowstar/ParserWrapper.h"
#include "gtest/gtest.h"
#include <fstream>

TEST( ParserTest, ParseAutomaton ) {
	using namespace hypro;

	// create model-file.

	std::ofstream file( "/tmp/automaton.model" );

#include "models/automaton.h"
	file << autString;
	file.close();

	// test content

	std::string filename = "/tmp/automaton.model";
	std::pair<HybridAutomaton<mpq_class>, ReachabilitySettings> parseResult = parseFlowstarFile<mpq_class>( filename );

	ReachabilitySettings settings = parseResult.second;
	HybridAutomaton<mpq_class> automaton = parseResult.first;

	EXPECT_EQ( unsigned( 3 ), automaton.getLocations().size() );
	EXPECT_EQ( unsigned( 3 ), automaton.getTransitions().size() );
}

TEST( ParserTest, ParseAutomaton_2 ) {
	using namespace hypro;

	// create model-file.

	std::ofstream file( "/tmp/automaton_2.model" );

#include "models/automaton_2.h"
	file << autString;
	file.close();

	// test content

	std::string filename = "/tmp/automaton_2.model";
	std::pair<HybridAutomaton<mpq_class>, ReachabilitySettings> parseResult = parseFlowstarFile<mpq_class>( filename );

	ReachabilitySettings settings = parseResult.second;
	HybridAutomaton<mpq_class> automaton = parseResult.first;

	EXPECT_EQ( unsigned( 2 ), automaton.getLocations().size() );
	EXPECT_EQ( unsigned( 3 ), automaton.getTransitions().size() );
}
