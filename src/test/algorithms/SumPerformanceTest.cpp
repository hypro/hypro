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
    	/*
    	 * Vertex Test, dimension always 3
    	 */

    	//double dimension = 2;
    	double vertexAmount = 10;
    	double radius = 100;
    	double angle = 360/vertexAmount;

    	/**
    	 * first Polytope
    	 */
    	std::vector<Point<double>*> pointSetP;
    	Point<double> centerP1 = Point<double>({0,0,radius});
    	Point<double> centerP2 = Point<double>({1,0,radius});

    	//first Points individually
		Point<double>* point1 = new Point<double>({0,0,0});
		Point<double>* point2 = new Point<double>({1,0,0});

		point1->addNeighbor(point2);
		point2->addNeighbor(point1);

		pointSetP.push_back(point1);
		pointSetP.push_back(point2);

		//edge from center to (0,0) [need only one, since direction is the same, only center changes]
		vector_t<double> edgeP = polytope::computeEdge(centerP1, *point1);
		//vector_t<double> edgeP2 = polytope::computeEdge(centerP2, p2);

		//the rest iteratively
		double offsetP = angle;
		matrix_t<double> rotationMatP = matrix_t<double>(3,3);
		//rotate around x-axis
		rotationMatP(0,0) = 1;
		rotationMatP(0,1) = 0;
		rotationMatP(0,2) = 0;
		rotationMatP(1,0) = 0;
		rotationMatP(2,0) = 0;

    	for (double i = 1; i < vertexAmount; ++i) {
    		//rotate the edge according to offset
    		double degCos = cos(offsetP*PI_DN/180);
    		double degSin = sin(offsetP*PI_DN/180);
    		degCos = std::round(degCos*1000000)/1000000;
    		degSin = std::round(degSin*1000000)/1000000;
    		rotationMatP(1,1) = degCos;
    		rotationMatP(1,2) = -degSin;
    		rotationMatP(2,1) = degSin;
    		rotationMatP(2,2) = degCos;

    		vector_t<double> targetEdgeP = rotationMatP * edgeP;

    		Point<double>* p1 = new Point<double>(polytope::computePoint(centerP1, targetEdgeP, false));
    		Point<double>* p2 = new Point<double>(polytope::computePoint(centerP2, targetEdgeP, false));

    		p1->addNeighbor(p2);
    		p2->addNeighbor(p1);

    		pointSetP.push_back(p1);
    		pointSetP.push_back(p2);

    		offsetP += angle;
    	}

    	for(unsigned i = 0; i < pointSetP.size()-2; ++i) {
    		pointSetP.at(i)->addNeighbor(pointSetP.at(i+2));
    		pointSetP.at(i+2)->addNeighbor(pointSetP.at(i));
    	}

    	//the first & last point has to be treated seperately (for each sequence)
    	pointSetP.at(0)->addNeighbor(pointSetP.at(pointSetP.size()-2));
    	pointSetP.at(1)->addNeighbor(pointSetP.at(pointSetP.size()-1));
    	pointSetP.at(pointSetP.size()-2)->addNeighbor(pointSetP.at(0));
    	pointSetP.at(pointSetP.size()-1)->addNeighbor(pointSetP.at(1));

    	//experimental
    	for (auto& point : pointSetP) {
    		std::vector<carl::Variable> variables = point->variables();
    		for (auto it=variables.begin(); it != variables.end(); ++it) {
    			point->setCoordinate(*it, std::round(point->at(*it).toDouble()));
    		}
    	}

    	for (unsigned i = 0; i < pointSetP.size(); ++i) {
    		polyP.addPoint(*pointSetP.at(i));
    	}

    	//necessary since updatePoints() seems bugged
    	polyP.setPointsUpToDate(true);

    	/**
    	 * second Polytope
    	 */
    	std::vector<Point<double>*> pointSetQ;
    	Point<double> centerQ1 = Point<double>({1,1,radius});
    	Point<double> centerQ2 = Point<double>({2,1,radius});

    	//first Points individually
		Point<double>* qoint1 = new Point<double>({1,1,0});
		Point<double>* qoint2 = new Point<double>({2,1,0});

		qoint1->addNeighbor(qoint2);
		qoint2->addNeighbor(qoint1);

		pointSetQ.push_back(qoint1);
		pointSetQ.push_back(qoint2);

		//edge from center to (0,0) [need only one, since direction is the same, only center changes]
		vector_t<double> edgeQ = polytope::computeEdge(centerQ1, *qoint1);
		//vector_t<double> edgeP2 = polytope::computeEdge(centerP2, p2);

		//the rest iteratively
		double offsetQ = angle;
		matrix_t<double> rotationMatQ = matrix_t<double>(3,3);
		//rotate around x-axis
		rotationMatQ(0,0) = 1;
		rotationMatQ(0,1) = 0;
		rotationMatQ(0,2) = 0;
		rotationMatQ(1,0) = 0;
		rotationMatQ(2,0) = 0;

    	for (double i = 1; i < vertexAmount; ++i) {
    		//rotate the edge according to offset
    		double degCos = cos(offsetQ*PI_UP/180);
    		double degSin = sin(offsetQ*PI_UP/180);
    		degCos = std::round(degCos*1000000)/1000000;
    		degSin = std::round(degSin*1000000)/1000000;
    		rotationMatQ(1,1) = degCos;
    		rotationMatQ(1,2) = -degSin;
    		rotationMatQ(2,1) = degSin;
    		rotationMatQ(2,2) = degCos;

    		vector_t<double> targetEdgeQ = rotationMatQ * edgeQ;

    		Point<double>* q1 = new Point<double>(polytope::computePoint(centerQ1, targetEdgeQ, false));
    		Point<double>* q2 = new Point<double>(polytope::computePoint(centerQ2, targetEdgeQ, false));

    		q1->addNeighbor(q2);
    		q2->addNeighbor(q1);

    		pointSetQ.push_back(q1);
    		pointSetQ.push_back(q2);

    		offsetQ += angle;
    	}

    	for(unsigned i = 0; i < pointSetQ.size()-2; ++i) {
    		pointSetQ.at(i)->addNeighbor(pointSetQ.at(i+2));
    		pointSetQ.at(i+2)->addNeighbor(pointSetQ.at(i));
    	}

    	//the first & last point has to be treated seperately (for each sequence)
    	pointSetQ.at(0)->addNeighbor(pointSetQ.at(pointSetQ.size()-2));
    	pointSetQ.at(1)->addNeighbor(pointSetQ.at(pointSetQ.size()-1));
    	pointSetQ.at(pointSetQ.size()-2)->addNeighbor(pointSetQ.at(0));
    	pointSetQ.at(pointSetQ.size()-1)->addNeighbor(pointSetQ.at(1));

    	//experimental
    	for (auto& point : pointSetQ) {
    		std::vector<carl::Variable> variables = point->variables();
    		for (auto it=variables.begin(); it != variables.end(); ++it) {
    			point->setCoordinate(*it, std::round(point->at(*it).toDouble()));
    		}
    	}

    	for (unsigned i = 0; i < pointSetQ.size(); ++i) {
    		polyQ.addPoint(*pointSetQ.at(i));
    	}

    	//necessary since updatePoints() seems bugged
    	polyQ.setPointsUpToDate(true);


    /*
     * ----------------------------------------------
     * ----------------------------------------------
     * ----------------------------------------------
     */

    /*
     * Dimension test, variable amount of vertices (depending on dimension)
     */
    constexpr long unsigned int dimension = 4;
    double vertices = std::pow(2,dimension);
    std::vector<double> tuple(dimension,0);
    std::vector<Point<double>*> pointSetD;

    for (double i = 0; i < vertices; ++i) {
        std::bitset<dimension> bits(i);
        //std::cout << "Bits: " << bits.to_string() << std::endl;

        for (unsigned j=0; j < tuple.size(); ++j) {
        	tuple.at(tuple.size()-j-1) = bits[j];
        }

        std::cout << "List: " << tuple << std::endl;
    	Point<double>* d1 = new Point<double>(tuple);
        std::cout << "Point: " << *d1 << std::endl;

        pointSetD.push_back(d1);
    }

    std::cout << "Testing the point constructor (with Initializer List {0,0,0,1}): " << std::endl;
	Point<double>* d = new Point<double>({0,0,0,1});
    std::cout << "Point d: " << *d << std::endl;

    }

    virtual void TearDown()
    {
    	//TODO: tear down

    }

    hypro::Polytope<double> polyQ = Parma_Polyhedra_Library::C_Polyhedron(0,EMPTY);
    hypro::Polytope<double> polyP = Parma_Polyhedra_Library::C_Polyhedron(0,EMPTY);

    hypro::Polytope<double> polyD = Parma_Polyhedra_Library::C_Polyhedron(0,EMPTY);
};

TEST_F(SumPerformanceTest, playGroundTest)
{
	//std::cout << "Points P: " << polyP.points() << std::endl;

	/*
	for (unsigned i = 0; i < polyP.points().size(); ++i) {
		std::cout << "Neighbors P" << i+1 << ": " << polyP.points().at(i).neighbors() << std::endl;
	}*/
/*
	std::cout << "Points Q: " << polyQ.points() << std::endl;

*/
}

/*
TEST_F(SumPerformanceTest, altMinkowskiSumVTest)
{
	glp_term_out(GLP_OFF);
	//glp_term_out(GLP_ON);
	std::cout.setstate(std::ios::failbit);
	Polytope<double> omegaPoly;
	bool omega = polyP.altMinkowskiSum(omegaPoly,polyQ);
	std::cout.clear();
	std::cout << "-----------" << std::endl;
	std::cout << "Vertex Test " << std::endl;
	std::cout << "-----------" << std::endl;
	std::cout << "Return Value: " << omega << std::endl;
	std::cout << "Computed Sum Polytope: ";
	omegaPoly.print();
	std::cout << "Sum Size: " << omegaPoly.points().size() << std::endl;
}


TEST_F(SumPerformanceTest, origMinkowskiSumVTest)
{
	Polytope<double> omegaPoly;
	bool omega = polyP.minkowskiSum(omegaPoly,polyQ);
	std::cout << "-----------" << std::endl;
	std::cout << "Vertex Test " << std::endl;
	std::cout << "-----------" << std::endl;
	std::cout << "Return Value: " << omega << std::endl;
	std::cout << "Computed Sum Polytope: ";
	omegaPoly.print();
	std::cout << "Sum Size: " << omegaPoly.points().size() << std::endl;
}*/



