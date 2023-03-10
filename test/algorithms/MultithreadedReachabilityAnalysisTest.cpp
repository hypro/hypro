/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "test/defines.h"

#include "gtest/gtest.h"
#include <hypro/algorithms/reachability/Reach.h>
#include <hypro/datastructures/HybridAutomaton/HybridAutomaton.h>
#include <hypro/datastructures/reachability/ReachTreev2Util.h>
#include <hypro/parser/antlr4-flowstar/ParserWrapper.h>

TEST( MultithreadedReachabilityAnalysisTest, BouncingBallNoAggregation ) {
	using Number = double;
	using Representation = hypro::Box<Number>;
	using Automaton = hypro::HybridAutomaton<Number>;

	auto [automaton, reachSettings] = hypro::parseFlowstarFile<Number>( hypro::getTestModelsPath() + "parser/bouncing_ball.model" );

	auto roots = hypro::makeRoots<Representation, Automaton>( automaton );

	// settings: jump depth 10, local time horizon 5, delta 0.001, aggregation, clustering 2
	hypro::FixedAnalysisParameters fixedSettings{ 5, 5, 0.001 };
	hypro::AnalysisParameters dynamicSettings{ 0.001, hypro::AGG_SETTING::AGG, 2 };

	auto reacher = hypro::reachability::Reach<Representation, Automaton, hypro::DepthFirst<Representation, typename Automaton::LocationType>, hypro::UseMultithreading>( automaton, fixedSettings, dynamicSettings, roots );

	auto result = reacher.computeForwardReachability();

	std::cout << "Have computed " << hypro::getNumberNodes( roots ) << " nodes." << std::endl;

	SUCCEED();
}
