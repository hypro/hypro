#include "HybridAutomaton.h"

namespace hypro {

	template<typename Number, typename Representation>
	HybridAutomaton<Number, Representation>::HybridAutomaton(const HybridAutomaton& _hybrid) : mHybridAutomaton(_hybrid.mHybridAutomaton) {
	}

	template<typename Number, typename Representation>
	HybridAutomaton<Number, Representation>::HybridAutomaton(const locationSet _initLocs, const locationSet _locs, const transitionSet _trans, Representation _initVal) {
		mHybridAutomaton.init = _initLocs;
		mHybridAutomaton.locs = _locs;
		mHybridAutomaton.trans = _trans;
		mHybridAutomaton.valuation = _initVal;
	}

	template<typename Number, typename Representation>
	std::set<hypro::Location<Number>*> HybridAutomaton<Number, Representation>::initialLocations() {
		return mHybridAutomaton.init;
	}

	template<typename Number, typename Representation>
	std::set<hypro::Location<Number>*> HybridAutomaton<Number, Representation>::locations() {
		return mHybridAutomaton.locs;
	}

	template<typename Number, typename Representation>
	std::set<hypro::Transition<Number>*> HybridAutomaton<Number, Representation>::transitions() {
		return mHybridAutomaton.trans;
	}

	template<typename Number, typename Representation>
	Representation HybridAutomaton<Number, Representation>::valuation() {
		return mHybridAutomaton.valuation;
	}
        
        template<typename Number, typename Representation>
	Representation HybridAutomaton<Number, Representation>::extInputValuation() {
		return mHybridAutomaton.extInputValuation;
	}
	
	template<typename Number, typename Representation>
	unsigned HybridAutomaton<Number,Representation>::dimension() const {
		return (*mHybridAutomaton.init.begin())->activityMat().rows();
	}

	template<typename Number, typename Representation>
	struct HybridAutomaton<Number, Representation>::hybridAutomaton HybridAutomaton<Number, Representation>::hybridAutomaton() {
		return mHybridAutomaton;
	}

	template<typename Number, typename Representation>
	void HybridAutomaton<Number, Representation>::setInitialLocations(locationSet _initLocs) {
		mHybridAutomaton.init = _initLocs;
	}

	template<typename Number, typename Representation>
	void HybridAutomaton<Number, Representation>::setLocations(locationSet _locs) {
		mHybridAutomaton.locs = _locs;
	}

	template<typename Number, typename Representation>
	void HybridAutomaton<Number, Representation>::setTransitions(transitionSet _trans) {
		mHybridAutomaton.trans = _trans;
	}

	template<typename Number, typename Representation>
	void HybridAutomaton<Number, Representation>::setValuation(Representation _val) {
		mHybridAutomaton.valuation = _val;
	}
        
        template<typename Number, typename Representation>
        void HybridAutomaton<Number, Representation>::setExtInputValuation(Representation _extInputVal) {
                mHybridAutomaton.extInputValuation = _extInputVal;
        }

	template<typename Number, typename Representation>
	void HybridAutomaton<Number, Representation>::setHybridAutomaton(struct hybridAutomaton _hybrid) {
		mHybridAutomaton = _hybrid;
	}

	template<typename Number, typename Representation>
	void HybridAutomaton<Number, Representation>::addLocation(location* _location) {
		mHybridAutomaton.locs.insert(_location);
	}
	
	template<typename Number, typename Representation>
	void HybridAutomaton<Number, Representation>::addTransition(transition* _transition) {
		mHybridAutomaton.trans.insert(_transition);
	}
}
