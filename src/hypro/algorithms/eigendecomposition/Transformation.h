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
    using Matrix = matrix_t<Number>;
    template <typename Number>
    using Vector = vector_t<Number>;
    template <typename Number>
    using DiagonalMatrix= Eigen::DiagonalMatrix<Number,Eigen::Dynamic>;
    using BoolMatrix = matrix_t<bool>;
/*** STallValues as struct for all according value for a location of an hybrid automaton
 *      structs of structs can somehow not inherit <Number> ??
 *      reason for this use is to initialize all of them with 1 linetemplate <class Number>
 */
template <typename Number>
struct STinputVectors {   
    Vector<Number> x0;
    Vector<Number> x0_2;
};
template <typename Number>
struct STindependentFunct {
  DiagonalMatrix<Number> D;
  Matrix<Number> xinhom;
  Number delta;
  std::size_t deltalimit;
};
template <typename Number>
struct STdependentFunct {
  Matrix<Number> xhom;
  Matrix<Number> x_tr;
};
template <typename Number>
struct STevalFunctions {
  Matrix<Number> deriv;
  BoolMatrix direct;
};
template <typename Number>
struct STflowpipeSegment {
  std::vector<Vector<Number>> upper;
  std::vector<Vector<Number>> lower;
};
template <typename Number>
struct STallValues {
    STinputVectors      <Number> mSTinputVectors;
    STindependentFunct  <Number> mSTindependentFunct;
    STdependentFunct    <Number> mSTdependentFunct;
    STevalFunctions     <Number> mSTevalFunctions;
    STflowpipeSegment   <Number> mSTflowpipeSegment;
};

template <typename Number>
class Transformation {
  public:
  	using locationSet = std::set<Location<Number>*>;
	using transitionSet = std::set<Transition<Number>*>;
	using locationStateMap = std::multimap<Location<Number>*, RawState<Number>, locPtrComp<Number>>;
	using setVector = std::vector<std::pair<matrix_t<Number>, vector_t<Number>>>;
    
  private:
    std::map<locationSet, locationSet> maplLocations; //maps from original location to transformed organized as black/red tree
    HybridAutomaton<Number> mTransformedHA;
    //TODO std::map with struct for each location
    //STinputVectors      mSTinputVectors;    //?? needed ?? models ??
    //STflowpipeSegment   mSTflowpipeSegment;
    //std::map<ptr_originalHybAuto,ptr_transformedHybAuto>
	//void declare_structures(const int n, 
    //    STindependentFunct& mSTindependentFunct,
    //    STdependentFunct  & mSTdependentFunct,
    //    STevalFunctions   & mSTevalFunctions );
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
    Transformation<Number> (const HybridAutomaton<Number>& _hybrid);

//  backtransformation(HybridAutomaton& _hybrid, const Transformation& _trafo );
//  retransform reults


};
} //namespace hypro

#include "Transformation.tpp"
