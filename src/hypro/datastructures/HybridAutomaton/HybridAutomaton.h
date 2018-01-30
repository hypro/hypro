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
#include "HybridAutomatonComp.h"
#include "../../types.h"
#include "../../representations/GeometricObject.h"
#include "../../util/adaptions_eigen/adaptions_eigen.h"

#include <map>

namespace hypro
{

/**
 * @brief      Class for linear hybrid automata.
 * @tparam     Number  Number type.
 */
template <typename Number, typename State = State_t<Number,Number>>
class HybridAutomaton
{
  public:
    using locationSet = std::set<Location<Number>*>; /// Set of location pointers.
    using transitionSet = std::set<Transition<Number>*>; /// Set of transition pointers.
    using locationStateMap = std::multimap<const Location<Number>*, State>; /// Multi-map from location pointers to states.
    using locationConditionMap = std::map<const Location<Number>*, Condition<Number>>; /// Map from location pointers to conditions.
    using conditionVector = std::vector<Condition<Number>>; /// Vector of conditions.
    using variableVector = std::vector<std::string>; /// Vector of variables

  private:
    locationSet mLocations; 				/// The locations of the hybrid automaton.
    transitionSet mTransitions; 			/// The transitions of the hybrid automaton.
    locationStateMap mInitialStates; 		/// The set of initial states.
    locationConditionMap mLocalBadStates; 	/// The set of bad states which are bound to locations.
    conditionVector mGlobalBadStates; 		/// The set of bad states which are not bound to any location.
    variableVector mVariables;

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
    HybridAutomaton(const HybridAutomaton<Number,State>& hybrid) = default;

    /**
     * @brief      Move constructor.
     *
     * @param[in]  hybrid  The original hybrid automaton.
     */
    HybridAutomaton(HybridAutomaton<Number,State>&& hybrid) = default;
    HybridAutomaton(const locationSet& locs, const transitionSet& trans, const locationStateMap& initialStates);
    virtual ~HybridAutomaton() {
		// Without this we have a memory leak from HyproTransitionVisitor.
		// The leak will be patched later by using only references.
        while(!mTransitions.empty()) {
        	//auto toDelete = *mTransitions.begin();
            mTransitions.erase(mTransitions.begin());
            //delete toDelete;
        }
    }

    /**
     * @brief      Getter function.
     */
    ///@{
    //* @return The set of locations. */
    const locationSet& getLocations() const { return mLocations; }
    Location<Number>* getLocation(std::size_t id) const;
    Location<Number>* getLocation(std::string name) const;
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
    //* @return The vector of variables. */
    const variableVector& getVariables() const { return mVariables; }
    //* @return The set of all labels. */
    const std::set<Label> getLabels() const;
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
    void setVariables(const variableVector& variables) { mVariables = variables; }
    ///@}

    /**
     * @brief      Extension function.
     */
    ///@{
    void addLocation(Location<Number>* location) { mLocations.insert(location); }
    void addTransition(Transition<Number>* transition) { mTransitions.insert(transition); }
    void addInitialState(const State& state) { mInitialStates.insert(std::make_pair(state.getLocation(),state)); }
    void addLocalBadState(const Location<Number>* loc, const Condition<Number>& condition) { mLocalBadStates.insert(std::make_pair(loc,condition)); }
    void addGlobalBadState(const Condition<Number>& state) { mGlobalBadStates.push_back(state); }
    ///@}

    // copy assignment operator, TODO: implement via swap
    inline HybridAutomaton& operator=(const HybridAutomaton<Number,State>& rhs) = default;
    inline HybridAutomaton& operator=(HybridAutomaton<Number,State>&& rhs) = default;

    /**
     * @brief      Comparison for equality operator.
     * @param[in]  lhs   The left hand side.
     * @param[in]  rhs   The right hand side.
     * @return     True, if both automata are equal, false otherwise.
     */
    friend bool operator==( const HybridAutomaton<Number,State>& lhs, const HybridAutomaton<Number,State>& rhs ) {
    	return lhs.getLocations() == rhs.getLocations() &&
    			lhs.getTransitions() == rhs.getTransitions() &&
    			lhs.getInitialStates() == rhs.getInitialStates() &&
    			lhs.getLocalBadStates() == rhs.getLocalBadStates() &&
    			lhs.getGlobalBadStates() == rhs.getGlobalBadStates();
    }

    /**
     * @brief      Parallel Composition Operator.
     * @param[in]  lhs   The left hand side.
     * @param[in]  rhs   The right hand side.
     * @return     Return parallel composition of two Automata.
     */
    friend HybridAutomaton<Number, State> operator||(const HybridAutomaton<Number, State>& lhs, const HybridAutomaton<Number, State>& rhs) {
      std::cout << "||" << std::endl;

      HybridAutomaton<Number, State> ha;

      const variableVector& lhsVar = lhs.getVariables();
      const variableVector& rhsVar = rhs.getVariables();
      variableVector haVar;
      variableVector::size_type  i=0, j=0;
      while(i < lhsVar.size() and j < rhsVar.size()) {
        if (lhsVar.at(i) == rhsVar.at(j)) {
          haVar.push_back(lhsVar[i]);
          i++; j++;
          continue;
        }
        if (lhsVar.at(i) < rhsVar.at(j)) {
          haVar.push_back(lhsVar[i]);
          i++;
          continue;
        }
        if (lhsVar.at(i) > rhsVar.at(j)) {
          haVar.push_back(rhsVar[j]);
          j++;
          continue;
        }
      }
      for(; i < lhsVar.size(); i++) {
        haVar.push_back(lhsVar[i]);
      }
      for(; j < lhsVar.size(); j++) {
        haVar.push_back(lhsVar[j]);
      }
      ha.setVariables(haVar);


      std::cout << "locations & transisitons" << std::endl;
      LocationManager<Number>& manager = LocationManager<Number>::getInstance();

      for(const Location<Number>* locLhs : lhs.getLocations()) {
        for(const Location<Number>* locRhs : rhs.getLocations()) {
          Location<Number>* loc = parallelCompose(locLhs,locRhs,lhsVar,rhsVar,haVar);
          ha.addLocation(loc);
        }
      }

      std::cout << "trans" << std::endl;
      //build transisitons
      std::set<Label> lhsLabels = lhs.getLabels();
      std::set<Label> rhsLabels = rhs.getLabels();
      for(const auto lhsT: lhs.getTransitions()) {
        for(const auto rhsT: rhs.getTransitions()) {
          Transition<Number>* t = parallelCompose(lhsT, rhsT, lhsVar, rhsVar, haVar, ha, lhsLabels, rhsLabels);
          if(t) {
            ha.addTransition(t);
            (t->getSource())->addTransition(t);
          }
        }
      }



      // set initial states (//std:multimap<const Location<Number>*, State>;)
      std::cout << "set initial states" << std::endl;
      for(const auto initialStateLhs: lhs.getInitialStates()) {
        for(const auto initialStateRhs: rhs.getInitialStates()) {
          State state = parallelCompose(initialStateLhs.second,  initialStateRhs.second, lhsVar, rhsVar, haVar, ha);
          ha.addInitialState(state);
        }
      }

      //localBadstates
      //globalBAdstates

      return ha; //std::move???
    }

    /**
     * @brief      Combination Operator.
     * @param[in]  lhs   The left hand side.
     * @param[in]  rhs   The right hand side.
     * @return     Return compositional Automata of two Automata.
     */
    friend HybridAutomatonComp<Number, State> operator+(const HybridAutomaton<Number, State>& lhs, const HybridAutomaton<Number, State>& rhs) {
      HybridAutomatonComp<Number, State> hac;
      hac.addAutomata(lhs);
      hac.addAutomata(rhs);
      return hac;
    }

#ifdef HYPRO_LOGGING
    friend std::ostream& operator<<(std::ostream& ostr, const HybridAutomaton<Number,State>& a)
#else
    friend std::ostream& operator<<(std::ostream& ostr, const HybridAutomaton<Number,State>&)
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
