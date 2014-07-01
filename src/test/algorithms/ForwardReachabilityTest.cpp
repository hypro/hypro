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
    	invariantVec(0) = 16;
    	invariantVec(1) = 16;

    	invariantOp = LEQ;

    	invariantMat(0,0) = 1;
    	invariantMat(0,1) = 0;
    	invariantMat(1,0) = 0;
    	invariantMat(1,1) = 1;

    	loc1->setInvariant(invariantMat,invariantVec,invariantOp);

    	inv.op = invariantOp;
    	inv.mat = invariantMat;
    	inv.vec = invariantVec;

    	loc2->setInvariant(inv);

    	locationMat(0,0) = 2;
    	locationMat(0,1) = 0;
    	locationMat(1,0) = 0;
    	locationMat(1,1) = 2;

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


		 //* should work (change in other test also)
    	coordinates(0) = 2;
    	coordinates(1) = 3;

		std::vector< vector_t <double> > vecSet;


		std::vector< vector_t <double> >::iterator it;
		//TODO ERROR inserting does not work? "no match for < operator"
		vecSet.push_back(coordinates);

		//poly = Polytope<double>(vecSet);


    	std::map<carl::Variable, double> coordinate;
        coordinate.insert( std::make_pair(x, 0) );
        coordinate.insert( std::make_pair(y, 0) );
        p1 = Point<double>(coordinate);

    	pPoly = Polytope<double>(p1);

    	//hybrid.setValuation(poly);


    	//create Box
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

    	//TODO ERROR polytope.tpp:77
    	poly = Polytope<double>(boxMat,boxVec);

    	//hybrid.setValuation(poly);
    }

    virtual void TearDown()
    {
    	//todo: tear down
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
    vector_t<double> invariantVec = vector_t<double>(2,1);
    operator_e invariantOp;
    matrix_t<double> invariantMat = matrix_t<double>(2,2);
	struct Location<double>::invariant inv;
	matrix_t<double> locationMat = matrix_t<double>(2,2);

    struct hypro::Transition<double>::guard guard;

    struct hypro::Transition<double>::assignment assign;

    hypro::Location<double>* locations[2];
    std::set<hypro::Location<double>*> locSet;

    hypro::Location<double>* init[1];
    std::set<hypro::Location<double>*> initLocSet;

    hypro::Transition<double>* transition[1];
	std::set<hypro::Transition<double>*> transSet;

	//Point<double>::coordinates_map coordinates;
	vector_t<double> coordinates = vector_t<double>(2,1);
    Point<double> p1;
    hypro::Polytope<double> poly;
    hypro::Polytope<double> pPoly;

    //Box
    vector_t<double> boxVec = vector_t<double>(4,1);
    matrix_t<double> boxMat = matrix_t<double>(4,2);
};

TEST_F(ForwardReachabilityTest, ComputePostConditionTest)
{
	hypro::valuation_t<double> result;

	//TODO ERROR polytope.tpp:207   (linearTransformation(...) in computePostCondition)
	bool test = forwardReachability::computePostCondition(*trans, poly, result);
	EXPECT_TRUE(test);
}

TEST_F(ForwardReachabilityTest, ContainmentTest)
{

	//bool cTest = poly.contains(pPoly);

	//EXPECT_TRUE(cTest);

    //coordinate.insert( std::make_pair(x, 0) );
    //coordinate.insert( std::make_pair(y, 0) );

	hypro::vector_t<double> pointVec = hypro::vector_t<double>(4,1);

	pointVec(0) = 0;
	pointVec(1) = 0;
	pointVec(2) = 0;
	pointVec(3) = 0;

	Polytope<double> pointPoly;
	pointPoly = Polytope<double>(boxMat,pointVec);

	bool contains = poly.contains(pointPoly);
	EXPECT_TRUE(contains);

	pointVec(0) = 0.5;
	pointVec(1) = -0.5;
	pointVec(2) = 0.75;
	pointVec(3) = -0.75;

	pointPoly = Polytope<double>(boxMat,pointVec);

	bool contains2 = poly.contains(pointPoly);
	EXPECT_TRUE(contains2);

	pointVec(0) = 2;
	pointVec(1) = -2;
	pointVec(2) = 2;
	pointVec(3) = -2;

	pointPoly = Polytope<double>(boxMat,pointVec);

	bool contains3 = poly.contains(pointPoly);
	EXPECT_FALSE(contains3);

	pointVec(0) = 2;
	pointVec(1) = -2;
	pointVec(2) = 0.5;
	pointVec(3) = -0.5;

	pointPoly = Polytope<double>(boxMat,pointVec);

	bool contains4 = poly.contains(pointPoly);
	EXPECT_FALSE(contains4);







}

TEST_F(ForwardReachabilityTest, HybridAutomatonTest)
{

}
