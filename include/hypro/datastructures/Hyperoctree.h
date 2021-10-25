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

namespace hypro {

/**
 * Class to efficiently store data in a tree-like structure.
 * @tparam Number
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
		TRACE( "hypro.datastructures", "Add box " << data << " in " << *this );
		// if this box is already fully covered, do nothing.
		if ( mCovered ) {
			TRACE( "hypro.datastructures", "This container is already covered." );
			return;
		}
		// consider only the part that is contained in this box
		std::pair<CONTAINMENT, Box<Number>> result = mContainer.containmentReduce( data );
		// if the intersection of the data and this container is non-empty
		if ( result.first != CONTAINMENT::NO ) {
			TRACE( "hypro.datastructures", "At least partial intersection, resulting box: " << result.second );
			// the set is at least partially contained and we have already cut to the part that is also contained in this container, we can pass to the childen
			if ( mRemainingDepth == 0 ) {
				TRACE( "hypro.datastructures", "Reached leaf." );
				mData.push_back( data );
				updateCoverage( result.second );
				return;
			}
			// make sure child nodes exist
			updateChildren();
			// forward call to children
			TRACE( "hypro.datastructures", "Forward call to children" );
			std::for_each( std::begin( mChildren ), std::end( mChildren ), [&result]( const auto& child ) { child->add( result.second ); } );
			propagateCoverage();
		}
	}

	bool contains( const Point<Number>& point ) const {
		if ( !mContainer.contains( point ) ) {
			TRACE( "hypro.datastructures", "Point " << point << " is not contained in " << mContainer );
			return false;
		}
		if ( mCovered ) {
			TRACE( "hypro.datastructures", "Fully covered: " << *this );
			return true;
		} else {
			if ( mChildren.empty() ) {
				TRACE( "hypro.datastructures", "Check whether point " << point << " is contained in data\n" );
				for ( const auto& b : mData ) {
					TRACE( "hypro.datastructures", b );
				}
				auto tmp = std::any_of( std::begin( mData ), std::end( mData ), [&point]( const auto& box ) { return box.contains( point ); } );
				TRACE( "hypro.datastructures", "Contained in data of " << *this << ": " << tmp );
				return tmp;
			} else {
				TRACE( "hypro.datastructures", "Forward to child-nodes" );
				return std::any_of( std::begin( mChildren ), std::end( mChildren ), [&point]( const auto& child ) { return child->contains( point ); } );
			}
		}
	}

	bool isCovered() const {
		return mCovered;
	}

	const Box<Number>& getContainer() const { return mContainer; }
	const std::vector<std::unique_ptr<Hyperoctree<Number>>>& getChildren() const { return mChildren; }

  private:
	void propagateCoverage() {
		std::for_each( std::begin( mChildren ), std::end( mChildren ), []( auto& child ) { child->propagateCoverage(); } );
		// check intermediate nodes, leaf nodes update their coverage upon adding of content
		if ( mRemainingDepth != 0 && !mChildren.empty() && std::all_of( std::begin( mChildren ), std::end( mChildren ), []( const auto& child ) { return child->isCovered(); } ) ) {
			mCovered = true;
			TRACE( "hypro.datastructures", "All children of " << *this << " are covered" );
		}
	}

	void updateCoverage( const Box<Number>& newBox ) {
		TRACE( "hypro.datastructures", "Update coverage on " << newBox );
		std::vector<Box<Number>> tmp;
		for ( const Box<Number>& box : mToBeCovered ) {
			auto remainder = box.setMinus2( newBox );
			tmp.insert( tmp.end(), std::begin( remainder ), std::end( remainder ) );
		}
		if ( tmp.empty() ) {
			TRACE( "hypro.datastructures", "Everything covered, set covered and return" );
			mCovered = true;
			// the box is fully covered, no need to store child nodes or data
			mChildren.erase( std::begin( mChildren ), std::end( mChildren ) );
			mData.erase( std::begin( mData ), std::end( mData ) );
		}
		TRACE( "hypro.datastructures", "Not yet fully covered, remains:" );
		for ( const auto& s : tmp ) {
			TRACE( "hypro.datastructures", s );
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

template <typename Number>
std::ostream& operator<<( std::ostream& out, const Hyperoctree<Number>& in ) {
	out << "Container: " << in.getContainer() << "\ncovered: " << in.isCovered();
	return out;
}

}  // namespace hypro

//#include "Hyperoctree.tpp"