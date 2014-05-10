#include "HybridAutomaton.h"

namespace hypro {

	HybridAutomaton(const HybridAutomaton& _hybrid) : mHybridAutomaton(_hybrid.mHybridAutomaton) {
	}

	HybridAutomaton(const locationSet _initLocs, const locationSet _locs, const transitionSet _trans, hypro::valuation_t _initVal) {
		mInitialLocations = _initLocs;
		mLocations = _locs;
		mTransitions = _trans;
		mValuation = _initVal;

		mHybridAutomaton.init = _initLocs;
		mHybridAutomaton.locs = _locs;
		mHybridAutomaton.trans = _trans;
		mHybridAutomaton.valuation = _initVal;
	}

	locationSet initialLocations() {
		return mInitialLocations;
	}

	locationSet locations() {
		return mLocations;
	}

	transitionSet transitions() {
		return mTransitions;
	}

	hypro::valuation_t valuation() {
		return mValuation;
	}

	hybridAutomaton hybridAutomaton() {
		return mHybridAutomaton;
	}

	void setInitialLocations(locationSet _initLocs) {
		mInitialLocations = _initLocs;
	}

	void setLocations(locationSet _locs) {
		mLocations = _locs;
	}

	void setTransitions(transitionSet _trans) {
		mTransitions = _trans;
	}

	void setValuation(hypro::valuation_t _val) {
		mValuation = _val;
	}

	void setHybridAutomaton(hybridAutomaton _hybrid) {
		mHybridAutomaton = _hybrid;
	}

}
