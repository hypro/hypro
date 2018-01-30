/**
 * Testfile for hybrid automata.
 * Author: ckugler
 */

#include "gtest/gtest.h"
#include "../defines.h"
#include "datastructures/HybridAutomaton/LocationManager.h"
#include "datastructures/HybridAutomaton/Transition.h"
#include "datastructures/HybridAutomaton/HybridAutomaton.h"
#include "datastructures/HybridAutomaton/State.h"
#include "representations/GeometricObject.h"
#include "carl/core/VariablePool.h"

using namespace hypro;
using namespace carl;

template <typename Number>
using valuation_t = VPolytope<Number>;

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

		loc1 = locMan.create();
    	loc2 = locMan.create();


    	trans = new Transition<Number>();

		invariantVec(0) = 10;
		invariantVec(1) = 20;

		invariantMat(0,0) = 2;
		invariantMat(0,1) = 0;
		invariantMat(1,0) = 0;
		invariantMat(1,1) = 3;

		loc1->setInvariant(Condition<Number>(invariantMat,invariantVec));
		loc1->setName("Location1");

		inv.setMatrix(invariantMat);
		inv.setVector(invariantVec);

		loc2->setInvariant(inv);
		loc2->setName("Location2");

		locationMat(0,0) = 2;
		locationMat(0,1) = 0;
		locationMat(1,0) = 0;
		locationMat(1,1) = 1;

		loc1->setFlow(locationMat);
		loc2->setFlow(locationMat);

		/*
		 * Transition Setup
		 */
		guard.setMatrix(inv.getMatrix());
		guard.setVector(inv.getVector());

		reset.setMatrix(inv.getMatrix());
		reset.setVector(inv.getVector());

		trans->setGuard(guard);
		trans->setSource(loc1);
		trans->setTarget(loc2);
		trans->setReset(reset);

		/*
		 * Hybrid Automaton Setup
		 */
		locations[0] = loc1;
		locations[1] = loc2;

		locSet = std::set<Location<Number>*>(locations, locations+2);
		init[0] = loc1;
		initLocSet = std::set<Location<Number>*>(init, init+1);

		//Polytope for InitialValuation & Guard Assignment
		coordinates(0) = 2;
		coordinates(1) = 3;

    	std::vector< vector_t<Number> > vecSet;
    	vecSet.push_back(coordinates);
		poly = valuation_t<Number>(vecSet);
		auto hpoly = Converter<Number>::toHPolytope(poly);

		hybrid.setLocations(locSet);
		for(auto loc : initLocSet) {
			State_t<Number> initState(loc);
			initState.setSet(ConstraintSet<Number>(hpoly.matrix(), hpoly.vector()));
			hybrid.addInitialState(initState);
		}

		transition[0] = trans;
		transSet = std::set<Transition<Number>*>(transition, transition+1);

		hybrid.setTransitions(transSet);
		loc1->setTransitions(transSet);
    }

    virtual void TearDown()
    {
    	//delete loc1;
    	//delete loc2;
    	//delete trans;
    }

    //Hybrid Automaton Objects: Locations, Transitions, Automaton itself

    LocationManager<Number>& locMan = LocationManager<Number>::getInstance();

    Location<Number>* loc1;
    Location<Number>* loc2;
    Transition<Number>* trans;
    HybridAutomaton<Number> hybrid;

    //Other Objects: Vectors, Matrices, Guards...
    vector_t<Number> invariantVec = vector_t<Number>(2,1);
    matrix_t<Number> invariantMat = matrix_t<Number>(2,2);
	Condition<Number> inv;
	matrix_t<Number> locationMat = matrix_t<Number>(2,2);

    Condition<Number> guard;

    Reset<Number> reset;

    Location<Number>* locations[2];
    std::set<Location<Number>*> locSet;

    Location<Number>* init[1];
    std::set<Location<Number>*> initLocSet;

    Transition<Number>* transition[1];
	std::set<Transition<Number>*> transSet;

	vector_t<Number> coordinates = vector_t<Number>(2,1);
    valuation_t<Number> poly;
};

/**
 * Location Test
 */
TYPED_TEST(HybridAutomataTest, LocationTest)
{
    //invariant: vector
    EXPECT_EQ(this->loc1->getInvariant().getVector(), this->invariantVec);
    EXPECT_EQ(this->loc2->getInvariant().getVector(), this->invariantVec);

	vector_t<TypeParam> invariantVec2(2,1);
	invariantVec2(0) = 10;
	invariantVec2(1) = 10;
	EXPECT_NE(this->loc1->getInvariant().getVector(), invariantVec2);

	//invariant: matrix
	EXPECT_EQ(this->loc1->getInvariant().getMatrix(), this->invariantMat);
	EXPECT_EQ(this->loc2->getInvariant().getMatrix(), this->invariantMat);

	matrix_t<TypeParam> invariantMat2(2,2);
	invariantMat2(0,0) = 1;
	invariantMat2(0,1) = 0;
	invariantMat2(1,0) = 0;
	invariantMat2(1,1) = 3;
	EXPECT_NE(this->loc1->getInvariant().getMatrix(), invariantMat2);

	//location: matrix
	EXPECT_EQ(this->loc1->getFlow(), this->locationMat);

	matrix_t<TypeParam> locationMat2(2,2);
	locationMat2(0,0) = 1;
	locationMat2(0,1) = 0;
	locationMat2(1,0) = 0;
	locationMat2(1,1) = 1;
	EXPECT_NE(this->loc1->getFlow(), locationMat2);

	//location: set of outgoing transitions
	EXPECT_EQ(this->loc1->getTransitions(), this->transSet);

	EXPECT_TRUE(*this->loc1 < *this->loc2);
	EXPECT_FALSE(*this->loc2 < *this->loc1);

	EXPECT_TRUE(locPtrComp<TypeParam>()(this->loc1, this->loc2));
}

TYPED_TEST(HybridAutomataTest, LocationParallelcompositionTest)
{
	Location<TypeParam>* l1 = this->locMan.create();
	Location<TypeParam>* l2 = this->locMan.create();

	typename HybridAutomaton<TypeParam>::variableVector l1Vars{"a","b"};
	typename HybridAutomaton<TypeParam>::variableVector l2Vars{"x","b"};
	typename HybridAutomaton<TypeParam>::variableVector haVars{"a","x","b"};

	matrix_t<TypeParam> l1Flow = matrix_t<TypeParam>::Zero(2,2);
	l1Flow << 1,2,3,4;
	matrix_t<TypeParam> l2Flow = matrix_t<TypeParam>::Zero(2,2);
	l2Flow << 1,2,3,4;

	l1->setFlow(l1Flow);
	l2->setFlow(l2Flow);

	Location<TypeParam>* res1 = parallelCompose(l1,l2,l1Vars,l2Vars,haVars);
	matrix_t<TypeParam> expectedResult1 = matrix_t<TypeParam>::Zero(haVars.size(), haVars.size());
	expectedResult1 << 1,0,2,0,1,2,3,3,4;
	EXPECT_EQ(res1->getFlow(),expectedResult1);


	l1Vars = {"a","b"};
	l2Vars = {"c","d"};
	haVars = {"a","b","c","d"};
	Location<TypeParam>* res2 = parallelCompose(l1,l2,l1Vars,l2Vars,haVars);

	matrix_t<TypeParam> expectedResult2 = matrix_t<TypeParam>::Zero(haVars.size(), haVars.size());
	expectedResult2 << 1,2,0,0,3,4,0,0,0,0,1,2,0,0,3,4;
	EXPECT_EQ(res2->getFlow(),expectedResult2);
}

/**
 * Transition Test
 */
TYPED_TEST(HybridAutomataTest, TransitionTest)
{
	//transition: Start Location
	EXPECT_EQ(this->trans->getSource(), this->loc1);

	//transition: End Location
	EXPECT_EQ(this->trans->getTarget(), this->loc2);

	//transition: Assignment
	EXPECT_EQ(this->trans->getReset().getVector(), this->reset.getVector());
	EXPECT_EQ(this->trans->getReset().getMatrix(), this->reset.getMatrix());

	//transition: Guard
	EXPECT_EQ(this->trans->getGuard().getVector(), this->guard.getVector());
	EXPECT_EQ(this->trans->getGuard().getMatrix(), this->guard.getMatrix());

	// creation of transitions from source and target
	Transition<TypeParam>* t = new Transition<TypeParam>(this->loc1, this->loc2);
	EXPECT_EQ(t->getSource(), this->loc1);
	EXPECT_EQ(t->getTarget(), this->loc2);
	EXPECT_EQ(t->getAggregation(), Aggregation::none);
	EXPECT_FALSE(t->isTimeTriggered());

	t->setAggregation(Aggregation::boxAgg);
	EXPECT_EQ(t->getAggregation(), Aggregation::boxAgg);

	t->setTriggerTime(TypeParam(1));
	EXPECT_TRUE(t->isTimeTriggered());
	EXPECT_EQ(t->getTriggerTime(), TypeParam(1));
}

/**
 * Hybrid Automaton Test
 */
TYPED_TEST(HybridAutomataTest, HybridAutomatonTest)
{
	// construct a new hybrid automaton.
	HybridAutomaton<TypeParam> h1;

	h1.addLocation(this->loc1);
	h1.addLocation(this->loc2);

	EXPECT_TRUE(std::find(h1.getLocations().begin(), h1.getLocations().end(), this->loc1) != h1.getLocations().end());
	EXPECT_TRUE(std::find(h1.getLocations().begin(), h1.getLocations().end(), this->loc2) != h1.getLocations().end());

	EXPECT_TRUE(h1.getLocation("Location1") == this->loc1);
	EXPECT_TRUE(h1.getLocation(this->loc1->getId()) == this->loc1);
	EXPECT_TRUE(h1.getLocation("Location2") == this->loc2);
	EXPECT_TRUE(h1.getLocation(this->loc2->getId()) == this->loc2);

	h1.addTransition(this->trans);
	EXPECT_TRUE(std::find(h1.getTransitions().begin(), h1.getTransitions().end(), this->trans) != h1.getTransitions().end());

	matrix_t<TypeParam> matr = matrix_t<TypeParam>::Identity(2,2);
	vector_t<TypeParam> vec = vector_t<TypeParam>(2);
	vec << 1,2;

	State_t<TypeParam> s(this->loc1);
	s.setSet(ConstraintSet<TypeParam>(matr, vec));

	h1.addInitialState(s);

	// copy assignment operator
	HybridAutomaton<TypeParam> h2 = h1;
	EXPECT_EQ(h1, h2);
}

TYPED_TEST(HybridAutomataTest, LocationManagerTest)
{
	matrix_t<TypeParam> flow = matrix_t<TypeParam>::Identity(2,2);
	Location<TypeParam>* loc = this->locMan.create(flow);
	EXPECT_EQ(loc->getFlow(), flow);

	unsigned id = this->locMan.id(loc);
	EXPECT_EQ(this->locMan.location(id), loc);
}


TYPED_TEST(HybridAutomataTest, State) {
	// Constructors
	State_t<TypeParam> s1(this->loc1);

	matrix_t<TypeParam> matr = matrix_t<TypeParam>::Identity(2,2);
	vector_t<TypeParam> vec = vector_t<TypeParam>(2);
	vec << 1,2;
	State_t<TypeParam> s2(this->loc1);
	s2.setSet(ConstraintSet<TypeParam>(matr, vec));

	EXPECT_EQ(s1.getLocation()->getId(), this->loc1->getId());
	EXPECT_EQ(s2.getLocation()->getId(), this->loc1->getId());
	EXPECT_EQ(boost::get<ConstraintSet<TypeParam>>(s2.getSet()).matrix(), matr);
	EXPECT_EQ(boost::get<ConstraintSet<TypeParam>>(s2.getSet()).vector(), vec);
	EXPECT_EQ(boost::get<ConstraintSet<TypeParam>>(s2.getSet(0)).matrix(), matr);
	EXPECT_EQ(boost::get<ConstraintSet<TypeParam>>(s2.getSet(0)).vector(), vec);
}
