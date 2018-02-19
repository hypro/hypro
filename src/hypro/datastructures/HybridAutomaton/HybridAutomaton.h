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
		//std::cout << "||" << std::endl;

		HybridAutomaton<Number, State> ha;

		const variableVector& lhsVar = lhs.getVariables();
		const variableVector& rhsVar = rhs.getVariables();
		std::map<unsigned, std::pair<unsigned,unsigned>> sharedVars;

		//std::cout << "lhs variables: ";
		//for(auto a : lhsVar) { std::cout << a << " "; }
		//std::cout << std::endl;
		//std::cout << "rhs variables: ";
		//for(auto a : rhsVar) { std::cout << a << " "; }
		//std::cout << std::endl;

		variableVector haVar;
		variableVector::size_type  i=0, j=0;
		while(i < lhsVar.size() and j < rhsVar.size()) {
		if (lhsVar.at(i) == rhsVar.at(j)) {
			//std::cout << "same var, add " << lhsVar[i] << std::endl;
			haVar.push_back(lhsVar[i]);
			i++; j++;
			continue;
		}
		if (lhsVar.at(i) < rhsVar.at(j)) {
			//std::cout << "push left first " << lhsVar.at(i) << std::endl;
			haVar.push_back(lhsVar[i]);
			i++;
			continue;
		}
		if (lhsVar.at(i) > rhsVar.at(j)) {
			//std::cout << "push right first " << rhsVar.at(j) << std::endl;
			haVar.push_back(rhsVar[j]);
			j++;
			continue;
		}
		}
		for(; i < lhsVar.size(); i++) {
			//std::cout << "fill left: " << lhsVar[i] << std::endl;
			haVar.push_back(lhsVar[i]);
		}
		for(; j < rhsVar.size(); j++) {
			//std::cout << "fill right: " << rhsVar[j] << std::endl;
			haVar.push_back(rhsVar[j]);
		}
		ha.setVariables(haVar);

		//std::cout << "Variables: ";
		//for(auto a : haVar) { std::cout << a << " "; }
		//std::cout << "locations & transisitons" << std::endl;


		// find shared variables
		for(std::size_t i = 0; i != haVar.size(); ++i) {
			bool left = false;
			bool right = false;
			std::size_t l = 0;
			std::size_t r = 0;
			while(l != lhsVar.size()) {
				if(lhsVar[l] == haVar[i]){
					left = true;
					break;
				}
				++l;
			}
			while(r != rhsVar.size()) {
				if(rhsVar[r] == haVar[i]){
					right = true;
					break;
				}
				++r;
			}
			if(left && right) {
				//std::cout << "Shared var at " << i << " corresponds to (" << l << "," << r << ")" << std::endl;
				sharedVars[i] = std::make_pair(l,r);
			}
		}
		//std::cout << "Detected " << sharedVars.size() << " shared variables." << std::endl;

		for(const Location<Number>* locLhs : lhs.getLocations()) {
			for(const Location<Number>* locRhs : rhs.getLocations()) {
				Location<Number>* loc = parallelCompose(locLhs,locRhs,lhsVar,rhsVar,haVar);
				ha.addLocation(loc);
			}
		}

		//std::cout << "trans" << std::endl;
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

		// non-synchronizing transitions in each component
		// fix rhs first
		for(const auto lhsT: lhs.getTransitions()) {
			if(lhsT->getLabels().empty()) {
				for(const auto loc : rhs.getLocations()) {
					//std::cout << "Potential transition " << lhsT->getSource()->getName() << "_" << loc->getName() << " -> " << lhsT->getTarget()->getName() << "_" << loc->getName() << std::endl;
					//std::cout << "Original reset: " << lhsT->getReset().getMatrix() << " and " << lhsT->getReset().getVector() << std::endl;
					Transition<Number>* tmp = new Transition<Number>(loc,loc);
					// TODO: temporary test -> fix!
					//tmp->setReset();
					Reset<Number> tmpReset = Reset<Number>(matrix_t<Number>::Identity(rhsVar.size(), rhsVar.size()), vector_t<Number>::Zero(rhsVar.size()));
					if(!sharedVars.empty()) {
						// Attention: This is a temporary solution. Naturally, we would need to replicate the reset on the shared variables to create
						// an admissible combined reset.
						// Todo: iterate over rows, then over cols (only the ones which correspond to shared vars) and set the resets accordingly.

						//std::cout << "Have " << sharedVars.size() << " shared variables." << std::endl;
						for(auto shdIt = sharedVars.begin(); shdIt != sharedVars.end(); ++shdIt) {
							//std::cout << "update row " << shdIt->second.second << std::endl;
							for(auto colIt = sharedVars.begin(); colIt != sharedVars.end(); ++colIt) {
								tmpReset.rGetMatrix()(shdIt->second.second, colIt->second.second) = lhsT->getReset().getMatrix()(shdIt->second.first,colIt->second.first);
							}
							tmpReset.rGetVector()(shdIt->second.second) = lhsT->getReset().getVector()(shdIt->second.first);
						}
					}

					//std::cout << "tmpreset after update: " << tmpReset << std::endl;

					//tmp->setReset(combine(lhsT->getReset(),tmpReset,haVar,lhsVar,rhsVar));
					tmp->setReset(tmpReset);
					tmp->setAggregation(lhsT->getAggregation());

					Transition<Number>* t = parallelCompose(lhsT, tmp, lhsVar, rhsVar, haVar, ha, lhsLabels, rhsLabels);
					if(t) {
						//std::cout << "Add." << std::endl;
						ha.addTransition(t);
						(t->getSource())->addTransition(t);
					}
				}
			}
		}
		// fix lhs
		for(const auto rhsT: rhs.getTransitions()) {
				if(rhsT->getLabels().empty()) {
					for(const auto loc : lhs.getLocations()) {
						//std::cout << "Potential transition " << loc->getName()<< "_" << rhsT->getSource()->getName() << " -> " << loc->getName() << "_" << rhsT->getTarget()->getName() << std::endl;
						Transition<Number>* tmp = new Transition<Number>(loc,loc);
						// TODO: temporary test -> fix!
						Reset<Number> tmpReset = Reset<Number>(matrix_t<Number>::Identity(lhsVar.size(), lhsVar.size()), vector_t<Number>::Zero(lhsVar.size()));
						if(!sharedVars.empty()) {
							// Attention: This is a temporary solution. Naturally, we would need to replicate the reset on the shared variables to create
							// an admissible combined reset.
							for(auto shdIt = sharedVars.begin(); shdIt != sharedVars.end(); ++shdIt) {
								//std::cout << "update row " << shdIt->second.second << std::endl;
								for(auto colIt = sharedVars.begin(); colIt != sharedVars.end(); ++colIt) {
									tmpReset.rGetMatrix()(shdIt->second.first, colIt->second.first) = rhsT->getReset().getMatrix()(shdIt->second.second,colIt->second.second);
								}
								tmpReset.rGetVector()(shdIt->second.first) = rhsT->getReset().getVector()(shdIt->second.second);
							}
						}

						tmp->setReset(combine(rhsT->getReset(),tmpReset,haVar,rhsVar,lhsVar));
						tmp->setAggregation(rhsT->getAggregation());

						Transition<Number>* t = parallelCompose(tmp, rhsT, lhsVar, rhsVar, haVar, ha, lhsLabels, rhsLabels);
						if(t) {
							//std::cout << "Add." << std::endl;
							ha.addTransition(t);
							(t->getSource())->addTransition(t);
			        	}
					}
				}
		}



		// set initial states (//std:multimap<const Location<Number>*, State>;)
		//std::cout << "set initial states" << std::endl;
		for(const auto initialStateLhs: lhs.getInitialStates()) {
			for(const auto initialStateRhs: rhs.getInitialStates()) {
				State state = parallelCompose(initialStateLhs.second,  initialStateRhs.second, lhsVar, rhsVar, haVar, ha);
				ha.addInitialState(state);
			}
		}

		//localBadstates
		//globalBAdstates

		// remove non-reachable locations and transitions.
		ha.reduce();

		return ha; //std::move??? -> no, prevents copy-elision!
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
