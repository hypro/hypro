/*
 * Class that describes a hybrid automaton.
 * File:   hybridAutomaton.h
 * Author: stefan & ckugler
 *
 * Created on April 30, 2014, 9:06 AM
 */

#pragma once

#include "Location.h"
#include "Transition.h"
#include "util.h"

namespace hypro {
template <typename Number, typename Representation>
class HybridAutomaton {
  private:
	typedef std::set<Location<Number>*> locationSet;
	typedef std::set<Transition<Number>*> transitionSet;

  private:
	/**
	 * Member
	 */
	locationSet mInitialLocations;
	locationSet mLocations;
	transitionSet mTransitions;
	Representation mInitialValuation;
	Representation mExtInputValuation;

  public:
	/**
	 * Constructors & Destructor
	 */
	HybridAutomaton() {}
	HybridAutomaton( const HybridAutomaton& _hybrid );
	HybridAutomaton( const locationSet _initLocs, const locationSet _locs, const transitionSet _trans,
					 Representation _initVal );

	virtual ~HybridAutomaton() {}

	/**
	 * Getter & Setter
	 */
	const locationSet& initialLocations() const;
	const locationSet& locations() const;
	const transitionSet& transitions() const;
	const Representation& initialValuation() const;
	const Representation& extInputValuation() const;
	unsigned dimension() const;

	void setInitialLocations( const locationSet& _initLocs );
	void setLocations( const locationSet& _locs );
	void setTransitions( const transitionSet& _trans );
	void setInitialValuation( const Representation& _val );
	void setExtInputValuation( const Representation& _extInputVal );

	void addLocation( Location<Number>* _location );
	void addTransition( Transition<Number>* _transition );

	// copy assignment operator, TODO: implement via swap
	inline HybridAutomaton<Number, Representation>& operator=( const HybridAutomaton<Number, Representation>& _rhs ) {
		mInitialLocations = _rhs.initialLocations();
		mLocations = _rhs.locations();
		mTransitions = _rhs.transitions();
		mInitialValuation = _rhs.initialValuation();
		mExtInputValuation = _rhs.extInputValuation();
		return *this;
	}

	// move assignment operator, TODO: Implement
	inline HybridAutomaton<Number, Representation>& operator=( HybridAutomaton<Number, Representation>&& _rhs ) {
		return *this;
	}

	friend std::ostream& operator<<( std::ostream& _ostr, const HybridAutomaton<Number, Representation>& _a ) {
		_ostr << "initial: " << std::endl;
		for ( auto initialIT = _a.initialLocations().begin(); initialIT != _a.initialLocations().end(); ++initialIT ) {
			_ostr << **initialIT << std::endl;
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
