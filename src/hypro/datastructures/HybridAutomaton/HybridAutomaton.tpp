#include "HybridAutomaton.h"

namespace hypro
{
template<typename Number>
HybridAutomaton<Number>::HybridAutomaton(const locationSet& _locs, const transitionSet& _trans, const locationStateMap& _initialStates)
    : mLocations(_locs), mTransitions(_trans), mInitialStates(_initialStates)
{
}

template<typename Number>
const Location<Number>* HybridAutomaton<Number>::getLocation(std::size_t id) const {
	for(const auto loc : mLocations) {
		if(loc->getId() == id) {
			return loc;
		}
	}
	return nullptr;
}

template<typename Number>
const Location<Number>* HybridAutomaton<Number>::getLocation(std::string name) const {
	for(const auto loc : mLocations) {
		if(loc->getName() == name) {
			return loc;
		}
	}
	return nullptr;
}

unsigned HybridAutomaton::dimension() const
{
    if (mInitialStates.empty()) return 0;

    return (mInitialStates.begin()->first->getFlow().cols());
}

}  // namespace hydra

