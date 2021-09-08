
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
		solver.addRowRational( soplex::LPRowRational( soplex::Rational( supportValueRational ), directionRational, soplex::infinity ) );
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

	EvaluationResult<Number> res = detail::extractSolution<Number>( solver );
	return res;
}

template <typename Number>
bool soplexCheckConsistency( const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relations ) {
	soplex::SoPlex solver = detail::initializeSolver( constraints, constants, relations );

	std::cout << "Constraints: " << constraints << ", constants " << constants << std::endl;

	solver.solve();
	return solver.isPrimalFeasible();
}

template <typename Number>
bool soplexCheckPoint( const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relations, const Point<Number>& point ) {
	// Set column bounds equal to the point and check whether lp is feasible
	soplex::SoPlex solver = detail::initializeSolver( constraints, constants, relations );
	for ( unsigned varIndex = 0; varIndex < constraints.cols(); ++varIndex ) {
		mpq_t a;
		mpq_init( a );
		mpq_set( a, ( carl::convert<Number, mpq_class>( point.at( varIndex ) ) ).get_mpq_t() );
		solver.changeBoundsRational( varIndex, soplex::Rational( a ), soplex::Rational( a ) );
		mpq_clear( a );
	}

	solver.solve();
	return solver.isPrimalFeasible();
}

template <typename Number>
std::vector<std::size_t> soplexRedundantConstraints( const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relations ) {
	std::vector<std::size_t> res;

	// first call to check satisfiability
	soplex::SoPlex solver = detail::initializeSolver( constraints, constants, relations );
	solver.solve();
	if ( !solver.isPrimalFeasible() ) {
		return res;
	}

	for ( std::size_t constraintIndex = std::size_t( constraints.rows() - 1 );; --constraintIndex ) {
		// Set current row as objective
		for ( unsigned varIndex = 0; varIndex < constraints.cols(); ++varIndex ) {
			mpq_t a;
			mpq_init( a );
			mpq_set( a, ( carl::convert<Number, mpq_class>( constraints( constraintIndex, varIndex ) ) ).get_mpq_t() );
			solver.changeObjRational( varIndex, a );
			mpq_clear( a );
		}

		bool redundant = true;
		EvaluationResult<Number> actualMax;
		EvaluationResult<Number> actualMin;
		EvaluationResult<Number> updatedMax;
		EvaluationResult<Number> updatedMin;
		soplex::LPRowRational currentRow( constraints.cols() );

		// Save current constraints before removing
		solver.getRowRational( constraintIndex, currentRow );
		soplex::Rational lowerBound = solver.lhsRational( constraintIndex );
		soplex::Rational upperBound = solver.rhsRational( constraintIndex );

		switch ( relations[constraintIndex] ) {
			case carl::Relation::LEQ:
				// test upper bound
				solver.setIntParam( soplex::SoPlex::OBJSENSE, soplex::SoPlex::OBJSENSE_MAXIMIZE );

				actualMax = detail::extractSolution<Number>( solver );
				solver.removeRowRational( constraintIndex );

				updatedMax = detail::extractSolution<Number>( solver );
				if ( actualMax.errorCode != updatedMax.errorCode || actualMax.supportValue != updatedMax.supportValue ) {
					redundant = false;
				}
				break;
			case carl::Relation::GEQ:
				// test lower bound
				solver.setIntParam( soplex::SoPlex::OBJSENSE, soplex::SoPlex::OBJSENSE_MINIMIZE );

				actualMin = detail::extractSolution<Number>( solver );
				solver.removeRowRational( constraintIndex );

				updatedMin = detail::extractSolution<Number>( solver );
				if ( actualMin.errorCode != updatedMin.errorCode || actualMin.supportValue != updatedMin.supportValue ) {
					redundant = false;
				}
				break;
			case carl::Relation::EQ:
				// test both upper and lower bound
				solver.setIntParam( soplex::SoPlex::OBJSENSE, soplex::SoPlex::OBJSENSE_MAXIMIZE );
				actualMax = detail::extractSolution<Number>( solver );
				actualMin = detail::extractSolution<Number>( solver );
				solver.removeRowRational( constraintIndex );
				if ( actualMin.errorCode != updatedMin.errorCode || actualMin.supportValue != updatedMin.supportValue ||
					 actualMax.errorCode != updatedMax.errorCode || actualMax.supportValue != updatedMax.supportValue ) {
					redundant = false;
				}
				break;
			default:
				assert( false );
		}

		if ( redundant ) {
			res.push_back( constraintIndex );
		} else {
			// Restore constraint. Note that the row is appended as the last row to the matrix, so the order of constraints is changed
			solver.addRowRational( currentRow );

			switch ( relations[constraintIndex] ) {
				case carl::Relation::LEQ:
					solver.changeRhsRational( solver.numRows() - 1, upperBound );
					break;
				case carl::Relation::GEQ:
					solver.changeLhsRational( solver.numRows() - 1, lowerBound );
					break;
				case carl::Relation::EQ:
					solver.changeRangeRational( solver.numRows() - 1, lowerBound, upperBound );
					break;
				default:
					assert( false );
			}
		}

		if ( constraintIndex == 0 ) {
			break;
		}
	}
	return res;
}

template <typename Number>
EvaluationResult<Number> soplexGetInternalPoint( const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relations ) {
	soplex::SoPlex solver = detail::initializeSolver( constraints, constants, relations );

	EvaluationResult<Number> res = detail::extractSolution<Number>( solver );
	return res;
}

}  // namespace hypro
