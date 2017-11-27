#include "HybridAutomaton.h"

namespace hypro
{

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

template<typename Number>
unsigned HybridAutomaton<Number>::dimension() const
{
    if (mInitialStates.empty()) return 0;

    return (mInitialStates.begin()->first->getFlow().cols());
}

}  // namespace hydra

