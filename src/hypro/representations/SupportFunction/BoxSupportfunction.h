/*
 *  This file contains everything related directly to support functions of symmetric boxes and their evaluation
 *  Author: Norman Hansen
 */
#pragma once

//#include "hyreach_utils.h"
#include "SupportFunctionContent.h"

//#define BOXSUPPORTFUNCTION_VERBOSE

namespace hypro {
/*
* This class defines a support Function object representing a polytope (might not be closed)
* SupportFunctions can be evaluated in a specified direction l and return a correspondent evaluationResult
*/
template<class Setting>
class SymmetricCenteredBoxSupportFunction : public SupportFunctionContent {
  private:
	matrix_t<double> e;
	matrix_t<double> e_t;  // e is stored in transposed format too

  protected:
	/**
	 * This method computes the evaluation result for a specified direction l
	 */
	evaluationResult specificEvaluation( matrix_t<double> l ) {

		if(Setting::SUPPORTFUNCTION_VERBOSE && Setting::BOXSUPPORTFUNCTION_VERBOSE){
			TRACE("hypro.BoxSF","SymmetricCenteredBoxSupportFunction: evaluate" << '\n');
			TRACE("hypro.BoxSF","e_t: " << e_t << '\n');
			TRACE("hypro.BoxSF","abs(l): " << ( l.array().abs() ).matrix() << '\n');
		}

		evaluationResult result;
		result.errorCode = 1;

		matrix_t<double> temp = e_t * ( l.array().abs() ).matrix();

		result.supportValue = temp( 0 );
		result.optimumValue = l * temp;

		if(Setting::SUPPORTFUNCTION_VERBOSE && Setting::BOXSUPPORTFUNCTION_VERBOSE){
			TRACE("hypro.BoxSF","supportvalue: " << result.supportValue << '\n');
		}

		return result;
	}

  public:
	/*
	* This methods creates a copy of the instanciated object on the heap.
	*/
	SupportFunctionContent* copyToHeap() {
		SupportFunctionContent* result = new SymmetricCenteredBoxSupportFunction( e, getAD() );
		return result;
	}

	SymmetricCenteredBoxSupportFunction( matrix_t<double> e, artificialDirections* aD )
		: SupportFunctionContent( SupportFunctionType::Box_Type, aD ) {

		if(Setting::SUPPORTFUNCTION_VERBOSE && Setting::BOXSUPPORTFUNCTION_VERBOSE){
			TRACE("hypro.BoxSF","SymmetricCenteredBoxSupportFunction: constructor" << '\n');
		}

		this->e = e;
		this->e_t = e.transpose();
	}

	// getter for const e
	matrix_t<double> getE() { return e; }
};
}
