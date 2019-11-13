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
  public:
	using Node_t = Data*;
	using const_Node_t = const Data*;
	using NodeList_t = std::vector<Data*>;

  protected:
	NodeList_t mChildren;  /// children list
	NodeList_t mParents;   /// parents list, empty if root.

  public:
	DAGNode<Data>()
		: mChildren()
		, mParents() {}

	DAGNode<Data>( const typename DAGNode<Data>::NodeList_t& _children, Data* _parent )
		: mChildren( _children )
		, mParents() {
		mParents.push_back( _parent );
	}

	~DAGNode() {
		for ( auto child : mChildren ) {
			delete child;
		}
	}

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

	const typename DAGNode<Data>::NodeList_t& getParents() const {
		return mParents;
	}

	void addChild( Data* child ) {
		mChildren.push_back( child );
	}

	void addParent( Data* parent ) {
		mParents.push_back( parent );
	}

	friend bool operator==( const DAGNode<Data>& lhs, const DAGNode<Data>& rhs ) {
		return ( lhs.mDepth == rhs.mDepth && lhs.mParent == rhs.mParent && lhs.mChildren == rhs.mChildren );
	}
};

}  // namespace hypro
