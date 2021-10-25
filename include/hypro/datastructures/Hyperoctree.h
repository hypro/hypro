/*
 * Copyright (c) 2021.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Created by Stefan Schupp <stefan.schupp@tuwien.ac.at> on 24.09.21.
 */

#pragma once
#include "HyperoctreePredicates.h"

namespace hypro {

/**
 * Class to efficiently store data in a tree-like structure. The passed predicate is a functor which needs to implement a call-operator to determine, whether passed data fits the current node, does not fit the current node, or should be stored in a lower level.
 * @tparam Predicate
 * @tparam Data
 */
template <typename Number>
class Hyperoctree {
	using cellVector = std::vector<Box<Number>>;

  public:
	Hyperoctree( std::size_t splits, std::size_t maxDepth, const Box<Number>& container )
		: mSplits( splits )
		, mRemainingDepth( maxDepth )
		, mContainer( container )
		, mToBeCovered() {
		mToBeCovered.push_back( container );
	}

	void add( const Box<Number>& data ) {
		// if this box is already fully covered, do nothing.
		if ( mCovered ) {
			return;
		}
		// consider only the part that is contained in this box
		auto [containment, result] = mContainer.containmentReduce( data );
		// if the intersection of the data and this container is non-empty
		if ( containment != CONTAINMENT::NO ) {
			// the set is at least partially contained and we have already cut to the part that is also contained in this container, we can pass to the childen
			if ( mRemainingDepth == 0 ) {
				updateCoverage( result );
				mData.emplace_back( result );
				return;
			}
			// make sure child nodes exist
			updateChildren();
			// forward call to children
			std::for_each( std::begin( mChildren ), std::end( mChildren ), [&result]( const auto& child ) { child->add( result ); } );
		}
	}

  private:
	void updateCoverage( const Box<Number>& newBox ) {
		std::vector<Box<Number>> tmp;
		for ( const Box<Number>& box : mToBeCovered ) {
			auto remainder = box.setMinus2( newBox );
			tmp.insert( tmp.end(), std::begin( remainder ), std::end( remainder ) );
		}
		if ( tmp.empty() ) {
			mCovered = true;
			// the box is fully covered, no need to store child nodes or data
			mChildren.erase( std::begin( mChildren ), std::end( mChildren ) );
			mData.erase( std::begin( mData ), std::end( mData ) );
		}
		// update what remains to be covered
		std::swap( mToBeCovered, tmp );
	}

	void updateChildren() {
		if ( mChildren.empty() && mRemainingDepth != 0 ) {
			// create splits
			auto intervals = mContainer.intervals();
			auto dim = intervals.size();
			// split all intervals into mSplits many parts
			std::vector<decltype( intervals )> splitIntervals{ dim, decltype( intervals ){} };
			for ( std::size_t i = 0; i < dim; ++i ) {
				splitIntervals[i] = split_homogeneously_weak_bounds( intervals[i], mSplits );
			}

			// create all boxes by creating all combinations of intervals
			Combinator boxCombinator{ mSplits, dim };
			while ( !boxCombinator.end() ) {
				auto intervalIndices = boxCombinator();

				// assemble new box
				std::vector<carl::Interval<Number>> newIntervals;
				for ( std::size_t pos = 0; pos < dim; ++pos ) {
					newIntervals.push_back( splitIntervals[pos][intervalIndices[pos]] );
				}
				mChildren.emplace_back( std::make_unique<Hyperoctree<Number>>( mSplits, mRemainingDepth - 1, Box<Number>( newIntervals ) ) );
			}
		}
	}
	bool add_recursive( const Box<Number>& data, HyperOctreeOp parentDecision, Hyperoctree<Number>& parent );
	void insertData( const Box<Number>& obj ) { mData.push_back( obj ); }

  protected:
	std::size_t mSplits = 1;
	std::size_t mRemainingDepth = 0;  ///< indicates how may more splits can be made
	std::vector<std::unique_ptr<Hyperoctree<Number>>> mChildren;
	bool mCovered = false;
	Box<Number> mContainer;
	std::vector<Box<Number>> mToBeCovered;
	std::vector<Box<Number>> mData;	 ///< collects data suitable for this level
};

}  // namespace hypro

//#include "Hyperoctree.tpp"