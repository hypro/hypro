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
 * @details	   The automaton owns all the locations and transitions. Newly created locations and transitions
 			   can only be added as unique pointers. If another class/object requests a location/transition, 
 			   then only normal pointers are returned. 
 */
template <typename Number, typename State = State_t<Number,Number>>
class HybridAutomaton
{
  public:
    using locationSet = std::set<std::unique_ptr<Location<Number>>, locPtrComp<Number>>; /// Set of unique location pointers.
    using transitionSet = std::set<std::unique_ptr<Transition<Number>>>; /// Set of unique transition pointers.
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
  	 * @brief      	Default constructor.
  	 */
    HybridAutomaton() {}

    /**
     * @brief      	Copy constructor.
     *
     * @param[in]  	hybrid  The original hybrid automaton.
     * @details 	This operation is costly as it performs deep copies
     */
    HybridAutomaton(const HybridAutomaton<Number,State>& hybrid);

    /**
     * @brief      	Move constructor.
     *
     * @param[in]  	hybrid  The original hybrid automaton.
     */
    HybridAutomaton(HybridAutomaton<Number,State>&& hybrid) = default;

    /**
     * @brief 		Constructor from locations, transitions and initial states
     * @param[in]	locs 			Set of locations
     * @param[in]	trans 			Set of transitions
     * @param[in] 	initialStates 	Map of initial states
     */
    HybridAutomaton(const locationSet& locs, const transitionSet& trans, const locationStateMap& initialStates);

    /**
     * @brief 		Destructor
     */
    virtual ~HybridAutomaton() {}

    /**
     * @brief 		Copy Assignment 
     *
     * @param[in]	rhs 	The original hybrid automaton
     * @details 	This operation is costly as it performs deep copies
     */
    HybridAutomaton& operator=(const HybridAutomaton<Number,State>& rhs);

    /**
     * @brief 		Move Assignment 
     *
     * @param[in]	rhs 	The original hybrid automaton
     */
    HybridAutomaton& operator=(HybridAutomaton<Number,State>&& rhs);

    /**
     * @brief      Getter function.
     */
    ///@{
    //* @return The set of locations. */
    const locationSet& getLocations() const { return mLocations; }
    Location<Number>* getLocation(const std::size_t hash) const;
    Location<Number>* getLocation(const std::string& name) const;
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
    void setLocations(locationSet& locs) { mLocations.swap(locs); }
    void setTransitions(transitionSet& trans) { mTransitions.swap(trans); } 
    void setInitialStates(const locationStateMap& states) { mInitialStates = states; }
    void setLocalBadStates(const locationConditionMap& states) { mLocalBadStates = states; }
    void setGlobalBadStates(const conditionVector& states) { mGlobalBadStates = states; }
    void setVariables(const variableVector& variables) { mVariables = variables; }
    ///@}

    /**
     * @brief      Extension function.
     */
    ///@{
    void addLocation(std::unique_ptr<Location<Number>>&& location);
    void addTransition(std::unique_ptr<Transition<Number>>&& transition);
    void addInitialState(const State& state) { mInitialStates.insert(std::make_pair(state.getLocation(),state)); }
    void addLocalBadState(const Location<Number>* loc, const Condition<Number>& condition) { mLocalBadStates.insert(std::make_pair(loc,condition)); }
    void addGlobalBadState(const Condition<Number>& state) { mGlobalBadStates.push_back(state); }
    ///@}

    void removeTransition(std::unique_ptr<Transition<Number>> toRemove);
    
    /**
     * @brief Decomposes an automaton into the components
     *  defined by decomposition. The vector should contain
     *  sets of variables that are at least syntactically
     *  independet to each other.
     */
    void decompose(std::vector<std::vector<size_t>> decomposition);

    /**
     * @brief      Reduces the automaton, i.e. removes Locations which are not connected to the automaton by transitions.
     */
    void reduce();

    /**
     * @brief Function which tests whether this can be the result of a parallel composition with rhs.
     * @details Used to verify the result of operator|| for hybrid automata. Checks whether this automaton can be the composed of rhs and some
     * (potentially empty) other composite.
     *
     * @param rhs Automaton which can be a component of this.
     * @return True, if this is composed of rhs and some (possibly empty) rest.
     */
    bool isComposedOf(const HybridAutomaton<Number,State>& rhs) const;

    std::string getDotRepresentation() const;

    std::string getStatistics() const;

    //TODO: replace this with operator== for sets of pointers to loc (if implemented this way, standard == operator of set is used,
    //which does not compare correctly 
    bool equals(const locationSet& lhs, const locationSet& rhs) const {
        if(lhs.size() != rhs.size()) return false;
        auto rhsIt = rhs.begin(); 
        for(auto lhsIt = lhs.begin(); lhsIt != lhs.end(); ++lhsIt){
            //std::cout << "now comparing " << (*(lhsIt))->hash() << " and " << (*(rhsIt))->hash() << std::endl;
            if(**lhsIt != **rhsIt){
                return false;
            }
            ++rhsIt;
        }
        return true;
    }
    
    /**
     * @brief      Comparison for equality operator.
     * @param[in]  lhs   The left hand side.
     * @param[in]  rhs   The right hand side.
     * @return     True, if both automata are equal, false otherwise.
     */
    friend bool operator==( const HybridAutomaton<Number,State>& lhs, const HybridAutomaton<Number,State>& rhs ) {
        //return lhs.getLocations() == rhs.getLocations() &&
        return lhs.equals(lhs.getLocations(),rhs.getLocations()) &&
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
    //This template is needed or else gcc spits out the warning -Wno-non-template-friend
    //Num represents Number and Stat represents State
    template<typename Num, typename Stat>
	friend HybridAutomaton<Num, Stat> operator||(const HybridAutomaton<Num, Stat>& lhs, const HybridAutomaton<Num, Stat>& rhs);
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
