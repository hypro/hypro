#include <hypro/flags.h>
#ifdef HYPRO_USE_Z3

#include "hypro/util/linearOptimization/Optimizer.h"
#include "hypro/util/linearOptimization/z3/adaptions_z3.h"

namespace hypro {

// specialization for double to get result directly from z3 via Z3_get_numeral_double
template <>
EvaluationResult<double> z3OptimizeLinear( bool maximize, const vector_t<double>& _direction, const matrix_t<double>& constraints, const vector_t<double>& constants, const std::vector<carl::Relation>& relations ) {
	EvaluationResult<double> res;
	z3Context c;
	z3::optimize z3Optimizer( c );
	std::vector<z3::expr> variables;

	// create formula and objective
	std::pair<z3::expr, z3::expr> formulaObjectivePair = createFormula<double>( constraints, constants, relations, _direction, c, variables );

	// inform and add constraints
	z3Optimizer.add( formulaObjectivePair.first );
	/*
	#ifdef USE_PRESOLUTION
		z3Optimizer.push();
		if ( preSolution.errorCode == SOLUTION::FEAS ) {
			addPreSolution( z3Optimizer, c, preSolution, _direction, formulaObjectivePair.second );
		} else if ( preSolution.errorCode == SOLUTION::INFEAS ) {
			if ( z3Optimizer.check() == z3::unsat ) {
				return preSolution;  // glpk correctly detected infeasibility.
			}						 // if glpk falsely detected infeasibility, we cope with this case below.
		} else {					 // if glpk already detected unboundedness we return its result.
			return preSolution;
		}
	#endif
	*/
	// optimize with objective function
	z3::optimize::handle result( 0 );
	if ( maximize ) {
		result = z3Optimizer.maximize( formulaObjectivePair.second );
	} else {
		result = z3Optimizer.minimize( formulaObjectivePair.second );
	}

	// verify and set result
	if ( z3::sat == z3Optimizer.check() ) {
		z3::expr z3res = maximize ? z3Optimizer.upper( result ) : z3Optimizer.lower( result );
		assert( z3res.is_arith() );

		z3::model m = z3Optimizer.get_model();
		// check whether unbounded
		std::stringstream sstr;
		sstr << z3res;

		if ( sstr.str() == std::string( "oo" ) || sstr.str() == std::string( "(* (- 1) oo)" ) ) {
			res = EvaluationResult<double>( 1, SOLUTION::INFTY );
		} else {
			// int* enumerator = new int;
			// Z3_get_numeral_int( c, Z3_get_numerator( c, z3res ), enumerator );
			res.supportValue = double( Z3_get_numeral_double( c, z3res ) );
			vector_t<double> pointCoordinates = vector_t<double>::Zero( constraints.cols() );
			for ( unsigned i = 0; i < variables.size(); ++i ) {
				z3::func_decl tmp = variables.at( i ).decl();
				if ( Z3_model_get_const_interp( c, m, tmp ) != nullptr ) {
					pointCoordinates( i ) = double( Z3_get_numeral_double( c, m.get_const_interp( tmp ) ) );
				}
			}
			res.errorCode = SOLUTION::FEAS;
			res.optimumValue = pointCoordinates;
		}
	} else {
		res = EvaluationResult<double>( 0, SOLUTION::INFEAS );
	}
	return res;
}

}  // namespace hypro

#endif
