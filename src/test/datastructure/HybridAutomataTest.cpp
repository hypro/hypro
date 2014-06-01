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
protected:
    virtual void SetUp()
    {
    	/*
    	 * Location
    	 */

    	vector_t<double> invariantVec;
    	//invariantVec.insert( std::make_pair(x, carl::FLOAT_T<double>(10)) );
    	//invariantVec.insert( std::make_pair(y, carl::FLOAT_T<double>(20)) );
    	invariantVec.insert( std::make_pair(x, 10) );
    	invariantVec.insert( std::make_pair(y, 20) );

    	operator_e invariantOp = LEQ;

    	matrix_t<double> invariantMat(2,2);
    	invariantMat(0,0) = 2;
    	invariantMat(0,1) = 0;
    	invariantMat(1,0) = 0;
    	invariantMat(1,1) = 3;

    	loc1.setInvariant(&invariantMat,invariantVec,invariantOp);

    	struct Location<double>::invariant inv;
    	inv.op = invariantOp;
    	inv.mat = &invariantMat;
    	inv.vec = invariantVec;

    	loc2.setInvariant(inv);

    	matrix_t<double> locationMat(2,2);
    	locationMat(0,0) = 2;
    	locationMat(0,1) = 0;
    	locationMat(1,0) = 0;
    	locationMat(1,1) = 1;

    	loc1.setActivityMat(&locationMat);
    	loc2.setActivityMat(&locationMat);

    	/*
    	 * Transition
    	 */

    	struct hypro::Transition<double>::guard guard;
    	guard.op = inv.op;
    	guard.mat = inv.mat;
    	guard.vec = inv.vec;

    	trans.setGuard(guard);
    	trans.setStartLoc(&loc1);
    	trans.setTargetLoc(&loc2);

    	/*
    	 * Hybrid Automaton
    	 */

    	hypro::Location<double>* locations[] = {&loc1, &loc2};
    	std::set<hypro::Location<double>*> locSet(locations, locations+2);

    	hypro::Location<double>* init[] = {&loc1};
    	std::set<hypro::Location<double>*> initLocSet(init, init+1);

    	hybrid.setLocations(locSet);
    	hybrid.setInitialLocations(initLocSet);

    	hypro::Transition<double>* transition[] = {&trans};
    	std::set<hypro::Transition<double>*> transSet(transition, transition+1);

    	hybrid.setTransitions(transSet);
    	loc1.setTransitions(transSet);

    	//Polytope for InitialValuation
    	//Point<double>::coordinates_map coordinates;
    	vector_t<double> coordinates;
        //coordinates.insert( std::make_pair(x, FLOAT_T<double>(2)) );
        //coordinates.insert( std::make_pair(y, FLOAT_T<double>(3)) );
        coordinates.insert( std::make_pair(x, 2) );
        coordinates.insert( std::make_pair(y, 3) );
        p1 = Point<double>(coordinates);

    	hypro::Polytope<double> poly = Polytope<double>(p1);

    	hybrid.setValuation(poly);
    	trans.setAssignment(poly);


    }

    virtual void TearDown()
    {
    }

    carl::VariablePool& pool = VariablePool::getInstance();
    carl::Variable x = pool.getFreshVariable("x");
    carl::Variable y = pool.getFreshVariable("y");

    // Location<double> loc1; ?
    Location<double> loc1 = Location<double>();
    Location<double> loc2 = Location<double>();
    hypro::Transition<double> trans = hypro::Transition<double>();
    HybridAutomaton<double> hybrid = HybridAutomaton<double>();

    Point<double> p1;

};

/*
TEST_F(HybridAutomataTest, LocationConstructorTest)
{
    //Location<double> locA;
    Eigen::Matrix<carl::FLOAT_T<double>, Eigen::Dynamic, Eigen::Dynamic> matr(2,2);
    
    matr(0,0) = 1.0;
    matr(0,1) = 0.0;
    matr(1,0) = 1.0;
    matr(0,1) = 0.0;
    SUCCEED();
}
*/

TEST_F(HybridAutomataTest, LocationTest)
{
	//invariant: operator
    EXPECT_EQ(loc1.invariant().op,LEQ);
    EXPECT_EQ(loc2.invariant().op,LEQ);
    //EXPECT_EQ(loc2.location().inv.op,LEQ);

    //invariant: vector
	vector_t<double> invariantVec;
	invariantVec.insert( std::make_pair(x, 10) );
	invariantVec.insert( std::make_pair(y, 20) );
    EXPECT_EQ(loc1.invariant().vec, invariantVec);
    //EXPECT_EQ(loc2.invariant().vec, invariantVec);
    //EXPECT_EQ(loc1.location().inv.vec, invariantVec);

	vector_t<double> invariantVec2;
	invariantVec2.insert( std::make_pair(x, 10) );
	invariantVec2.insert( std::make_pair(y, 10) );
	EXPECT_NE(loc1.invariant().vec, invariantVec2);

	//invariant: matrix
	matrix_t<double> invariantMat(2,2);
	invariantMat(0,0) = 2;
	invariantMat(0,1) = 0;
	invariantMat(1,0) = 0;
	invariantMat(1,1) = 3;

	EXPECT_EQ(*loc1.invariant().mat, invariantMat);
	//EXPECT_EQ(*loc2.invariant().mat, invariantMat);

	matrix_t<double> invariantMat2(2,2);
	invariantMat2(0,0) = 1;
	invariantMat2(0,1) = 0;
	invariantMat2(1,0) = 0;
	invariantMat2(1,1) = 3;

	EXPECT_NE(*loc1.invariant().mat, invariantMat2);

	//location: matrix
	matrix_t<double> locationMat(2,2);
	locationMat(0,0) = 2;
	locationMat(0,1) = 0;
	locationMat(1,0) = 0;
	locationMat(1,1) = 1;

	loc1.setActivityMat(&locationMat);
	EXPECT_EQ(*loc1.activityMat(), locationMat);
	//EXPECT_EQ(*loc1.location().mat, locationMat);

	matrix_t<double> locationMat2(2,2);
	locationMat2(0,0) = 1;
	locationMat2(0,1) = 0;
	locationMat2(1,0) = 0;
	locationMat2(1,1) = 1;

	EXPECT_NE(*loc1.activityMat(), locationMat2);

	//location: set of outgoing transitions
/*
	hypro::Transition<double>* transition[] = {&trans};
	std::set<hypro::Transition<double>*> transSet(transition, transition+1);

	EXPECT_EQ(loc1.transitions(), transSet);
*/



}

TEST_F(HybridAutomataTest, TransitionTest)
{
	//transition: Start Location
	//EXPECT_EQ(*trans.startLoc(), loc1);

	//transition: End Location
	//EXPECT_EQ(*trans.targetLoc(), loc2);

	//transition: Assignment
	vector_t<double> coordinates;
    coordinates.insert( std::make_pair(x, 2) );
    coordinates.insert( std::make_pair(y, 3) );
    p1 = Point<double>(coordinates);

	hypro::Polytope<double> poly = Polytope<double>(p1);
	EXPECT_EQ(trans.assignment(), poly);

	//transition: Guard
	struct hypro::Transition<double>::guard guard;
	guard.op = loc1.invariant().op;
	guard.mat = loc1.invariant().mat;
	guard.vec = loc1.invariant().vec;
	//EXPECT_EQ(trans.guard(), guard);

}

TEST_F(HybridAutomataTest, HybridAutomatonTest)
{

}
