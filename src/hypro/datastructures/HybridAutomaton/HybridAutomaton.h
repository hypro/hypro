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
#include "State.h"
#include "Transition.h"
#include "Condition.h"
//#include <hypro/types.h>
#include "../../types.h"
#include <map>

namespace hypro
{

template <typename Number>
class HybridAutomaton
{
  public:
    using locationSet = std::set<Location<Number>*>;
    using transitionSet = std::set<Transition<Number>*>;
    using locationStateMap = std::multimap<const Location<Number>*, State<Number>, locPtrComp<Number>>;
    using locationConditionMap = std::map<const Location<Number>*, Condition<Number>, locPtrComp<Number>>;
    using conditionVector = std::vector<Condition<Number>>;

  private:
    locationSet mLocations;
    transitionSet mTransitions;
    locationStateMap mInitialStates;
    locationConditionMap mLocalBadStates;
    conditionVector mGlobalBadStates;

  public:
    HybridAutomaton() {}
    HybridAutomaton(const HybridAutomaton<Number>& hybrid) = default;
    HybridAutomaton(HybridAutomaton<Number>&& hybrid) = default;
    HybridAutomaton(const locationSet& locs, const transitionSet& trans, const locationStateMap& initialStates);
    virtual ~HybridAutomaton() {}

    const locationSet& getLocations() const { return mLocations; }
    const transitionSet& getTransitions() const { return mTransitions; }
    const locationStateMap& getInitialStates() const { return mInitialStates; }
    const locationConditionMap& getLocalBadStates() const { return mLocalBadStates; }
    const conditionVector& getGlobalBadStates() const { return mGlobalBadStates; }
    unsigned dimension() const;

    void setLocations(const locationSet& locs) { mLocations = locs; }
    void setTransitions(const transitionSet& trans) { mTransitions = trans; }
    void setInitialStates(const locationStateMap& states) { mInitialStates = states; }
    void setLocalBadStates(const locationConditionMap& states) { mLocalBadStates = states; }
    void setGlobalBadStates(const conditionVector& states) { mGlobalBadStates = states; }

    void addLocation(Location<Number>* location) { mLocations.insert(location); }
    void addTransition(Transition<Number>* transition) { mTransitions.insert(transition); }
    void addInitialState(const State<Number>& state) { mInitialStates.insert(std::make_pair(state.getLocation(),state)); }
    void addLocalBadState(const Location<Number>* loc, const Condition& condition) { mLocalBadStates.insert(std::make_pair(loc,condition)); }
    void addGlobalBadState(const Condition<Number>& state) { mGlobalBadStates.push_back(state); }

    // copy assignment operator, TODO: implement via swap
    inline HybridAutomaton& operator=(const HybridAutomaton<Number>& rhs) = default;
    inline HybridAutomaton& operator=(HybridAutomaton<Number>&& rhs) = default;

    friend std::ostream& operator<<(std::ostream& ostr, const HybridAutomaton<Number>& a)
    {
#ifdef HYDRA_USE_LOGGING
        /*_ostr << "initial states: " << std::endl;
        for ( auto initialIT = a.initialStates().begin(); initialIT != a.initialStates().end(); ++initialIT ) {
            ostr << ( *initialIT ).first->id() << ": " << ( *initialIT ).second.first
                  << " <= " << ( *initialIT ).second.second << std::endl;
        }*/  // TODO
        ostr << "locations: " << std::endl;
        for (auto locationIT = a.getLocations().begin(); locationIT != a.getLocations().end(); ++locationIT) {
            ostr << **locationIT << std::endl;
        }
        ostr << "transitions: " << std::endl;
        for (const auto& transition : a.getTransitions()) {
            ostr << *transition << std::endl;
        }
#endif
        return ostr;
    }
};
}
