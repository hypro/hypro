/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "test/defines.h"

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
	using Node = std::shared_ptr<dagtest::DataNode>;

	Node root = std::make_shared<dagtest::DataNode>();
	root->addParent( nullptr );
	root->content = 1;

	Node child = std::make_shared<dagtest::DataNode>();
	child->addParent( root );
	root->addChild( child );
	child->content = 2;

	Node child2 = std::make_shared<dagtest::DataNode>();
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
