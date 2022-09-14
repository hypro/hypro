#pragma once
#include "../../types.h"

namespace hypro {

template <typename Number>
class Transition;

template <typename Representation>
struct IndexedValuationSet {
	Representation valuationSet{};
	SegmentInd index{};
};

template <typename Representation>
struct EnabledSets {
	const Transition<rep_number<Representation>>* transition;
	std::vector<IndexedValuationSet<Representation>> valuationSets{};
};

template <typename Representation>
struct TimedValuationSet {
	Representation valuationSet{};
	carl::Interval<SegmentInd> time{};
};

template <typename Representation>
struct JumpSuccessor {
	const Transition<rep_number<Representation>>* transition;
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
