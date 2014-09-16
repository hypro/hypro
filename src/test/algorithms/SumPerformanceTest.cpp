#include "gtest/gtest.h"
#include "../defines.h"
#include "../../lib/datastructures/hybridAutomata/util.h"
#include <carl/core/VariablePool.h>
#include "../../lib/datastructures/Point.h"


using namespace hypro;
using namespace carl;

class SumPerformanceTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
    	double dimension = 2;
    	double vertexAmount = 2;

    	/**
    	 * first Polytope
    	 */
    	for (double i = 1; i <= vertexAmount; ++i) {
    		Point<double>* p1 = new Point<double>({0,i-1,0});
    		Point<double>* p2 = new Point<double>({1,i-1,0});

    		p1->addNeighbor(p2);
    		p2->addNeighbor(p1);

    		polyP.addPoint(*p1);
    		polyP.addPoint(*p2);
    	}

    	//necessary since updatePoints() seems bugged
    	polyP.setPointsUpToDate(true);

    	for (unsigned i=0; i < polyP.points().size()-2; ++i) {
    		std::vector<Point<double>> points = polyP.points();
    		Point<double>* post = new Point<double>(points.at(i+2));
    		Point<double>* pre = new Point<double>(points.at(i));
    		points.at(i).addNeighbor(post);
    		post->addNeighbor(pre);
    	}

    	/**
    	 * second Polytope
    	 */
    	for (double i = 1; i <= vertexAmount; ++i) {
    		Point<double>* q1 = new Point<double>({1,1+i-1,0});
    		Point<double>* q2 = new Point<double>({2,1+i-1,0});

    		q1->addNeighbor(q2);
    		q2->addNeighbor(q1);

    		polyQ.addPoint(*q1);
    		polyQ.addPoint(*q2);
    	}

    	//necessary since updatePoints() seems bugged
    	polyQ.setPointsUpToDate(true);

    	for (unsigned i=0; i < polyQ.points().size()-1; ++i) {
    		std::vector<Point<double>> points = polyQ.points();
    		Point<double>* post = new Point<double>(points.at(i+1));
    		Point<double>* pre = new Point<double>(points.at(i));
    		pre->addNeighbor(post);
    		post->addNeighbor(pre);
    	}

    }

    virtual void TearDown()
    {
    	//TODO: tear down

    }

    hypro::Polytope<double> polyQ = Parma_Polyhedra_Library::C_Polyhedron(0,EMPTY);
    hypro::Polytope<double> polyP = Parma_Polyhedra_Library::C_Polyhedron(0,EMPTY);
};

TEST_F(SumPerformanceTest, playGroundTest)
{
	std::cout << "Points P: " << polyP.points() << std::endl;
	std::cout << "Neighbors P: " << polyP.points().at(0).neighbors() << std::endl;
	std::cout << "Points Q: " << polyQ.points() << std::endl;
	std::cout << "Neighbors Q: " << polyQ.points().at(0).neighbors() << std::endl;
}

/*
TEST_F(SumPerformanceTest, altMinkowskiSumTest)
{
	glp_term_out(GLP_OFF);
	std::cout.setstate(std::ios::failbit);
	Polytope<double> omegaPoly;
	bool omega = polyQ.altMinkowskiSum(omegaPoly,polyP);
	std::cout.clear();
	std::cout << "Return Value: " << omega << std::endl;
	std::cout << "Computed Sum Polytope: ";
	omegaPoly.print();
}*/

/*
TEST_F(SumPerformanceTest, origMinkowskiSumTest)
{
	Polytope<double> omegaPoly;
	bool omega = polyQ.minkowskiSum(omegaPoly,polyP);
	std::cout << "Return Value: " << omega << std::endl;
	std::cout << "Computed Sum Polytope: ";
	omegaPoly.print();
}*/



