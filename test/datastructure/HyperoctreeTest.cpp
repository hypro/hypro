/*
 * Copyright (c) 2021.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Created by stefan on 05.10.21.
 */

#include "test/defines.h"
#include "gtest/gtest.h"
#include <hypro/datastructures/Hyperoctree.h>

TEST( HyperoctreeTest, Constructor ) {
	hypro::Hyperoctree<double> octree{ 2, 2,
									   hypro::Box<double>( std::vector<carl::Interval<double>>(
											 { carl::Interval<double>( 1, 2 ), carl::Interval<double>( 1, 2 ) } ) ) };
}

TEST( HyperoctreeTest, Insertion ) {
	hypro::Hyperoctree<double> octree{ 2, 2,
									   hypro::Box<double>( std::vector<carl::Interval<double>>(
											 { carl::Interval<double>( 0, 10 ), carl::Interval<double>( 0, 10 ) } ) ) };

	octree.add( hypro::Box<double>(
		  std::vector<carl::Interval<double>>( { carl::Interval<double>( 1, 2 ), carl::Interval<double>( 1, 2 ) } ) ) );

	EXPECT_TRUE( octree.contains( hypro::Point<double>{ 1, 1 } ) );
	EXPECT_TRUE( octree.contains( hypro::Point<double>{ 1, 2 } ) );
	EXPECT_TRUE( octree.contains( hypro::Point<double>{ 2, 1 } ) );
	EXPECT_TRUE( octree.contains( hypro::Point<double>{ 2, 2 } ) );
	EXPECT_TRUE( octree.contains( hypro::Point<double>{ 1.5, 1.5 } ) );

	EXPECT_FALSE( octree.contains( hypro::Point<double>{ 0.9, 1 } ) );
	EXPECT_FALSE( octree.contains( hypro::Point<double>{ 1, 2.1 } ) );
	EXPECT_FALSE( octree.contains( hypro::Point<double>{ 0, 0 } ) );
	EXPECT_FALSE( octree.contains( hypro::Point<double>{ 5, 5 } ) );
}

TEST( HyperoctreeTest, Coverage ) {
	hypro::Hyperoctree<double> octree{ 2, 1,
									   hypro::Box<double>( std::vector<carl::Interval<double>>(
											 { carl::Interval<double>( 0, 5 ), carl::Interval<double>( 0, 5 ) } ) ) };

	octree.add( hypro::Box<double>( std::vector<carl::Interval<double>>(
		  { carl::Interval<double>( -1, 6 ), carl::Interval<double>( -1, 6 ) } ) ) );
	EXPECT_TRUE( octree.isCovered() );

	hypro::Hyperoctree<double> octree_partial_covered{
		  2, 1,
		  hypro::Box<double>( std::vector<carl::Interval<double>>(
				{ carl::Interval<double>( 0, 5 ), carl::Interval<double>( 0, 5 ) } ) ) };
	octree_partial_covered.add( hypro::Box<double>( std::vector<carl::Interval<double>>(
		  { carl::Interval<double>( -1, 6 ), carl::Interval<double>( 0, 3 ) } ) ) );
	EXPECT_FALSE( octree_partial_covered.isCovered() );
	EXPECT_EQ( 2, std::count_if( std::begin( octree_partial_covered.getChildren() ),
								 std::end( octree_partial_covered.getChildren() ),
								 []( const auto& ptr ) { return ptr->isCovered(); } ) );
	EXPECT_EQ( 2, std::count_if( std::begin( octree_partial_covered.getChildren() ),
								 std::end( octree_partial_covered.getChildren() ),
								 []( const auto& ptr ) { return !ptr->isCovered(); } ) );
}
