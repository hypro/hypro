#include "../defines.h"
#include "gtest/gtest.h"
#include <hypro/algorithms/reachability/Reach.h>
#include <hypro/algorithms/reachability/analyzer/RectangularAnalyzer.h>
#include <hypro/algorithms/reachability/workers/RectangularWorker.h>
#include <hypro/datastructures/HybridAutomaton/HybridAutomaton.h>
#include <hypro/datastructures/reachability/ReachTreev2Util.h>
#include <hypro/datastructures/reachability/Settings.h>
#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/util/plotting/Plotter.h>

using Number = mpq_class;
using VPoly = hypro::VPolytope<Number>;
using Matrix = hypro::matrix_t<Number>;
using Interval = carl::Interval<Number>;
using Vector = hypro::vector_t<Number>;
using Point = hypro::Point<Number>;

template <typename Number>
hypro::HybridAutomaton<Number> createRectangularHA() {
	// One-dimensional HA with one location

	hypro::HybridAutomaton<Number> res;

	// Create location
	auto loc = res.createLocation();

	// Set flow x' = [1,2]
	Interval flow{ 1, 2 };
	typename hypro::rectangularFlow<Number>::flowMap fMap;
	fMap[hypro::VariablePool::getInstance().carlVarByIndex( 0 )] = flow;
	loc->setFlow( { hypro::rectangularFlow<Number>{ fMap } } );

	// Set invariant x <= 10
	Matrix invariantConstraints = Matrix::Zero( 1, 1 );
	invariantConstraints( 0, 0 ) = 1;
	Vector invariantConstants = Vector::Zero( 1 );
	invariantConstants( 0 ) = 10;
	loc->setInvariant( { invariantConstraints, invariantConstants } );

	// Set initial state x = 0, aff = 1
	Matrix initialConstraints = Matrix::Zero( 2, 1 );
	Vector initialConstants = Vector::Zero( 2 );
	initialConstraints << 1, -1;
	initialConstants << 0, 0;

	// set loc as initial location + add initial valuation
	res.addInitialState( loc, hypro::Condition<Number>( initialConstraints, initialConstants ) );

	return res;
}

template <typename Number>
hypro::HybridAutomaton<Number> createRectangularHA2() {
	// One-dimensional reactangular automaton with two locations
	hypro::HybridAutomaton<Number> res;

	// Create location
	auto loc = res.createLocation();

	// Set flow x' = [1,2]
	Interval flow{ 1, 2 };
	typename hypro::rectangularFlow<Number>::flowMap fMap;
	fMap[hypro::VariablePool::getInstance().carlVarByIndex( 0 )] = flow;
	loc->setFlow( { hypro::rectangularFlow<Number>{ fMap } } );

	// Set invariant x <= 10
	Matrix invariantConstraints = Matrix::Zero( 1, 1 );
	invariantConstraints( 0, 0 ) = 1;
	Vector invariantConstants = Vector::Zero( 1 );
	invariantConstants( 0 ) = 10;
	loc->setInvariant( { invariantConstraints, invariantConstants } );

	// Create second location
	auto loc2 = res.createLocation();

	// Add transition from first to second location with no guard and no reset
	auto transition = loc->createTransition( loc2 );

	// Set initial state x = 0, aff = 1
	Matrix initialConstraints = Matrix::Zero( 2, 1 );
	Vector initialConstants = Vector::Zero( 2 );
	initialConstraints << 1, -1;
	initialConstants << 0, 0;

	// Create HA
	res.addInitialState( loc, hypro::Condition<Number>( initialConstraints, initialConstants ) );

	return res;
}

template <typename Number>
hypro::HybridAutomaton<Number> createRectangularHA3() {
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
	hypro::Reset<Number> reset{ { { 0, 0 }, { 0, 0 } } };

	std::unique_ptr<hypro::Transition<Number>> trans0 =
		  std::make_unique<hypro::Transition<Number>>( uniqueLoc0.get(), uniqueLoc0.get(), guard, reset );

	// l0 -> l1 with guard y <= -2 and no reset
	transConstraint = Matrix::Zero( 1, 2 );
	transConstants = -2 * Vector::Ones( 1 );
	transConstraint( 0, 1 ) = 1;
	guard = hypro::Condition<Number>( transConstraint, transConstants );
	reset = hypro::Reset<Number>( { carl::Interval<Number>(), carl::Interval<Number>() } );

	std::unique_ptr<hypro::Transition<Number>> trans1 =
		  std::make_unique<hypro::Transition<Number>>( uniqueLoc0.get(), uniqueLoc1.get(), guard, reset );

	// Set initial state x = 0, y = 0, aff = 1
	Matrix initialConstraints = Matrix::Zero( 4, 2 );
	Vector initialConstants = Vector::Zero( 4 );
	initialConstraints << 1, 0, -1, 0, 0, 1, 0, -1;
	initialConstants << 0, 0, 0, 0;

	// Create HA
	uniqueLoc0->addTransition( std::move( trans0 ) );
	uniqueLoc0->addTransition( std::move( trans1 ) );

	res.addInitialState( uniqueLoc0.get(), hypro::Condition<Number>( initialConstraints, initialConstants ) );

	res.addLocation( std::move( uniqueLoc0 ) );
	res.addLocation( std::move( uniqueLoc1 ) );

	return res;
}

template <typename Number>
hypro::HybridAutomaton<Number> createRectangularHA4() {
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
	hypro::Reset<Number> reset{ { { 1, 1 } } };

	std::unique_ptr<hypro::Transition<Number>> trans0 =
		  std::make_unique<hypro::Transition<Number>>( loc.get(), loc.get(), guard, reset );

	reset = hypro::Reset<Number>{ { { -1, -1 } } };
	std::unique_ptr<hypro::Transition<Number>> trans1 =
		  std::make_unique<hypro::Transition<Number>>( loc.get(), loc.get(), guard, reset );

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

template <typename Number>
hypro::HybridAutomaton<Number> createPLTSingularAutomaton() {
	// automaton created from a parametric location tree of a hybrid Petri net
	using Matrix = hypro::matrix_t<Number>;
	using Vector = hypro::vector_t<Number>;

	hypro::HybridAutomaton<Number> res;

	// get location pointers
	auto* locAllOn = res.createLocation();
	auto* locInOffFirst = res.createLocation();
	auto* locOutOffFirst = res.createLocation();
	auto* locAllOff = res.createLocation();
	auto* locRateAdaptationUp = res.createLocation();
	auto* locRateAdaptationLo = res.createLocation();

	// set dynamics, variable order: t,s,x,aff
	Eigen::Index aff = 3;
	Eigen::Index t = 0;
	Eigen::Index s = 1;
	Eigen::Index x = 2;
	Matrix dynamics = Matrix::Zero( 4, 4 );
	dynamics( t, aff ) = 1;	 // t' = 1

	dynamics( s, aff ) = 1;	 // s' = 1
	dynamics( x, aff ) = 1;	 // x' = 1
	locAllOn->setLinearFlow( { dynamics } );

	dynamics( s, aff ) = 0;	  // s' = 1
	dynamics( x, aff ) = -1;  // x' = -1
	locInOffFirst->setLinearFlow( { dynamics } );

	dynamics( s, aff ) = 1;	 // s' = 1
	dynamics( x, aff ) = 2;	 // x' = 2
	locOutOffFirst->setLinearFlow( { dynamics } );

	dynamics( s, aff ) = 0;	 // s' = 0
	dynamics( x, aff ) = 0;	 // x' = 0
	locAllOff->setLinearFlow( { dynamics } );
	locRateAdaptationLo->setLinearFlow( { dynamics } );

	dynamics( s, aff ) = 1;	 // s' = 1
	dynamics( x, aff ) = 0;	 // x' = 0
	locRateAdaptationUp->setLinearFlow( { dynamics } );

	// set invariants
	Matrix constraints = Matrix::Zero( 4, 3 );
	Vector constants = Vector::Zero( 4 );

	// global invariants: t <= 15, x in [0,10]
	constraints( 0, t ) = 1;
	constants( 0 ) = 15;
	constraints( 1, x ) = 1;
	constants( 1 ) = 10;
	constraints( 2, x ) = -1;
	constants( 2 ) = 0;

	locOutOffFirst->setInvariant( { constraints, constants } );
	locAllOff->setInvariant( { constraints, constants } );
	locRateAdaptationUp->setInvariant( { constraints, constants } );

	// t <= 5
	constraints( 3, t ) = 1;
	constants( 3 ) = 5;

	locAllOn->setInvariant( { constraints, constants } );
	locInOffFirst->setInvariant( { constraints, constants } );
	locRateAdaptationLo->setInvariant( { constraints, constants } );

	// transitions with guards
	Matrix guardConstraints = Matrix::Zero( 2, 3 );
	Vector guardConstants = Vector::Zero( 2 );

	// guard t = 5
	guardConstraints( 0, t ) = 1;
	guardConstraints( 1, t ) = -1;
	guardConstants( 0 ) = 5;
	guardConstants( 1 ) = -5;

	locAllOn->createTransition( locInOffFirst );
	auto* t1 = locAllOn->createTransition( locOutOffFirst );
	auto* t2 = locInOffFirst->createTransition( locRateAdaptationLo );
	auto* t3 = locInOffFirst->createTransition( locAllOff );
	auto* t4 = locOutOffFirst->createTransition( locRateAdaptationUp );
	locOutOffFirst->createTransition( locAllOff );
	auto* t6 = locRateAdaptationLo->createTransition( locAllOff );
	locRateAdaptationUp->createTransition( locAllOff );

	t1->setGuard( { guardConstraints, guardConstants } );
	t3->setGuard( { guardConstraints, guardConstants } );
	t6->setGuard( { guardConstraints, guardConstants } );

	// guard x = 0
	guardConstraints = Matrix::Zero( 2, 3 );
	guardConstants = Vector::Zero( 2 );
	guardConstraints( 0, x ) = 1;
	guardConstraints( 1, x ) = -1;
	guardConstants( 0 ) = 0;
	guardConstants( 1 ) = -0;

	t2->setGuard( { guardConstraints, guardConstants } );

	// guard x = 10
	guardConstants( 0 ) = 10;
	guardConstants( 1 ) = -10;

	t4->setGuard( { guardConstraints, guardConstants } );

	// initial states: x=z=t=0, aff = 1
	Matrix initialConstraints = Matrix::Zero( 6, 3 );
	Vector initialConstants = Vector::Zero( 6 );
	initialConstraints( 0, t ) = 1;
	initialConstraints( 1, t ) = -1;
	initialConstraints( 2, x ) = 1;
	initialConstraints( 3, x ) = -1;
	initialConstraints( 4, s ) = 1;
	initialConstraints( 5, s ) = -1;

	res.addInitialState( locAllOn, { initialConstraints, initialConstants } );

	return res;
}

TEST( RectangularRechabilityTest, WorkerConstruction ) {
	using Number = mpq_class;
	using VPoly = hypro::VPolytope<Number>;

	auto automaton = createRectangularHA<Number>();

	hypro::AnalysisParameters analysisParameters;
	analysisParameters.timeStep = hypro::tNumber( 1 ) / hypro::tNumber( 100 );
	analysisParameters.aggregation = hypro::AGG_SETTING::AGG;
	analysisParameters.representation_type = hypro::representation_name::polytope_v;

	hypro::Settings settings{ {},
							  hypro::FixedAnalysisParameters{ 5, hypro::tNumber( 4 ), hypro::tNumber( 0.01 ) },
							  { analysisParameters } };

	auto worker = hypro::RectangularWorker<VPoly>( automaton, settings );
	SUCCEED();
}

TEST( RectangularRechabilityTest, ReacherConstruction ) {
	using Number = mpq_class;
	using VPoly = hypro::VPolytope<Number>;

	auto automaton = createRectangularHA<Number>();
	auto roots = hypro::makeRoots<VPoly, Number>( automaton );

	hypro::AnalysisParameters analysisParameters;
	analysisParameters.timeStep = hypro::tNumber( 1 ) / hypro::tNumber( 100 );
	analysisParameters.aggregation = hypro::AGG_SETTING::AGG;
	analysisParameters.representation_type = hypro::representation_name::polytope_v;

	hypro::Settings settings{ {},
							  hypro::FixedAnalysisParameters{ 5, hypro::tNumber( 4 ), hypro::tNumber( 0.01 ) },
							  { analysisParameters } };

	auto reach = hypro::reachability::ReachBase<VPoly, hypro::RectangularAnalyzer<VPoly>>( automaton, settings, roots );
	SUCCEED();
}

TEST( RectangularRechabilityTest, ComputeReachability1 ) {
	using Number = mpq_class;
	using VPoly = hypro::VPolytope<Number>;

	auto automaton = createRectangularHA<Number>();
	auto roots = hypro::makeRoots<VPoly, Number>( automaton );

	hypro::AnalysisParameters analysisParameters;
	analysisParameters.timeStep = hypro::tNumber( 1 ) / hypro::tNumber( 100 );
	analysisParameters.aggregation = hypro::AGG_SETTING::AGG;
	analysisParameters.representation_type = hypro::representation_name::polytope_v;

	hypro::Settings settings{ {},
							  hypro::FixedAnalysisParameters{ 5, hypro::tNumber( 4 ), hypro::tNumber( 0.01 ) },
							  { analysisParameters } };

	auto reach = hypro::reachability::ReachBase<VPoly, hypro::RectangularAnalyzer<VPoly>>( automaton, settings, roots );

	// call verifier, validate result
	auto reachabilityResult = reach.computeForwardReachability();
	EXPECT_EQ( hypro::REACHABILITY_RESULT::SAFE, reachabilityResult );

	// validate computed flowpipes
	std::vector<std::vector<VPoly>> flowpipes;
	std::for_each( roots.begin(), roots.end(), [&]( auto& root ) {
		auto fp = getFlowpipes( root );
		flowpipes.insert( flowpipes.end(), fp.begin(), fp.end() );
	} );
}

/*
TEST( RectangularRechabilityTest, SingularAnalyzer ) {
	// Create automaton and analyzer
	auto automaton = createRectangularHA<Number>();

	// Add bad states and analyze
	// 1. x >= 0.5 (unsafe)
	Matrix badStateMat = Matrix::Zero( 1, 1 );
	badStateMat << -1;
	Vector badStateVec = -0.5 * Vector::Ones( 1 );

	automaton.setGlobalBadStates( { hypro::Condition<Number>( badStateMat, badStateVec ) } );
	auto initialNodes1 = hypro::makeRoots<VPoly, Number>( automaton );
	auto analyzer = hypro::SingularAnalyzer<VPoly>(
		  automaton, hypro::FixedAnalysisParameters{ 0, hypro::tNumber( 4 ), hypro::tNumber( 0.01 ) }, initialNodes1 );
	auto result = analyzer.run();
	EXPECT_EQ( hypro::REACHABILITY_RESULT::UNKNOWN, result.result() );

	// Compare flowpipes. Expect one flowpipe with two Polytopes (one for initial state and one for final)
	auto flowpipes = hypro::getFlowpipes( initialNodes1 );
	EXPECT_TRUE( flowpipes.size() == 1 );
	EXPECT_TRUE( flowpipes[0].size() == 2 );

	// Initial contains only x = 0, final is the line segment x = [0, 1]
	VPoly init( { Point{ 0 } } );
	VPoly final( { Point{ 0 }, Point{ 1 } } );
	EXPECT_EQ( init, flowpipes[0].begin()[0] );
	EXPECT_EQ( final, flowpipes[0].begin()[1] );
}

TEST( RectangularRechabilityTest, SingularAnalyzer2 ) {
	// 2. x >= 2 (safe)
	Matrix badStateMat = Matrix::Zero( 1, 1 );
	badStateMat << -1;
	Vector badStateVec = -0.5 * Vector::Ones( 1 );

	auto automaton = createRectangularHA<Number>();

	badStateVec = -2 * Vector::Ones( 1 );
	automaton.setGlobalBadStates( { hypro::Condition<Number>( badStateMat, badStateVec ) } );
	auto initialNodes2 = hypro::makeRoots<VPoly, Number>( automaton );
	auto analyzer2 = hypro::SingularAnalyzer<VPoly>(
		  automaton, hypro::FixedAnalysisParameters{ 0, hypro::tNumber( 4 ), hypro::tNumber( 0.01 ) }, initialNodes2 );
	auto result = analyzer2.run();
	EXPECT_EQ( hypro::REACHABILITY_RESULT::SAFE, result.result() );
}

TEST( RectangularRechabilityTest, SingularAnalyzer3 ) {
	// 3. x >= 0.5 with time horizon 0.2 (safe)
	Matrix badStateMat = Matrix::Zero( 1, 1 );
	badStateMat << -1;
	Vector badStateVec = -0.5 * Vector::Ones( 1 );

	auto automaton = createRectangularHA<Number>();

	badStateVec = -0.5 * Vector::Ones( 1 );
	automaton.setGlobalBadStates( { hypro::Condition<Number>( badStateMat, badStateVec ) } );
	auto initialNodes3 = hypro::makeRoots<VPoly, Number>( automaton );
	auto analyzer3 = hypro::SingularAnalyzer<VPoly>(
		  automaton, hypro::FixedAnalysisParameters{ 0, hypro::tNumber( 0.2 ), hypro::tNumber( 0.01 ) },
		  initialNodes3 );
	auto result = analyzer3.run();
	EXPECT_EQ( hypro::REACHABILITY_RESULT::SAFE, result.result() );
}

*/
