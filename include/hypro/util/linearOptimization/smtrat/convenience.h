/**
 * Holds convenience functions when working with SMTRat.
 */
#pragma once
#include "../../../flags.h"
#ifdef HYPRO_USE_SMTRAT
#include "../../../datastructures/Point.h"
#include "../../VariablePool.h"

#include <carl/interval/Interval.h>
#include <fstream>

namespace hypro {

template <typename Number>
static std::unordered_map<smtrat::FormulaT, std::size_t> createFormula( const matrix_t<Number>& _constraints, const vector_t<Number> _constants, const std::vector<carl::Relation>& relations ) {
	assert( _constraints.rows() == _constants.rows() );
	assert( relations.size() == _constraints.rows() );

	VariablePool& pool = VariablePool::getInstance();

	std::unordered_map<smtrat::FormulaT, std::size_t> constraints;
	for ( unsigned rowIndex = 0; rowIndex < _constraints.rows(); ++rowIndex ) {
		carl::MultivariatePolynomial<smtrat::Rational> row;
		for ( unsigned colIndex = 0; colIndex < _constraints.cols(); ++colIndex ) {
			row += carl::convert<Number, smtrat::Rational>( _constraints( rowIndex, colIndex ) ) * pool.carlVarByIndex( colIndex );
		}
		row -= carl::convert<Number, smtrat::Rational>( _constants( rowIndex ) );
		// std::cout << "atempt to insert constraint " << rowIndex << " (" << _constraints.row(rowIndex) << ", " << _constants(rowIndex) << ")" << std::endl;
		constraints.insert( std::make_pair( smtrat::FormulaT( row, relations[rowIndex] ), rowIndex ) );
	}
	return constraints;
}

template <typename Number>
static std::unordered_map<smtrat::FormulaT, std::size_t> createFormula( const std::vector<carl::Interval<Number>>& _intervals ) {
	VariablePool& pool = VariablePool::getInstance();

	std::unordered_map<smtrat::FormulaT, std::size_t> constraints;
	for ( unsigned intervalIndex = 0; intervalIndex < _intervals.size(); ++intervalIndex ) {
		carl::MultivariatePolynomial<smtrat::Rational> lower;
		switch ( _intervals[intervalIndex].lowerBoundType() ) {
			case carl::BoundType::STRICT: {
				lower += pool.carlVarByIndex( intervalIndex ) - carl::convert<Number, smtrat::Rational>( _intervals[intervalIndex].lower() );
				constraints.insert( std::make_pair( smtrat::FormulaT( lower, carl::Relation::GREATER ), intervalIndex ) );
				break;
			}
			case carl::BoundType::WEAK: {
				lower += pool.carlVarByIndex( intervalIndex ) - carl::convert<Number, smtrat::Rational>( _intervals[intervalIndex].lower() );
				constraints.insert( std::make_pair( smtrat::FormulaT( lower, carl::Relation::GEQ ), intervalIndex ) );
				break;
			}
			case carl::BoundType::INFTY: {
				break;
			}
		}
		carl::MultivariatePolynomial<smtrat::Rational> upper;
		switch ( _intervals[intervalIndex].upperBoundType() ) {
			case carl::BoundType::STRICT: {
				upper += pool.carlVarByIndex( intervalIndex ) - carl::convert<Number, smtrat::Rational>( _intervals[intervalIndex].lower() );
				constraints.insert( std::make_pair( smtrat::FormulaT( upper, carl::Relation::LESS ), intervalIndex ) );
				break;
			}
			case carl::BoundType::WEAK: {
				upper += pool.carlVarByIndex( intervalIndex ) - carl::convert<Number, smtrat::Rational>( _intervals[intervalIndex].lower() );
				constraints.insert( std::make_pair( smtrat::FormulaT( upper, carl::Relation::LEQ ), intervalIndex ) );
				break;
			}
			case carl::BoundType::INFTY: {
				break;
			}
		}
	}
	return constraints;
}

template <typename Number>
static std::unordered_map<smtrat::FormulaT, std::size_t> createFormula( const Point<Number>& _point ) {
	VariablePool& pool = VariablePool::getInstance();

	std::unordered_map<smtrat::FormulaT, std::size_t> constraints;
	for ( unsigned d = 0; d < _point.dimension(); ++d ) {
		carl::MultivariatePolynomial<smtrat::Rational> row;
		row += smtrat::Rational( -carl::convert<Number, smtrat::Rational>( _point.at( d ) ) ) + pool.carlVarByIndex( d );
		// std::cout << "atempt to insert constraint " << d << " (" << _constraints.row(d) << ", " << _constants(d) << ")" << std::endl;
		constraints.insert( std::make_pair( smtrat::FormulaT( row, carl::Relation::EQ ), d ) );
	}
	return constraints;
}

template <typename InType>
static carl::MultivariatePolynomial<smtrat::Rational> createObjective( const vector_t<InType>& _objective ) {
	carl::MultivariatePolynomial<smtrat::Rational> objective;
	VariablePool& pool = VariablePool::getInstance();

	// get new variables
	for ( unsigned index = 0; index < _objective.rows(); ++index ) {
		objective += carl::convert<InType, smtrat::Rational>( _objective( index ) ) * pool.carlVarByIndex( index );
	}
	return objective;
}

#ifdef VERIFY_RESULT
static void outputToSmtlibFormat( const smtrat::SimplexSolver& solver, unsigned count, const smtrat::Poly& objective, const std::string& _prefix ) {
	std::string filename = _prefix + std::to_string( count ) + ".smt2";
	std::ofstream ofs( filename, std::ofstream::app );
	ofs << "(set-logic QF_LRA)\n"
		<< "(set-info :smt-lib-version 2.0)\n(push 1)";
	ofs << ( (smtrat::FormulaT)solver.formula() ).toString( false, 1, "", true, false, true, true );
	ofs << "(maximize " << objective.toString( false ) << " )\n";
	ofs << "(check-sat)\n(reset)" << std::endl;
	ofs.close();
}
#endif

}  // namespace hypro
#endif
