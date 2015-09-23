/*
 *  This file contains everything related directly to support functions of symmetric boxes and their evaluation
 *  Author: Norman Hansen
 */
#pragma once

#include "hyreach_utils.h"

//#define BOXSUPPORTFUNCTION_VERBOSE

namespace hypro {
/*
* This class defines a support Function object representing a polytope (might not be closed)
* SupportFunctions can be evaluated in a specified direction l and return a correspondent evaluationResult
*/
class SymmetricCenteredBoxSupportFunction : public SupportFunction {
  private:
	matrix_t<double> e;
	matrix_t<double> e_t;  // e is stored in transposed format too

  protected:
	/**
	 * This method computes the evaluation result for a specified direction l
	 */
	evaluationResult specificEvaluation( matrix_t<double> l ) {
#ifdef SUPPORTFUNCTION_VERBOSE
#ifdef BOXSUPPORTFUNCTION_VERBOSE
		std::cout << "SymmetricCenteredBoxSupportFunction: evaluate" << '\n';
		std::cout << "e_t: " << e_t << '\n';
		std::cout << "abs(l): " << ( l.array().abs() ).matrix() << '\n';
#endif
#endif

		evaluationResult result;
		result.errorCode = 1;

		matrix_t<double> temp = e_t * ( l.array().abs() ).matrix();

		result.supportValue = temp( 0 );
		result.optimumValue = l * temp;

#ifdef SUPPORTFUNCTION_VERBOSE
#ifdef BOXSUPPORTFUNCTION_VERBOSE
		std::cout << "supportvalue: " << result.supportValue << '\n';
#endif
#endif

		return result;
	}

  public:
	/*
	* This methods creates a copy of the instanciated object on the heap.
	*/
	SupportFunction* copyToHeap() {
		SupportFunction* result = new SymmetricCenteredBoxSupportFunction( e, getAD() );
		return result;
	}

	SymmetricCenteredBoxSupportFunction( matrix_t<double> e, artificialDirections* aD )
		: SupportFunction( SupportFunctionType::Box_Type, aD ) {
#ifdef SUPPORTFUNCTION_VERBOSE
#ifdef BOXSUPPORTFUNCTION_VERBOSE
		std::cout << "SymmetricCenteredBoxSupportFunction: constructor" << '\n';
#endif
#endif
		this->e = e;
		this->e_t = e.transpose();
	}

	// getter for const e
	matrix_t<double> getE() { return e; }
};
}
