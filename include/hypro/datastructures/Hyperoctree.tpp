#pragma once
#include "Hyperoctree.h"

namespace hypro {

template <template <typename> class Predicate, typename Data>
bool Hyperoctree<Predicate, Data>::add( Data&& data ) {
	HyperOctreeOp predicateResult = mDecider( std::forward( data ) );
	if ( mRemainingDepth == 0 || predicateResult == HyperOctreeOp::ADD ) {
		mData.emplace_back( std::forward( data ) );
		return true;
	}

	if ( predicateResult == HyperOctreeOp::DESCEND ) {
		if ( mChildren.empty() ) {
			assert( mRemainingDepth != 0 );
			std::vector<Predicate<Data>> childPredicates = mDecider.split();
			for ( const auto& p : childPredicates ) {
				mChildren.emplace_back( std::make_unique<Hyperoctree<Predicate, Data>>( p ) );
			}
		}

		for ( const std::unique_ptr<Hyperoctree<Predicate, Data>>& child : mChildren ) {
			bool res = child->add( std::forward( data ) );
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