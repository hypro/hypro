/*
 * Copyright (c) 2022.
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
	// check the actual box
	EXPECT_TRUE( octree.contains( hypro::Box<double>(
		  std::vector<carl::Interval<double>>( { carl::Interval<double>( 1, 2 ), carl::Interval<double>( 1, 2 ) } ) ) ) );

	EXPECT_FALSE( octree.contains( hypro::Point<double>{ 0.9, 1 } ) );
	EXPECT_FALSE( octree.contains( hypro::Point<double>{ 1, 2.1 } ) );
	EXPECT_FALSE( octree.contains( hypro::Point<double>{ 0, 0 } ) );
	EXPECT_FALSE( octree.contains( hypro::Point<double>{ 5, 5 } ) );
	// the container should not be fully contained
	EXPECT_FALSE( octree.contains( hypro::Box<double>(
		  std::vector<carl::Interval<double>>( { carl::Interval<double>( 0, 10 ), carl::Interval<double>( 0, 10 ) } ) ) ) );
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
								 []( const auto& child ) { return child.isCovered(); } ) );
	EXPECT_EQ( 2, std::count_if( std::begin( octree_partial_covered.getChildren() ),
								 std::end( octree_partial_covered.getChildren() ),
								 []( const auto& child ) { return !child.isCovered(); } ) );
}

TEST( HyperoctreeTest, IncrementalCoverage ) {
	using Otree = hypro::Hyperoctree<double>;
	using I = carl::Interval<double>;
	using IV = std::vector<I>;
	using Box = hypro::Box<double>;
	Otree octree{ 2, 2, Box( IV( { I( 0, 1 ), I( 0, 1 ) } ) ) };

	octree.add( Box( IV( { I( -1.0, 0.3 ), I( -1.0, 0.3 ) } ) ) );
	EXPECT_FALSE( octree.isCovered() );
	auto intermediate_child_it = std::find_if( std::begin( octree.getChildren() ), std::end( octree.getChildren() ), []( const Otree& child ) { return child.getContainer() == Box{ IV{ I{ 0.0, 0.5 }, I{ 0.0, 0.5 } } }; } );
	ASSERT_TRUE( intermediate_child_it != std::end( octree.getChildren() ) );
	EXPECT_FALSE( intermediate_child_it->isCovered() );
	auto covered_child_it = std::find_if( std::begin( intermediate_child_it->getChildren() ), std::end( intermediate_child_it->getChildren() ), []( const Otree& child ) { return child.getContainer() == Box{ IV{ I{ 0.0, 0.25 }, I{ 0.0, 0.25 } } }; } );
	EXPECT_TRUE( covered_child_it != std::end( intermediate_child_it->getChildren() ) );
	EXPECT_TRUE( covered_child_it->isCovered() );
	EXPECT_TRUE( covered_child_it->getChildren().empty() );
	EXPECT_TRUE( covered_child_it->getRemainingDepth() == std::size_t( 0 ) );
	EXPECT_TRUE( covered_child_it->getData().empty() );
	auto covered_child_it2 = std::find_if( std::begin( intermediate_child_it->getChildren() ), std::end( intermediate_child_it->getChildren() ), []( const Otree& child ) { return child.getContainer() == Box{ IV{ I{ 0.25, 0.5 }, I{ 0.0, 0.25 } } }; } );
	EXPECT_TRUE( covered_child_it2->getRemainingDepth() == std::size_t( 0 ) );
	EXPECT_FALSE( covered_child_it2->getData().empty() );

	octree.add( Box( IV( { I( -1.0, 0.6 ), I( -1.0, 0.3 ) } ) ) );
	EXPECT_FALSE( intermediate_child_it->isCovered() );
	EXPECT_TRUE( covered_child_it->isCovered() );

	ASSERT_TRUE( covered_child_it2 != std::end( intermediate_child_it->getChildren() ) );
	EXPECT_TRUE( covered_child_it2->isCovered() );
	EXPECT_TRUE( std::all_of( std::begin( intermediate_child_it->getChildren() ), std::end( intermediate_child_it->getChildren() ), [covered_child_it, covered_child_it2]( const Otree& child ) { return ( child == *covered_child_it || child == *covered_child_it2 ) || !child.isCovered(); } ) );

	octree.add( Box( IV( { I( 0.4, 0.6 ), I( 0.4, 0.6 ) } ) ) );
	EXPECT_FALSE( intermediate_child_it->isCovered() );
	EXPECT_TRUE( std::all_of( std::begin( intermediate_child_it->getChildren() ), std::end( intermediate_child_it->getChildren() ), [covered_child_it, covered_child_it2]( const Otree& child ) { return ( child == *covered_child_it || child == *covered_child_it2 ) || !child.isCovered(); } ) );

	auto covered_child_it3 = std::find_if( std::begin( intermediate_child_it->getChildren() ), std::end( intermediate_child_it->getChildren() ), []( const Otree& child ) { return child.getContainer() == Box{ IV{ I{ 0.0, 0.25 }, I{ 0.25, 0.5 } } }; } );
	auto covered_child_it4 = std::find_if( std::begin( intermediate_child_it->getChildren() ), std::end( intermediate_child_it->getChildren() ), []( const Otree& child ) { return child.getContainer() == Box{ IV{ I{ 0.25, 0.5 }, I{ 0.25, 0.5 } } }; } );
	EXPECT_FALSE( covered_child_it3->isCovered() );
	EXPECT_FALSE( covered_child_it4->isCovered() );
	octree.add( Box( IV( { I( 0.0, 0.3 ), I( 0.2, 0.6 ) } ) ) );
	EXPECT_TRUE( covered_child_it3->isCovered() );
	EXPECT_FALSE( covered_child_it4->isCovered() );
	EXPECT_FALSE( covered_child_it4->getData().empty() );

	octree.add( Box( IV( { I( 0.2, 0.42 ), I( 0.2, 0.6 ) } ) ) );
	EXPECT_TRUE( covered_child_it3->isCovered() );
	EXPECT_FALSE( covered_child_it4->isCovered() );
	EXPECT_FALSE( covered_child_it4->getData().empty() );

	octree.add( Box( IV( { I( 0.2, 0.42 ), I( 0.2, 0.6 ) } ) ) );
	EXPECT_TRUE( covered_child_it3->isCovered() );
	EXPECT_FALSE( covered_child_it4->isCovered() );
	EXPECT_FALSE( covered_child_it4->getData().empty() );

	octree.add( Box( IV( { I( 0.4, 0.62 ), I( 0.2, 0.6 ) } ) ) );
	EXPECT_TRUE( covered_child_it3->isCovered() );
	EXPECT_TRUE( covered_child_it4->isCovered() );
	EXPECT_TRUE( covered_child_it4->getData().empty() );
	EXPECT_TRUE( intermediate_child_it->isCovered() );
	EXPECT_FALSE( octree.isCovered() );
}
