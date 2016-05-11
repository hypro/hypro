#include "HybridAutomaton.h"

namespace hypro {

template <typename Number>
HybridAutomaton<Number>::HybridAutomaton( const HybridAutomaton &_hybrid )
	: mLocations( _hybrid.locations() )
	, mTransitions( _hybrid.transitions() )
	, mInitialStates( _hybrid.initialStates() )
	, mLocalBadStates( _hybrid.localBadStates() )
	, mGlobalBadStates( _hybrid.globalBadStates() )
	, mReachabilitySettings( _hybrid.reachabilitySettings() )
{}

template <typename Number>
HybridAutomaton<Number>::HybridAutomaton( const locationSet& _locs,
														  const transitionSet& _trans, const locationStateMap& _initialStates )
	: mLocations( _locs )
	, mTransitions( _trans )
	, mInitialStates( _initialStates )
{}

template <typename Number>
const std::set<hypro::Location<Number> *> &HybridAutomaton<Number>::locations() const {
	return mLocations;
}

template <typename Number>
const std::set<hypro::Transition<Number> *> &HybridAutomaton<Number>::transitions() const {
	return mTransitions;
}

template <typename Number>
const typename HybridAutomaton<Number>::locationStateMap& HybridAutomaton<Number>::initialStates() const {
	return mInitialStates;
}

template <typename Number>
const typename HybridAutomaton<Number>::locationStateMap& HybridAutomaton<Number>::localBadStates() const {
	return mLocalBadStates;
}

template <typename Number>
const typename HybridAutomaton<Number>::setVector& HybridAutomaton<Number>::globalBadStates() const {
	return mGlobalBadStates;
}

template<typename Number>
const ReachabilitySettings<Number>& HybridAutomaton<Number>::reachabilitySettings() const {
	return mReachabilitySettings;
}

template <typename Number>
unsigned HybridAutomaton<Number>::dimension() const {
	if(mInitialStates.empty()) return 0;

	return ( mInitialStates.begin()->first->flow().cols() );
}

template <typename Number>
void HybridAutomaton<Number>::setLocations( const locationSet &_locs ) {
	mLocations = _locs;
}

template <typename Number>
void HybridAutomaton<Number>::setTransitions( const transitionSet &_trans ) {
	mTransitions = _trans;
}

template <typename Number>
void HybridAutomaton<Number>::setInitialStates( const locationStateMap& _states ) {
	mInitialStates = _states;
}

template <typename Number>
void HybridAutomaton<Number>::setLocalBadStates( const locationStateMap& _states ) {
	mLocalBadStates = _states;
}

template <typename Number>
void HybridAutomaton<Number>::setGlobalBadStates( const setVector& _states ) {
	mGlobalBadStates = _states;
}

template<typename Number>
void HybridAutomaton<Number>::setReachabilitySettings( const ReachabilitySettings<Number>& _settings) {
	mReachabilitySettings = _settings;
}

template <typename Number>
void HybridAutomaton<Number>::addLocation( Location<Number> *_location ) {
	mLocations.insert( _location );
}

template <typename Number>
void HybridAutomaton<Number>::addTransition( Transition<Number> *_transition ) {
	mTransitions.insert( _transition );
}

template <typename Number>
void HybridAutomaton<Number>::addInitialState( const State<Number>& _state ) {
	mInitialStates.insert( std::make_pair(_state.location, _state));
}

template <typename Number>
void HybridAutomaton<Number>::addLocalBadState( const State<Number>& _state ) {
	mLocalBadStates.insert(std::make_pair(_state.location, _state));
}

template <typename Number>
void HybridAutomaton<Number>::addGlobalBadState( const std::pair<matrix_t<Number>, vector_t<Number>>& _valuation ) {
	mGlobalBadStates.push_back(_valuation);
}

} // namespace hypro
