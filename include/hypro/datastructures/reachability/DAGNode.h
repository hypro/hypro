/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * File:   DAGNode.h
 * Author: Dustin Hütter <dustin.huetter@rwth-aachen.de>
 *
 * Created on April 15, 2016, 10:57 AM
 */
#pragma once
#include <vector>

namespace hypro {

template <typename Data>
class DAGNode {
  private:
	using NodeListWeak_t = std::vector<std::weak_ptr<Data>>;

  public:
	using Node_t = std::shared_ptr<Data>;
	using NodeList_t = std::vector<Node_t>;

  protected:
	NodeList_t mChildren;	  ///< children list
	NodeListWeak_t mParents;  ///< parents list, empty if root.

  public:
	DAGNode<Data>()
		: mChildren()
		, mParents() {}

	DAGNode<Data>( const typename DAGNode<Data>::NodeList_t& _children, Data* _parent )
		: mChildren( _children )
		, mParents() {
		mParents.push_back( _parent );
	}

	virtual ~DAGNode() {}

	std::size_t getSubtreeSize() const {
		if ( getChildren().empty() ) return 0;

		std::size_t size = 0;
		for ( const auto child : getChildren() ) {
			size += child->getSubtreeSize();
		}
		return getChildren().size() + size;
	}

	double getAvgSubtreeBranching() const {
		if ( getChildren().empty() ) return 0;
		double res = 0.0;
		auto zeroes = 0;
		for ( const auto child : getChildren() ) {
			auto tmp = child->getAvgSubtreeBranching();
			if ( tmp == 0 ) {
				zeroes += 1;
			}
			res += tmp;
		}
		res += getChildren().size();
		res /= getChildren().size() + 1 - zeroes;
		return res;
	}

	const typename DAGNode<Data>::NodeList_t& getChildren() const {
		return mChildren;
	}

	typename DAGNode<Data>::NodeList_t getParents() const {
		NodeList_t res;
		for ( auto& parent : mParents ) {
			res.emplace_back( parent.lock() );
		}
		return res;
	}

	void addChild( Node_t child ) {
		mChildren.push_back( child );
	}

	void addParent( Node_t parent ) {
		mParents.push_back( parent );
	}

	friend bool operator==( const DAGNode<Data>& lhs, const DAGNode<Data>& rhs ) {
		return ( lhs.mDepth == rhs.mDepth && lhs.mParent == rhs.mParent && lhs.mChildren == rhs.mChildren );
	}
};

}  // namespace hypro
