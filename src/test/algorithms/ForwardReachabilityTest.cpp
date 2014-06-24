#include "gtest/gtest.h"
#include "../defines.h"
#include "../../lib/datastructures/hybridAutomata/Location.h"
#include "../../lib/datastructures/hybridAutomata/Transition.h"
#include "../../lib/datastructures/hybridAutomata/HybridAutomaton.h"
#include "carl/core/VariablePool.h"
#include "../../lib/datastructures/Point.h"
#include "../../lib/algorithms/reachability/forwardReachability.h"


using namespace hypro;
using namespace carl;

class ForwardReachabilityTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
    	/*
    	 * Location
    	 */
    	//invariantVec.insert( std::make_pair(x, 10) );
    	//invariantVec.insert( std::make_pair(y, 20) );
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
    	 * Transition
    	 */
    	guard.op = inv.op;
    	guard.mat = inv.mat;
    	guard.vec = inv.vec;

    	trans->setGuard(guard);
    	trans->setStartLoc(loc1);
    	trans->setTargetLoc(loc2);

    	/*
    	 * Hybrid Automaton
    	 */
    	locations[0] = loc1;
    	locations[1] = loc2;

    	locSet = std::set<hypro::Location<double>*>(locations, locations+2);

    	init[0] = loc1;

    	initLocSet = std::set<hypro::Location<double>*>(init, init+1);

    	hybrid.setLocations(locSet);
    	hybrid.setInitialLocations(initLocSet);

    	transition[0] = trans;

    	transSet = std::set<hypro::Transition<double>*>(transition, transition+1);

    	hybrid.setTransitions(transSet);
    	loc1->setTransitions(transSet);

    	//Polytope for InitialValuation & Guard Assignment
        //coordinates.insert( std::make_pair(x, 2) );
        //coordinates.insert( std::make_pair(y, 3) );
    	coordinates(0) = 2;
    	coordinates(1) = 3;

    	std::map<carl::Variable, double> coordinate;
        coordinate.insert( std::make_pair(x, 2) );
        coordinate.insert( std::make_pair(y, 3) );
        p1 = Point<double>(coordinate);

    	poly = Polytope<double>(p1);

    	hybrid.setValuation(poly);
    	trans->setAssignment(poly);
    }

    virtual void TearDown()
    {
    	//TODO
    	//std::cout << loc1.invariant().mat << std::endl;
    }

    //Variable Objects
    carl::VariablePool& pool = carl::VariablePool::getInstance();
    carl::Variable x = pool.getFreshVariable("x");
    carl::Variable y = pool.getFreshVariable("y");

    //Hybrid Automaton Objects: Locations, Transitions, Automaton itself
    Location<double>* loc1 = new Location<double>();
    Location<double>* loc2 = new Location<double>();
    hypro::Transition<double>* trans = new hypro::Transition<double>();
    HybridAutomaton<double> hybrid = HybridAutomaton<double>();

    //Other Objects: Vectors, Matrices, Guards...
    vector_t<double> invariantVec;
    operator_e invariantOp;
    matrix_t<double> invariantMat = matrix_t<double>(2,2);
	struct Location<double>::invariant inv;
	matrix_t<double> locationMat = matrix_t<double>(2,2);

    struct hypro::Transition<double>::guard guard;

    hypro::Location<double>* locations[2];
    std::set<hypro::Location<double>*> locSet;

    hypro::Location<double>* init[1];
    std::set<hypro::Location<double>*> initLocSet;

    hypro::Transition<double>* transition[1];
	std::set<hypro::Transition<double>*> transSet;

	//Point<double>::coordinates_map coordinates;
	vector_t<double> coordinates;
    Point<double> p1;
    hypro::Polytope<double> poly;

};

TEST_F(ForwardReachabilityTest, ComputePostConditionTest)
{
	hypro::valuation_t<double> result;
	hypro::Polytope<double> polytope = hypro::Polytope<double>(trans->guard().mat, trans->guard().vec);
	//matrix_t<FLOAT_T<double>> testMat = matrix_t<FLOAT_T<double>>(2,2);
	//testMat(0,0) = 1;
	//testMat(1,0) = 1;
	//testMat(0,1) = 1;
	//testMat(0,0) = 1;
	//hypro::Polytope<double> poly2 = hypro::Polytope<double>(testMat);
	//hypro::Polytope<double> poly2 = hypro::Polytope<double>(trans->guard().mat);
	bool test = forwardReachability::computePostCondition(*trans, poly, result);
	//EXPECT_TRUE(test);
}

TEST_F(ForwardReachabilityTest, TransitionTest)
{


}

TEST_F(ForwardReachabilityTest, HybridAutomatonTest)
{

}
