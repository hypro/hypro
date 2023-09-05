/**
 * Testfile for the computation of the Minkowski Sum according to Komei Fukuda.
 * Author: ckugler
 */

#include "../../hypro/datastructures/Point.h"
#include "../../hypro/datastructures/hybridAutomata/util.h"
#include "../defines.h"
#include "gtest/gtest.h"

using namespace hypro;
using namespace carl;

class MinkowskiSumTest : public ::testing::Test {
  protected:
	virtual void SetUp() {
		/**
		 * first Polytope
		 */
		coordinates( 0 ) = 1;
		coordinates( 1 ) = 1;

		std::vector<vector_t<double>> vecSet;
		vecSet.push_back( coordinates );

		coordinates( 0 ) = 0;
		coordinates( 1 ) = 0;
		vecSet.push_back( coordinates );

		coordinates( 0 ) = 0;
		coordinates( 1 ) = 1;
		vecSet.push_back( coordinates );

		coordinates( 0 ) = 1;
		coordinates( 1 ) = 0;
		vecSet.push_back( coordinates );

		poly = Polytope<double>( vecSet );

		/**
		 * second Polytope
		 */
		coordinates( 0 ) = 4;
		coordinates( 1 ) = 4;

		std::vector<vector_t<double>> vecSet2;
		vecSet2.push_back( coordinates );

		coordinates( 0 ) = 3;
		coordinates( 1 ) = 3;
		vecSet2.push_back( coordinates );

		coordinates( 0 ) = 3;
		coordinates( 1 ) = 4;
		vecSet2.push_back( coordinates );

		coordinates( 0 ) = 4;
		coordinates( 1 ) = 3;
		vecSet2.push_back( coordinates );

		poly2 = Polytope<double>( vecSet2 );

		/**
		 * one Polytope with Adjacency set up
		 */

		t1 = new Point<double>( { 1, 1 } );

		t2 = new Point<double>( { 0, 0 } );

		t3 = new Point<double>( { 0, 1 } );

		t4 = new Point<double>( { 1, 0 } );

		t1->addNeighbor( t3 );
		t1->addNeighbor( t4 );

		t2->addNeighbor( t3 );
		t2->addNeighbor( t4 );

		t3->addNeighbor( t1 );
		t3->addNeighbor( t2 );

		t4->addNeighbor( t1 );
		t4->addNeighbor( t2 );

		polyAdj.addPoint( *t1 );
		polyAdj.addPoint( *t2 );
		polyAdj.addPoint( *t3 );
		polyAdj.addPoint( *t4 );

		/**
		 * another Polytope with Adjacency set up
		 */
		t5 = new Point<double>( { 2, 2 } );

		t6 = new Point<double>( { 1, 1 } );

		t7 = new Point<double>( { 1, 2 } );

		t8 = new Point<double>( { 2, 1 } );

		t5->addNeighbor( t7 );
		t5->addNeighbor( t8 );

		t6->addNeighbor( t7 );
		t6->addNeighbor( t8 );

		t7->addNeighbor( t5 );
		t7->addNeighbor( t6 );

		t8->addNeighbor( t5 );
		t8->addNeighbor( t6 );

		polyAdj2.addPoint( *t5 );
		polyAdj2.addPoint( *t6 );
		polyAdj2.addPoint( *t7 );
		polyAdj2.addPoint( *t8 );

		/**
		 * the 3D Test Setup
		 */
		q1 = new Point<double>( { 0, 0, 0 } );
		q2 = new Point<double>( { 1, 0, 0 } );
		q3 = new Point<double>( { 1, 1, 0 } );
		q4 = new Point<double>( { 0, 1, 0 } );
		q5 = new Point<double>( { 0, 0, 1 } );
		q6 = new Point<double>( { 1, 0, 1 } );
		q7 = new Point<double>( { 1, 1, 1 } );
		q8 = new Point<double>( { 0, 1, 1 } );

		q1->addNeighbor( q2 );
		q1->addNeighbor( q4 );
		q1->addNeighbor( q5 );

		q2->addNeighbor( q3 );
		q2->addNeighbor( q1 );
		q2->addNeighbor( q6 );

		q3->addNeighbor( q2 );
		q3->addNeighbor( q4 );
		q3->addNeighbor( q7 );

		q4->addNeighbor( q3 );
		q4->addNeighbor( q1 );
		q4->addNeighbor( q8 );

		q5->addNeighbor( q6 );
		q5->addNeighbor( q8 );
		q5->addNeighbor( q1 );

		q6->addNeighbor( q7 );
		q6->addNeighbor( q5 );
		q6->addNeighbor( q2 );

		q7->addNeighbor( q6 );
		q7->addNeighbor( q8 );
		q7->addNeighbor( q3 );

		q8->addNeighbor( q7 );
		q8->addNeighbor( q5 );
		q8->addNeighbor( q4 );

		polyQ.addPoint( *q1 );
		polyQ.addPoint( *q2 );
		polyQ.addPoint( *q3 );
		polyQ.addPoint( *q4 );
		polyQ.addPoint( *q5 );
		polyQ.addPoint( *q6 );
		polyQ.addPoint( *q7 );
		polyQ.addPoint( *q8 );

		// seccond Poly
		p1 = new Point<double>( { 1, 1, 0 } );
		p2 = new Point<double>( { 2, 1, 0 } );
		p3 = new Point<double>( { 2, 2, 0 } );
		p4 = new Point<double>( { 1, 2, 0 } );
		p5 = new Point<double>( { 1, 1, 1 } );
		p6 = new Point<double>( { 2, 1, 1 } );
		p7 = new Point<double>( { 2, 2, 1 } );
		p8 = new Point<double>( { 1, 2, 1 } );

		p1->addNeighbor( p2 );
		p1->addNeighbor( p4 );
		p1->addNeighbor( p5 );

		p2->addNeighbor( p3 );
		p2->addNeighbor( p1 );
		p2->addNeighbor( p6 );

		p3->addNeighbor( p2 );
		p3->addNeighbor( p4 );
		p3->addNeighbor( p7 );

		p4->addNeighbor( p3 );
		p4->addNeighbor( p1 );
		p4->addNeighbor( p8 );

		p5->addNeighbor( p6 );
		p5->addNeighbor( p8 );
		p5->addNeighbor( p1 );

		p6->addNeighbor( p7 );
		p6->addNeighbor( p5 );
		p6->addNeighbor( p2 );

		p7->addNeighbor( p6 );
		p7->addNeighbor( p8 );
		p7->addNeighbor( p3 );

		p8->addNeighbor( p7 );
		p8->addNeighbor( p5 );
		p8->addNeighbor( p4 );

		polyP.addPoint( *p1 );
		polyP.addPoint( *p2 );
		polyP.addPoint( *p3 );
		polyP.addPoint( *p4 );
		polyP.addPoint( *p5 );
		polyP.addPoint( *p6 );
		polyP.addPoint( *p7 );
		polyP.addPoint( *p8 );

		// disables GLPK output
		glp_term_out( GLP_OFF );
	}

	virtual void TearDown() {}

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
	hypro::Polytope<double> polyAdj = Parma_Polyhedra_Library::C_Polyhedron( 0, EMPTY );
	hypro::Polytope<double> polyAdj2 = Parma_Polyhedra_Library::C_Polyhedron( 0, EMPTY );

	vector_t<double> coordinates = vector_t<double>( 2, 1 );

	// for 3D
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

	hypro::Polytope<double> polyQ = Parma_Polyhedra_Library::C_Polyhedron( 0, EMPTY );
	hypro::Polytope<double> polyP = Parma_Polyhedra_Library::C_Polyhedron( 0, EMPTY );
};

/**
 * computeMaxPoint() Test
 */
TEST_F( MinkowskiSumTest, computeMaxPointTest ) {
#ifdef fukuda_DEBUG
	std::cout << "Minkowski Sum - Polytope 1: ";
	poly.print();
	std::cout << "Minkowski Sum - Polytope 2: ";
	poly2.print();

	std::cout << "Size Poly1: " << poly.points().size() << std::endl;
#endif

	Point<double> res = poly.computeMaxPoint();
#ifdef fukuda_DEBUG
	std::cout << "Point 1: " << res << std::endl;
#endif

	Point<double> res2 = poly2.computeMaxPoint();
#ifdef fukuda_DEBUG
	std::cout << "Point 2: " << res2 << std::endl;
#endif
}

/**
 * computeInitVertex() Test
 */
TEST_F( MinkowskiSumTest, computeInitVertexTest ) {
#ifdef fukuda_DEBUG
	std::cout << "Minkowski Sum - Polytope 1: ";
	poly.print();
	std::cout << "Minkowski Sum - Polytope 2: ";
	poly2.print();
#endif

	Point<double> res = poly.computeInitVertex( poly2 );
#ifdef fukuda_DEBUG
	std::cout << "Point v*: " << res << std::endl;

	std::cout << "v* composed of: " << res.composedOf() << std::endl;
#endif

	Polytope<double> result;
	bool temp = poly.minkowskiSum( result, poly2 );
	ASSERT_TRUE( temp );
#ifdef fukuda_DEBUG
	std::cout << "--------" << std::endl;
	std::cout << "as comparison - original MinkowskiSum result: ";
	result.print();
#endif
}

/**
 * computeMaxVDegree() Test
 */
TEST_F( MinkowskiSumTest, computeMaxVDegreeTest ) {
#ifdef fukuda_DEBUG
	std::cout << "Minkowski Sum - Adjacency Polytope: ";
	polyAdj.print();
#endif

	std::vector<Point<double>> tmp = polyAdj.points();

	std::vector<Point<double>>::iterator it = tmp.begin();
#ifdef fukuda_DEBUG
	std::cout << "Point iterator (first Element): " << ( *it ) << std::endl;
#endif

	int result = polyAdj.computeMaxVDegree();
	// just to prevent warning
	result = result;
#ifdef fukuda_DEBUG
	std::cout << "Max Vertex Degree: " << result << std::endl;
#endif
}

/**
 * computePoint() Test
 */
TEST_F( MinkowskiSumTest, computePointTest ) {
	vector_t<double> edge = vector_t<double>( 2, 1 );
	edge( 0 ) = 3;
	edge( 1 ) = 4;

	Point<double> result = polytope::computePoint( *t1, edge, false );
#ifdef fukuda_DEBUG
	std::cout << "source Point: " << *t1 << std::endl;
	std::cout << "Edge: " << std::endl;
	std::cout << edge << std::endl;
	std::cout << "computed Point: " << result << std::endl;
#endif
}

/**
 * computeEdge() Test
 */
TEST_F( MinkowskiSumTest, computeEdgeTest ) {
	Point<double> p;
	p = Point<double>( { 4, 3 } );

	vector_t<double> result = polytope::computeEdge( *t1, p );
#ifdef fukuda_DEBUG
	std::cout << "source Point: " << *t1 << std::endl;
	std::cout << "target Point: " << p << std::endl;
	std::cout << "computed Edge: " << std::endl;
	std::cout << result << std::endl;
#endif
}

/**
 * adjOracle() Test
 */
TEST_F( MinkowskiSumTest, adjOracleTest ) {
	Point<double> res = polyAdj.computeInitVertex( polyAdj2 );
#ifdef fukuda_DEBUG
	std::cout << "Point v*: " << res << std::endl;
#endif

	Point<double> adjPoint;
	std::pair<int, int> counter;
	counter.first = 1;
	counter.second = 1;

	bool exists = polytope::adjOracle( adjPoint, res, counter );
	ASSERT_TRUE( exists );
#ifdef fukuda_DEBUG
	std::cout << "AdjOracle return value: " << exists << std::endl;
	std::cout << "Computed Point: " << adjPoint << std::endl;
#endif
}

/**
 * computeMaximizerVector() Test
 */
TEST_F( MinkowskiSumTest, computeMaximizerVectorTest ) {
	Point<double> v = polyAdj.computeInitVertex( polyAdj2 );
#ifdef fukuda_DEBUG
	std::cout << "Point v*: " << v << std::endl;
#endif

	Point<double> target;
	vector_t<double> result = polytope::computeMaximizerVector( target, v );
#ifdef fukuda_DEBUG
	std::cout << "Vector: " << std::endl;
	std::cout << result << std::endl;
	std::cout << "Target Vertex: " << target << std::endl;
#endif
}

/**
 * computeNormalConeVector() Test
 */
TEST_F( MinkowskiSumTest, computeNormalConeVectorTest ) {
	Point<double> p;
	p = Point<double>( { 0, 1 } );

	vector_t<double> result = polytope::computeEdge( *t1, p );
#ifdef fukuda_DEBUG
	std::cout << "source Point: " << t1 << std::endl;
	std::cout << "target Point: " << p << std::endl;
	std::cout << "Edge: " << std::endl;
	std::cout << result << std::endl;
#endif

	std::vector<vector_t<double>> edgeSet;
	edgeSet.push_back( result );

	// for the maximizer vector we need v=v1+v2
	Point<double> v = polyAdj.computeInitVertex( polyAdj2 );
	Point<double> target;
	vector_t<double> maximizer = polytope::computeMaximizerVector( target, v );
#ifdef fukuda_DEBUG
	std::cout << "Maximizer Vector: " << std::endl;
	std::cout << maximizer << std::endl;
#endif

	vector_t<double> resultingEdge = polytope::computeNormalConeVector<double>( edgeSet, maximizer );
#ifdef fukuda_DEBUG
	std::cout << "Computed Edge (Scalar Product <= 0): " << std::endl;
	std::cout << resultingEdge << std::endl;
#endif
}

/**
 * localSearch() Test for the 2D example
 */

TEST_F( MinkowskiSumTest, localSearchTest ) {
	Polytope<double> sumPoly = Parma_Polyhedra_Library::C_Polyhedron( 0, EMPTY );

	Point<double> initVertex = polyAdj.computeInitVertex( polyAdj2 );
#ifdef fukuda_DEBUG
	std::cout << "Point v*: " << initVertex << std::endl;
	std::cout << "-------------------------" << std::endl;
#endif

	sumPoly.addPoint( initVertex );

	Point<double> adjPoint;
	std::pair<int, int> counter;
	counter.first = 1;
	counter.second = 1;

	bool exists = polytope::adjOracle( adjPoint, initVertex, counter );
	ASSERT_TRUE( exists );

	Point<double> sinkMaximizerTarget;
	vector_t<double> sinkMaximizerVector = polytope::computeMaximizerVector( sinkMaximizerTarget, initVertex );

#ifdef fukuda_DEBUG
	std::cout << "sinkMaximizerVector: " << sinkMaximizerVector << std::endl;
	std::cout << "sinkMaximizerTarget: " << sinkMaximizerTarget << std::endl;
	std::cout << "-------------------------" << std::endl;
#endif

	polytope::Cone<double>* cone = polytope::computeCone( initVertex, sinkMaximizerVector );
	sumPoly.rFan().add( cone );

#ifdef fukuda_DEBUG
	std::cout << "Sink Cone added to Fan." << std::endl;
#endif

	Point<double> f = sumPoly.localSearch( adjPoint, sinkMaximizerTarget );
}

/**
 * localSearch() Test for the 3D example
 */

TEST_F( MinkowskiSumTest, localSearchTest3D ) {
#ifdef fukuda_DEBUG
	std::cout << "PolyQ: ";
	polyQ.print();
	std::cout << "PolyP: ";
	polyP.print();
#endif

	Polytope<double> sumPoly = Parma_Polyhedra_Library::C_Polyhedron( 0, EMPTY );

	Point<double> initVertex = polyQ.computeInitVertex( polyP );
#ifdef fukuda_DEBUG
	std::cout << "Point v*: " << initVertex << std::endl;
	std::cout << "-------------------------" << std::endl;
#endif

	sumPoly.addPoint( initVertex );

	Point<double> adjPoint;
	std::pair<int, int> counter;
	counter.first = 1;
	counter.second = 1;

	bool exists = polytope::adjOracle( adjPoint, initVertex, counter );
	ASSERT_TRUE( exists );

	Point<double> sinkMaximizerTarget;
	vector_t<double> sinkMaximizerVector = polytope::computeMaximizerVector( sinkMaximizerTarget, initVertex );

#ifdef fukuda_DEBUG
	std::cout << "sinkMaximizerVector: " << sinkMaximizerVector << std::endl;
	std::cout << "sinkMaximizerTarget: " << sinkMaximizerTarget << std::endl;
	std::cout << "-------------------------" << std::endl;
#endif

	polytope::Cone<double>* cone = polytope::computeCone( initVertex, sinkMaximizerVector );
	sumPoly.rFan().add( cone );

#ifdef fukuda_DEBUG
	std::cout << "Sink Cone added to Fan." << std::endl;
#endif

	Point<double> f = sumPoly.localSearch( adjPoint, sinkMaximizerTarget );
}

/**
 * Test of the whole Minkowski Sum computation according to Fukuda
 */
TEST_F( MinkowskiSumTest, altMinkowskiSumTest ) {
	glp_term_out( GLP_OFF );
#ifndef fukuda_DEBUG
	std::cout.setstate( std::ios::failbit );
#endif
	Polytope<double> omegaPoly;
	bool omega = polyAdj.altMinkowskiSum( omegaPoly, polyAdj2 );
	ASSERT_TRUE( omega );
	std::cout.clear();
#ifdef fukuda_DEBUG
	std::cout << "Return Value: " << omega << std::endl;
	std::cout << "Computed Sum Polytope: ";
	omegaPoly.print();
#endif
	// std::cout << "Neighbors of P1: " << omegaPoly.points().at(0).neighbors() << std::endl;
}

/**
 * Test of the brute force computation for the Minkowski Sum
 */
TEST_F( MinkowskiSumTest, origMinkowskiSumTest ) {
	Polytope<double> omegaPoly;
	bool omega = polyAdj.minkowskiSum( omegaPoly, polyAdj2 );
	ASSERT_TRUE( omega );
#ifdef fukuda_DEBUG
	std::cout << "Return Value: " << omega << std::endl;
	std::cout << "Computed Sum Polytope: ";
	omegaPoly.print();
#endif
}

/**
 * Test of the whole Minkowski Sum computation according to Fukuda (3D case)
 */

TEST_F( MinkowskiSumTest, altMinkowskiSumTest3D ) {
	glp_term_out( GLP_OFF );
#ifndef fukuda_DEBUG
	std::cout.setstate( std::ios::failbit );
#endif
	Polytope<double> omegaPoly;
	bool omega = polyQ.altMinkowskiSum( omegaPoly, polyP );
	ASSERT_TRUE( omega );
	std::cout.clear();
#ifdef fukuda_DEBUG
	std::cout << "Return Value: " << omega << std::endl;
	std::cout << "Computed Sum Polytope: ";
	omegaPoly.print();
#endif
}

/**
 * Test of the brute force computation for the Minkowski Sum (3D case)
 */

TEST_F( MinkowskiSumTest, origMinkowskiSumTest3D ) {
	Polytope<double> omegaPoly;
	bool omega = polyQ.minkowskiSum( omegaPoly, polyP );
	ASSERT_TRUE( omega );
#ifdef fukuda_DEBUG
	std::cout << "Return Value: " << omega << std::endl;
	std::cout << "Computed Sum Polytope: ";
	omegaPoly.print();
#endif
}
