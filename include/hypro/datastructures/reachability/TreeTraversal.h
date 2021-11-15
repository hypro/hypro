#pragma once

#include <boost/range/iterator_range.hpp>

namespace hypro {

// TODO ConstTreeIterator

template <class NodeType>
class TreeIterator {
	std::vector<NodeType*> mStack{};

  public:
	TreeIterator() = default;

	TreeIterator( NodeType& node )
		: mStack( { &node } ) {}

	TreeIterator( NodeType* node )
		: mStack( { node } ) {}

	TreeIterator( std::vector<NodeType*>& nodes )
		: mStack( nodes ) {}

	using difference_type = std::ptrdiff_t;
	using value_type = NodeType;
	using pointer = value_type*;
	using reference = value_type&;
	using iterator_category = std::input_iterator_tag;

	reference operator*() {
		return *mStack.back();
	}

	pointer operator->() {
		return mStack.back();
	}

	TreeIterator& operator++() {
		auto* node = mStack.back();
		mStack.pop_back();
		mStack.insert( mStack.end(), node->getChildren().begin(), node->getChildren().end() );
		return *this;
	}

	TreeIterator operator++( int ) {
		TreeIterator old = *this;
		++( *this );
		return old;
	}

	bool operator==( TreeIterator const& other ) const {
		if ( mStack.empty() || other.mStack.empty() ) {
			return mStack.empty() && other.mStack.empty();
		} else {
			return mStack.back() == other.mStack.back();
		}
	}
	bool operator!=( TreeIterator const& other ) const {
		return !( *this == other );
	}
};

template <class NodeType>
boost::iterator_range<TreeIterator<NodeType>> preorder( NodeType& node ) {
	return { TreeIterator{ node }, TreeIterator<NodeType>{} };
}

template <class NodeType>
boost::iterator_range<TreeIterator<NodeType>> preorder( std::vector<NodeType>& nodes ) {
	std::vector<NodeType*> ptrs{};
	std::transform( nodes.begin(), nodes.end(), std::back_inserter( ptrs ), []( auto& node ) { return &node; } );
	return { TreeIterator<NodeType>{ ptrs }, TreeIterator<NodeType>{} };
}

template <class NodeType>
boost::iterator_range<TreeIterator<NodeType>> preorder( std::vector<NodeType*>& nodePtrs ) {
	return { TreeIterator<NodeType>{ nodePtrs }, TreeIterator<NodeType>{} };
}

template <class NodeType>
class TreeIterator_const {
	std::vector<const NodeType*> mStack{};

  public:
	TreeIterator_const() = default;

	TreeIterator_const( const NodeType& node )
		: mStack( { &node } ) {}

	TreeIterator_const( const NodeType* node )
		: mStack( { node } ) {}

	TreeIterator_const( std::vector<const NodeType*>& nodes )
		: mStack( nodes ) {}

	using difference_type = std::ptrdiff_t;
	using value_type = NodeType;
	using pointer = const value_type*;
	using reference = const value_type&;
	using iterator_category = std::input_iterator_tag;

	reference operator*() {
		return *mStack.back();
	}

	pointer operator->() {
		return mStack.back();
	}

	TreeIterator_const& operator++() {
		auto* node = mStack.back();
		mStack.pop_back();
		for ( const auto& ch : node->getChildren() ) {
			mStack.push_back( &ch );
		}
		// mStack.insert( mStack.end(), node->getChildren().begin(), node->getChildren().end() );
		return *this;
	}

	TreeIterator_const operator++( int ) {
		TreeIterator_const old = *this;
		++( *this );
		return old;
	}

	bool operator==( TreeIterator_const const& other ) const {
		if ( mStack.empty() || other.mStack.empty() ) {
			return mStack.empty() && other.mStack.empty();
		} else {
			return mStack.back() == other.mStack.back();
		}
	}
	bool operator!=( TreeIterator_const const& other ) const {
		return !( *this == other );
	}
};

template <class NodeType>
boost::iterator_range<TreeIterator_const<NodeType>> preorder( const NodeType& node ) {
	return { TreeIterator_const{ node }, TreeIterator_const<NodeType>{} };
}

template <class NodeType>
boost::iterator_range<TreeIterator_const<NodeType>> preorder( const std::vector<NodeType>& nodes ) {
	std::vector<const NodeType*> ptrs{};
	std::transform( nodes.begin(), nodes.end(), std::back_inserter( ptrs ), []( auto& node ) { return &node; } );
	return { TreeIterator_const<NodeType>{ ptrs }, TreeIterator_const<NodeType>{} };
}

template <class NodeType>
boost::iterator_range<TreeIterator_const<NodeType>> preorder( std::vector<const NodeType*>& nodePtrs ) {
	return { TreeIterator_const<NodeType>{ nodePtrs }, TreeIterator_const<NodeType>{} };
}

}  // namespace hypro