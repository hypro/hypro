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
    	/*
    	vector_t<double> invariantVec;
    	//invariantVec.insert( std::make_pair(x, carl::FLOAT_T<double>(10)) );
    	//invariantVec.insert( std::make_pair(y, carl::FLOAT_T<double>(20)) );
    	invariantVec.insert( std::make_pair(x, 10) );
    	invariantVec.insert( std::make_pair(y, 20) );

    	operator_e invariantOp = LEQ;
*/
    	//matrix_t<double> invariantMat;
    	Eigen::Matrix<carl::FLOAT_T<double>, Eigen::Dynamic, Eigen::Dynamic> invariantMat;
    	invariantMat(0,0) = 2;
    	//invariantMat(0,1) = 0;
    	//invariantMat(1,0) = 0;
    	//invariantMat(1,1) = 3;
/*
    	loc1.setInvariant(&invariantMat,invariantVec,invariantOp);

    	struct Location<double>::invariant inv;
    	inv.op = invariantOp;
    	inv.mat = &invariantMat;
    	inv.vec = invariantVec;

    	loc2.setInvariant(inv);

    	matrix_t<double> locationMat;
    	locationMat(0,0) = 2;
    	locationMat(0,1) = 0;
    	locationMat(1,0) = 0;
    	locationMat(1,1) = 1;

    	loc1.setActivityMat(&locationMat);
    	loc2.setActivityMat(&locationMat);

    	/*
    	 * Transition
    	 */
    	/*
    	struct Transition<double>::guard guard;
    	guard.op = inv.op;
    	guard.mat = inv.mat;
    	guard.vec = inv.vec;

    	trans.setGuard(guard);
    	trans.setStartLoc(&loc1);
    	trans.setTargetLoc(&loc2);

    	/*
    	 * Hybrid Automaton
    	 */
    	/*
    	hypro::Location<double>* locations[] = {&loc1, &loc2};
    	std::set<hypro::Location<double>*> locSet(locations, locations+2);

    	hypro::Location<double>* init[] = {&loc1};
    	std::set<hypro::Location<double>*> initLocSet(init, init+1);

    	hybrid.setLocations(locSet);
    	hybrid.setInitialLocations(initLocSet);

    	hypro::Transition<double>* transition[] = {&trans};
    	std::set<hypro::Transition<double>*> transSet(transition, transition+1);

    	hybrid.setTransitions(transSet);

    	//Polytope for InitialValuation
    	Point<double>::coordinates_map coordinates;
        //coordinates.insert( std::make_pair(x, FLOAT_T<double>(2)) );
        //coordinates.insert( std::make_pair(y, FLOAT_T<double>(3)) );
        coordinates.insert( std::make_pair(x, 2) );
        coordinates.insert( std::make_pair(y, 3) );
        p1 = Point<double>(coordinates);

    	hypro::Polytope<double> poly = Polytope<double>(p1);

    	hybrid.setValuation(poly);
    	*/

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
    Transition<double> trans = Transition<double>();
    HybridAutomaton<double> hybrid = HybridAutomaton<double>();

    Point<double> p1;

};

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

TEST_F(HybridAutomataTest, LocationTest)
{
    //EXPECT_EQ(loc1.invariant().op,LEQ);
    //EXPECT_EQ(1,1);
}

TEST_F(HybridAutomataTest, TransitionTest)
{

}

TEST_F(HybridAutomataTest, HybridAutomatonTest)
{

}
