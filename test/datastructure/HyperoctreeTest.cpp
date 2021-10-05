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