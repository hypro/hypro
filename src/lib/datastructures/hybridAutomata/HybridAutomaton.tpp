#include "HybridAutomaton.h"

namespace hypro {

template <typename Number>
HybridAutomaton<Number>::HybridAutomaton( const HybridAutomaton &_hybrid )
	: mLocations( _hybrid.locations() )
	, mTransitions( _hybrid.transitions() )
	, mInitialStates( _hybrid.initialStates() )
	, mBadStates( _hybrid.badStates() )
{}

template <typename Number>
HybridAutomaton<Number>::HybridAutomaton( const locationSet& _locs,
														  const transitionSet& _trans, const locationSetMap& _initialStates )
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
const typename HybridAutomaton<Number>::locationSetMap& HybridAutomaton<Number>::initialStates() const {
	return mInitialStates;
}

template <typename Number>
const typename HybridAutomaton<Number>::locationSetMap& HybridAutomaton<Number>::badStates() const {
	return mBadStates;
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
void HybridAutomaton<Number>::setInitialStates( const locationSetMap& _states ) {
	mInitialStates = _states;
}

template <typename Number>
void HybridAutomaton<Number>::setBadStates( const locationSetMap& _states ) {
	mBadStates = _states;
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
void HybridAutomaton<Number>::addInitialState( Location<Number>* _location , const std::pair<matrix_t<Number>, vector_t<Number>>& _valuation ) {
	mInitialStates.insert(std::make_pair(_location, _valuation));
}

template <typename Number>
void HybridAutomaton<Number>::addBadState( Location<Number>* _location , const std::pair<matrix_t<Number>, vector_t<Number>>& _valuation ) {
	mBadStates.insert(std::make_pair(_location, _valuation));
}

} // namespace hypro
