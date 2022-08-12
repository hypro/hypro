/**
 * Testfile for the reachability computation based on Vpolytopes.
 * Author: ckugler
 */

#include "../../hypro/algorithms/reachability/forwardReachability.h"
#include "../../hypro/datastructures/Point.h"
#include "../../hypro/datastructures/hybridAutomata/HybridAutomaton.h"
#include "../../hypro/datastructures/hybridAutomata/LocationManager.h"
#include "../../hypro/datastructures/hybridAutomata/Transition.h"
#include "../../hypro/representations/GeometricObjectBase.h"
#include "../defines.h"
#include "gtest/gtest.h"
#include <carl/core/VariablePool.h>

using namespace hypro;
using namespace carl;

class ForwardReachabilityTest : public ::testing::Test {
	/**
	 * Test Setup:
	 * one hybrid automaton which consists of two locations that are connected by one transition
	 */
  protected:
	virtual void SetUp() {
		/*
		 * Location
		 */
		invariantVec( 0 ) = 16;
		invariantVec( 1 ) = 16;

		invariantMat( 0, 0 ) = 1;
		invariantMat( 0, 1 ) = 0;
		invariantMat( 1, 0 ) = 0;
		invariantMat( 1, 1 ) = 1;

		loc1->setInvariant( invariantMat, invariantVec );

		inv.mat = invariantMat;
		inv.vec = invariantVec;

		loc2->setInvariant( inv );

		// note: 3rd variable is for the encoded constant factor
		// here: x' = 2, y'= 2, z' = 0  (x' := derivative)
		locationMat( 0, 0 ) = 0.69314718056;
		locationMat( 0, 1 ) = 0;
		locationMat( 0, 2 ) = 0;
		locationMat( 1, 0 ) = 0;
		locationMat( 1, 1 ) = 0.69314718056;
		locationMat( 1, 2 ) = 0;
		locationMat( 2, 0 ) = 0;
		locationMat( 2, 1 ) = 0;
		locationMat( 2, 2 ) = 0;

		loc1->setFlow( locationMat );
		loc2->setFlow( locationMat );

		/*
		 * Transition
		 */
		guard.mat = inv.mat;
		guard.vec = inv.vec;

		assign.vec = inv.vec;
		assign.mat = inv.mat;

		trans->setGuard( guard );
		trans->setSource( loc1 );
		trans->setTarget( loc2 );
		trans->setReset( assign );

		/*
		 * Hybrid Automaton
		 */
		locations[0] = loc1;
		locations[1] = loc2;

		locSet = std::set<hypro::Location<mpq_class>*>( locations, locations + 2 );

		init[0] = loc1;

		initLocSet = std::set<hypro::Location<mpq_class>*>( init, init + 1 );

		hybrid.setLocations( locSet );

		transition[0] = trans;

		transSet = std::set<hypro::Transition<mpq_class>*>( transition, transition + 1 );

		hybrid.setTransitions( transSet );
		loc1->setTransitions( transSet );

		// VPolytope for InitialValuation & Guard Assignment

		// create Box (note: 3rd variable is for the constant factor)
		boxVec( 0 ) = 1;
		boxVec( 1 ) = 0;
		boxVec( 2 ) = 1;
		boxVec( 3 ) = 0;

		boxMat( 0, 0 ) = 1;
		boxMat( 0, 1 ) = 0;
		boxMat( 1, 0 ) = -1;
		boxMat( 1, 1 ) = 0;
		boxMat( 2, 0 ) = 0;
		boxMat( 2, 1 ) = 1;
		boxMat( 3, 0 ) = 0;
		boxMat( 3, 1 ) = -1;

		for ( auto location : initLocSet ) {
			hybrid.addInitialState( location, std::make_pair( boxMat, boxVec ) );
		}

		/*
		 * Testing of other ways to construct a Vpolytope
		 */

		coordinates( 0 ) = 1;
		coordinates( 1 ) = 1;

		std::vector<vector_t<mpq_class>> vecSet;
		vecSet.push_back( coordinates );

		pPoly = VPolytope<mpq_class>( vecSet );

		//--------
		p1 = Point<mpq_class>( { 1, 1 } );

		pPoly = VPolytope<mpq_class>( p1 );
	}

	virtual void TearDown() {
		// TODO: tear down
	}

	// Hybrid Automaton Objects: Locations, Transitions, Automaton itself
	LocationManager<mpq_class>& locManag = hypro::LocationManager<mpq_class>::getInstance();

	Location<mpq_class>* loc1 = locManag.create();
	Location<mpq_class>* loc2 = locManag.create();
	hypro::Transition<mpq_class>* trans = new hypro::Transition<mpq_class>();
	HybridAutomaton<mpq_class> hybrid = HybridAutomaton<mpq_class>();

	// Other Objects: Vectors, Matrices, Guards...
	vector_t<mpq_class> invariantVec = vector_t<mpq_class>( 2, 1 );
	matrix_t<mpq_class> invariantMat = matrix_t<mpq_class>( 2, 2 );
	struct Location<mpq_class>::Invariant inv;
	matrix_t<mpq_class> locationMat = matrix_t<mpq_class>( 3, 3 );

	struct hypro::Transition<mpq_class>::Guard guard;

	struct hypro::Transition<mpq_class>::Reset assign;

	hypro::Location<mpq_class>* locations[2];
	std::set<hypro::Location<mpq_class>*> locSet;

	hypro::Location<mpq_class>* init[1];
	std::set<hypro::Location<mpq_class>*> initLocSet;

	hypro::Transition<mpq_class>* transition[1];
	std::set<hypro::Transition<mpq_class>*> transSet;

	vector_t<mpq_class> coordinates = vector_t<mpq_class>( 2, 1 );
	Point<mpq_class> p1;
	hypro::VPolytope<mpq_class> poly;
	hypro::VPolytope<mpq_class> pPoly;

	// Box
	vector_t<mpq_class> boxVec = vector_t<mpq_class>( 4, 1 );
	matrix_t<mpq_class> boxMat = matrix_t<mpq_class>( 4, 2 );
};

/**
 * Test for function computePostCondition()
 */
TEST_F( ForwardReachabilityTest, ComputePostConditionTest ) {
	hypro::VPolytope<mpq_class> result;
	bool inside = forwardReachability::computePostCondition( *trans, poly, result );
	EXPECT_TRUE( inside );

	// place box outside of guard
	boxVec( 0 ) = 18;
	boxVec( 1 ) = -17;
	boxVec( 2 ) = 18;
	boxVec( 3 ) = -17;

	VPolytope<mpq_class> oPoly;
	oPoly = VPolytope<mpq_class>( boxMat, boxVec );

	bool outside = forwardReachability::computePostCondition( *trans, oPoly, result );
	EXPECT_FALSE( outside );
}

/**
 * Test for function computeForwardTimeClosure()
 */
TEST_F( ForwardReachabilityTest, ComputeForwardTimeClosureTest ) {
	std::vector<hypro::VPolytope<mpq_class>> flowpipe;

#ifdef fReach_DEBUG
	std::cout << "original VPolytope (Box): ";
	poly.print();
#endif

	flowpipe = forwardReachability::computeForwardTimeClosure( *loc1, poly );

	// check size of flowpipe
#ifdef fReach_DEBUG
	int size = flowpipe.size();

	std::cout << "Flowpipe size: ";
	std::cout << size << std::endl;
#endif
}

/**
 * Test for function computeForwardsReachability()
 */
TEST_F( ForwardReachabilityTest, ComputeForwardsReachabilityTest ) {
	// TODO
}

/**
 * Containment Tests: if HVolytopes are created correctly
 */
TEST_F( ForwardReachabilityTest, ContainmentTest ) {
	/*
	 * Tests based on VPolytope(Matrix,Vector) constructor
	 */
	hypro::vector_t<mpq_class> pointVec = hypro::vector_t<mpq_class>( 4, 1 );

	pointVec( 0 ) = 0;
	pointVec( 1 ) = 0;
	pointVec( 2 ) = 0;
	pointVec( 3 ) = 0;

	VPolytope<mpq_class> pointPoly;
	pointPoly = VPolytope<mpq_class>( boxMat, pointVec );

	bool contains = poly.contains( pointPoly );
	EXPECT_TRUE( contains );

	pointVec( 0 ) = 0.5;
	pointVec( 1 ) = -0.5;
	pointVec( 2 ) = 0.75;
	pointVec( 3 ) = -0.75;

	pointPoly = VPolytope<mpq_class>( boxMat, pointVec );

	bool contains2 = poly.contains( pointPoly );
	EXPECT_TRUE( contains2 );

	pointVec( 0 ) = 2;
	pointVec( 1 ) = -2;
	pointVec( 2 ) = 2;
	pointVec( 3 ) = -2;

	pointPoly = VPolytope<mpq_class>( boxMat, pointVec );

	bool contains3 = poly.contains( pointPoly );
	EXPECT_FALSE( contains3 );

	pointVec( 0 ) = 2;
	pointVec( 1 ) = -2;
	pointVec( 2 ) = 0.5;
	pointVec( 3 ) = -0.5;

	pointPoly = VPolytope<mpq_class>( boxMat, pointVec );

	bool contains4 = poly.contains( pointPoly );
	EXPECT_FALSE( contains4 );
}

TEST_F( ForwardReachabilityTest, UtilityTest ) {
	/**
	 * computeVPolytope() Test
	 */
	hypro::VPolytope<mpq_class> testBoxPoly;
	int dimension = 2;	// the last component is used for contstants
	mpq_class radius = 5;
	testBoxPoly = hypro::computePolytope<mpq_class, hypro::VPolytope<mpq_class>>( dimension, radius );

	hypro::vector_t<mpq_class> pointVec = hypro::vector_t<mpq_class>( 4, 1 );

	matrix_t<mpq_class> testMat = boxMat;

	pointVec( 0 ) = 5;
	pointVec( 1 ) = 5;
	pointVec( 2 ) = 5;
	pointVec( 3 ) = 5;

	VPolytope<mpq_class> pointPoly;
	pointPoly = VPolytope<mpq_class>( testMat, pointVec );

	EXPECT_TRUE( pointPoly.contains( testBoxPoly ) );
	EXPECT_TRUE( testBoxPoly.contains( pointPoly ) );

	pointVec( 0 ) = 5;
	pointVec( 1 ) = -5;
	pointVec( 2 ) = 5;
	pointVec( 3 ) = -5;

	pointPoly = VPolytope<mpq_class>( testMat, pointVec );
	EXPECT_TRUE( testBoxPoly.contains( pointPoly ) );

	pointVec( 0 ) = 6;
	pointVec( 1 ) = -6;
	pointVec( 2 ) = 5;
	pointVec( 3 ) = -5;

	pointPoly = VPolytope<mpq_class>( testMat, pointVec );
	EXPECT_FALSE( testBoxPoly.contains( pointPoly ) );

	/**
	 * convertMatToDouble() Test
	 */

	/*
	Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> doubleMat(invariantMat.rows(),invariantMat.cols());
	doubleMat = hypro::convertMatToDouble(invariantMat);
	EXPECT_EQ(invariantMat(0,0).toDouble(), doubleMat(0,0));
	*/
	/**
	 * convertMatToFloatT() Test
	 */

	/*
	matrix_t<mpq_class> floatTMat(doubleMat.rows(),doubleMat.cols());
	floatTMat = hypro::convertMatToFloatT(doubleMat);
	EXPECT_EQ(mpq_class(doubleMat(0,0)), floatTMat(0,0));
	*/
}
