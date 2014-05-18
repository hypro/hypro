#include "HybridAutomaton.h"

namespace hypro {

	template<typename Number>
	HybridAutomaton<Number>::HybridAutomaton(const HybridAutomaton& _hybrid) : mHybridAutomaton(_hybrid.mHybridAutomaton) {
	}

	template<typename Number>
	HybridAutomaton<Number>::HybridAutomaton(const locationSet _initLocs, const locationSet _locs, const transitionSet _trans, hypro::valuation_t _initVal) {
		mInitialLocations = _initLocs;
		mLocations = _locs;
		mTransitions = _trans;
		mValuation = _initVal;

		mHybridAutomaton.init = _initLocs;
		mHybridAutomaton.locs = _locs;
		mHybridAutomaton.trans = _trans;
		mHybridAutomaton.valuation = _initVal;
	}

	template<typename Number>
	std::set<hypro::Location<Number>*> HybridAutomaton<Number>::initialLocations() {
		return mInitialLocations;
	}

	template<typename Number>
	std::set<hypro::Location<Number>*> HybridAutomaton<Number>::locations() {
		return mLocations;
	}

	template<typename Number>
	std::set<hypro::Transition<Number>*> HybridAutomaton<Number>::transitions() {
		return mTransitions;
	}

	template<typename Number>
	hypro::valuation_t HybridAutomaton<Number>::valuation() {
		return mValuation;
	}

	template<typename Number>
	struct HybridAutomaton<Number>::hybridAutomaton HybridAutomaton<Number>::hybridAutomaton() {
		return mHybridAutomaton;
	}

	template<typename Number>
	void HybridAutomaton<Number>::setInitialLocations(locationSet _initLocs) {
		mInitialLocations = _initLocs;
	}

	template<typename Number>
	void HybridAutomaton<Number>::setLocations(locationSet _locs) {
		mLocations = _locs;
	}

	template<typename Number>
	void HybridAutomaton<Number>::setTransitions(transitionSet _trans) {
		mTransitions = _trans;
	}

	template<typename Number>
	void HybridAutomaton<Number>::setValuation(hypro::valuation_t _val) {
		mValuation = _val;
	}

	template<typename Number>
	void HybridAutomaton<Number>::setHybridAutomaton(struct hybridAutomaton _hybrid) {
		mHybridAutomaton = _hybrid;
	}

}
