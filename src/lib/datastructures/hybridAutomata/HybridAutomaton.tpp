#include "HybridAutomaton.h"

namespace hypro {

	HybridAutomaton(const HybridAutomaton& _hybrid) : mHybridAutomaton(_hybrid.mHybridAutomaton) {
	}

	HybridAutomaton(const locationSet _initLocs, const locationSet _locs, const transitionSet _trans, valuation_t _initVal) {
		mInitialLocations = _initLocs;
		mLocations = _locs;
		mTransitions = _trans;
		mValuation = _initVal;

		mHybridAutomaton.init = _initLocs;
		mHybridAutomaton.locs = _locs;
		mHybridAutomaton.trans = _trans;
		mHybridAutomaton.valuation = _initVal;
	}

	locationSet getInitialLocations() {
		return mInitialLocations;
	}

	locationSet getLocations() {
		return mLocations;
	}

	transitionSet getTransitions() {
		return mTransitions;
	}

	valuation_t getValuation() {
		return mValuation;
	}

	hybridAutomaton getHybridAutomaton() {
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

	void setValuation(valuation_t _val) {
		mValuation = _val;
	}

	void setHybridAutomaton(hybridAutomaton _hybrid) {
		mHybridAutomaton = _hybrid;
	}

}
