#include "gtest/gtest.h"
#include "../defines.h"
#include "../../lib/datastructures/hybridAutomata/util.h"
#include "carl/core/VariablePool.h"
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
	     * third Polytope, where each Point has an adjacency list
	     */
	    //create adjacency list for each Point
    	/*
	    std::set<Point<double>>::iterator it=poly.points().begin();
	    Point<double> p1 = *it;
	    std::cout << "Point it: " << (*it) << std::endl;
	    it++;
	    Point<double> p2 = *it;
	    it++;
	    Point<double> p3 = *it;
	    it++;
	    Point<double> p4 = *it;

	    p1.addNeighbor(&p3);
	    p1.addNeighbor(&p4);

	    p2.addNeighbor(&p3);
	    p2.addNeighbor(&p4);

	    p3.addNeighbor(&p1);
	    p3.addNeighbor(&p2);

	    p4.addNeighbor(&p1);
	    p4.addNeighbor(&p2);

	    polyAdj.addPoint(p1);
	    polyAdj.addPoint(p2);
	    polyAdj.addPoint(p3);
	    polyAdj.addPoint(p4);
	    */

	    //

    	Point<double>::coordinateMap coordinate;
    	coordinate.insert( std::make_pair(x, 1) );
    	coordinate.insert( std::make_pair(y, 1) );
    	t1 = Point<double>(coordinate);

    	Point<double>::coordinateMap coordinate2;
    	coordinate2.insert( std::make_pair(x, 0) );
    	coordinate2.insert( std::make_pair(y, 0) );
    	t2 = Point<double>(coordinate2);

    	Point<double>::coordinateMap coordinate3;
    	coordinate3.insert( std::make_pair(x, 0) );
    	coordinate3.insert( std::make_pair(y, 1) );
    	t3 = Point<double>(coordinate3);

    	Point<double>::coordinateMap coordinate4;
    	coordinate4.insert( std::make_pair(x, 1) );
    	coordinate4.insert( std::make_pair(y, 0) );
    	t4 = Point<double>(coordinate4);

	    t1.addNeighbor(t3);
	    t1.addNeighbor(t4);

	    t2.addNeighbor(t3);
	    t2.addNeighbor(t4);

	    t3.addNeighbor(t1);
	    t3.addNeighbor(t2);

	    t4.addNeighbor(t1);
	    t4.addNeighbor(t2);

	    std::cout << "Neighbors of P4: " << t4.neighbors() << std::endl;

    	polyAdj.addPoint(t1);
    	polyAdj.addPoint(t2);
    	polyAdj.addPoint(t3);
    	polyAdj.addPoint(t4);
    }

    virtual void TearDown()
    {
    	//TODO: tear down

    }
    carl::VariablePool& pool = carl::VariablePool::getInstance();
    carl::Variable x = pool.getFreshVariable("x");
    carl::Variable y = pool.getFreshVariable("y");

    Point<double> t1;
    Point<double> t2;
    Point<double> t3;
    Point<double> t4;

    hypro::Polytope<double> poly;
    hypro::Polytope<double> poly2;
    hypro::Polytope<double> polyAdj = Parma_Polyhedra_Library::C_Polyhedron(0,EMPTY);

	vector_t<double> coordinates = vector_t<double>(2,1);
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

	Polytope<double> result;
	bool temp = poly.minkowskiSum(result,poly2);
	std::cout << "--------" << std::endl;
	std::cout << "as comparison - original MinkowskiSum result: ";
	result.print();
}

TEST_F(MinkowskiSumTest, computeMaxVDegreeTest)
{
   	std::cout << "Minkowski Sum - Adjacency Polytope: ";
    polyAdj.print();

    std::vector<Point<double>> tmp = polyAdj.points();

    //std::cout << "Point Set: " << tmp << std::endl;

    //TODO doesn't work, why?

    std::vector<Point<double>>::iterator it=tmp.begin();
    std::cout << "Point iterator (first Element): " << (*it) << std::endl;

	int result = polyAdj.computeMaxVDegree();
	std::cout << "Max Vertex Degree: " << result << std::endl;
}
