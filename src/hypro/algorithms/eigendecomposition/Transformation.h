 /**
  * @file Transformation.h
  */
#pragma once
#include "../../datastructures/HybridAutomaton/Settings.h"
#include "../../datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../representations/conversion/Converter.h"
//#include "../../datastructures/HybridAutomaton/Transition.h"
//#include "../../datastructures/HybridAutomaton/Location.h"
//#include "../../datastructures/HybridAutomaton/LocationManager.h"
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
    Vector<Number>              x0;
    Vector<Number>              x0_2;
};
template <typename Number>
struct STindependentFunct {
  DiagonalMatrix<Number>        D;
  Matrix<Number>                xinhom;
  Number                        delta;
  std::size_t                   deltalimit;
};
template <typename Number>
struct STdependentFunct {
  Matrix<Number>                xhom;
  Matrix<Number>                x_tr;
};
template <typename Number>
struct STevalFunctions {
  Matrix<Number>                deriv;
  BoolMatrix                    direct;
};
template <typename Number>
struct STflowpipeSegment {
  Matrix<Number>                V;
  Matrix<Number>                Vinv;
  std::vector<Vector<Number>>   upper;
  std::vector<Vector<Number>>   lower;
};
template <typename Number>
struct STallValues {
    STinputVectors      <Number> mSTinputVectors;
    STindependentFunct  <Number> mSTindependentFunct;
    STdependentFunct    <Number> mSTdependentFunct;
    STevalFunctions     <Number> mSTevalFunctions;
    STflowpipeSegment   <Number> mSTflowpipeSegment;
};

template <typename Number, typename Representation>
class Transformation {
  public:
  //TODO recheck if constLocPtr or just LocPtr better in map+multimap
  	using locationSet = std::set<Location<Number>*>;
	using transitionSet = std::set<Transition<Number>*>;
    using locationStateMap = std::multimap<const Location<Number>*, State<Number,ConstraintSet<Number>>, locPtrComp<Number>>; /// Multi-map from location pointers to states.
    using locationConditionMap = std::map<Location<Number>*, Condition<Number>, locPtrComp<Number>>;
    using conditionVector = std::vector<Condition<Number>>; /// Vector of conditions.
	using setVector = std::vector<std::pair<matrix_t<Number>, vector_t<Number>>>;
    
  private:
    //maps from original location to transformed organized as black/red tree
    std::map<const Location<Number>*,Location<Number>*, locPtrComp<Number> > mLocationPtrsMap;     
    std::map< Location<Number>*,STallValues<Number>, locPtrComp<Number>> mLocPtrtoComputationvaluesMap;
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

    void declare_structures(STallValues<Number> & mSTallValues, const int n);
    void mark_x0isMin(Matrix<Number>& x_tr, const int n);       //TODO reformulate struct [when multiple points
    void swap_x0isMax(Matrix<Number>& x_tr, const int n);       //TODO direct index call without vector swapping
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
	Transformation<Number,Representation> ( const Transformation& _trafo );

    //copy Transition, modify and insert to set
    //then insert to automaton
    //State --> linearTransformation 
    //Guards Condition
    //Reset --> Vector von ConstraintSets [Hpolytope]
    //Converter

    /**
     * @brief      Constructor from hybrid automata to adjust automaton and transformation
     *             adding properties for pre-system analysis would make sense here
     * @param[in]  _hybrid  The original hybrid automaton.
     * @param[in]  transformed_ha  The transformed hybrid automaton.
     */
	//Transformation( HybridAutomaton<Number>& _hybrid );
    Transformation<Number,Representation> (const HybridAutomaton<Number>& _hybrid);

    void output_HybridAutomaton();    //TODO BROKEN? if invariants not set/empty

//  backtransformation(HybridAutomaton& _hybrid, const Transformation& _trafo );
//  retransform reults

//template<typename Number>
//struct locPtrComp {
//    bool operator()(const Location<Number>* lhs, const Location<Number>* rhs) const { return (*lhs < *rhs); }
//};

};
} //namespace hypro

#include "Transformation.tpp"
