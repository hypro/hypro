/**
 *
 */
#ifdef HYPRO_USE_CLP
#include "adaptions_clp.h"

namespace hypro {

template <typename Number>
EvaluationResult<Number> clpOptimizeLinear( clp_context& context, const vector_t<Number>& _direction, const matrix_t<Number>& constraints, const vector_t<Number>& constants, bool useExact ) {
	// create objective
	double objective[_direction.rows()];
	// set objective
	for ( int i = 0; i < _direction.cols(); ++i ) {
		objective[i] = carl::toDouble( _direction( i ) );
	}
	// load problem into problem instance
	context.lp.loadProblem( context.matrix, nullptr, nullptr, objective, context.mLowerBounds, context.mUpperBounds );

	context.lp.primal();
	if ( context.lp.primalFeasible() ) {
		const double* solution = context.lp.primalColumnSolution();
		int i;
		EvaluationResult<Number> res;
		res.optimumValue = vector_t<Number>( _direction.cols() );
		for ( i = 0; i < _direction.cols(); i++ ) {
			if ( solution[i] ) {
				res.optimumValue( i ) = carl::convert<double, Number>( solution[i] );
			}
		}
	} else {
		return EvaluationResult<Number>( SOLUTION::INFEAS );
	}
}

template <typename Number>
bool clpCheckPoint( clp_context& context, const matrix_t<Number>& constraints, const vector_t<Number>& constants, const Point<Number>& _point ) {
}

template <typename Number>
std::vector<std::size_t> clpRedundantConstraints( clp_context& context, const matrix_t<Number>& constraints, const vector_t<Number>& constants ) {
}

template <typename Number>
EvaluationResult<Number> clpGetInternalPoint( clp_context& context ) {
}

}  // namespace hypro
#endif
