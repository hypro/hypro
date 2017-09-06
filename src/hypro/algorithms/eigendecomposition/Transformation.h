 /**
  * @file Transformation.h
  */
#pragma once
#include "algorithms/reachability/Settings.h"
#include "datastructures/hybridAutomata/HybridAutomaton.h"
#include "datastructures/hybridAutomata/Location.h"
#include "datastructures/hybridAutomata/RawState.h"
#include "datastructures/hybridAutomata/Transition.h"
#include <Eigen/Eigenvalues>
#include <Eigen/Dense>
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
    
    using Matrix = matrix_t<Number>;
    using Vector = vector_t<Number>;
    using DiagonalMatrix = Eigen::DiagonalMatrix<Number,Eigen::Dynamic>;
    using BoolMatrix = matrix_t<bool>;
    
    struct Independent_part_funct {
        DiagonalMatrix D;
        Matrix xinhom;
        Number delta;
        std::size_t deltalimit;
    };
    struct Dependent_part_funct {
        Matrix xhom;
        Matrix x_tr;
    };
    struct Eval_functions {
        Matrix deriv;
        BoolMatrix direct;
    };
  private:
    std::map<locationSet, locationSet> maplLocations; //maps from original location to transformed organized as black/red tree
    //std::map<ptr_originalHybAuto,ptr_transformedHybAuto>
    
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
	Transformation() = delete;
    /**
	 * @brief      Copy constructor.
	 *
	 * @param[in]  _hybrid  The original transformation for an hybrid automaton.
	 */
	Transformation<Number> ( const Transformation& _trafo );

    /**
     * @brief      Constructor from hybrid automata to adjust automaton and transformation
     *             adding properties for pre-system analysis would make sense here
     * @param[in]  _hybrid  The original hybrid automaton.
     * @param[in]  transformed_ha  The transformed hybrid automaton.
     */
	//Transformation( HybridAutomaton<Number>& _hybrid );
    Transformation<Number> (const HybridAutomaton<Number>& _hybrid, HybridAutomaton<Number>& transformed_ha);

//  backtransformation(HybridAutomaton& _hybrid, const Transformation& _trafo );
//  retransform reults


};
} //namespace hypro

#include "Transformation.tpp"
