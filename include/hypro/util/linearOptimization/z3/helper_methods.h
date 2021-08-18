#pragma once
#include "z3Context.h"

#include <z3.h>

namespace hypro {

template <typename Number>
void addPreSolution( z3::optimize& solver, z3Context& c, const EvaluationResult<Number>& preSolution, const vector_t<Number>& direction, const z3::expr& objective ) {
	// add assignment from presolution

	z3::expr_vector constraints( c );
	z3::expr_vector variables( c );
	for ( unsigned i = 0; i < direction.rows(); ++i ) {
		z3::expr var( c );
		const char* varName = ( "x_" + std::to_string( i ) ).c_str();
		var = c.real_const( varName );
		variables.push_back( var );
		// TRACE( "hypro.optimizer", "Created z3 Variable " << var );
	}
	// TRACE( "hypro.optimizer", "Variables.size() " << variables.size() );

	// create and add bound constraints
	for ( unsigned i = 0; i < direction.rows(); ++i ) {
		if ( direction( i ) != 0 ) {
			z3::expr coeff( c );
			coeff = c.real_val( ( carl::convert<Number, mpq_class>( preSolution.optimumValue( i ) ) ) );
			// TRACE( "hypro.optimizer", "Coefficient is " << coeff );

			z3::expr bound( c );
			// TRACE( "hypro.optimizer", "Variable is " << variables[j] );
			bound = variables[i] - coeff;
			if ( direction( i ) > 0 ) {
				z3::expr constraint( bound >= 0 );
				solver.add( constraint );
			} else {
				z3::expr constraint( bound <= 0 );
				solver.add( constraint );
			}
		}
	}

	// add constraint for improvement of glpk solution.
	z3::expr preSolutionPolynomial = objective - c.real_val( carl::convert<Number, mpq_class>( preSolution.supportValue ) );
	z3::expr preSolutionConstraint( preSolutionPolynomial >= 0 );

	// TRACE( "hypro.optimizer", "Inform and add improvement constraint " << preSolutionConstraint );
	solver.add( preSolutionConstraint );
}

}  // namespace hypro
