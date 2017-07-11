/*
#include "HybridAutomaton.h"

namespace hypro
{
HybridAutomaton::HybridAutomaton(const locationSet& _locs, const transitionSet& _trans, const locationStateMap& _initialStates)
    : mLocations(_locs), mTransitions(_trans), mInitialStates(_initialStates)
{
}

unsigned HybridAutomaton::dimension() const
{
    if (mInitialStates.empty()) return 0;

    return (mInitialStates.begin()->first->getFlow().cols());
}

}  // namespace hydra

*/