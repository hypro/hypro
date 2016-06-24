/*
 * Class that describes a hybrid automaton.
 * @file   hybridAutomaton.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since 	2014-04-30
 * @version	2015-03-07
 */

#pragma once

#include "Location.h"
#include "Transition.h"
#include "algorithms/reachability/Settings.h"
#include <map>

namespace hypro {

template<typename Number>
struct State;

template <typename Number>
class HybridAutomaton {
  public:

  	using locationSet = std::set<Location<Number>*>;
	using transitionSet = std::set<Transition<Number>*>;
	using locationStateMap = std::multimap<Location<Number>*, State<Number>, locPtrComp<Number>>;
	using setVector = std::vector<std::pair<matrix_t<Number>, vector_t<Number>>>;
  private:
	/**
	 * Member
	 */
	locationSet mLocations;
	transitionSet mTransitions;
	locationStateMap mInitialStates;
	locationStateMap mLocalBadStates;
	setVector mGlobalBadStates;
	ReachabilitySettings<Number> mReachabilitySettings;

  public:
	/**
	 * Constructors & Destructor
	 */
	HybridAutomaton() {}
	HybridAutomaton( const HybridAutomaton& _hybrid );
	HybridAutomaton( const locationSet& _locs, const transitionSet& _trans,
					 const locationStateMap& _initialStates );

	virtual ~HybridAutomaton() {
		while(!mTransitions.empty()) {
			Transition<Number>* toDelete = *mTransitions.begin();
			mTransitions.erase(mTransitions.begin());
			delete toDelete;
		}
	}

	/**
	 * Getter & Setter
	 */
	const locationSet& locations() const;
	const transitionSet& transitions() const;
	const locationStateMap& initialStates() const;
	const locationStateMap& localBadStates() const;
	const setVector& globalBadStates() const;
	const ReachabilitySettings<Number>& reachabilitySettings() const;
	unsigned dimension() const;

	void setLocations( const locationSet& _locs );
	void setTransitions( const transitionSet& _trans );
	void setInitialStates( const locationStateMap& _states );
	void setLocalBadStates( const locationStateMap& _states );
	void setGlobalBadStates( const setVector& _states );
	void setReachabilitySettings( const ReachabilitySettings<Number>& _settings);

	void addLocation( Location<Number>* _location );
	void addTransition( Transition<Number>* _transition );
	void addInitialState( const State<Number>& _state );
	void addLocalBadState( const State<Number>& _state );
	void addGlobalBadState( const std::pair<matrix_t<Number>, vector_t<Number>>& _valuation );

	// copy assignment operator, TODO: implement via swap
	inline HybridAutomaton<Number>& operator=( const HybridAutomaton<Number>& _rhs ) {
		mLocations = _rhs.locations();
		mTransitions = _rhs.transitions();
		mInitialStates = _rhs.initialStates();
		mLocalBadStates = _rhs.localBadStates();
		mGlobalBadStates = _rhs.globalBadStates();
		mReachabilitySettings = _rhs.reachabilitySettings();
		return *this;
	}

	friend std::ostream& operator<<( std::ostream& _ostr, const HybridAutomaton<Number>& _a ) {
		_ostr << "initial states: " << std::endl;
		for ( auto initialIT = _a.initialStates().begin(); initialIT != _a.initialStates().end(); ++initialIT ) {
			_ostr << (*initialIT).first->id() << ": " << (*initialIT).second.first << " <= " << (*initialIT).second.second << std::endl;
		}
		_ostr << "locations: " << std::endl;
		for ( auto locationIT = _a.locations().begin(); locationIT != _a.locations().end(); ++locationIT ) {
			_ostr << **locationIT << std::endl;
		}
		_ostr << "transitions: " << std::endl;
		for ( const auto& transition : _a.transitions() ) {
			_ostr << *transition << std::endl;
		}
		return _ostr;
	}
};
}

#include "HybridAutomaton.tpp"
