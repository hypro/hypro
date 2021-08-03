#include <gtest/gtest.h>
#include <hypro/algorithms/reachability/Reach.h>
#include <hypro/algorithms/reachability/analyzer/UrgencyAnalyzer.h>
#include <hypro/algorithms/reachability/analyzer/UrgencyCEGARAnalyzer.h>
#include <hypro/algorithms/reachability/handlers/urgencyHandlers/ltiUrgencyHandler.h>
#include <hypro/algorithms/reachability/workers/UrgencyWorker.h>
#include <hypro/datastructures/HybridAutomaton/HybridAutomaton.h>
#include <hypro/datastructures/reachability/Settings.h>
#include <hypro/representations/GeometricObjectBase.h>

#include "../defines.h"

using namespace hypro;
using Number = mpq_class;
using Matrix = matrix_t<Number>;
using Vector = vector_t<Number>;

template <typename Number>
HybridAutomaton<Number> ha3() {
	// One-dimensional HA with two locations
	using Matrix = matrix_t<Number>;
	using Vector = vector_t<Number>;

	HybridAutomaton<Number> res;

	// Create locations
	Location<Number> loc0;
	Location<Number> loc1;
	auto uniqueLoc0{ std::make_unique<Location<Number>>( loc0 ) };
	auto uniqueLoc1{ std::make_unique<Location<Number>>( loc1 ) };
	uniqueLoc0->setName( "l0" );
	uniqueLoc1->setName( "l1" );

	// Set flow x' = 1 in loc0
	Matrix flow0 = Matrix::Zero( 2, 2 );
	flow0( 0, 1 ) = 1;
	uniqueLoc0->setFlow( flow0 );

	// Set flow x' = 0 in loc1
	Matrix flow1 = Matrix::Zero( 2, 2 );
	uniqueLoc1->setFlow( flow1 );

	// Set invariant x <= 3 in loc0
	Matrix invariantConstraints = Matrix::Zero( 1, 1 );
	invariantConstraints( 0, 0 ) = 1;
	Vector invariantConstants = 3 * Vector::Ones( 1 );
	uniqueLoc0->setInvariant( { invariantConstraints, invariantConstants } );

	// Construct transitions
	// l0 -> l1 urgent with guard x >= 10
	Matrix transConstraint1 = Matrix::Zero( 1, 1 );
	Vector transConstants1 = -10 * Vector::Ones( 1 );
	transConstraint1( 0, 0 ) = -1;
	Condition<Number> guard1( transConstraint1, transConstants1 );
	Reset<Number> reset1{ Matrix::Ones( 1, 1 ), Vector::Zero( 1 ) };

	std::unique_ptr<Transition<Number>> trans1 =
		  std::make_unique<Transition<Number>>( uniqueLoc0.get(), uniqueLoc1.get(), guard1, reset1 );
	trans1->setUrgent();

	// l0 -> l1 urgent with guard x >= 1
	Matrix transConstraint2 = Matrix::Zero( 1, 1 );
	Vector transConstants2 = -1 * Vector::Ones( 1 );
	transConstraint2( 0, 0 ) = -1;
	Condition<Number> guard2( transConstraint2, transConstants2 );
	Reset<Number> reset2{ Matrix::Ones( 1, 1 ), Vector::Zero( 1 ) };

	std::unique_ptr<Transition<Number>> trans2 =
		  std::make_unique<Transition<Number>>( uniqueLoc0.get(), uniqueLoc1.get(), guard2, reset2 );
	trans2->setUrgent();

	// Set initial state x = 0, aff = 1 in loc0
	Matrix initialConstraints = Matrix::Zero( 2, 1 );
	Vector initialConstants = Vector::Zero( 2 );
	initialConstraints << 1, -1;
	initialConstants << 0, 0;

	// Create HA
	uniqueLoc0->addTransition( std::move( trans1 ) );
	uniqueLoc0->addTransition( std::move( trans2 ) );

	res.addLocation( std::move( uniqueLoc0 ) );
	res.addLocation( std::move( uniqueLoc1 ) );

	Location<Number>* loc0ptr = res.getLocation( "l0" );
	res.addInitialState( loc0ptr, Condition<Number>( initialConstraints, initialConstants ) );

	return res;
}

TEST( UrgencyHandling, Cutoff ) {
	ltiUrgencyHandler<VPolytope<Number>> urgencyHandler;
	Vector p1( 2 ), p2( 2 ), p3( 2 ), p4( 2 );
	p1 << 0, 0;
	p2 << 0, 1;
	p3 << 1, 0;
	p4 << 1, 1;
	VPolytope<Number> square( std::vector<Point<Number>>{ Point<Number>( p1 ), Point<Number>( p2 ), Point<Number>( p3 ),
														  Point<Number>( p4 ) } );

	Matrix mat = Matrix( 1, 2 );
	mat << -1, -1;
	Vector vec = Vector( 1 );
	vec << -1.5;

	Condition<Number> cond( mat, vec );
	auto res = urgencyHandler.cutoff( square, cond );

	Vector p5( 2 ), p6( 2 );
	p5 << 0.5, 1;
	p6 << 1, 0.5;
	VPolytope<Number> expectedRes( std::vector<Point<Number>>{
		  Point<Number>( p1 ), Point<Number>( p2 ), Point<Number>( p3 ), Point<Number>( p5 ), Point<Number>( p6 ) } );
	EXPECT_TRUE( res.contains( expectedRes ) );
	EXPECT_TRUE( expectedRes.contains( res ) );

	mat << 1, 1;
	vec << 1.5;
	cond.setMatrix( mat );
	cond.setVector( vec );
	res = urgencyHandler.cutoff( square, cond );

	expectedRes = VPolytope<Number>(
		  std::vector<Point<Number>>{ Point<Number>( p4 ), Point<Number>( p5 ), Point<Number>( p6 ) } );
	EXPECT_TRUE( expectedRes.contains( res ) );
	EXPECT_TRUE( res.contains( expectedRes ) );

	Vector q1( 3 ), q2( 3 ), q3( 3 ), q4( 3 ), q5( 3 ), q6( 3 ), q7( 3 ), q8( 3 );
	q1 << 0, 0, 0;
	q2 << 0, 0, 1;
	q3 << 0, 1, 0;
	q4 << 0, 1, 1;
	q5 << 1, 0, 0;
	q6 << 1, 0, 1;
	q7 << 1, 1, 0;
	q8 << 1, 1, 1;
	VPolytope<Number> cube( std::vector<Point<Number>>{ Point<Number>( q1 ), Point<Number>( q2 ), Point<Number>( q3 ),
														Point<Number>( q4 ), Point<Number>( q5 ), Point<Number>( q6 ),
														Point<Number>( q7 ), Point<Number>( q8 ) } );
	mat = Matrix( 2, 3 );
	mat << 0, -1, 0, 0, 0, -1;
	vec = Vector( 2 );
	vec << -0.5, -0.5;
	cond.setMatrix( mat );
	cond.setVector( vec );
	res = urgencyHandler.cutoff( cube, cond );

	Vector s1( 3 ), s2( 3 ), s3( 3 ), s4( 3 ), s5( 3 ), s6( 3 ), s7( 3 ), s8( 3 ), s9( 3 ), s10( 3 );
	s1 << 0, 0, 0;
	s2 << 0, 0, 1;
	s3 << 0, 1, 0;
	s4 << 0, 0.5, 1;
	s5 << 0, 1, 0.5;
	s6 << 1, 0, 0;
	s7 << 1, 0, 1;
	s8 << 1, 1, 0;
	s9 << 1, 0.5, 1;
	s10 << 1, 1, 0.5;
	expectedRes = VPolytope<Number>( std::vector<Point<Number>>{
		  Point<Number>( s1 ), Point<Number>( s2 ), Point<Number>( s3 ), Point<Number>( s4 ), Point<Number>( s5 ),
		  Point<Number>( s6 ), Point<Number>( s7 ), Point<Number>( s8 ), Point<Number>( s9 ), Point<Number>( s10 ) } );
	EXPECT_TRUE( expectedRes.contains( res ) );
	EXPECT_TRUE( res.contains( expectedRes ) );
}

// TEST( UrgencyReachabilityTest, Analysis ) {
//	auto automaton = ha4<Number>();
//	// Matrix badStateMat = -1 * Matrix::Ones( 1, 1 );
//	// Vector badStateVec = -2 * Vector::Ones( 1 );
//
//	// auto l1 = automaton.getLocation( "l1" );
//
//	// std::map<const Location<Number>*, Condition<Number>> localBadStates;
//	// Condition<Number> badState( badStateMat, badStateVec );
//	// localBadStates[l1] = badState;
//	// automaton.setLocalBadStates( localBadStates );
//
//	AnalysisParameters analysisParameters;
//	analysisParameters.timeStep = tNumber( 1 ) / tNumber( 10 );
//	analysisParameters.aggregation = AGG_SETTING::NO_AGG;
//	analysisParameters.representation_type = representation_name::box;
//	FixedAnalysisParameters fixedParams{ 5, tNumber( 3 ), tNumber( 0.1 ) };
//	UrgencyCEGARSettings us{};
//	us.refinementLevels = { UrgencyRefinementLevel::CUTOFF };
//	us.refineHalfspaces = true;
//	UrgencyCEGARAnalyzer<Box<Number>> analyzer( automaton, fixedParams,
// analysisParameters, us ); 	auto result = analyzer.run(); 	EXPECT_EQ(
// REACHABILITY_RESULT::SAFE, result.result() ); 	SUCCEED();
//}