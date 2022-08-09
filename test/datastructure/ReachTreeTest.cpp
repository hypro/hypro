/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "test/defines.h"

#include "gtest/gtest.h"
#include <bits/c++config.h>
#include <carl/interval/Interval.h>
#include <hypro/datastructures/HybridAutomaton/HybridAutomaton.h>
#include <hypro/datastructures/reachability/ReachTreev2.h>
#include <hypro/datastructures/reachability/ReachTreev2Heuristics.h>
#include <hypro/datastructures/reachability/ReachTreev2Util.h>
#include <hypro/types.h>

namespace test::detail {
template <typename N>
struct Representation {
	using NumberType = N;
	int content_;
};

}  // namespace test::detail

TEST( ReachtTreeTest, Constructor ) {
	// root location
	hypro::Location<int> root_loc;
	root_loc.setName( "l0" );
	// root node
	hypro::ReachTreeNode<test::detail::Representation<int>, hypro::Location<int>> root{
		  &root_loc, { 1 }, carl::Interval<hypro::SegmentInd>{ 0, 0 } };

	// transition
	hypro::Location<int> source;
	hypro::Location<int> target;
	hypro::Transition<int, hypro::Location<int>> trans{ &source, &target };

	// add children
	root.addChild( { 1 }, carl::Interval<hypro::SegmentInd>{ 0, 1 }, &trans );
	root.addChild( { 2 }, carl::Interval<hypro::SegmentInd>{ 1, 2 }, &trans );

	SUCCEED();
}

TEST( ReachtTreeTest, CountSegments ) {
	// root node
	hypro::ReachTreeNode<test::detail::Representation<int>, hypro::Location<int>> root{
		  nullptr, { 1 }, carl::Interval<hypro::SegmentInd>{ 0, 0 } };

	// transition
	hypro::Location<int> source;
	hypro::Location<int> target;
	hypro::Transition<int, hypro::Location<int>> trans{ &source, &target };

	// add children
	auto& ch1 = root.addChild( { 1 }, carl::Interval<hypro::SegmentInd>{ 0, 0 }, &trans );
	auto& ch2 = root.addChild( { 2 }, carl::Interval<hypro::SegmentInd>{ 0, 0 }, &trans );

	// add flowpipes
	ch1.setFlowpipe( { { 1 }, { 2 }, { 3 } } );
	std::vector<test::detail::Representation<int>> fp2{ { 3 }, { 4 }, { 5 } };
	root.setFlowpipe( fp2 );
	ch2.setFlowpipe( std::move( fp2 ) );

	std::size_t numberSegments = hypro::getNumberSegments( root );
	EXPECT_EQ( std::size_t{ 9 }, numberSegments );
}

TEST( ReachTreeTest, Paths ) {
	using Node = hypro::ReachTreeNode<test::detail::Representation<int>, hypro::Location<int>>;
	using Loc = hypro::Location<int>;
	std::vector<Loc*> locations;
	Loc l0{ "l0" };
	Loc l1{ "l1" };
	Loc l2{ "l2" };
	locations.push_back( &l0 );
	locations.push_back( &l1 );
	locations.push_back( &l2 );

	// root node
	Node root{
		  locations[0], { 1 }, carl::Interval<hypro::SegmentInd>{ 0, 0 } };

	// transition
	hypro::Transition<int, Loc> trans0{ locations[0], locations[1] };
	hypro::Transition<int, Loc> trans1{ locations[0], locations[2] };

	// add children
	root.addChild( { 1 }, carl::Interval<hypro::SegmentInd>{ 0, 1 }, &trans0 );
	root.addChild( { 2 }, carl::Interval<hypro::SegmentInd>{ 1, 2 }, &trans1 );

	Node* leaf1 = *( root.getChildren().begin() );

	// get path
	hypro::Path<int> path = leaf1->getPath();
	EXPECT_EQ( std::size_t( 1 ), path.elements.size() );

	// print path
	std::stringstream ss;
	ss << path;
	EXPECT_EQ( "l0, [0, 1] -> l1", ss.str() );
}

TEST( ReachTreeTest, CycleHeuristics ) {
	using Node = hypro::ReachTreeNode<test::detail::Representation<int>, hypro::Location<int>>;
	using Loc = hypro::Location<int>;
	std::vector<Loc*> locations;
	Loc l0{ "l0" };
	Loc l1{ "l1" };
	Loc l2{ "l2" };
	locations.push_back( &l0 );
	locations.push_back( &l1 );
	locations.push_back( &l2 );

	// root node
	Node root{
		  locations[0], { 1 }, carl::Interval<hypro::SegmentInd>{ 0, 0 } };

	// transition
	hypro::Transition<int, Loc> trans0{ locations[0], locations[1] };
	hypro::Transition<int, Loc> trans1{ locations[0], locations[2] };
	hypro::Transition<int, Loc> trans2{ locations[1], locations[0] };
	hypro::Transition<int, Loc> trans3{ locations[2], locations[0] };
	hypro::Transition<int, Loc> trans4{ locations[2], locations[1] };

	// add children: 0 -> 2 -> 0 -> 1
	auto* child = &root.addChild( { 2 }, carl::Interval<hypro::SegmentInd>{ 0, 1 }, &trans1 );
	child = &child->addChild( { 3 }, carl::Interval<hypro::SegmentInd>{ 0, 1 }, &trans3 );
	auto leaf1 = &child->addChild( { 3 }, carl::Interval<hypro::SegmentInd>{ 0, 1 }, &trans0 );
	// add children 0 -> 2 -> 1 -> 0
	child = &root.addChild( { 2 }, carl::Interval<hypro::SegmentInd>{ 0, 1 }, &trans1 );
	child = &child->addChild( { 3 }, carl::Interval<hypro::SegmentInd>{ 0, 1 }, &trans4 );
	auto leaf2 = &child->addChild( { 3 }, carl::Interval<hypro::SegmentInd>{ 0, 1 }, &trans2 );
	auto comp = hypro::LeastLocationCycleCount<test::detail::Representation<int>, hypro::Location<int>>{};
	EXPECT_EQ( 2, comp.largestLocationCycle( leaf1 ) );
	EXPECT_EQ( 1, comp.largestLocationCycle( leaf2 ) );
	EXPECT_TRUE( comp( leaf2, leaf1 ) );
	EXPECT_FALSE( comp( leaf1, leaf2 ) );
	EXPECT_FALSE( comp( leaf1, leaf1 ) );
	EXPECT_FALSE( comp( leaf2, leaf2 ) );
}
