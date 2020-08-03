
#pragma once
#include "adaptions_soplex.h"

namespace hypro {

template <typename Number> 
EvaluationResult<Number> soplexOptimizeLinearPostSolve( const vector_t<Number>& direction, const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relations, bool maximize, const EvaluationResult<Number>& preSolution ) {
	
	soplex::SoPlex solver = detail::initializeSolver( constraints, constants, relations );

	// set objective
	for ( unsigned varIndex = 0; varIndex < direction.rows(); ++varIndex ) {
		mpq_t a;
		mpq_init( a );
		mpq_set( a, ( carl::convert<Number, mpq_class>( direction( varIndex ) ) ).get_mpq_t() );
		solver.changeObjRational( varIndex, a );
		mpq_clear( a );
	}

	// create new constraint row
	soplex::DSVectorRational directionRational( constraints.cols() );
    for ( unsigned colIndex = 0; colIndex < constraints.cols(); ++colIndex ) {
        mpq_t a;
        mpq_init( a );
        mpq_set( a, ( carl::convert<Number, mpq_class>( direction( colIndex ) ) ).get_mpq_t() );
        directionRational.add( colIndex, soplex::Rational( a ) );
        mpq_clear( a );
    }
    mpq_t supportValueRational;
	mpq_init( supportValueRational );
	mpq_set( supportValueRational, ( carl::convert<Number, mpq_class>( preSolution.supportValue ) ).get_mpq_t() );

	// set new constraint bound
	if ( maximize ) {
		solver.setIntParam( soplex::SoPlex::OBJSENSE, soplex::SoPlex::OBJSENSE_MAXIMIZE );
		solver.addRowRational( soplex::LPRowRational( soplex::Rational( supportValueRational ) , directionRational, soplex::infinity ) );
	} else {
		solver.setIntParam( soplex::SoPlex::OBJSENSE, soplex::SoPlex::OBJSENSE_MINIMIZE );
		solver.addRowRational( soplex::LPRowRational( soplex::Rational( -1 ) * soplex::infinity, directionRational, soplex::Rational( supportValueRational ) ) );
	}
	mpq_clear( supportValueRational );

	// solve new lp
	EvaluationResult<Number> postSolution = detail::extractSolution<Number>( solver );
	if ( postSolution.errorCode == SOLUTION::INFEAS ) {
		postSolution = preSolution;
	}
	return postSolution;
}


template <typename Number>
EvaluationResult<Number> soplexOptimizeLinear( const vector_t<Number>& direction, const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relations, bool maximize ) {
	
	soplex::SoPlex solver = detail::initializeSolver( constraints, constants, relations );
	if ( maximize ) {
		solver.setIntParam( soplex::SoPlex::OBJSENSE, soplex::SoPlex::OBJSENSE_MAXIMIZE );
	} else {
		solver.setIntParam( soplex::SoPlex::OBJSENSE, soplex::SoPlex::OBJSENSE_MINIMIZE );
	}

	// set objective
	for ( unsigned varIndex = 0; varIndex < direction.rows(); ++varIndex ) {
		mpq_t a;
		mpq_init( a );
		mpq_set( a, ( carl::convert<Number, mpq_class>( direction( varIndex ) ) ).get_mpq_t() );
		solver.changeObjRational( varIndex, a );
		mpq_clear( a );
	}

	/* solve LP */
	EvaluationResult<Number> res = detail::extractSolution<Number>( solver );
	return res;
}



template <typename Number>
bool soplexCheckConsistency( const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relations ) {
	
	soplex::SoPlex solver = detail::initializeSolver( constraints, constants, relations );

	/* solve LP */
	solver.solve();
	return solver.isPrimalFeasible();
}

template <typename Number>
bool soplexCheckPoint( const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relations, const Point<Number>& point ) {
	
	soplex::SoPlex solver = detail::initializeSolver( constraints, constants, relations );
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

template <typename Number>
std::vector<std::size_t> soplexRedundantConstraints( const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relations ) {
	std::vector<std::size_t> res;

	// first call to check satisfiability
	soplex::SoPlex solver = detail::initializeSolver( constraints, constants, relations );
	solver.solve();
	if( !solver.isPrimalFeasible() ) {
		return res;
	}

	for ( std::size_t constraintIndex = std::size_t( constraints.rows() - 1 );; --constraintIndex ) {
		bool redundant = true;
		carl::Relation relation = relations[ constraintIndex ];
		EvaluationResult<Number> actualRes;
		EvaluationResult<Number> updatedRes;

		for ( unsigned varIndex = 0; varIndex < constraints.cols(); ++varIndex ) {
			mpq_t a;
			mpq_init( a );
			mpq_set( a, ( carl::convert<Number, mpq_class>( constraints( constraintIndex, varIndex ) ) ).get_mpq_t() );
			solver.changeObjRational( varIndex, a );
			mpq_clear( a );
		}

		if ( relation == carl::Relation::LEQ || relation == carl::Relation::EQ ){
			solver.setIntParam( soplex::SoPlex::OBJSENSE, soplex::SoPlex::OBJSENSE_MAXIMIZE );
			actualRes = detail::extractSolution<Number>( solver );
			solver.changeRhsRational( constraintIndex,  soplex::infinity );
			updatedRes = detail::extractSolution<Number>( solver );
			if ( actualRes.errorCode != updatedRes.errorCode || actualRes.supportValue != updatedRes.supportValue ){
				redundant = false;
			}
		}
		if( relation == carl::Relation::GEQ || relation == carl::Relation::EQ ) {
			solver.setIntParam( soplex::SoPlex::OBJSENSE, soplex::SoPlex::OBJSENSE_MINIMIZE );
			actualRes = detail::extractSolution<Number>( solver );
			solver.changeLhsRational( constraintIndex,  soplex::Rational( -1 ) * soplex::infinity );
			updatedRes = detail::extractSolution<Number>( solver );
			if ( actualRes.errorCode != updatedRes.errorCode || actualRes.supportValue != updatedRes.supportValue ){
				redundant = false;
			}
		}

		if ( redundant ){
			res.push_back( constraintIndex );
		} else {
			mpq_t a;
        	mpq_init( a );
        	mpq_set( a, ( carl::convert<Number, mpq_class>( constants( constraintIndex ) ) ).get_mpq_t() );

			if ( relation == carl::Relation::LEQ || relation == carl::Relation::EQ ){
				solver.changeRhsRational( constraintIndex, a );
			}
			if  (relation == carl::Relation::GEQ || relation == carl::Relation::EQ ){
				solver.changeLhsRational( constraintIndex, a );
			} 
		}

		if ( constraintIndex == 0 ){
			break;
		}
	}
	return res;
}

template <typename Number>
EvaluationResult<Number> clpGetInternalPoint( const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relations ) {
	soplex::SoPlex solver = initializeSolver( constraints, constants, relations );

	EvaluationResult<Number> res = detail::extractSolution<Number>( solver );
	return res;
}

}  // namespace hypro
