#include "HybridAutomaton.h"

namespace hypro
{

template<typename Number, typename State>
Location<Number>* HybridAutomaton<Number,State>::getLocation(std::size_t id) const {
	for(const auto loc : mLocations) {
		if(loc->getId() == id) {
			return loc;
		}
	}
	return nullptr;
}

template<typename Number, typename State>
Location<Number>* HybridAutomaton<Number,State>::getLocation(const std::string& name) const {
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

template<typename Number, typename State>
const std::set<Label> HybridAutomaton<Number,State>::getLabels() const {

	//TODO:
	std::set<Label> labels;
	for(const auto tra: mTransitions) {
		for(const auto lab: tra->getLabels()) {
			labels.insert(lab);
		}
	}
	return labels;
}

template<typename Number, typename State>
void HybridAutomaton<Number,State>::reduce() {
	bool changed = true;
	while(changed) {
		changed = false;
		for(auto locIt = mLocations.begin(); locIt != mLocations.end(); ) {
			// non-initial locations
			if(mInitialStates.find(*locIt) == mInitialStates.end()) {
				// check for being a target
				bool isTarget = false;
				for(auto t : mTransitions) {
					if(t->getTarget() == *locIt) {
						isTarget = true;
						break;
					}
				}
				// the location is discretely not reachable -> remove all outgoing transitions and then the location itself.
				if(!isTarget) {
					changed = true;
					for(auto t = mTransitions.begin(); t != mTransitions.end(); ) {
						if((*t)->getSource() == *locIt) {
							std::cout << __func__ << ": remove transition " << (*t)->getSource()->getName() << " -> " << (*t)->getTarget()->getName() << std::endl;
							t = mTransitions.erase(t);
						} else {
							++t;
						}
					}
					std::cout << __func__ << ": remove unreachable location " << (*locIt)->getName() << std::endl;
					locIt = mLocations.erase(locIt);
				} else {
					++locIt;
				}
			}
		}
	}
}

template<typename Number, typename State>
std::string HybridAutomaton<Number,State>::getDotRepresentation() const {
	std::string res = "digraph {\n";

	std::map<unsigned, Location<Number>*> locIds;
	for(const auto loc : mLocations) {
		res += loc->getDotRepresentation(mVariables);
	}

	for(const auto tra : mTransitions) {
		res += tra->getDotRepresentation(mVariables);
	}

	res += "}\n";

	return res;
}

}  // namespace hydra

