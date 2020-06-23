#pragma once
#include "../../datastructures/HybridAutomaton/Condition.h"
#include "../../util/Range.h"
#include "../../util/plotting/PlotData.h"

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
	Flowpipe( /* args */ );
	~Flowpipe();

	void setStates( const States& states ) { mStates = states; }
	void setStates( States&& states ) { mStates = std::move( states ); }
	void addState( const State& state ) { mStates.emplace_back( state ); }
	void addState( State&& state ) { mStates.emplace_back( state ); }

	template <typename Number>
	Range<States> selectSatisfyingStates( const Condition<Number>& cond ) {
		return selectFirstConsecutiveRange( mStates, [&]( const State& in ) -> bool { auto tmp = in.satisfiesHalfspaces(cond.getMatrix(), cond.getVector()).first; return tmp != CONTAINMENT::NO && tmp != CONTAINMENT::BOT; } ); 
	}

	std::vector<PlotData<State>> getPlotData( std::size_t refinementLevel = 0, std::size_t threadId = 0 ) const;

	typename States::iterator begin() { return mStates.begin(); }
	typename States::iterator end() { return mStates.end(); }
	typename States::const_iterator begin() const { return mStates.begin(); }
	typename States::const_iterator end() const { return mStates.end(); }

	std::size_t size() const { return mStates.size(); }
};

}  // namespace hypro

#include "Flowpipe.tpp"
