/*
 * Copyright (c) 2022.
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

#include "../representations/GeometricObjectBase.h"
#include "../util/serialization/interval_serialization.h"

#include <cereal/types/common.hpp>
#include <cereal/types/vector.hpp>

namespace hypro {

template <typename N>
class Hyperoctree;

template <class Archive, typename N>
void serialize( Archive& archive, Hyperoctree<N>& tree );

/**
 * Class to efficiently store data in a tree-like structure.
 * @tparam Number
 */
template <typename Number>
class Hyperoctree {
	using cellVector = std::vector<Box<Number>>;
	template <class Archive>
	friend void serialize( Archive& archive, Hyperoctree<Number>& tree );

  public:
	/*
	 * Default constructor. Should not be used, but is required for serialization. Instead use constructor with splits, depth and container parameter.
	 */
	Hyperoctree() {}
	/// Constructor, is to be used in favor of the default constructor.
	Hyperoctree( std::size_t splits, std::size_t maxDepth, const Box<Number>& container )
		: mSplits( splits )
		, mRemainingDepth( maxDepth )
		, mContainer( container )
		, mToBeCovered() {
		mToBeCovered.push_back( container );
	}

	/**
	 * @brief Setter for the splits-value.
	 * @details Avoid using this function, as it is very expensive when used on a non-empty hyperoctree.
	 * @param splits New number of splits.
	 */
	void setSplits( std::size_t splits ) {
		// TODO what needs to be done: recursively collect everything, temporarily keep it, update the splits-value and reinsert everything.
		throw std::logic_error( "This function is not yet implemented." );
	}
	/**
	 * @brief Setter for the depth-value
	 * @details Avoid using this, as it is very expensive for non-empty hyperoctrees. Resets the remaining depth - potentially allows to mess up the data-structure to get imbalanced trees and such.
	 * @param depth New depth value.
	 */
	void setDepth( std::size_t depth ) {
		// TODO what needs to be done: recursively collect everything, temporarily keep it, update the depth-value and reinsert everything.
		throw std::logic_error( "This function is not yet implemented." );
	}
	/**
	 * @brief Setter for the container boundaries
	 * @details Avoid this, this is very expensive and even allows to create inconsistent state for non-empty hyperoctrees.
	 * @param box
	 */
	void setContainer( const Box<Number> box ) {
		// TODO what needs to be done: recursively collect everything, temporarily keep it, update the container and reinsert everything.
		throw std::logic_error( "This function is not yet implemented." );
	}
	/**
	 * @brief Add a box to the tree
	 * @details Recursively adds a box to the tree, which is potentially split during the process.
	 * @param data The new box
	 */
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
			std::for_each( std::begin( mChildren ), std::end( mChildren ), [&result]( auto& child ) { child.add_recursive( result.second ); } );
			propagateCoverage();
		}
	}
	/**
	 * @brief Containment test for a single point
	 * @param point The point
	 * @return True, if the point is contained in the set represented by the hyperoctree.
	 */
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
				return std::any_of( std::begin( mChildren ), std::end( mChildren ), [&point]( const auto& child ) { return child.contains( point ); } );
			}
		}
	}
	/**
	 * @brief Containment test for a box
	 * @param set The box
	 * @return True, if the box is fully contained in the set represented by the hyperoctree.
	 */
	bool contains( const Box<Number>& set ) const {
		if ( set.empty() ) {
			return true;
		}
		if ( !mContainer.contains( set ) ) {
			TRACE( "hypro.datastructures", "Set " << set << " is not contained in " << mContainer );
			return false;
		}
		if ( mCovered ) {
			TRACE( "hypro.datastructures", "Fully covered: " << *this );
			return true;
		} else {
			if ( mChildren.empty() ) {
				TRACE( "hypro.datastructures", "Check whether box " << set << " is contained in data\n" );
				for ( const auto& b : mData ) {
					TRACE( "hypro.datastructures", b );
				}
				std::vector<Box<Number>> remainder;
				remainder.emplace_back( set );
				auto dataIt = mData.begin();
				for ( const auto& dataItem : mData ) {
					std::vector<Box<Number>> newRemainder;
					for ( const auto& box : remainder ) {
						auto tmp = box.setMinus2( dataItem );
						newRemainder.insert( newRemainder.end(), tmp.begin(), tmp.end() );
					}
					remainder = newRemainder;
					if ( remainder.empty() ) {
						break;
					}
				}
				return remainder.empty();
			} else {
				TRACE( "hypro.datastructures", "Forward to child-nodes" );
				return std::all_of( std::begin( mChildren ), std::end( mChildren ), [&set]( const auto& child ) {
					return child.contains( set.intersect( child.mContainer ) );
				} );
			}
		}
		return true;
	}
	/**
	 * @brief Getter for the coverage value
	 * @return True, if the added sets fully cover the maximal set representable by this hyperoctree.
	 */
	bool isCovered() const {
		assert( !mCovered || mData.empty() );
		return mCovered;
	}
	/// Getter for the set-container, i.e., the maximal representable set of the hyperoctree.
	const Box<Number>& getContainer() const { return mContainer; }
	/// Getter for child-trees. The union of all child-trees covers the set represented by the container.
	const std::vector<Hyperoctree<Number>>& getChildren() const {
		assert( mChildren.empty() || mData.empty() );
		return mChildren;
	}
	/// Getter for the stored sets. Should be non-empty only for leaf nodes.
	const std::vector<Box<Number>>& getData() const { return mData; }
	/// Equality-comparison operator.
	bool operator==( const Hyperoctree<Number>& other ) const {
		if ( mSplits != other.mSplits || mRemainingDepth != other.mRemainingDepth || mCovered != other.mCovered || mContainer != other.mContainer ) {
			return false;
		}
		if ( !std::equal( std::begin( mData ), std::end( mData ), std::begin( other.mData ) ) ) {
			return false;
		}
		if ( !std::equal( std::begin( mToBeCovered ), std::end( mToBeCovered ), std::begin( other.mToBeCovered ) ) ) {
			return false;
		}
		return std::equal( std::begin( mChildren ), std::end( mChildren ), std::begin( other.mChildren ) );
	}

  private:
	/// Recursively propagage coverage value up in the tree. Required after adding new sets: when all children are fully covered, the parent is also marked as fully covered.
	void propagateCoverage() {
		std::for_each( std::begin( mChildren ), std::end( mChildren ), []( auto& child ) { child.propagateCoverage(); } );
		// check intermediate nodes, leaf nodes update their coverage upon adding of content
		if ( mRemainingDepth != 0 && !mChildren.empty() && std::all_of( std::begin( mChildren ), std::end( mChildren ), []( const auto& child ) { return child.isCovered(); } ) ) {
			mCovered = true;
			TRACE( "hypro.datastructures", "All children of " << *this << " are covered" );
		}
	}
	/// Updates the storage of sets which still need to be covered in the current tree before achieving full coverage.
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
	/// initialization of child trees
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
				mChildren.emplace_back( Hyperoctree<Number>( mSplits, mRemainingDepth - 1, Box<Number>( newIntervals ) ) );
			}
		}
	}
	/// Recursive function which is called during adding of sets to the hyperoctree.
	void add_recursive( const Box<Number>& data ) {
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
			std::for_each( std::begin( mChildren ), std::end( mChildren ), [&result]( auto& child ) { child.add_recursive( result.second ); } );
		}
	}

  protected:
	std::size_t mSplits = 1;					 ///< number of splits done per dimension
	std::size_t mRemainingDepth = 0;			 ///< indicates how may more splits can be made
	std::vector<Hyperoctree<Number>> mChildren;	 ///< child trees, if the remaining depth is larger than zero
	bool mCovered = false;						 ///< flag - if true, the whole container is covered by sets that have been added.
	Box<Number> mContainer;						 ///< container representing the maximal set that can be represented
	std::vector<Box<Number>> mToBeCovered;		 ///< cache which stores what area needs to be covered in order to fully cover the container
	std::vector<Box<Number>> mData;				 ///< collects data suitable for this level
};
/// outstream-operator
template <typename Number>
std::ostream& operator<<( std::ostream& out, const Hyperoctree<Number>& in ) {
	out << "Container: " << in.getContainer() << "\ncovered: " << in.isCovered();
	return out;
}
/// serialization-function
template <class Archive>
void serialize( Archive& archive,
				Hyperoctree<double>& tree ) {
	archive( tree.mSplits, tree.mRemainingDepth, tree.mCovered, tree.mContainer, tree.mToBeCovered, tree.mData, tree.mChildren );
}

}  // namespace hypro

// Specialization for LoadAndConstruct for hyperoctrees
namespace cereal {
template <>
struct LoadAndConstruct<hypro::Hyperoctree<double>> {
	// load_and_construct will be passed the archive that you will be loading
	// from as well as a special construct object that can be used to invoke
	// the constructor for your class.
	//
	// More advanced functionality is available using construct, such as accessing
	// class members, which is detailed in the doxygen docs.
	//
	// As with the internal load_and_construct, versioning can be supported by adding an
	// additional final parameter: const std::uint32_t version
	template <class Archive>
	static void load_and_construct( Archive& ar, cereal::construct<hypro::Hyperoctree<double>>& construct ) {
		std::size_t splits, depth;
		bool covered;
		hypro::Box<double> container;
		std::vector<hypro::Box<double>> toBeCovered, data;
		std::vector<hypro::Hyperoctree<double>> children;
		ar( splits, depth, covered, container, toBeCovered, data, children );
		construct( splits, depth, container, covered, toBeCovered, data, children );
	}
};
}  // namespace cereal
