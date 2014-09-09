#include "gtest/gtest.h"
#include "../defines.h"
#include "../../lib/datastructures/hybridAutomata/util.h"
#include <carl/core/VariablePool.h>
#include "../../lib/datastructures/Point.h"


using namespace hypro;
using namespace carl;

class MinkowskiSumTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {

    	/**
    	 * first Polytope
    	 */
    	coordinates(0) = 1;
    	coordinates(1) = 1;

    	std::vector< vector_t <double> > vecSet;
    	vecSet.push_back(coordinates);

    	coordinates(0) = 0;
    	coordinates(1) = 0;
    	vecSet.push_back(coordinates);

    	coordinates(0) = 0;
    	coordinates(1) = 1;
    	vecSet.push_back(coordinates);

    	coordinates(0) = 1;
    	coordinates(1) = 0;
    	vecSet.push_back(coordinates);

    	poly = Polytope<double>(vecSet);

	    /**
	     * second Polytope
	     */
    	coordinates(0) = 4;
    	coordinates(1) = 4;

    	std::vector< vector_t <double> > vecSet2;
    	vecSet2.push_back(coordinates);

    	coordinates(0) = 3;
    	coordinates(1) = 3;
    	vecSet2.push_back(coordinates);

    	coordinates(0) = 3;
    	coordinates(1) = 4;
    	vecSet2.push_back(coordinates);

    	coordinates(0) = 4;
    	coordinates(1) = 3;
    	vecSet2.push_back(coordinates);

    	poly2 = Polytope<double>(vecSet2);

	    /**
	     * one Polytope with Adjacency set up
	     */

    	Point<double>::coordinateMap coordinate;
    	coordinate.insert( std::make_pair(x, 1) );
    	coordinate.insert( std::make_pair(y, 1) );
    	t1 = new Point<double>(coordinate);

    	Point<double>::coordinateMap coordinate2;
    	coordinate2.insert( std::make_pair(x, 0) );
    	coordinate2.insert( std::make_pair(y, 0) );
    	t2 = new Point<double>(coordinate2);

    	Point<double>::coordinateMap coordinate3;
    	coordinate3.insert( std::make_pair(x, 0) );
    	coordinate3.insert( std::make_pair(y, 1) );
    	t3 = new Point<double>(coordinate3);

    	Point<double>::coordinateMap coordinate4;
    	coordinate4.insert( std::make_pair(x, 1) );
    	coordinate4.insert( std::make_pair(y, 0) );
    	t4 = new Point<double>(coordinate4);

	    t1->addNeighbor(t3);
	    t1->addNeighbor(t4);

	    t2->addNeighbor(t3);
	    t2->addNeighbor(t4);

	    t3->addNeighbor(t1);
	    t3->addNeighbor(t2);

	    t4->addNeighbor(t1);
	    t4->addNeighbor(t2);

    	polyAdj.addPoint(*t1);
    	polyAdj.addPoint(*t2);
    	polyAdj.addPoint(*t3);
    	polyAdj.addPoint(*t4);

	    /**
	     * another Polytope with Adjacency set up
	     */
    	Point<double>::coordinateMap coordinate5;
    	coordinate5.insert( std::make_pair(x, 2) );
    	coordinate5.insert( std::make_pair(y, 2) );
    	t5 = new Point<double>(coordinate5);

    	Point<double>::coordinateMap coordinate6;
    	coordinate6.insert( std::make_pair(x, 1) );
    	coordinate6.insert( std::make_pair(y, 1) );
    	t6 = new Point<double>(coordinate6);

    	Point<double>::coordinateMap coordinate7;
    	coordinate7.insert( std::make_pair(x, 1) );
    	coordinate7.insert( std::make_pair(y, 2) );
    	t7 = new Point<double>(coordinate7);

    	Point<double>::coordinateMap coordinate8;
    	coordinate8.insert( std::make_pair(x, 2) );
    	coordinate8.insert( std::make_pair(y, 1) );
    	t8 = new Point<double>(coordinate8);

	    t5->addNeighbor(t7);
	    t5->addNeighbor(t8);

	    t6->addNeighbor(t7);
	    t6->addNeighbor(t8);

	    t7->addNeighbor(t5);
	    t7->addNeighbor(t6);

	    t8->addNeighbor(t5);
	    t8->addNeighbor(t6);

    	polyAdj2.addPoint(*t5);
    	polyAdj2.addPoint(*t6);
    	polyAdj2.addPoint(*t7);
    	polyAdj2.addPoint(*t8);

    	/**
    	 * the 3D Test Setup
    	 */
    	q1 = new Point<double>({0,0,0});
    	q2 = new Point<double>({1,0,0});
    	q3 = new Point<double>({1,1,0});
    	q4 = new Point<double>({0,1,0});
    	q5 = new Point<double>({0,0,1});
    	q6 = new Point<double>({1,0,1});
    	q7 = new Point<double>({1,1,1});
    	q8 = new Point<double>({0,1,1});

    	q1->addNeighbor(q2);
    	q1->addNeighbor(q4);
    	q1->addNeighbor(q5);

    	q2->addNeighbor(q3);
    	q2->addNeighbor(q1);
    	q2->addNeighbor(q6);

    	q3->addNeighbor(q2);
    	q3->addNeighbor(q4);
    	q3->addNeighbor(q7);

    	q4->addNeighbor(q3);
    	q4->addNeighbor(q1);
    	q4->addNeighbor(q8);

    	q5->addNeighbor(q6);
    	q5->addNeighbor(q8);
    	q5->addNeighbor(q1);

    	q6->addNeighbor(q7);
    	q6->addNeighbor(q5);
    	q6->addNeighbor(q2);

    	q7->addNeighbor(q6);
    	q7->addNeighbor(q8);
    	q7->addNeighbor(q3);

    	q8->addNeighbor(q7);
    	q8->addNeighbor(q5);
    	q8->addNeighbor(q4);

    	polyQ.addPoint(*q1);
    	polyQ.addPoint(*q2);
    	polyQ.addPoint(*q3);
    	polyQ.addPoint(*q4);
    	polyQ.addPoint(*q5);
    	polyQ.addPoint(*q6);
    	polyQ.addPoint(*q7);
    	polyQ.addPoint(*q8);

    	//seccond Poly
    	p1 = new Point<double>({1,1,0});
    	p2 = new Point<double>({2,1,0});
    	p3 = new Point<double>({2,2,0});
    	p4 = new Point<double>({1,2,0});
    	p5 = new Point<double>({1,1,1});
    	p6 = new Point<double>({2,1,1});
    	p7 = new Point<double>({2,2,1});
    	p8 = new Point<double>({1,2,1});

    	p1->addNeighbor(p2);
    	p1->addNeighbor(p4);
    	p1->addNeighbor(p5);

    	p2->addNeighbor(p3);
    	p2->addNeighbor(p1);
    	p2->addNeighbor(p6);

    	p3->addNeighbor(p2);
    	p3->addNeighbor(p4);
    	p3->addNeighbor(p7);

    	p4->addNeighbor(p3);
    	p4->addNeighbor(p1);
    	p4->addNeighbor(p8);

    	p5->addNeighbor(p6);
    	p5->addNeighbor(p8);
    	p5->addNeighbor(p1);

    	p6->addNeighbor(p7);
    	p6->addNeighbor(p5);
    	p6->addNeighbor(p2);

    	p7->addNeighbor(p6);
    	p7->addNeighbor(p8);
    	p7->addNeighbor(p3);

    	p8->addNeighbor(p7);
    	p8->addNeighbor(p5);
    	p8->addNeighbor(p4);

    	polyP.addPoint(*p1);
    	polyP.addPoint(*p2);
    	polyP.addPoint(*p3);
    	polyP.addPoint(*p4);
    	polyP.addPoint(*p5);
    	polyP.addPoint(*p6);
    	polyP.addPoint(*p7);
    	polyP.addPoint(*p8);
    }

    virtual void TearDown()
    {
    	//TODO: tear down

    }
    carl::VariablePool& pool = carl::VariablePool::getInstance();
    carl::Variable x = pool.getFreshVariable("x");
    carl::Variable y = pool.getFreshVariable("y");

    Point<double>* t1;
    Point<double>* t2;
    Point<double>* t3;
    Point<double>* t4;

    Point<double>* t5;
    Point<double>* t6;
    Point<double>* t7;
    Point<double>* t8;

    hypro::Polytope<double> poly;
    hypro::Polytope<double> poly2;
    hypro::Polytope<double> polyAdj = Parma_Polyhedra_Library::C_Polyhedron(0,EMPTY);
    hypro::Polytope<double> polyAdj2 = Parma_Polyhedra_Library::C_Polyhedron(0,EMPTY);

	vector_t<double> coordinates = vector_t<double>(2,1);

	//for 3D
    Point<double>* q1;
    Point<double>* q2;
    Point<double>* q3;
    Point<double>* q4;
    Point<double>* q5;
    Point<double>* q6;
    Point<double>* q7;
    Point<double>* q8;

    Point<double>* p1;
    Point<double>* p2;
    Point<double>* p3;
    Point<double>* p4;
    Point<double>* p5;
    Point<double>* p6;
    Point<double>* p7;
    Point<double>* p8;

    hypro::Polytope<double> polyQ = Parma_Polyhedra_Library::C_Polyhedron(0,EMPTY);
    hypro::Polytope<double> polyP = Parma_Polyhedra_Library::C_Polyhedron(0,EMPTY);
};

TEST_F(MinkowskiSumTest, computeMaxPointTest)
{
   	std::cout << "Minkowski Sum - Polytope 1: ";
    poly.print();
  	std::cout << "Minkowski Sum - Polytope 2: ";
    poly2.print();

    std::cout << "Size Poly1: " << poly.points().size() << std::endl;

	Point<double> res = poly.computeMaxPoint();
	std::cout << "Point 1: " << res << std::endl;

	Point<double> res2 = poly2.computeMaxPoint();
	std::cout << "Point 2: " << res2 << std::endl;
}

TEST_F(MinkowskiSumTest, computeInitVertexTest)
{
   	std::cout << "Minkowski Sum - Polytope 1: ";
    poly.print();
  	std::cout << "Minkowski Sum - Polytope 2: ";
    poly2.print();

	Point<double> res = poly.computeInitVertex(poly2);
	std::cout << "Point v*: " << res << std::endl;

    std::cout << "v* composed of: " << res.composedOf() << std::endl;

	Polytope<double> result;
	bool temp = poly.minkowskiSum(result,poly2);
	ASSERT_TRUE(temp);
	std::cout << "--------" << std::endl;
	std::cout << "as comparison - original MinkowskiSum result: ";
	result.print();
}

TEST_F(MinkowskiSumTest, computeMaxVDegreeTest)
{
   	std::cout << "Minkowski Sum - Adjacency Polytope: ";
    polyAdj.print();

    std::vector<Point<double>> tmp = polyAdj.points();

    std::vector<Point<double>>::iterator it=tmp.begin();
    std::cout << "Point iterator (first Element): " << (*it) << std::endl;

	int result = polyAdj.computeMaxVDegree();
	std::cout << "Max Vertex Degree: " << result << std::endl;
}

TEST_F(MinkowskiSumTest, computePointTest)
{
	vector_t<double> edge = vector_t<double>(2,1);
	edge(0) = 3;
	edge(1) = 4;

	Point<double> result = polytope::computePoint(*t1, edge, false);
	std::cout << "source Point: " << t1 << std::endl;
	std::cout << "Edge: " << std::endl;
	std::cout << edge << std::endl;
	std::cout << "computed Point: " << result << std::endl;
}

TEST_F(MinkowskiSumTest, computeEdgeTest)
{
	Point<double> p;
	Point<double>::coordinateMap coordinateMap;
	coordinateMap.insert( std::make_pair(x, 4) );
	coordinateMap.insert( std::make_pair(y, 3) );
	p = Point<double>(coordinateMap);

	vector_t<double> result = polytope::computeEdge(*t1, p);
	std::cout << "source Point: " << t1 << std::endl;
	std::cout << "target Point: " << p << std::endl;
	std::cout << "computed Edge: " << std::endl;
	std::cout << result << std::endl;

}

TEST_F(MinkowskiSumTest, adjOracleTest)
{
	Point<double> res = polyAdj.computeInitVertex(polyAdj2);
	std::cout << "Point v*: " << res << std::endl;

	Point<double> adjPoint;
	std::pair<int,int> counter;
	counter.first = 1;
	counter.second = 1;

	bool exists = polytope::adjOracle(adjPoint, res, counter);
	std::cout << "AdjOracle return value: " << exists << std::endl;
	std::cout << "Computed Point: " << adjPoint << std::endl;
}

TEST_F(MinkowskiSumTest, computeMaximizerVectorTest)
{
	Point<double> v = polyAdj.computeInitVertex(polyAdj2);
	std::cout << "Point v*: " << v << std::endl;

	Point<double> target;
	vector_t<double> result = polytope::computeMaximizerVector(target, v);
	std::cout << "Vector: " << std::endl;
	std::cout << result << std::endl;
	std::cout << "Target Vertex: " << target << std::endl;
}

TEST_F(MinkowskiSumTest, computeNormalConeVectorTest)
{
	Point<double> p;
	Point<double>::coordinateMap coordinateMap;
	coordinateMap.insert( std::make_pair(x, 0) );
	coordinateMap.insert( std::make_pair(y, 1) );
	p = Point<double>(coordinateMap);

	vector_t<double> result = polytope::computeEdge(*t1, p);
	std::cout << "source Point: " << t1 << std::endl;
	std::cout << "target Point: " << p << std::endl;
	std::cout << "Edge: " << std::endl;
	std::cout << result << std::endl;

	std::vector<vector_t<double>> edgeSet;
	edgeSet.push_back(result);

	//for the maximizer vector we need v=v1+v2
	Point<double> v = polyAdj.computeInitVertex(polyAdj2);
	Point<double> target;
	vector_t<double> maximizer = polytope::computeMaximizerVector(target, v);
	std::cout << "Maximizer Vector: " << std::endl;
	std::cout << maximizer << std::endl;

	vector_t<double> resultingEdge = polytope::computeNormalConeVector<double>(edgeSet, maximizer);
	std::cout << "Computed Edge (Scalar Product <= 0): " << std::endl;
	std::cout << resultingEdge << std::endl;
}
/*
TEST_F(MinkowskiSumTest, localSearchTest)
{
	Polytope<double> sumPoly = Parma_Polyhedra_Library::C_Polyhedron(0,EMPTY);

	Point<double> initVertex = polyAdj.computeInitVertex(polyAdj2);
	std::cout << "Point v*: " << initVertex << std::endl;
	std::cout << "-------------------------" << std::endl;

	sumPoly.addPoint(initVertex);

	Point<double> adjPoint;
	std::pair<int,int> counter;
	counter.first = 1;
	counter.second = 1;

	bool exists = polytope::adjOracle(adjPoint, initVertex, counter);

	Point<double> sinkMaximizerTarget;
	vector_t<double> sinkMaximizerVector = polytope::computeMaximizerVector(sinkMaximizerTarget, initVertex);

    std::cout<< "sinkMaximizerVector: " << sinkMaximizerVector << std::endl;
    std::cout<< "sinkMaximizerTarget: " << sinkMaximizerTarget << std::endl;
	std::cout << "-------------------------" << std::endl;

	polytope::Cone<double>* cone = polytope::computeCone(initVertex, sinkMaximizerVector);
	sumPoly.rFan().add(cone);

	std::cout << "Sink Cone added to Fan." << std::endl;

	Point<double> f = sumPoly.localSearch(adjPoint, sinkMaximizerTarget);
}*/

/*
TEST_F(MinkowskiSumTest, localSearchTest3D)
{
	std::cout << "PolyQ: ";
	polyQ.print();
	std::cout << "PolyP: ";
	polyP.print();

	Polytope<double> sumPoly = Parma_Polyhedra_Library::C_Polyhedron(0,EMPTY);

	Point<double> initVertex = polyQ.computeInitVertex(polyP);
	std::cout << "Point v*: " << initVertex << std::endl;
	std::cout << "-------------------------" << std::endl;

	sumPoly.addPoint(initVertex);

	Point<double> adjPoint;
	std::pair<int,int> counter;
	counter.first = 1;
	counter.second = 1;

	bool exists = polytope::adjOracle(adjPoint, initVertex, counter);

	Point<double> sinkMaximizerTarget;
	vector_t<double> sinkMaximizerVector = polytope::computeMaximizerVector(sinkMaximizerTarget, initVertex);

    std::cout<< "sinkMaximizerVector: " << sinkMaximizerVector << std::endl;
    std::cout<< "sinkMaximizerTarget: " << sinkMaximizerTarget << std::endl;
	std::cout << "-------------------------" << std::endl;

	polytope::Cone<double>* cone = polytope::computeCone(initVertex, sinkMaximizerVector);
	sumPoly.rFan().add(cone);

	std::cout << "Sink Cone added to Fan." << std::endl;

	Point<double> f = sumPoly.localSearch(adjPoint, sinkMaximizerTarget);

}*/

TEST_F(MinkowskiSumTest, altMinkowskiSumTest)
{
	glp_term_out(GLP_OFF);
	std::cout.setstate(std::ios::failbit);
	Polytope<double> omegaPoly;
	bool omega = polyAdj.altMinkowskiSum(omegaPoly,polyAdj2);
	std::cout.clear();
	std::cout << "Return Value: " << omega << std::endl;
	std::cout << "Computed Sum Polytope: ";
	omegaPoly.print();
}

TEST_F(MinkowskiSumTest, origMinkowskiSumTest)
{
	Polytope<double> omegaPoly;
	bool omega = polyAdj.minkowskiSum(omegaPoly,polyAdj2);
	std::cout << "Return Value: " << omega << std::endl;
	std::cout << "Computed Sum Polytope: ";
	omegaPoly.print();
}

TEST_F(MinkowskiSumTest, altMinkowskiSumTest3D)
{
	glp_term_out(GLP_OFF);
	std::cout.setstate(std::ios::failbit);
	Polytope<double> omegaPoly;
	bool omega = polyQ.altMinkowskiSum(omegaPoly,polyP);
	std::cout.clear();
	std::cout << "Return Value: " << omega << std::endl;
	std::cout << "Computed Sum Polytope: ";
	omegaPoly.print();
}

TEST_F(MinkowskiSumTest, origMinkowskiSumTest3D)
{
	Polytope<double> omegaPoly;
	bool omega = polyQ.minkowskiSum(omegaPoly,polyP);
	std::cout << "Return Value: " << omega << std::endl;
	std::cout << "Computed Sum Polytope: ";
	omegaPoly.print();
}



