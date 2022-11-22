/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * @file Transformation.h
 * @author Jan Philipp Hafer
 */
#pragma once
#include "../../datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../datastructures/reachability/Settings.h"
#include "../../representations/conversion/Converter.h"

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Eigenvalues>
#include <eigen3/Eigen/SVD>

namespace hypro {
// EVD possible values of Euler functions
enum EXP_FUNCT_TYPE { CONVERGENT,
					  DIVERGENT,
					  LINEAR,
					  CONSTANT,
					  UNDEFINED,
					  INITIALIZED };

template <typename Number>
using Matrix = matrix_t<Number>;
template <typename Number>
using Vector = vector_t<Number>;
template <typename Number>
using DiagonalMatrix = Eigen::DiagonalMatrix<Number, Eigen::Dynamic>;
using DiagonalMatrixdouble = Eigen::DiagonalMatrix<double, Eigen::Dynamic>;
using BoolMatrix = matrix_t<bool>;
using ExpFunctionTypeStdVector = std::vector<EXP_FUNCT_TYPE>;
// STRUCT containing runtime-relevant information for the EVD
template <typename Number>
struct STindependentFunct {
	DiagonalMatrix<Number> D;
	Vector<Number> xinhom;
	ExpFunctionTypeStdVector expFunctionType;
};
// STRUCT containing construction and initializing information for the EVD
template <typename Number>
struct STflowpipeSegment {
	Matrix<Number> V;
	Matrix<Number> Vinv;
	Matrix<Number> trafoInput;
};
/**
 * @brief   STallValues as struct for all for reachability analysis relevant EVD values for constant flow of location
 *          input vertices have to be representable as points for evaluation
 */
template <typename Number>
struct STallValues {
	STindependentFunct<Number> mSTindependentFunct;
	STflowpipeSegment<Number> mSTflowpipeSegment;
};
/**
 * @brief      Class for transformation of Hybrid Automata for Eigenvalue Decomposition(EVD) forward reachability analysis.
 * @tparam     Number  The used number type.
 */
template <typename Number>
class Transformation {
  public:
	using Location = Location<Number>;
	using locationVector = std::vector<Location*>;
	using transitionVector = std::vector<Transition<Location>*>;
	using locationStateMap = typename HybridAutomaton<Number>::locationStateMap;
	using locationConditionMap = std::map<Location<Number>*, Condition<Number>, locPtrComp<Number>>;
	using conditionVector = std::vector<Condition<Number>>;	 /// Vector of conditions.
	using setVector = std::vector<std::pair<matrix_t<Number>, vector_t<Number>>>;
	// Map from old location to new location transformed into the Eigenspace
	using locationPtrMap = std::map<const Location<Number>*, Location<Number>*, locPtrComp<Number>>;
	// Location<Number>* points to locations of transformed Hybrid Automaton with according values
	using locationComputationSTMap = std::map<Location<Number>*, STallValues<Number>, locPtrComp<Number>>;

  private:
	locationPtrMap mLocationPtrsMap;
	locationComputationSTMap mLocPtrtoComputationvaluesMap;
	HybridAutomaton<Number> mTransformedHA;
	bool globalBadStatesTransformed = false;
	// initializing geometric objects for EVD with according size
	void declare_structures( STallValues<Number>& mSTallValues, const int n );

	// count linear terms in A_in and set some properties accordingly in mSTallvalues
	size_t countLinearAndRemember( const Matrix<Number>& A_in, const size_t dimension,
								   STallValues<Number>& mSTallvalues );
	// inserting A_nonlinear terms from A_in and b_in respectively and classify linearity in mSTallvalues
	void insertNonLinearAndClassify( const Matrix<Number>& A_in, const Vector<Number>& b_in, const size_t dimension,
									 Matrix<Number>& A_nonlinear, Vector<Number>& b_nonlinear, STallValues<Number>& mSTallvalues );
	// run EVD on A_nonlinear checking CONDITION_LIMIT returning result in V_EVD,D_EVD,Vinv_EVD
	void EigenvalueDecomposition( const Matrix<Number>& A_nonlinear, const size_t dimensionNonLinear,
								  const size_t CONDITION_LIMIT, Matrix<Number>& V_EVD, DiagonalMatrix<Number>& D_EVD,
								  Matrix<Number>& Vinv_EVD );
	// use EVD results adjusting V,Vinv,D accordingly to be of full rang to use implemented methods
	// V,Vinv,D are written to mSTallvalues to be accessible for reachability analysis
	// NOTE: this is a quick fix, but one could adapt the reachability analysis for the linear/constant terms accordingly saving computation effort etc
	void adjustLinearAndEVDcomponents(
		  const Matrix<Number>& V_EVD, const DiagonalMatrix<Number>& D_EVD, const Matrix<Number>& Vinv_EVD,
		  const Matrix<Number>& A_in, const Vector<Number>& b_nonlinear, const size_t dimension,
		  Matrix<Number>& V, Matrix<Number>& Vinv,
		  Vector<Number>& b_tr, STallValues<Number>& mSTallvalues );
	// analyzing exponential terms in case of no linear terms
	void analyzeExponentialTerms( const size_t dimension, STallValues<Number>& mSTallvalues );

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
	// Transformation( HybridAutomaton<Number>& _hybrid );
	Transformation<Number>( const HybridAutomaton<Number>& _hybrid );
	/**
	 * @brief      Copy constructor.
	 *
	 * @param[in]  _hybrid  The original transformation for an hybrid automaton.
	 */
	// TODO implement?
	Transformation<Number>( const Transformation<Number>& _trafo );
	// TODO clean up locations and transitions on desctructor
	void output_HybridAutomaton();

	/*
	 * @brief       adding transformedBadGlobalStates to transformedLocalBadStates
	 *   [optional] call only by setting according flag to reachability analysis
	 * TODO storage requirement setting/analysis?
	 * due to count(location)*sizeof(BadStates) instead of sizeof(BadState) storage requirement
	 *
	 * @param[in] _hybrid the original Hybrid Automaton (to check location ptrs against)
	 */
	void addGlobalBadStates( const HybridAutomaton<Number>& _hybrid, const bool transform );

	// Getter for handling Automaton in Analysis non-const due to GlobalBadStates transformation
	HybridAutomaton<Number>& getTransformedHybridAutomaton() { return mTransformedHA; }
	// Map from newLoc to struct for reachability analysis using EVD
	const locationComputationSTMap& getLocationComputationSTMap() { return mLocPtrtoComputationvaluesMap; }
};
}  // namespace hypro

#include "Transformation.tpp"
