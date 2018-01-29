#include "HybridAutomaton.h"

namespace hypro
{

template<typename Number, typename State>
const Location<Number>* HybridAutomaton<Number,State>::getLocation(std::size_t id) const {
	for(const auto loc : mLocations) {
		if(loc->getId() == id) {
			return loc;
		}
	}
	return nullptr;
}

template<typename Number, typename State>
const Location<Number>* HybridAutomaton<Number,State>::getLocation(const std::string& name) const {
	for(const auto loc : mLocations) {
		if(loc->getName() == name) {
			return loc;
		}
	}
	return nullptr;
}

template<typename Number, typename State>
unsigned HybridAutomaton<Number,State>::dimension() const
{
    if (mInitialStates.empty()) return 0;

    return (mInitialStates.begin()->first->getFlow().cols()-1);
}

}  // namespace hydra

