/**
 * Specific benchmark implementation for the reachability computation based on polytopes.
 * Author: ckugler
 */

#include "../../hypro/algorithms/reachability/forwardReachability.h"
#include "../../hypro/datastructures/Point.h"
#include "../../hypro/datastructures/hybridAutomata/HybridAutomaton.h"
#include "../../hypro/datastructures/hybridAutomata/Location.h"
#include "../../hypro/datastructures/hybridAutomata/Transition.h"
#include "../defines.h"
#include "gtest/gtest.h"
#include <carl/core/VariablePool.h>

using namespace hypro;
using namespace carl;

class ReachabilityPerformanceTest : public ::testing::Test {
	/**
	 * Benchmark:
	 * computing the flowpipe for one location
	 */
  protected:
	virtual void SetUp() {
		/*
		 * Location
		 */
		invariantVec( 0 ) = 10;
		invariantVec( 1 ) = 10;

		invariantOp = LEQ;

		invariantMat( 0, 0 ) = 1;
		invariantMat( 0, 1 ) = 0;
		invariantMat( 1, 0 ) = 0;
		invariantMat( 1, 1 ) = 1;

		loc1->setInvariant( invariantMat, invariantVec, invariantOp );

		locationMat( 0, 0 ) = -1;
		locationMat( 0, 1 ) = -4;
		locationMat( 1, 0 ) = 4;
		locationMat( 1, 1 ) = -1;

		loc1->setActivityMat( locationMat );

		// Polytope for InitialValuation & Guard Assignment

		// create Box
		initVec( 0 ) = 1.1;
		initVec( 1 ) = 0.9;
		initVec( 2 ) = 0.1;
		initVec( 3 ) = -0.1;

		initMat( 0, 0 ) = 1;
		initMat( 0, 1 ) = 0;
		initMat( 1, 0 ) = -1;
		initMat( 1, 1 ) = 0;
		initMat( 2, 0 ) = 0;
		initMat( 2, 1 ) = 1;
		initMat( 3, 0 ) = 0;
		initMat( 3, 1 ) = -1;

		Point<double>* p1 = new Point<double>{ 0.9, -0.1 };
		Point<double>* p2 = new Point<double>{ 0.9, 0.1 };
		Point<double>* p3 = new Point<double>{ 1.1, -0.1 };
		Point<double>* p4 = new Point<double>{ 1.1, 0.1 };

		p1->addNeighbor( p2 );
		p1->addNeighbor( p3 );

		p2->addNeighbor( p1 );
		p2->addNeighbor( p4 );

		p3->addNeighbor( p1 );
		p3->addNeighbor( p4 );

		p4->addNeighbor( p2 );
		p4->addNeighbor( p3 );

		initVal.addPoint( *p1 );
		initVal.addPoint( *p2 );
		initVal.addPoint( *p3 );
		initVal.addPoint( *p4 );

#ifdef fReach_DEBUG
		std::cout << "-------" << std::endl;
		std::cout << "X0 Polytope: " << std::endl;
		initVal.print();
		initVal.setPointsUpToDate( true );
		// for (auto& point : initVal.points()) {
		//	std::cout << "Neighbors: " << point.neighbors() << std::endl;
		// }
		std::cout << "-------" << std::endl;
#endif
	}

	virtual void TearDown() {}

	Location<double>* loc1 = new Location<double>();

	vector_t<double> invariantVec = vector_t<double>( 2, 1 );
	operator_e invariantOp;
	matrix_t<double> invariantMat = matrix_t<double>( 2, 2 );
	matrix_t<double> locationMat = matrix_t<double>( 2, 2 );

	hypro::Polytope<double> initVal = Parma_Polyhedra_Library::C_Polyhedron( 0, EMPTY );

	vector_t<double> initVec = vector_t<double>( 4, 1 );
	matrix_t<double> initMat = matrix_t<double>( 4, 2 );
	std::vector<hypro::valuation_t<double>> flowpipe;
};

/**
 * auxiliary function for the visualization of the results
 * computes a center for given vertices of a polytope
 */
std::vector<double> computeCenter( std::vector<std::vector<double>> input ) {
	std::vector<double> result;
	result.push_back( 0 );
	result.push_back( 0 );
	for ( unsigned i = 0; i < input.size(); ++i ) {
		result.at( 0 ) += input.at( i ).at( 0 );
		result.at( 1 ) += input.at( i ).at( 1 );
	}
	result.at( 0 ) = result.at( 0 ) / input.size();
	result.at( 1 ) = result.at( 1 ) / input.size();
	return result;
}

/**
 * auxiliary function for the visualization of the results
 * sorts a set of vertices anti-clockwise (based on a given center)
 */
std::vector<std::vector<double>> sortSet( std::vector<std::vector<double>> input, std::vector<double> center ) {
	std::vector<std::vector<double>> result;

	std::map<double, std::vector<double>> map;
	for ( unsigned i = 0; i < input.size(); ++i ) {
		double angle = std::atan2( input.at( i ).at( 1 ) - center.at( 1 ), input.at( i ).at( 0 ) - center.at( 0 ) );
		map.insert( std::pair<double, std::vector<double>>( angle, input.at( i ) ) );
	}

	for ( auto& element : map ) {
		result.push_back( element.second );
	}

	return result;
}

/**
 * in this test:
 * a) a flowpipe based on the benchmark setup is computed
 * b) the vertices of the polytopes (i.e. of each flowpipe segment) are sorted anti-clockwise
 * c) the data is written to a file in GnuPlot format
 */
TEST_F( ReachabilityPerformanceTest, ComputeFlowpipeTest ) {
	// configuration of console output
	glp_term_out( GLP_OFF );
	// std::cout.setstate(std::ios::failbit);

	// compute the flowpipe
	flowpipe = forwardReachability::computeForwardTimeClosure( *loc1, initVal );
	// std::cout.clear();
	// std::cout.setstate(std::ios::failbit);

	// sort points anti-clockwise
	std::vector<std::vector<std::vector<double>>> newPipe;

#ifdef fReach_DEBUG
	std::cout << "-------" << std::endl;
	std::cout << "From here on: Order Set" << std::endl;
	std::cout << "-------" << std::endl;
#endif

	for ( auto& segment : flowpipe ) {
		segment.setPointsUpToDate( false );
		std::vector<std::vector<double>> newSegment;
		for ( auto& point : segment.points() ) {
			std::vector<double> coords;
			for ( auto& var : point.variables() ) {
				coords.push_back( point.coordinate( var ).toDouble() );
			}
			newSegment.push_back( coords );
		}
#ifdef fReach_DEBUG
		std::cout << "Unordered Set: " << std::endl;
		std::cout << newSegment << std::endl;
		std::cout << "-------" << std::endl;
#endif

		std::vector<double> center = computeCenter( newSegment );
#ifdef fReach_DEBUG
		std::cout << "Center: " << center << std::endl;
#endif

		newSegment = sortSet( newSegment, center );
#ifdef fReach_DEBUG
		std::cout << "Ordered Set: " << std::endl;
		std::cout << newSegment << std::endl;
		std::cout << "-------" << std::endl;
#endif

		newPipe.push_back( newSegment );
	}

	// create file based on sorted points
	FILE* fp;
	fp = fopen( "pipe.plt", "w" );

	fprintf( fp, "set terminal postscript\n" );

	char filename[10 + 10];
	sprintf( filename, "pipe.eps" );
	fprintf( fp, "set output '%s'\n", filename );

	fprintf( fp, "set style line 1 linecolor rgb \"blue\"\n" );
	fprintf( fp, "set autoscale\n" );
	fprintf( fp, "unset label\n" );
	fprintf( fp, "set xtic auto\n" );
	fprintf( fp, "set ytic auto\n" );
	fprintf( fp, "set xlabel \"%s\"\n", "x" );
	fprintf( fp, "set ylabel \"%s\"\n", "y" );
	fprintf( fp, "plot '-' notitle with lines ls 1\n" );

	for ( auto& segment : newPipe ) {
		bool first = true;
		std::vector<double> c;
		for ( auto& point : segment ) {
			// a copy of the first point has to be placed at the very end (for GnuPlot to draw correctly)
			if ( first ) {
				c = point;
				first = false;
			}
			fprintf( fp, "%lf %lf\n", point.at( 0 ), point.at( 1 ) );
		}
		fprintf( fp, "%lf %lf\n", c.at( 0 ), c.at( 1 ) );
		fprintf( fp, "\n\n" );
	}
	fclose( fp );

	std::cout.clear();

#ifdef fReach_DEBUG
	int size = flowpipe.size();
	std::cout << "Flowpipe size: ";
	std::cout << size << std::endl;
#endif
}
