#include "HybridAutomaton.h"

namespace hypro {

	template<typename Number, typename Representation>
	HybridAutomaton<Number, Representation>::HybridAutomaton(const HybridAutomaton& _hybrid) :
		mInitialLocations(_hybrid.initialLocations()),
		mLocations(_hybrid.locations()),
		mTransitions(_hybrid.transitions()),
		mInitialValuation(_hybrid.initialValuation()),
		mExtInputValuation(_hybrid.extInputValuation())
	{}

	template<typename Number, typename Representation>
	HybridAutomaton<Number, Representation>::HybridAutomaton(const locationSet _initLocs, const locationSet _locs, const transitionSet _trans, Representation _initVal) :
		mInitialLocations(_initLocs),
		mLocations(_locs),
		mTransitions(_trans),
		mInitialValuation(_initVal),
		mExtInputValuation()
	{}

	template<typename Number, typename Representation>
	const std::set<hypro::Location<Number>*>& HybridAutomaton<Number, Representation>::initialLocations() const{
		return mInitialLocations;
	}

	template<typename Number, typename Representation>
	const std::set<hypro::Location<Number>*>& HybridAutomaton<Number, Representation>::locations() const{
		return mLocations;
	}

	template<typename Number, typename Representation>
	const std::set<hypro::Transition<Number>*>& HybridAutomaton<Number, Representation>::transitions() const{
		return mTransitions;
	}

	template<typename Number, typename Representation>
	const Representation& HybridAutomaton<Number, Representation>::initialValuation() const{
		return mInitialValuation;
	}

		template<typename Number, typename Representation>
	const Representation& HybridAutomaton<Number, Representation>::extInputValuation() const{
		return mExtInputValuation;
	}

	template<typename Number, typename Representation>
	unsigned HybridAutomaton<Number,Representation>::dimension() const {
		return (*mInitialLocations.begin())->activityMat().rows();
	}

	template<typename Number, typename Representation>
	void HybridAutomaton<Number, Representation>::setInitialLocations(const locationSet& _initLocs) {
		mInitialLocations = _initLocs;
	}

	template<typename Number, typename Representation>
	void HybridAutomaton<Number, Representation>::setLocations(const locationSet& _locs) {
		mLocations = _locs;
	}

	template<typename Number, typename Representation>
	void HybridAutomaton<Number, Representation>::setTransitions(const transitionSet& _trans) {
		mTransitions = _trans;
	}

	template<typename Number, typename Representation>
	void HybridAutomaton<Number, Representation>::setInitialValuation(const Representation& _val) {
		mInitialValuation = _val;
	}

	template<typename Number, typename Representation>
	void HybridAutomaton<Number, Representation>::setExtInputValuation(const Representation& _extInputVal) {
		mExtInputValuation = _extInputVal;
	}

	template<typename Number, typename Representation>
	void HybridAutomaton<Number, Representation>::addLocation(Location<Number>* _location) {
		mLocations.insert(_location);
	}

	template<typename Number, typename Representation>
	void HybridAutomaton<Number, Representation>::addTransition(Transition<Number>* _transition) {
		mTransitions.insert(_transition);
	}
}
