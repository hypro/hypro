/**
 * TemplatePolyhedronContextTest.cpp
 *
 * Test suite for TemplatePolyhedronContext.tpp and all the handlers it entails:
 * TPolyFirstSegmentHandler, TPolyContinuousEvolutionHandler
 *
 * NOTE: Since ReachTreeNodes cannot be copied or copy assigned, everything that one needs
 * to create a TemplatePolyhedronContext i.e. the State, the ReachTreeNode, the task and the context itself
 * is constructed again in every test case.
 *
 * @author Phillip Tse
 * @date 30.9.2019
 */

#include "../../hypro/algorithms/reachability/contexts/TemplatePolyhedronContext.h"
#include "../../hypro/datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../hypro/representations/GeometricObject.h"
#include "../defines.h"
#include "gtest/gtest.h"

using namespace hypro;

// Settings structs with fitting template contents
struct OnlyInit : TemplatePolyhedronDefault {
	static constexpr TEMPLATE_CONTENT TEMPLATE_SHAPE = TEMPLATE_CONTENT::ONLY_INIT;
};
struct InitInv : TemplatePolyhedronDefault {
	static constexpr TEMPLATE_CONTENT TEMPLATE_SHAPE = TEMPLATE_CONTENT::INIT_INV;
};
struct InitInvGuard : TemplatePolyhedronDefault {
	static constexpr TEMPLATE_CONTENT TEMPLATE_SHAPE = TEMPLATE_CONTENT::INIT_INV_GUARD;
};
struct InitInvGuardBad : TemplatePolyhedronDefault {
	static constexpr TEMPLATE_CONTENT TEMPLATE_SHAPE = TEMPLATE_CONTENT::INIT_INV_GUARD_BAD;
};
struct Octagon : TemplatePolyhedronDefault {
	static constexpr TEMPLATE_CONTENT TEMPLATE_SHAPE = TEMPLATE_CONTENT::OCTAGON;
};

template <typename Number>
using TPoly = TemplatePolyhedronT<Number, hypro::Converter<Number>, TemplatePolyhedronDefault>;

template <typename Number>
class TemplatePolyhedronContextTest : public ::testing::Test {
  protected:
	virtual void SetUp() {
		// Initialize Location with unbounded invariants
		flow = matrix_t<Number>::Zero( 3, 3 );
		flow << 3, 2, 1,  // affine flow, should grow into infinity
			  0, -2, -1,  // linear flow, should grow into -infinity
			  0, 0, 0;
		invMat = -matrix_t<Number>::Identity( 2, 2 );
		invVec = 10 * vector_t<Number>::Ones( 2 );
		inv = Condition<Number>( invMat, invVec );	// x >= -10 && y >= -10
		loc = Location<Number>( flow );
		loc.setInvariant( inv );
		loc.setName( "loc" );

		// Initialize tpoly - is a triangle with corner points (0,0,)(2,1)(4,0)//(0,0),(1,2),(2,0)
		mat = matrix_t<Number>::Zero( 3, 2 );
		mat << -2, 1, 2, 1, 0, -1;
		vec = vector_t<Number>::Zero( 3 );
		vec << 0, 2, 0;
		tpoly = TPoly<Number>( mat, vec );

		// Initialize Location with positive invariant
		// NOTE: trappingFlow will eventually direct everything to (0,0)
		trappingFlow = matrix_t<Number>::Zero( 3, 3 );
		trappingFlow << 0.5, 0, 0,	// shrinks x every timestep, never reaching 0
			  0, 0.5, 0,			// shrinks y every timestep, never reaching 0
			  0, 0, 0;
		triangleInvMat = mat;
		triangleInvVec = vec;
		triangleInvVec( 1 ) = 4;
		triangleInv =
			  Condition<Number>( triangleInvMat, triangleInvVec );	// triangle with corner points (0,0),(2,4),(4,0)
		trappingLoc = Location<Number>( trappingFlow );
		trappingLoc.setInvariant( triangleInv );
		trappingLoc.setName( "trappingLoc" );

		growingFlow = matrix_t<Number>::Zero( 3, 3 );
		growingFlow << 3, 2, 1,	 // affine flow, should grow into infinity
			  3, 2, 1,			 // linear flow, should grow into -infinity
			  0, 0, 0;
		/*
				//Needed to initialize task
				//state = State_t<Number>(tpoly);
				//state.setLocation(&loc);
				state = State_t<Number>(&loc);
				state.setSet(tpoly,0);
				rnode = ReachTreeNode<State_t<Number>>(state,0);
				task = std::make_shared<Task<State_t<Number>>>(&rnode);
		*/
		// Initialize tpcontext
		strat = Strategy<State_t<Number>>();
		localQueue = nullptr;
		localCEXQueue = nullptr;
		localSegments = Flowpipe<State_t<Number>>();
		settings = ReachabilitySettings();
		// tpcontext = TemplatePolyhedronContext<State_t<Number>>(task,strat,localQueue,localCEXQueue,settings);
	}

	virtual void TearDown() {}

	// Location members - Needed to create State
	matrix_t<Number> flow;
	matrix_t<Number> invMat;
	vector_t<Number> invVec;
	Condition<Number> inv;
	Location<Number> loc;

	// Trapping location as location with positive invariant
	matrix_t<Number> trappingFlow;
	matrix_t<Number> triangleInvMat;
	vector_t<Number> triangleInvVec;
	Condition<Number> triangleInv;
	Location<Number> trappingLoc;

	matrix_t<Number> growingFlow;

	// Empty Location
	Location<Number> emptyLoc;

	// Template Polyhedron members - Needed to create State
	matrix_t<Number> mat;
	vector_t<Number> vec;
	TemplatePolyhedronT<Number, hypro::Converter<Number>, TemplatePolyhedronDefault> tpoly;

	// Needed to create Task
	// State_t<Number> state;
	// ReachTreeNode<State_t<Number>> rnode;
	// std::shared_ptr<Task<State_t<Number>>> task;

	// Needed to create tpcontext
	Strategy<State_t<Number>> strat;
	WorkQueue<std::shared_ptr<Task<State_t<Number>>>>* localQueue;
	WorkQueue<std::shared_ptr<Task<State_t<Number>>>>* localCEXQueue;
	Flowpipe<State_t<Number>> localSegments;
	ReachabilitySettings settings;

	// The thing we want to test
	// TemplatePolyhedronContext<State_t<Number>> tpcontext;
};

TYPED_TEST( TemplatePolyhedronContextTest, GradientOfLinearFunction ) {
	// Initialize tpcontext
	// NOTE: This must be copied into every test since ReachTreeNodes cannot be copy assigned and therefore cannot be a
	// member of the test
	State_t<TypeParam> state( &( this->loc ) );
	state.setSet( this->tpoly, 0 );
	ReachTreeNode<State_t<TypeParam>> rnode( state, (unsigned)0 );
	auto task = std::make_shared<Task<State_t<TypeParam>>>( &rnode );
	TemplatePolyhedronContext<State_t<TypeParam>> tpcontext( task, this->strat, this->localQueue, this->localCEXQueue,
															 this->localSegments, this->settings );

	// Zero function - Given the vector (0,0,0), so the function f = 0*x + 0*y + 0, the gradient is (df/dx, df/dy, 0)
	// and thus (0,0,0) NOTE: the last 0 is just an extension needed for the other computations within
	// TemplatePolyhedronContext
	vector_t<TypeParam> zeroFunction = vector_t<TypeParam>::Zero( 3 );
	EXPECT_EQ( tpcontext.gradientOfLinearFct( zeroFunction ), zeroFunction );

	// Constant fct
	vector_t<TypeParam> testFunction = zeroFunction;
	testFunction( 2 ) = TypeParam( 1000 );
	EXPECT_EQ( tpcontext.gradientOfLinearFct( testFunction ), zeroFunction );

	// multivariate linear fct
	testFunction << 100, 200, 300;
	auto res = tpcontext.gradientOfLinearFct( testFunction );
	EXPECT_EQ( res( 0 ), testFunction( 0 ) );
	EXPECT_EQ( res( 1 ), testFunction( 1 ) );
	EXPECT_EQ( res( 2 ), 0 );
}

TYPED_TEST( TemplatePolyhedronContextTest, LieDerivative ) {
	// Initialize tpcontext
	// NOTE: This must be copied into every test since ReachTreeNodes cannot be copy assigned and therefore cannot be a
	// member of the test
	State_t<TypeParam> state( &( this->loc ) );
	state.setSet( this->tpoly, 0 );
	ReachTreeNode<State_t<TypeParam>> rnode( state, (unsigned)0 );
	auto task = std::make_shared<Task<State_t<TypeParam>>>( &rnode );
	TemplatePolyhedronContext<State_t<TypeParam>> tpcontext( task, this->strat, this->localQueue, this->localCEXQueue,
															 this->localSegments, this->settings );

	// Zero function
	vector_t<TypeParam> zeroFunction = vector_t<TypeParam>::Zero( 2 );
	EXPECT_EQ( tpcontext.lieDerivative( zeroFunction ).first, zeroFunction );
	EXPECT_EQ( tpcontext.lieDerivative( zeroFunction ).second, 0 );

	// Constant function - Not possible right now since we extend the given function within the lieDerivative() function

	// Multivariate linear fct
	vector_t<TypeParam> testFunction = zeroFunction;
	testFunction << 1, 2;
	auto res = tpcontext.lieDerivative( testFunction );
	EXPECT_EQ( res.first( 0 ), 3 );
	EXPECT_EQ( res.first( 1 ), -2 );
	EXPECT_EQ( res.second, -1 );
}

TYPED_TEST( TemplatePolyhedronContextTest, PositiveInvariant ) {
	// Test with empty loc fails since one cannot extract a non existent invariant

	// Test 1: Test with positive invariant
	// Initialize tpcontext with positive invariant flow
	State_t<TypeParam> state( &( this->trappingLoc ) );
	state.setSet( this->tpoly, 0 );
	ReachTreeNode<State_t<TypeParam>> rnodeTrapping( state, (unsigned)0 );
	auto taskTrapping = std::make_shared<Task<State_t<TypeParam>>>( &rnodeTrapping );
	TemplatePolyhedronContext<State_t<TypeParam>> tpcontextTrapping(
		  taskTrapping, this->strat, this->localQueue, this->localCEXQueue, this->localSegments, this->settings );

	// Overapproximate positive invariant
	TPoly<TypeParam> tpolyTrap( this->trappingLoc.getInvariant().getMatrix(),
								this->trappingLoc.getInvariant().getVector() );
	EXPECT_TRUE( tpolyTrap.isBounded() );
	tpolyTrap = tpolyTrap.overapproximate( this->tpoly.matrix() );

	// Test whether positive invariant with positive invariant
	EXPECT_TRUE( tpcontextTrapping.isRelaxedInvariant( this->tpoly, tpolyTrap.vector() ) );

	// Test 2: Test with non positive invariant
	// Initialize tpcontext with not positive invariant flow
	this->loc.setFlow( this->growingFlow );
	this->loc.setInvariant( Condition<TypeParam>( this->triangleInvMat, this->triangleInvVec ) );
	state.setLocation( &( this->loc ) );
	ReachTreeNode<State_t<TypeParam>> rnode( state, (unsigned)0 );
	auto task = std::make_shared<Task<State_t<TypeParam>>>( &rnode );
	TemplatePolyhedronContext<State_t<TypeParam>> tpcontext( task, this->strat, this->localQueue, this->localCEXQueue,
															 this->localSegments, this->settings );
	/*
		//Overapproximate non positive invariant
		auto widenedTriangleVec = 5*vector_t<TypeParam>::Ones(3);
		TPoly<TypeParam> tpolyNoTrap(this->triangleInvMat,widenedTriangleVec);
		tpolyNoTrap = tpolyNoTrap.overapproximate(this->tpoly.matrix());
		EXPECT_TRUE(tpolyNoTrap.isBounded());
		std::cout << "state: " << state << "tpolyNoTrap: " << tpolyNoTrap << "tpoly: " << this->tpoly << std::endl;

		//Test whether positive invariant with non positive invariant
		EXPECT_FALSE(tpcontext.isPositiveInvariant(this->tpoly, tpolyNoTrap.vector()));
	*/
}

TYPED_TEST( TemplatePolyhedronContextTest, CreateTemplateContent ) {
	// Build new badstate
	matrix_t<TypeParam> badstateFlow = matrix_t<TypeParam>::Identity( 3, 3 );
	badstateFlow( 2, 2 ) = TypeParam( 0 );
	Location<TypeParam> badstate( badstateFlow );
	matrix_t<TypeParam> lBadstateMat = matrix_t<TypeParam>::Zero( 1, 2 );
	lBadstateMat << -2, 0;
	vector_t<TypeParam> lBadstateVec = -5 * vector_t<TypeParam>::Ones( 1 );

	// Global badstate
	matrix_t<TypeParam> gBadstateMat = matrix_t<TypeParam>::Zero( 2, 2 );
	gBadstateMat << 2, 0, -2, 0;
	vector_t<TypeParam> gBadstateVec = -5 * vector_t<TypeParam>::Ones( 2 );
	std::vector<Condition<TypeParam>> gBadstate{ Condition<TypeParam>( gBadstateMat, gBadstateVec ) };

	// Add transition from loc to badstate
	matrix_t<TypeParam> guardMat = matrix_t<TypeParam>::Zero( 2, 2 );
	guardMat << -1, 0, -1, -1;
	vector_t<TypeParam> guardVec = -2 * vector_t<TypeParam>::Ones( 2 );
	auto trans = std::make_unique<Transition<TypeParam>>( &( this->loc ), &( badstate ) );
	trans->setGuard( Condition<TypeParam>( guardMat, guardVec ) );
	this->loc.addTransition( std::move( trans ) );

	// Initialize tpcontext
	// NOTE: This must be copied into every test since ReachTreeNodes cannot be copy assigned and therefore cannot be a
	// member of the test
	State_t<TypeParam> state( &( this->loc ) );
	state.setSet( this->tpoly, 0 );
	ReachTreeNode<State_t<TypeParam>> rnode( state, (unsigned)0 );
	auto task = std::make_shared<Task<State_t<TypeParam>>>( &rnode );
	TemplatePolyhedronContext<State_t<TypeParam>> tpcontext( task, this->strat, this->localQueue, this->localCEXQueue,
															 this->localSegments, this->settings );

	// For each custom settings struct, check if the resulting matrix is the right one
	using T = TypeParam;
	using C = Converter<TypeParam>;

	// Test case: only initial constraints
	// Result: nothing should change
	TemplatePolyhedronT<T, C, OnlyInit> testPoly( this->tpoly );
	// std::cout << "CreateTemplateContentTest, testPoly: \n"
	//		  << testPoly << "createTContent: \n"
	//		  << tpcontext.createTemplateContent( testPoly ) << std::endl;
	EXPECT_EQ( tpcontext.createTemplateContent( testPoly ), testPoly );

	// Test case: initial constraints and invariants,
	// Result: 1 of 2 invariants should be added and the one added should be corrected from x >= -10 to x >= 0
	auto testPoly2 = TemplatePolyhedronT<T, C, InitInv>( this->tpoly );
	matrix_t<T> controlMat = matrix_t<T>::Zero( 4, 2 );
	controlMat << -2, 1, 2, 1, 0, -1, -1, 0;
	vector_t<T> controlVec = vector_t<T>::Zero( 4 );
	controlVec << 0, 2, 0, 0;
	TemplatePolyhedronT<T, C, InitInv> controlPoly2( controlMat, controlVec );
	EXPECT_EQ( tpcontext.createTemplateContent( testPoly2 ), controlPoly2 );

	// Test case - initial, invariants and guards
	TemplatePolyhedronT<T, C, InitInvGuard> testPoly3( this->tpoly );
	controlMat = matrix_t<T>::Zero( 5, 2 );
	controlMat << -2, 1, 2, 1, 0, -1, -1, 0, -1, -1;
	controlVec = vector_t<T>::Zero( 5 );
	controlVec << 0, 2, 0, 0, 0;
	TemplatePolyhedronT<T, C, InitInvGuard> controlPoly3( controlMat, controlVec );
	// std::cout << "CreateTemplateContentTest, createTContent testPoly3: \n"
	//		  << tpcontext.createTemplateContent( testPoly3 ) << std::endl;
	EXPECT_EQ( tpcontext.createTemplateContent( testPoly3 ), controlPoly3 );

	// Build HybridAutomaton and add badstates
	std::vector<std::unique_ptr<Location<TypeParam>>> locVec;
	locVec.emplace_back( std::make_unique<Location<TypeParam>>( this->loc ) );
	locVec.emplace_back( std::make_unique<Location<TypeParam>>( badstate ) );
	std::map<const Location<TypeParam>*, Condition<TypeParam>> initialSets;
	initialSets.insert(
		  std::make_pair( locVec.front().get(), Condition<TypeParam>( this->tpoly.matrix(), this->tpoly.vector() ) ) );
	std::map<const Location<TypeParam>*, Condition<TypeParam>> localBadstates;
	localBadstates.insert( std::make_pair( locVec.back().get(), Condition<TypeParam>( lBadstateMat, lBadstateVec ) ) );
	HybridAutomaton<TypeParam> ha;
	ha.setLocations( std::move( locVec ) );
	ha.setInitialStates( initialSets );
	ha.setLocalBadStates( localBadstates );
	ha.setGlobalBadStates( gBadstate );

	// Test case - initial, invariants, guards and badstates
	TemplatePolyhedronT<T, C, InitInvGuardBad> testPoly4( this->tpoly );
	controlMat = matrix_t<T>::Zero( 5, 2 );
	controlMat << -2, 1, 2, 1, 0, -1, -1, 0, -1, -1;
	controlVec = vector_t<T>::Zero( 5 );
	controlVec << 0, 2, 0, 0, 0;
	TemplatePolyhedronT<T, C, InitInvGuardBad> controlPoly4( controlMat, controlVec );
	// std::cout << "CreateTemplateContentTest, createTContent testPoly4: \n"
	//		  << tpcontext.createTemplateContent( testPoly4 ) << std::endl;
	EXPECT_EQ( tpcontext.createTemplateContent( testPoly4 ), controlPoly4 );

	// TODO: Test case - octagon
	TemplatePolyhedronT<T, C, Octagon> testPoly5( this->tpoly );
	controlMat = matrix_t<T>::Zero( 8, 2 );
	controlMat << 1, 0, -1, 0, 0, 1, 0, -1, 1, 1, -1, -1, 1, -1, -1, 1;
	controlVec = vector_t<T>::Zero( 8 );
	controlVec << 1, 0, 1, 0, 1.5, 0, 1, 0.5;
	TemplatePolyhedronT<T, C, Octagon> controlPoly5( controlMat, controlVec );
	std::cout << "CreateTemplateContentTest, createTContent testPoly4: \n"
			  << tpcontext.createTemplateContent( testPoly5 ) << std::endl;
	EXPECT_EQ( tpcontext.createTemplateContent( testPoly5 ), controlPoly5 );
}

TYPED_TEST( TemplatePolyhedronContextTest, LocationInvariantStrengthening ) {
	// TODO: Test case - no invariant

	// First Test: have triangle shaped initial sets and triangle shaped invariants
	// Initialize tpcontext with positive invariant flow
	State_t<TypeParam> state( &( this->trappingLoc ) );
	state.setSet( this->tpoly, 0 );
	ReachTreeNode<State_t<TypeParam>> rnodeTrapping( state, (unsigned)0 );
	auto taskTrapping = std::make_shared<Task<State_t<TypeParam>>>( &rnodeTrapping );
	TemplatePolyhedronContext<State_t<TypeParam>> tpcontextTrapping(
		  taskTrapping, this->strat, this->localQueue, this->localCEXQueue, this->localSegments, this->settings );

	// Overapproximate positive invariant
	vector_t<TypeParam> tpolyTrapVector = vector_t<TypeParam>::Zero( 3 );
	tpolyTrapVector << 2, 4, 1;
	TPoly<TypeParam> tpolyTrap( this->trappingLoc.getInvariant().getMatrix(), tpolyTrapVector );
	EXPECT_TRUE( tpolyTrap.isBounded() );
	EXPECT_TRUE( tpcontextTrapping.isPositiveInvariant( this->tpoly, tpolyTrapVector ) );

	// Test if it just works - The result should be the same as before
	auto res = tpcontextTrapping.locationInvariantStrengthening( tpolyTrap, this->tpoly.vector() );
	for ( int i = 0; i < res.rows(); ++i ) {
		EXPECT_TRUE( ( this->tpoly.vector()( i ) <= res( i ) ) );
		EXPECT_TRUE( ( res( i ) <= tpolyTrap.vector()( i ) ) );
	}

	// Second Test: Have triangle shaped initial sets and box shaped invariants
	// Build box invariants
	std::cout << "=== SECOND TEST ===" << std::endl;
	matrix_t<TypeParam> boxInvMat = matrix_t<TypeParam>::Zero( 4, 2 );
	boxInvMat << 1, 0, -1, 0, 0, 1, 0, -1;
	vector_t<TypeParam> boxInvVec = 5 * vector_t<TypeParam>::Ones( 4 );
	this->trappingLoc.setInvariant( Condition<TypeParam>( boxInvMat, boxInvVec ) );
	EXPECT_EQ( state.getLocation()->getInvariant(), Condition<TypeParam>( boxInvMat, boxInvVec ) );

	// Overapproximate positive box invariant with triangle shape of tpoly
	TPoly<TypeParam> tpolyTrapBox( this->trappingLoc.getInvariant().getMatrix(),
								   this->trappingLoc.getInvariant().getVector() );
	EXPECT_TRUE( tpolyTrapBox.isBounded() );
	TPoly<TypeParam> tpolyTrapBoxOverapprox = tpolyTrapBox.overapproximate( this->tpoly.matrix() );

	// Test with box invariants - The result should be the same as before
	auto res2 = tpcontextTrapping.locationInvariantStrengthening( tpolyTrapBoxOverapprox, this->tpoly.vector() );
	for ( int i = 0; i < res2.rows(); ++i ) {
		EXPECT_TRUE( ( this->tpoly.vector()( i ) <= res2( i ) ) );
		EXPECT_TRUE( ( res2( i ) <= tpolyTrapBoxOverapprox.vector()( i ) ) );
	}

	// Third test: Have box shaped initial sets and box shaped invariants
	// Build box shaped tpoly and set it as state
	std::cout << "THIRD TEST" << std::endl;
	TPoly<TypeParam> boxTPoly( boxInvMat, vector_t<TypeParam>::Ones( 4 ) );
	state.setSet( boxTPoly );

	// Overapproximate positive box invariant with triangle shape of tpoly
	tpolyTrapBoxOverapprox = tpolyTrapBox.overapproximate( boxTPoly.matrix() );

	// Test with box invariants - The result should be the same as before
	auto res3 = tpcontextTrapping.locationInvariantStrengthening( tpolyTrapBoxOverapprox, boxTPoly.vector() );
	for ( int i = 0; i < res3.rows(); ++i ) {
		EXPECT_TRUE( ( boxTPoly.vector()( i ) <= res3( i ) ) );
		EXPECT_TRUE( ( res3( i ) <= tpolyTrapBoxOverapprox.vector()( i ) ) );
	}
}

// TYPED_TEST( TemplatePolyhedronContextTest, ExecBeforeFirstSegment ) {
//	SUCCEED();
// }
// TYPED_TEST( TemplatePolyhedronContextTest, FirstSegment ) {
//	SUCCEED();
// }
// TYPED_TEST( TemplatePolyhedronContextTest, ApplyContinuousEvolution ) {
//	SUCCEED();
// }
// TYPED_TEST( TemplatePolyhedronContextTest, Reachability ) {
//	SUCCEED();
// }

// Unit Tests: Instantiation, Every handler,

// Integration Tests: One Reachability Analysis,