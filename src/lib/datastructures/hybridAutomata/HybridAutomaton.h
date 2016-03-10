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

namespace hypro {
template <typename Number>
class HybridAutomaton {
  private:
	typedef std::set<Location<Number>*> locationSet;
	typedef std::set<Transition<Number>*> transitionSet;
	typedef std::map<Location<Number>*, std::pair<matrix_t<Number>, vector_t<Number>>> initialStateMap;

  private:
	/**
	 * Member
	 */
	locationSet mLocations;
	transitionSet mTransitions;
	initialStateMap mInitialStates;

  public:
	/**
	 * Constructors & Destructor
	 */
	HybridAutomaton() {}
	HybridAutomaton( const HybridAutomaton& _hybrid );
	HybridAutomaton( const locationSet& _locs, const transitionSet& _trans,
					 const initialStateMap& _initialStates );

	virtual ~HybridAutomaton() {}

	/**
	 * Getter & Setter
	 */
	const locationSet& locations() const;
	const transitionSet& transitions() const;
	const initialStateMap& initialStates() const;
	unsigned dimension() const;

	void setLocations( const locationSet& _locs );
	void setTransitions( const transitionSet& _trans );
	void setInitialStates( const initialStateMap& _states );

	void addLocation( Location<Number>* _location );
	void addTransition( Transition<Number>* _transition );
	void addInitialState( Location<Number>* _location , const std::pair<matrix_t<Number>, vector_t<Number>>& _valuation );

	// copy assignment operator, TODO: implement via swap
	inline HybridAutomaton<Number>& operator=( const HybridAutomaton<Number>& _rhs ) {
		mLocations = _rhs.locations();
		mTransitions = _rhs.transitions();
		mInitialStates = _rhs.initialStates();
		return *this;
	}

	// move assignment operator, TODO: Implement
	//inline HybridAutomaton<Number>& operator=( HybridAutomaton<Number>&& _rhs ) {
	//
	//	return *this;
	//}

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
