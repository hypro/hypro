#pragma once
#include "../../util/plotting/PlotData.h"
#include "../../util/Range.h"
#include "../../datastructures/HybridAutomaton/Condition.h"

/*
    Requirements:
 */

namespace hypro {


/**
 * @brief Container for a flowpipe, i.e. an ordered sequence of state sets (flowpipe segments).
 *
 * @tparam State Used state type.
 */
template<typename State>
class Flowpipe
{
private:
    std::vector<State> mStates;
public:
    Flowpipe(/* args */);
    ~Flowpipe();

    void setStates(const std::vector<State>& states) { mStates = states; }
    void setStates(std::vector<State>&& states) { mStates = std::move(states); }
    void addState(const State& state) { mStates.emplace_back(state); }
    void addState(State&& state) { mStates.emplace_back(state); }

    const std::vector<State>& getStates() const { return mStates; }
    std::vector<State>& rGetStates() { return mStates; }
    Range<std::vector<State>> selectTimestamps(const carl::Interval<tNumber>& span) { return selectFirstConsecutiveRange(mStates, [&](const State& in)->bool{ return in.timeStamp.intersects(span); } ); }

    template<typename Number>
    Range<std::vector<State>> selectSatisfyingStates(const Condition<Number>& cond) { return selectFirstConsecutiveRange(mStates, [&](const State& in)->bool{ auto tmp = in.satisfiesHalfspaces(cond.getMatrix(), cond.getVector()).first; return tmp != CONTAINMENT::NO && tmp != CONTAINMENT::BOT; } ); }

    std::vector<PlotData<State>> getPlotData(std::size_t refinementLevel = 0, std::size_t threadId = 0) const;
};

} // namespace hypro

#include "Flowpipe.tpp"
