/**
 *
 */
#pragma once
#include "../Optimizer.h"

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
} // namespace hypro
