/*
 *  This file contains everything related directly to support functions of polyhedra and their evaluation
 *  Author: Norman Hansen
 */

#pragma once

//#define SUPPORTFUNCTION_VERBOSE
//#define PPOLYTOPESUPPORTFUNCTION_VERBOSE

#include "hyreach_utils.h"

namespace hypro {
/*
* This class defines a support Function object representing a polytope (might not be closed)
* SupportFunctions can be evaluated in a specified direction l and return a correspondent evaluationResult
*/
class PolytopeSupportFunction : public SupportFunction {
  private:
	glp_prob* lp;
	int* ia;
	int* ja;
	double* ar;

	void createArrays( unsigned int size ) {
		ia = new int[size + 1];
		ja = new int[size + 1];
		ar = new double[size + 1];
	}

	void deleteArrays() {
		delete[] ia;
		delete[] ja;
		delete[] ar;
	}

	/**
	* Implements the functionality of the constructor. Used by both "real" constructors of this class
	*/
	void initialize( matrix_t<double> constraints, matrix_t<double> constraintConstants, operator_e operation,
					 unsigned int dimensionality ) {
#ifdef SUPPORTFUNCTION_VERBOSE
#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
		std::string method = "PolytopeSupportFunction:";
#endif
#endif

// TODO: depending on the operator, invert constraints

#ifdef SUPPORTFUNCTION_VERBOSE
#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
		std::cout << method << " copied constraint pointers" << '\n';
#endif
#endif

		/* create glpk problem */
		lp = glp_create_prob();
		glp_set_prob_name( lp, "supportfunction" );
		glp_set_obj_dir( lp, GLP_MAX );

#ifndef PPOLYTOPESUPPORTFUNCTION_VERBOSE
		glp_term_out( GLP_OFF );
#endif

		int numberOfConstraints = constraints.rows();
#ifdef SUPPORTFUNCTION_VERBOSE
#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
		// check dimensionalities
		int numberOfConstraintConstant = constraintConstants.size();
		if ( numberOfConstraints != numberOfConstraintConstant ) {
			std::cout << method << " incompatible number of constraints and correspondent values";
		}

		if ( constraints.cols() != dimensionality ) {
			std::cout << method << " constraints are of invalid dimensionality";
		}
#endif
#endif

		// convert constraint constants
		glp_add_rows( lp, numberOfConstraints );

#ifdef SUPPORTFUNCTION_VERBOSE
#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
		std::cout << method << " Constructed GLPK problem" << '\n' << "dimensionality: " << dimensionality << '\n';
#endif
#endif

		for ( int i = 0; i < numberOfConstraints; i++ ) {
			glp_set_row_bnds( lp, i + 1, GLP_UP, 0.0, double( constraintConstants( i ) ) );
		}

		// add cols here
		glp_add_cols( lp, dimensionality );

#ifdef SUPPORTFUNCTION_VERBOSE
#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
		std::cout << method << " added constraints (values)" << '\n';
#endif
#endif

		createArrays( constraints.size() );

		// convert constraint matrix
		for ( int i = 0; i < constraints.size(); i++ ) {
			ia[i + 1] = ( (int)( i / dimensionality ) ) + 1;

#ifdef SUPPORTFUNCTION_VERBOSE
#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
			std::cout << method << " index i: " << ia[i + 1] << '\n';
#endif
#endif
			ja[i + 1] = ( (int)( i % dimensionality ) ) + 1;

#ifdef SUPPORTFUNCTION_VERBOSE
#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
			std::cout << method << " index j: " << ja[i + 1] << '\n';
#endif
#endif
			ar[i + 1] = constraints( (int)( i / dimensionality ), (int)( i % dimensionality ) );

#ifdef SUPPORTFUNCTION_VERBOSE
#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
			std::cout << method << " value: " << ar[i + 1] << '\n';
#endif
#endif
		}

#ifdef SUPPORTFUNCTION_VERBOSE
#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
		std::cout << method << " terminated matrix construction" << '\n';
		std::cout << method << " number of matrix elements: " << constraints.size() << '\n';
		std::cout << "ia: " << ia << '\n';
		std::cout << "ja: " << ja << '\n';
		std::cout << "ar: " << ar << '\n';
#endif
#endif

		glp_load_matrix( lp, constraints.size(), ia, ja, ar );

#ifdef SUPPORTFUNCTION_VERBOSE
#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
		std::cout << method << " added constraints (matrix)" << '\n';
#endif
#endif
	}

  protected:
	/*
	* This method computes the evaluation result for a specified direction l
	*/
	evaluationResult specificEvaluation( matrix_t<double> l ) {
#ifdef SUPPORTFUNCTION_VERBOSE
#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
		std::cout << "PolytopeSupportFunction: evaluate" << '\n';
#endif
#endif
		int dimensions = l.size();

		for ( int i = 0; i < dimensions; i++ ) {
			glp_set_col_bnds( lp, i + 1, GLP_FR, 0.0, 0.0 );
			glp_set_obj_coef( lp, i + 1, double( l( i, 0 ) ) );
		}

		/* solve problem */
		glp_simplex( lp, NULL );

		evaluationResult result;

		/* recover and display results */
		result.supportValue = glp_get_obj_val( lp );

		matrix_t<double> x( dimensions, 1 );
		for ( int i = 0; i < dimensions; i++ ) {
			x( i ) = glp_get_col_prim( lp, i + 1 );
		}
		result.optimumValue = x;
		result.errorCode = glp_get_status( lp );

		// display potential problems
		switch ( result.errorCode ) {
			case GLP_OPT:
			case GLP_FEAS:
				break;
			case GLP_UNBND:
				result.supportValue = INFINITY;
				break;
			default:
				std::cout << "Unable to find a suitable solution for the support function (linear program). ErrorCode: "
						  << result.errorCode << '\n';
		}

#ifdef SUPPORTFUNCTION_VERBOSE
#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
		printf( "fx = %g; x = ", result.supportValue );
		std::cout << x;
		std::cout << '\n' << "size x: " << x.size() << '\n';
#endif
#endif

		return result;
	}

  public:
	/*
	* Creates a new supportFunction for the closed convex set described by constraints * x operation(>= or <=)
	* constraintConstants
	*/
	PolytopeSupportFunction( matrix_t<double> constraints, matrix_t<double> constraintConstants, operator_e operation,
							 unsigned int dimensionality, artificialDirections* aD )
		: SupportFunction( SupportFunctionType::Polytope_Type, aD ) {
		matrix_t<double> extendedConstraints( constraints.rows() + 2, constraints.cols() );
		extendedConstraints.block( 0, 0, constraints.rows(), constraints.cols() ) = constraints;
		extendedConstraints.block( extendedConstraints.rows() - 2, 0, 1, constraints.cols() ) = aD->dir1.transpose();
		extendedConstraints.block( extendedConstraints.rows() - 1, 0, 1, constraints.cols() ) = aD->dir2.transpose();

		// constraintConstants.conservaticeResize(constraintConstants.rows()+2,1);
		matrix_t<double> extendedConstraintConstants( constraintConstants.rows() + 2, 1 );
		extendedConstraintConstants.block( 0, 0, constraintConstants.rows(), 1 ) = constraintConstants;
		extendedConstraintConstants( extendedConstraintConstants.rows() - 2, 0 ) = artificialDirections::dir1_eval;
		extendedConstraintConstants( extendedConstraintConstants.rows() - 1, 0 ) = artificialDirections::dir2_eval;

#ifdef SUPPORTFUNCTION_VERBOSE
#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
		std::cout << "PolytopeSupportFunction()_1: new constraint/value pairs: " << BL;
		std::cout << extendedConstraints << BL;
		std::cout << extendedConstraintConstants << BL;
#endif
#endif

		// call constructor functionality
		initialize( extendedConstraints, extendedConstraintConstants, operation, dimensionality );
	}

	PolytopeSupportFunction( matrix_t<double> constraints, vector_t<double> constraintConstants, operator_e operation,
							 unsigned int dimensionality, artificialDirections* aD )
		: SupportFunction( SupportFunctionType::Polytope_Type, aD ) {
		matrix_t<double> extendedConstraints( constraints.rows() + 2, constraints.cols() );
		extendedConstraints.block( 0, 0, constraints.rows(), constraints.cols() ) = constraints;
		extendedConstraints.block( extendedConstraints.rows() - 2, 0, 1, constraints.cols() ) = aD->dir1.transpose();
		extendedConstraints.block( extendedConstraints.rows() - 1, 0, 1, constraints.cols() ) = aD->dir2.transpose();

		matrix_t<double> extendedConstraintConstants( constraintConstants.size() + 2, 1 );
		extendedConstraintConstants.block( 0, 0, constraintConstants.size(), 1 ) = constraintConstants;
		extendedConstraintConstants( extendedConstraintConstants.size() - 2, 0 ) = artificialDirections::dir1_eval;
		extendedConstraintConstants( extendedConstraintConstants.size() - 1, 0 ) = artificialDirections::dir2_eval;

#ifdef SUPPORTFUNCTION_VERBOSE
#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
		std::cout << "PolytopeSupportFunction()_2: new constraint/value pairs: " << BL;
		std::cout << extendedConstraints << BL;
		std::cout << extendedConstraintConstants << BL;
#endif
#endif

		// call constructor functionality
		initialize( extendedConstraints, extendedConstraintConstants, operation, dimensionality );
	}

	// supports only <= operator by design -> !!!! See first std::cout !!!!
	PolytopeSupportFunction( std::vector<matrix_t<double>>* constraints, matrix_t<double> constraintConstants,
							 unsigned int dimensionality, artificialDirections* aD )
		: SupportFunction( SupportFunctionType::Polytope_Type, aD ) {
		// std::cout << "!!!! PolytopeSupportFunction(): this constructor assumes that the two last entries from
		// 'constraints' correspond to the two aritifcial directions" << BL;

		// std::cout << "C:" << BL;
		// printDirectionList(*constraints);
		// std::cout << BL << "d:" << constraintConstants;

		// reset artificial directions
		constraintConstants( 0, 0 ) = artificialDirections::dir1_eval;
		constraintConstants( 1, 0 ) = artificialDirections::dir2_eval;

		// std::cout << BL << "resetted d:" << constraintConstants << BL;

		matrix_t<double> temp;

#ifdef SUPPORTFUNCTION_VERBOSE
#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
		std::string method = "PolytopeSupportFunction:";
#endif
#endif

		/* create glpk problem */
		lp = glp_create_prob();
		glp_set_prob_name( lp, "supportfunction" );
		glp_set_obj_dir( lp, GLP_MAX );

		int numberOfConstraints = constraints->size();
#ifdef SUPPORTFUNCTION_VERBOSE
#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
		// check dimensionalities
		int numberOfConstraintConstant = constraintConstants.size();
		if ( numberOfConstraints != numberOfConstraintConstant ) {
			std::cout << method << " incompatible number of constraints and correspondent values";
		}
#endif
#endif

		// convert constraint constants
		glp_add_rows( lp, numberOfConstraints );

#ifdef SUPPORTFUNCTION_VERBOSE
#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
		std::cout << method << " Constructed GLPK problem" << '\n' << "dimensionality: " << dimensionality << '\n';
		std::cout << "constraintConstants as doubles: ";
#endif
#endif

		for ( int i = 0; i < numberOfConstraints; i++ ) {
			glp_set_row_bnds( lp, i + 1, GLP_UP, 0.0, double( constraintConstants( i ) ) );
#ifdef SUPPORTFUNCTION_VERBOSE
#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
			std::cout << constraintConstants( i ) << "->" << double( constraintConstants( i ) ) << ", ";
#endif
#endif
		}

		// add cols here
		glp_add_cols( lp, dimensionality );

#ifdef SUPPORTFUNCTION_VERBOSE
#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
		std::cout << method << " added constraints (values)" << '\n';
#endif
#endif

		createArrays( constraints->size() * constraints->at( 0 ).size() );

		unsigned int counter = 1;
		// convert constraint matrix
		for ( unsigned int i = 0; i < constraints->size(); i++ ) {
			for ( int j = 0; j < constraints->at( i ).size(); j++ ) {
				ia[counter] = i + 1;

#ifdef SUPPORTFUNCTION_VERBOSE
#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
				std::cout << method << " index i: " << ia[counter] << '\n';
#endif
#endif
				ja[counter] = j + 1;

#ifdef SUPPORTFUNCTION_VERBOSE
#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
				std::cout << method << " index j: " << ja[counter] << '\n';
#endif
#endif
				temp = constraints->at( i );
				ar[counter] = double( temp( j, 0 ) );

#ifdef SUPPORTFUNCTION_VERBOSE
#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
				std::cout << method << " value: " << ar[counter] << '\n';
#endif
#endif
				counter++;
			}
		}

#ifdef SUPPORTFUNCTION_VERBOSE
#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
		std::cout << method << " terminated matrix construction" << '\n';
		std::cout << "ia: " << ia << '\n';
		std::cout << "ja: " << ja << '\n';
		std::cout << "ar: " << ar << '\n';
#endif
#endif

		glp_load_matrix( lp, dimensionality * constraints->size(), ia, ja, ar );

#ifdef SUPPORTFUNCTION_VERBOSE
#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
		std::cout << method << " added constraints" << '\n';
#endif
#endif
	}

	// destructor
	~PolytopeSupportFunction() {
#ifdef SUPPORTFUNCTION_VERBOSE
#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
		std::cout << "PolytopeSupportFunction: destructor" << '\n';
#endif
#endif

		deleteArrays();

		// free glpk resources
		glp_delete_prob( lp );

#ifdef SUPPORTFUNCTION_VERBOSE
#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
		std::cout << "PolytopeSupportFunction: destructor - complete" << '\n';
#endif
#endif
	}
};
}
