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
class ReachTreeNode;

class HybridAutomaton
{
  public:
    using locationSet = std::set<Location*>;
    using transitionSet = std::set<Transition*>;
    using locationStateMap = std::multimap<const Location*, State, locPtrComp>;
    using locationConditionMap = std::map<const Location*, Condition, locPtrComp>;
    using conditionVector = std::vector<Condition>;

  private:
    locationSet mLocations;
    transitionSet mTransitions;
    locationStateMap mInitialStates;
    locationConditionMap mLocalBadStates;
    conditionVector mGlobalBadStates;

  public:
    HybridAutomaton() {}
    HybridAutomaton(const HybridAutomaton& hybrid) = default;
    HybridAutomaton(HybridAutomaton&& hybrid) = default;
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

    void addLocation(Location* location) { mLocations.insert(location); }
    void addTransition(Transition* transition) { mTransitions.insert(transition); }
    void addInitialState(const State& state) { mInitialStates.insert(std::make_pair(state.getLocation(),state)); }
    void addLocalBadState(const Location* loc, const Condition& condition) { mLocalBadStates.insert(std::make_pair(loc,condition)); }
    void addGlobalBadState(const Condition& state) { mGlobalBadStates.push_back(state); }

    // copy assignment operator, TODO: implement via swap
    inline HybridAutomaton& operator=(const HybridAutomaton& rhs) = default;
    inline HybridAutomaton& operator=(HybridAutomaton&& rhs) = default;

    friend std::ostream& operator<<(std::ostream& ostr, const HybridAutomaton& a)
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
