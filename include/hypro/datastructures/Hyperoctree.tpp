#pragma once
#include "Hyperoctree.h"

namespace hypro {

template <template <typename> class Predicate, typename Data>
void Hyperoctree<Predicate, Data>::add( const Data& data ) {
	// query the predicate
	HyperOctreeOp predicateResult = mDecider( data );

	// if there are no layers or if data does not even satisfy the root predicate, simply add
	if ( mRemainingDepth == 0 || predicateResult == HyperOctreeOp::SKIP ) {
		mData.emplace_back( std::forward( data ) );
	}

	// recommendation: consider a child node
	if ( predicateResult == HyperOctreeOp::DESCEND ) {
		assert( mRemainingDepth != 0 );
		// if next layer is not yet initialized, initialize
		if ( mChildren.empty() ) {
			std::vector<Predicate<Data>> childPredicates = mDecider.split();
			for ( const auto& p : childPredicates ) {
				mChildren.emplace_back( std::make_unique<Hyperoctree<Predicate, Data>>( p ) );
			}
		}

		for ( std::unique_ptr<Hyperoctree<Predicate, Data>>& child : mChildren ) {
			bool res = child->add_recursive( std::forward( data ), predicateResult, *this );
			if ( res ) {
				return;
			}
		}
		assert( false && "This should not be reachable." );
	}
}
template <template <typename> class Predicate, typename Data>
bool Hyperoctree<Predicate, Data>::add_recursive( const Data& data, HyperOctreeOp parentDecision, Hyperoctree<Predicate, Data>& parent ) {
	if ( mRemainingDepth == 0 ) {
		mData.emplace_back( std::forward( data ) );
		return true;
	}
	// query predicate
	HyperOctreeOp predicateResult = mDecider( data );

	// recommendation: add to parent
	if ( predicateResult == HyperOctreeOp::ADD ) {
		parent.insertData( data );
		return true;
	}

	// recommendation: descend into one child
	if ( predicateResult == HyperOctreeOp::DESCEND ) {
		assert( mRemainingDepth != 0 );
		// if next layer is not yet initialized, initialize
		if ( mChildren.empty() ) {
			std::vector<Predicate<Data>> childPredicates = mDecider.split();
			for ( const auto& p : childPredicates ) {
				mChildren.emplace_back( std::make_unique<Hyperoctree<Predicate, Data>>( p ) );
			}
		}

		for ( std::unique_ptr<Hyperoctree<Predicate, Data>>& child : mChildren ) {
			bool res = child->add_recursive( std::forward( data ), predicateResult, *this );
			if ( res ) {
				return true;
			}
		}
		assert( false && "This should not be reachable." );
	}

	assert( predicateResult == HyperOctreeOp::SKIP );
	return false;
}

}  // namespace hypro