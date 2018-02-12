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
const Location<Number>* HybridAutomaton<Number,State>::getLocation(std::string name) const {
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

    return (mInitialStates.begin()->first->getFlow().cols());
}

template<typename Number, typename State>
void HybridAutomaton<Number,State>::decompose(std::vector<std::vector<size_t>> decomposition){
	// decompose locations (flow (affine trafo) and invariant(condition))
    for(auto location : mLocations){
    	location->decompose(decomposition);
    }
    
    // decompose transitions (guard and resets (both conditions))
    for(auto transition : mTransitions){
    	transition->decompose(decomposition);
    }
	
	// decompose local bad states (condition)
	for(typename std::map<const Location<Number>*, Condition<Number>>::iterator it = mLocalBadStates.begin(); it != mLocalBadStates.end(); ++it){
		it->second.decompose(decomposition);
	}			

	// decompose global bad states (conditions)
	for(typename std::vector<Condition<Number>>::iterator it = mGlobalBadStates.begin(); it != mGlobalBadStates.end(); ++it){
		it->decompose(decomposition);
	}
	
	// decompose intial states (state sets)
	for(typename std::multimap<const Location<Number>*, State>::iterator it = mInitialStates.begin(); it != mInitialStates.end(); ++it){
		it->second.decompose(decomposition);
	}
}


}  // namespace hydra

