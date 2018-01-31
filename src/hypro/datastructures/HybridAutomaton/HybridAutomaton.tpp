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
Location<Number>* HybridAutomaton<Number,State>::getLocation(std::string name) const {
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

}

template<typename Number, typename State>
std::string HybridAutomaton<Number,State>::getDotRepresentation() const {
	std::string res = "";

	return res;
}

template<typename Number, typename State>
std::size_t HybridAutomaton<Number,State>::getDotRepresentation(std::size_t startIndex, std::string& nodes, std::string& transitions, std::vector<unsigned>& levels) {

}

}  // namespace hydra

