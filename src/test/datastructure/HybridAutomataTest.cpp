/**
 * Testfile for hybrid automata.
 * Author: ckugler
 */

#include "gtest/gtest.h"
#include "../defines.h"
#include "../../hypro/datastructures/hybridAutomata/LocationManager.h"
#include "../../hypro/datastructures/hybridAutomata/Transition.h"
#include "../../hypro/datastructures/hybridAutomata/HybridAutomaton.h"
#include "../../hypro/representations/GeometricObject.h"
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
    	trans = new hypro::Transition<Number>();

		invariantVec(0) = 10;
		invariantVec(1) = 20;

		invariantMat(0,0) = 2;
		invariantMat(0,1) = 0;
		invariantMat(1,0) = 0;
		invariantMat(1,1) = 3;

		loc1->setInvariant(invariantMat,invariantVec);

		inv.mat = invariantMat;
		inv.vec = invariantVec;

		loc2->setInvariant(inv);

		locationMat(0,0) = 2;
		locationMat(0,1) = 0;
		locationMat(1,0) = 0;
		locationMat(1,1) = 1;

		loc1->setFlow(locationMat);
		loc2->setFlow(locationMat);

		/*
		 * Transition Setup
		 */
		guard.mat = inv.mat;
		guard.vec = inv.vec;

		reset.vec = inv.vec;
		reset.mat = inv.mat;

		trans->setGuard(guard);
		trans->setSource(loc1);
		trans->setTarget(loc2);
		trans->setReset(reset);

		/*
		 * Hybrid Automaton Setup
		 */
		locations[0] = loc1;
		locations[1] = loc2;

		locSet = std::set<hypro::Location<Number>*>(locations, locations+2);
		init[0] = loc1;
		initLocSet = std::set<hypro::Location<Number>*>(init, init+1);

		//Polytope for InitialValuation & Guard Assignment
		coordinates(0) = 2;
		coordinates(1) = 3;

    	std::vector< vector_t<Number> > vecSet;
    	vecSet.push_back(coordinates);
		poly = valuation_t<Number>(vecSet);
		auto hpoly = hypro::Converter<Number>::toHPolytope(poly);

		hybrid.setLocations(locSet);
		for(auto loc : initLocSet) {
			hybrid.addInitialState(loc, std::make_pair(hpoly.matrix(), hpoly.vector()));
		}

		transition[0] = trans;
		transSet = std::set<hypro::Transition<Number>*>(transition, transition+1);

		hybrid.setTransitions(transSet);
		loc1->setTransitions(transSet);
    }

    virtual void TearDown()
    {
    	delete loc1;
    	delete loc2;
    	delete trans;
    }

    //Hybrid Automaton Objects: Locations, Transitions, Automaton itself

    LocationManager<Number>& locMan = LocationManager<Number>::getInstance();

    Location<Number>* loc1;
    Location<Number>* loc2;
    hypro::Transition<Number>* trans;
    HybridAutomaton<Number> hybrid;

    //Other Objects: Vectors, Matrices, Guards...
    vector_t<Number> invariantVec = vector_t<Number>(2,1);
    matrix_t<Number> invariantMat = matrix_t<Number>(2,2);
	struct Location<Number>::Invariant inv;
	matrix_t<Number> locationMat = matrix_t<Number>(2,2);

    struct hypro::Transition<Number>::Guard guard;

    struct hypro::Transition<Number>::Reset reset;

    hypro::Location<Number>* locations[2];
    std::set<hypro::Location<Number>*> locSet;

    hypro::Location<Number>* init[1];
    std::set<hypro::Location<Number>*> initLocSet;

    hypro::Transition<Number>* transition[1];
	std::set<hypro::Transition<Number>*> transSet;

	vector_t<Number> coordinates = vector_t<Number>(2,1);
    valuation_t<Number> poly;
};

/**
 * Location Test
 */
TYPED_TEST(HybridAutomataTest, LocationTest)
{
    //invariant: vector
    EXPECT_EQ(this->loc1->invariant().vec, this->invariantVec);
    EXPECT_EQ(this->loc2->invariant().vec, this->invariantVec);

	vector_t<TypeParam> invariantVec2(2,1);
	invariantVec2(0) = 10;
	invariantVec2(1) = 10;
	EXPECT_NE(this->loc1->invariant().vec, invariantVec2);

	//invariant: matrix
	EXPECT_EQ(this->loc1->invariant().mat, this->invariantMat);
	EXPECT_EQ(this->loc2->invariant().mat, this->invariantMat);

	matrix_t<TypeParam> invariantMat2(2,2);
	invariantMat2(0,0) = 1;
	invariantMat2(0,1) = 0;
	invariantMat2(1,0) = 0;
	invariantMat2(1,1) = 3;
	EXPECT_NE(this->loc1->invariant().mat, invariantMat2);

	//location: matrix
	EXPECT_EQ(this->loc1->flow(), this->locationMat);

	matrix_t<TypeParam> locationMat2(2,2);
	locationMat2(0,0) = 1;
	locationMat2(0,1) = 0;
	locationMat2(1,0) = 0;
	locationMat2(1,1) = 1;
	EXPECT_NE(this->loc1->flow(), locationMat2);

	//location: set of outgoing transitions
	EXPECT_EQ(this->loc1->transitions(), this->transSet);
}

/**
 * Transition Test
 */
TYPED_TEST(HybridAutomataTest, TransitionTest)
{
	//transition: Start Location
	EXPECT_EQ(this->trans->source(), this->loc1);

	//transition: End Location
	EXPECT_EQ(this->trans->target(),this-> loc2);

	//transition: Assignment
	EXPECT_EQ(this->trans->reset().vec, this->reset.vec);
	EXPECT_EQ(this->trans->reset().mat, this->reset.mat);

	//transition: Guard
	EXPECT_EQ(this->trans->guard().vec, this->guard.vec);
	EXPECT_EQ(this->trans->guard().mat, this->guard.mat);

}

/**
 * Hybrid Automaton Test
 */
TYPED_TEST(HybridAutomataTest, HybridAutomatonTest)
{
	//hybrid automaton: initial Location
	//EXPECT_EQ(this->hybrid.initialLocations(), this->initLocSet);
	//EXPECT_NE(this->hybrid.initialLocations(), this->locSet);

	//hybrid automaton: Location set
	EXPECT_EQ(this->hybrid.locations(), this->locSet);
	EXPECT_NE(this->hybrid.locations(), this->initLocSet);

	//hybrid automaton: Transition set
	EXPECT_EQ(this->hybrid.transitions(), this->transSet);

	//hybrid automaton: initial Valuation
	//equivalence has to be confirmed through console output
#ifdef fReach_DEBUG
	//this->hybrid.initialValuation().print();
	this->poly.print();
#endif

}
