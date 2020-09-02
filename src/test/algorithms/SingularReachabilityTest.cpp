#include "../defines.h"
#include "gtest/gtest.h"
#include <algorithms/reachability/analyzer/SingularAnalyzer.h>
#include <algorithms/reachability/workers/SingularWorker.h>
#include <datastructures/HybridAutomaton/HybridAutomaton.h>
#include <datastructures/reachability/Settings.h>
#include <representations/GeometricObjectBase.h>

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
	Matrix invariantConstraints = Matrix::Zero( 1, 2 );
	invariantConstraints( 0, 0 ) = 1;
	Vector invariantConstants = Vector::Ones( 1 );
	loc.setInvariant( { invariantConstraints, invariantConstants } );

	// Set initial state x = 0, aff = 1
	Matrix initialConstraints = Matrix::Zero( 4, 2 );
	Vector initialConstants = Vector::Zero( 4 );
	initialConstraints << 1, 0, -1, 0, 0, 1, 0, -1;
	initialConstants << 0, 0, 1, -1;

	// Create HA
	res.addLocation( std::make_unique<hypro::Location<Number>>( loc ) );
	res.addInitialState( &loc, hypro::Condition<Number>( initialConstraints, initialConstants ) );

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
	Matrix invariantConstraints = Matrix::Zero( 1, 3 );
	invariantConstraints( 0, 0 ) = 1;
	Vector invariantConstants = 3 * Vector::Ones( 1 );
	loc.setInvariant( { invariantConstraints, invariantConstants } );

	// Set initial state x = 0, y = 1, aff = 1
	Matrix initialConstraints = Matrix::Zero( 6, 3 );
	Vector initialConstants = Vector::Zero( 6 );
	initialConstraints << 1, 0, 0, -1, 0, 0, 0, 1, 0, 0, -1, 0, 0, 0, 1, 0, 0, -1;
	initialConstants << 0, 0, 1, -1, 1, -1;

	// Create HA
	res.addLocation( std::make_unique<hypro::Location<Number>>( loc ) );
	res.addInitialState( &loc, hypro::Condition<Number>( initialConstraints, initialConstants ) );

	return res;
}

template <typename Number>
hypro::HybridAutomaton<Number> createSingularHA3() {
	// Two-dimensional HA with two locations
	using Matrix = hypro::matrix_t<Number>;
	using Vector = hypro::vector_t<Number>;

	hypro::HybridAutomaton<Number> res;

	// Create locations
	std::unique_ptr<hypro::Location<Number>> loc0 = std::make_unique<hypro::Location<Number>>();
	std::unique_ptr<hypro::Location<Number>> loc1 = std::make_unique<hypro::Location<Number>>();
	loc0->setName( "l0" );
	loc1->setName( "l1" );

	// Set flow x' = 1, y' = -1 in loc0
	Matrix flow0 = Matrix::Zero( 3, 3 );
	flow0( 0, 2 ) = 1;
	flow0( 1, 2 ) = -1;
	loc0->setFlow( flow0 );

	// Set flow x' = 0, y' = 1 in loc1
	Matrix flow1 = Matrix::Zero( 3, 3 );
	flow1( 1, 2 ) = 1;
	loc1->setFlow( flow1 );

	// Set invariant x <= 3 in loc0
	Matrix invariantConstraints = Matrix::Zero( 1, 3 );
	invariantConstraints( 0, 0 ) = 1;
	Vector invariantConstants = 3 * Vector::Ones( 1 );
	loc0->setInvariant( { invariantConstraints, invariantConstants } );
	loc1->setInvariant( { invariantConstraints, invariantConstants } );

	// Construct transitions
	// l0 -> l0 with guard x >= 1 and reset x := 0, y := 0
	Matrix transConstraint = Matrix::Zero( 1, 3 );
	Vector transConstants = -1 * Vector::Ones( 1 );
	transConstraint( 0, 0 ) = -1;
	hypro::Condition<Number> guard( transConstraint, transConstants );
	// resets: interval-assignments all to zero
	std::vector<carl::Interval<Number>> resets{ { 0, 0 }, { 0, 0 }, { 0, 0 } };
	hypro::Reset<Number> reset{ resets };

	std::unique_ptr<hypro::Transition<Number>> trans0 =
		  std::make_unique<hypro::Transition<Number>>( loc0.get(), loc0.get(), guard, reset );

	// l0 -> l1 with guard y <= -2 and no reset
	transConstraint = Matrix::Zero( 1, 3 );
	transConstants = -2 * Vector::Ones( 1 );
	transConstraint( 0, 1 ) = 1;
	guard = hypro::Condition<Number>( transConstraint, transConstants );
	reset = hypro::Reset<Number>();

	std::unique_ptr<hypro::Transition<Number>> trans1 =
		  std::make_unique<hypro::Transition<Number>>( loc0.get(), loc1.get(), guard, reset );

	// Set initial state x = 0, y = 0, aff = 1
	Matrix initialConstraints = Matrix::Zero( 6, 3 );
	Vector initialConstants = Vector::Zero( 6 );
	initialConstraints << 1, 0, 0, -1, 0, 0, 0, 1, 0, 0, -1, 0, 0, 0, 1, 0, 0, -1;
	initialConstants << 0, 0, 0, 0, 1, -1;

	// Create HA
	loc0->addTransition( std::move( trans0 ) );
	loc0->addTransition( std::move( trans1 ) );
	res.addLocation( std::move( loc0 ) );
	res.addLocation( std::move( loc1 ) );
	res.addInitialState( loc0.get(), hypro::Condition<Number>( initialConstraints, initialConstants ) );

	return res;
}

TEST( SingularRechabilityTest, WorkerConstruction ) {
	using Number = mpq_class;
	using VPoly = hypro::VPolytope<Number>;

	auto automaton = createSingularHA<Number>();

	auto worker = hypro::SingularWorker<VPoly>( automaton, hypro::Settings{ {}, { 1, hypro::tNumber( 10 ) }, {} } );
}

TEST( SingularRechabilityTest, SingularAnalyzer ) {
	using Number = mpq_class;
	using VPoly = hypro::VPolytope<Number>;
	using Matrix = hypro::matrix_t<Number>;
	using Vector = hypro::vector_t<Number>;

	// Create automaton and analyzer
	auto automaton = createSingularHA<Number>();

	// Add bad states and analyze
	// 1. x >= 0.5 (unsafe)
	Matrix badStateMat = Matrix::Zero( 1, 2 );
	badStateMat << -1, 0;
	Vector badStateVec = -0.5 * Vector::Ones( 1 );

	automaton.setGlobalBadStates( { hypro::Condition<Number>( badStateMat, badStateVec ) } );
	auto analyzer = hypro::SingularAnalyzer<VPoly>(
		  automaton, hypro::Settings{ {}, { 0, hypro::tNumber( 4 ), hypro::tNumber( 0.01 ) }, {} } );
	hypro::REACHABILITY_RESULT result = analyzer.run();
	EXPECT_EQ( hypro::REACHABILITY_RESULT::UNKNOWN, result );

	// 2. x >= 2 (safe)
	badStateVec = -2 * Vector::Ones( 1 );
	automaton.setGlobalBadStates( { hypro::Condition<Number>( badStateMat, badStateVec ) } );
	analyzer = hypro::SingularAnalyzer<VPoly>(
		  automaton, hypro::Settings{ {}, { 0, hypro::tNumber( 4 ), hypro::tNumber( 0.01 ) }, {} } );
	result = analyzer.run();
	EXPECT_EQ( hypro::REACHABILITY_RESULT::SAFE, result );

	// 3. x >= 0.5 with time horizon 0.2 (safe)
	badStateVec = -0.5 * Vector::Ones( 1 );
	automaton.setGlobalBadStates( { hypro::Condition<Number>( badStateMat, badStateVec ) } );
	analyzer = hypro::SingularAnalyzer<VPoly>(
		  automaton, hypro::Settings{ {}, { 0, hypro::tNumber( 0.2 ), hypro::tNumber( 0.01 ) }, {} } );
	result = analyzer.run();
	EXPECT_EQ( hypro::REACHABILITY_RESULT::SAFE, result );

	// two-dimensional HA
	automaton = createSingularHA2<Number>();

	// 1. y <= -1 (unsafe)
	badStateMat = Matrix::Zero( 1, 3 );
	badStateMat << 0, 1, 0;
	badStateVec = -1 * Vector::Ones( 1 );

	automaton.setGlobalBadStates( { hypro::Condition<Number>( badStateMat, badStateVec ) } );
	analyzer = hypro::SingularAnalyzer<VPoly>(
		  automaton, hypro::Settings{ {}, { 0, hypro::tNumber( 4 ), hypro::tNumber( 0.01 ) }, {} } );
	result = analyzer.run();
	EXPECT_EQ( hypro::REACHABILITY_RESULT::UNKNOWN, result );

	// 2. x <= 1 (unsafe)
	badStateMat << 1, 0, 0;
	badStateVec = Vector::Ones( 1 );

	automaton.setGlobalBadStates( { hypro::Condition<Number>( badStateMat, badStateVec ) } );
	analyzer = hypro::SingularAnalyzer<VPoly>(
		  automaton, hypro::Settings{ {}, { 0, hypro::tNumber( 4 ), hypro::tNumber( 0.01 ) }, {} } );
	result = analyzer.run();
	EXPECT_EQ( hypro::REACHABILITY_RESULT::UNKNOWN, result );

	// 3. y <= -1 && x <= 1 (safe)
	badStateMat = Matrix::Zero( 2, 3 );
	badStateMat << 0, 1, 0, 1, 0, 0;
	badStateVec = Vector::Zero( 2 );
	badStateVec << -1, 1;

	automaton.setGlobalBadStates( { hypro::Condition<Number>( badStateMat, badStateVec ) } );
	analyzer = hypro::SingularAnalyzer<VPoly>(
		  automaton, hypro::Settings{ {}, { 0, hypro::tNumber( 4 ), hypro::tNumber( 0.01 ) }, {} } );
	result = analyzer.run();
	EXPECT_EQ( hypro::REACHABILITY_RESULT::SAFE, result );

	// two-dimensional HA with two locations
	automaton = createSingularHA3<Number>();

	// Get locations for local bad states
	hypro::Location<Number>* l0 = automaton.getLocation( "l0" );
	hypro::Location<Number>* l1 = automaton.getLocation( "l1" );

	std::map<const hypro::Location<Number>*, hypro::Condition<Number>> localBadStates;

	// 1. l0, y <= -4 (safe)
	badStateMat = Matrix::Zero( 1, 3 );
	badStateMat( 0, 1 ) = 1;
	badStateVec = -4 * Vector::Ones( 1 );
	hypro::Condition<Number> badState( badStateMat, badStateVec );
	localBadStates[l0] = badState;

	automaton.setLocalBadStates( localBadStates );
	analyzer = hypro::SingularAnalyzer<VPoly>(
		  automaton, hypro::Settings{ {}, { 5, hypro::tNumber( 10 ), hypro::tNumber( 0.01 ) }, {} } );
	result = analyzer.run();
	EXPECT_EQ( hypro::REACHABILITY_RESULT::SAFE, result );

	// 2. l1, y <= -2 (unsafe)
	badStateVec( 0 ) = 0;
	badState = hypro::Condition<Number>( badStateMat, badStateVec );
	localBadStates.clear();
	localBadStates[l1] = badState;

	automaton.setLocalBadStates( localBadStates );
	analyzer = hypro::SingularAnalyzer<VPoly>(
		  automaton, hypro::Settings{ {}, { 5, hypro::tNumber( 10 ), hypro::tNumber( 0.01 ) }, {} } );
	result = analyzer.run();
	EXPECT_EQ( hypro::REACHABILITY_RESULT::UNKNOWN, result );

	// 3. l1, x >= 3 (unsafe)
	badStateMat = Matrix::Zero( 1, 3 );
	badStateMat( 0, 0 ) = -1;
	badStateVec = -3 * Vector::Ones( 1 );
	badState = hypro::Condition<Number>( badStateMat, badStateVec );
	localBadStates.clear();
	localBadStates[l1] = badState;

	automaton.setLocalBadStates( localBadStates );
	analyzer = hypro::SingularAnalyzer<VPoly>(
		  automaton, hypro::Settings{ {}, { 5, hypro::tNumber( 10 ), hypro::tNumber( 0.01 ) }, {} } );
	result = analyzer.run();
	EXPECT_EQ( hypro::REACHABILITY_RESULT::UNKNOWN, result );
}