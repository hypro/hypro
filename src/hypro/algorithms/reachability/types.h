#pragma once
#include "../../types.h"

namespace hypro {

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

}  // namespace hypro
