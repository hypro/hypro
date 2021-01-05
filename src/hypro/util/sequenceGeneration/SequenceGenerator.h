#pragma once
#include "generators.h"

namespace hypro {

// forward declaration for aliasses
template <typename Alg>
class PermutationSequenceGenerator;

// aliasses
using Permutator = PermutationSequenceGenerator<detail::NoReturningWithoutOrder>;
using Combinator = PermutationSequenceGenerator<detail::WithReturningNoOrder>;

/**
 * @brief Class which implements a generator for permutations based on different ways of chosing.
 * @detail The class upon calling the operator() the class generates the next tuple of size numberChoices, the elements of the tuple are taken from the domain [0, domainUpperBound-1].
 * @tparam IterationAlgorithm The algorithm-parameter is instanciated with a functor which implements different incrementation methods based on the type of choice (Order of elements can be used to distinguish tuples [ 0,1 is different from 1,0] and there may or may not be duplicate elements)
 */
template <typename IterationAlgorithm>
class PermutationSequenceGenerator {
  private:
	std::vector<std::size_t> mCurrent;	///< the current tuple
	std::size_t max;					///< all elements are less than max
	bool mEnd;							///< indicates the end of the sequence has been reached

  public:
	/**
     * @brief Construct a new Permutation Sequence Generator object
     * @param domainUpperBound All tuple elements are chosen from [0,domainUpperBound-1]
     * @param numberChoices Number of generated elements per tuple
     */
	PermutationSequenceGenerator( std::size_t domainUpperBound, std::size_t numberChoices )
		: mCurrent( IterationAlgorithm::initialize( numberChoices, domainUpperBound ) )
		, max( domainUpperBound )
		, mEnd( false ) {
	}

	/// calls the iteration and returns a (possibly new if the end has not been reached) tuple
	std::vector<std::size_t> operator()() {
		if ( mEnd ) {
			return mCurrent;
		}

		auto res = mCurrent;

		// perform increment
		auto [end, tuple] = IterationAlgorithm::increment( mCurrent, max );

		if ( end ) {
			mEnd = true;
		} else {
			// update after increment
			mCurrent = tuple;
		}
		return res;

		std::vector<std::size_t> tmp = mCurrent;

		// find pos to iterate
		std::size_t pos = 0;
		while ( pos < mCurrent.size() && mCurrent.at( pos ) == max - 1 ) {
			++pos;
		}

		// check whether last item has already been enumerated
		if ( pos == mCurrent.size() ) {
			mEnd = true;
			return tmp;
		}

		// actual increment
		mCurrent[pos] += 1;

		//
		while ( pos > 0 ) {
			--pos;
			mCurrent[pos] = 0;
		}

		return tmp;
	}

	/// returns true if the end of the sequence has been reached, false otherwise
	bool end() const {
		return mEnd;
	}

	/// resets the sequence generator
	void reset() {
		mCurrent = IterationAlgorithm::initialize( mCurrent.size(), this->max );
		mEnd = false;
	}
};
}  // namespace hypro
