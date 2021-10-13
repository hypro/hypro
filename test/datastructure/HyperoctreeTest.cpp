/*
 * Created by stefan on 05.10.21.
 */

#include "test/defines.h"
#include "gtest/gtest.h"
#include <hypro/datastructures/Hyperoctree.h>

template <typename N>
struct Predicate_simple {
	Predicate_simple( int splits = 2 ) { mSplits = 2; }

	hypro::HyperOctreeOp operator()( int i ) { return hypro::HyperOctreeOp::ADD; }
	std::vector<Predicate_simple> split() { return std::vector<Predicate_simple>( mSplits ); }

	int mSplits;
};

TEST( HyperoctreeTest, Constructor ) {
	using D = int;
	Predicate_simple<D> p{ 2 };
	hypro::Hyperoctree<Predicate_simple, D> octree{ p };
}

TEST( HyperoctreeTest, Predicates ) {
	using I = carl::Interval<int>;

	hypro::Box<int> initialBox{ std::vector<I>{ I{ 1, 4 }, I{ 4, 7 } } };
	hypro::BoxContainment<hypro::Box<int>> containmentPredicate{ 3, initialBox };

	// box not contained
	hypro::Box<int> outsideBox{ std::vector<I>{ I{ -1, 0 }, I{ 4, 5 } } };
	EXPECT_EQ( hypro::HyperOctreeOp::SKIP, containmentPredicate( outsideBox ) );

	// box fully contained
	hypro::Box<int> insideBox{ std::vector<I>{ I{ 1, 1 }, I{ 4, 4 } } };
	EXPECT_EQ( hypro::HyperOctreeOp::DESCEND, containmentPredicate( insideBox ) );

	// box partially contained
	hypro::Box<int> intersectingBox{ std::vector<I>{ I{ 1, 9 }, I{ 4, 4 } } };
	EXPECT_EQ( hypro::HyperOctreeOp::ADD, containmentPredicate( intersectingBox ) );

	// test splitting
	auto splits = containmentPredicate.split();
	EXPECT_EQ( std::size_t( 9 ), splits.size() );
	std::vector<hypro::Box<int>> targetBoxes;
	targetBoxes.emplace_back( hypro::Box<int>{ std::vector<I>{ I{ 1, 2 }, I{ 4, 5 } } } );
	targetBoxes.emplace_back( hypro::Box<int>{ std::vector<I>{ I{ 2, 3 }, I{ 4, 5 } } } );
	targetBoxes.emplace_back( hypro::Box<int>{ std::vector<I>{ I{ 3, 4 }, I{ 4, 5 } } } );

	targetBoxes.emplace_back( hypro::Box<int>{ std::vector<I>{ I{ 1, 2 }, I{ 5, 6 } } } );
	targetBoxes.emplace_back( hypro::Box<int>{ std::vector<I>{ I{ 2, 3 }, I{ 5, 6 } } } );
	targetBoxes.emplace_back( hypro::Box<int>{ std::vector<I>{ I{ 3, 4 }, I{ 5, 6 } } } );

	targetBoxes.emplace_back( hypro::Box<int>{ std::vector<I>{ I{ 1, 2 }, I{ 6, 7 } } } );
	targetBoxes.emplace_back( hypro::Box<int>{ std::vector<I>{ I{ 2, 3 }, I{ 6, 7 } } } );
	targetBoxes.emplace_back( hypro::Box<int>{ std::vector<I>{ I{ 3, 4 }, I{ 6, 7 } } } );

	EXPECT_TRUE( std::all_of( std::begin( targetBoxes ), std::end( targetBoxes ), [&splits]( const auto& b ) {
		return std::any_of( std::begin( splits ), std::end( splits ),
							[&b]( const auto& p ) { return p.mContainer == b; } );
	} ) );
}