/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once
#include "../../types.h"


namespace hypro {

template <typename Location>
class Transition;

template <typename Representation>
struct IndexedValuationSet {
	Representation valuationSet{};
	SegmentInd index{};
};

template <typename Representation, class Location>
struct EnabledSets {
	const Transition<Location>* transition;
	std::vector<IndexedValuationSet<Representation>> valuationSets{};
};

template <typename Representation>
struct TimedValuationSet {
	Representation valuationSet{};
	carl::Interval<SegmentInd> time{};
};

template <typename Representation, class Location>
struct JumpSuccessor {
	const Transition<Location>* transition;
	std::vector<TimedValuationSet<Representation>> valuationSets{};
};

template <typename Representation>
struct SubspaceJumpSuccessors {
	carl::Interval<SegmentInd> time{};
	std::map<std::size_t, Representation> subspaceSets{};
};

template <typename Number>
class TimeInformation {
	using TimeIntervals = std::vector<carl::Interval<Number>>;

  public:
	TimeInformation()
		: mTimeIntervals( TimeIntervals{} ) {}
	TimeInformation( std::size_t clockCount )
		: mTimeIntervals( TimeIntervals( clockCount, createEmptyInterval<Number>() ) ) {}
	TimeInformation( const TimeIntervals& timeIntervals )
		: mTimeIntervals( timeIntervals ) {}
	TimeInformation( std::size_t clockCount, Number lower, Number upper )
		: mTimeIntervals( TimeIntervals( clockCount, carl::Interval<Number>( lower, upper ) ) ) {}

	TimeIntervals getTimeIntervals() const {
		return mTimeIntervals;
	}
	carl::Interval<Number> getTimeInterval( std::size_t clockIndex ) const {
		assert( clockIndex < mTimeIntervals.size() && "clockIndex too large " );
		return mTimeIntervals[clockIndex];
	}
	void setTimeIntervals( const TimeIntervals& timeIntervals ) {
		mTimeIntervals = timeIntervals;
	}
	void setTimeInterval( std::size_t clockIndex, const carl::Interval<Number>& timeInterval ) {
		assert( clockIndex < mTimeIntervals.size() && "clockIndex too large" );
		mTimeIntervals[clockIndex] = timeInterval;
	}
	std::size_t clockCount() const {
		return mTimeIntervals.size();
	}
	bool empty() const {
		return std::any_of( mTimeIntervals.begin(), mTimeIntervals.end(), []( const auto& time ) {
			return isEmpty( time );
		} );
	}
	TimeInformation<Number> intersect( const TimeInformation<Number>& rhs ) const {
		assert( rhs.clockCount() == this->clockCount() && "cannot intersect timings with different clock count" );
		TimeIntervals intersectedTimes( rhs.clockCount() );
		for ( std::size_t clockIndex = 0; clockIndex < rhs.clockCount(); ++clockIndex ) {
			carl::Interval<Number> rhsInterval = rhs.getTimeInterval( clockIndex );
			carl::Interval<Number> lhsInterval = this->getTimeInterval( clockIndex );
			intersectedTimes[clockIndex] = carl::set_intersection( rhs.getTimeInterval( clockIndex ), this->getTimeInterval( clockIndex ) );
		}
		return TimeInformation<Number>( intersectedTimes );
	}

	TimeInformation<Number> unite( const TimeInformation<Number>& rhs ) const {
		assert( rhs.clockCount() == this->clockCount() && "cannot compute union of timings with different clock count" );
		TimeIntervals unionTimes( rhs.clockCount() );
		for ( std::size_t clockIndex = 0; clockIndex < rhs.clockCount(); ++clockIndex ) {
			carl::Interval<Number> rhsInterval = rhs.getTimeInterval( clockIndex );
			carl::Interval<Number> lhsInterval = this->getTimeInterval( clockIndex );
			unionTimes[clockIndex] = carl::Interval<Number>( std::min( rhsInterval.lower(), lhsInterval.lower() ), std::max( rhsInterval.upper(), lhsInterval.upper() ) );
		}
		return TimeInformation<Number>( unionTimes );
	}

  protected:
	TimeIntervals mTimeIntervals;
};

}  // namespace hypro
