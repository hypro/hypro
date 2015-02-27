/*
 * This file contains the basic implementation of support functions of polyhedra (template polyhedra) and their evaluation.
 * @file PolytopeSupportFunction.tpp
 * 
 * @author Norman Hansen
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * 
 * @version	2015-02-27
 */

#include "PolytopeSupportFunction.h"

namespace hypro {
	
	template<typename Number>
	void PolytopeSupportFunction<Number>::createArrays(unsigned size) {
		ia = new int[size+1];
		ja = new int[size+1];
		ar = new double[size+1];
	}
	
	template<typename Number>
	void PolytopeSupportFunction<Number>::deleteArrays() {
		 delete[] ia;
		 delete[] ja;
		 delete[] ar;
	}
	
	template<typename Number>
	void PolytopeSupportFunction<Number>::initialize(matrix_t<Number> constraints, vector_t<Number> constraintConstants) {
		assert(constraints.rows() == constraintConstants.rows());
		mDimension = constraints.cols();

		#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
			std::cout << __func__ << " copied constraint pointers" << std::endl;
		#endif

		/* create glpk problem */
		lp = glp_create_prob();
		glp_set_prob_name(lp, "supportfunction");
		glp_set_obj_dir(lp, GLP_MAX);

		#ifndef PPOLYTOPESUPPORTFUNCTION_VERBOSE
			glp_term_out(GLP_OFF);
		#endif

		int numberOfConstraints = constraints.rows();
		#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
			// check dimensionalities
			int numberOfConstraintConstant = constraintConstants.size();
			if (numberOfConstraints != numberOfConstraintConstant)
			{
				std::cout << __func__ << " incompatible number of constraints and correspondent values";
			}
		#endif

		// convert constraint constants
		glp_add_rows(lp, numberOfConstraints);

		#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
			std::cout << __func__ << " Constructed GLPK problem" << std::endl << "mDimension: " << mDimension << std::endl;
		#endif

		for (int i = 0; i < numberOfConstraints; i++)
		{
			glp_set_row_bnds(lp, i + 1, GLP_UP, 0.0, double(constraintConstants(i)));
		}

		// add cols here
		glp_add_cols(lp, mDimension);

		#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
			std::cout << __func__ << " added constraints (values)" << std::endl;
		#endif

		createArrays(constraints.size());

		// convert constraint matrix
		for (int i = 0; i < constraints.size(); i++)
		{
			ia[i+1] = ((int)(i / mDimension))+1;
			ja[i+1] = ((int)(i%mDimension))+1;
			ar[i+1] = double(constraints((int)(i / mDimension), (int)(i%mDimension)));

			#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
				std::cout << __func__ << " set: ar[" << i+1 << "]=" << ar[i+1] << ", ja[" << i+1 << "]=" << ja[i+1] << ", ia[" << i+1 << "]=" << ia[i+1] << std::endl;
			#endif
		}

		#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
			std::cout << __func__ << " terminated matrix construction" << std::endl;
			std::cout << __func__ << " number of matrix elements: " << constraints.size() << std::endl;
			std::cout << "ia: " << ia << std::endl;
			std::cout << "ja: " << ja << std::endl;
			std::cout << "ar: " << ar << std::endl;
		#endif

		glp_load_matrix(lp, constraints.size(), ia, ja, ar);

		#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
			std::cout << __func__ << " added constraints (matrix)" << std::endl;
		#endif
	}
	
	template<typename Number>
	PolytopeSupportFunction<Number>::PolytopeSupportFunction(matrix_t<Number> constraints, vector_t<Number> constraintConstants){
		initialize(constraints, constraintConstants);
	}	
	
	template<typename Number>
	PolytopeSupportFunction<Number>::~PolytopeSupportFunction()
	{
		#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
			std::cout << "PolytopeSupportFunction: destructor" << std::endl;
		#endif

		deleteArrays();

		// free glpk resources
		glp_delete_prob(lp);

		#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
			std::cout << "PolytopeSupportFunction: destructor - complete" << std::endl;
		#endif
	}
	
	template<typename Number>
	unsigned PolytopeSupportFunction<Number>::dimension() const {
		return mDimension;
	}
	
	template<typename Number>
	evaluationResult<Number> PolytopeSupportFunction<Number>::evaluate(const vector_t<Number>& l) const {
		#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
			std::cout << "PolytopeSupportFunction: evaluate in " << l << std::endl;
		#endif   
		assert(l.rows() == mDimension);

		for (int i = 0; i < mDimension; i++)
		{
			glp_set_col_bnds(lp, i+1, GLP_FR, 0.0, 0.0);
			glp_set_obj_coef(lp, i+1, double(l(i,0)));
		}

		/* solve problem */
		glp_simplex(lp, NULL);

		evaluationResult<Number> result;

		/* recover and display results */
		result.supportValue = glp_get_obj_val(lp);
		
		//std::cout << " Obj coeff: " << glp_get_obj_coef(lp,0) << " and " << glp_get_obj_coef(lp,1) << std::endl;

		vector_t<Number> x = vector_t<Number>(mDimension);
		for (int i = 0; i < mDimension; i++)
		{
			x(i) = Number(glp_get_col_prim(lp, i+1));
		}
		result.optimumValue = x;
		result.errorCode = glp_get_status(lp);

		// display potential problems
		switch(result.errorCode)
		{
			case GLP_OPT:
			case GLP_FEAS:
				 break;
			case GLP_UNBND:
				 result.supportValue = INFINITY;
				 break;
			default: 
				 std::cout << "Unable to find a suitable solution for the support function (linear program). ErrorCode: " << result.errorCode << std::endl;             
		}

		#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
			printf("fx = %g; x = ", double(result.supportValue));
			std::cout << x;
			std::cout << std::endl << "size x: " << x.size() << std::endl;
		#endif

		return result;
	}
	
	template<typename Number>
	bool PolytopeSupportFunction<Number>::empty() const {
		for (int i = 0; i < mDimension; i++)
		{
			glp_set_col_bnds(lp, i+1, GLP_FR, 0.0, 0.0); // unbounded
			glp_set_obj_coef(lp, i+1, 1.0); 
		}
		
		glp_simplex(lp, NULL);
		
		int errorCode = glp_get_status(lp);
		
		if(errorCode == GLP_INFEAS || errorCode == GLP_NOFEAS)
			return false;
		
		return true;
	}
} // namespace
