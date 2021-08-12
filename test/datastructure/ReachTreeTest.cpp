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
	// root node
	hypro::ReachTreeNode<test::detail::Representation<int>> root{
		  nullptr, { 1 }, carl::Interval<hypro::SegmentInd>{ 0, 0 } };

	// transition
	hypro::Location<int> source;
	hypro::Location<int> target;
	hypro::Transition<int> trans{ &source, &target };

	// add children
	root.addChild( { 1 }, carl::Interval<hypro::SegmentInd>{ 0, 0 }, &trans );
	root.addChild( { 2 }, carl::Interval<hypro::SegmentInd>{ 0, 0 }, &trans );

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
