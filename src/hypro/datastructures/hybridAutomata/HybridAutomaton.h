/**
 * @file HybridAutomaton.h
 */

#pragma once

#include "Location.h"
#include "Transition.h"
#include "algorithms/reachability/Settings.h"
#include <map>

namespace hypro {

template<typename Number>
struct RawState;


/**
 * @brief      Class for hybrid automata.
 *
 * @tparam     Number  The used number type.
 */
template <typename Number>
class HybridAutomaton {
  public:

  	using locationSet = std::set<Location<Number>*>;
	using transitionSet = std::set<Transition<Number>*>;
	using locationStateMap = std::multimap<Location<Number>*, RawState<Number>, locPtrComp<Number>>;
	using setVector = std::vector<std::pair<matrix_t<Number>, vector_t<Number>>>;
  private:

	locationSet mLocations;
	transitionSet mTransitions;
	locationStateMap mInitialStates;
	locationStateMap mLocalBadStates;
	setVector mGlobalBadStates;
	reachability::ReachabilitySettings<Number> mReachabilitySettings;

  public:

	/**
	 * @brief      Default constructor.
	 */
	HybridAutomaton() {}

	/**
	 * @brief      Copy constructor.
	 *
	 * @param[in]  _hybrid  The original hybrid automaton.
	 */
	HybridAutomaton( const HybridAutomaton& _hybrid );

	/**
	 * @brief      Constructor from a set of locations, a set of transitions and a map of initial states.
	 *
	 * @param[in]  _locs           The locations.
	 * @param[in]  _trans          The transitions.
	 * @param[in]  _initialStates  The initial states.
	 */
	HybridAutomaton( const locationSet& _locs, const transitionSet& _trans,
					 const locationStateMap& _initialStates );

	/**
	 * @brief      Destroys the object.
	 */
	virtual ~HybridAutomaton() {
		while(!mTransitions.empty()) {
			Transition<Number>* toDelete = *mTransitions.begin();
			mTransitions.erase(mTransitions.begin());
			//delete toDelete;
		}
	}

	const locationSet& locations() const;
	const transitionSet& transitions() const;
	const locationStateMap& initialStates() const;
	const locationStateMap& localBadStates() const;
	const setVector& globalBadStates() const;
	const reachability::ReachabilitySettings<Number>& reachabilitySettings() const;
	unsigned dimension() const;
	void addArtificialDimension();

	/**
	 * @brief      Sets the locations.
	 *
	 * @param[in]  _locs  The locations.
	 */
	void setLocations( const locationSet& _locs );

	/**
	 * @brief      Sets the transitions.
	 *
	 * @param[in]  _trans  The transitions.
	 */
	void setTransitions( const transitionSet& _trans );

	/**
	 * @brief      Sets the initial states.
	 *
	 * @param[in]  _states  The states.
	 */
	void setInitialStates( const locationStateMap& _states );

	/**
	 * @brief      Sets the local bad states.
	 *
	 * @param[in]  _states  The states.
	 */
	void setLocalBadStates( const locationStateMap& _states );

	/**
	 * @brief      Sets the global bad states.
	 *
	 * @param[in]  _states  The states.
	 */
	void setGlobalBadStates( const setVector& _states );

	/**
	 * @brief      Sets the reachability settings.
	 *
	 * @param[in]  _settings  The settings.
	 */
	void setReachabilitySettings( const reachability::ReachabilitySettings<Number>& _settings);

	/**
	 * @brief      Adds a location.
	 *
	 * @param      _location  The location.
	 */
	void addLocation( Location<Number>* _location );

	/**
	 * @brief      Adds a transition.
	 *
	 * @param      _transition  The transition.
	 */
	void addTransition( Transition<Number>* _transition );

	/**
	 * @brief      Adds an initial state.
	 *
	 * @param[in]  _state  The state.
	 */
	void addInitialState( const RawState<Number>& _state );

	/**
	 * @brief      Adds a local bad state.
	 *
	 * @param[in]  _state  The state.
	 */
	void addLocalBadState( const RawState<Number>& _state );

	/**
	 * @brief      Adds a global bad state as a variable valuation described by a set of linear constraints.
	 *
	 * @param[in]  _valuation  The valuation.
	 */
	void addGlobalBadState( const std::pair<matrix_t<Number>, vector_t<Number>>& _valuation );

	/**
	 * @brief      Copy assignment operator.
	 *
	 * @param[in]  _rhs  The right hand side.
	 *
	 * @return     A reference to the new object.
	 */
	inline HybridAutomaton<Number>& operator=( const HybridAutomaton<Number>& _rhs ) {
		mLocations = _rhs.locations();
		mTransitions = _rhs.transitions();
		mInitialStates = _rhs.initialStates();
		mLocalBadStates = _rhs.localBadStates();
		mGlobalBadStates = _rhs.globalBadStates();
		mReachabilitySettings = _rhs.reachabilitySettings();
		return *this;
	}

	/**
	 * @brief      Outstream operator.
	 *
	 * @param      _ostr  The ostr.
	 * @param[in]  _a     The object.
	 *
	 * @return     A reference to the outstream.
	 */
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
