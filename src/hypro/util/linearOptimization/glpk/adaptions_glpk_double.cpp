#include "adaptions_glpk.h"

namespace hypro {

template <>
EvaluationResult<double> glpkOptimizeLinear( glpk_context& context, const vector_t<double>& _direction, const matrix_t<double>& constraints, const vector_t<double>&, bool useExact ) {
	//std::cout << __func__ << " in direction " << _direction.transpose() << std::endl;
	//std::cout << __func__ << " constraints: " << std::endl << constraints << std::endl << "Glpk Problem: " << std::endl;
	//printProblem(glpkProblem);

	// setup glpk
	for ( int i = 0; i < constraints.cols(); i++ ) {
		glp_set_col_bnds( context.lp, i + 1, GLP_FR, 0.0, 0.0 );
		glp_set_obj_coef( context.lp, i + 1, carl::toDouble( _direction( i ) ) );
	}

	// scale problem to improve its stability
	glp_scale_prob( context.lp, GLP_SF_AUTO );

	/* solve problem */
	if ( useExact ) {
		glp_simplex( context.lp, &context.parm );
		glp_exact( context.lp, &context.parm );
	} else {
		glp_simplex( context.lp, &context.parm );
	}

	switch ( glp_get_status( context.lp ) ) {
		case GLP_OPT:
		case GLP_FEAS: {
			vector_t<double> glpkModel( constraints.cols() );
			for ( int i = 1; i <= constraints.cols(); ++i ) {
				glpkModel( i - 1 ) = glp_get_col_prim( context.lp, i );
			}

			return EvaluationResult<double>( glp_get_obj_val( context.lp ), glpkModel, SOLUTION::FEAS );
			break;
		}
		case GLP_UNBND: {
			vector_t<double> glpkModel( constraints.cols() );
			for ( int i = 1; i <= constraints.cols(); ++i ) {
				glpkModel( i - 1 ) = glp_get_col_prim( context.lp, i );
			}
			return EvaluationResult<double>( 1, glpkModel, SOLUTION::INFTY );
			break;
		}
		default:
			return EvaluationResult<double>( 0, vector_t<double>::Zero( 1 ), SOLUTION::INFEAS );
	}
}

template <>
bool glpkCheckPoint( glpk_context& context, const matrix_t<double>& constraints, const vector_t<double>&, const Point<double>& point ) {
	// set point
	assert( constraints.cols() == point.rawCoordinates().rows() );
	for ( int i = 0; i < constraints.cols(); ++i ) {
		glp_set_col_bnds( context.lp, i + 1, GLP_FX, point.rawCoordinates()( i ), 0.0 );
		glp_set_obj_coef( context.lp, i + 1, 1.0 );  // not needed?
	}
	glp_simplex( context.lp, &context.parm );
	return ( glp_get_status( context.lp ) != GLP_NOFEAS );
}

template <>
std::vector<std::size_t> glpkRedundantConstraints( glpk_context& context, matrix_t<double> constraints, vector_t<double> constants, std::vector<carl::Relation>& relations ) {
	std::vector<std::size_t> res;

	// TODO: ATTENTION: This relies upon that glpk maintains the order of the constraints!
	for ( int i = 0; i < constraints.cols(); ++i ) {
		glp_set_col_bnds( context.lp, i + 1, GLP_FR, 0.0, 0.0 );
		glp_set_obj_coef( context.lp, i + 1, 1.0 );  // not needed?
	}

	// first call to check satisfiability
	glp_simplex( context.lp, &context.parm );

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
		EvaluationResult<double> actualRes;
		EvaluationResult<double> updatedRes;
		if ( relation == carl::Relation::LEQ || relation == carl::Relation::EQ ) {
			// test if upper bound is redundant
			glp_set_obj_dir( context.lp, GLP_MAX );
			actualRes = glpkOptimizeLinear( context, vector_t<double>( constraints.row( constraintIndex ) ), constraints, constants, true );
			glp_set_row_bnds( context.lp, int( constraintIndex ) + 1, GLP_FR, 0.0, 0.0 );
			updatedRes = glpkOptimizeLinear( context, vector_t<double>( constraints.row( constraintIndex ) ), constraints, constants, true );
			// actual solution is always bounded because of the constraint, so updated should still be bounded if redundant
			if ( actualRes.errorCode != updatedRes.errorCode || actualRes.supportValue != updatedRes.supportValue ){
				redundant = false;
			}
		}
		if ( relation == carl::Relation::GEQ || relation == carl::Relation::EQ ){
			// test if lower bound is redundant
			glp_set_obj_dir( context.lp, GLP_MIN );
			actualRes = glpkOptimizeLinear( context, vector_t<double>( constraints.row( constraintIndex ) ), constraints, constants, true );
			glp_set_row_bnds( context.lp, int( constraintIndex ) + 1, GLP_FR, 0.0, 0.0 );
			updatedRes = glpkOptimizeLinear( context, vector_t<double>( constraints.row( constraintIndex ) ), constraints, constants, true );
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

}  // namespace hypro
