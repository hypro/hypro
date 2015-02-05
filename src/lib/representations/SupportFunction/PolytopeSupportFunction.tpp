#include "PolytopeSupportfunction.h"

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
	void PolytopeSupportFunction<Number>::initialize(matrix_t<Number> constraints, matrix_t<Number> constraintConstants, operator_e operation, unsigned int dimensionality) {
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
	evaluationResult<Number> PolytopeSupportFunction<Number>::specificEvaluation(const matrix_t<Number>& l) const {
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
	PolytopeSupportFunction<Number>::PolytopeSupportFunction(matrix_t<Number> constraints, matrix_t<Number> constraintConstants, operator_e operation, unsigned int dimensionality, artificialDirections<Number>* aD) : SupportFunction<Number>(SupportFunctionType::Polytope_Type, aD) {                        
		matrix_t<Number> extendedConstraints(constraints.rows()+2, constraints.cols());
		extendedConstraints.block(0,0,constraints.rows(),constraints.cols()) = constraints;
		extendedConstraints.block(extendedConstraints.rows()-2,0,1,constraints.cols()) = aD->dir1.transpose();
		extendedConstraints.block(extendedConstraints.rows()-1,0,1,constraints.cols()) = aD->dir2.transpose();

		//constraintConstants.conservaticeResize(constraintConstants.rows()+2,1);
		matrix_t<Number> extendedConstraintConstants(constraintConstants.rows()+2,1);
		extendedConstraintConstants.block(0,0,constraintConstants.rows(),1) = constraintConstants;
		extendedConstraintConstants(extendedConstraintConstants.rows()-2,0) = 1; //artificialDirections<Number>::dir1_eval;
		extendedConstraintConstants(extendedConstraintConstants.rows()-1,0) = -1; //artificialDirections<Number>::dir2_eval;

		#ifdef SUPPORTFUNCTION_VERBOSE
			 #ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
				 std::cout << "PolytopeSupportFunction()_1: new constraint/value pairs: " << std::endl;
				 std::cout << extendedConstraints << std::endl;
				 std::cout << extendedConstraintConstants << std::endl;
			 #endif
		#endif

		// call constructor functionality                                      
		initialize(extendedConstraints, extendedConstraintConstants, operation, dimensionality);
//		initialize(constraints, constraintConstants, operation, dimensionality);
	}
	
	template<typename Number>
	PolytopeSupportFunction<Number>::PolytopeSupportFunction(matrix_t<Number> constraints, vector_t<Number> constraintConstants, operator_e operation, unsigned int dimensionality, artificialDirections<Number>* aD) : SupportFunction<Number>(SupportFunctionType::Polytope_Type, aD) {   
		std::cout << "ping" << std::endl; 
		matrix_t<Number> extendedConstraints(constraints.rows()+2, constraints.cols());
		 extendedConstraints.block(0,0,constraints.rows(),constraints.cols()) = constraints;
		 extendedConstraints.block(extendedConstraints.rows()-2,0,1,constraints.cols()) = aD->dir1.transpose();
		 extendedConstraints.block(extendedConstraints.rows()-1,0,1,constraints.cols()) = aD->dir2.transpose();

		 matrix_t<Number> extendedConstraintConstants(constraintConstants.size()+2,1);
		 extendedConstraintConstants.block(0,0,constraintConstants.size(),1) = constraintConstants;
		 extendedConstraintConstants(extendedConstraintConstants.size()-2,0) = 1; //artificialDirections<Number>::dir1_eval;
		 extendedConstraintConstants(extendedConstraintConstants.size()-1,0) = -1; //artificialDirections<Number>::dir2_eval;

		 #ifdef SUPPORTFUNCTION_VERBOSE
			 #ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
				 std::cout << "PolytopeSupportFunction()_2: new constraint/value pairs: " << std::endl;
				 std::cout << extendedConstraints << std::endl;
				 std::cout << extendedConstraintConstants << std::endl;
			 #endif
		 #endif

		 // call constructor functionality
		 initialize(extendedConstraints, extendedConstraintConstants, operation, dimensionality);
	}
	
	template<typename Number>
	PolytopeSupportFunction<Number>::PolytopeSupportFunction(std::vector<matrix_t<Number>>* constraints, matrix_t<Number> constraintConstants, unsigned int dimensionality, artificialDirections<Number>* aD) : SupportFunction<Number>(SupportFunctionType::Polytope_Type, aD) {   
		//std::cout << "!!!! PolytopeSupportFunction(): this constructor assumes that the two last entries from 'constraints' correspond to the two aritifcial directions" << std::endl;

		//std::cout << "C:" << std::endl;
		//printDirectionList(*constraints);
		//std::cout << std::endl << "d:" << constraintConstants;

		// reset artificial directions
		constraintConstants(0,0) = 1; //artificialDirections<Number>::dir1_eval;
		constraintConstants(1,0) = -1; //artificialDirections<Number>::dir2_eval;
		std::cout << "ping" << std::endl;
		//std::cout << std::endl << "resetted d:" << constraintConstants << std::endl;

		matrix_t<double> temp;

		 #ifdef SUPPORTFUNCTION_VERBOSE
				 #ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
				   std::string method = "PolytopeSupportFunction:";
				 #endif
		 #endif

			/* create glpk problem */
			lp = glp_create_prob();
			glp_set_prob_name(lp, "supportfunction");
			glp_set_obj_dir(lp, GLP_MAX);

			int numberOfConstraints = constraints->size();
			#ifdef SUPPORTFUNCTION_VERBOSE
				#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
					// check dimensionalities
					int numberOfConstraintConstant = constraintConstants.size();
					if (numberOfConstraints != numberOfConstraintConstant)
					{
						std::cout << method << " incompatible number of constraints and correspondent values";
					}
				#endif
			#endif

			// convert constraint constants
			glp_add_rows(lp, numberOfConstraints);

			#ifdef SUPPORTFUNCTION_VERBOSE
				#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
					std::cout << method << " Constructed GLPK problem" << '\n' << "dimensionality: " << dimensionality << '\n';
					std::cout << "constraintConstants as doubles: ";
				#endif
			#endif

			for (int i = 0; i < numberOfConstraints; i++)
			{
				glp_set_row_bnds(lp, i + 1, GLP_UP, 0.0, double(constraintConstants(i)));
				#ifdef SUPPORTFUNCTION_VERBOSE
					#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
						std::cout << constraintConstants(i) << "->" << double(constraintConstants(i)) << ", ";
					#endif
				#endif
			}

			// add cols here
			glp_add_cols(lp, dimensionality);

			#ifdef SUPPORTFUNCTION_VERBOSE
				#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
					std::cout << method << " added constraints (values)" << '\n';
				#endif
			#endif

			createArrays(constraints->size()*constraints->at(0).size());

			unsigned int counter = 1;
			// convert constraint matrix
			for (unsigned int i = 0; i < constraints->size(); i++)
			{
				for(int j=0; j<constraints->at(i).size(); j++)
				{
					ia[counter] = i+1;

					#ifdef SUPPORTFUNCTION_VERBOSE
						#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
							std::cout << method << " index i: " << ia[counter]  << '\n';
						#endif
					#endif
					ja[counter] = j+1;

					#ifdef SUPPORTFUNCTION_VERBOSE
						#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
							std::cout << method << " index j: " << ja[counter] << '\n';
						#endif
					#endif
					temp = constraints->at(i);
					ar[counter] = double(temp(j,0));

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

			glp_load_matrix(lp, dimensionality*constraints->size(), ia, ja, ar);

			#ifdef SUPPORTFUNCTION_VERBOSE
				#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
					std::cout << method << " added constraints" << '\n';
				#endif
			#endif
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
	
} // namespace
