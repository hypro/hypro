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

TEST( MultithreadedReachabilityAnalysisTest, LTIBouncingBallNoAggregation ) {
	using Number = double;
	using Representation = hypro::Box<Number>;
	using Automaton = hypro::HybridAutomaton<Number>;

	auto [automaton, reachSettings] = hypro::parseFlowstarFile<Number>( hypro::getTestModelsPath() + "parser/bouncing_ball.model" );

	// settings: jump depth 3, local time horizon 5, delta 0.01, no aggregation, clustering 2
	hypro::FixedAnalysisParameters fixedSettings{ 2, 5, 0.01 };
	hypro::AnalysisParameters dynamicSettings{ 0.01, hypro::AGG_SETTING::NO_AGG, 2 };

	auto roots_mt = hypro::makeRoots<Representation, Automaton>( automaton );
	auto reacher_mt = hypro::reachability::Reach<Representation, Automaton, hypro::DepthFirst<Representation, typename Automaton::LocationType>, hypro::UseMultithreading>( automaton, fixedSettings, dynamicSettings, roots_mt );
	auto result_mt = reacher_mt.computeForwardReachability();

	auto roots_st = hypro::makeRoots<Representation, Automaton>( automaton );
	auto reacher_st = hypro::reachability::Reach<Representation, Automaton, hypro::DepthFirst<Representation, typename Automaton::LocationType>, hypro::NoMultithreading>( automaton, fixedSettings, dynamicSettings, roots_st );
	auto result_st = reacher_st.computeForwardReachability();

	EXPECT_EQ( result_mt, result_st );
	EXPECT_EQ( hypro::getNumberNodes( roots_mt ), hypro::getNumberNodes( roots_st ) );
}
