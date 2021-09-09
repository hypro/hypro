#include "test/defines.h"
#include "gtest/gtest.h"
#include <hypro/datastructures/reachability/TreeNodev2.h>
#include <hypro/datastructures/reachability/TreeTraversal.h>
#include <hypro/datastructures/reachability/TreeUtil.h>

using namespace hypro;

struct DataNode : public TreeNode<DataNode> {
	int data;

	explicit DataNode( int i ) : data( i ) {}

	DataNode& addChild( int d ) { return TreeNode<DataNode>::addChild( d ); }
};

TEST( TreeTest, Constructor ) {
	DataNode root{ 0 };
	root.addChild( 1 );
	root.addChild( 2 );
	auto& c3 = root.addChild( 3 );
	c3.addChild( 4 );

	SUCCEED();
}

TEST( TreeTest, Traversal ) {
	DataNode root{ 0 };
	root.addChild( 1 );
	root.addChild( 2 );
	auto& c3 = root.addChild( 3 );
	c3.addChild( 4 );

	TreeIterator<DataNode> begin{ root };
	TreeIterator<DataNode> end{};
	while ( begin != end ) {
		std::cout << "Content: " << begin->data << std::endl;
		++begin;
	}
	SUCCEED();
}

TEST( TreeTest, CountNodes ) {
	DataNode root{ 0 };
	root.addChild( 1 );
	root.addChild( 2 );
	auto& c3 = root.addChild( 3 );
	c3.addChild( 4 );

	EXPECT_EQ( std::size_t( 5 ), getNumberNodes( root ) );

	SUCCEED();
}
