/**
 * A Testfixture, which uses boxes as a representation and executes different parts of a reachability algorithm to test the implementation of boxes.
 *
 */

#include "gtest/gtest.h"
#include "../defines.h"
#include "../../lib/representations/Box/Box.h"
#include "../../lib/datastructures/Point.h"
 #include "../../lib/datastructures/hybridAutomata/LocationManager.h"
#include "../../lib/algorithms/reachability/Reach.h"

template<typename Number>
using Representation = hypro::Box<Number>;

template<typename Number>
class BoxReachabilityTest : public ::testing::Test
{
/**
 * Test Setup:
 * one hybrid automaton which consists of two locations that are connected by one transition
 */
protected:
	virtual void SetUp()
	{
		/*
		 * Location
		 */
		invariantVec(0) = 16;
		invariantVec(1) = 16;

		invariantOp = hypro::LEQ;

		invariantMat(0,0) = 1;
		invariantMat(0,1) = 0;
		invariantMat(1,0) = 0;
		invariantMat(1,1) = 1;

		loc1->setInvariant(invariantMat,invariantVec,invariantOp);

		inv.op = invariantOp;
		inv.mat = invariantMat;
		inv.vec = invariantVec;

		loc2->setInvariant(inv);

		//note: 3rd variable is for the encoded constant factor
		//here: x' = 2, y'= 2, z' = 0  (x' := derivative)
		locationMat(0,0) = 0.69314718056;
		locationMat(0,1) = 0;
		locationMat(0,2) = 0;
		locationMat(1,0) = 0;
		locationMat(1,1) = 0.69314718056;
		locationMat(1,2) = 0;
		locationMat(2,0) = 0;
		locationMat(2,1) = 0;
		locationMat(2,2) = 0;

		loc1->setActivityMat(locationMat);
		loc2->setActivityMat(locationMat);

		/*
		 * Transition
		 */
		guard.op = inv.op;
		guard.mat = inv.mat;
		guard.vec = inv.vec;

		assign.translationVec = inv.vec;
		assign.transformMat = inv.mat;

		trans->setGuard(guard);
		trans->setSource(loc1);
		trans->setTarget(loc2);
		trans->setReset(assign);

		/*
		 * Hybrid Automaton
		 */
		locations[0] = loc1;
		locations[1] = loc2;

		locSet = std::set<hypro::Location<Number>*>(locations, locations+2);

		init[0] = loc1;

		initLocSet = std::set<hypro::Location<Number>*>(init, init+1);

		H.setLocations(locSet);
		H.setInitialLocations(initLocSet);

		transition[0] = trans;

		transSet = std::set<hypro::Transition<Number>*>(transition, transition+1);

		H.setTransitions(transSet);
		loc1->setTransitions(transSet);

		//Representation for InitialValuation & Guard Assignment

		//create Box (note: 3rd variable is for the constant factor)
		boxVec(0) = 1;
		boxVec(1) = 0;
		boxVec(2) = 1;
		boxVec(3) = 0;

		boxMat(0,0) = 1;
		boxMat(0,1) = 0;
		boxMat(1,0) = -1;
		boxMat(1,1) = 0;
		boxMat(2,0) = 0;
		boxMat(2,1) = 1;
		boxMat(3,0) = 0;
		boxMat(3,1) = -1;

		initialBox = Representation<Number>(boxMat,boxVec);

		H.setInitialValuation(initialBox);
	}

	virtual void TearDown()
	{}

	//Hybrid Automaton Objects: Locations, Transitions, Automaton itself
	hypro::HybridAutomaton<Number, Representation<Number>> H = hypro::HybridAutomaton<Number, Representation<Number>>();

	hypro::LocationManager<Number>& locManag = hypro::LocationManager<Number>::getInstance();
	hypro::Location<Number>* loc1 = locManag.create();
	hypro::Location<Number>* loc2 = locManag.create();
	hypro::Transition<Number>* trans = new hypro::Transition<Number>();



	hypro::Location<Number>* locations[2];
	std::set<hypro::Location<Number>*> locSet;

	hypro::Location<Number>* init[1];
	std::set<hypro::Location<Number>*> initLocSet;

	//Other Objects: Vectors, Matrices, Guards...
	struct hypro::Location<Number>::Invariant inv;
	struct hypro::Transition<Number>::Guard guard;
	struct hypro::Transition<Number>::Reset assign;

	hypro::vector_t<Number> invariantVec = hypro::vector_t<Number>(2,1);
	hypro::operator_e invariantOp;
	hypro::matrix_t<Number> invariantMat = hypro::matrix_t<Number>(2,2);

	hypro::matrix_t<Number> locationMat = hypro::matrix_t<Number>(3,3);



	hypro::Transition<Number>* transition[1];
	std::set<hypro::Transition<Number>*> transSet;

	hypro::vector_t<Number> coordinates = hypro::vector_t<Number>(2,1);
	hypro::Point<Number> p1;
	Representation<Number> initialBox;
	Representation<Number> pPoly;

	//Box
	hypro::vector_t<Number> boxVec = hypro::vector_t<Number>(4,1);
	hypro::matrix_t<Number> boxMat = hypro::matrix_t<Number>(4,2);
};

/**
 * Test for function computePostCondition()
 */
TYPED_TEST(BoxReachabilityTest, ComputePostConditionTest)
{
	Representation<TypeParam> result;
	hypro::reachability::Reach<TypeParam, Representation<TypeParam>> reacher(this->H);
}

/**
 * Test for function computeForwardTimeClosure()
 */
TYPED_TEST(BoxReachabilityTest, ComputeForwardTimeClosureTest)
{
}

/**
 * Test for function computeForwardsReachability()
 */
TYPED_TEST(BoxReachabilityTest, ComputeForwardsReachabilityTest)
{
}

/**
 * Containment Tests: if polytopes are created correctly
 */
TYPED_TEST(BoxReachabilityTest, ContainmentTest)
{
}

TYPED_TEST(BoxReachabilityTest, UtilityTest)
{
}
