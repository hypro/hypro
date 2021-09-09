#include "test/defines.h"
#include "gtest/gtest.h"
#include <bits/c++config.h>
#include <carl/interval/Interval.h>
#include <hypro/datastructures/HybridAutomaton/HybridAutomaton.h>
#include <hypro/datastructures/reachability/ReachTreev2.h>
#include <hypro/datastructures/reachability/ReachTreev2Util.h>
#include <hypro/types.h>

namespace test::detail {
template <typename N>
struct Representation {
	int content_;
};

}  // namespace test::detail

TEST( ReachtTreeTest, Constructor ) {
	// root location
	hypro::Location<int> root_loc;
	root_loc.setName( "l0" );
	// root node
	hypro::ReachTreeNode<test::detail::Representation<int>> root{
		  &root_loc, { 1 }, carl::Interval<hypro::SegmentInd>{ 0, 0 } };

	// transition
	hypro::Location<int> source;
	hypro::Location<int> target;
	hypro::Transition<int> trans{ &source, &target };

	// add children
	root.addChild( { 1 }, carl::Interval<hypro::SegmentInd>{ 0, 1 }, &trans );
	root.addChild( { 2 }, carl::Interval<hypro::SegmentInd>{ 1, 2 }, &trans );

	SUCCEED();
}

TEST( ReachtTreeTest, CountSegments ) {
	// root node
	hypro::ReachTreeNode<test::detail::Representation<int>> root{
		  nullptr, { 1 }, carl::Interval<hypro::SegmentInd>{ 0, 0 } };

	// transition
	hypro::Location<int> source;
	hypro::Location<int> target;
	hypro::Transition<int> trans{ &source, &target };

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
	using Node = hypro::ReachTreeNode<test::detail::Representation<int>>;
	using Loc = hypro::Location<int>;
	std::vector<Loc*> locations;
	Loc l0{ "l0" };
	Loc l1{ "l1" };
	Loc l2{ "l2" };
	locations.push_back( &l0 );
	locations.push_back( &l1 );
	locations.push_back( &l2 );

	// root node
	hypro::ReachTreeNode<test::detail::Representation<int>> root{
		  locations[0], { 1 }, carl::Interval<hypro::SegmentInd>{ 0, 0 } };

	// transition
	hypro::Transition<int> trans0{ locations[0], locations[1] };
	hypro::Transition<int> trans1{ locations[0], locations[2] };

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
