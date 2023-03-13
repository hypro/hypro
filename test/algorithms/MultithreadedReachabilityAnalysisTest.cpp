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
#include <hypro/algorithms/reachability/analyzer/RectangularAnalyzer.h>
#include <hypro/datastructures/HybridAutomaton/HybridAutomaton.h>
#include <hypro/datastructures/reachability/ReachTreev2Util.h>
#include <hypro/parser/antlr4-flowstar/ParserWrapper.h>

template <typename Number>
hypro::HybridAutomaton<Number> createRectangularHA3() {
	// Two-dimensional HA with two locations
	using Matrix = hypro::matrix_t<Number>;
	using Vector = hypro::vector_t<Number>;
	using Interval = carl::Interval<Number>;

	hypro::HybridAutomaton<Number> res;

	// Create locations
	hypro::Location<Number>* loc0 = res.createLocation();
	hypro::Location<Number>* loc1 = res.createLocation();
	loc0->setName( "l0" );
	loc1->setName( "l1" );

	// Set flow x' = 1, y' = -1 in loc0
	Interval flowx{ 1, 1 };
	Interval flowy{ -1, -1 };
	typename hypro::rectangularFlow<Number>::flowMap fMap;
	fMap[hypro::VariablePool::getInstance().carlVarByIndex( 0 )] = flowx;
	fMap[hypro::VariablePool::getInstance().carlVarByIndex( 1 )] = flowy;
	loc0->setFlow( { hypro::rectangularFlow<Number>{ fMap } } );

	// Set flow x' = 0, y' = -1 in loc1
	flowx = Interval{ 0, 0 };
	flowy = Interval{ -1, -1 };
	fMap[hypro::VariablePool::getInstance().carlVarByIndex( 0 )] = flowx;
	fMap[hypro::VariablePool::getInstance().carlVarByIndex( 1 )] = flowy;
	loc1->setFlow( { hypro::rectangularFlow<Number>{ fMap } } );

	// Set invariant x <= 3 in loc0 and loc1
	Matrix invariantConstraints = Matrix::Zero( 1, 2 );
	invariantConstraints( 0, 0 ) = 1;
	Vector invariantConstants = 3 * Vector::Ones( 1 );
	loc0->setInvariant( { invariantConstraints, invariantConstants } );
	loc1->setInvariant( { invariantConstraints, invariantConstants } );

	// Construct transitions
	// l0 -> l0 with guard x >= 1 and reset x := 0, y := 0
	Matrix transConstraint = Matrix::Zero( 1, 2 );
	Vector transConstants = -1 * Vector::Ones( 1 );
	transConstraint( 0, 0 ) = -1;
	hypro::Condition<Number> guard( transConstraint, transConstants );
	hypro::Reset<Number> reset{ { carl::Interval<Number>{ 0, 0 }, carl::Interval<Number>{ 0, 0 } } };

	auto* trans0 = loc0->createTransition( loc0 );
	trans0->setGuard( guard );
	trans0->setReset( reset );

	// l0 -> l1 with guard y <= -2 and no reset
	transConstraint = Matrix::Zero( 1, 2 );
	transConstants = -2 * Vector::Ones( 1 );
	transConstraint( 0, 1 ) = 1;
	guard = hypro::Condition<Number>( transConstraint, transConstants );
	reset = hypro::Reset<Number>( { carl::Interval<Number>(), carl::Interval<Number>() } );

	auto* trans1 = loc0->createTransition( loc1 );
	trans1->setGuard( guard );
	trans1->setReset( reset );

	// Set initial state x = 0, y = 0, aff = 1
	Matrix initialConstraints = Matrix::Zero( 4, 2 );
	Vector initialConstants = Vector::Zero( 4 );
	initialConstraints << 1, 0, -1, 0, 0, 1, 0, -1;
	initialConstants << 0, 0, 0, 0;

	// Add initial configuration
	res.addInitialState( loc0, hypro::Condition<Number>( initialConstraints, initialConstants ) );

	return res;
}

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

TEST( MultithreadedReachabilityAnalysisTest, Rectangular ) {
	using Number = mpq_class;
	using Representation = hypro::HPolytope<Number>;
	using Automaton = hypro::HybridAutomaton<Number>;

	auto automaton = createRectangularHA3<Number>();

	hypro::AnalysisParameters analysisParameters;
	analysisParameters.timeStep = hypro::tNumber( 1 ) / hypro::tNumber( 100 );
	analysisParameters.aggregation = hypro::AGG_SETTING::AGG;
	analysisParameters.representation_type = hypro::representation_name::polytope_v;

	hypro::Settings settings{ {},
							  hypro::FixedAnalysisParameters{ 5, hypro::tNumber( 4 ), hypro::tNumber( 0.01 ) },
							  { analysisParameters } };

	auto roots_mt = hypro::makeRoots<Representation, Automaton>( automaton );
	EXPECT_EQ( std::size_t( 1 ), roots_mt.size() );
	auto reach_mt = hypro::reachability::ReachBase<Representation, decltype( automaton ), hypro::RectangularAnalyzer<Representation, decltype( automaton ), hypro::UseMultithreading>>( automaton, settings,
																																														roots_mt );

	// call verifier, validate result
	auto reachabilityResult_mt = reach_mt.computeForwardReachability();
	EXPECT_EQ( hypro::REACHABILITY_RESULT::SAFE, reachabilityResult_mt );

	auto roots_st = hypro::makeRoots<Representation, Automaton>( automaton );
	auto reach_st = hypro::reachability::ReachBase<Representation, decltype( automaton ), hypro::RectangularAnalyzer<Representation, decltype( automaton ), hypro::NoMultithreading>>( automaton, settings,
																																													   roots_st );

	// call verifier, validate result
	auto reachabilityResult_st = reach_st.computeForwardReachability();
	EXPECT_EQ( hypro::REACHABILITY_RESULT::SAFE, reachabilityResult_st );

	EXPECT_EQ( reachabilityResult_mt, reachabilityResult_st );
	EXPECT_EQ( hypro::getNumberNodes( roots_mt ), hypro::getNumberNodes( roots_st ) );
}
