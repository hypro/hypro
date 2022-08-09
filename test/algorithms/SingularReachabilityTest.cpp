/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "test/algorithms/automata/automataCreation.h"
#include "test/defines.h"

#include "gtest/gtest.h"
#include <carl/interval/Interval.h>
#include <hypro/algorithms/reachability/Reach.h>
#include <hypro/algorithms/reachability/analyzer/SingularAnalyzer.h>
#include <hypro/algorithms/reachability/workers/SingularWorker.h>
#include <hypro/datastructures/HybridAutomaton/Condition.h>
#include <hypro/datastructures/HybridAutomaton/HybridAutomaton.h>
#include <hypro/datastructures/HybridAutomaton/Location.h>
#include <hypro/datastructures/HybridAutomaton/Transition.h>
#include <hypro/datastructures/reachability/ReachTreev2Util.h>
#include <hypro/datastructures/reachability/Settings.h>
#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/types.h>
#include <hypro/util/VariablePool.h>
#include <hypro/util/plotting/Plotter.h>

using Number = mpq_class;
using VPoly = hypro::VPolytope<Number>;
using Matrix = hypro::matrix_t<Number>;
using Vector = hypro::vector_t<Number>;
using Point = hypro::Point<Number>;

template <typename Number>
hypro::HybridAutomaton<Number> createBouncingBall() {
	using Matrix = hypro::matrix_t<Number>;
	using Vector = hypro::vector_t<Number>;

	hypro::HybridAutomaton<Number> res;

	hypro::Location<Number> loc;
	loc.setName( "l0" );

	Matrix invariantConstraints = Matrix::Zero( 1, 3 );
	invariantConstraints( 1, 1 ) = Number( -1 );
	Vector invariantConstants = Vector::Zero( 1 );
	loc.setInvariant( { invariantConstraints, invariantConstants } );

	res.addLocation( std::make_unique<hypro::Location<Number>>( loc ) );

	return hypro::HybridAutomaton<Number>{};
}

template <typename Number>
hypro::HybridAutomaton<Number> createSingularHA() {
	// One-dimensional HA with one location
	using Matrix = hypro::matrix_t<Number>;
	using Vector = hypro::vector_t<Number>;

	hypro::HybridAutomaton<Number> res;

	// Create location
	hypro::Location<Number> loc;

	// Set flow x' = 1
	Matrix flow = Matrix::Zero( 2, 2 );
	flow( 0, 1 ) = 1;
	loc.setFlow( flow );

	// Set invariant x <= 1
	Matrix invariantConstraints = Matrix::Zero( 1, 1 );
	invariantConstraints( 0, 0 ) = 1;
	Vector invariantConstants = Vector::Ones( 1 );
	loc.setInvariant( { invariantConstraints, invariantConstants } );

	// Set initial state x = 0, aff = 1
	Matrix initialConstraints = Matrix::Zero( 2, 1 );
	Vector initialConstants = Vector::Zero( 2 );
	initialConstraints << 1, -1;
	initialConstants << 0, 0;

	// Create HA
	auto& locPtr = res.addLocation( std::make_unique<hypro::Location<Number>>( loc ) );
	res.addInitialState( locPtr.get(), hypro::Condition<Number>( initialConstraints, initialConstants ) );

	return res;
}

template <typename Number>
hypro::HybridAutomaton<Number> createSingularHA2() {
	// Two-dimensional HA with one location
	using Matrix = hypro::matrix_t<Number>;
	using Vector = hypro::vector_t<Number>;

	hypro::HybridAutomaton<Number> res;

	// Create location
	hypro::Location<Number> loc;

	// Set flow x' = 1, y' = -1
	Matrix flow = Matrix::Zero( 3, 3 );
	flow( 0, 2 ) = 1;
	flow( 1, 2 ) = -1;
	loc.setFlow( flow );

	// Set invariant x <= 3
	Matrix invariantConstraints = Matrix::Zero( 1, 2 );
	invariantConstraints( 0, 0 ) = 1;
	Vector invariantConstants = 3 * Vector::Ones( 1 );
	loc.setInvariant( { invariantConstraints, invariantConstants } );

	// Set initial state x = 0, y = 1, aff = 1
	Matrix initialConstraints = Matrix::Zero( 4, 2 );
	Vector initialConstants = Vector::Zero( 4 );
	initialConstraints << 1, 0, -1, 0, 0, 1, 0, -1;
	initialConstants << 0, 0, 1, -1;

	// Create HA
	auto& locPtr = res.addLocation( std::make_unique<hypro::Location<Number>>( loc ) );
	res.addInitialState( locPtr.get(), hypro::Condition<Number>( initialConstraints, initialConstants ) );

	return res;
}

template <typename Number>
hypro::HybridAutomaton<Number> createSingularHA3() {
	// Two-dimensional HA with two locations
	using Matrix = hypro::matrix_t<Number>;
	using Vector = hypro::vector_t<Number>;

	hypro::HybridAutomaton<Number> res;

	// Create locations
	hypro::Location<Number> loc0{};
	hypro::Location<Number> loc1{};
	auto uniqueLoc0{ std::make_unique<hypro::Location<Number>>( loc0 ) };
	auto uniqueLoc1{ std::make_unique<hypro::Location<Number>>( loc1 ) };
	uniqueLoc0->setName( "l0" );
	uniqueLoc1->setName( "l1" );

	// Set flow x' = 1, y' = -1 in loc0
	Matrix flow0 = Matrix::Zero( 3, 3 );
	flow0( 0, 2 ) = 1;
	flow0( 1, 2 ) = -1;
	uniqueLoc0->setFlow( flow0 );

	// Set flow x' = 0, y' = 1 in loc1
	Matrix flow1 = Matrix::Zero( 3, 3 );
	flow1( 1, 2 ) = 1;
	uniqueLoc1->setFlow( flow1 );

	// Set invariant x <= 3 in loc0 and loc1
	Matrix invariantConstraints = Matrix::Zero( 1, 2 );
	invariantConstraints( 0, 0 ) = 1;
	Vector invariantConstants = 3 * Vector::Ones( 1 );
	uniqueLoc0->setInvariant( { invariantConstraints, invariantConstants } );
	uniqueLoc1->setInvariant( { invariantConstraints, invariantConstants } );

	// Construct transitions
	// l0 -> l0 with guard x >= 1 and reset x := 0, y := 0
	Matrix transConstraint = Matrix::Zero( 1, 2 );
	Vector transConstants = -1 * Vector::Ones( 1 );
	transConstraint( 0, 0 ) = -1;
	hypro::Condition<Number> guard( transConstraint, transConstants );
	hypro::Reset<Number> reset{ { carl::Interval<Number>{ 0, 0 }, carl::Interval<Number>{ 0, 0 } } };

	std::unique_ptr<hypro::Transition<Number, typename hypro::HybridAutomaton<Number>::LocationType>> trans0 =
		  std::make_unique<hypro::Transition<Number, typename hypro::HybridAutomaton<Number>::LocationType>>( uniqueLoc0.get(), uniqueLoc0.get(), guard, reset );

	// l0 -> l1 with guard y <= -2 and no reset
	transConstraint = Matrix::Zero( 1, 2 );
	transConstants = -2 * Vector::Ones( 1 );
	transConstraint( 0, 1 ) = 1;
	guard = hypro::Condition<Number>( transConstraint, transConstants );
	reset = hypro::Reset<Number>( { carl::Interval<Number>(), carl::Interval<Number>() } );

	std::unique_ptr<hypro::Transition<Number, typename hypro::HybridAutomaton<Number>::LocationType>> trans1 =
		  std::make_unique<hypro::Transition<Number, typename hypro::HybridAutomaton<Number>::LocationType>>( uniqueLoc0.get(), uniqueLoc1.get(), guard, reset );

	// Set initial state x = 0, y = 0, aff = 1
	Matrix initialConstraints = Matrix::Zero( 4, 2 );
	Vector initialConstants = Vector::Zero( 4 );
	initialConstraints << 1, 0, -1, 0, 0, 1, 0, -1;
	initialConstants << 0, 0, 0, 0;

	// Create HA
	uniqueLoc0->addTransition( std::move( trans0 ) );
	uniqueLoc0->addTransition( std::move( trans1 ) );

	res.addLocation( std::move( uniqueLoc0 ) );
	res.addLocation( std::move( uniqueLoc1 ) );

	hypro::Location<Number>* loc0ptr = res.getLocation( "l0" );
	res.addInitialState( loc0ptr, hypro::Condition<Number>( initialConstraints, initialConstants ) );

	return res;
}

template <typename Number>
hypro::HybridAutomaton<Number> createSingularHA4() {
	// Automaton with multiple transitions enabled simultaneously
	using Matrix = hypro::matrix_t<Number>;
	using Vector = hypro::vector_t<Number>;

	hypro::HybridAutomaton<Number> res;

	// Create location
	std::unique_ptr<hypro::Location<Number>> loc = std::make_unique<hypro::Location<Number>>();

	// Flow
	Matrix flow = Matrix::Zero( 2, 2 );
	loc->setFlow( flow );

	// Invariant
	hypro::Condition<Number> invariant( Matrix::Zero( 1, 1 ), Vector::Zero( 1 ) );
	loc->setInvariant( invariant );

	// Transition
	Matrix transConstraint = Matrix::Ones( 1, 1 );
	Vector transConstants = Vector::Zero( 1 );
	hypro::Condition<Number> guard( transConstraint, transConstants );
	hypro::Reset<Number> reset{ { carl::Interval<Number>{ 1, 1 } } };

	std::unique_ptr<hypro::Transition<Number, typename hypro::HybridAutomaton<Number>::LocationType>> trans0 =
		  std::make_unique<hypro::Transition<Number, typename hypro::HybridAutomaton<Number>::LocationType>>( loc.get(), loc.get(), guard, reset );

	reset = hypro::Reset<Number>{ { carl::Interval<Number>{ -1, -1 } } };
	std::unique_ptr<hypro::Transition<Number, typename hypro::HybridAutomaton<Number>::LocationType>> trans1 =
		  std::make_unique<hypro::Transition<Number, typename hypro::HybridAutomaton<Number>::LocationType>>( loc.get(), loc.get(), guard, reset );

	loc->addTransition( std::move( trans0 ) );
	loc->addTransition( std::move( trans1 ) );

	Matrix initialConstraints = Matrix::Zero( 2, 1 );
	Vector initialConstants = Vector::Zero( 2 );
	initialConstraints << 1, -1;
	initialConstants << 0, 0;

	auto& locPtr = res.addLocation( std::move( loc ) );
	res.addInitialState( locPtr.get(), hypro::Condition<Number>( initialConstraints, initialConstants ) );

	return res;
}

TEST( SingularRechabilityTest, WorkerConstruction ) {
	using Number = mpq_class;
	using VPoly = hypro::VPolytope<Number>;

	auto automaton = createSingularHA<Number>();

	auto worker = hypro::SingularWorker<VPoly, hypro::HybridAutomaton<Number>>( automaton, hypro::FixedAnalysisParameters{ 1, hypro::tNumber( 10 ) } );
}

TEST( SingularRechabilityTest, ReacherConstruction ) {
	using Number = mpq_class;
	using VPoly = hypro::VPolytope<Number>;

	auto automaton = createSingularHA<Number>();
	auto roots = hypro::makeRoots<VPoly, hypro::HybridAutomaton<Number>>( automaton );

	auto reach = hypro::reachability::ReachSingular<VPoly, hypro::HybridAutomaton<Number>>(
		  automaton, hypro::FixedAnalysisParameters{ 1, hypro::tNumber( 10 ) }, roots );
}

TEST( SingularRechabilityTest, SingularAnalyzer ) {
	// Create automaton and analyzer
	auto automaton = createSingularHA<Number>();

	// Add bad states and analyze
	// 1. x >= 0.5 (unsafe)
	Matrix badStateMat = Matrix::Zero( 1, 1 );
	badStateMat << -1;
	Vector badStateVec = -0.5 * Vector::Ones( 1 );

	automaton.setGlobalBadStates( { hypro::Condition<Number>( badStateMat, badStateVec ) } );
	auto initialNodes1 = hypro::makeRoots<VPoly, decltype( automaton )>( automaton );
	auto analyzer = hypro::SingularAnalyzer<VPoly, hypro::HybridAutomaton<Number>>(
		  automaton, hypro::FixedAnalysisParameters{ 0, hypro::tNumber( 4 ), hypro::tNumber( 0.01 ) }, initialNodes1 );
	auto result = analyzer.run();
	EXPECT_EQ( hypro::REACHABILITY_RESULT::UNKNOWN, result.result() );

	// Compare flowpipes. Expect one flowpipe with two Polytopes (one for initial state and one for final)
	auto flowpipes = hypro::getFlowpipes( initialNodes1 );
	EXPECT_TRUE( flowpipes.size() == 1 );
	EXPECT_TRUE( flowpipes[0].size() == 1 );

	// Initial contains only x = 0, final is the line segment x = [0, 1]
	VPoly init( { Point{ 0 } } );
	VPoly final( { Point{ 0 }, Point{ 1 } } );
	EXPECT_TRUE( flowpipes[0].begin()[0].contains( init ) );
	EXPECT_EQ( final, flowpipes[0].begin()[0] );
}

TEST( SingularRechabilityTest, SingularAnalyzer2 ) {
	// 2. x >= 2 (safe)
	Matrix badStateMat = Matrix::Zero( 1, 1 );
	badStateMat << -1;
	Vector badStateVec = -0.5 * Vector::Ones( 1 );

	auto automaton = createSingularHA<Number>();

	badStateVec = -2 * Vector::Ones( 1 );
	automaton.setGlobalBadStates( { hypro::Condition<Number>( badStateMat, badStateVec ) } );
	auto initialNodes2 = hypro::makeRoots<VPoly, decltype( automaton )>( automaton );
	auto analyzer2 = hypro::SingularAnalyzer<VPoly, hypro::HybridAutomaton<Number>>(
		  automaton, hypro::FixedAnalysisParameters{ 0, hypro::tNumber( 4 ), hypro::tNumber( 0.01 ) }, initialNodes2 );
	auto result = analyzer2.run();
	EXPECT_EQ( hypro::REACHABILITY_RESULT::SAFE, result.result() );
}

TEST( SingularRechabilityTest, SingularAnalyzer3 ) {
	// 3. x >= 0.5 with time horizon 0.2 (safe)
	Matrix badStateMat = Matrix::Zero( 1, 1 );
	badStateMat << -1;
	Vector badStateVec = -0.5 * Vector::Ones( 1 );

	auto automaton = createSingularHA<Number>();

	badStateVec = -0.5 * Vector::Ones( 1 );
	automaton.setGlobalBadStates( { hypro::Condition<Number>( badStateMat, badStateVec ) } );
	auto initialNodes3 = hypro::makeRoots<VPoly, decltype( automaton )>( automaton );
	auto analyzer3 = hypro::SingularAnalyzer<VPoly, hypro::HybridAutomaton<Number>>(
		  automaton, hypro::FixedAnalysisParameters{ 0, hypro::tNumber( 0.2 ), hypro::tNumber( 0.01 ) },
		  initialNodes3 );
	auto result = analyzer3.run();
	EXPECT_EQ( hypro::REACHABILITY_RESULT::SAFE, result.result() );
}

TEST( SingularRechabilityTest, SingularAnalyzerTwoDimensions ) {
	// two-dimensional HA
	Matrix badStateMat = Matrix::Zero( 1, 1 );
	badStateMat << -1;
	Vector badStateVec = -0.5 * Vector::Ones( 1 );

	auto automaton = createSingularHA2<Number>();

	// 1. y <= -1 (unsafe)
	badStateMat = Matrix::Zero( 1, 2 );
	badStateMat << 0, 1;
	badStateVec = -1 * Vector::Ones( 1 );

	automaton.setGlobalBadStates( { hypro::Condition<Number>( badStateMat, badStateVec ) } );
	auto initialNodes4 = hypro::makeRoots<VPoly, decltype( automaton )>( automaton );
	auto analyzer4 = hypro::SingularAnalyzer<VPoly, hypro::HybridAutomaton<Number>>(
		  automaton, hypro::FixedAnalysisParameters{ 0, hypro::tNumber( 4 ), hypro::tNumber( 0.01 ) }, initialNodes4 );
	auto result = analyzer4.run();
	EXPECT_EQ( hypro::REACHABILITY_RESULT::UNKNOWN, result.result() );
}

TEST( SingularRechabilityTest, SingularAnalyzerTwoDimensionsUnsafe ) {
	// 2. x <= 1 (unsafe)
	Matrix badStateMat = Matrix::Zero( 1, 2 );
	Vector badStateVec = -0.5 * Vector::Ones( 1 );

	badStateMat << 1, 0;
	badStateVec = Vector::Ones( 1 );

	auto automaton = createSingularHA2<Number>();

	automaton.setGlobalBadStates( { hypro::Condition<Number>( badStateMat, badStateVec ) } );
	auto initialNodes5 = hypro::makeRoots<VPoly, decltype( automaton )>( automaton );
	auto analyzer5 = hypro::SingularAnalyzer<VPoly, hypro::HybridAutomaton<Number>>(
		  automaton, hypro::FixedAnalysisParameters{ 0, hypro::tNumber( 4 ), hypro::tNumber( 0.01 ) }, initialNodes5 );
	auto result = analyzer5.run();
	EXPECT_EQ( hypro::REACHABILITY_RESULT::UNKNOWN, result.result() );
}

TEST( SingularRechabilityTest, SingularAnalyzerTwoDimensionsSafe ) {
	// 3. y <= -1 && x <= 1 (safe)
	Matrix badStateMat = Matrix::Zero( 2, 2 );
	badStateMat << 0, 1, 1, 0;
	Vector badStateVec = Vector::Zero( 2 );
	badStateVec << -1, 1;

	auto automaton = createSingularHA2<Number>();

	automaton.setGlobalBadStates( { hypro::Condition<Number>( badStateMat, badStateVec ) } );
	auto initialNodes6 = hypro::makeRoots<VPoly, decltype( automaton )>( automaton );
	auto analyzer6 = hypro::SingularAnalyzer<VPoly, hypro::HybridAutomaton<Number>>(
		  automaton, hypro::FixedAnalysisParameters{ 0, hypro::tNumber( 4 ), hypro::tNumber( 0.01 ) }, initialNodes6 );
	auto result = analyzer6.run();
	EXPECT_EQ( hypro::REACHABILITY_RESULT::SAFE, result.result() );
}

TEST( SingularRechabilityTest, SingularAnalyzerWithJumpsSafe ) {
	// two-dimensional HA with two locations
	auto automaton = createSingularHA3<Number>();

	// Get locations for local bad states
	hypro::Location<Number>* l0 = automaton.getLocation( "l0" );

	std::map<const hypro::Location<Number>*, hypro::Condition<Number>> localBadStates;

	// 1. l0, y <= -4 (safe)
	Matrix badStateMat = Matrix::Zero( 1, 2 );
	badStateMat( 0, 1 ) = 1;
	Vector badStateVec = -4 * Vector::Ones( 1 );
	hypro::Condition<Number> badState( badStateMat, badStateVec );
	localBadStates[l0] = badState;

	automaton.setLocalBadStates( localBadStates );
	auto initialNodes7 = hypro::makeRoots<VPoly, decltype( automaton )>( automaton );
	auto analyzer7 = hypro::SingularAnalyzer<VPoly, hypro::HybridAutomaton<Number>>(
		  automaton, hypro::FixedAnalysisParameters{ 5, hypro::tNumber( 10 ), hypro::tNumber( 0.01 ) }, initialNodes7 );
	auto result = analyzer7.run();
	EXPECT_EQ( hypro::REACHABILITY_RESULT::SAFE, result.result() );

	// same test using the Reach-interface
	auto roots = hypro::makeRoots<VPoly, decltype( automaton )>( automaton );
	auto reach = hypro::reachability::ReachSingular<VPoly, hypro::HybridAutomaton<Number>>(
		  automaton, hypro::FixedAnalysisParameters{ 5, hypro::tNumber( 10 ), hypro::tNumber( 0.01 ) }, roots );
	hypro::REACHABILITY_RESULT reachRes = reach.computeForwardReachability();
	EXPECT_EQ( hypro::REACHABILITY_RESULT::SAFE, reachRes );
}

TEST( SingularRechabilityTest, SingularAnalyzerWithJumpsUnsafe ) {
	auto automaton = createSingularHA3<Number>();
	// 2. l1, y <= -2 (unsafe)
	Matrix badStateMat = Matrix::Zero( 2, 2 );
	Vector badStateVec = Vector::Zero( 2 );
	badStateMat( 0, 1 ) = 1;
	badStateVec( 0 ) = -2;
	auto badState = hypro::Condition<Number>( badStateMat, badStateVec );

	hypro::Location<Number>* l1 = automaton.getLocation( "l1" );
	std::map<const hypro::Location<Number>*, hypro::Condition<Number>> localBadStates;
	localBadStates[l1] = badState;

	automaton.setLocalBadStates( localBadStates );

	auto initialNodes8 = hypro::makeRoots<VPoly, decltype( automaton )>( automaton );
	auto analyzer8 = hypro::SingularAnalyzer<VPoly, hypro::HybridAutomaton<Number>>(
		  automaton, hypro::FixedAnalysisParameters{ 5, hypro::tNumber( 10 ), hypro::tNumber( 0.01 ) }, initialNodes8 );
	auto result = analyzer8.run();
	EXPECT_EQ( hypro::REACHABILITY_RESULT::UNKNOWN, result.result() );

	// 3. l1, x >= 3 (unsafe)
	badStateMat = Matrix::Zero( 1, 2 );
	badStateMat( 0, 0 ) = -1;
	badStateVec = -3 * Vector::Ones( 1 );
	badState = hypro::Condition<Number>( badStateMat, badStateVec );
	localBadStates.clear();
	localBadStates[l1] = badState;

	automaton.setLocalBadStates( localBadStates );
	auto initialNodes9 = hypro::makeRoots<VPoly, decltype( automaton )>( automaton );
	auto analyzer9 = hypro::SingularAnalyzer<VPoly, hypro::HybridAutomaton<Number>>(
		  automaton, hypro::FixedAnalysisParameters{ 5, hypro::tNumber( 10 ), hypro::tNumber( 0.01 ) }, initialNodes9 );
	result = analyzer9.run();
	EXPECT_EQ( hypro::REACHABILITY_RESULT::UNKNOWN, result.result() );
}

TEST( SingularRechabilityTest, MultipleJumpsEnabled ) {
	using Number = mpq_class;
	using VPoly = hypro::VPolytope<Number>;
	using Matrix = hypro::matrix_t<Number>;
	using Vector = hypro::vector_t<Number>;

	auto automaton = createSingularHA4<Number>();

	Matrix badStateMat = Matrix::Zero( 1, 1 );
	badStateMat << 1;
	Vector badStateVec = -1 * Vector::Ones( 1 );

	automaton.setGlobalBadStates( { hypro::Condition<Number>( badStateMat, badStateVec ) } );
	auto initialNodes1 = hypro::makeRoots<VPoly, decltype( automaton )>( automaton );
	auto analyzer = hypro::SingularAnalyzer<VPoly, hypro::HybridAutomaton<Number>>(
		  automaton, hypro::FixedAnalysisParameters{ 5, hypro::tNumber( 4 ), hypro::tNumber( 0.01 ) }, initialNodes1 );
	auto result = analyzer.run();
	EXPECT_EQ( hypro::REACHABILITY_RESULT::UNKNOWN, result.result() );

	badStateMat << -1;
	automaton.setGlobalBadStates( { hypro::Condition<Number>( badStateMat, badStateVec ) } );
	auto initialNodes2 = hypro::makeRoots<VPoly, decltype( automaton )>( automaton );
	auto analyzer2 = hypro::SingularAnalyzer<VPoly, hypro::HybridAutomaton<Number>>(
		  automaton, hypro::FixedAnalysisParameters{ 5, hypro::tNumber( 4 ), hypro::tNumber( 0.01 ) }, initialNodes2 );
	result = analyzer2.run();
	EXPECT_EQ( hypro::REACHABILITY_RESULT::UNKNOWN, result.result() );
}

TEST( SingularRechabilityTest, SimplePLTScenario ) {
	// example which uses the automaton created from a plt
	using Number = mpq_class;
	using HPoly = hypro::HPolytope<Number>;

	auto automaton = hypro::testing::createPLTSingularAutomaton<Number>();

	auto initialNodes = hypro::makeRoots<HPoly, decltype( automaton )>( automaton );
	EXPECT_TRUE( initialNodes.size() == 1 );
	auto analyzer = hypro::SingularAnalyzer<HPoly, decltype( automaton )>(
		  automaton, hypro::FixedAnalysisParameters{ 3, hypro::tNumber( 15 ), hypro::tNumber( 0.01 ) }, initialNodes );
	auto result = analyzer.run();
	EXPECT_EQ( hypro::REACHABILITY_RESULT::SAFE, result.result() );

	// TODO Test some actual properties

	/*
	// plot flowpipes
	hypro::Plotter<Number>& plt = hypro::Plotter<Number>::getInstance();
	plt.rSettings().fill = true;
	plt.rSettings().cummulative = true;
	// variable order: t,s,x,aff
	std::vector<std::vector<std::size_t>> pltDimensions{ { 0, 1 }, { 0, 2 }, { 1, 2 } };
	std::vector<std::string> filenames{ "test_t_s", "test_t_x", "test_s_x" };
	std::size_t pos = 0;
	auto flowpipes = getFlowpipes( initialNodes.front() );
	for ( const auto& dimPair : pltDimensions ) {
		plt.setFilename( filenames[pos] );
		++pos;
		for ( const auto& fp : flowpipes ) {
			for ( const auto& segment : fp ) {
				plt.addObject( reduceToDimensions( segment.projectOn( dimPair ).vertices(), dimPair ) );
			}
		}
		plt.plot2d();
		plt.clear();
	}
	*/
}

TEST( SingularRechabilityTest, ReservoirCaseStudy ) {
	// Example of a reservoir modelled by a Hybrid Petri net. We analyze the resulting singular automaton with
	// continuous non-determinism involved.
	using Number = mpq_class;
	using M = hypro::matrix_t<Number>;
	using V = hypro::vector_t<Number>;
	using HPoly = hypro::HPolytope<Number>;
	// automaton
	hypro::HybridAutomaton<Number> automaton;
	// 5 locations
	hypro::Location<Number>* l0 = automaton.createLocation();
	l0->setName( "l0" );
	hypro::Location<Number>* l1 = automaton.createLocation();
	l1->setName( "l1" );
	hypro::Location<Number>* l2 = automaton.createLocation();
	l2->setName( "l2" );
	hypro::Location<Number>* l3 = automaton.createLocation();
	l3->setName( "l3" );
	hypro::Location<Number>* l4 = automaton.createLocation();
	l4->setName( "l4" );
	// variable order: x,c,s
	const Eigen::Index x = 0;
	const Eigen::Index c = 1;
	const Eigen::Index s = 2;
	// try to allocate variables with correct name
	hypro::VariablePool::getInstance().carlVarByIndex( x, "x" );
	hypro::VariablePool::getInstance().carlVarByIndex( c, "c" );
	hypro::VariablePool::getInstance().carlVarByIndex( s, "s" );
	// initial configuration
	std::vector<carl::Interval<Number>> initialValuations{ carl::Interval<Number>( 0 ), carl::Interval<Number>( 0 ),
														   carl::Interval<Number>( 0 ) };
	automaton.addInitialState( l0, hypro::conditionFromIntervals<Number>( initialValuations ) );
	// basic matrix for dynamics, to realize singular dynamics only modify the last column
	M dynamics = M::Zero( 4, 4 );
	// invariants are for all locations the same: x in [0,10], all others in [-11,11] (for ploting)
	std::vector<carl::Interval<Number>> invariantIntervals{
		  carl::Interval<Number>( 0, 10 ), carl::Interval<Number>( -11, 11 ), carl::Interval<Number>( -11, 11 ) };
	auto invariants = hypro::conditionFromIntervals( invariantIntervals );
	DEBUG( "hypro.reachability", "Created invariant condition: " << invariants );
	l0->setInvariant( invariants );
	l1->setInvariant( invariants );
	l2->setInvariant( invariants );
	l3->setInvariant( invariants );
	l4->setInvariant( invariants );
	// set dynamics l0
	dynamics( x, 3 ) = Number( 1 );
	dynamics( c, 3 ) = Number( 1 );
	dynamics( s, 3 ) = Number( 1 );
	l0->setFlow( dynamics );
	// set dynamics l1
	dynamics( x, 3 ) = Number( -1 );
	dynamics( c, 3 ) = Number( 0 );
	dynamics( s, 3 ) = Number( 1 );
	l1->setFlow( dynamics );
	// set dynamics l2
	dynamics( x, 3 ) = Number( 2 );
	dynamics( c, 3 ) = Number( 1 );
	dynamics( s, 3 ) = Number( 0 );
	l2->setFlow( dynamics );
	// set dynamics l3
	dynamics( x, 3 ) = Number( 0 );
	dynamics( c, 3 ) = Number( 0 );
	dynamics( s, 3 ) = Number( 0 );
	l3->setFlow( dynamics );
	// set dynamics l4, similar to l3
	l4->setFlow( dynamics );
	// transitions
	// l0 -> l1
	M guardConstraints = M::Zero( 1, 3 );
	V guardConstants = V::Zero( 1 );
	{
		hypro::Transition<Number, typename hypro::HybridAutomaton<Number>::LocationType>* t = l0->createTransition( l1 );
		guardConstraints( 0, c ) = Number( -1 );
		guardConstants( 0 ) = Number( -2 );
		t->setGuard( { guardConstraints, guardConstants } );
	}
	// l2 -> l3
	{
		auto* t = l2->createTransition( l3 );
		t->setGuard( { guardConstraints, guardConstants } );
	}
	// l0 -> l2
	std::vector<carl::Interval<Number>> resets;
	// identity resets are indicated by empty intervals
	resets.emplace_back( carl::Interval<Number>::emptyInterval() );
	resets.emplace_back( carl::Interval<Number>::emptyInterval() );
	// resets.emplace_back( carl::Interval<Number>( Number( 0 ) ) );
	resets.emplace_back( carl::Interval<Number>::emptyInterval() );
	{
		auto* t = l0->createTransition( l2 );
		t->setReset( { resets } );
	}
	// l1 -> l3
	{
		auto* t = l1->createTransition( l3 );
		t->setReset( { resets } );
	}
	// l0 -> l4
	guardConstraints = M::Zero( 2, 3 );
	guardConstants = V::Zero( 2 );
	guardConstraints( 0, x ) = Number( 1 );
	guardConstraints( 1, x ) = Number( -1 );
	guardConstants( 0 ) = Number( 10 );
	guardConstants( 1 ) = Number( -10 );
	{
		auto* t = l0->createTransition( l4 );
		t->setGuard( { guardConstraints, guardConstants } );
	}
	// l2 -> l4
	{
		auto* t = l2->createTransition( l4 );
		t->setGuard( { guardConstraints, guardConstants } );
	}
	// l1 -> l4
	guardConstraints = M::Zero( 1, 3 );
	guardConstants = V::Zero( 1 );
	guardConstraints( 0, x ) = Number( 1 );
	{
		auto* t = l1->createTransition( l4 );
		t->setGuard( { guardConstraints, guardConstants } );
	}

	auto initialNodes = hypro::makeRoots<HPoly, decltype( automaton )>( automaton );
	EXPECT_TRUE( initialNodes.size() == 1 );
	auto analyzer = hypro::SingularAnalyzer<HPoly, decltype( automaton )>(
		  automaton, hypro::FixedAnalysisParameters{ 5, hypro::tNumber( 15 ), hypro::tNumber( 0.01 ) }, initialNodes );
	auto result = analyzer.run();
	// trivially safe, as no unsafe states have been defined
	EXPECT_EQ( hypro::REACHABILITY_RESULT::SAFE, result.result() );

	// TODO Test some actual properties

	/*
	// plot flowpipes
	hypro::Plotter<Number>& plt = hypro::Plotter<Number>::getInstance();
	plt.rSettings().fill = true;
	plt.rSettings().cummulative = true;
	// variable order: x,c,s
	std::vector<std::vector<std::size_t>> pltDimensions{ { s, x }, { x, c } };
	std::vector<std::string> filenames{ "reservoir_s_x", "reservoir_x_c" };
	std::size_t pos = 0;
	auto flowpipes = getFlowpipes( initialNodes.front() );
	for ( const auto& dimPair : pltDimensions ) {
		plt.setFilename( filenames[pos] );
		++pos;
		for ( const auto& fp : flowpipes ) {
			for ( const auto& segment : fp ) {
				plt.addObject( reduceToDimensions( segment.projectOn( dimPair ).vertices(), dimPair ) );
			}
		}
		plt.plot2d();
		plt.clear();
	}
	*/
}