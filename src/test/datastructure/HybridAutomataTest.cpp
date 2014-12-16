/**
 * Testfile for hybrid automata.
 * Author: ckugler
 */

#include "gtest/gtest.h"
#include "../defines.h"
#include "../../lib/datastructures/hybridAutomata/Location.h"
#include "../../lib/datastructures/hybridAutomata/Transition.h"
#include "../../lib/datastructures/hybridAutomata/HybridAutomaton.h"
#include "carl/core/VariablePool.h"
#include "../../lib/datastructures/Point.h"


using namespace hypro;
using namespace carl;

class HybridAutomataTest : public ::testing::Test
{
/**
 * Test Setup:
 * one hybrid automaton which consists of two locations that are connected by one transition
 */
protected:
    virtual void SetUp()
    {
      	/*
		 * Location Setup
		 */
		invariantVec(0) = 10;
		invariantVec(1) = 20;

		invariantOp = LEQ;

		invariantMat(0,0) = 2;
		invariantMat(0,1) = 0;
		invariantMat(1,0) = 0;
		invariantMat(1,1) = 3;

		loc1->setInvariant(invariantMat,invariantVec,invariantOp);

		inv.op = invariantOp;
		inv.mat = invariantMat;
		inv.vec = invariantVec;

		loc2->setInvariant(inv);

		locationMat(0,0) = 2;
		locationMat(0,1) = 0;
		locationMat(1,0) = 0;
		locationMat(1,1) = 1;

		loc1->setActivityMat(locationMat);
		loc2->setActivityMat(locationMat);

		/*
		 * Transition Setup
		 */
		guard.op = inv.op;
		guard.mat = inv.mat;
		guard.vec = inv.vec;

		assign.translationVec = inv.vec;
		assign.transformMat = inv.mat;

		trans->setGuard(guard);
		trans->setStartLoc(loc1);
		trans->setTargetLoc(loc2);
		trans->setAssignment(assign);

		/*
		 * Hybrid Automaton Setup
		 */
		locations[0] = loc1;
		locations[1] = loc2;

		locSet = std::set<hypro::Location<number>*>(locations, locations+2);

		init[0] = loc1;

		initLocSet = std::set<hypro::Location<number>*>(init, init+1);

		hybrid.setLocations(locSet);
		hybrid.setInitialLocations(initLocSet);

		transition[0] = trans;

		transSet = std::set<hypro::Transition<number>*>(transition, transition+1);

		hybrid.setTransitions(transSet);
		loc1->setTransitions(transSet);

		//Polytope for InitialValuation & Guard Assignment
		coordinates(0) = 2;
		coordinates(1) = 3;

    	std::vector< vector_t <number> > vecSet;
    	vecSet.push_back(coordinates);

    	poly = Polytope<number>(vecSet);

		hybrid.setValuation(poly);
    }

    virtual void TearDown()
    {
    	//TODO TearDown
    }

    //Hybrid Automaton Objects: Locations, Transitions, Automaton itself
    Location<number>* loc1 = new Location<number>();
    Location<number>* loc2 = new Location<number>();
    hypro::Transition<number>* trans = new hypro::Transition<number>();
    HybridAutomaton<number, valuation> hybrid;

    //Other Objects: Vectors, Matrices, Guards...
    vector_t<number> invariantVec = vector_t<number>(2,1);
    operator_e invariantOp;
    matrix_t<number> invariantMat = matrix_t<number>(2,2);
	struct Location<number>::invariant inv;
	matrix_t<number> locationMat = matrix_t<number>(2,2);

    struct hypro::Transition<number>::guard guard;

    struct hypro::Transition<number>::assignment assign;

    hypro::Location<number>* locations[2];
    std::set<hypro::Location<number>*> locSet;

    hypro::Location<number>* init[1];
    std::set<hypro::Location<number>*> initLocSet;

    hypro::Transition<number>* transition[1];
	std::set<hypro::Transition<number>*> transSet;

	vector_t<number> coordinates = vector_t<number>(2,1);
    hypro::Polytope<number> poly;

};

/**
 * Location Test
 */
TEST_F(HybridAutomataTest, LocationTest)
{
	//invariant: operator
    EXPECT_EQ(loc1->invariant().op,LEQ);
    EXPECT_EQ(loc2->invariant().op,LEQ);
    EXPECT_EQ(loc2->location().inv.op,LEQ);

    //invariant: vector
    EXPECT_EQ(loc1->invariant().vec, invariantVec);
    EXPECT_EQ(loc2->invariant().vec, invariantVec);
    EXPECT_EQ(loc1->location().inv.vec, invariantVec);
    EXPECT_EQ(loc2->location().inv.vec, invariantVec);

	vector_t<number> invariantVec2(2,1);
	invariantVec2(0) = 10;
	invariantVec2(1) = 10;
	EXPECT_NE(loc1->invariant().vec, invariantVec2);

	//invariant: matrix
	EXPECT_EQ(loc1->invariant().mat, invariantMat);
	EXPECT_EQ(loc2->invariant().mat, invariantMat);
	EXPECT_EQ(loc1->location().inv.mat, invariantMat);

	matrix_t<number> invariantMat2(2,2);
	invariantMat2(0,0) = 1;
	invariantMat2(0,1) = 0;
	invariantMat2(1,0) = 0;
	invariantMat2(1,1) = 3;
	EXPECT_NE(loc1->invariant().mat, invariantMat2);

	//location: matrix
	EXPECT_EQ(loc1->activityMat(), locationMat);
	EXPECT_EQ(loc1->location().mat, locationMat);

	matrix_t<number> locationMat2(2,2);
	locationMat2(0,0) = 1;
	locationMat2(0,1) = 0;
	locationMat2(1,0) = 0;
	locationMat2(1,1) = 1;
	EXPECT_NE(loc1->activityMat(), locationMat2);

	//location: set of outgoing transitions
	EXPECT_EQ(loc1->transitions(), transSet);
}

/**
 * Transition Test
 */
TEST_F(HybridAutomataTest, TransitionTest)
{
	//transition: Start Location
	EXPECT_EQ(trans->startLoc(), loc1);

	//transition: End Location
	EXPECT_EQ(trans->targetLoc(), loc2);

	//transition: Assignment
	EXPECT_EQ(trans->assignment().translationVec, assign.translationVec);
	EXPECT_EQ(trans->assignment().transformMat, assign.transformMat);

	//transition: Guard
	EXPECT_EQ(trans->guard().vec, guard.vec);
	EXPECT_EQ(trans->guard().mat, guard.mat);
	EXPECT_EQ(trans->guard().op, guard.op);

}

/**
 * Hybrid Automaton Test
 */
TEST_F(HybridAutomataTest, HybridAutomatonTest)
{
	//hybrid automaton: initial Location
	EXPECT_EQ(hybrid.initialLocations(), initLocSet);
	EXPECT_NE(hybrid.initialLocations(), locSet);

	//hybrid automaton: Location set
	EXPECT_EQ(hybrid.locations(), locSet);
	EXPECT_NE(hybrid.locations(), initLocSet);

	//hybrid automaton: Transition set
	EXPECT_EQ(hybrid.transitions(), transSet);

	//hybrid automaton: initial Valuation
	//equivalence has to be confirmed through console output
#ifdef fReach_DEBUG
	hybrid.valuation().print();
	poly.print();
#endif

}
