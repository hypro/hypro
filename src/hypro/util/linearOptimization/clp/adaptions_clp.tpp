/**
 *
 */
#ifdef HYPRO_USE_CLP
#include "adaptions_clp.h"

namespace hypro {

template <typename Number>
EvaluationResult<Number> clpOptimizeLinear( clp_context& context, const vector_t<Number>& _direction, const matrix_t<Number>& constraints, const vector_t<Number>&, bool ) {
	double* objective = new double[ constraints.cols() ];
	// set objective
	for ( int i = 0; i < constraints.cols(); ++i ) {
		objective[i] = carl::toDouble( _direction( i ) );
	}
	// remove lower bounds on columns    
    for(int i = 0; i < constraints.cols(); ++i){
    	context.mColumnLowerBounds[i] = -COIN_DBL_MAX;
    }
    // load problem into problem instance
	context.lp.loadProblem( context.matrix, context.mColumnLowerBounds, nullptr, objective, context.mLowerBounds, context.mUpperBounds );

	context.lp.primal();
	EvaluationResult<Number> res;
	if ( context.lp.primalFeasible() ) {
		res.errorCode = SOLUTION::FEAS;
		const double* solution = context.lp.primalColumnSolution();
		res.optimumValue = vector_t<Number>( constraints.cols() );
		for ( int i = 0; i < constraints.cols(); ++i ) {
			if ( solution[i] ) {
				res.optimumValue( i ) = carl::convert<double, Number>( solution[i] );
			}
		}
		res.supportValue = carl::convert<double, Number>( context.lp.objectiveValue() );
	} else {
		res.errorCode = SOLUTION::INFEAS;
	}
	delete[] objective;
	return res;
}

template <typename Number>
bool clpCheckPoint( clp_context& context, const matrix_t<Number>& constraints, const vector_t<Number>&, const Point<Number>& _point ) {
	assert( constraints.cols() == _point.rawCoordinates().rows() );

	// set column lower and upper bounds	
	for ( int i = 0; i < constraints.cols(); ++i ){
		context.mColumnLowerBounds[i] = carl::toDouble( _point.rawCoordinates()( i ) );
		context.mColumnUpperBounds[i] = carl::toDouble( _point.rawCoordinates()( i ) );
	}

	// load problem with fixed column and without objective
	context.lp.loadProblem( context.matrix, context.mColumnLowerBounds, context.mColumnUpperBounds, nullptr, context.mLowerBounds, context.mUpperBounds );
	context.lp.primal();

	return context.lp.primalFeasible();
}

template <typename Number>
std::vector<std::size_t> clpRedundantConstraints( clp_context& context, const matrix_t<Number>& constraints, const vector_t<Number>& constants, std::vector<carl::Relation>& relations ) {
	std::vector<std::size_t> res;

	// first call to check satisfiability
    for(int i = 0; i < constraints.cols(); ++i){
    	context.mColumnLowerBounds[i] = -COIN_DBL_MAX;
    }
	context.lp.loadProblem( context.matrix, context.mColumnLowerBounds, nullptr, nullptr, context.mLowerBounds, context.mUpperBounds );
	context.lp.primal();

	if ( !context.lp.primalFeasible() ) {
		return res;
	}


	for ( std::size_t constraintIndex = std::size_t( constraints.rows() - 1 );; --constraintIndex ) {
		EvaluationResult<Number> actualRes = clpOptimizeLinear( context, vector_t<Number>( constraints.row( constraintIndex ) ), constraints, constants, true );

		// remove constraint by removing the boundaries
		context.mUpperBounds[ int( constraintIndex ) ] = COIN_DBL_MAX;
		context.mLowerBounds[ int( constraintIndex ) ] = -COIN_DBL_MAX;
		EvaluationResult<Number> updatedRes;

		switch ( relations[ constraintIndex ] ){
			case carl::Relation::LEQ:
				context.lp.setOptimizationDirection(-1);
				updatedRes = clpOptimizeLinear( context, vector_t<Number>( constraints.row( constraintIndex ) ), constraints, constants, true );
				if ( updatedRes.optimumValue == actualRes.optimumValue ) {
					res.push_back( constraintIndex );
				} else {
					context.mUpperBounds[ constraintIndex ] = carl::toDouble( constants( constraintIndex ) );
				}
				break;
			case carl::Relation::GEQ:
				context.lp.setOptimizationDirection(1);
				updatedRes = clpOptimizeLinear( context, vector_t<Number>( constraints.row( constraintIndex ) ), constraints, constants, true );
				if ( updatedRes.optimumValue == actualRes.optimumValue ) {
					res.push_back( constraintIndex );
				} else {
					context.mLowerBounds[ constraintIndex ] = carl::toDouble( constants( constraintIndex ) );
				}
				break;
			case carl::Relation::EQ:
				context.lp.setOptimizationDirection(-1);
				updatedRes = clpOptimizeLinear( context, vector_t<Number>( constraints.row( constraintIndex ) ), constraints, constants, true );
				if ( updatedRes.optimumValue != actualRes.optimumValue ){
					context.mLowerBounds[ constraintIndex ] = carl::toDouble( constants( constraintIndex ) );
					context.mUpperBounds[ constraintIndex ] = carl::toDouble( constants( constraintIndex ) );
				} else {
					context.lp.setOptimizationDirection(1);
					updatedRes = clpOptimizeLinear( context, vector_t<Number>( constraints.row( constraintIndex ) ), constraints, constants, true );
					if ( updatedRes.optimumValue == actualRes.optimumValue ) {
						res.push_back( constraintIndex );
					} else {
						context.mLowerBounds[ constraintIndex ] = carl::toDouble( constants( constraintIndex ) );
						context.mUpperBounds[ constraintIndex ] = carl::toDouble( constants( constraintIndex ) );
					}
				}
				break;
			default:
				// clp cannot handle strict inequalities.
				assert( false );
				std::cout << "This should not happen." << std::endl;
		}
		if ( constraintIndex == 0 ) {
			break;
		}
	}

	// restore original problem
	for ( const auto item : res ) {
		switch ( relations[ int( item ) ] ){
			case carl::Relation::LEQ:
				context.mUpperBounds[ int( item ) ] = carl::toDouble( constants( item ) );
				break;
			case carl::Relation::GEQ:
				context.mLowerBounds[ int( item ) ] = carl::toDouble( constants( item ) );
				break;
			case carl::Relation::EQ:
				context.mUpperBounds[ int( item ) ] = carl::toDouble( constants( item ) );
				context.mLowerBounds[ int( item ) ] = carl::toDouble( constants( item ) );
				break;
			default:
				// clp cannot handle strict inequalities.
				assert( false );
				std::cout << "This should not happen." << std::endl;
		}
	}

	return res;
}

template <typename Number>
EvaluationResult<Number> clpGetInternalPoint( clp_context& context ) {
	// remove lower bounds on columns
    for(int i = 0; i < context.matrix.getNumCols(); ++i){
    	context.mColumnLowerBounds[i] = -COIN_DBL_MAX;
    }
	context.lp.loadProblem( context.matrix, context.mColumnLowerBounds, nullptr, nullptr, context.mLowerBounds, context.mUpperBounds );
	context.lp.setOptimizationDirection(0);
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
