#include "gtest/gtest.h"
#include "parser/antlr4-flowstar/ParserWrapper.h"
#include "datastructures/HybridAutomaton/HybridAutomaton.h"
#include "datastructures/reachability/Settings.h"
#include <fstream>

TEST(ParserTest, ParseAutomaton)
{
	using namespace hypro;

	// create model-file.

	std::ofstream file("/tmp/automaton.model");

	#include "models/automaton.h"
	file << autString;
	file.close();

	// test content

	std::string filename = "/tmp/automaton.model";
	std::pair<HybridAutomaton<mpq_class>, ReachabilitySettings> parseResult = parseFlowstarFile<mpq_class>(filename);

	ReachabilitySettings settings = parseResult.second;
	HybridAutomaton<mpq_class> automaton = parseResult.first;

	EXPECT_EQ(automaton.getLocations().size(), unsigned(2));
	EXPECT_EQ(automaton.getTransitions().size(), unsigned(3));
}
