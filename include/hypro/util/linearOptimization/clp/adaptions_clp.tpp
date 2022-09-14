/**
 *
 */
#ifdef HYPRO_USE_CLP
#include "adaptions_clp.h"

namespace hypro {

template <typename Number>
EvaluationResult<Number> clpOptimizeLinearPostSolve( clp_context& context, const vector_t<Number>& _direction, const matrix_t<Number>& constraints, const vector_t<Number>& constants, bool useExact, const EvaluationResult<Number>& preSolution ) {
	// Add presolution as new row constraint to the lp
	int* rowIndices = new int[constraints.cols()];
	double* rowValues = new double[constraints.cols()];
	double rowLowerBound;
	double rowUpperBound;
	for ( int i = 0; i < constraints.cols(); ++i ) {
		rowValues[i] = toDouble( _direction( i ) );
		rowIndices[i] = i;
	}
	if ( context.lp.optimizationDirection() == -1 ) {
		rowUpperBound = COIN_DBL_MAX;
		rowLowerBound = toDouble( preSolution.supportValue );
	} else {
		rowUpperBound = toDouble( preSolution.supportValue );
		rowLowerBound = -COIN_DBL_MAX;
	}
	context.lp.addRow( constraints.cols(), rowIndices, rowValues, rowLowerBound, rowUpperBound );

	// Evaluate new problem
	EvaluationResult<Number> res = clpOptimizeLinear( context, _direction, constraints, constants, useExact );
	if ( res.errorCode == SOLUTION::INFEAS ) {
		res = preSolution;
	}

	// Restore original problem
	context.lp.loadProblem( context.matrix, context.mColumnLowerBounds, context.mColumnUpperBounds, nullptr, context.mLowerBounds, context.mUpperBounds );

	delete[] rowIndices;
	delete[] rowValues;
	return res;
}

template <typename Number>
EvaluationResult<Number> clpOptimizeLinear( clp_context& context, const vector_t<Number>& _direction, const matrix_t<Number>& constraints, const vector_t<Number>&, bool ) {
	double* objective = new double[constraints.cols()];
	// set objective
	for ( int i = 0; i < constraints.cols(); ++i ) {
		objective[i] = toDouble( _direction( i ) );
	}
	// remove bounds on columns
	for ( int i = 0; i < constraints.cols(); ++i ) {
		context.mColumnLowerBounds[i] = -COIN_DBL_MAX;
		context.mColumnUpperBounds[i] = COIN_DBL_MAX;
	}
	// load problem into problem instance
	context.lp.chgColumnLower( context.mColumnLowerBounds );
	context.lp.chgColumnUpper( context.mColumnUpperBounds );
	context.lp.chgObjCoefficients( objective );

	context.lp.primal();
	EvaluationResult<Number> res;
	if ( context.lp.primalFeasible() ) {
		// In this case there is a solution
		if ( context.lp.dualFeasible() ) {
			// optimal solution
			res.errorCode = SOLUTION::FEAS;
		} else {
			// unbounded
			res.errorCode = SOLUTION::INFTY;
		}
		const double* solution = context.lp.primalColumnSolution();
		res.optimumValue = vector_t<Number>( constraints.cols() );
		for ( int i = 0; i < constraints.cols(); ++i ) {
			if ( solution[i] ) {
				res.optimumValue( i ) = carl::convert<double, Number>( solution[i] );
			}
		}
		res.supportValue = carl::convert<double, Number>( context.lp.objectiveValue() );
	} else {
		res = EvaluationResult<Number>( 0, vector_t<Number>::Zero( 1 ), SOLUTION::INFEAS );
	}
	delete[] objective;
	return res;
}

template <typename Number>
bool clpCheckPoint( clp_context& context, const matrix_t<Number>& constraints, const vector_t<Number>&, const Point<Number>& _point ) {
	assert( constraints.cols() == _point.rawCoordinates().rows() );

	// set column lower and upper bounds
	for ( int i = 0; i < constraints.cols(); ++i ) {
		context.mColumnLowerBounds[i] = toDouble( _point.rawCoordinates()( i ) );
		context.mColumnUpperBounds[i] = toDouble( _point.rawCoordinates()( i ) );
	}

	// load problem with fixed column and without objective
	context.lp.chgColumnLower( context.mColumnLowerBounds );
	context.lp.chgColumnUpper( context.mColumnUpperBounds );
	context.lp.chgObjCoefficients( nullptr );
	context.lp.primal();

	return context.lp.primalFeasible();
}

template <typename Number>
std::vector<std::size_t> clpRedundantConstraints( clp_context& context, const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relations ) {
	std::vector<std::size_t> res;

	// first call to check satisfiability
	for ( int i = 0; i < constraints.cols(); ++i ) {
		context.mColumnLowerBounds[i] = -COIN_DBL_MAX;
		context.mColumnUpperBounds[i] = COIN_DBL_MAX;
	}
	context.lp.chgColumnLower( context.mColumnLowerBounds );
	context.lp.chgColumnUpper( context.mColumnUpperBounds );
	context.lp.chgObjCoefficients( nullptr );
	context.lp.primal();

	if ( !context.lp.primalFeasible() ) {
		return res;
	}

	for ( std::size_t constraintIndex = std::size_t( constraints.rows() - 1 );; --constraintIndex ) {
		bool redundant = true;
		carl::Relation relation = relations[constraintIndex];
		EvaluationResult<Number> actualRes;
		EvaluationResult<Number> updatedRes;
		if ( relation == carl::Relation::LEQ || relation == carl::Relation::EQ ) {
			// test if upper bound is redundant
			context.lp.setOptimizationDirection( -1 );
			actualRes = clpOptimizeLinear( context, vector_t<Number>( constraints.row( constraintIndex ) ), constraints, constants, true );
			context.lp.setRowUpper( constraintIndex, COIN_DBL_MAX );
			updatedRes = clpOptimizeLinear( context, vector_t<Number>( constraints.row( constraintIndex ) ), constraints, constants, true );
			// actual solution is always bounded because of the constraint, so updated should still be bounded if redundant
			if ( actualRes.errorCode != updatedRes.errorCode || actualRes.supportValue != updatedRes.supportValue ) {
				redundant = false;
			}
		}
		if ( relation == carl::Relation::GEQ || relation == carl::Relation::EQ ) {
			// test if lower bound is redundant
			context.lp.setOptimizationDirection( 1 );
			actualRes = clpOptimizeLinear( context, vector_t<Number>( constraints.row( constraintIndex ) ), constraints, constants, true );
			context.lp.setRowLower( constraintIndex, -COIN_DBL_MAX );
			updatedRes = clpOptimizeLinear( context, vector_t<Number>( constraints.row( constraintIndex ) ), constraints, constants, true );
			// actual solution is always bounded because of the constraint, so updated should still be bounded if redundant
			if ( actualRes.errorCode != updatedRes.errorCode || actualRes.supportValue != updatedRes.supportValue ) {
				redundant = false;
			}
		}

		if ( redundant ) {
			res.push_back( constraintIndex );
		} else {
			if ( relation == carl::Relation::LEQ || relation == carl::Relation::EQ ) {
				context.lp.setRowUpper( constraintIndex, toDouble( constants( constraintIndex ) ) );
			}
			if ( relation == carl::Relation::GEQ || relation == carl::Relation::EQ ) {
				context.lp.setRowLower( constraintIndex, toDouble( constants( constraintIndex ) ) );
			}
		}

		if ( constraintIndex == 0 ) {
			break;
		}
	}

	// restore original problem
	context.lp.chgRowUpper( context.mUpperBounds );
	context.lp.chgRowLower( context.mLowerBounds );

	return res;
}

template <typename Number>
EvaluationResult<Number> clpGetInternalPoint( clp_context& context ) {
	// remove bounds on columns
	for ( int i = 0; i < context.matrix.getNumCols(); ++i ) {
		context.mColumnLowerBounds[i] = -COIN_DBL_MAX;
		context.mColumnUpperBounds[i] = COIN_DBL_MAX;
	}
	context.lp.chgColumnLower( context.mColumnLowerBounds );
	context.lp.chgColumnUpper( context.mColumnUpperBounds );
	context.lp.chgObjCoefficients( nullptr );
	context.lp.primal();

	EvaluationResult<Number> res;
	if ( context.lp.primalFeasible() ) {
		res.errorCode = SOLUTION::FEAS;
		const double* solution = context.lp.primalColumnSolution();
		res.optimumValue = vector_t<Number>( context.matrix.getNumCols() );
		for ( int i = 0; i < context.matrix.getNumCols(); i++ ) {
			if ( solution[i] ) {
				res.optimumValue( i ) = carl::convert<double, Number>( solution[i] );
			}
		}
		res.supportValue = carl::convert<double, Number>( context.lp.objectiveValue() );
	} else {
		res = EvaluationResult<Number>( 0, vector_t<Number>::Zero( 1 ), SOLUTION::INFEAS );
	}
	return res;
}

}  // namespace hypro
#endif
