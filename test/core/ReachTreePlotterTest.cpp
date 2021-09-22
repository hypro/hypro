#include "gtest/gtest.h"
#include <hypro/algorithms/reachability/Reach.h>
#include <hypro/parser/antlr4-flowstar/ParserWrapper.h>
#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/types.h>
#include <hypro/util/plotting/ReachTreePlotter.h>

using namespace hypro;
using Representation = Box<double>;

std::vector<ReachTreeNode<Representation>> create_tree() {
	std::ofstream file( "/tmp/bball_automaton.model" );

#include "models/bball_automaton.h"
	file << autString;
	file.close();

	// test content

	std::string filename = "/tmp/bball_automaton.model";

	auto [automaton, _] = parseFlowstarFile<double>( filename );

	// set up reach tree
	std::vector<ReachTreeNode<Representation>> roots = hypro::makeRoots<Representation>( automaton );

	using tNumber = hypro::tNumber;
	hypro::FixedAnalysisParameters fixedParameters;
	fixedParameters.jumpDepth = 3;
	fixedParameters.localTimeHorizon = 5;
	fixedParameters.fixedTimeStep = tNumber( 1 ) / tNumber( 100 );

	hypro::AnalysisParameters analysisParameters;
	analysisParameters.timeStep = tNumber( 1 ) / tNumber( 100 );
	analysisParameters.aggregation = hypro::AGG_SETTING::AGG;
	analysisParameters.representation_type = hypro::representation_name::box;

	hypro::Settings settings{ {}, fixedParameters, { analysisParameters } };

	auto reacher = reachability::Reach<Representation>( automaton, settings.fixedParameters(),
														settings.strategy().front(), roots );

	// run reacher. Return type explicit to be able to monitor changes
	reacher.computeForwardReachability();
	return roots;
}

TEST( ReachTreePlotterTest, Construction ) {
	// empty plotter
	std::vector<ReachTreeNode<Representation>> roots;
	auto emptyPlotter = plotting::ReachTreePlotter<Representation>( roots, {} );

	// non-empty plotter
	auto bball_roots = create_tree();
	auto bball_tree_plotter = plotting::ReachTreePlotter<Representation>( bball_roots, {} );
}

TEST( ReachTreePlotterTest, PlotSimpleTree ) {
	auto bball_roots = create_tree();
	EXPECT_EQ( 4, getNumberNodes( bball_roots.front() ) );
	auto bball_tree_plotter = plotting::ReachTreePlotter<Representation>( bball_roots, {} );

	bball_tree_plotter.plot();
}
