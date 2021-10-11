/*
 * Copyright (c) 2021.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Created by Stefan Schupp <stefan.schupp@tuwien.ac.at> on 24.09.21.
 */

#pragma once

namespace hypro {

enum class HyperOctreeOp { ADD,
						   DESCEND,
						   SKIP };

/**
 * Class to efficiently store data in a tree-like structure. The passed predicate is a functor which needs to implement a call-operator to determine, whether passed data fits the current node, does not fit the current node, or should be stored in a lower level.
 * @tparam Predicate
 * @tparam Data
 */
template <template <typename> class Predicate, typename Data>
class Hyperoctree {
	using childVector = std::vector<std::unique_ptr<Hyperoctree<Predicate, Data>>>;

  public:
	Hyperoctree( const Predicate<Data>& p )
		: mDecider( p ) {}

	bool add( Data&& data );

	std::size_t getRemainingDepth() const { return mRemainingDepth; }
	const childVector& getChildren() const { return mChildren; }
	const std::vector<Data>& getData() const { return mData; }

  protected:
	std::size_t mRemainingDepth = 0;  ///< indicates how may more splits can be made
	Predicate<Data> mDecider;		  ///< functor
	childVector mChildren;			  ///< collects child-hyperoctrees
	std::vector<Data> mData;		  ///< collects data suitable for this level
};

}  // namespace hypro

#include "Hyperoctree.tpp"