/**
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @since	2016-03-22
 * @version	2016-03-22
 */

#include "../config.h"

#pragma once

namespace hypro {

/**
 * @brief      Class for a permutator.
 * @details    This functor returns a sequence of d-tuples where the maximal element is totalsize-1. All permutations
 * 				are without considering order of the items and each item only occurs once.
 */
class Permutator {
  private:
	std::vector<std::size_t> mCurrent;
	std::size_t max;
	bool mEnd;

  public:
	Permutator( std::size_t totalSize, std::size_t d )
		: mCurrent( d, 0 )
		, max( totalSize )
		, mEnd( false ) {
		assert( d <= totalSize );
		if ( d <= totalSize ) {
			for ( std::size_t i = 0; i < d; ++i ) {
				mCurrent[i] = d - i - 1;
			}
		}
	}

	std::vector<std::size_t> operator()() {
		if ( mEnd ) {
			return mCurrent;
		}

		std::vector<std::size_t> tmp = mCurrent;

		// find pos to iterate
		std::size_t pos = 0;
		while ( pos < mCurrent.size() && mCurrent.at( pos ) == max - pos - 1 ) {
			++pos;
		}

		if ( pos == mCurrent.size() ) {
			mEnd = true;
			return tmp;
		}

		mCurrent[pos] += 1;
		while ( pos > 0 ) {
			--pos;
			mCurrent[pos] = mCurrent[pos + 1] + 1;
		}

		return tmp;
	}

	bool end() const {
		return mEnd;
	}
};

}  // namespace hypro
