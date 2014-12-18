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

template<typename Number>
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

		locSet = std::set<hypro::Location<Number>*>(locations, locations+2);

		init[0] = loc1;

		initLocSet = std::set<hypro::Location<Number>*>(init, init+1);

		hybrid.setLocations(locSet);
		hybrid.setInitialLocations(initLocSet);

		transition[0] = trans;

		transSet = std::set<hypro::Transition<Number>*>(transition, transition+1);

		hybrid.setTransitions(transSet);
		loc1->setTransitions(transSet);

		//Polytope for InitialValuation & Guard Assignment
		coordinates(0) = 2;
		coordinates(1) = 3;

    	std::vector< vector_t<Number> > vecSet;
    	vecSet.push_back(coordinates);

    	poly = Polytope<Number>(vecSet);

		hybrid.setValuation(poly);
    }

    virtual void TearDown()
    {
    	//TODO TearDown
    }

    //Hybrid Automaton Objects: Locations, Transitions, Automaton itself
    Location<Number>* loc1 = new Location<Number>();
    Location<Number>* loc2 = new Location<Number>();
    hypro::Transition<Number>* trans = new hypro::Transition<Number>();
    HybridAutomaton<Number, valuation_t<Number>> hybrid;

    //Other Objects: Vectors, Matrices, Guards...
    vector_t<Number> invariantVec = vector_t<Number>(2,1);
    operator_e invariantOp;
    matrix_t<Number> invariantMat = matrix_t<Number>(2,2);
	struct Location<Number>::invariant inv;
	matrix_t<Number> locationMat = matrix_t<Number>(2,2);

    struct hypro::Transition<Number>::guard guard;

    struct hypro::Transition<Number>::assignment assign;

    hypro::Location<Number>* locations[2];
    std::set<hypro::Location<Number>*> locSet;

    hypro::Location<Number>* init[1];
    std::set<hypro::Location<Number>*> initLocSet;

    hypro::Transition<Number>* transition[1];
	std::set<hypro::Transition<Number>*> transSet;

	vector_t<Number> coordinates = vector_t<Number>(2,1);
    hypro::Polytope<Number> poly;

};

/**
 * Location Test
 */
TYPED_TEST(HybridAutomataTest, LocationTest)
{
	//invariant: operator
    EXPECT_EQ(this->loc1->invariant().op,LEQ);
    EXPECT_EQ(this->loc2->invariant().op,LEQ);
    EXPECT_EQ(this->loc2->location().inv.op,LEQ);

    //invariant: vector
    EXPECT_EQ(this->loc1->invariant().vec, this->invariantVec);
    EXPECT_EQ(this->loc2->invariant().vec, this->invariantVec);
    EXPECT_EQ(this->loc1->location().inv.vec, this->invariantVec);
    EXPECT_EQ(this->loc2->location().inv.vec, this->invariantVec);

	vector_t<TypeParam> invariantVec2(2,1);
	invariantVec2(0) = 10;
	invariantVec2(1) = 10;
	EXPECT_NE(this->loc1->invariant().vec, invariantVec2);

	//invariant: matrix
	EXPECT_EQ(this->loc1->invariant().mat, this->invariantMat);
	EXPECT_EQ(this->loc2->invariant().mat, this->invariantMat);
	EXPECT_EQ(this->loc1->location().inv.mat, this->invariantMat);

	matrix_t<TypeParam> invariantMat2(2,2);
	invariantMat2(0,0) = 1;
	invariantMat2(0,1) = 0;
	invariantMat2(1,0) = 0;
	invariantMat2(1,1) = 3;
	EXPECT_NE(this->loc1->invariant().mat, invariantMat2);

	//location: matrix
	EXPECT_EQ(this->loc1->activityMat(), this->locationMat);
	EXPECT_EQ(this->loc1->location().mat, this->locationMat);

	matrix_t<TypeParam> locationMat2(2,2);
	locationMat2(0,0) = 1;
	locationMat2(0,1) = 0;
	locationMat2(1,0) = 0;
	locationMat2(1,1) = 1;
	EXPECT_NE(this->loc1->activityMat(), locationMat2);

	//location: set of outgoing transitions
	EXPECT_EQ(this->loc1->transitions(), this->transSet);
}

/**
 * Transition Test
 */
TYPED_TEST(HybridAutomataTest, TransitionTest)
{
	//transition: Start Location
	EXPECT_EQ(this->trans->startLoc(), this->loc1);

	//transition: End Location
	EXPECT_EQ(this->trans->targetLoc(),this-> loc2);

	//transition: Assignment
	EXPECT_EQ(this->trans->assignment().translationVec, this->assign.translationVec);
	EXPECT_EQ(this->trans->assignment().transformMat, this->assign.transformMat);

	//transition: Guard
	EXPECT_EQ(this->trans->guard().vec, this->guard.vec);
	EXPECT_EQ(this->trans->guard().mat, this->guard.mat);
	EXPECT_EQ(this->trans->guard().op, this->guard.op);

}

/**
 * Hybrid Automaton Test
 */
TYPED_TEST(HybridAutomataTest, HybridAutomatonTest)
{
	//hybrid automaton: initial Location
	EXPECT_EQ(this->hybrid.initialLocations(), this->initLocSet);
	EXPECT_NE(this->hybrid.initialLocations(), this->locSet);

	//hybrid automaton: Location set
	EXPECT_EQ(this->hybrid.locations(), this->locSet);
	EXPECT_NE(this->hybrid.locations(), this->initLocSet);

	//hybrid automaton: Transition set
	EXPECT_EQ(this->hybrid.transitions(), this->transSet);

	//hybrid automaton: initial Valuation
	//equivalence has to be confirmed through console output
#ifdef fReach_DEBUG
	this->hybrid.valuation().print();
	poly.print();
#endif

}
