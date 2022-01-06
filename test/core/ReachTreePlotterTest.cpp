/*
 * Copyright (c) 2021.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of
 * the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
 * THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "gtest/gtest.h"
#include <hypro/algorithms/reachability/Reach.h>
#include <hypro/parser/antlr4-flowstar/ParserWrapper.h>
#include <hypro/paths.h>
#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/types.h>
#include <hypro/util/plotting/ReachTreePlotter.h>

#ifdef HYPRO_HAS_GRAPHVIZ

using namespace hypro;
using Representation = Box<double>;

std::vector<ReachTreeNode<Representation>> create_tree( const HybridAutomaton<double>& automaton ) {
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
	auto emptyPlotter = plotting::ReachTreePlotter<Representation>( roots );

	// non-empty plotter
	auto [automaton, _] = parseFlowstarFile<double>( getTestModelsPath() + "parser/bouncing_ball.model" );
	auto bball_roots = create_tree( automaton );
	auto bball_tree_plotter = plotting::ReachTreePlotter<Representation>( bball_roots );
}

TEST( ReachTreePlotterTest, PlotSimpleTree ) {
	auto [automaton, _] = parseFlowstarFile<double>( getTestModelsPath() + "parser/bouncing_ball.model" );

	auto bball_roots = create_tree( automaton );
	EXPECT_EQ( 4, getNumberNodes( bball_roots.front() ) );
	auto bball_tree_plotter = plotting::ReachTreePlotter<Representation>( bball_roots );

	bball_tree_plotter.plot( { bball_roots.front().getChildren()[0] } );

	// std::system( "cat rt_out.dot" );
}

#endif