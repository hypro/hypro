#include "PolytopeSupportFunction.h"

namespace hypro {
	
	template<typename Number>
	void PolytopeSupportFunction<Number>::createArrays(unsigned int size) {
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
	void PolytopeSupportFunction<Number>::initialize(matrix_t<Number> constraints, vector_t<Number> constraintConstants, operator_e operation, unsigned int dimensionality) {
		mDimension = dimensionality;
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
		glp_set_prob_name(lp, "supportfunction");
		glp_set_obj_dir(lp, GLP_MAX);

		#ifndef PPOLYTOPESUPPORTFUNCTION_VERBOSE
			glp_term_out(GLP_OFF);
		#endif

		int numberOfConstraints = constraints.rows();
		#ifdef SUPPORTFUNCTION_VERBOSE
			#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
				// check dimensionalities
				int numberOfConstraintConstant = constraintConstants.size();
				if (numberOfConstraints != numberOfConstraintConstant)
				{
					std::cout << method << " incompatible number of constraints and correspondent values";
				}

				if (constraints.cols() != dimensionality)
				{
					std::cout << method << " constraints are of invalid dimensionality";
				}
			#endif
		#endif

		// convert constraint constants
		glp_add_rows(lp, numberOfConstraints);

		#ifdef SUPPORTFUNCTION_VERBOSE
			#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
				std::cout << method << " Constructed GLPK problem" << '\n' << "dimensionality: " << dimensionality << '\n';
			#endif
		#endif

		for (int i = 0; i < numberOfConstraints; i++)
		{
			glp_set_row_bnds(lp, i + 1, GLP_UP, 0.0, double(constraintConstants(i)));
		}

		// add cols here
		glp_add_cols(lp, dimensionality);

		#ifdef SUPPORTFUNCTION_VERBOSE
			#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
				std::cout << method << " added constraints (values)" << '\n';
			#endif
		#endif

		createArrays(constraints.size());

		// convert constraint matrix
		for (int i = 0; i < constraints.size(); i++)
		{
			ia[i+1] = ((int)(i / dimensionality))+1;

			#ifdef SUPPORTFUNCTION_VERBOSE
				#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
					std::cout << method << " index i: " << ia[i+1]  << '\n';
				#endif
			#endif
			ja[i+1] = ((int)(i%dimensionality))+1;

			#ifdef SUPPORTFUNCTION_VERBOSE
				#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
					std::cout << method << " index j: " << ja[i+1] << '\n';
				#endif
			#endif
			ar[i+1] = double(constraints((int)(i / dimensionality), (int)(i%dimensionality)));

			#ifdef SUPPORTFUNCTION_VERBOSE
				#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
					std::cout << method << " value: " << ar[i+1] << '\n';
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

		glp_load_matrix(lp, constraints.size(), ia, ja, ar);

		#ifdef SUPPORTFUNCTION_VERBOSE
			#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
				std::cout << method << " added constraints (matrix)" << '\n';
			#endif
		#endif
	}
	
	template<typename Number>
	evaluationResult<Number> PolytopeSupportFunction<Number>::evaluate(const vector_t<Number>& l) const {
		#ifdef SUPPORTFUNCTION_VERBOSE
			#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
				std::cout << "PolytopeSupportFunction: evaluate" << '\n';
			#endif
		#endif             
		int dimensions = l.size();

		for (int i = 0; i < dimensions; i++)
		{
			glp_set_col_bnds(lp, i+1, GLP_FR, 0.0, 0.0);
			glp_set_obj_coef(lp, i+1, double(l(i,0)));
		}
		
		std::cout << " Direction: " << l << std::endl; 

		/* solve problem */
		glp_simplex(lp, NULL);

		evaluationResult<Number> result;

		/* recover and display results */
		result.supportValue = glp_get_obj_val(lp);
		
		std::cout << " Obj coeff: " << glp_get_obj_coef(lp,0) << " and " << glp_get_obj_coef(lp,1) << std::endl;

		matrix_t<Number> x(dimensions, 1);
		for (int i = 0; i < dimensions; i++)
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
				 std::cout << "Unable to find a suitable solution for the support function (linear program). ErrorCode: " << result.errorCode << '\n';             
		}

		#ifdef SUPPORTFUNCTION_VERBOSE
			   #ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
				   printf("fx = %g; x = ", double(result.supportValue));
				   std::cout << x;
				   std::cout << '\n' << "size x: " << x.size() << '\n';
			   #endif
		#endif

		return result;
	}
	
	template<typename Number>
	PolytopeSupportFunction<Number>::PolytopeSupportFunction(matrix_t<Number> constraints, matrix_t<Number> constraintConstants, operator_e operation, unsigned int dimensionality, artificialDirections<Number>* aD){                        
		vector_t<Number> constants = vector_t<Number>(dimensionality, 1);
		constants.block(0,0,dimensionality, 1) = constraintConstants.block(0,0,dimensionality, 1);
		
		initialize(constraints, constraintConstants, operation, dimensionality);
	}
	
	template<typename Number>
	PolytopeSupportFunction<Number>::PolytopeSupportFunction(matrix_t<Number> constraints, vector_t<Number> constraintConstants, operator_e operation, unsigned int dimensionality, artificialDirections<Number>* aD){
		initialize(constraints, constraintConstants, operation, dimensionality);
	}	
	
	template<typename Number>
	PolytopeSupportFunction<Number>::~PolytopeSupportFunction()
	{
		#ifdef SUPPORTFUNCTION_VERBOSE
			#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
				std::cout << "PolytopeSupportFunction: destructor" << '\n';
			#endif
		#endif

		deleteArrays();

		// free glpk resources
		glp_delete_prob(lp);

		#ifdef SUPPORTFUNCTION_VERBOSE
			#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
				std::cout << "PolytopeSupportFunction: destructor - complete" << '\n';
			#endif
		#endif 
	}
	
	template<typename Number>
	unsigned int PolytopeSupportFunction<Number>::dimension() {
		return mDimension;
	}
} // namespace
