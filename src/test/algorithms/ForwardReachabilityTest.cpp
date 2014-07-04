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
        
        std::cout << "Poly: " << std::endl;
        poly.print();

    	hybrid.setValuation(poly);


    	/*
    	 * Testing of other ways to construct a polytope
    	 */

		 // should work (change in other test also)
    	coordinates(0) = 2;
    	coordinates(1) = 3;

    	std::vector< vector_t <double> > vecSet;
    	vecSet.push_back(coordinates);

    	//poly = Polytope<double>(vecSet);

    	//--------
    	std::map<carl::Variable, double> coordinate;
    	coordinate.insert( std::make_pair(x, 0) );
    	coordinate.insert( std::make_pair(y, 0) );
    	p1 = Point<double>(coordinate);

    	std::cout << "PointPolyGeneratorStart" << std::endl;

    	pPoly = Polytope<double>(p1);

    	std::cout << "PointPolyGeneratorEnd" << std::endl;
    }

    virtual void TearDown()
    {
    	//TODO: tear down
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


TEST_F(ForwardReachabilityTest, ComputeForwardTimeClosureTest)
{
	std::vector<hypro::valuation_t<double>> flowpipe;

	//flowpipe = forwardReachability::computeForwardTimeClosure(*loc1, poly);

	//TODO should work, probably doesn't because of FLOAT_T<Number> instead of simply Number
	//hypro::matrix_t<double> expMat(2,2);
	//expMat = invariantMat.exp();

	Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> testMat(2,2);
	testMat(0,0) = 1;
   	testMat(0,1) = 0;
   	testMat(1,0) = 0;
   	testMat(1,1) = 1;

	Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> exponentialMat(2,2);
   	exponentialMat = testMat.exp();

   	//---------
   	/*

   	//check size of flowpipe
   	int size = flowpipe.size();
   	EXPECT_EQ(size,5);

   	//check each Segment of the flowpipe
	hypro::vector_t<double> pointVec = hypro::vector_t<double>(4,1);
	Polytope<double> pointPoly;

	//first Segment
  	EXPECT_EQ(flowpipe.front(), poly);   //currently doesn't work (<< Operator)

	pointVec(0) = 1;
	pointVec(1) = -1;
	pointVec(2) = 1;
	pointVec(3) = -1;
	pointPoly = Polytope<double>(boxMat,pointVec);
	EXPECT_TRUE(flowpipe.front().contains(pointPoly));

	pointVec(0) = 2;
	pointVec(1) = -2;
	pointVec(2) = 2;
	pointVec(3) = -2;
	pointPoly = Polytope<double>(boxMat,pointVec);
	EXPECT_FALSE(flowpipe.front().contains(pointPoly));

	//second Segment
	pointVec(0) = 2;
	pointVec(1) = -2;
	pointVec(2) = 2;
	pointVec(3) = -2;
	pointPoly = Polytope<double>(boxMat,pointVec);
	EXPECT_TRUE(flowpipe[1].contains(pointPoly));

	pointVec(0) = 3;
	pointVec(1) = -3;
	pointVec(2) = 3;
	pointVec(3) = -3;
	pointPoly = Polytope<double>(boxMat,pointVec);
	EXPECT_FALSE(flowpipe[1].contains(pointPoly));

	//third Segment
	pointVec(0) = 4;
	pointVec(1) = -4;
	pointVec(2) = 4;
	pointVec(3) = -4;
	pointPoly = Polytope<double>(boxMat,pointVec);
	EXPECT_TRUE(flowpipe[2].contains(pointPoly));

	pointVec(0) = 5;
	pointVec(1) = -5;
	pointVec(2) = 5;
	pointVec(3) = -5;
	pointPoly = Polytope<double>(boxMat,pointVec);
	EXPECT_FALSE(flowpipe[2].contains(pointPoly));

	//fourth Segment
	pointVec(0) = 8;
	pointVec(1) = -8;
	pointVec(2) = 8;
	pointVec(3) = -8;
	pointPoly = Polytope<double>(boxMat,pointVec);
	EXPECT_TRUE(flowpipe[3].contains(pointPoly));

	pointVec(0) = 9;
	pointVec(1) = -9;
	pointVec(2) = 9;
	pointVec(3) = -9;
	pointPoly = Polytope<double>(boxMat,pointVec);
	EXPECT_FALSE(flowpipe[3].contains(pointPoly));

	//fifth Segment
	pointVec(0) = 16;
	pointVec(1) = -16;
	pointVec(2) = 16;
	pointVec(3) = -16;
	pointPoly = Polytope<double>(boxMat,pointVec);
	EXPECT_TRUE(flowpipe[4].contains(pointPoly));

	pointVec(0) = 17;
	pointVec(1) = -17;
	pointVec(2) = 17;
	pointVec(3) = -17;
	pointPoly = Polytope<double>(boxMat,pointVec);
	EXPECT_FALSE(flowpipe[4].contains(pointPoly));
	*/
}

TEST_F(ForwardReachabilityTest, ComputeReachTest)
{

}

TEST_F(ForwardReachabilityTest, ComputeForwardsReachabilityTest)
{

}

TEST_F(ForwardReachabilityTest, ContainmentTest)
{

	/*
	 * Tests based on Polytope(Point) construktor
	 */

	/**TODO
	*C++ exception with description "PPL::C_Polyhedron::contains(y):
	*this->space_dimension() == 2, y.space_dimension() == 4." thrown in the test body.

	bool cTest = poly.contains(pPoly);

	EXPECT_TRUE(cTest);

	//coordinate.insert( std::make_pair(x, 0) );
    //coordinate.insert( std::make_pair(y, 0) );
	*/

	/*
	 * Tests based on Polytope(Matrix,Vektor) constructor
	 */
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
