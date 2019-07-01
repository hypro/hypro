#include "HybridAutomaton.h"

namespace hypro
{

//Copy constructor
template<typename Number>
HybridAutomaton<Number>::HybridAutomaton(const HybridAutomaton<Number>& hybrid)
	: mLocations()
	//, mTransitions()
	//, mLocalBadStates(hybrid.getLocalBadStates())
	, mGlobalBadStates(hybrid.getGlobalBadStates())
	, mVariables(hybrid.getVariables())
{
	//std::cout << "Copy construct hybrid automaton" << std::endl;
	// mappings to update nested datastructures (transitions sets of locations and source/target locations of transitions).
	std::map<const Location<Number>*, std::size_t> locationMapping; // maps to position in new vector.
	std::map<Transition<Number>*, std::size_t> transitionMapping; // maps to position in new vector.

	// create real copies of the locations
	for(const auto l : hybrid.getLocations()){
		Location<Number> tmp = Location<Number>(*l);
		//tmp.setTransitions(std::vector<Transition<Number>*>());
    	mLocations.emplace_back(std::make_unique<Location<Number>>(tmp));
		locationMapping[l] = mLocations.size() - 1;
		assert(tmp.hash() == l->hash());
   	}
	// create copies of transitions
	//for(const auto t : hybrid.getTransitions()){
	//	mTransitions.emplace_back(std::make_unique<Transition<Number>>(Transition<Number>(*t)));
	//	mTransitions.back()->setSource(nullptr);
	//	mTransitions.back()->setTarget(nullptr);
	//	transitionMapping[t] = mTransitions.size() - 1;
	//}

	//update locations of transitions and transitions of locations
	for(auto& l : mLocations) {
		//std::cout << "consider new location " << l->getName() << "(" << l.get() << ")" << std::endl;
		for(auto& t : l->rGetTransitions()) {
			//std::cout << "consider copied transition " << t->getSource()->getName() << " (" << t->getSource() << ") --> " << t->getTarget()->getName() << " (" << t->getTarget() << ")" << std::endl;
			// verify that the source of the location already corresponds to the new location.
			assert(t->getSource() == l.get());

			// the target is updated to the new location.
			t->setTarget(mLocations[locationMapping[t->getTarget()]].get());
		}
	}

	// get correct location pointer for initial states.
	for(auto& otherInitial : hybrid.getInitialStates()) {
		auto copy = otherInitial.second;
		// update location
		this->addInitialState(mLocations[locationMapping[otherInitial.first]].get(), copy);
	}

	for(auto& otherBad : hybrid.getLocalBadStates()) {
		auto copy = otherBad.second;
		// update location
		this->addLocalBadState(mLocations[locationMapping[otherBad.first]].get(), copy);
	}

	#ifdef HYPRO_LOGGING
	DEBUG("hypro.datastructures","Hybrid automaton initial states after COPY construction.");
	for(const auto& iPair : mInitialStates) {
		DEBUG("hypro.datastructures","Initial state in loc " << iPair.first->getName());
	}
	#endif
}

/*
//Move constructor
template<typename Number>
HybridAutomaton<Number>::HybridAutomaton(HybridAutomaton<Number>&& hybrid)
	:
	mLocations(),
	mTransitions(),
	mGlobalBadStates(hybrid.getGlobalBadStates()),
	mVariables(hybrid.getVariables())
 {
	 std::cout << "Move construct hybrid automaton" << std::endl;
// mappings to update nested datastructures (transitions sets of locations and source/target locations of transitions).
	std::map<const Location<Number>*, std::size_t> locationMapping; // maps to position in new vector.
	std::map<Transition<Number>*, std::size_t> transitionMapping; // maps to position in new vector.

	// create real copies of the locations
	for(auto l : hybrid.getLocations()){
		Location<Number> tmp = Location<Number>(*l);
		tmp.setTransitions(std::vector<Transition<Number>*>());
    	mLocations.emplace_back(std::make_unique<Location<Number>>(tmp));
		locationMapping[l] = mLocations.size() - 1;
		assert(tmp.hash() == l->hash());
   	}
	// create copies of transitions
	for(auto& t : hybrid.getTransitions()){
		mTransitions.emplace_back(std::make_unique<Transition<Number>>(Transition<Number>(*t)));
		transitionMapping[t] = mTransitions.size() - 1;
	}

	//update locations of transitions and transitions of locations
	for(auto l : hybrid.getLocations()) {
		// only update transitions which are assigned to locations.
		for(auto t : l->getTransitions()) {

			// update transitions inside location
			mLocations[locationMapping[l]]->addTransition(mTransitions[transitionMapping[t]].get());

			// update source location.
			assert(t->getSource() == l);
			mTransitions[transitionMapping[t]]->setSource(mLocations[locationMapping[l]].get());

			// update correct target.
			mTransitions[transitionMapping[t]]->setTarget(mLocations[locationMapping[t->getTarget()]].get());
		}
	}

	// get correct location pointer for initial states.
	for(auto& otherInitial : hybrid.getInitialStates()) {
		auto copy = otherInitial.second;
		// update location
		this->addInitialState(mLocations[locationMapping[otherInitial.first]].get(), copy);
	}

	for(auto& otherBad : hybrid.getLocalBadStates()) {
		auto copy = otherBad.second;
		// update location
		this->addLocalBadState(mLocations[locationMapping[otherBad.first]].get(), copy);
	}

	DEBUG("hypro.datastructures","Hybrid automaton initial states after MOVE construction.");
	for(const auto& iPair : mInitialStates) {
		DEBUG("hypro.datastructures","Initial state in loc " << iPair.first->getName());
	}
}
*/

//Copy assignment
template<typename Number>
HybridAutomaton<Number>& HybridAutomaton<Number>::operator=(const HybridAutomaton<Number>& rhs){
	//std::cout << "In HA copy assignment!\n";
   	if(this != &rhs){
		auto copy{rhs};
		*this = std::move(copy);
	}
	return *this;
}

//Move Assignment
template<typename Number>
HybridAutomaton<Number>& HybridAutomaton<Number>::operator=(HybridAutomaton<Number>&& rhs){
	//std::cout << "In HA move assignment!\n";
   	if(this != &rhs){
    	//std::swap(rhs.mLocations, mLocations);
    	//std::swap(rhs.mTransitions, mTransitions);
    	mLocations = std::move(rhs.mLocations) ;
    	//mTransitions = std::move(rhs.mTransitions) ;
   		//Copy the rest
		mInitialStates = rhs.getInitialStates();
		mLocalBadStates = rhs.getLocalBadStates();
		mGlobalBadStates = rhs.getGlobalBadStates();
		mVariables = rhs.getVariables();
	}
	return *this;
}

template<typename Number>
std::vector<Location<Number>*> HybridAutomaton<Number>::getLocations() const {
	std::vector<Location<Number>*> res;
	for(const auto& l : mLocations){
		res.emplace_back(l.get());
	}
	return res;
}

template<typename Number>
Location<Number>* HybridAutomaton<Number>::getLocation(const std::size_t hash) const {
	for(const auto& loc : mLocations) {
		assert(loc != nullptr);
		if(loc->hash() == hash) {
			return loc.get();
		}
	}
	return nullptr;
}

template<typename Number>
Location<Number>* HybridAutomaton<Number>::getLocation(const std::string& name) const {

	for(const auto& loc : mLocations) {
		assert(loc != nullptr);
		if(loc->getName() == name) {
			return loc.get();
		}
	}
	return nullptr;
}


template<typename Number>
std::vector<Transition<Number>*> HybridAutomaton<Number>::getTransitions() const {
	std::vector<Transition<Number>*> res;
	for(const auto& loc : mLocations){
		for(auto tPtr : loc->getTransitions()) {
			res.emplace_back(tPtr);
		}
	}
	return res;
}

template<typename Number>
unsigned HybridAutomaton<Number>::dimension() const
{
    if (mInitialStates.empty()) return 0;

    return (mInitialStates.begin()->first->dimension());
}


template<typename Number>
const std::set<Label> HybridAutomaton<Number>::getLabels() const {

	//TODO:
	assert(false && "NOT IMPLEMENTED");
	std::set<Label> labels;
	/*
	for(const auto& tra: mTransitions) {
		for(const auto& lab: tra->getLabels()) {
			labels.emplace(lab);
		}
	}
	*/
	return labels;
}

template<typename Number>
Location<Number>* HybridAutomaton<Number>::addLocation(const Location<Number>& location) {
	return this->addLocation(std::move(std::make_unique<Location<Number>>(location)));
}

template<typename Number>
Location<Number>* HybridAutomaton<Number>::addLocation(std::unique_ptr<Location<Number>>&& location) {
	assert(location != nullptr);
    mLocations.emplace_back(std::move(location));
	assert(location.get() == mLocations.back().get());
	return mLocations.back().get();
}

/*
template<typename Number>
void HybridAutomaton<Number>::addTransition(const Transition<Number>& transition) {
	this->addTransition(std::move(std::make_unique<Transition<Number>>(transition)));
}
*/

template<typename Number>
void HybridAutomaton<Number>::addTransition(std::unique_ptr<Transition<Number>>&& transition) {
	assert(transition != nullptr);
	for(auto& l : mLocations) {
		if(l.get() == transition->getSource()) {
			l.addTransition(std::move(transition));
			break;
		}
	}
}

/*
template<typename Number>
void HybridAutomaton<Number>::removeTransition(Transition<Number>* toRemove) {
	for(auto tIt = mTransitions.begin(); tIt != mTransitions.end(); ) {
		if((*tIt).get() == toRemove)
			tIt = mTransitions.erase(tIt);
		else
			++tIt;
	}
}
*/

template<typename Number>
void HybridAutomaton<Number>::reduce() {
	// TODO rewrite

	assert(false && "NOT IMPLEMENTED.");
}

template<typename Number>
bool HybridAutomaton<Number>::isComposedOf(const HybridAutomaton<Number>& rhs) const {
	// trivial case.
	if(*this == rhs) return true;

	// check variable sets
	for(const auto& v : rhs.getVariables()) {
		if(std::find(mVariables.begin(), mVariables.end(), v) == mVariables.end()) {
			//std::cout << "Variable " << v << " not contained in this, return false" << std::endl;
			return false;
		}
	}

	// check locations:
	// try to find *exactly* one location, which matches - matching is defined by name, flow and invariant.
	for(auto& locPtr : this->mLocations) {
		bool foundOne = false;
		//std::cout << "Try to find a matching location for " << locPtr->getName() << std::endl;
		for(auto& rhsLocPtr : rhs.getLocations()) {
			//std::cout << "Consider " << rhsLocPtr->getName() << std::endl;
			if(locPtr->isComposedOf(*rhsLocPtr, rhs.getVariables(), this->getVariables())) {
				if(foundOne) {
					//std::cout << "composed from more than one loc - return false." << std::endl;
					return false;
				}
				foundOne = true;
			}
		}
		if(!foundOne) {
			//std::cout << "could not find a matching location in rhs." << std::endl;
			return false;
		}
	}

	// check transitions:
	// try to find a matching transition. Also take loops (no-op loops) into account for the check.
	for(auto& transPtr : this->mTransitions) {
		bool foundOne = false;
		//std::cout << "Try to find transition for " << transPtr->getSource()->getName() << " -> " << transPtr->getTarget()->getName() << std::endl;
		// first try to find no-op transitions (where the control stays in the same mode for that component)
		bool loop = false;
		for(auto& locPtr : rhs.getLocations()) {
			//std::cout << "Find name " << locPtr->getName() << std::endl;
			if(transPtr->getSource()->getName().find(locPtr->getName()) != std::string::npos && transPtr->getTarget()->getName().find(locPtr->getName()) != std::string::npos) {
				//std::cout << "Found loop: " << transPtr->getSource()->getName() << " -> " << transPtr->getTarget()->getName() << std::endl;
				if(loop) {
					//std::cout << "Two loops - return false" << std::endl;
					return false;
				}
				loop = true;
			}
		}
		if(!loop) {
			for(const auto rhsTransPtr : rhs.getTransitions()) {
				//std::cout << "consider " << rhsTransPtr->getSource()->getName() << " -> " << rhsTransPtr->getTarget()->getName() << std::endl;
				if(transPtr->isComposedOf(*rhsTransPtr, rhs.getVariables(), this->getVariables())) {
					//std::cout << "Found " << rhsTransPtr->getSource()->getName() << " -> " << rhsTransPtr->getTarget()->getName() << std::endl;
					if(foundOne) {
						//std::cout << "found two matching transitions - return false" << std::endl;
						return false;
					}
					foundOne = true;
				}
			}
		}

		if(!foundOne && !loop) {
			//std::cout << "Did not find matching transition - return false." << std::endl;
			return false;
		}
	}

	return true;
}

template<typename Number>
std::string HybridAutomaton<Number>::getDotRepresentation() const {
	std::string res = "digraph {\n";

	for(const auto& loc : mLocations) {
		res += loc->getDotRepresentation(mVariables);
	}

	/*
	for(const auto& tra : mTransitions) {
		res += tra->getDotRepresentation(mVariables);
	}
	*/

	res += "}\n";

	return res;
}

template<typename Number>
void HybridAutomaton<Number>::decompose(const Decomposition& decomposition){
	// decompose locations (flow (affine trafo) and invariant(condition))
    for(auto& location : mLocations){
    	location->decompose(decomposition);
    }

	/*
    // decompose transitions (guard and resets (both conditions))
    for(auto& transition : mTransitions){
    	transition->decompose(decomposition);
    }
	*/

	// decompose local bad states (condition)
	for(auto it = mLocalBadStates.begin(); it != mLocalBadStates.end(); ++it){
		it->second.decompose(decomposition);
	}

	// decompose global bad states (conditions)
	for(auto it = mGlobalBadStates.begin(); it != mGlobalBadStates.end(); ++it){
		it->decompose(decomposition);
	}
	// decompose intial states (state sets)
	DEBUG("hypro.datastructures","Decompose initial states.");
	for(auto it = mInitialStates.begin(); it != mInitialStates.end(); ++it){
		it->second.decompose(decomposition);
	}
	DEBUG("hypro.datastructures","Decompose initial states done. Having " << mInitialStates.size() << " initial states.");
}

template<typename Number>
std::string HybridAutomaton<Number>::getStatistics() const {
	std::stringstream out;
	out << "#Locations: " << mLocations.size() << std::endl;
	//out << "#Transitions: " << mTransitions.size() << std::endl;

	return out.str();
}


template<typename Number>
HybridAutomaton<Number> operator||(const HybridAutomaton<Number>& lhs, const HybridAutomaton<Number>& rhs) {
	//std::cout << "||" << std::endl;

	HybridAutomaton<Number> ha;
	using variableVector = std::vector<std::string>; /// Vector of variables
	const variableVector& lhsVar = lhs.getVariables();
	const variableVector& rhsVar = rhs.getVariables();
	std::map<unsigned, std::pair<unsigned,unsigned>> sharedVars;

	//std::cout << "lhs variables: ";
	//for(auto a : lhsVar) { std::cout << a << " "; }
	//std::cout << std::endl;
	//std::cout << "rhs variables: ";
	//for(auto a : rhsVar) { std::cout << a << " "; }
	//std::cout << std::endl;

	variableVector haVar;
	variableVector::size_type  i=0, j=0;
	while(i < lhsVar.size() and j < rhsVar.size()) {
	if (lhsVar.at(i) == rhsVar.at(j)) {
		//std::cout << "same var, add " << lhsVar[i] << std::endl;
		haVar.push_back(lhsVar[i]);
		i++; j++;
		continue;
	}
	if (lhsVar.at(i) < rhsVar.at(j)) {
		//std::cout << "push left first " << lhsVar.at(i) << std::endl;
		haVar.push_back(lhsVar[i]);
		i++;
		continue;
	}
	if (lhsVar.at(i) > rhsVar.at(j)) {
		//std::cout << "push right first " << rhsVar.at(j) << std::endl;
		haVar.push_back(rhsVar[j]);
		j++;
		continue;
	}
	}
	for(; i < lhsVar.size(); i++) {
		//std::cout << "fill left: " << lhsVar[i] << std::endl;
		haVar.push_back(lhsVar[i]);
	}
	for(; j < rhsVar.size(); j++) {
		//std::cout << "fill right: " << rhsVar[j] << std::endl;
		haVar.push_back(rhsVar[j]);
	}
	ha.setVariables(haVar);

	//std::cout << "Variables: ";
	//for(auto a : haVar) { std::cout << a << " "; }
	//std::cout << "locations & transisitons" << std::endl;


	// find shared variables
	for(std::size_t i = 0; i != haVar.size(); ++i) {
		bool left = false;
		bool right = false;
		std::size_t l = 0;
		std::size_t r = 0;
		while(l != lhsVar.size()) {
			if(lhsVar[l] == haVar[i]){
				left = true;
				break;
			}
			++l;
		}
		while(r != rhsVar.size()) {
			if(rhsVar[r] == haVar[i]){
				right = true;
				break;
			}
			++r;
		}
		if(left && right) {
			//std::cout << "Shared var at " << i << " corresponds to (" << l << "," << r << ")" << std::endl;
			sharedVars[i] = std::make_pair(l,r);
		}
	}
	//std::cout << "Detected " << sharedVars.size() << " shared variables." << std::endl;

	for(const auto& locLhs : lhs.getLocations()) {
		for(const auto& locRhs : rhs.getLocations()) {
			//Location<Number>* loc = parallelCompose(locLhs,locRhs,lhsVar,rhsVar,haVar);
			//ha.addLocation(*loc);
			std::unique_ptr<Location<Number>> loc = parallelCompose(locLhs,locRhs,lhsVar,rhsVar,haVar);
			ha.addLocation(std::move(loc));
		}
	}

	//std::cout << "######################## TRANSITIONS ########################" << std::endl;
	//build transisitons
	std::set<Label> lhsLabels = lhs.getLabels();
	std::set<Label> rhsLabels = rhs.getLabels();
	for(const auto lhsT: lhs.getTransitions()) {
		for(const auto rhsT: rhs.getTransitions()) {
			//Transition<Number>* t = parallelCompose(lhsT, rhsT, lhsVar, rhsVar, haVar, ha, lhsLabels, rhsLabels);
			std::unique_ptr<Transition<Number>> t = parallelCompose(lhsT, rhsT, lhsVar, rhsVar, haVar, ha, lhsLabels, rhsLabels);
			if(t) {
				ha.addTransition(std::move(t));
				(t->getSource())->addTransition(t.get());
			}
		}
	}

	// non-synchronizing transitions in each component
	// fix rhs first
	//std::cout << "Fix rhs." << std::endl;
	for(const auto lhsT: lhs.getTransitions()) {
		if(lhsT->getLabels().empty()) {
			for(const auto& loc : rhs.getLocations()) {
				//std::cout << "Potential transition " << lhsT->getSource()->getName() << "_" << loc->getName() << " -> " << lhsT->getTarget()->getName() << "_" << loc->getName() << std::endl;
				//std::cout << "Original reset: " << lhsT->getReset().getMatrix() << " and " << lhsT->getReset().getVector() << std::endl;
				//Transition<Number>* tmp = new Transition<Number>(loc,loc);
				//std::unique_ptr<Transition<Number>> tmp = std::make_unique<Transition<Number>>(new Transition<Number>(loc,loc));
				std::unique_ptr<Transition<Number>> tmp = std::make_unique<Transition<Number>>(Transition<Number>(loc,loc));
				// TODO: temporary test -> fix!
				Reset<Number> tmpReset = Reset<Number>(matrix_t<Number>::Identity(rhsVar.size(), rhsVar.size()), vector_t<Number>::Zero(rhsVar.size()));
				if(!sharedVars.empty()) {
					// Attention: This is a temporary solution. Naturally, we would need to replicate the reset on the shared variables to create
					// an admissible combined reset.
					// Todo: iterate over rows, then over cols (only the ones which correspond to shared vars) and set the resets accordingly.

					//std::cout << "Have " << sharedVars.size() << " shared variables." << std::endl;
					for(auto shdIt = sharedVars.begin(); shdIt != sharedVars.end(); ++shdIt) {
						//std::cout << "update row " << shdIt->second.second << std::endl;
						for(auto colIt = sharedVars.begin(); colIt != sharedVars.end(); ++colIt) {
							tmpReset.rGetMatrix()(shdIt->second.second, colIt->second.second) = lhsT->getReset().getMatrix()(shdIt->second.first,colIt->second.first);
						}
						tmpReset.rGetVector()(shdIt->second.second) = lhsT->getReset().getVector()(shdIt->second.first);
					}
				}

				//std::cout << "tmpreset after update: " << tmpReset << std::endl;

				//tmp->setReset(combine(lhsT->getReset(),tmpReset,haVar,lhsVar,rhsVar));
				tmp->setReset(tmpReset);
				tmp->setAggregation(lhsT->getAggregation());

				//Transition<Number>* t = parallelCompose(lhsT, tmp, lhsVar, rhsVar, haVar, ha, lhsLabels, rhsLabels);
				std::unique_ptr<Transition<Number>> t = parallelCompose(lhsT, tmp.get(), lhsVar, rhsVar, haVar, ha, lhsLabels, rhsLabels);
				if(t) {
					//std::cout << "Add." << std::endl;
					ha.addTransition(std::move(t));
					(t->getSource())->addTransition(t.get());
				}
			}
		}
	}
	// fix lhs
	//std::cout << "Fix lhs." << std::endl;
	for(const auto rhsT: rhs.getTransitions()) {
		if(rhsT->getLabels().empty()) {
			for(const auto& loc : lhs.getLocations()) {
				//std::cout << "Potential transition " << loc->getName()<< "_" << rhsT->getSource()->getName() << " -> " << loc->getName() << "_" << rhsT->getTarget()->getName() << std::endl;
				//std::cout << "Original reset: " << rhsT->getReset().getMatrix() << " and " << rhsT->getReset().getVector() << std::endl;
				//Transition<Number>* tmp = new Transition<Number>(loc,loc);
				std::unique_ptr<Transition<Number>> tmp = std::make_unique<Transition<Number>>(Transition<Number>(loc,loc));
				// TODO: temporary test -> fix!
				Reset<Number> tmpReset = Reset<Number>(matrix_t<Number>::Identity(lhsVar.size(), lhsVar.size()), vector_t<Number>::Zero(lhsVar.size()));
				if(!sharedVars.empty()) {
					// Attention: This is a temporary solution. Naturally, we would need to replicate the reset on the shared variables to create
					// an admissible combined reset.
					for(auto shdIt = sharedVars.begin(); shdIt != sharedVars.end(); ++shdIt) {
						//std::cout << "update row " << shdIt->second.second << std::endl;
						for(auto colIt = sharedVars.begin(); colIt != sharedVars.end(); ++colIt) {
							tmpReset.rGetMatrix()(shdIt->second.first, colIt->second.first) = rhsT->getReset().getMatrix()(shdIt->second.second,colIt->second.second);
						}
						tmpReset.rGetVector()(shdIt->second.first) = rhsT->getReset().getVector()(shdIt->second.second);
					}
				}

				//std::cout << "tmpreset after update: " << tmpReset << std::endl;

				//tmp->setReset(combine(rhsT->getReset(),tmpReset,haVar,rhsVar,lhsVar));
				tmp->setReset(tmpReset);
				tmp->setAggregation(rhsT->getAggregation());

				//Transition<Number>* t = parallelCompose(tmp, rhsT, lhsVar, rhsVar, haVar, ha, lhsLabels, rhsLabels);
				std::unique_ptr<Transition<Number>> t = parallelCompose(tmp.get(), rhsT, lhsVar, rhsVar, haVar, ha, lhsLabels, rhsLabels);
				if(t) {
					//std::cout << "Add." << std::endl;
					ha.addTransition(std::move(t));
					(t->getSource())->addTransition(t.get());
		       	}
			}
		}
	}

	// set initial states (//std:multimap<const Location<Number>*, State>;)
	//std::cout << "set initial states" << std::endl;
	for(const auto& initialStateLhs: lhs.getInitialStates()) {
		for(const auto& initialStateRhs: rhs.getInitialStates()) {
			std::cout << "WARNING: parallel composition of initial states not implemented yet." << std::endl;
			assert(false);
			//State state = parallelCompose(initialStateLhs.second,  initialStateRhs.second, lhsVar, rhsVar, haVar, ha);
			//ha.addInitialState(state);
		}
	}

	//localBadstates
	//globalBAdstates

	// remove non-reachable locations and transitions.
	ha.reduce();

	return ha; //std::move??? -> no, prevents copy-elision!
}

}  // namespace hypro
