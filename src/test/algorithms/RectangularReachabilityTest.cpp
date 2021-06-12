#include "../defines.h"
#include "automata/automataCreation.h"
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

template <typename T>
class RectangularReachabilityTest : public testing::Test {
  protected:
	virtual void SetUp() {}
	virtual void TearDown() {}

  public:
};

/// Tests whether a point is contained in a flowpipe segment
template <typename Representation>
bool is_reachable_in( const hypro::Point<typename Representation::NumberType>& sample, const Representation& segment ) {
	return segment.contains( sample );
}

/// Tests whether a point is contained in a flowpipe
template <typename Representation>
bool is_reachable_in( const hypro::Point<typename Representation::NumberType>& sample,
					  const std::vector<Representation>& flowpipe ) {
	return std::any_of( flowpipe.begin(), flowpipe.end(),
						[&]( const auto& segment ) { return is_reachable_in( sample, segment ); } );
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
	flow = Interval{ 0, 1 };
	fMap[hypro::VariablePool::getInstance().carlVarByIndex( 0 )] = flow;
	loc2->setFlow( { hypro::rectangularFlow<Number>{ fMap } } );
	loc2->setInvariant( { invariantConstraints, invariantConstants } );

	// Add transition from first to second location with no guard and no reset
	loc->createTransition( loc2 );

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

	hypro::Transition<Number>* trans0 = loc0->createTransition( loc0 );
	trans0->setGuard( guard );
	trans0->setReset( reset );

	// l0 -> l1 with guard y <= -2 and no reset
	transConstraint = Matrix::Zero( 1, 2 );
	transConstants = -2 * Vector::Ones( 1 );
	transConstraint( 0, 1 ) = 1;
	guard = hypro::Condition<Number>( transConstraint, transConstants );
	reset = hypro::Reset<Number>( { carl::Interval<Number>(), carl::Interval<Number>() } );

	hypro::Transition<Number>* trans1 = loc0->createTransition( loc1 );
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

TYPED_TEST( RectangularReachabilityTest, WorkerConstruction ) {
	auto [automaton, reachable_points, non_reachable_points] =
		  hypro::testing::createRectangularHA<typename TypeParam::NumberType>();

	hypro::AnalysisParameters analysisParameters;
	analysisParameters.timeStep = hypro::tNumber( 1 ) / hypro::tNumber( 100 );
	analysisParameters.aggregation = hypro::AGG_SETTING::AGG;
	analysisParameters.representation_type = hypro::representation_name::polytope_v;

	hypro::Settings settings{ {},
							  hypro::FixedAnalysisParameters{ 5, hypro::tNumber( 4 ), hypro::tNumber( 0.01 ) },
							  { analysisParameters } };

	auto worker = hypro::RectangularWorker<TypeParam>( automaton, settings );
	SUCCEED();
}

TYPED_TEST( RectangularReachabilityTest, ReacherConstruction ) {
	using Number = typename TypeParam::NumberType;

	auto [automaton, reachable_points, non_reachable_points] = hypro::testing::createRectangularHA<Number>();
	auto roots = hypro::makeRoots<TypeParam, Number>( automaton );

	hypro::AnalysisParameters analysisParameters;
	analysisParameters.timeStep = hypro::tNumber( 1 ) / hypro::tNumber( 100 );
	analysisParameters.aggregation = hypro::AGG_SETTING::AGG;
	analysisParameters.representation_type = hypro::representation_name::polytope_v;

	hypro::Settings settings{ {},
							  hypro::FixedAnalysisParameters{ 5, hypro::tNumber( 4 ), hypro::tNumber( 0.01 ) },
							  { analysisParameters } };

	auto reach = hypro::reachability::ReachBase<TypeParam, hypro::RectangularAnalyzer<TypeParam>>( automaton, settings,
																								   roots );
	SUCCEED();
}

TYPED_TEST( RectangularReachabilityTest, ComputeReachability1 ) {
	using Number = typename TypeParam::NumberType;

	auto [automaton, reachable_points, non_reachable_points] = hypro::testing::createRectangularHA<Number>();
	auto roots = hypro::makeRoots<TypeParam, Number>( automaton );
	EXPECT_EQ( std::size_t( 1 ), roots.size() );

	hypro::AnalysisParameters analysisParameters;
	analysisParameters.timeStep = hypro::tNumber( 1 ) / hypro::tNumber( 100 );
	analysisParameters.aggregation = hypro::AGG_SETTING::AGG;
	analysisParameters.representation_type = hypro::representation_name::polytope_v;

	hypro::Settings settings{ {},
							  hypro::FixedAnalysisParameters{ 5, hypro::tNumber( 4 ), hypro::tNumber( 0.01 ) },
							  { analysisParameters } };

	auto reach = hypro::reachability::ReachBase<TypeParam, hypro::RectangularAnalyzer<TypeParam>>( automaton, settings,
																								   roots );

	// call verifier, validate result
	auto reachabilityResult = reach.computeForwardReachability();
	EXPECT_EQ( hypro::REACHABILITY_RESULT::SAFE, reachabilityResult );

	// validate computed flowpipes
	std::vector<TypeParam> flowpipes;
	std::for_each( roots.begin(), roots.end(), [&]( auto& root ) {
		auto fp = getFlowpipes( root );
		std::for_each( fp.begin(), fp.end(), [&]( const auto& flowpipe ) {
			flowpipes.insert( flowpipes.end(), flowpipe.begin(), flowpipe.end() );
		} );
	} );

	std::for_each( flowpipes.begin(), flowpipes.end(),
				   [&]( const auto& segment ) { std::cout << "segment: " << segment << std::endl; } );

	// checks
	EXPECT_EQ( std::size_t( 1 ), flowpipes.size() );
	for ( const auto& p : reachable_points ) {
		EXPECT_TRUE( is_reachable_in( p, flowpipes ) );
	}

	for ( const auto& p : non_reachable_points ) {
		EXPECT_FALSE( is_reachable_in( p, flowpipes ) );
	}
}

TYPED_TEST( RectangularReachabilityTest, ComputeReachabilityWithJumps ) {
	using Number = typename TypeParam::NumberType;

	auto automaton = createRectangularHA2<Number>();
	auto roots = hypro::makeRoots<TypeParam, Number>( automaton );
	EXPECT_EQ( std::size_t( 1 ), roots.size() );

	hypro::AnalysisParameters analysisParameters;
	analysisParameters.timeStep = hypro::tNumber( 1 ) / hypro::tNumber( 100 );
	analysisParameters.aggregation = hypro::AGG_SETTING::AGG;
	analysisParameters.representation_type = hypro::representation_name::polytope_v;

	hypro::Settings settings{ {},
							  hypro::FixedAnalysisParameters{ 5, hypro::tNumber( 4 ), hypro::tNumber( 0.01 ) },
							  { analysisParameters } };

	auto reach = hypro::reachability::ReachBase<TypeParam, hypro::RectangularAnalyzer<TypeParam>>( automaton, settings,
																								   roots );

	// call verifier, validate result
	auto reachabilityResult = reach.computeForwardReachability();
	EXPECT_EQ( hypro::REACHABILITY_RESULT::SAFE, reachabilityResult );

	// validate computed flowpipes
	std::vector<TypeParam> flowpipes;
	std::for_each( roots.begin(), roots.end(), [&]( auto& root ) {
		auto fp = getFlowpipes( root );
		std::for_each( fp.begin(), fp.end(), [&]( const auto& flowpipe ) {
			flowpipes.insert( flowpipes.end(), flowpipe.begin(), flowpipe.end() );
		} );
	} );

	std::for_each( flowpipes.begin(), flowpipes.end(),
				   [&]( const auto& segment ) { std::cout << "segment: " << segment << std::endl; } );

	// checks
	EXPECT_EQ( std::size_t( 2 ), flowpipes.size() );
	EXPECT_TRUE( is_reachable_in( Point{ 0 }, flowpipes ) );  // initial set, also in loc 2
	EXPECT_TRUE( is_reachable_in( Point{ 8 }, flowpipes ) );  // maximal time elapse loc 1
	EXPECT_FALSE( is_reachable_in( Point{ -0.1 }, flowpipes ) );
	EXPECT_TRUE( is_reachable_in( Point{ 10 }, flowpipes ) );  // maximal time elapse loc 2
	EXPECT_FALSE( is_reachable_in( Point{ 10.1 }, flowpipes ) );
	EXPECT_FALSE( flowpipes[0].contains( Point{ 8.1 } ) );
}

TYPED_TEST( RectangularReachabilityTest, ComputeReachabilityWithJumpsTwoDimensions ) {
	using Number = typename TypeParam::NumberType;

	auto automaton = createRectangularHA3<Number>();
	auto roots = hypro::makeRoots<TypeParam, Number>( automaton );
	EXPECT_EQ( std::size_t( 1 ), roots.size() );

	hypro::AnalysisParameters analysisParameters;
	analysisParameters.timeStep = hypro::tNumber( 1 ) / hypro::tNumber( 100 );
	analysisParameters.aggregation = hypro::AGG_SETTING::AGG;
	analysisParameters.representation_type = hypro::representation_name::polytope_v;

	hypro::Settings settings{ {},
							  hypro::FixedAnalysisParameters{ 5, hypro::tNumber( 4 ), hypro::tNumber( 0.01 ) },
							  { analysisParameters } };

	auto reach = hypro::reachability::ReachBase<TypeParam, hypro::RectangularAnalyzer<TypeParam>>( automaton, settings,
																								   roots );

	// call verifier, validate result
	auto reachabilityResult = reach.computeForwardReachability();
	EXPECT_EQ( hypro::REACHABILITY_RESULT::SAFE, reachabilityResult );

	// validate computed flowpipes
	std::vector<TypeParam> flowpipes;
	std::for_each( roots.begin(), roots.end(), [&]( auto& root ) {
		auto fp = getFlowpipes( root );
		std::for_each( fp.begin(), fp.end(), [&]( const auto& flowpipe ) {
			flowpipes.insert( flowpipes.end(), flowpipe.begin(), flowpipe.end() );
		} );
	} );

	std::for_each( flowpipes.begin(), flowpipes.end(),
				   [&]( const auto& segment ) { std::cout << "segment: " << segment << std::endl; } );

	// checks
	EXPECT_EQ( std::size_t( 11 ), flowpipes.size() );
	EXPECT_TRUE( is_reachable_in( Point{ 0, 0 }, flowpipes ) );	 // initial set
	EXPECT_TRUE( is_reachable_in( Point{ 3, -3 }, flowpipes ) );
	EXPECT_TRUE( is_reachable_in( Point{ 2, -2 }, flowpipes ) );
	EXPECT_TRUE( is_reachable_in( Point{ 2, -6 }, flowpipes ) );
	EXPECT_TRUE( is_reachable_in( Point{ 3, -7 }, flowpipes ) );

	EXPECT_FALSE( is_reachable_in( Point{ 3, -7.1 }, flowpipes ) );
	EXPECT_FALSE( is_reachable_in( Point{ 2, -6.1 }, flowpipes ) );
	EXPECT_FALSE( is_reachable_in( Point{ 3, -2.9 }, flowpipes ) );
	EXPECT_FALSE( is_reachable_in( Point{ 2, -1.9 }, flowpipes ) );
}

TYPED_TEST( RectangularReachabilityTest, BackwardsTimeComputation ) {
	using Number = typename TypeParam::NumberType;
	using Matrix = typename hypro::matrix_t<Number>;
	using Vector = typename hypro::vector_t<Number>;
	using Point = typename hypro::Point<Number>;
	auto ha = createRectangularHA3<Number>();

	// the automaton returned is actually a singular automaton. Update the flow for loc1 to a truly rectangular dynamics
	auto l1ptr = ha.getLocation( "l1" );
	EXPECT_TRUE( l1ptr != nullptr );
	std::map<carl::Variable, carl::Interval<Number>> fmap;
	carl::Interval<Number> flowx = carl::Interval<Number>{ 1, 1 };
	carl::Interval<Number> flowy = carl::Interval<Number>{ 1, 2 };
	fmap[hypro::VariablePool::getInstance().carlVarByIndex( 0 )] = flowx;
	fmap[hypro::VariablePool::getInstance().carlVarByIndex( 1 )] = flowy;
	l1ptr->setFlow( { hypro::rectangularFlow<Number>{ fmap } } );

	// to make results observable, also make the invariant a unit box scaled by 10
	Matrix inv_constraints = Matrix::Zero( 4, 2 );
	inv_constraints( 0, 0 ) = 1;
	inv_constraints( 1, 0 ) = -1;
	inv_constraints( 2, 1 ) = 1;
	inv_constraints( 3, 1 ) = -1;
	Vector inv_constants = Vector( 4 );
	inv_constants << 10, 10, 10, 10;
	l1ptr->setInvariant( { inv_constraints, inv_constants } );

	hypro::AnalysisParameters analysisParameters;
	analysisParameters.timeStep = hypro::tNumber( 1 ) / hypro::tNumber( 100 );
	analysisParameters.aggregation = hypro::AGG_SETTING::AGG;
	analysisParameters.representation_type = hypro::representation_name::polytope_h;

	hypro::Settings settings{ {},
							  hypro::FixedAnalysisParameters{ 5, hypro::tNumber( 4 ), hypro::tNumber( 0.01 ) },
							  { analysisParameters } };

	auto worker = hypro::RectangularWorker<TypeParam>( ha, settings );

	// Create initial set (unit box)
	Matrix constraints = Matrix::Zero( 4, 2 );
	constraints( 0, 0 ) = 1;
	constraints( 1, 0 ) = -1;
	constraints( 2, 1 ) = 1;
	constraints( 3, 1 ) = -1;
	Vector constants = Vector( 4 );
	constants << 1, 1, 1, 1;
	TypeParam initialSet{ constraints, constants };
	// Create timings (dummy)
	auto timings = carl::Interval<hypro::SegmentInd>{ 0, 2 };

	// Create artificial task for backwards analysis
	hypro::ReachTreeNode<TypeParam> taskNode{ l1ptr, initialSet, timings };

	auto result = worker.computeTimePredecessors( taskNode );
	EXPECT_TRUE( result == hypro::REACHABILITY_RESULT::SAFE );
	EXPECT_TRUE( worker.getFlowpipe().size() >= std::size_t( 1 ) );
	const auto& segment{ worker.getFlowpipe().front() };
	std::cout << "Computed segment: " << segment << std::endl;
	auto& plt = hypro::Plotter<Number>::getInstance();
	plt.addObject( segment.vertices() );
	plt.setFilename( "backwards_computation" );
	plt.plot2d( hypro::PLOTTYPE::png );
	plt.clear();
	EXPECT_TRUE( segment.contains( initialSet ) );
	// check containment of expected vertices in the flowpipe. The initial set is the unit box, the flow is -1 in x and
	// [1,2] in y. The invariant is the scaled unit box by factor 10. The resulting vertices will be tested.
	// vertices of the initial set:
	EXPECT_TRUE( segment.contains( Point{ 1, 1 } ) );
	EXPECT_TRUE( segment.contains( Point{ -1, 1 } ) );
	EXPECT_TRUE( segment.contains( Point{ 1, -1 } ) );
	EXPECT_TRUE( segment.contains( Point{ -1, -1 } ) );
	// additional vertices of the time successors
	EXPECT_TRUE( segment.contains( Point{ -10, -10 } ) );
	EXPECT_TRUE( segment.contains( Point{ -10, -8 } ) );
	EXPECT_TRUE( segment.contains( Point{ -3.5, -10 } ) );
	// check some points close to the set which should not be contained
	EXPECT_FALSE( segment.contains( Point{ -1, 1.1 } ) );
	EXPECT_FALSE( segment.contains( Point{ 1, 1.1 } ) );
	EXPECT_FALSE( segment.contains( Point{ 1.1, 1 } ) );
	EXPECT_FALSE( segment.contains( Point{ 1.1, -1 } ) );
	EXPECT_FALSE( segment.contains( Point{ -3.5, -10.1 } ) );
	EXPECT_FALSE( segment.contains( Point{ -3.4, -10 } ) );
	EXPECT_FALSE( segment.contains( Point{ -10, -7.9 } ) );
}