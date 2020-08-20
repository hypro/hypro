#include "../../src/hypro/algorithms/convexHull/ConvexHull.h"
#include "../../src/hypro/representations/GeometricObjectBase.h"
#include "../defines.h"
#include "gtest/gtest.h"

#include "../../src/hypro/config.h"

using namespace hypro;

class FacetEnumerationTest : public ::testing::Test {
  protected:
	virtual void SetUp() {}

	virtual void TearDown() {}

  public:
	FacetEnumerationTest() {}
	~FacetEnumerationTest() {}
};

TEST_F( FacetEnumerationTest, Constructor ) {
	std::vector<Point<mpq_class>> points;
	points.push_back( Point<mpq_class>( { 1, 0 } ) );

	ConvexHull<mpq_class> def;
	ConvexHull<mpq_class> degenerate( points );
	EXPECT_EQ( std::size_t( 1 ), degenerate.getPoints().size() );

	points.push_back( Point<mpq_class>( { 0, 0 } ) );
	points.push_back( Point<mpq_class>( { 0, 1 } ) );
	points.push_back( Point<mpq_class>( { 1, 1 } ) );

	ConvexHull<mpq_class> box( points );
	ConvexHull<mpq_class> boxCopy( box );

	EXPECT_EQ( std::size_t( 1 ), degenerate.getPoints().size() );
	EXPECT_EQ( std::size_t( 4 ), box.getPoints().size() );
	EXPECT_EQ( std::size_t( 4 ), boxCopy.getPoints().size() );

	SUCCEED();
}

TEST_F( FacetEnumerationTest, Access ) {}

TEST_F( FacetEnumerationTest, SimpleEnumeration ) {
	std::vector<Point<mpq_class>> points;
	points.push_back( Point<mpq_class>( { 1, 0 } ) );
	points.push_back( Point<mpq_class>( { 0, 0 } ) );
	points.push_back( Point<mpq_class>( { 0, 1 } ) );
	points.push_back( Point<mpq_class>( { 1, 1 } ) );
	ConvexHull<mpq_class> box( points );
	box.convexHullVertices();
	EXPECT_EQ( std::size_t( 4 ), box.getHsv().size() );
	HPolytope<mpq_class> resContainer( box.getHsv() );
	for ( const auto& point : points ) {
		EXPECT_TRUE( resContainer.contains( point ) );
	}
}

TEST_F( FacetEnumerationTest, SimpleRedundantEnumeration ) {
	std::vector<Point<mpq_class>> points;
	points.push_back( Point<mpq_class>( { 1, 0 } ) );
	points.push_back( Point<mpq_class>( { 0, 0 } ) );
	points.push_back( Point<mpq_class>( { 0, 1 } ) );
	points.push_back( Point<mpq_class>( { 1, 1 } ) );
	points.push_back( Point<mpq_class>( { 1, 0 } ) );
	points.push_back( Point<mpq_class>( { carl::rationalize<mpq_class>( 0.5 ), 1 } ) );
	points.push_back(
		  Point<mpq_class>( { carl::rationalize<mpq_class>( 0.5 ), carl::rationalize<mpq_class>( 0.5 ) } ) );
	points.push_back( Point<mpq_class>( { 1, 1 } ) );
	points.push_back( Point<mpq_class>( { 1, 1 } ) );
	ConvexHull<mpq_class> box( points );
	box.convexHullVertices();
	EXPECT_EQ( std::size_t( 4 ), box.getHsv().size() );
	HPolytope<mpq_class> resContainer( box.getHsv() );
	for ( const auto& point : points ) {
		EXPECT_TRUE( resContainer.contains( point ) );
	}
}

TEST_F( FacetEnumerationTest, DegenerateEnumeration ) {
	// Test a pyramid with quadratic foundation in 3D space
	std::vector<Point<mpq_class>> points;
	points.push_back( Point<mpq_class>( { 1, 0, 1 } ) );
	points.push_back( Point<mpq_class>( { 1, 0, -1 } ) );
	points.push_back( Point<mpq_class>( { -1, 0, 1 } ) );
	points.push_back( Point<mpq_class>( { -1, 0, -1 } ) );
	points.push_back( Point<mpq_class>( { 0, 1, 0 } ) );
	ConvexHull<mpq_class> box( points );
	box.convexHullVertices();
	EXPECT_EQ( std::size_t( 5 ), box.getHsv().size() );
	HPolytope<mpq_class> resContainer( box.getHsv() );
	for ( const auto& point : points ) {
		EXPECT_TRUE( resContainer.contains( point ) );
	}
}

TEST_F( FacetEnumerationTest, DegenerateEnumeration2 ) {
	// Actual (failing) problem from benchmark runs, which specifies an object described by 2 points in a 3D space.
	std::vector<Point<mpq_class>> points;
	// approx. (0.1001,0,0)
	points.push_back( Point<mpq_class>( { mpq_class( "1170371095970163531301353990512407462289424333177/"
													 "11692013098647223345629478661730264157247460343808" ),
										  0, 0 } ) );
	// approx. (0.2002,0,0)
	points.push_back( Point<mpq_class>( { mpq_class( "2340742191940321312133937153702758040756082833417/"
													 "11692013098647223345629478661730264157247460343808" ),
										  0, 0 } ) );

	ConvexHull<mpq_class> ch( points );
	ch.convexHullVertices();

	EXPECT_EQ( std::size_t( 6 ), ch.getHsv().size() );
	HPolytope<mpq_class> resContainer( ch.getHsv() );
	for ( const auto& point : points ) {
		EXPECT_TRUE( resContainer.contains( point ) );
	}
}

TEST_F( FacetEnumerationTest, DegenerateEnumeration3 ) {
	std::vector<Point<mpq_class>> points;
	points.push_back( Point<mpq_class>( { mpq_class( "510" ), mpq_class( "20" ), mpq_class( "20" ) } ) );
	points.push_back( Point<mpq_class>( { mpq_class( "511" ), mpq_class( "21" ), mpq_class( "21" ) } ) );
	points.push_back( Point<mpq_class>( { mpq_class( "511" ), mpq_class( "21" ), mpq_class( "22" ) } ) );
	points.push_back( Point<mpq_class>( { mpq_class( "511" ), mpq_class( "22" ), mpq_class( "21" ) } ) );
	points.push_back( Point<mpq_class>( { mpq_class( "511" ), mpq_class( "22" ), mpq_class( "22" ) } ) );
	points.push_back( Point<mpq_class>( { mpq_class( "520" ), mpq_class( "20" ), mpq_class( "20" ) } ) );
	points.push_back( Point<mpq_class>( { mpq_class( "521" ), mpq_class( "21" ), mpq_class( "21" ) } ) );
	points.push_back( Point<mpq_class>( { mpq_class( "521" ), mpq_class( "21" ), mpq_class( "22" ) } ) );
	points.push_back( Point<mpq_class>( { mpq_class( "521" ), mpq_class( "22" ), mpq_class( "21" ) } ) );
	points.push_back( Point<mpq_class>( { mpq_class( "521" ), mpq_class( "22" ), mpq_class( "22" ) } ) );

	ConvexHull<mpq_class> ch( points );
	ch.convexHullVertices();

	HPolytope<mpq_class> resContainer( ch.getHsv() );
	for ( const auto& point : points ) {
		EXPECT_TRUE( resContainer.contains( point ) );
	}
}

/*
TEST_F( FacetEnumerationTest, DegenerateEnumeration4 ) {
	// Actual (failing) problem from benchmark runs.
	std::vector<Point<mpq_class>> points;
	points.push_back( Point<mpq_class>( { mpq_class( "510" ), mpq_class( "20" ), mpq_class( "20" ) } ) );
	points.push_back( Point<mpq_class>( { mpq_class( "499997556421277873/980373000000000" ),
										  mpq_class( "500001253523251079/24987506500000000" ),
										  mpq_class( "500001253523251079/24987506500000000" ) } ) );
	points.push_back( Point<mpq_class>( { mpq_class( "499997556421277873/980373000000000" ),
										  mpq_class( "500001253523251079/24987506500000000" ),
										  mpq_class( "250000626774106751/12493753000000000" ) } ) );
	points.push_back( Point<mpq_class>( { mpq_class( "499997556421277873/980373000000000" ),
										  mpq_class( "250000626774106751/12493753000000000" ),
										  mpq_class( "500001253523251079/24987506500000000" ) } ) );
	points.push_back( Point<mpq_class>( { mpq_class( "499997556421277873/980373000000000" ),
										  mpq_class( "250000626774106751/12493753000000000" ),
										  mpq_class( "250000626774106751/12493753000000000" ) } ) );
	points.push_back( Point<mpq_class>( { mpq_class( "520" ), mpq_class( "20" ), mpq_class( "20" ) } ) );
	points.push_back( Point<mpq_class>( { mpq_class( "249998801730340251/480750500000000" ),
										  mpq_class( "500001253523251079/24987506500000000" ),
										  mpq_class( "500001253523251079/24987506500000000" ) } ) );
	points.push_back( Point<mpq_class>( { mpq_class( "249998801730340251/480750500000000" ),
										  mpq_class( "500001253523251079/24987506500000000" ),
										  mpq_class( "250000626774106751/12493753000000000" ) } ) );
	points.push_back( Point<mpq_class>( { mpq_class( "249998801730340251/480750500000000" ),
										  mpq_class( "250000626774106751/12493753000000000" ),
										  mpq_class( "500001253523251079/24987506500000000" ) } ) );
	points.push_back( Point<mpq_class>( { mpq_class( "249998801730340251/480750500000000" ),
										  mpq_class( "250000626774106751/12493753000000000" ),
										  mpq_class( "250000626774106751/12493753000000000" ) } ) );

	ConvexHull<mpq_class> ch( points );
	ch.convexHullVertices();

	HPolytope<mpq_class> resContainer( ch.getHsv() );
	for ( const auto& point : points ) {
		EXPECT_TRUE( resContainer.contains( point ) );
	}
}
*/
