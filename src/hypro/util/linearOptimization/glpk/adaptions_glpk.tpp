/**
 *
 */
#include "adaptions_glpk.h"

namespace hypro {

	inline void printProblem(glp_prob* glpkProblem) {
		int cols = glp_get_num_cols(glpkProblem);
		int* ind = new int[unsigned(cols) + 1];
		double* val = new double[unsigned(cols) + 1];
		for(int i = 1; i <= glp_get_num_rows(glpkProblem); ++i) {
			int nonZeroCount = glp_get_mat_row(glpkProblem, i, ind, val);
			for(int colIndex = 1; colIndex <= cols; ++colIndex) {
				bool found = false;
				// glpk always starts indexing at 1 -> we can skip the element at 0
				for(int arrayIndex = 1; arrayIndex < nonZeroCount+1; ++arrayIndex) {
					if(ind[arrayIndex] == colIndex) {
						found = true;
						std::cout << val[arrayIndex] << "\t";
					}
				}
				if(!found) {
					std::cout << "0\t";
				}
			}
			if( glp_get_row_type(glpkProblem,i) == GLP_UP ) {
				//std::cout << " <= " << glp_get_row_ub(glpkProblem,i) << std::endl;
			} else if ( glp_get_row_type(glpkProblem,i) == GLP_FR ) {
				//std::cout << " <= +INF" << std::endl;
			}
		}
		delete[] ind;
		delete[] val;
	}

	template<typename Number>
	EvaluationResult<Number> glpkOptimizeLinear(glp_prob* glpkProblem, const vector_t<Number>& _direction, const matrix_t<Number>& constraints, const vector_t<Number>& constants, bool useExact) {
		/*
		std::cout << __func__ << " in direction " << convert<Number,double>(_direction).transpose() << std::endl;
		std::cout << __func__ << " constraints: " << std::endl << constraints << std::endl << "constants: " << std::endl << constants << std::endl << "Glpk Problem: " << std::endl;
		//printProblem(glpkProblem);
		*/

		// setup glpk
		for ( int i = 0; i < constraints.cols(); i++ ) {
			glp_set_col_bnds( glpkProblem, i + 1, GLP_FR, 0.0, 0.0 );
			glp_set_obj_coef( glpkProblem, i + 1, carl::toDouble( _direction( i ) ) );
		}
		/* solve problem */
		if(useExact){
			glp_exact( glpkProblem, NULL );
		} else {
			glp_simplex( glpkProblem, NULL );
		}

		vector_t<Number> exactSolution;
		switch ( glp_get_status( glpkProblem ) ) {
			case GLP_OPT:
			case GLP_FEAS: {
				// if satisfiable, derive exact solution by intersecting all constraints, which are at their upper bounds (we always maximize).
				matrix_t<Number> exactSolutionMatrix = matrix_t<Number>::Zero(constraints.cols(), constraints.cols());
				vector_t<Number> exactSolutionVector = vector_t<Number>::Zero(constraints.cols());
				unsigned pos = 0;
				for(int i = 1; i <= constraints.rows(); ++i) {
					// we search for d non-basic variables at their upper bound, which define the optimal point.
					int status = glp_get_row_stat( glpkProblem, i);
					if( status == GLP_NU ) {
						#ifdef DEBUG_MSG
						//std::cout << "Row " << i << " is at its upper bounds." << std::endl;
						#endif
						exactSolutionMatrix.row(pos) = constraints.row(i-1);
						exactSolutionVector(pos) = constants(i-1);
						++pos;
					}
				}
				exactSolution = Eigen::FullPivLU<matrix_t<Number>>(exactSolutionMatrix).solve(exactSolutionVector);
				#ifdef DEBUG_MSG
				//std::cout << "Problem for exact solution: " << exactSolutionMatrix << ", " << exactSolutionVector << std::endl;
				//std::cout << "Exact solution is: " << exactSolution << std::endl << "with support value: " << _direction.dot(exactSolution) << std::endl;
				#endif
				return EvaluationResult<Number>(_direction.dot(exactSolution), exactSolution, SOLUTION::FEAS);
				break;
			}
			case GLP_UNBND: {
				vector_t<Number> glpkModel(constraints.cols());
				for(int i=1; i <= constraints.cols(); ++i) {
					glpkModel(i-1) = carl::rationalize<Number>(glp_get_col_prim( glpkProblem, i));
				}
				return EvaluationResult<Number>(1, glpkModel, SOLUTION::INFTY);
				break;
			}
			default:
				return EvaluationResult<Number>(0, vector_t<Number>::Zero(1), SOLUTION::INFEAS);
		}
	}

	template<typename Number>
	bool glpkCheckPoint(glp_prob* glpkProblem, const matrix_t<Number>& constraints, const vector_t<Number>& , const Point<Number>& point) {
		// set point
		assert(constraints.cols() == point.rawCoordinates().rows());
		for ( int i = 0; i < constraints.cols(); ++i ) {
			glp_set_col_bnds( glpkProblem, i + 1, GLP_FX, carl::toDouble(point.rawCoordinates()(i)), 0.0 );
			glp_set_obj_coef( glpkProblem, i + 1, 1.0 ); // not needed?
		}
		glp_simplex( glpkProblem, NULL);
		glp_exact( glpkProblem, NULL );
		return (glp_get_status( glpkProblem ) != GLP_NOFEAS);
	}

	template<typename Number>
	std::vector<std::size_t> glpkRedundantConstraints(glp_prob* glpkProblem, matrix_t<Number> constraints, vector_t<Number> constants) {
		std::vector<std::size_t> res;

		// TODO: ATTENTION: This relies upon that glpk maintains the order of the constraints!
		for ( int i = 0; i < constraints.cols(); ++i ) {
			glp_set_col_bnds( glpkProblem, i + 1, GLP_FR, 0.0, 0.0 );
			glp_set_obj_coef( glpkProblem, i + 1, 1.0 ); // not needed?
		}

		// first call to check satisfiability
		glp_simplex( glpkProblem, NULL);
		glp_exact( glpkProblem, NULL );

		switch (glp_get_status( glpkProblem )) {
			case GLP_INFEAS:
			case GLP_NOFEAS: {
				return res;
			}
		}

		for(std::size_t constraintIndex = std::size_t(constraints.rows()-1); constraintIndex >= 0; --constraintIndex) {
			// evaluate in current constraint direction
			EvaluationResult<Number> actualRes = glpkOptimizeLinear(glpkProblem, vector_t<Number>(constraints.row(constraintIndex)), constraints, constants, true);
			//assert(actualRes.supportValue <= constants(constraintIndex));

			// remove constraint by removing the boundaries
			glp_set_row_bnds(glpkProblem, int(constraintIndex)+1, GLP_FR, 0.0, 0.0);
			EvaluationResult<Number> updatedRes = glpkOptimizeLinear(glpkProblem, vector_t<Number>(constraints.row(constraintIndex)), constraints, constants, true);

			if(updatedRes.supportValue == actualRes.supportValue && updatedRes.errorCode == actualRes.errorCode) {
				res.push_back(constraintIndex);
			} else {
				glp_set_row_bnds(glpkProblem, int(constraintIndex)+1, GLP_UP,  0.0, carl::toDouble( constants(constraintIndex) ));
			}
		}

		// restore original problem
		for(const auto item : res ) {
			glp_set_row_bnds(glpkProblem, int(item)+1, GLP_UP,  0.0, carl::toDouble( constants(item) ));
		}

		return res;
	}
} // namespace hypro
