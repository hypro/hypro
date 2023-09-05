/**
 * Performance test for the Minkowski Sum computation according to Komei Fukuda.
 * Author: ckugler
 */

#include "../../hypro/datastructures/Point.h"
#include "../../hypro/datastructures/hybridAutomata/util.h"
#include "../defines.h"
#include "gtest/gtest.h"
#include <chrono>

using namespace hypro;
using namespace carl;

class SumPerformanceTest : public ::testing::Test {
  protected:
	typedef std::chrono::high_resolution_clock clock;
	///
	typedef std::chrono::microseconds timeunit;
	virtual void SetUp() {
		/*
		 * Vertex Test, dimension always 3
		 */

		// double dimension = 2;
		double vertexAmount = 20;
		double radius = 100;
		double angle = 360 / vertexAmount;

		/**
		 * first Polytope
		 */
		std::vector<Point<double>*> pointSetP;
		Point<double> centerP1 = Point<double>( { 0, 0, radius } );
		Point<double> centerP2 = Point<double>( { 1, 0, radius } );

		// first Points individually
		Point<double>* point1 = new Point<double>( { 0, 0, 0 } );
		Point<double>* point2 = new Point<double>( { 1, 0, 0 } );

		point1->addNeighbor( point2 );
		point2->addNeighbor( point1 );

		pointSetP.push_back( point1 );
		pointSetP.push_back( point2 );

		// edge from center to (0,0) [need only one, since direction is the same, only center changes]
		vector_t<double> edgeP = polytope::computeEdge( centerP1, *point1 );

		// the rest iteratively
		double offsetP = angle;
		matrix_t<double> rotationMatP = matrix_t<double>( 3, 3 );
		// rotate around x-axis
		rotationMatP( 0, 0 ) = 1;
		rotationMatP( 0, 1 ) = 0;
		rotationMatP( 0, 2 ) = 0;
		rotationMatP( 1, 0 ) = 0;
		rotationMatP( 2, 0 ) = 0;

		for ( double i = 1; i < vertexAmount; ++i ) {
			// rotate the edge according to offset
			double degCos = cos( offsetP * PI_DN / 180 );
			double degSin = sin( offsetP * PI_DN / 180 );
			degCos = std::round( degCos * 1000000 ) / 1000000;
			degSin = std::round( degSin * 1000000 ) / 1000000;
			rotationMatP( 1, 1 ) = degCos;
			rotationMatP( 1, 2 ) = -degSin;
			rotationMatP( 2, 1 ) = degSin;
			rotationMatP( 2, 2 ) = degCos;

			vector_t<double> targetEdgeP = rotationMatP * edgeP;

			Point<double>* p1 = new Point<double>( polytope::computePoint( centerP1, targetEdgeP, false ) );
			Point<double>* p2 = new Point<double>( polytope::computePoint( centerP2, targetEdgeP, false ) );

			p1->addNeighbor( p2 );
			p2->addNeighbor( p1 );

			pointSetP.push_back( p1 );
			pointSetP.push_back( p2 );

			offsetP += angle;
		}

		for ( unsigned i = 0; i < pointSetP.size() - 2; ++i ) {
			pointSetP.at( i )->addNeighbor( pointSetP.at( i + 2 ) );
			pointSetP.at( i + 2 )->addNeighbor( pointSetP.at( i ) );
		}

		// the first & last point has to be treated seperately (for each sequence)
		pointSetP.at( 0 )->addNeighbor( pointSetP.at( pointSetP.size() - 2 ) );
		pointSetP.at( 1 )->addNeighbor( pointSetP.at( pointSetP.size() - 1 ) );
		pointSetP.at( pointSetP.size() - 2 )->addNeighbor( pointSetP.at( 0 ) );
		pointSetP.at( pointSetP.size() - 1 )->addNeighbor( pointSetP.at( 1 ) );

		// experimental: only allow integer values (for ease of debugging)
		for ( auto& point : pointSetP ) {
			std::vector<carl::Variable> variables = point->variables();
			for ( auto it = variables.begin(); it != variables.end(); ++it ) {
				point->setCoordinate( *it, std::round( point->at( *it ).toDouble() ) );
			}
		}

		for ( unsigned i = 0; i < pointSetP.size(); ++i ) {
			polyP.addPoint( *pointSetP.at( i ) );
		}

		// necessary since updatePoints() seems bugged
		polyP.setPointsUpToDate( true );

		/**
		 * second Polytope
		 */
		std::vector<Point<double>*> pointSetQ;
		Point<double> centerQ1 = Point<double>( { 1, 1, radius } );
		Point<double> centerQ2 = Point<double>( { 2, 1, radius } );

		// first Points individually
		Point<double>* qoint1 = new Point<double>( { 1, 1, 0 } );
		Point<double>* qoint2 = new Point<double>( { 2, 1, 0 } );

		qoint1->addNeighbor( qoint2 );
		qoint2->addNeighbor( qoint1 );

		pointSetQ.push_back( qoint1 );
		pointSetQ.push_back( qoint2 );

		// edge from center to (0,0) [need only one, since direction is the same, only center changes]
		vector_t<double> edgeQ = polytope::computeEdge( centerQ1, *qoint1 );

		// the rest iteratively
		double offsetQ = angle;
		matrix_t<double> rotationMatQ = matrix_t<double>( 3, 3 );
		// rotate around x-axis
		rotationMatQ( 0, 0 ) = 1;
		rotationMatQ( 0, 1 ) = 0;
		rotationMatQ( 0, 2 ) = 0;
		rotationMatQ( 1, 0 ) = 0;
		rotationMatQ( 2, 0 ) = 0;

		for ( double i = 1; i < vertexAmount; ++i ) {
			// rotate the edge according to offset
			double degCos = cos( offsetQ * PI_UP / 180 );
			double degSin = sin( offsetQ * PI_UP / 180 );
			degCos = std::round( degCos * 1000000 ) / 1000000;
			degSin = std::round( degSin * 1000000 ) / 1000000;
			rotationMatQ( 1, 1 ) = degCos;
			rotationMatQ( 1, 2 ) = -degSin;
			rotationMatQ( 2, 1 ) = degSin;
			rotationMatQ( 2, 2 ) = degCos;

			vector_t<double> targetEdgeQ = rotationMatQ * edgeQ;

			Point<double>* q1 = new Point<double>( polytope::computePoint( centerQ1, targetEdgeQ, false ) );
			Point<double>* q2 = new Point<double>( polytope::computePoint( centerQ2, targetEdgeQ, false ) );

			q1->addNeighbor( q2 );
			q2->addNeighbor( q1 );

			pointSetQ.push_back( q1 );
			pointSetQ.push_back( q2 );

			offsetQ += angle;
		}

		for ( unsigned i = 0; i < pointSetQ.size() - 2; ++i ) {
			pointSetQ.at( i )->addNeighbor( pointSetQ.at( i + 2 ) );
			pointSetQ.at( i + 2 )->addNeighbor( pointSetQ.at( i ) );
		}

		// the first & last point has to be treated seperately (for each sequence)
		pointSetQ.at( 0 )->addNeighbor( pointSetQ.at( pointSetQ.size() - 2 ) );
		pointSetQ.at( 1 )->addNeighbor( pointSetQ.at( pointSetQ.size() - 1 ) );
		pointSetQ.at( pointSetQ.size() - 2 )->addNeighbor( pointSetQ.at( 0 ) );
		pointSetQ.at( pointSetQ.size() - 1 )->addNeighbor( pointSetQ.at( 1 ) );

		// experimental
		for ( auto& point : pointSetQ ) {
			std::vector<carl::Variable> variables = point->variables();
			for ( auto it = variables.begin(); it != variables.end(); ++it ) {
				point->setCoordinate( *it, std::round( point->at( *it ).toDouble() ) );
			}
		}

		for ( unsigned i = 0; i < pointSetQ.size(); ++i ) {
			polyQ.addPoint( *pointSetQ.at( i ) );
		}

		// necessary since updatePoints() seems bugged
		polyQ.setPointsUpToDate( true );

		/*
		 * ----------------------------------------------
		 * ----------------------------------------------
		 * ----------------------------------------------
		 */

		/*
		 * Dimension test, variable amount of vertices (depending on dimension)
		 */
		constexpr long unsigned int dimension = 6;
		double vertices = std::pow( 2, dimension );
		std::vector<double> tuple( dimension, 0 );
		std::vector<Point<double>*> pointSetD;

		for ( double i = 0; i < vertices; ++i ) {
			std::bitset<dimension> bits( i );

			for ( unsigned j = 0; j < tuple.size(); ++j ) {
				tuple.at( tuple.size() - j - 1 ) = bits[j];
			}

			Point<double>* d1 = new Point<double>( tuple );

			pointSetD.push_back( d1 );
		}

		// set neighbors
		Point<double> referencePoint;
		for ( auto& point : pointSetD ) {
			for ( auto& var : point->variables() ) {
				referencePoint = Point<double>( *point );

				if ( referencePoint.at( var ) == 0 ) {
					referencePoint.setCoordinate( var, 1 );
				} else {
					referencePoint.setCoordinate( var, 0 );
				}

				for ( unsigned j = 0; j < pointSetD.size(); ++j ) {
					if ( *pointSetD.at( j ) == referencePoint ) {
						bool alreadyNeighbor = false;
						for ( auto& neighbor : point->neighbors() ) {
							if ( neighbor == *pointSetD.at( j ) ) {
								alreadyNeighbor = true;
							}
						}
						if ( !alreadyNeighbor ) {
							pointSetD.at( j )->addNeighbor( point );
							point->addNeighbor( pointSetD.at( j ) );
						}
						break;
					}
				}
			}
		}

		for ( unsigned i = 0; i < pointSetD.size(); ++i ) {
			polyD.addPoint( *pointSetD.at( i ) );
		}

		// necessary since updatePoints() seems bugged
		polyD.setPointsUpToDate( true );

		/*
		 * second Poly (for dimension Test)
		 */

		std::vector<double> tuple2( dimension, 0 );
		std::vector<Point<double>*> pointSetE;

		for ( double i = 0; i < vertices; ++i ) {
			std::bitset<dimension> bits( i );

			for ( unsigned j = 0; j < tuple2.size(); ++j ) {
				tuple2.at( tuple2.size() - j - 1 ) = bits[j];
			}

			Point<double>* e1 = new Point<double>( tuple2 );

			pointSetE.push_back( e1 );
		}

		// set neighbors
		Point<double> referencePoint2;
		for ( auto& point : pointSetE ) {
			for ( auto& var : point->variables() ) {
				referencePoint2 = Point<double>( *point );
				if ( referencePoint2.at( var ) == 0 ) {
					referencePoint2.setCoordinate( var, 1 );
				} else {
					referencePoint2.setCoordinate( var, 0 );
				}

				for ( unsigned j = 0; j < pointSetE.size(); ++j ) {
					if ( *pointSetE.at( j ) == referencePoint2 ) {
						bool alreadyNeighbor = false;
						for ( auto& neighbor : point->neighbors() ) {
							if ( neighbor == *pointSetE.at( j ) ) {
								alreadyNeighbor = true;
							}
						}
						if ( !alreadyNeighbor ) {
							pointSetE.at( j )->addNeighbor( point );
							point->addNeighbor( pointSetE.at( j ) );
						}
						break;
					}
				}
			}
		}

		for ( unsigned i = 0; i < pointSetE.size(); ++i ) {
			polyE.addPoint( *pointSetE.at( i ) );
		}

		// necessary since updatePoints() seems bugged
		polyE.setPointsUpToDate( true );

		// move the polytope somewhere else (to differentiate it from polyD)
		vector_t<double> translation = vector_t<double>( dimension, 1 );
		matrix_t<double> transformation = matrix_t<double>( dimension, dimension );

		for ( unsigned i = 0; i < translation.rows(); ++i ) {
			translation( i ) = 1;
			for ( unsigned j = 0; j < transformation.cols(); ++j ) {
				if ( i == j ) {
					transformation( i, j ) = 2;
				} else {
					transformation( i, j ) = 0;
				}
			}
		}

		// the following line moves the polytope (optional)
		// bool ret = polyE.linearTransformation(polyE, transformation, translation);
	}

	virtual void TearDown() {
		// TODO: tear down
	}

	hypro::Polytope<double> polyQ = Parma_Polyhedra_Library::C_Polyhedron( 0, EMPTY );
	hypro::Polytope<double> polyP = Parma_Polyhedra_Library::C_Polyhedron( 0, EMPTY );

	hypro::Polytope<double> polyD = Parma_Polyhedra_Library::C_Polyhedron( 0, EMPTY );
	hypro::Polytope<double> polyE = Parma_Polyhedra_Library::C_Polyhedron( 0, EMPTY );
};

// only used for debugging, not a real test
/*
TEST_F(SumPerformanceTest, playGroundTest)
{
	//std::cout << "Points P: " << polyP.points() << std::endl;


	for (unsigned i = 0; i < polyP.points().size(); ++i) {
		std::cout << "Neighbors P" << i+1 << ": " << polyP.points().at(i).neighbors() << std::endl;
	}

	//std::cout << "Points Q: " << polyQ.points() << std::endl;


	std::cout << "Points D: " << polyD.points() << std::endl;

	for (unsigned i = 0; i < polyD.points().size(); ++i) {
		std::cout << "Neighbors D" << i+1 << ": " << polyD.points().at(i).neighbors() << std::endl;
	}


	std::cout << "Points E: " << polyE.points() << std::endl;

	for (unsigned i = 0; i < polyE.points().size(); ++i) {
		std::cout << "Neighbors E" << i+1 << ": " << polyE.points().at(i).neighbors() << std::endl;
	}
}*/

/**
 * Vertex Test - Fukuda
 */
TEST_F( SumPerformanceTest, altMinkowskiSum_VertexTest ) {
	glp_term_out( GLP_OFF );
	std::cout.setstate( std::ios::failbit );
	Polytope<double> omegaPoly;

#ifdef fukuda_DEBUG
	clock::time_point start = clock::now();
#endif

	bool omega = polyP.altMinkowskiSum( omegaPoly, polyQ );
	ASSERT_TRUE( omega );

	std::cout.clear();

#ifdef fukuda_DEBUG
	std::cout << "Total time: " << std::chrono::duration_cast<timeunit>( clock::now() - start ).count() / 1000 << "ms"
			  << std::endl;

	std::cout << "-----------" << std::endl;
	std::cout << "Vertex Test " << std::endl;
	std::cout << "-----------" << std::endl;
	std::cout << "Return Value: " << omega << std::endl;
	std::cout << "Computed Sum Polytope: ";
	omegaPoly.print();
	std::cout << "Sum Size: " << omegaPoly.points().size() << std::endl;
#endif
}

/**
 * Vertex Test - brute force
 */
TEST_F( SumPerformanceTest, origMinkowskiSum_VertexTest ) {
	Polytope<double> omegaPoly;
#ifdef fukuda_DEBUG
	clock::time_point start2 = clock::now();
#endif

	bool omega = polyP.minkowskiSum( omegaPoly, polyQ );
	ASSERT_TRUE( omega );

#ifdef fukuda_DEBUG
	std::cout << "Total time: " << std::chrono::duration_cast<timeunit>( clock::now() - start2 ).count() / 1000 << "ms"
			  << std::endl;

	std::cout << "-----------" << std::endl;
	std::cout << "Vertex Test " << std::endl;
	std::cout << "-----------" << std::endl;
	std::cout << "Return Value: " << omega << std::endl;
	std::cout << "Computed Sum Polytope: ";
	omegaPoly.print();
	std::cout << "Sum Size: " << omegaPoly.points().size() << std::endl;
#endif
}

/**
 * Dimension Test - Fukuda
 */
TEST_F( SumPerformanceTest, altMinkowskiSum_DimensionTest ) {
	glp_term_out( GLP_OFF );
	// glp_term_out(GLP_ON);
	std::cout.setstate( std::ios::failbit );
	Polytope<double> omegaPoly;

#ifdef fukuda_DEBUG
	clock::time_point start3 = clock::now();
#endif

	bool omega = polyD.altMinkowskiSum( omegaPoly, polyD );
	ASSERT_TRUE( omega );

	std::cout.clear();

#ifdef fukuda_DEBUG
	std::cout << "Total time: " << std::chrono::duration_cast<timeunit>( clock::now() - start3 ).count() / 1000 << "ms"
			  << std::endl;

	std::cout << "-----------" << std::endl;
	std::cout << "Dimension Test " << std::endl;
	std::cout << "-----------" << std::endl;
	std::cout << "Return Value: " << omega << std::endl;
	std::cout << "Computed Sum Polytope: ";
	omegaPoly.print();
	std::cout << "Sum Size: " << omegaPoly.points().size() << std::endl;
#endif
}

/**
 * Dimension Test - brute force
 */
TEST_F( SumPerformanceTest, origMinkowskiSum_DimensionTest ) {
	Polytope<double> omegaPoly;

#ifdef fukuda_DEBUG
	clock::time_point start4 = clock::now();
#endif

	bool omega = polyD.minkowskiSum( omegaPoly, polyD );
	ASSERT_TRUE( omega );

#ifdef fukuda_DEBUG
	std::cout << "Total time: " << std::chrono::duration_cast<timeunit>( clock::now() - start4 ).count() / 1000 << "ms"
			  << std::endl;

	std::cout << "-----------" << std::endl;
	std::cout << "Dimension Test " << std::endl;
	std::cout << "-----------" << std::endl;
	std::cout << "Return Value: " << omega << std::endl;
	std::cout << "Computed Sum Polytope: ";
	omegaPoly.print();
	std::cout << "Sum Size: " << omegaPoly.points().size() << std::endl;
#endif
}
