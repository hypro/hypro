 /**
  * @file Transformation.h
  */
#pragma once

#include "datastructures/hybridAutomata/HybridAutomaton.h"
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

};
} //namespace hypro

#include "Transformation.tpp"
