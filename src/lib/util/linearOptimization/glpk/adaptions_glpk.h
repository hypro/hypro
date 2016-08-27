/**
 *
 */
#pragma once
#include "../Optimizer.h"

#include <glpk.h>

namespace hypro {

	template<typename Number>
	EvaluationResult<Number> glpkOptimizeLinear(glp_prob* glpkProblem, const vector_t<Number>& _direction, const matrix_t<Number>& constraints, const vector_t<Number>& constants) {
		// setup glpk
		for ( unsigned i = 0; i < constraints.cols(); i++ ) {
			glp_set_col_bnds( glpkProblem, i + 1, GLP_FR, 0.0, 0.0 );
			glp_set_obj_coef( glpkProblem, i + 1, carl::toDouble( _direction( i ) ) );
		}
		/* solve problem */
		glp_exact( glpkProblem, NULL );

		vector_t<Number> exactSolution;
		switch ( glp_get_status( glpkProblem ) ) {
			case GLP_OPT:
			case GLP_FEAS: {
				// if satisfiable, derive exact solution by intersecting all constraints, which are at their upper bounds (we always maximize).
				matrix_t<Number> exactSolutionMatrix = matrix_t<Number>(constraints.cols(), constraints.cols());
				vector_t<Number> exactSolutionVector = vector_t<Number>(constraints.cols());
				unsigned pos = 0;
				for(unsigned i = 1; i <= constraints.rows(); ++i) {
					// we search for d non-basic variables at their upper bound, which define the optimal point.
					int status = glp_get_row_stat( glpkProblem, i);
					if( status == GLP_NU ) {
						#ifdef DEBUG_MSG
						std::cout << "Row " << i << " is at its upper bounds." << std::endl;
						#endif
						exactSolutionMatrix.row(pos) = constraints.row(i-1);
						exactSolutionVector(pos) = constants(i-1);
						++pos;
					}
				}
				exactSolution = Eigen::FullPivLU<matrix_t<Number>>(exactSolutionMatrix).solve(exactSolutionVector);
				#ifdef DEBUG_MSG
				std::cout << "Problem for exact solution: " << exactSolutionMatrix << ", " << exactSolutionVector << std::endl;
				std::cout << "Exact solution is: " << exactSolution << std::endl << "with support value: " << _direction.dot(exactSolution) << std::endl;
				#endif

				return EvaluationResult<Number>(_direction.dot(exactSolution), exactSolution, SOLUTION::FEAS);
				break;
			}
			case GLP_UNBND: {
				vector_t<Number> glpkModel(constraints.cols());
				for(unsigned i=1; i <= constraints.cols(); ++i) {
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
	bool glpkCheckPoint(glp_prob* glpkProblem, const matrix_t<Number>& constraints, const vector_t<Number>& constants, const Point<Number>& point) {
		// set point
		assert(constraints.cols() == point.rawCoordinates().rows());
		for ( unsigned i = 0; i < constraints.cols(); ++i ) {
			glp_set_col_bnds( glpkProblem, i + 1, GLP_FX, carl::toDouble(point.rawCoordinates()(i)), 0.0 );
			glp_set_obj_coef( glpkProblem, i + 1, 1.0 ); // not needed?
		}
		glp_simplex( glpkProblem, NULL);
		glp_exact( glpkProblem, NULL );
		return (glp_get_status( glpkProblem ) != GLP_NOFEAS);
	}

	template<typename Number>
	std::vector<std::size_t> glpkRedundantConstraints(glp_prob* glpkProblem, const matrix_t<Number>& constraints, const vector_t<Number>& constants) {
		std::vector<std::size_t> res;

		// TODO: ATTENTION: This relies upon that glpk maintains the order of the constraints!
		for ( unsigned i = 0; i < constraints.cols(); ++i ) {
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
		int* ind = new int[constraints.cols()+1];
		double* val = new double[constraints.cols()+1];
		for(unsigned constraintIndex = 0; constraintIndex < constraints.rows(); ++constraintIndex) {
			// create and add negated constraint
			std::cout << "create negated constraint." << std::endl;

			for(unsigned d = 0; d < constraints.cols(); ++d) {
				ind[d+1] = d+1;
				val[d+1] = -carl::convert<Number,double>(constraints(constraintIndex, d));
				std::cout << d+1 << ": Index: " << ind[d+1] << " Val: " << val[d+1] << std::endl;
			}
			glp_set_mat_row(glpkProblem, constraintIndex+1, constraints.cols(), ind, val);
			glp_set_row_bnds(glpkProblem, constraintIndex+1, GLP_UP, -carl::convert<Number,double>(constants(constraintIndex)), 0.0 );

			glp_term_out(GLP_ON);
			glp_simplex( glpkProblem, NULL);
			//glp_exact( glpkProblem, NULL );

			if(glp_get_status(glpkProblem) == GLP_NOFEAS || glp_get_status(glpkProblem) == GLP_INFEAS) {
				std::cout << "Redundant constraint no. " << constraintIndex << std::endl;
				res.push_back(constraintIndex);
			}

			// revert constraint
			std::cout << "revert constraint." << std::endl;
			for(unsigned d = 0; d < constraints.cols(); ++d) {
				ind[d+1] = d+1;
				val[d+1] = carl::convert<Number,double>(constraints(constraintIndex, d));
				std::cout << d+1 << ": Index: " << ind[d+1] << " Val: " << val[d+1] << std::endl;
			}
			glp_set_mat_row(glpkProblem, constraintIndex+1, constraints.cols(), ind, val);
			glp_set_row_bnds(glpkProblem, constraintIndex+1, GLP_UP, -carl::convert<Number,double>(constants(constraintIndex)), 0.0 );
		}
		delete[] ind;
		delete[] val;

		std::cout << "DONE." << std::endl;

		return res;
	}
} // namespace hypro
