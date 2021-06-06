#pragma once
#include "../../datastructures/HybridAutomaton/Condition.h"
#include "../../util/Range.h"

/*
    Requirements:
 */

namespace hypro {

/**
 * @brief Container for a flowpipe, i.e. an ordered sequence of state sets (flowpipe segments).
 *
 * @tparam State Used state type.
 */
template <typename Representation>
class Flowpipe {
  private:
	std::vector<Representation> mStates;

  public:
	Flowpipe( /* args */ ){};
	~Flowpipe(){};

	void setStates( const std::vector<Representation>& states ) { mStates = states; }
	void setStates( std::vector<Representation>&& states ) { mStates = std::move( states ); }
	void addState( const Representation& state ) { mStates.emplace_back( state ); }
	void addState( Representation&& state ) { mStates.emplace_back( state ); }

	template <typename Number>
	Range<std::vector<Representation>> selectSatisfyingStates( const Condition<Number>& cond ) {
		return selectFirstConsecutiveRange( mStates, [&]( const Representation& in ) -> bool { auto tmp = in.satisfiesHalfspaces(cond.getMatrix(), cond.getVector()).first; return tmp != CONTAINMENT::NO && tmp != CONTAINMENT::BOT; } );
	}

	void clear() { mStates.clear(); }

	typename std::vector<Representation>::iterator begin() { return mStates.begin(); }
	typename std::vector<Representation>::iterator end() { return mStates.end(); }
	typename std::vector<Representation>::const_iterator begin() const { return mStates.begin(); }
	typename std::vector<Representation>::const_iterator end() const { return mStates.end(); }

	std::size_t size() const { return mStates.size(); }
};

}  // namespace hypro
