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
    enum EXP_FUNCT_TYPE { CONVERGENT, DIVERGENT, LINEAR, CONSTANT, UNDEFINED, INITIALIZED };

    template <typename Number>
    using Matrix = matrix_t<Number>;
    template <typename Number>
    using Vector = vector_t<Number>;
    template <typename Number>
    using DiagonalMatrix= Eigen::DiagonalMatrix<Number,Eigen::Dynamic>;
    using DiagonalMatrixdouble = Eigen::DiagonalMatrix<double, Eigen::Dynamic>;
    using BoolMatrix = matrix_t<bool>;
    //using BoolVector = vector_t<bool>;
    using ExpFunctionTypeStdVector = std::vector<EXP_FUNCT_TYPE>;
    //std::generate(vec.begin(), vec.end(), EXP_FUNCT_TYPE::INITIALIZED)

template <typename Number>
struct STindependentFunct {
  DiagonalMatrix<Number>        D;
  Vector<Number>                xinhom;
  ExpFunctionTypeStdVector      expFunctionType;
};
template <typename Number>
struct STflowpipeSegment {
  Matrix<Number>                V;
  Matrix<Number>                Vinv;
};
/** 
 * @brief   STallValues as struct for all static EVD values for constant flow of location
 *          input has to be representable as points for evaluation
 */
template <typename Number>
struct STallValues {
    STindependentFunct  <Number> mSTindependentFunct;
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

    void declare_structures(STallValues<Number> & mSTallValues, const int n);

    size_t countLinearAndRemember(const Matrix<Number>& A_in, const size_t dimension, 
        STallValues<Number>& mSTallvalues);
    void insertNonLinearAndClassify(const Matrix<Number>& A_in, const Vector<Number>& b_in, const size_t dimension, 
        Matrix<Number>& A_nonlinear, Vector<Number>& b_nonlinear, STallValues<Number>& mSTallvalues);
    void EigenvalueDecomposition(const Matrix<Number>& A_nonlinear, const size_t dimensionNonLinear, 
        const size_t CONDITION_LIMIT, Matrix<Number>& V_EVD, DiagonalMatrix<Number>& D_EVD, 
        Matrix<Number>& Vinv_EVD);
//Adjust EVD-results and b using b_in, b_nonlinear
    void adjustLinearAndEVDcomponents(
        const Matrix<Number>& V_EVD, const DiagonalMatrix<Number>& D_EVD, const Matrix<Number>& Vinv_EVD, 
        const Matrix<Number>& A_in, const Vector<Number>& b_nonlinear, const size_t dimension, 
        Matrix<Number>& V, Matrix<Number>& Vinv, 
        Vector<Number>& b_tr, STallValues<Number>& mSTallvalues);
    
    //void mark_x0isMin(Matrix<Number>& x_tr, const int n); //pair-wise comparing only
    //void swap_x0isMax(Matrix<Number>& x_tr, const int n); //pair-wise comparing only
  public:
    /**
	 * @brief      Default constructor.
	 */
	Transformation() = delete;
    /**
     * @brief      Constructor from hybrid automata to adjust automaton and transformation
     *             All static properties relating to the Hybrid Automaton 
     *             are stored in this class.
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
    

    //TODO clean up locations and transitions on desctructor

    void output_HybridAutomaton();    //TODO BROKEN? if invariants not set/empty

    /* 
     * @brief       adding transformedBadGlobalStates to transformedLocalBadStates
     *   [optional] call only by setting according flag to reachability analysis
     * TODO storage requirement setting/analysis
     * due to count(location)*sizeof(BadStates) instead of sizeof(BadState) storage requirement
     *
     * @param[in] _hybrid the original Hybrid Automaton (to check location ptrs against)
     */
    void addGlobalBadStates(const HybridAutomaton<Number>& _hybrid, const bool transform);

    //Getter for handling Automaton in Analysis non-const due to GlobalBadStates transformation
    HybridAutomaton<Number>& getTransformedHybridAutomaton() { return mTransformedHA; }
    //Map from newLoc to struct for evaluating location during time
    const locationComputationSTMap & getLocationComputationSTMap() { return mLocPtrtoComputationvaluesMap; }

};
} //namespace hypro

#include "Transformation.tpp"
