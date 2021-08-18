#include "test/defines.h"
#include "gtest/gtest.h"
#include <hypro/datastructures/reachability/timing/HierarchicalIntervalVector.h>

using namespace hypro;

/**
 * @brief Test fixture to initialize the HIV properly for each test.
 */
class HIVTest : public ::testing::Test {
  public:
	using Intv = carl::Interval<mpq_class>;

  protected:
	void SetUp() override {
		hivPlain.initialize( CONTAINMENT::BOT, 10 );
		hiv1.initialize( CONTAINMENT::BOT, 10 );

		hiv1.insertInterval( CONTAINMENT::PARTIAL, Intv( 2, 7 ) );
		hiv1.insertInterval( CONTAINMENT::FULL, Intv( 3, 5 ) );
		hiv1.insertInterval( CONTAINMENT::FULL, Intv( 7, 8 ) );
	}

	void TearDown() override {
		hivPlain.clear();
		hiv1.clear();
	}

	std::vector<CONTAINMENT> order{ CONTAINMENT::BOT, CONTAINMENT::PARTIAL, CONTAINMENT::FULL };

	HierarchicalIntervalVector<CONTAINMENT, mpq_class> hivPlain =
		  HierarchicalIntervalVector<CONTAINMENT, mpq_class>{ order };
	HierarchicalIntervalVector<CONTAINMENT, mpq_class> hiv1 =
		  HierarchicalIntervalVector<CONTAINMENT, mpq_class>{ order };
};

TEST_F( HIVTest, Insertion ) {}

TEST_F( HIVTest, Override ) {}

TEST_F( HIVTest, Fill ) {
	hivPlain.fill( CONTAINMENT::PARTIAL, 5 );
	EXPECT_TRUE( hivPlain.hasEntry( Intv( 5, 10 ), CONTAINMENT::PARTIAL ) );
	EXPECT_TRUE( hivPlain.hasEntry( Intv( 0, 1 ), CONTAINMENT::BOT ) );

	// partial intersections
	EXPECT_TRUE( hivPlain.hasEntry( Intv( 4, 7 ), CONTAINMENT::PARTIAL ) );
	EXPECT_TRUE( hivPlain.hasEntry( Intv( 4, 7 ), CONTAINMENT::BOT ) );

	// no intersections
	EXPECT_FALSE( hivPlain.hasEntry( Intv( 3, 4 ), CONTAINMENT::PARTIAL ) );
	EXPECT_FALSE( hivPlain.hasEntry( Intv( 6, 7 ), CONTAINMENT::BOT ) );
}

TEST_F( HIVTest, FullCover ) {
	EXPECT_TRUE( fullCover( hiv1, Intv( 3, 5 ), CONTAINMENT::FULL ) );
	EXPECT_TRUE( fullCover( hiv1, Intv( 4, 5 ), CONTAINMENT::FULL ) );
	EXPECT_TRUE( fullCover( hiv1, Intv( 5, 7 ), CONTAINMENT::PARTIAL ) );

	EXPECT_FALSE( fullCover( hiv1, Intv( 0, 10 ), CONTAINMENT::FULL ) );
	EXPECT_FALSE( fullCover( hiv1, Intv( 4, 6 ), CONTAINMENT::FULL ) );
	EXPECT_FALSE( fullCover( hiv1, Intv( 4, 6 ), CONTAINMENT::PARTIAL ) );
	EXPECT_FALSE( fullCover( hiv1, Intv( 5, 7 ), CONTAINMENT::FULL ) );
}
