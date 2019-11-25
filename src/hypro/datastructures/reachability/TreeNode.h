/*
 * File:   TreeNode.h
 * Author: Dustin Hütter <dustin.huetter@rwth-aachen.de>
 *
 * Created on April 15, 2016, 10:57 AM
 */
#pragma once
#include <vector>

namespace hypro {

template <typename Data>
class TreeNode {
  protected:
	unsigned mDepth;			   /// depth cache
	std::vector<Data*> mChildren;  /// children list
	Data* mParent;				   /// pointer to parent node, nullptr if root.

  public:
	using Node_t = Data*;
	using const_Node_t = const Data*;
	using NodeList_t = std::vector<Data*>;

	TreeNode<Data>()
		: mDepth( 0 )
		, mChildren()
		, mParent( nullptr ) {}

	TreeNode<Data>( unsigned _depth, const std::vector<Data*>& _children, Data* _parent )
		: mDepth( _depth )
		, mChildren( _children )
		, mParent( _parent ) {
#ifndef NDEBUG
		if ( mDepth == 0 ) {
			assert( mParent == nullptr );
		} else {
			unsigned tmpDepth = 1;
			Data* parent = this->getParent();
			while ( parent->getParent() != nullptr ) {
				++tmpDepth;
				parent = parent->getParent();
			}
			assert( tmpDepth == mDepth );
		}
#endif
	}

	~TreeNode() {
		for ( auto child : mChildren ) {
			delete child;
		}
	}

	unsigned getDepth() const {
		if ( this->getParent() == nullptr ) {
			return 0;
		}
#ifndef NDEBUG
		unsigned tmpDepth = 1;
		Data* parent = this->getParent();
		while ( parent->getParent() != nullptr ) {
			++tmpDepth;
			parent = parent->getParent();
		}
		assert( tmpDepth == mDepth );
#endif
		return mDepth;
	}

	std::size_t getSubtreeDepth() const {
		if ( getChildren().empty() ) return 0;

		std::size_t maxDepth = 0;
		for ( const auto child : getChildren() ) {
			std::size_t tmp = child->getSubtreeDepth();
			maxDepth = tmp > maxDepth ? tmp : maxDepth;
		}
		return maxDepth + 1;
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

	const std::vector<Data*>& getChildren() const {
		return mChildren;
	}

	Data* getParent() const {
		return mParent;
	}

	void setDepth( unsigned _depth ) {
		mDepth = _depth;
#ifndef NDEBUG
		if ( mDepth == 0 ) {
			assert( mParent == nullptr );
		} else {
			unsigned tmpDepth = 1;
			Data* parent = this->getParent();
			while ( parent->getParent() != nullptr ) {
				++tmpDepth;
				parent = parent->getParent();
			}
			assert( tmpDepth == mDepth );
		}
#endif
	}

	void addChild( Data* child ) {
		assert( *child->getParent() == *this );
		mChildren.push_back( child );
	}

	void setParent( Data* parent ) {
		mParent = parent;
		// update depth
		mDepth = mParent->getDepth() + 1;
	}

	friend bool operator==( const TreeNode<Data>& lhs, const TreeNode<Data>& rhs ) {
		return ( lhs.mDepth == rhs.mDepth && lhs.mParent == rhs.mParent && lhs.mChildren == rhs.mChildren );
	}
};

}  // namespace hypro
