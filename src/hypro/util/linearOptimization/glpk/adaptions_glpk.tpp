/**
 *
 */
#include "adaptions_glpk.h"

namespace hypro {

inline void printProblem( glp_prob* glpkProblem ) {
	int cols = glp_get_num_cols( glpkProblem );
	int* ind = new int[unsigned( cols ) + 1];
	double* val = new double[unsigned( cols ) + 1];
	for ( int i = 1; i <= glp_get_num_rows( glpkProblem ); ++i ) {
		int nonZeroCount = glp_get_mat_row( glpkProblem, i, ind, val );
		for ( int colIndex = 1; colIndex <= cols; ++colIndex ) {
			bool found = false;
			// glpk always starts indexing at 1 -> we can skip the element at 0
			for ( int arrayIndex = 1; arrayIndex < nonZeroCount + 1; ++arrayIndex ) {
				if ( ind[arrayIndex] == colIndex ) {
					found = true;
					std::cout << val[arrayIndex] << "\t";
				}
			}
			if ( !found ) {
				std::cout << "0\t";
			}
		}
		/*
			if( glp_get_row_type(glpkProblem,i) == GLP_UP ) {
				//std::cout << " <= " << glp_get_row_ub(glpkProblem,i) << std::endl;
			} else if ( glp_get_row_type(glpkProblem,i) == GLP_FR ) {
				//std::cout << " <= +INF" << std::endl;
			}
			*/
	}
	delete[] ind;
	delete[] val;
}

template <typename Number>
vector_t<Number> refineSolution( glpk_context& context, const matrix_t<Number>& constraints, const vector_t<Number>& constants ) {
	matrix_t<Number> exactSolutionMatrix = matrix_t<Number>::Zero( constraints.cols(), constraints.cols() );
	vector_t<Number> exactSolutionVector = vector_t<Number>::Zero( constraints.cols() );
	unsigned pos = 0;
	if ( glp_get_obj_dir( context.lp ) == GLP_MAX ) {
		for ( unsigned i = 1; i <= constraints.rows(); ++i ) {
			// we search for d non-basic variables at their upper bound, which define the optimal point.
			if ( glp_get_row_stat( context.lp, i ) == GLP_NU ) {
				exactSolutionMatrix.row( pos ) = constraints.row( i - 1 );
				exactSolutionVector( pos ) = constants( i - 1 );
				++pos;
			}
		}
	} else {
		assert( glp_get_obj_dir( context.lp ) == GLP_MIN );
		for ( unsigned i = 1; i <= constraints.rows(); ++i ) {
			// we search for d non-basic variables at their lower bound, which define the optimal point.
			if ( glp_get_row_stat( context.lp, i ) == GLP_NL ) {
				exactSolutionMatrix.row( pos ) = constraints.row( i - 1 );
				exactSolutionVector( pos ) = constants( i - 1 );
				++pos;
			}
		}
	}
	// solve and return
	return Eigen::FullPivLU<matrix_t<Number>>( exactSolutionMatrix ).solve( exactSolutionVector );
}

template <typename Number>
EvaluationResult<Number> glpkOptimizeLinearPostSolve( glpk_context& context, const vector_t<Number>& _direction, const matrix_t<Number>& constraints, const vector_t<Number>& constants, bool useExact, const EvaluationResult<Number>& preSolution  ) {
	
	// Add presolution as new row constraint to the lp
	// Create row:
	glp_add_rows( context.lp, 1 );
	int* rowIndices = new int[ constraints.cols()+1 ];
	double* rowValues = new double[ constraints.cols()+1 ];
	for ( int i = 0; i <= constraints.cols(); ++i ) {
		rowValues[i] = carl::toDouble( _direction( i-1 ) );
		rowIndices[i] = i;
	}
	// Add row to problem:
	glp_set_mat_row( context.lp, constraints.rows() + 1, constraints.cols(), rowIndices, rowValues );

	// Set presolution bound:
	if( glp_get_obj_dir( context.lp ) == GLP_MAX ) {
		glp_set_row_bnds( context.lp, constraints.rows()+1, GLP_LO, carl::toDouble( preSolution.supportValue ), 0.0 );
	} else{
		assert( glp_get_obj_dir( context.lp ) == GLP_MIN );
		glp_set_row_bnds( context.lp, constraints.rows()+1, GLP_UP, 0.0, carl::toDouble( preSolution.supportValue ) );
	}

	EvaluationResult<Number> res = glpkOptimizeLinear( context, _direction, constraints, constants, useExact );
	if ( res.errorCode == SOLUTION::INFEAS ) {
		// glpk thinks the solution is infeasible, so we don't get an improvement
		res = preSolution;
	}

	// Restore original problem. Glp starts indexing at 1 so the first index does not matter
	int delRow[] = { 0, (int) constraints.rows() + 1 };
	glp_del_rows( context.lp, 1, delRow );
	
	delete[] rowIndices;
	delete[] rowValues;
	return res;


}

template <typename Number>
EvaluationResult<Number> glpkOptimizeLinear( glpk_context& context, const vector_t<Number>& _direction, const matrix_t<Number>& constraints, const vector_t<Number>& constants, bool useExact ) {
	/*
		std::cout << __func__ << " in direction " << convert<Number,double>(_direction).transpose() << std::endl;
		std::cout << __func__ << " constraints: " << std::endl << constraints << std::endl << "constants: " << std::endl << constants << std::endl << "Glpk Problem: " << std::endl;
		//printProblem(glpkProblem);
		*/

	// setup glpk
	for ( unsigned i = 0; i < constraints.cols(); i++ ) {
		glp_set_col_bnds( context.lp, i + 1, GLP_FR, 0.0, 0.0 );
		glp_set_obj_coef( context.lp, i + 1, carl::toDouble( _direction( i ) ) );
	}
	/* solve problem */
	if ( useExact ) {
		glp_exact( context.lp, &context.parm );
	} else {
		glp_simplex( context.lp, &context.parm );
	}

	vector_t<Number> exactSolution;
	switch ( glp_get_status( context.lp ) ) {
		case GLP_OPT:
		case GLP_FEAS: {
			// if satisfiable, derive exact solution by intersecting all constraints, which are at their upper respectively lower bounds .
			exactSolution = refineSolution( context, constraints, constants );
			return EvaluationResult<Number>( _direction.dot( exactSolution ), exactSolution, SOLUTION::FEAS );
			break;
		}
		case GLP_UNBND: {
			vector_t<Number> glpkModel( constraints.cols() );
			for ( unsigned i = 1; i <= constraints.cols(); ++i ) {
				glpkModel( i - 1 ) = carl::rationalize<Number>( glp_get_col_prim( context.lp, i ) );
			}
			return EvaluationResult<Number>( 1, glpkModel, SOLUTION::INFTY );
			break;
		}
		default:
			return EvaluationResult<Number>( 0, vector_t<Number>::Zero( 1 ), SOLUTION::INFEAS );
	}
}

template <typename Number>
bool glpkCheckPoint( glpk_context& context, const matrix_t<Number>& constraints, const vector_t<Number>&, const Point<Number>& point ) {
	// set point
	assert( constraints.cols() == point.rawCoordinates().rows() );
	for ( unsigned i = 0; i < constraints.cols(); ++i ) {
		glp_set_col_bnds( context.lp, i + 1, GLP_FX, carl::toDouble( point.rawCoordinates()( i ) ), 0.0 );
		glp_set_obj_coef( context.lp, i + 1, 1.0 );  // not needed?
	}
	glp_simplex( context.lp, &context.parm );
	glp_exact( context.lp, &context.parm );
	return ( glp_get_status( context.lp ) != GLP_NOFEAS );
}

template <typename Number>
std::vector<std::size_t> glpkRedundantConstraints( glpk_context& context, matrix_t<Number> constraints, vector_t<Number> constants, std::vector<carl::Relation>& relations ) {
	std::vector<std::size_t> res;

	// TODO: ATTENTION: This relies upon that glpk maintains the order of the constraints!
	for ( unsigned i = 0; i < constraints.cols(); ++i ) {
		glp_set_col_bnds( context.lp, i + 1, GLP_FR, 0.0, 0.0 );
		glp_set_obj_coef( context.lp, i + 1, 1.0 );  // not needed?
	}

	// first call to check satisfiability
	glp_simplex( context.lp, &context.parm );
	glp_exact( context.lp, &context.parm );

	switch ( glp_get_status( context.lp ) ) {
		case GLP_INFEAS:
		case GLP_NOFEAS:
			return res;
		default:
			break;
	}

	for ( std::size_t constraintIndex = std::size_t( constraints.rows() - 1 );; --constraintIndex ) {
		bool redundant = true;
		carl::Relation relation = relations[ constraintIndex ];
		EvaluationResult<Number> actualRes;
		EvaluationResult<Number> updatedRes;
		if ( relation == carl::Relation::LEQ || relation == carl::Relation::EQ ) {
			// test if upper bound is redundant
			glp_set_obj_dir( context.lp, GLP_MAX );
			actualRes = glpkOptimizeLinear( context, vector_t<Number>( constraints.row( constraintIndex ) ), constraints, constants, true );
			glp_set_row_bnds( context.lp, int( constraintIndex ) + 1, GLP_FR, 0.0, 0.0 );
			updatedRes = glpkOptimizeLinear( context, vector_t<Number>( constraints.row( constraintIndex ) ), constraints, constants, true );
			// actual solution is always bounded because of the constraint, so updated should still be bounded if redundant
			if ( actualRes.errorCode != updatedRes.errorCode || actualRes.supportValue != updatedRes.supportValue ){
				redundant = false;
			}
		}
		if ( relation == carl::Relation::GEQ || relation == carl::Relation::EQ ){
			// test if lower bound is redundant
			glp_set_obj_dir( context.lp, GLP_MIN );
			actualRes = glpkOptimizeLinear( context, vector_t<Number>( constraints.row( constraintIndex ) ), constraints, constants, true );
			glp_set_row_bnds( context.lp, int( constraintIndex ) + 1, GLP_FR, 0.0, 0.0 );
			updatedRes = glpkOptimizeLinear( context, vector_t<Number>( constraints.row( constraintIndex ) ), constraints, constants, true );
			// actual solution is always bounded because of the constraint, so updated should still be bounded if redundant
			if ( actualRes.errorCode != updatedRes.errorCode && actualRes.supportValue != updatedRes.supportValue ){
				redundant = false;
			}
		}

		if ( redundant ){
			res.push_back( constraintIndex );
		} else {
			// restore bound
			switch ( relation ) {
				case carl::Relation::LEQ:
					// set upper bounds, lb-values (here 0.0) are ignored.
					glp_set_row_bnds( context.lp, constraintIndex + 1, GLP_UP, 0.0, carl::toDouble( constants( constraintIndex ) ) );
					break;
				case carl::Relation::GEQ:
					// if it is an equality, the value is read from the lb-value, ub.values (here 0.0) are ignored.
					glp_set_row_bnds( context.lp, constraintIndex + 1, GLP_LO, carl::toDouble( constants( constraintIndex ) ), 0.0 );
					break;
				case carl::Relation::EQ:
					// if it is an equality, the value is read from the lb-value, ub.values (here 0.0) are ignored.
					glp_set_row_bnds( context.lp, constraintIndex + 1, GLP_FX, carl::toDouble( constants( constraintIndex ) ), 0.0 );
					break;
				default:
					// glpk cannot handle strict inequalities.
					assert( false );
					std::cout << "This should not happen." << std::endl;
			}
		}

		if ( constraintIndex == 0 ){
			break;
		}
	}

	// restore original problem
	for ( const auto idx : res ) {
		switch ( relations[ idx ] ) {
			case carl::Relation::LEQ:
				// set upper bounds, lb-values (here 0.0) are ignored.
				glp_set_row_bnds( context.lp, idx + 1, GLP_UP, 0.0, carl::toDouble( constants( idx ) ) );
				break;
			case carl::Relation::GEQ:
				// if it is an equality, the value is read from the lb-value, ub.values (here 0.0) are ignored.
				glp_set_row_bnds( context.lp, idx + 1, GLP_LO, carl::toDouble( constants( idx ) ), 0.0 );
				break;
			case carl::Relation::EQ:
				// if it is an equality, the value is read from the lb-value, ub.values (here 0.0) are ignored.
				glp_set_row_bnds( context.lp, idx + 1, GLP_FX, carl::toDouble( constants( idx ) ), 0.0 );
				break;
			default:
				// glpk cannot handle strict inequalities.
				assert( false );
				std::cout << "This should not happen." << std::endl;
			}
	}

	return res;
}

template <typename Number>
EvaluationResult<Number> glpkGetInternalPoint( glpk_context& context, std::size_t dimension, bool useExact ) {
	glp_simplex( context.lp, &context.parm );
	if ( useExact ) {
		glp_exact( context.lp, &context.parm );
	}

	vector_t<Number> glpkModel( dimension );
	for ( int i = 1; i <= int( dimension ); ++i ) {
		glpkModel( i - 1 ) = glp_get_col_prim( context.lp, i );
	}

	switch ( glp_get_status( context.lp ) ) {
		case GLP_OPT:
		case GLP_FEAS:
			return EvaluationResult<Number>( glp_get_obj_val( context.lp ), glpkModel, SOLUTION::FEAS );
			break;
		case GLP_UNBND:
			return EvaluationResult<Number>( 1, glpkModel, SOLUTION::INFTY );
			break;
		default:
			return EvaluationResult<Number>( 0, vector_t<Number>::Zero( 1 ), SOLUTION::INFEAS );
	}
}
}  // namespace hypro
