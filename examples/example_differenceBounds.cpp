/**
 * \example example_differenceBounds.cpp This example shows how to use a
 * representation by difference Bounds.
 */

#include <hypro/datastructures/Halfspace.h>
#include <hypro/datastructures/Point.h>
#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/util/plotting/Plotter.h>

typedef double Number;
hypro::DifferenceBounds<Number> testDBM;
hypro::DifferenceBounds<Number> testDBM2;
hypro::DifferenceBounds<Number> testDBM3;
hypro::DifferenceBounds<Number> testDBMExtra;
hypro::HPolytope<Number> testHPolytope;
void createTestDBM();
void createTestDBM2();
void createTestDBM3();
void createTestDBMExtra();
void createTestHPolytope();
void testComparison();
void testPlus();
void testVertices();
void testElapse();
void testRewind();
void testFree();
void testReset();
void testCopy();
void testShift();
void testEmpty();
void testContains();
void testIntersectConstraint();
void testContainsPoint();
void testIntersectDBM();
void testUnion();
void testConversionDifferenceBoundsToDifferenceBounds();
void testConversionHPolyToDBM();
void testConversionBoxToDBM();
void testSatisfiesHalfspace();
void testSatisfiesHalfspaces();
void testIntersectHalfspace();
void testIntersectHalfspaces();
void testLinearTransformation();
void testAffineTransformation();
void testMinkowskiSum();
void testExtraM();
void testExtraMPlus();
void testExtraLU();
void testExtraLUPlus();
void testPrint();

int main() {
	createTestDBM();
	createTestDBM2();
	createTestDBM3();
	createTestDBMExtra();
	createTestHPolytope();
	testComparison();
	testPlus();
	testVertices();
	testElapse();
	testRewind();
	testFree();
	testReset();
	testCopy();
	testShift();
	testEmpty();
	testContains();
	testIntersectConstraint();
	testContainsPoint();
	testIntersectDBM();
	testUnion();
	testConversionDifferenceBoundsToDifferenceBounds();
	testConversionHPolyToDBM();
	testConversionBoxToDBM();
	testSatisfiesHalfspace();
	testSatisfiesHalfspaces();
	testIntersectHalfspace();
	testIntersectHalfspaces();
	testLinearTransformation();
	testAffineTransformation();
	testMinkowskiSum();
	testExtraM();
	testExtraMPlus();
	testExtraLU();
	testExtraLUPlus();
	// testPrint();
	return 0;
}

void createTestDBM() {
	hypro::matrix_t<hypro::DifferenceBounds<Number>::DBMEntry> mat =
		  hypro::matrix_t<hypro::DifferenceBounds<Number>::DBMEntry>( 3, 3 );
	mat << hypro::DifferenceBounds<Number>::DBMEntry(
		  0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ ),
		  hypro::DifferenceBounds<Number>::DBMEntry(
				-4.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ ),
		  hypro::DifferenceBounds<Number>::DBMEntry(
				-4.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ ),
		  hypro::DifferenceBounds<Number>::DBMEntry(
				9.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ ),
		  hypro::DifferenceBounds<Number>::DBMEntry(
				0.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ ),
		  hypro::DifferenceBounds<Number>::DBMEntry(
				0.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ ),
		  hypro::DifferenceBounds<Number>::DBMEntry(
				11.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ ),
		  hypro::DifferenceBounds<Number>::DBMEntry(
				2.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ ),
		  hypro::DifferenceBounds<Number>::DBMEntry(
				0.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ );
	testDBM = hypro::DifferenceBounds<Number>();
	testDBM.setDBM( mat );
	testDBM.setTimeHorizon( 20.0 );
}

void createTestDBM2() {
	hypro::matrix_t<hypro::DifferenceBounds<Number>::DBMEntry> mat =
		  hypro::matrix_t<hypro::DifferenceBounds<Number>::DBMEntry>( 3, 3 );
	mat << hypro::DifferenceBounds<Number>::DBMEntry(
		  0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ ),
		  hypro::DifferenceBounds<Number>::DBMEntry(
				-4.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ ),
		  hypro::DifferenceBounds<Number>::DBMEntry(
				-4.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ ),
		  hypro::DifferenceBounds<Number>::DBMEntry(
				9.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ ),
		  hypro::DifferenceBounds<Number>::DBMEntry(
				0.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ ),
		  hypro::DifferenceBounds<Number>::DBMEntry(
				0.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ ),
		  hypro::DifferenceBounds<Number>::DBMEntry(
				10.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ ),
		  hypro::DifferenceBounds<Number>::DBMEntry(
				1.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ ),
		  hypro::DifferenceBounds<Number>::DBMEntry(
				0.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ );
	testDBM2 = hypro::DifferenceBounds<Number>();
	testDBM2.setDBM( mat );
	testDBM2.setTimeHorizon( 20.0 );
}

void createTestDBM3() {
	// shift dbm 0.5 to the right and 1 down
	testDBM3 = testDBM.shift( 1, 1 );
	testDBM3 = testDBM3.shift( 2, -1.0 );
}

void createTestDBMExtra() {
	hypro::matrix_t<hypro::DifferenceBounds<Number>::DBMEntry> mat =
		  hypro::matrix_t<hypro::DifferenceBounds<Number>::DBMEntry>( 3, 3 );
	mat << hypro::DifferenceBounds<Number>::DBMEntry(
		  0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ ),
		  hypro::DifferenceBounds<Number>::DBMEntry(
				-4.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ ),
		  hypro::DifferenceBounds<Number>::DBMEntry(
				-4.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ ),
		  hypro::DifferenceBounds<Number>::DBMEntry(
				9.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ ),
		  hypro::DifferenceBounds<Number>::DBMEntry(
				0.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ ),
		  hypro::DifferenceBounds<Number>::DBMEntry(
				0.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ ),
		  hypro::DifferenceBounds<Number>::DBMEntry(
				11.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ ),
		  hypro::DifferenceBounds<Number>::DBMEntry(
				2.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ ),
		  hypro::DifferenceBounds<Number>::DBMEntry(
				0.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ );
	testDBMExtra = hypro::DifferenceBounds<Number>();
	testDBMExtra.setDBM( mat );
	testDBMExtra.setTimeHorizon( 20.0 );
}

void createTestHPolytope() {
	std::vector<hypro::Point<Number>> vec;
	std::vector<Number> coord1;
	coord1.push_back( 1 );
	coord1.push_back( 4 );

	std::vector<Number> coord2;
	coord2.push_back( 5 );
	coord2.push_back( 4 );

	std::vector<Number> coord3;
	coord3.push_back( 3 );
	coord3.push_back( 5 );

	std::vector<Number> coord4;
	coord4.push_back( 3 );
	coord4.push_back( 3 );

	vec.push_back( hypro::Point<Number>( coord1 ) );
	vec.push_back( hypro::Point<Number>( coord2 ) );
	vec.push_back( hypro::Point<Number>( coord3 ) );
	vec.push_back( hypro::Point<Number>( coord4 ) );

	testHPolytope = hypro::HPolytope<Number>( vec );
}

void testComparison() {
	hypro::DifferenceBounds<Number>::DBMEntry infty =
		  hypro::DifferenceBounds<Number>::DBMEntry(
				0, hypro::DifferenceBounds<Number>::BOUND_TYPE::INFTY );

	hypro::DifferenceBounds<Number>::DBMEntry smaller1 =
		  hypro::DifferenceBounds<Number>::DBMEntry(
				1.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER );
	hypro::DifferenceBounds<Number>::DBMEntry smaller2 =
		  hypro::DifferenceBounds<Number>::DBMEntry(
				2.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER );

	hypro::DifferenceBounds<Number>::DBMEntry smallerEq1 =
		  hypro::DifferenceBounds<Number>::DBMEntry(
				1.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ );
	hypro::DifferenceBounds<Number>::DBMEntry smallerEq2 =
		  hypro::DifferenceBounds<Number>::DBMEntry(
				2.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ );

	std::cout << infty << " < " << infty << " :" << ( infty < infty ) << "\n";
	std::cout << smaller1 << " < " << infty << " :" << ( smaller1 < infty ) << "\n";
	std::cout << infty << " < " << smaller1 << " :" << ( infty < smaller1 ) << "\n";
	std::cout << smallerEq1 << " < " << infty << " :" << ( smallerEq1 < infty )
			  << "\n";
	std::cout << infty << " < " << smallerEq1 << " :" << ( infty < smallerEq1 )
			  << "\n";

	std::cout << smaller1 << " < " << smaller2 << " :" << ( smaller1 < smaller2 )
			  << "\n";
	std::cout << smaller2 << " < " << smaller1 << " :" << ( smaller2 < smaller1 )
			  << "\n";

	std::cout << smaller1 << " < " << smallerEq1 << " :"
			  << ( smaller1 < smallerEq1 ) << "\n";
	std::cout << smallerEq1 << " < " << smaller1 << " :"
			  << ( smallerEq1 < smaller1 ) << "\n";
	std::cout << smaller1 << " < " << smallerEq2 << " :"
			  << ( smaller1 < smallerEq2 ) << "\n";
	std::cout << smallerEq2 << " < " << smaller1 << " :"
			  << ( smallerEq2 < smaller1 ) << "\n";

	std::cout << smallerEq2 << " < " << smallerEq1 << " :"
			  << ( smallerEq2 < smallerEq1 ) << "\n";
	std::cout << smallerEq1 << " < " << smallerEq2 << " :"
			  << ( smallerEq1 < smallerEq2 ) << "\n";
}

void testPlus() {
	hypro::DifferenceBounds<Number>::DBMEntry infty =
		  hypro::DifferenceBounds<Number>::DBMEntry(
				0, hypro::DifferenceBounds<Number>::BOUND_TYPE::INFTY );

	hypro::DifferenceBounds<Number>::DBMEntry smaller1 =
		  hypro::DifferenceBounds<Number>::DBMEntry(
				1.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER );
	hypro::DifferenceBounds<Number>::DBMEntry smaller2 =
		  hypro::DifferenceBounds<Number>::DBMEntry(
				2.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER );

	hypro::DifferenceBounds<Number>::DBMEntry smallerEq1 =
		  hypro::DifferenceBounds<Number>::DBMEntry(
				1.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ );
	hypro::DifferenceBounds<Number>::DBMEntry smallerEq2 =
		  hypro::DifferenceBounds<Number>::DBMEntry(
				2.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ );

	std::cout << infty << " + " << infty << " :" << ( infty + infty ) << "\n";
	std::cout << smaller1 << " + " << infty << " :" << ( smaller1 + infty ) << "\n";
	std::cout << infty << " + " << smaller1 << " :" << ( infty + smaller1 ) << "\n";
	std::cout << smallerEq1 << " + " << infty << " :" << ( smallerEq1 + infty )
			  << "\n";
	std::cout << infty << " + " << smallerEq1 << " :" << ( infty + smallerEq1 )
			  << "\n";

	std::cout << smaller1 << " + " << smaller2 << " :" << ( smaller1 + smaller2 )
			  << "\n";
	std::cout << smaller2 << " + " << smaller1 << " :" << ( smaller2 + smaller1 )
			  << "\n";

	std::cout << smaller1 << " + " << smallerEq1 << " :"
			  << ( smaller1 + smallerEq1 ) << "\n";
	std::cout << smallerEq1 << " + " << smaller1 << " :"
			  << ( smallerEq1 + smaller1 ) << "\n";
	std::cout << smaller1 << " + " << smallerEq2 << " :"
			  << ( smaller1 + smallerEq2 ) << "\n";
	std::cout << smallerEq2 << " + " << smaller1 << " :"
			  << ( smallerEq2 + smaller1 ) << "\n";

	std::cout << smallerEq2 << " + " << smallerEq1 << " :"
			  << ( smallerEq2 + smallerEq1 ) << "\n";
	std::cout << smallerEq1 << " + " << smallerEq2 << " :"
			  << ( smallerEq1 + smallerEq2 ) << "\n";
}

void testVertices() {
	// compute vertices
	std::cout << "Test instance vertices for DBM1: \n";
	std::vector<hypro::Point<Number>> verts1 = testDBM.vertices();
	std::cout << verts1;

	std::cout << "Test instance vertices for DBM2: \n";
	std::vector<hypro::Point<Number>> verts2 = testDBM2.vertices();
	std::cout << verts2;

	// plot to pdf
	hypro::Plotter<Number>::getInstance().clear();
	unsigned obj2 = hypro::Plotter<Number>::getInstance().addObject( verts1 );
	unsigned obj3 = hypro::Plotter<Number>::getInstance().addObject( verts2 );
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj2, hypro::plotting::colors[hypro::plotting::green] );
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj3, hypro::plotting::colors[hypro::plotting::red] );

	// create a *.plt file (gnuplot).
	hypro::Plotter<Number>::getInstance().setFilename( "verticesTest" );
	hypro::Plotter<Number>::getInstance().plot2d();
}

void testElapse() {
	std::cout << "Test elapse: \n";

	hypro::DifferenceBounds<Number> elapsed = testDBM.elapse();
	std::cout << elapsed;
	std::vector<hypro::Point<Number>> verts = elapsed.vertices();
	std::cout << verts;

	// plot to pdf
	hypro::Plotter<Number>::getInstance().clear();
	unsigned obj2 = hypro::Plotter<Number>::getInstance().addObject( verts );
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj2, hypro::plotting::colors[hypro::plotting::green] );

	// create a *.plt file (gnuplot).
	hypro::Plotter<Number>::getInstance().setFilename( "elapseTest" );
	hypro::Plotter<Number>::getInstance().plot2d();
}

void testRewind() {
	std::cout << "Test rewind: \n";

	hypro::DifferenceBounds<Number> rewind = testDBM.rewind();
	std::cout << rewind;
	std::vector<hypro::Point<Number>> verts = rewind.vertices();
	std::cout << verts;

	// plot to pdf
	hypro::Plotter<Number>::getInstance().clear();
	unsigned obj2 = hypro::Plotter<Number>::getInstance().addObject( verts );
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj2, hypro::plotting::colors[hypro::plotting::green] );

	// create a *.plt file (gnuplot).
	hypro::Plotter<Number>::getInstance().setFilename( "rewindTest" );
	hypro::Plotter<Number>::getInstance().plot2d();
}

void testFree() {
	std::cout << "Test free: \n";

	hypro::DifferenceBounds<Number> freed = testDBM.free( 2 );	// free y
	std::cout << freed;
	std::vector<hypro::Point<Number>> verts = freed.vertices();
	std::cout << verts;

	// plot to pdf
	hypro::Plotter<Number>::getInstance().clear();
	unsigned obj2 = hypro::Plotter<Number>::getInstance().addObject( verts );
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj2, hypro::plotting::colors[hypro::plotting::green] );

	// create a *.plt file (gnuplot).
	hypro::Plotter<Number>::getInstance().setFilename( "freeTest" );
	hypro::Plotter<Number>::getInstance().plot2d();
}

void testReset() {
	std::cout << "Test reset: \n";

	hypro::DifferenceBounds<Number> reset = testDBM.reset( 1, 0.0 );  // reset x
	std::cout << reset;
	std::vector<hypro::Point<Number>> verts = reset.vertices();
	std::cout << verts;

	// plot to pdf
	hypro::Plotter<Number>::getInstance().clear();
	unsigned obj2 = hypro::Plotter<Number>::getInstance().addObject( verts );
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj2, hypro::plotting::colors[hypro::plotting::green] );

	// create a *.plt file (gnuplot).
	hypro::Plotter<Number>::getInstance().setFilename( "resetTest" );
	hypro::Plotter<Number>::getInstance().plot2d();
}

void testCopy() {
	std::cout << "Test copy: \n";

	hypro::DifferenceBounds<Number> copy = testDBM.copy( 1, 2 );  // copy x to y
	std::cout << copy;
	std::vector<hypro::Point<Number>> verts = copy.vertices();
	std::cout << verts;

	// plot to pdf
	hypro::Plotter<Number>::getInstance().clear();
	unsigned obj2 = hypro::Plotter<Number>::getInstance().addObject( verts );
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj2, hypro::plotting::colors[hypro::plotting::green] );

	// create a *.plt file (gnuplot).
	hypro::Plotter<Number>::getInstance().setFilename( "copyTest" );
	hypro::Plotter<Number>::getInstance().plot2d();
}

void testShift() {
	std::cout << "Test shift: \n";

	hypro::DifferenceBounds<Number> shift =
		  testDBM.shift( 1, 5.0 );	// shift x 5 to the right
	std::cout << shift;
	std::vector<hypro::Point<Number>> verts = shift.vertices();
	std::cout << verts;

	// plot to pdf
	hypro::Plotter<Number>::getInstance().clear();
	unsigned obj2 = hypro::Plotter<Number>::getInstance().addObject( verts );
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj2, hypro::plotting::colors[hypro::plotting::green] );

	// create a *.plt file (gnuplot).
	hypro::Plotter<Number>::getInstance().setFilename( "shiftTest" );
	hypro::Plotter<Number>::getInstance().plot2d();
}

void testEmpty() {
	bool isEmpty = testDBM.empty();
	std::cout << "DBM is empty: " << isEmpty << "\n";
}

void testContains() {
	bool contains = testDBM.contains( testDBM2 );
	std::cout << "DBM1 contains DBM2: " << contains << "\n";
}

void testIntersectConstraint() {
	std::cout << "Test intersection with constraint: \n";

	// intersect with x-0 <= 8.0
	hypro::DifferenceBounds<Number> intersection = testDBM.intersectConstraint(
		  1, 0,
		  hypro::DifferenceBounds<Number>::DBMEntry(
				8.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ ) );
	std::cout << intersection;
	std::vector<hypro::Point<Number>> verts = intersection.vertices();
	std::cout << verts;

	// plot to pdf
	hypro::Plotter<Number>::getInstance().clear();
	unsigned obj2 = hypro::Plotter<Number>::getInstance().addObject( verts );
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj2, hypro::plotting::colors[hypro::plotting::green] );

	// create a *.plt file (gnuplot).
	hypro::Plotter<Number>::getInstance().setFilename( "intersectionTest" );
	hypro::Plotter<Number>::getInstance().plot2d();
}

void testContainsPoint() {
	hypro::vector_t<Number> coordinates( 2 );
	coordinates << 10, 11.1;
	hypro::Point<Number> point = hypro::Point<Number>( coordinates );
	bool contains = testDBM.contains( point );
	std::cout << "DBM1 contains Point" << point << " : " << contains << "\n";
}

void testIntersectDBM() {
	std::cout << "Test intersection with dbm: \n";

	hypro::DifferenceBounds<Number> intersection = testDBM.intersect( testDBM3 );
	std::cout << intersection;
	std::vector<hypro::Point<Number>> intersectVerts = intersection.vertices();
	std::cout << intersectVerts;

	// plot to pdf
	hypro::Plotter<Number>::getInstance().clear();

	unsigned obj3 =
		  hypro::Plotter<Number>::getInstance().addObject( testDBM.vertices() );
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj3, hypro::plotting::colors[hypro::plotting::blue] );

	unsigned obj4 =
		  hypro::Plotter<Number>::getInstance().addObject( testDBM3.vertices() );
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj4, hypro::plotting::colors[hypro::plotting::green] );

	unsigned obj2 =
		  hypro::Plotter<Number>::getInstance().addObject( intersectVerts );
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj2, hypro::plotting::colors[hypro::plotting::red] );

	// create a *.plt file (gnuplot).
	hypro::Plotter<Number>::getInstance().setFilename( "intersectionDBMTest" );
	hypro::Plotter<Number>::getInstance().plot2d();
}

void testUnion() {
	std::cout << "Test union with dbm: \n";

	hypro::DifferenceBounds<Number> unioned = testDBM.unite( testDBM3 );
	std::cout << unioned;
	std::vector<hypro::Point<Number>> unionVerts = unioned.vertices();
	std::cout << unionVerts;

	// plot to pdf
	hypro::Plotter<Number>::getInstance().clear();

	unsigned obj3 =
		  hypro::Plotter<Number>::getInstance().addObject( testDBM.vertices() );
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj3, hypro::plotting::colors[hypro::plotting::blue] );

	unsigned obj4 =
		  hypro::Plotter<Number>::getInstance().addObject( testDBM3.vertices() );
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj4, hypro::plotting::colors[hypro::plotting::green] );

	unsigned obj2 = hypro::Plotter<Number>::getInstance().addObject( unionVerts );
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj2, hypro::plotting::colors[hypro::plotting::red] );

	// create a *.plt file (gnuplot).
	hypro::Plotter<Number>::getInstance().setFilename( "unionDBMTest" );
	hypro::Plotter<Number>::getInstance().plot2d();
}

void testConversionDifferenceBoundsToDifferenceBounds() {
	std::cout << "Test conversion from DBM to DBM: \n";
	hypro::DifferenceBounds<Number> conversion =
		  hypro::Converter<Number>::toDifferenceBounds( testDBM );
	std::cout << conversion;
	std::vector<hypro::Point<Number>> conversionVerts = conversion.vertices();
	std::cout << conversionVerts;

	// plot to pdf
	hypro::Plotter<Number>::getInstance().clear();

	unsigned obj2 =
		  hypro::Plotter<Number>::getInstance().addObject( conversionVerts );
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj2, hypro::plotting::colors[hypro::plotting::red] );

	// create a *.plt file (gnuplot).
	hypro::Plotter<Number>::getInstance().setFilename( "conversionDBMDBMTest" );
	hypro::Plotter<Number>::getInstance().plot2d();
}

void testConversionHPolyToDBM() {
	std::cout << "Test conversion from HPoly to DBM: \n";

	// plot to pdf
	hypro::Plotter<Number>::getInstance().clear();
	hypro::DifferenceBounds<Number> conversion =
		  hypro::Converter<Number>::toDifferenceBounds( testHPolytope );
	std::cout << conversion;
	unsigned obj2 =
		  hypro::Plotter<Number>::getInstance().addObject( testHPolytope.vertices() );
	std::cout << "HPolytope vertices:" << testHPolytope.vertices() << "\n";
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj2, hypro::plotting::colors[hypro::plotting::red] );

	unsigned obj3 =
		  hypro::Plotter<Number>::getInstance().addObject( conversion.vertices() );
	std::cout << "Conversion vertices:" << conversion.vertices() << "\n";
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj3, hypro::plotting::colors[hypro::plotting::green] );

	// create a *.plt file (gnuplot).
	hypro::Plotter<Number>::getInstance().setFilename( "conversionHPolyToDBMTest" );
	hypro::Plotter<Number>::getInstance().plot2d();
}

void testConversionBoxToDBM() {
	std::cout << "Test conversion from Box to DBM: \n";
	std::vector<carl::Interval<Number>> boundaries;
	boundaries.push_back( carl::Interval<Number>( 2, 4 ) );
	boundaries.push_back( carl::Interval<Number>( 2, 4 ) );

	hypro::Box<Number> box = hypro::Box<Number>( boundaries );

	// plot to pdf
	hypro::Plotter<Number>::getInstance().clear();
	unsigned obj3 =
		  hypro::Plotter<Number>::getInstance().addObject( box.vertices() );
	std::cout << "Box vertices:" << box.vertices() << "\n";
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj3, hypro::plotting::colors[hypro::plotting::red] );

	hypro::DifferenceBounds<Number> conversion =
		  hypro::Converter<Number>::toDifferenceBounds( box );
	unsigned obj2 =
		  hypro::Plotter<Number>::getInstance().addObject( conversion.vertices() );
	std::cout << "Conversion vertices:" << conversion.vertices() << "\n";
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj2, hypro::plotting::colors[hypro::plotting::green] );
	// create a *.plt file (gnuplot).
	hypro::Plotter<Number>::getInstance().setFilename( "conversionBoxToDBMTest" );
	hypro::Plotter<Number>::getInstance().plot2d();
}

void testSatisfiesHalfspace() {
	std::cout << "Test satisfies halfspace: \n";
	hypro::Halfspace<Number> hp1( { Number( 1 ), Number( 1 ) }, Number( 16 ) );
	std::pair<hypro::CONTAINMENT, hypro::DifferenceBounds<Number>> res =
		  testDBM.satisfiesHalfspace( hp1 );

	std::cout << "Containment is: " << res.first;
	// plot to pdf
	hypro::Plotter<Number>::getInstance().clear();
	unsigned obj1 =
		  hypro::Plotter<Number>::getInstance().addObject( testDBM.vertices() );
	std::cout << "DBM vertices:" << testDBM.vertices() << "\n";
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj1, hypro::plotting::colors[hypro::plotting::red] );

	unsigned obj2 =
		  hypro::Plotter<Number>::getInstance().addObject( res.second.vertices() );
	std::cout << "DBM vertices:" << res.second.vertices() << "\n";
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj2, hypro::plotting::colors[hypro::plotting::green] );

	unsigned obj3 = hypro::Plotter<Number>::getInstance().addObject( hp1 );
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj3, hypro::plotting::colors[hypro::plotting::blue] );

	// create a *.plt file (gnuplot).
	hypro::Plotter<Number>::getInstance().setFilename( "satisfiesHalfspaceTest" );
	hypro::Plotter<Number>::getInstance().plot2d();
}

void testSatisfiesHalfspaces() {
	std::cout << "Test satisfies halfspaces: \n";
	hypro::Halfspace<Number> hp1( { Number( 1 ), Number( 1 ) }, Number( 16 ) );
	hypro::Halfspace<Number> hp2( { Number( 1 ), Number( 0 ) }, Number( 7.5 ) );

	hypro::matrix_t<Number> mat = hypro::matrix_t<Number>( 2, 2 );
	mat << 1, 1, 1, 0;

	hypro::vector_t<Number> vec = hypro::vector_t<Number>( 2 );
	vec << 16, 7.5;

	std::pair<hypro::CONTAINMENT, hypro::DifferenceBounds<Number>> res =
		  testDBM.satisfiesHalfspaces( mat, vec );

	std::cout << "Containment is: " << res.first;
	// plot to pdf
	hypro::Plotter<Number>::getInstance().clear();
	unsigned obj1 =
		  hypro::Plotter<Number>::getInstance().addObject( testDBM.vertices() );
	std::cout << "DBM vertices:" << testDBM.vertices() << "\n";
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj1, hypro::plotting::colors[hypro::plotting::red] );

	unsigned obj2 =
		  hypro::Plotter<Number>::getInstance().addObject( res.second.vertices() );
	std::cout << "DBM vertices:" << res.second.vertices() << "\n";
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj2, hypro::plotting::colors[hypro::plotting::green] );

	unsigned obj3 = hypro::Plotter<Number>::getInstance().addObject( hp1 );
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj3, hypro::plotting::colors[hypro::plotting::blue] );

	unsigned obj4 = hypro::Plotter<Number>::getInstance().addObject( hp2 );
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj4, hypro::plotting::colors[hypro::plotting::blue] );

	// create a *.plt file (gnuplot).
	hypro::Plotter<Number>::getInstance().setFilename( "satisfiesHalfspacesTest" );
	hypro::Plotter<Number>::getInstance().plot2d();
}

void testIntersectHalfspace() {
	std::cout << "Test intersect halfspace: \n";
	hypro::Halfspace<Number> hp1( { Number( 1 ), Number( 1 ) }, Number( 16 ) );
	hypro::DifferenceBounds<Number> res = testDBM.intersectHalfspace( hp1 );
	// plot to pdf
	hypro::Plotter<Number>::getInstance().clear();
	unsigned obj1 =
		  hypro::Plotter<Number>::getInstance().addObject( testDBM.vertices() );
	std::cout << "DBM vertices:" << testDBM.vertices() << "\n";
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj1, hypro::plotting::colors[hypro::plotting::red] );

	unsigned obj2 =
		  hypro::Plotter<Number>::getInstance().addObject( res.vertices() );
	std::cout << "DBM vertices:" << res.vertices() << "\n";
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj2, hypro::plotting::colors[hypro::plotting::green] );

	unsigned obj3 = hypro::Plotter<Number>::getInstance().addObject( hp1 );
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj3, hypro::plotting::colors[hypro::plotting::blue] );

	// create a *.plt file (gnuplot).
	hypro::Plotter<Number>::getInstance().setFilename( "intersectHalfspaceTest" );
	hypro::Plotter<Number>::getInstance().plot2d();
}
void testIntersectHalfspaces() {
	std::cout << "Test intersect halfspaces: \n";
	hypro::Halfspace<Number> hp1( { Number( 1 ), Number( 1 ) }, Number( 16 ) );
	hypro::Halfspace<Number> hp2( { Number( 1 ), Number( 0 ) }, Number( 7.5 ) );

	hypro::matrix_t<Number> mat = hypro::matrix_t<Number>( 2, 2 );
	mat << 1, 1, 1, 0;

	hypro::vector_t<Number> vec = hypro::vector_t<Number>( 2 );
	vec << 16, 7.5;

	hypro::DifferenceBounds<Number> res = testDBM.intersectHalfspaces( mat, vec );

	// plot to pdf
	hypro::Plotter<Number>::getInstance().clear();
	unsigned obj1 =
		  hypro::Plotter<Number>::getInstance().addObject( testDBM.vertices() );
	std::cout << "DBM vertices:" << testDBM.vertices() << "\n";
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj1, hypro::plotting::colors[hypro::plotting::red] );

	unsigned obj2 =
		  hypro::Plotter<Number>::getInstance().addObject( res.vertices() );
	std::cout << "DBM vertices:" << res.vertices() << "\n";
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj2, hypro::plotting::colors[hypro::plotting::green] );

	unsigned obj3 = hypro::Plotter<Number>::getInstance().addObject( hp1 );
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj3, hypro::plotting::colors[hypro::plotting::blue] );

	unsigned obj4 = hypro::Plotter<Number>::getInstance().addObject( hp2 );
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj4, hypro::plotting::colors[hypro::plotting::blue] );

	// create a *.plt file (gnuplot).
	hypro::Plotter<Number>::getInstance().setFilename( "intersectHalfspacesTest" );
	hypro::Plotter<Number>::getInstance().plot2d();
}

void testLinearTransformation() {
	hypro::matrix_t<Number> A( 2, 2 );
	A( 0, 0 ) = 1;
	A( 0, 1 ) = 2;
	A( 1, 0 ) = 3;
	A( 1, 1 ) = 4;

	hypro::DifferenceBounds<Number> res = testDBM.linearTransformation( A );
	hypro::HPolytope<Number> controlPolytope =
		  hypro::Converter<Number>::toHPolytope( testDBM ).linearTransformation( A );

	hypro::Plotter<Number>::getInstance().clear();
	unsigned obj1 =
		  hypro::Plotter<Number>::getInstance().addObject( testDBM.vertices() );
	std::cout << "DBM vertices:" << testDBM.vertices() << "\n";
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj1, hypro::plotting::colors[hypro::plotting::red] );

	unsigned obj2 =
		  hypro::Plotter<Number>::getInstance().addObject( res.vertices() );
	std::cout << "DBM vertices:" << res.vertices() << "\n";
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj2, hypro::plotting::colors[hypro::plotting::green] );

	unsigned obj3 = hypro::Plotter<Number>::getInstance().addObject(
		  controlPolytope.vertices() );
	std::cout << "Control Polytope vertices:" << controlPolytope.vertices()
			  << "\n";
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj3, hypro::plotting::colors[hypro::plotting::blue] );

	// create a *.plt file (gnuplot).
	hypro::Plotter<Number>::getInstance().setFilename( "linearTransformationTest" );
	hypro::Plotter<Number>::getInstance().plot2d();
}

void testAffineTransformation() {
	hypro::matrix_t<Number> A( 2, 2 );
	A( 0, 0 ) = 1;
	A( 0, 1 ) = 2;
	A( 1, 0 ) = 3;
	A( 1, 1 ) = 4;

	hypro::vector_t<Number> b( 2 );
	b( 0 ) = 1;
	b( 1 ) = 1;

	hypro::DifferenceBounds<Number> res = testDBM.affineTransformation( A, b );
	hypro::HPolytope<Number> controlPolytope =
		  hypro::Converter<Number>::toHPolytope( testDBM ).affineTransformation( A, b );

	hypro::Plotter<Number>::getInstance().clear();
	unsigned obj1 =
		  hypro::Plotter<Number>::getInstance().addObject( testDBM.vertices() );
	std::cout << "DBM vertices:" << testDBM.vertices() << "\n";
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj1, hypro::plotting::colors[hypro::plotting::red] );

	unsigned obj2 =
		  hypro::Plotter<Number>::getInstance().addObject( res.vertices() );
	std::cout << "DBM vertices:" << res.vertices() << "\n";
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj2, hypro::plotting::colors[hypro::plotting::green] );

	unsigned obj3 = hypro::Plotter<Number>::getInstance().addObject(
		  controlPolytope.vertices() );
	std::cout << "Control Polytope vertices:" << controlPolytope.vertices()
			  << "\n";
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj3, hypro::plotting::colors[hypro::plotting::blue] );

	// create a *.plt file (gnuplot).
	hypro::Plotter<Number>::getInstance().setFilename( "affineTransformationTest" );
	hypro::Plotter<Number>::getInstance().plot2d();
}

void testMinkowskiSum() {
	hypro::DifferenceBounds<Number> res = testDBM.minkowskiSum( testDBM2 );
	hypro::HPolytope<Number> controlPolytope =
		  hypro::Converter<Number>::toHPolytope( testDBM ).minkowskiSum(
				hypro::Converter<Number>::toHPolytope( testDBM2 ) );

	hypro::Plotter<Number>::getInstance().clear();
	unsigned obj1 =
		  hypro::Plotter<Number>::getInstance().addObject( testDBM.vertices() );
	std::cout << "DBM vertices:" << testDBM.vertices() << "\n";
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj1, hypro::plotting::colors[hypro::plotting::red] );

	unsigned obj2 =
		  hypro::Plotter<Number>::getInstance().addObject( testDBM2.vertices() );
	std::cout << "DBM vertices:" << testDBM2.vertices() << "\n";
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj2, hypro::plotting::colors[hypro::plotting::blue] );

	unsigned obj3 =
		  hypro::Plotter<Number>::getInstance().addObject( res.vertices() );
	std::cout << "Result  vertices:" << res.vertices() << "\n";
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj3, hypro::plotting::colors[hypro::plotting::green] );

	unsigned obj4 = hypro::Plotter<Number>::getInstance().addObject(
		  controlPolytope.vertices() );
	std::cout << "Result  vertices:" << controlPolytope.vertices() << "\n";
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj4, hypro::plotting::colors[hypro::plotting::orange] );

	// create a *.plt file (gnuplot).
	hypro::Plotter<Number>::getInstance().setFilename( "minkowskiSumTest" );
	hypro::Plotter<Number>::getInstance().plot2d();
}

void testExtraM() {
	std::cout << "Test ExtraM: \n";
	hypro::vector_t<hypro::DifferenceBounds<Number>::DBMEntry> MBounds(
		  3 );	//+1 for 0 clock
	/*
   * MBounds(x_0)=0
   * MBounds(x_1)=3
   * MBounds(x_2)=13
   */
	MBounds << hypro::DifferenceBounds<Number>::DBMEntry(
		  0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ ),
		  hypro::DifferenceBounds<Number>::DBMEntry(
				3.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ ),
		  hypro::DifferenceBounds<Number>::DBMEntry(
				13, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ );

	std::cout << "Original DBM: \n"
			  << testDBMExtra << "\n";
	std::cout << "Extrapolated DBM: \n"
			  << testDBMExtra.extraM( MBounds ) << "\n";
	// plot to pdf
	hypro::Plotter<Number>::getInstance().clear();
	unsigned obj1 =
		  hypro::Plotter<Number>::getInstance().addObject( testDBMExtra.vertices() );
	std::cout << "Original DBM vertices:" << testDBMExtra.vertices() << "\n";
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj1, hypro::plotting::colors[hypro::plotting::blue] );

	unsigned obj2 = hypro::Plotter<Number>::getInstance().addObject(
		  testDBMExtra.extraM( MBounds ).vertices() );
	std::cout << "Extrapolated DBM vertices:"
			  << testDBMExtra.extraM( MBounds ).vertices() << "\n";
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj2, hypro::plotting::colors[hypro::plotting::red] );

	// create a *.plt file (gnuplot).
	hypro::Plotter<Number>::getInstance().setFilename( "extraMTest" );
	hypro::Plotter<Number>::getInstance().plot2d();
}

void testExtraMPlus() {
	// TODO this is the only one that does not look like the pic in the paper, but
	// works correct.??
	// TODO Maybe my example is just bad.
	std::cout << "Test ExtraMPlus: \n";
	hypro::vector_t<hypro::DifferenceBounds<Number>::DBMEntry> MBounds(
		  3 );	//+1 for 0 clock
	/*
   * MBounds(x_0)=0
   * MBounds(x_1)=3
   * MBounds(x_2)=13
   */
	MBounds << hypro::DifferenceBounds<Number>::DBMEntry(
		  0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ ),
		  hypro::DifferenceBounds<Number>::DBMEntry(
				3.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ ),
		  hypro::DifferenceBounds<Number>::DBMEntry(
				13, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ );

	std::cout << "Original DBM: \n"
			  << testDBMExtra << "\n";
	std::cout << "Extrapolated DBM: \n"
			  << testDBMExtra.extraMPlus( MBounds ) << "\n";
	// plot to pdf
	hypro::Plotter<Number>::getInstance().clear();
	unsigned obj1 =
		  hypro::Plotter<Number>::getInstance().addObject( testDBMExtra.vertices() );
	std::cout << "Original DBM vertices:" << testDBMExtra.vertices() << "\n";
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj1, hypro::plotting::colors[hypro::plotting::blue] );

	unsigned obj2 = hypro::Plotter<Number>::getInstance().addObject(
		  testDBMExtra.extraMPlus( MBounds ).vertices() );
	std::cout << "Extrapolated DBM vertices:"
			  << testDBMExtra.extraMPlus( MBounds ).vertices() << "\n";
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj2, hypro::plotting::colors[hypro::plotting::red] );

	// create a *.plt file (gnuplot).
	hypro::Plotter<Number>::getInstance().setFilename( "extraMPlusTest" );
	hypro::Plotter<Number>::getInstance().plot2d();
}

void testExtraLU() {
	std::cout << "Test ExtraLU: \n";
	hypro::vector_t<hypro::DifferenceBounds<Number>::DBMEntry> LBounds(
		  3 );	//+1 for 0 clock
	hypro::vector_t<hypro::DifferenceBounds<Number>::DBMEntry> UBounds(
		  3 );	//+1 for 0 clock

	LBounds << hypro::DifferenceBounds<Number>::DBMEntry(
		  0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ ),
		  hypro::DifferenceBounds<Number>::DBMEntry(
				3.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ ),
		  hypro::DifferenceBounds<Number>::DBMEntry(
				1.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ );

	UBounds << hypro::DifferenceBounds<Number>::DBMEntry(
		  0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ ),
		  hypro::DifferenceBounds<Number>::DBMEntry(
				3.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ ),
		  hypro::DifferenceBounds<Number>::DBMEntry(
				13, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ );

	std::cout << "Original DBM: \n"
			  << testDBMExtra << "\n";
	std::cout << "Extrapolated DBM: \n"
			  << testDBMExtra.extraLU( LBounds, UBounds ) << "\n";
	// plot to pdf
	hypro::Plotter<Number>::getInstance().clear();
	unsigned obj1 =
		  hypro::Plotter<Number>::getInstance().addObject( testDBMExtra.vertices() );
	std::cout << "Original DBM vertices:" << testDBMExtra.vertices() << "\n";
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj1, hypro::plotting::colors[hypro::plotting::blue] );

	unsigned obj2 = hypro::Plotter<Number>::getInstance().addObject(
		  testDBMExtra.extraLU( LBounds, UBounds ).vertices() );
	std::cout << "Extrapolated DBM vertices:"
			  << testDBMExtra.extraLU( LBounds, UBounds ).vertices() << "\n";
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj2, hypro::plotting::colors[hypro::plotting::red] );

	// create a *.plt file (gnuplot).
	hypro::Plotter<Number>::getInstance().setFilename( "extraLUTest" );
	hypro::Plotter<Number>::getInstance().plot2d();
}
void testExtraLUPlus() {
	std::cout << "Test ExtraLU: \n";
	hypro::vector_t<hypro::DifferenceBounds<Number>::DBMEntry> LBounds(
		  3 );	//+1 for 0 clock
	hypro::vector_t<hypro::DifferenceBounds<Number>::DBMEntry> UBounds(
		  3 );	//+1 for 0 clock

	LBounds << hypro::DifferenceBounds<Number>::DBMEntry(
		  0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ ),
		  hypro::DifferenceBounds<Number>::DBMEntry(
				3.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ ),
		  hypro::DifferenceBounds<Number>::DBMEntry(
				1.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ );

	UBounds << hypro::DifferenceBounds<Number>::DBMEntry(
		  0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ ),
		  hypro::DifferenceBounds<Number>::DBMEntry(
				3.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ ),
		  hypro::DifferenceBounds<Number>::DBMEntry(
				13, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ );

	std::cout << "Original DBM: \n"
			  << testDBMExtra << "\n";
	std::cout << "Extrapolated DBM: \n"
			  << testDBMExtra.extraLUPlus( LBounds, UBounds ) << "\n";
	// plot to pdf
	hypro::Plotter<Number>::getInstance().clear();
	unsigned obj1 =
		  hypro::Plotter<Number>::getInstance().addObject( testDBMExtra.vertices() );
	std::cout << "Original DBM vertices:" << testDBMExtra.vertices() << "\n";
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj1, hypro::plotting::colors[hypro::plotting::blue] );

	unsigned obj2 = hypro::Plotter<Number>::getInstance().addObject(
		  testDBMExtra.extraLUPlus( LBounds, UBounds ).vertices() );
	std::cout << "Extrapolated DBM vertices:"
			  << testDBMExtra.extraLUPlus( LBounds, UBounds ).vertices() << "\n";
	hypro::Plotter<Number>::getInstance().setObjectColor(
		  obj2, hypro::plotting::colors[hypro::plotting::red] );

	// create a *.plt file (gnuplot).
	hypro::Plotter<Number>::getInstance().setFilename( "extraLUPlusTest" );
	hypro::Plotter<Number>::getInstance().plot2d();
}

void testPrint() {
	std::cout << "Test instance DBM: \n";
	std::cout << testDBM;
}
