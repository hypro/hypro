
#pragma once
#include "adaptions_soplex.h"

namespace hypro {

template <typename Number>
soplex::SoPlex initializeSolver( const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relations ) {
	soplex::SoPlex solver;

	solver.setIntParam( soplex::SoPlex::CHECKMODE, soplex::SoPlex::CHECKMODE_RATIONAL );
	solver.setIntParam( soplex::SoPlex::SOLVEMODE, soplex::SoPlex::SOLVEMODE_RATIONAL );
	solver.setIntParam( soplex::SoPlex::READMODE, soplex::SoPlex::READMODE_RATIONAL );
	solver.setIntParam( soplex::SoPlex::SYNCMODE, soplex::SoPlex::SYNCMODE_AUTO );
	solver.setIntParam( soplex::SoPlex::VERBOSITY, soplex::SoPlex::VERBOSITY_ERROR );
	solver.setRealParam( soplex::SoPlex::FEASTOL, 0.0 );
	solver.setRealParam( soplex::SoPlex::OPTTOL, 0.0 );

	// Add free variables without objective
	soplex::DSVectorRational columns( 0 );
	for ( unsigned varCount = 0; varCount < constraints.cols(); ++varCount ) {
		solver.addColRational( soplex::LPColRational( soplex::Rational( 0 ), columns, soplex::infinity, soplex::Rational( -1 ) * soplex::infinity ) );
	}

	// Add constraints
	for ( unsigned rowIndex = 0; rowIndex < constraints.rows(); ++rowIndex ) {
		// Create row
		soplex::DSVectorRational row( constraints.cols() );
		for ( unsigned colIndex = 0; colIndex < constraints.cols(); ++colIndex ) {
			mpq_t a;
			mpq_init( a );
			mpq_set( a, ( carl::convert<Number, mpq_class>( constraints( rowIndex, colIndex ) ) ).get_mpq_t() );
			row.add( colIndex, soplex::Rational( a ) );
			mpq_clear( a );
		}

		// Set bounds on row
		mpq_t a;
		mpq_init( a );
		mpq_set( a, ( carl::convert<Number, mpq_class>( constants( rowIndex ) ) ).get_mpq_t() );
		switch( relations[ rowIndex ] ) {
			case carl::Relation::LEQ:
				solver.addRowRational( soplex::LPRowRational( soplex::Rational( -1 ) * soplex::infinity, row, soplex::Rational( a ) ) );
				break;
			case carl::Relation::GEQ:
				solver.addRowRational( soplex::LPRowRational( soplex::Rational( a ) , row, soplex::infinity ) );
				break;
			case carl::Relation::EQ:
				solver.addRowRational( soplex::LPRowRational( soplex::Rational( a ) , row, soplex::Rational( a ) ) );
				break;
			default:
				// cannot handle strict inequalities.
				assert( false );
				std::cout << "This should not happen." << std::endl;
		}
		mpq_clear( a );
	}

	return solver;
}

template <typename Number>
EvaluationResult<Number> soplexOptimizeLinear( const vector_t<Number>& _direction, const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relations, bool maximize ) {
	
	soplex::SoPlex solver = initializeSolver( constraints, constants, relations );
	if ( maximize ) {
		solver.setIntParam( soplex::SoPlex::OBJSENSE, soplex::SoPlex::OBJSENSE_MAXIMIZE );
	} else {
		solver.setIntParam( soplex::SoPlex::OBJSENSE, soplex::SoPlex::OBJSENSE_MINIMIZE );
	}

	// set objective
	for ( unsigned varIndex = 0; varIndex < _direction.rows(); ++varIndex ) {
		mpq_t a;
		mpq_init( a );
		mpq_set( a, ( carl::convert<Number, mpq_class>( _direction( varIndex ) ) ).get_mpq_t() );
		solver.changeObjRational( varIndex, a );
		mpq_clear( a );
	}

	/* solve LP */
	soplex::SPxSolver::Status stat;
	soplex::DVectorRational prim( constraints.cols() );
	soplex::DVectorRational dual( constraints.rows() );
	stat = solver.solve();

	switch ( stat ) {
		case soplex::SPxSolver::OPTIMAL: {
			vector_t<Number> optimalPoint = vector_t<Number>( constraints.cols() );
			solver.getPrimalRational( prim );
			for ( unsigned colIndex = 0; colIndex < constraints.cols(); ++colIndex ) {
				optimalPoint( colIndex ) = carl::convert<mpq_class, Number>( mpq_class( *( prim[colIndex] ).getMpqPtr() ) );
			}
			//std::cout << "Result evaluation (optimal): " << EvaluationResult<Number>(carl::convert<mpq_class,Number>(mpq_class(*(solver.objValueRational()).getMpqPtr())), optimalPoint, SOLUTION::FEAS) << std::endl;
			//std::cout << "Optimal point: " <<  optimalPoint << std::endl;
			return EvaluationResult<Number>( carl::convert<mpq_class, Number>( mpq_class( *( solver.objValueRational() ).getMpqPtr() ) ), optimalPoint, SOLUTION::FEAS );
		}
		case soplex::SPxSolver::UNBOUNDED: {
			return EvaluationResult<Number>( SOLUTION::INFTY );
		}
		case soplex::SPxSolver::INFEASIBLE: {
			return EvaluationResult<Number>( SOLUTION::INFEAS );
		}
		default:
			assert( false );
			return EvaluationResult<Number>();
	}
}



template <typename Number>
bool soplexCheckConsistency( const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relations ) {
	
	soplex::SoPlex solver = initializeSolver( constraints, constants, relations );

	/* solve LP */
	solver.solve();
	return solver.isPrimalFeasible();
}

template <typename Number>
bool soplexCheckPoint( const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relations, const Point<Number>& point ) {
	
	soplex::SoPlex solver = initializeSolver( constraints, constants, relations );
	for( unsigned varIndex = 0; varIndex < constraints.cols(); ++varIndex ) {
		mpq_t a;
		mpq_init( a );
		mpq_set( a, ( carl::convert<Number, mpq_class>( point.at( varIndex ) ) ).get_mpq_t() );
		solver.changeBoundsRational( varIndex, soplex::Rational( a ), soplex::Rational( a ) );
		mpq_clear( a );
	}

	/* solve LP */
	solver.solve();
	return solver.isPrimalFeasible();
}

}  // namespace hypro
