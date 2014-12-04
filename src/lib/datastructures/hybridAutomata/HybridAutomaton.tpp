#include "HybridAutomaton.h"

namespace hypro {

	template<typename Number>
	HybridAutomaton<Number>::HybridAutomaton(const HybridAutomaton& _hybrid) : mHybridAutomaton(_hybrid.mHybridAutomaton) {
	}

	template<typename Number>
	HybridAutomaton<Number>::HybridAutomaton(const locationSet _initLocs, const locationSet _locs, const transitionSet _trans, hypro::valuation_t<Number> _initVal) {
		mHybridAutomaton.init = _initLocs;
		mHybridAutomaton.locs = _locs;
		mHybridAutomaton.trans = _trans;
		mHybridAutomaton.valuation = _initVal;
	}

	template<typename Number>
	std::set<hypro::Location<Number>*> HybridAutomaton<Number>::initialLocations() {
		return mHybridAutomaton.init;
	}

	template<typename Number>
	std::set<hypro::Location<Number>*> HybridAutomaton<Number>::locations() {
		return mHybridAutomaton.locs;
	}

	template<typename Number>
	std::set<hypro::Transition<Number>*> HybridAutomaton<Number>::transitions() {
		return mHybridAutomaton.trans;
	}

	template<typename Number>
	hypro::valuation_t<Number> HybridAutomaton<Number>::valuation() {
		return mHybridAutomaton.valuation;
	}

	template<typename Number>
	struct HybridAutomaton<Number>::hybridAutomaton HybridAutomaton<Number>::hybridAutomaton() {
		return mHybridAutomaton;
	}

	template<typename Number>
	void HybridAutomaton<Number>::setInitialLocations(locationSet _initLocs) {
		mHybridAutomaton.init = _initLocs;
	}

	template<typename Number>
	void HybridAutomaton<Number>::setLocations(locationSet _locs) {
		mHybridAutomaton.locs = _locs;
	}

	template<typename Number>
	void HybridAutomaton<Number>::setTransitions(transitionSet _trans) {
		mHybridAutomaton.trans = _trans;
	}

	template<typename Number>
	void HybridAutomaton<Number>::setValuation(hypro::valuation_t<Number> _val) {
		mHybridAutomaton.valuation = _val;
	}

	template<typename Number>
	void HybridAutomaton<Number>::setHybridAutomaton(struct hybridAutomaton _hybrid) {
		mHybridAutomaton = _hybrid;
	}

	template<typename Number>
	void HybridAutomaton<Number>::addLocation(location* _location) {
		mHybridAutomaton.locs.insert(_location);
	}
	
	template<typename Number>
	void HybridAutomaton<Number>::addTransition(transition* _transition) {
		mHybridAutomaton.trans.insert(_transition);
	}
	/*
	template<typename Number>
	HybridAutomaton<Number>& HybridAutomaton<Number>::operator= (HybridAutomaton<Number>&& _rhs) {
		mHybridAutomaton = std::move(_rhs.mHybridAutomaton);
		return *this;
	}*/
}
