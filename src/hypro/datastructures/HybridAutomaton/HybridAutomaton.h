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
#include "LocationManager.h"
#include "State.h"
#include "Transition.h"
#include "Condition.h"
#include "../../types.h"
#include "../../representations/GeometricObject.h"
#include <map>

namespace hypro
{

/**
 * @brief      Class for linear hybrid automata.
 * @tparam     Number  Number type.
 */
template <typename Number>
class HybridAutomaton
{
  public:
    using locationSet = std::set<Location<Number>*>; /// Set of location pointers.
    using transitionSet = std::set<Transition<Number>*>; /// Set of transition pointers.
    using locationStateMap = std::multimap<const Location<Number>*, State<Number,Number,ConstraintSet<Number>>>; /// Multi-map from location pointers to states.
    using locationConditionMap = std::map<const Location<Number>*, Condition<Number>>; /// Map from location pointers to conditions.
    using conditionVector = std::vector<Condition<Number>>; /// Vector of conditions.

  private:
    locationSet mLocations; 				/// The locations of the hybrid automaton.
    transitionSet mTransitions; 			/// The transitions of the hybrid automaton.
    locationStateMap mInitialStates; 		/// The set of initial states.
    locationConditionMap mLocalBadStates; 	/// The set of bad states which are bound to locations.
    conditionVector mGlobalBadStates; 		/// The set of bad states which are not bound to any location.

  public:
  	/**
  	 * @brief      Default constructor.
  	 */
    HybridAutomaton() {}

    /**
     * @brief      Copy constructor.
     *
     * @param[in]  hybrid  The original hybrid automaton.
     */
    HybridAutomaton(const HybridAutomaton<Number>& hybrid) = default;

    /**
     * @brief      Move constructor.
     *
     * @param[in]  hybrid  The original hybrid automaton.
     */
    HybridAutomaton(HybridAutomaton<Number>&& hybrid) = default;
    HybridAutomaton(const locationSet& locs, const transitionSet& trans, const locationStateMap& initialStates);
    virtual ~HybridAutomaton() {
		// Without this we have a memory leak from HyproTransitionVisitor.
		// The leak will be patched later by using only references.
        //while(!mTransitions.empty()) {
        //	auto toDelete = *mTransitions.begin();
        //    mTransitions.erase(mTransitions.begin());
        //    delete toDelete;
        //}
    }

    /**
     * @brief      Getter function.
     */
    ///@{
    //* @return The set of locations. */
    const locationSet& getLocations() const { return mLocations; }
    const Location<Number>* getLocation(std::size_t id) const;
    const Location<Number>* getLocation(std::string name) const;
    //* @return The set of transitions. */
    const transitionSet& getTransitions() const { return mTransitions; }
    //* @return The set of initial states. */
    const locationStateMap& getInitialStates() const { return mInitialStates; }
    //* @return The set of bad states bound to locations. */
    const locationConditionMap& getLocalBadStates() const { return mLocalBadStates; }
    //* @return The set of bad states which are not bound to locations. */
    const conditionVector& getGlobalBadStates() const { return mGlobalBadStates; }
    //* @return The state space dimension. */
    unsigned dimension() const;
    ///@}

    /**
     * @brief      Setter function.
     */
    ///@{
    void setLocations(const locationSet& locs) { mLocations = locs; }
    void setTransitions(const transitionSet& trans) { mTransitions = trans; }
    void setInitialStates(const locationStateMap& states) { mInitialStates = states; }
    void setLocalBadStates(const locationConditionMap& states) { mLocalBadStates = states; }
    void setGlobalBadStates(const conditionVector& states) { mGlobalBadStates = states; }
    ///@}

    /**
     * @brief      Extension function.
     */
    ///@{
    void addLocation(Location<Number>* location) { mLocations.insert(location); }
    void addTransition(Transition<Number>* transition) { mTransitions.insert(transition); }
    void addInitialState(const State<Number,Number,ConstraintSet<Number>>& state) { mInitialStates.insert(std::make_pair(state.getLocation(),state)); }
    void addLocalBadState(const Location<Number>* loc, const Condition<Number>& condition) { mLocalBadStates.insert(std::make_pair(loc,condition)); }
    void addGlobalBadState(const Condition<Number>& state) { mGlobalBadStates.push_back(state); }
    ///@}

    // copy assignment operator, TODO: implement via swap
    inline HybridAutomaton& operator=(const HybridAutomaton<Number>& rhs) = default;
    inline HybridAutomaton& operator=(HybridAutomaton<Number>&& rhs) = default;

    /**
     * @brief      Comparison for equality operator.
     * @param[in]  lhs   The left hand side.
     * @param[in]  rhs   The right hand side.
     * @return     True, if both automata are equal, false otherwise.
     */
    friend bool operator==( const HybridAutomaton<Number>& lhs, const HybridAutomaton<Number>& rhs ) {
    	return lhs.getLocations() == rhs.getLocations() &&
    			lhs.getTransitions() == rhs.getTransitions() &&
    			lhs.getInitialStates() == rhs.getInitialStates() &&
    			lhs.getLocalBadStates() == rhs.getLocalBadStates() &&
    			lhs.getGlobalBadStates() == rhs.getGlobalBadStates();
    }

#ifdef HYPRO_LOGGING
    friend std::ostream& operator<<(std::ostream& ostr, const HybridAutomaton<Number>& a)
#else
    friend std::ostream& operator<<(std::ostream& ostr, const HybridAutomaton<Number>&)
#endif
    {
#ifdef HYPRO_LOGGING
        /*_ostr << "initial states: " << std::endl;
        for ( auto initialIT = a.initialStates().begin(); initialIT != a.initialStates().end(); ++initialIT ) {
            ostr << ( *initialIT ).first->id() << ": " << ( *initialIT ).second.first
                  << " <= " << ( *initialIT ).second.second << std::endl;
        }*/  // TODO
        ostr << "initial states: " << std::endl;
        for(auto initialIt = a.getInitialStates().begin(); initialIt != a.getInitialStates().end(); ++initialIt){
            ostr << *((*initialIt).first) << ": " << (*initialIt).second << std::endl;
        }
        ostr << "locations: " << std::endl;
        for (auto locationIT = a.getLocations().begin(); locationIT != a.getLocations().end(); ++locationIT) {
            ostr << **locationIT << std::endl;
        }
        ostr << "transitions: " << std::endl;
        for (const auto& transition : a.getTransitions()) {
            ostr << *transition << std::endl;
        }
        ostr << "local bad states: " << std::endl;
        for(auto badStateIt = a.getLocalBadStates().begin(); badStateIt != a.getLocalBadStates().end(); ++badStateIt){
            ostr << *((*badStateIt).first) << ": " << (*badStateIt).second << std::endl;
        }
#endif
        return ostr;
    }
};
} // namespace hypro

#include "HybridAutomaton.tpp"
