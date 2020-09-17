#include "../defines.h"
#include "gtest/gtest.h"
#include <hypro/datastructures/reachability/DAGNode.h>

using namespace hypro;

namespace hypro {
namespace dagtest {
struct DataNode : public ::DAGNode<DataNode> {
	int content;
};
}  // namespace dagtest
}  // namespace hypro

TEST( DAGNodeTest, Construction ) {
	using Node = dagtest::DataNode;

	Node* root = new Node();
	root->addParent( nullptr );
	root->content = 1;

	Node* child = new Node();
	child->addParent( root );
	root->addChild( child );
	child->content = 2;

	Node* child2 = new Node();
	child2->content = 3;
	root->addChild( child2 );
	child2->addParent( root );
	child2->addParent( child );
	child->addChild( child2 );

	EXPECT_EQ( std::size_t( 2 ), child2->getParents().size() );
	EXPECT_TRUE( std::find( child2->getParents().begin(), child2->getParents().end(), root ) !=
				 child2->getParents().end() );
	EXPECT_TRUE( std::find( child2->getParents().begin(), child2->getParents().end(), child ) !=
				 child2->getParents().end() );
	EXPECT_TRUE( std::find( child->getParents().begin(), child->getParents().end(), root ) !=
				 child->getParents().end() );
	EXPECT_TRUE( std::find( root->getChildren().begin(), root->getChildren().end(), child ) !=
				 root->getChildren().end() );
	EXPECT_TRUE( std::find( root->getChildren().begin(), root->getChildren().end(), child2 ) !=
				 root->getChildren().end() );
}
