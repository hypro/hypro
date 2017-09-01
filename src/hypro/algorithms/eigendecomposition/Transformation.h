 /**
  * @file Transformation.h
  */
#pragma once
#include "algorithms/reachability/Settings.h"
#include "datastructures/hybridAutomata/HybridAutomaton.h"
#include "datastructures/hybridAutomata/Location.h"
#include "datastructures/hybridAutomata/RawState.h"
#include "datastructures/hybridAutomata/Transition.h"
/**
 * @brief      Class for transformation of Hybrid Automata.
 *
 * @tparam     Number  The used number type.
 */

namespace hypro {

template <typename Number>
class Transformation {
  public:

  	using locationSet = std::set<Location<Number>*>;
	using transitionSet = std::set<Transition<Number>*>;
	using locationStateMap = std::multimap<Location<Number>*, RawState<Number>, locPtrComp<Number>>;
	using setVector = std::vector<std::pair<matrix_t<Number>, vector_t<Number>>>;
  private:

    //use structs here?

	//locationSet mLocations;
	//transitionSet mTransitions;
	//locationStateMap mInitialStates;
	//locationStateMap mLocalBadStates;
	//setVector mGlobalBadStates;
	//reachability::ReachabilitySettings<Number> mReachabilitySettings;

  public:
	/**
	 * @brief      Default constructor.
	 */
	Transformation() {}
	/**
	 * @brief      Copy constructor.
	 *
	 * @param[in]  _hybrid  The original transformation for an hybrid automaton.
	 */
	Transformation( const Transformation& _trafo );

//adding properties for pre-system analysis would make sense here
    /**
     * @brief      Constructor from hybrid automata to adjust automaton and transformation
     *
     * @param[in]  _hybrid  The original hybrid automaton.
     */
	//Transformation( HybridAutomaton<Number>& _hybrid );
    void transform( HybridAutomaton<Number>& _hybrid );

//  backtransformation(HybridAutomaton& _hybrid, const Transformation& _trafo );
//  retransform reults


};
} //namespace hypro

#include "Transformation.tpp"
