/**
 * Testfile for hybrid automata.
 * Author: ckugler
 */

#include "gtest/gtest.h"
#include "../defines.h"
#include "datastructures/HybridAutomaton/LocationManager.h"
#include "datastructures/HybridAutomaton/HybridAutomaton.h"
#include "datastructures/HybridAutomaton/output/Flowstar.h"
#include "util/multithreading/Filewriter.h"
#include "parser/antlr4-flowstar/ParserWrapper.h"


using namespace hypro;

using valuation_t = VPolytope<double>;

class HybridAutomataOutputTest : public ::testing::Test
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


    	trans = new Transition<double>();

		invariantVec(0) = 10;
		invariantVec(1) = 20;

		invariantMat(0,0) = 2;
		invariantMat(0,1) = 0;
		invariantMat(1,0) = 0;
		invariantMat(1,1) = 3;

		loc1->setInvariant(Condition<double>(invariantMat,invariantVec));
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

		locSet = std::set<Location<double>*>(locations, locations+2);
		init[0] = loc1;
		initLocSet = std::set<Location<double>*>(init, init+1);

		//Polytope for InitialValuation & Guard Assignment
		coordinates(0) = 2;
		coordinates(1) = 3;

    	std::vector< vector_t<double> > vecSet;
    	vecSet.push_back(coordinates);
		poly = valuation_t(vecSet);
		auto hpoly = Converter<double>::toHPolytope(poly);

		hybrid.setLocations(locSet);
		for(auto loc : initLocSet) {
			State_t<double> initState(loc);
			initState.setSet(ConstraintSet<double>(hpoly.matrix(), hpoly.vector()));
			hybrid.addInitialState(initState);
		}

		transition[0] = trans;
		transSet = std::set<Transition<double>*>(transition, transition+1);

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

    LocationManager<double>& locMan = LocationManager<double>::getInstance();

    Location<double>* loc1;
    Location<double>* loc2;
    Transition<double>* trans;
    HybridAutomaton<double> hybrid;

    //Other Objects: Vectors, Matrices, Guards...
    vector_t<double> invariantVec = vector_t<double>(2,1);
    matrix_t<double> invariantMat = matrix_t<double>(2,2);
	Condition<double> inv;
	matrix_t<double> locationMat = matrix_t<double>::Zero(3,3);

    Condition<double> guard;

    Reset<double> reset;

    Location<double>* locations[2];
    std::set<Location<double>*> locSet;

    Location<double>* init[1];
    std::set<Location<double>*> initLocSet;

    Transition<double>* transition[1];
	std::set<Transition<double>*> transSet;

	vector_t<double> coordinates = vector_t<double>(2,1);
    valuation_t poly;
};


/**
 * Hybrid Automaton Test
 */
TEST_F(HybridAutomataOutputTest, HybridAutomatonTest)
{
	// construct a new hybrid automaton.
	HybridAutomaton<double> h1;

	h1.addLocation(loc1);
	h1.addLocation(loc2);
	h1.addTransition(trans);

	matrix_t<double> matr = matrix_t<double>::Identity(2,2);
	vector_t<double> vec = vector_t<double>(2);
	vec << 1,2;

	State_t<double> s(loc1);
	s.setSet(ConstraintSet<double>(matr, vec));

	h1.addInitialState(s);

	LockedFileWriter out("tmp.model");
	out.clearFile();
	out << toFlowstarFormat(h1);

	//boost::tuple<HybridAutomaton<double,State_t<double,double>>, ReachabilitySettings<double>> parsedResult = parseFlowstarFile<double>(std::string("tmp.model"));
	//std::remove("tmp.model");

	//EXPECT_EQ(boost::get<0>(parsedResult), h1);
	SUCCEED();
}
