/**
 * Testfile for the reachability computation based on polytopes.
 * Author: ckugler
 */

#include "gtest/gtest.h"
#include "../defines.h"
#include "../../lib/datastructures/hybridAutomata/Location.h"
#include "../../lib/datastructures/hybridAutomata/Transition.h"
#include "../../lib/datastructures/hybridAutomata/HybridAutomaton.h"
#include <carl/core/VariablePool.h>
#include "../../lib/datastructures/Point.h"
#include "../../lib/algorithms/reachability/forwardReachability.h"


using namespace hypro;
using namespace carl;

class ForwardReachabilityTest : public ::testing::Test
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
    	invariantVec(2) = 1;

    	invariantOp = LEQ;

    	invariantMat(0,0) = 1;
    	invariantMat(0,1) = 0;
    	invariantMat(0,2) = 0;
    	invariantMat(1,0) = 0;
    	invariantMat(1,1) = 1;
    	invariantMat(1,2) = 0;
    	invariantMat(2,0) = 0;
    	invariantMat(2,1) = 0;
    	invariantMat(2,2) = 1;

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
    	trans->setStartLoc(loc1);
    	trans->setTargetLoc(loc2);
    	trans->setAssignment(assign);

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

    	//create Box (note: 3rd variable is for the constant factor)
    	boxVec(0) = 1;
    	boxVec(1) = 0;
    	boxVec(2) = 1;
    	boxVec(3) = 0;
    	boxVec(4) = 1;
    	boxVec(5) = -1;

    	boxMat(0,0) = 1;
    	boxMat(0,1) = 0;
    	boxMat(0,2) = 0;
    	boxMat(1,0) = -1;
    	boxMat(1,1) = 0;
    	boxMat(1,2) = 0;
    	boxMat(2,0) = 0;
    	boxMat(2,1) = 1;
    	boxMat(2,2) = 0;
    	boxMat(3,0) = 0;
    	boxMat(3,1) = -1;
    	boxMat(3,2) = 0;
    	boxMat(4,0) = 0;
    	boxMat(4,1) = 0;
    	boxMat(4,2) = 1;
    	boxMat(5,0) = 0;
    	boxMat(5,1) = 0;
    	boxMat(5,2) = -1;

    	poly = Polytope<double>(boxMat,boxVec);

    	hybrid.setValuation(poly);


    	/*
    	 * Testing of other ways to construct a polytope
    	 */

    	coordinates(0) = 1;
    	coordinates(1) = 1;

    	std::vector< vector_t <double> > vecSet;
    	vecSet.push_back(coordinates);

    	pPoly = Polytope<double>(vecSet);

    	//--------
    	p1 = Point<double>({1,1});

    	pPoly = Polytope<double>(p1);

    }

    virtual void TearDown()
    {
    	//TODO: tear down
    }

    //Hybrid Automaton Objects: Locations, Transitions, Automaton itself
    Location<double>* loc1 = new Location<double>();
    Location<double>* loc2 = new Location<double>();
    hypro::Transition<double>* trans = new hypro::Transition<double>();
    HybridAutomaton<double> hybrid = HybridAutomaton<double>();

    //Other Objects: Vectors, Matrices, Guards...
    vector_t<double> invariantVec = vector_t<double>(3,1);
    operator_e invariantOp;
    matrix_t<double> invariantMat = matrix_t<double>(3,3);
	struct Location<double>::invariant inv;
	matrix_t<double> locationMat = matrix_t<double>(3,3);

    struct hypro::Transition<double>::guard guard;

    struct hypro::Transition<double>::assignment assign;

    hypro::Location<double>* locations[2];
    std::set<hypro::Location<double>*> locSet;

    hypro::Location<double>* init[1];
    std::set<hypro::Location<double>*> initLocSet;

    hypro::Transition<double>* transition[1];
	std::set<hypro::Transition<double>*> transSet;

	vector_t<double> coordinates = vector_t<double>(2,1);
    Point<double> p1;
    hypro::Polytope<double> poly;
    hypro::Polytope<double> pPoly;

    //Box
    vector_t<double> boxVec = vector_t<double>(6,1);
    matrix_t<double> boxMat = matrix_t<double>(6,3);
};

/**
 * Test for function computePostCondition()
 */
TEST_F(ForwardReachabilityTest, ComputePostConditionTest)
{
	hypro::valuation_t<double> result;
	bool inside = forwardReachability::computePostCondition(*trans, poly, result);
	EXPECT_TRUE(inside);

	//place box outside of guard
	boxVec(0) = 18;
	boxVec(1) = -17;
	boxVec(2) = 18;
	boxVec(3) = -17;

	Polytope<double> oPoly;
	oPoly = Polytope<double>(boxMat,boxVec);

	bool outside = forwardReachability::computePostCondition(*trans, oPoly, result);
	EXPECT_FALSE(outside);
}

/**
 * Test for function computeForwardTimeClosure()
 */
TEST_F(ForwardReachabilityTest, ComputeForwardTimeClosureTest)
{

	std::vector<hypro::valuation_t<double>> flowpipe;

#ifdef fReach_DEBUG
   	std::cout << "original Polytope (Box): ";
    poly.print();
#endif

	flowpipe = forwardReachability::computeForwardTimeClosure(*loc1, poly);

   	//check size of flowpipe
#ifdef fReach_DEBUG
   	int size = flowpipe.size();

   	std::cout <<  "Flowpipe size: ";
   	std::cout << size << std::endl;
#endif

}

/**
 * Test for function computeForwardsReachability()
 */
TEST_F(ForwardReachabilityTest, ComputeForwardsReachabilityTest)
{
	//TODO
}

/**
 * Containment Tests: if polytopes are created correctly
 */
TEST_F(ForwardReachabilityTest, ContainmentTest)
{
	/*
	 * Tests based on Polytope(Matrix,Vector) constructor
	 */
	hypro::vector_t<double> pointVec = hypro::vector_t<double>(6,1);

	pointVec(0) = 0;
	pointVec(1) = 0;
	pointVec(2) = 0;
	pointVec(3) = 0;
	pointVec(4) = 1;
	pointVec(5) = -1;

	Polytope<double> pointPoly;
	pointPoly = Polytope<double>(boxMat,pointVec);

	bool contains = poly.contains(pointPoly);
	EXPECT_TRUE(contains);

	pointVec(0) = 0.5;
	pointVec(1) = -0.5;
	pointVec(2) = 0.75;
	pointVec(3) = -0.75;
	pointVec(4) = 1;
	pointVec(5) = -1;

	pointPoly = Polytope<double>(boxMat,pointVec);

	bool contains2 = poly.contains(pointPoly);
	EXPECT_TRUE(contains2);

	pointVec(0) = 2;
	pointVec(1) = -2;
	pointVec(2) = 2;
	pointVec(3) = -2;
	pointVec(4) = 1;
	pointVec(5) = -1;

	pointPoly = Polytope<double>(boxMat,pointVec);

	bool contains3 = poly.contains(pointPoly);
	EXPECT_FALSE(contains3);

	pointVec(0) = 2;
	pointVec(1) = -2;
	pointVec(2) = 0.5;
	pointVec(3) = -0.5;
	pointVec(4) = 1;
	pointVec(5) = -1;

	pointPoly = Polytope<double>(boxMat,pointVec);

	bool contains4 = poly.contains(pointPoly);
	EXPECT_FALSE(contains4);

}

TEST_F(ForwardReachabilityTest, UtilityTest)
{

	/**
	 * computePolytope() Test
	 */
	hypro::Polytope<double> testBoxPoly;
	int dimension = 4;
	double radius = 5;
	testBoxPoly = hypro::computePolytope(dimension,radius);

	hypro::vector_t<double> pointVec = hypro::vector_t<double>(6,1);

	matrix_t<double> testMat = boxMat;

	pointVec(0) = 5;
	pointVec(1) = 5;
	pointVec(2) = 5;
	pointVec(3) = 5;
	pointVec(4) = 5;
	pointVec(5) = 5;

	Polytope<double> pointPoly;
	pointPoly = Polytope<double>(testMat,pointVec);

	EXPECT_TRUE(pointPoly.contains(testBoxPoly));
	EXPECT_TRUE(testBoxPoly.contains(pointPoly));

	pointVec(0) = 5;
	pointVec(1) = -5;
	pointVec(2) = 5;
	pointVec(3) = -5;
	pointVec(4) = 5;
	pointVec(5) = -5;

	pointPoly = Polytope<double>(testMat,pointVec);
	EXPECT_TRUE(testBoxPoly.contains(pointPoly));

	pointVec(0) = 6;
	pointVec(1) = -6;
	pointVec(2) = 5;
	pointVec(3) = -5;
	pointVec(4) = 5;
	pointVec(5) = -5;

	pointPoly = Polytope<double>(testMat,pointVec);
	EXPECT_FALSE(testBoxPoly.contains(pointPoly));

	/**
	 * convertMatToDouble() Test
	 */
	Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> doubleMat(invariantMat.rows(),invariantMat.cols());
	doubleMat = hypro::convertMatToDouble(invariantMat);
	EXPECT_EQ(invariantMat(0,0).toDouble(), doubleMat(0,0));

	/**
	 * convertMatToFloatT() Test
	 */
	matrix_t<double> floatTMat(doubleMat.rows(),doubleMat.cols());
	floatTMat = hypro::convertMatToFloatT(doubleMat);
	EXPECT_EQ(carl::FLOAT_T<double>(doubleMat(0,0)), floatTMat(0,0));

}

