#include "test/defines.h"
#include "gtest/gtest.h"
#include <hypro/util/Range.h>

using namespace hypro;

TEST( RangeTest, Constructor ) {
	std::vector<int> a{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	Range<std::vector<int>> r =
		  selectFirstConsecutiveRange( a, std::function( [&]( int i ) -> bool { return i >= 4; } ) );

	// conversion to vector
	auto v = toContainer( r );
	EXPECT_EQ( std::size_t( 6 ), v.size() );
}
