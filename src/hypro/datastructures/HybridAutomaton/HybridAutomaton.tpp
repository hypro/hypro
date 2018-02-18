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
							//std::cout << __func__ << ": remove transition " << (*t)->getSource()->getName() << " -> " << (*t)->getTarget()->getName() << std::endl;
							t = mTransitions.erase(t);
						} else {
							++t;
						}
					}
					//std::cout << __func__ << ": remove unreachable location " << (*locIt)->getName() << std::endl;
					locIt = mLocations.erase(locIt);
				} else {
					++locIt;
				}
			} else {
				++locIt;
			}
		}
	}
}

template<typename Number,typename State>
bool HybridAutomaton<Number,State>::isComposedOf(const HybridAutomaton<Number,State>& rhs) const {
	// trivial case.
	if(*this == rhs) return true;

	// check variables
	for(const auto& v : rhs.getVariables()) {
		if(std::find(mVariables.begin(), mVariables.end(), v) == mVariables.end()) {
			std::cout << "Variable " << v << " not contained in this, return false" << std::endl;
			return false;
		}
	}

	// check locations
	for(auto locPtr : this->mLocations) {
		bool foundOne = false;
		std::cout << "Try to find a matching location for " << locPtr->getName() << std::endl;
		for(auto rhsLocPtr : rhs.getLocations()) {
			std::cout << "Consider " << rhsLocPtr->getName() << std::endl;
			if(locPtr->isComposedOf(*rhsLocPtr, rhs.getVariables(), this->getVariables())) {
				if(foundOne) {
					std::cout << "composed from more than one loc - return false." << std::endl;
					return false;
				}
				foundOne = true;
			}
		}
		if(!foundOne) {
			std::cout << "could not find a matching location in rhs." << std::endl;
			return false;
		}
	}

	// check transitions
	for(auto transPtr : this->mTransitions) {
		bool foundOne = false;
		std::cout << "Try to find transition for " << transPtr->getSource()->getName() << " -> " << transPtr->getTarget()->getName() << std::endl;
		// first try to find no-op transitions (where the control stays in the same mode for that component)
		bool loop = false;
		for(auto locPtr : rhs.getLocations()) {
			if(transPtr->getSource()->getName().find(locPtr->getName()) && transPtr->getTarget()->getName().find(locPtr->getName())) {
				if(loop) {
					std::cout << "Two loops - return false" << std::endl;
					return false;
				}
				loop = true;
			}
		}
		if(!loop) {
			for(auto rhsTransPtr : rhs.getTransitions()) {
				std::cout << "consider " << rhsTransPtr->getSource()->getName() << " -> " << rhsTransPtr->getTarget()->getName() << std::endl;
				if(transPtr->isComposedOf(*rhsTransPtr, rhs.getVariables(), this->getVariables())) {
					if(foundOne) {
						std::cout << "found two matching transitions - return false" << std::endl;
						return false;
					}
					foundOne = true;
				}
			}
		}

		if(!foundOne && !loop) {
			std::cout << "Did not find matching transition - return false." << std::endl;
			return false;
		}
	}

	return true;
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

