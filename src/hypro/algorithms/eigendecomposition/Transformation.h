 /**
  * @file Transformation.h
  * @author Jan Philipp Hafer
  */
#pragma once
#include "../../datastructures/HybridAutomaton/Settings.h"
#include "../../datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../representations/conversion/Converter.h"
//#include "../../util/adaptions_eigen/adaptions_eigen.h"
//#include "parser/antlr4-flowstar/ParserWrapper.h"
//#include "../../datastructures/HybridAutomaton/Transition.h"
//#include "../../datastructures/HybridAutomaton/Location.h"
//#include "../../datastructures/HybridAutomaton/LocationManager.h"
#include <Eigen/Eigenvalues>
#include <Eigen/Dense>
#include <Eigen/SVD>
#include <Eigen/Core>
/**
 * @brief      Class for transformation of Hybrid Automata for eigendecomposition reachability.
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
    using DiagonalMatrixdouble = Eigen::DiagonalMatrix<double, Eigen::Dynamic>;
    using BoolMatrix = matrix_t<bool>;
    using BoolVector = vector_t<bool>;
//template <typename Number>
//struct STinputVectors {   
//    Vector<Number>              x0;
//    Vector<Number>              x0_2;
//};
template <typename Number>
struct STindependentFunct {
  DiagonalMatrix<Number>        D;
  Vector<Number>                xinhom;
  BoolVector                    convergent;
//  Number                        delta;
//  std::size_t                   deltalimit;
};
//template <typename Number>
//struct STdependentFunct {
//  Matrix<Number>                xhom;
//  Matrix<Number>                x_tr;
//};
//template <typename Number>
//struct STevalFunctions {
//  Matrix<Number>                deriv;
//  BoolMatrix                    direct;
//};
template <typename Number>
struct STflowpipeSegment {
  Matrix<Number>                V;
  Matrix<Number>                Vinv;
//  std::vector<Vector<Number>>   upper;
//  std::vector<Vector<Number>>   lower;
};
/** 
 * @brief   STallValues as struct for all according values 
 *          for a location of an hybrid automaton 
 * NOTE     will be later used for setting dynamically values according to input
 *          input has to be representable as points for evaluation
 */
template <typename Number>
struct STallValues {
    //STinputVectors      <Number> mSTinputVectors;
    STindependentFunct  <Number> mSTindependentFunct;
//    STdependentFunct    <Number> mSTdependentFunct;
//    STevalFunctions     <Number> mSTevalFunctions;
    STflowpipeSegment   <Number> mSTflowpipeSegment;
};

template <typename Number>
class Transformation {
  public:
  	using locationSet = std::set<Location<Number>*>;
	using transitionSet = std::set<Transition<Number>*>;
    using locationStateMap = std::multimap<const Location<Number>*, State<Number,ConstraintSet<Number>>, locPtrComp<Number>>;
    using locationConditionMap = std::map<Location<Number>*, Condition<Number>, locPtrComp<Number>>;
    using conditionVector = std::vector<Condition<Number>>; /// Vector of conditions.
	using setVector = std::vector<std::pair<matrix_t<Number>, vector_t<Number>>>;
//Map of old location to new location 
    using locationPtrMap = std::map<const Location<Number>*,Location<Number>*, locPtrComp<Number> >;
//Location<Number>* points to locations of transformed Hybrid Automaton, struct for computation
    using locationComputationSTMap = std::map< Location<Number>*,STallValues<Number>, locPtrComp<Number>>;
  private:
    //maps from original location to transformed organized as black/red tree
    //std::map<const Location<Number>*,Location<Number>*, locPtrComp<Number> > mLocationPtrsMap;
    locationPtrMap mLocationPtrsMap;
    locationComputationSTMap mLocPtrtoComputationvaluesMap;
    HybridAutomaton<Number> mTransformedHA;
    bool globalBadStatesTransformed = false;

//helper functions
    bool keyCompare(locationSet& lhs, locationPtrMap& rhs);
    void declare_structures(STallValues<Number> & mSTallValues, const int n);
    void mark_x0isMin(Matrix<Number>& x_tr, const int n); //TODO reformulate struct [when multiple points
    void swap_x0isMax(Matrix<Number>& x_tr, const int n); //TODO direct index call without vector swapping
  public:
    /**
	 * @brief      Default constructor.
	 */
	Transformation() = delete;
    /**
     * @brief      Constructor from hybrid automata to adjust automaton and transformation
     *             All static properties  relating to the Hybrid Automaton 
     *             are stored in this class.
     *        TODO adding properties for pre-system analysis would make sense here
     * @param[in]  _hybrid  The original hybrid automaton.
     */
	//Transformation( HybridAutomaton<Number>& _hybrid );
    Transformation<Number> (const HybridAutomaton<Number>& _hybrid);
    /**
	 * @brief      Copy constructor.
	 *
	 * @param[in]  _hybrid  The original transformation for an hybrid automaton.
	 */
//TODO implement?
	Transformation<Number> (const Transformation<Number>& _trafo);
    
    /**
     * @brief       Analyzing Exponential Function and writing values accordingly to struct
     */
    void analyzeExponentialFunctions();
    /*
     * @brief       Analyzing State and create according vertices with boxes
     */
    //analyzeInput();

    //computeFirstSegment();

    //computeFlow();

    //TODO clean up locations and transitions on desctructor

    void output_HybridAutomaton();    //TODO BROKEN? if invariants not set/empty

    /* 
     * @brief       adding transformedBadGlobalStates to transformedLocalBadStates
     *   [optional] call only by setting according flag to reachability analysis
     * TODO storage requirement setting/analysis
     * due to count(location)*sizeof(BadStates) instead of sizeof(Badstead) storage requirement
     *
     * @param[in] _hybrid the original Hybrid Automaton (to check location ptrs against)
     */
    void transformGlobalBadStates(const HybridAutomaton<Number>& _hybrid);


    //Getter for handling Automaton in Analysis TODO why not const?
    HybridAutomaton<Number>& getTransformedHybridAutomaton() { return mTransformedHA; }
    //Map from newLoc to struct for evaluating location during time
    const locationComputationSTMap & getLocationComputationSTMap() { return mLocPtrtoComputationvaluesMap; }


//  backtransformation(HybridAutomaton& _hybrid, const Transformation& _trafo );
//  retransform reults

    //compute Flow in Location
//    void Transformation<Number,Representation>::computeFlowinLocation(Location* LocPtr);

};
} //namespace hypro

#include "Transformation.tpp"
