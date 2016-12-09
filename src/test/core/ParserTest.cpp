#include "gtest/gtest.h"
#include "parser/flowstar/ParserWrapper.h"
#include "datastructures/hybridAutomata/HybridAutomaton.h"
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
	boost::tuple<HybridAutomaton<mpq_class>, reachability::ReachabilitySettings<mpq_class>> parseResult = parseFlowstarFile<mpq_class>(filename);

	reachability::ReachabilitySettings<mpq_class> settings = boost::get<1>(parseResult);
	HybridAutomaton<mpq_class> automaton = boost::get<0>(parseResult);

	EXPECT_EQ(automaton.locations().size(), unsigned(2));
	EXPECT_EQ(automaton.transitions().size(), unsigned(3));
}
