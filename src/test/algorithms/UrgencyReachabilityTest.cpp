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

template <typename Number>
HybridAutomaton<Number> createHa() {
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

	// Set flow x' = 1, y' = 0 in loc0
	Matrix flow0 = Matrix::Zero( 3, 3 );
	flow0( 0, 2 ) = 1;
	uniqueLoc0->setFlow( flow0 );

	Matrix flow1 = Matrix::Zero( 3, 3 );
	uniqueLoc1->setFlow( flow1 );

	// Construct transitions
	// l0 -> l1 urgent with guard x <= 0.5 and y >= 0.5
	Matrix A1( 2, 2 );
	Vector b1( 2 );
	A1 << 1, 0, 0, -1;
	b1 << Number( 0.5 ), Number( -0.5 );

	Condition<Number> g1( A1, b1 );
	Reset<Number> r1{ Matrix::Identity( 2, 2 ), Vector::Zero( 2 ) };

	std::unique_ptr<Transition<Number>> t0 =
		  std::make_unique<Transition<Number>>( uniqueLoc0.get(), uniqueLoc1.get(), g1, r1 );
	t0->setUrgent();
	t0->addLabel( Label( "t0" ) );
	uniqueLoc0->addTransition( std::move( t0 ) );

	// l0 -> l1 urgent with guard x <= 2, x >= 1.5 and y >= 0.5
	Matrix A2 = Matrix( 3, 2 );
	Vector b2 = Vector( 3 );
	A2 << 1, 0, -1, 0, 0, -1;
	b2 << 2, -1.5, -0.5;
	Condition<Number> g2( A2, b2 );
	Reset<Number> r2{ Matrix::Identity( 2, 2 ), Vector::Zero( 2 ) };

	std::unique_ptr<Transition<Number>> t1 =
		  std::make_unique<Transition<Number>>( uniqueLoc0.get(), uniqueLoc1.get(), g2, r2 );
	t1->setUrgent();
	t1->addLabel( Label( "t1" ) );
	uniqueLoc0->addTransition( std::move( t1 ) );

	// Set initial state [0,1] x [0,1] in loc0
	Matrix initialConstraints = Matrix( 4, 2 );
	Vector initialConstants = Vector( 4 );
	initialConstraints << 1, 0, -1, 0, 0, 1, 0, -1;
	initialConstants << 1, 0, 1, 0;

	// Create HA
	res.addLocation( std::move( uniqueLoc0 ) );
	res.addLocation( std::move( uniqueLoc1 ) );
	res.addInitialState( res.getLocation( "l0" ), Condition<Number>( initialConstraints, initialConstants ) );

	return res;
}

template <typename Representation>
class UrgencyCEGARReachabilityTest : public ::testing::Test {
  protected:
	virtual void setUp() {}
	virtual void tearDown() {}
};

TEST( UrgencyHandling, Cutoff ) {
	using Number = mpq_class;
	using Matrix = matrix_t<Number>;
	using Vector = vector_t<Number>;

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

TYPED_TEST( UrgencyCEGARReachabilityTest, TimeElapse ) {
	using Representation = TypeParam;
	using Number = typename Representation::NumberType;
	using Vector = vector_t<Number>;
	auto automaton = createHa<Number>();

	auto l0 = automaton.getLocation( "l0" );
	Transition<Number>*t0, *t1;
	for ( auto const& t : l0->getTransitions() ) {
		if ( t->getLabels()[0].getName() == "t0" ) t0 = t.get();
		if ( t->getLabels()[0].getName() == "t1" ) t1 = t.get();
	}

	Representation initialSet( automaton.getInitialStates().at( l0 ).getMatrix(),
							   automaton.getInitialStates().at( l0 ).getVector() );

	AnalysisParameters analysisParameters;
	analysisParameters.timeStep = tNumber( 1 ) / tNumber( 10 );
	analysisParameters.representation_type = Representation::type();

	TimeTransformationCache<Number> cache{};
	UrgencyWorker<Representation> worker( automaton, analysisParameters, 10, cache );
	ReachTreeNode<Representation> node( l0, initialSet, carl::Interval<SegmentInd>( 0 ) );

	node.getUrgent()[t0] = UrgencyRefinementLevel::SETDIFF;
	worker.computeTimeSuccessors( node );

	auto flowpipe = worker.getFlowpipe();
	// first set is initial set
	EXPECT_TRUE( initialSet == flowpipe[0].valuationSet );
	// first segment should be split
	EXPECT_TRUE( std::count_if( flowpipe.begin(), flowpipe.end(),
								[]( auto indexedSegment ) { return indexedSegment.index == 0; } ) > 2 );

	// test points
	Vector c1( 2 ), c2( 2 ), c3( 2 );
	Vector n1( 2 ), n2( 2 ), n3( 2 );
	c1 << 0.25, 0.25;
	c2 << 0.75, 0.25;
	c3 << 0.75, 0.75;
	n1 << 0.25, 0.75;
	n2 << 0, 0.75;
	n3 << 0.25, 1;
	bool found1 = false, found2 = false, found3 = false;
	// first segment is initial set without set difference, so it is skipped
	for ( std::size_t i = 1; i < flowpipe.size(); ++i ) {
		if ( flowpipe[i].index > 0 ) break;
		if ( flowpipe[i].valuationSet.contains( Point<Number>( c1 ) ) ) found1 = true;
		if ( flowpipe[i].valuationSet.contains( Point<Number>( c2 ) ) ) found2 = true;
		if ( flowpipe[i].valuationSet.contains( Point<Number>( c3 ) ) ) found3 = true;
	}
	EXPECT_TRUE( found1 );
	EXPECT_TRUE( found2 );
	EXPECT_TRUE( found3 );

	Vector c4( 2 );
	c4 << 1.75, 0.75;
	bool found4 = false;
	// first segment is initial set without set difference, so it is skipped
	for ( std::size_t i = 1; i < flowpipe.size(); ++i ) {
		EXPECT_FALSE( flowpipe[i].valuationSet.contains( Point<Number>( n1 ) ) );
		EXPECT_FALSE( flowpipe[i].valuationSet.contains( Point<Number>( n2 ) ) );
		EXPECT_FALSE( flowpipe[i].valuationSet.contains( Point<Number>( n3 ) ) );
		if ( flowpipe[i].valuationSet.contains( Point<Number>( c4 ) ) ) found4 = true;
	}
	EXPECT_TRUE( found4 );

	node.getUrgent()[t1] = UrgencyRefinementLevel::SETDIFF;
	worker.reset();
	worker.computeTimeSuccessors( node );
	flowpipe = worker.getFlowpipe();
	for ( std::size_t i = 1; i < flowpipe.size(); ++i ) {
		if ( flowpipe[i].valuationSet.contains( Point<Number>( c4 ) ) ) {
			std::cout << i << ": " << flowpipe[i].valuationSet << "\n";
		}
		EXPECT_FALSE( flowpipe[i].valuationSet.contains( Point<Number>( c4 ) ) );
	}
}
