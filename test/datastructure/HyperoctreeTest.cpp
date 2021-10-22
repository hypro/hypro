/*
 * Created by stefan on 05.10.21.
 */

#include "test/defines.h"
#include "gtest/gtest.h"
#include <hypro/datastructures/Hyperoctree.h>

TEST( HyperoctreeTest, Constructor ) {
	hypro::Hyperoctree<double> octree{ 2, 2,
									   hypro::Box<double>( std::vector<carl::Interval<double>>(
											 carl::Interval<double>( 1, 2 ), carl::Interval<double>( 1, 2 ) ) ) };
}
