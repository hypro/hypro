/**
 * Holds convenience functions when working with SMTRat.
 */

#ifdef USE_SMTRAT

#pragma once
#include "../VariablePool.h"

namespace hypro {

	template<typename Number>
	static smtrat::FormulaT createFormula(const matrix_t<Number>& _constraints, const vector_t<Number> _constants, carl::Relation _rel = carl::Relation::LEQ) {
		assert(_constraints.rows() == _constants.rows());

		VariablePool& pool = VariablePool::getInstance();

		std::vector<smtrat::FormulaT> constraints;
		for(unsigned rowIndex = 0; rowIndex < _constraints.rows(); ++rowIndex) {
			Poly row;
			for(unsigned colIndex = 0; colIndex < _constraints.cols(); ++colIndex) {
				row += carl::convert<Number,Rational>(_constraints(rowIndex,colIndex)) * pool.carlVarByIndex(colIndex);
			}
			row -= carl::convert<Number,Rational>(_constants(rowIndex));
			constraints.emplace_back(row,_rel);
		}
		return std::move(smtrat::FormulaT(carl::FormulaType::AND, std::move(constraints)));
	}

	template<typename Number>
	static std::pair<smtrat::FormulaT,Poly> createFormula(const matrix_t<Number>& _constraints, const vector_t<Number>& _constants, const vector_t<Number>& _objective, carl::Relation _rel = carl::Relation::LEQ) {
		assert(_constraints.rows() == _constants.rows());
		Poly objective;
		VariablePool& pool = VariablePool::getInstance();

		// get new variables
		for(unsigned colIndex = 0; colIndex < _constraints.cols(); ++colIndex) {
			objective += carl::convert<Number,Rational>(_objective(colIndex))*pool.carlVarByIndex(colIndex);
		}

		std::vector<smtrat::FormulaT> constraints;
		for(unsigned rowIndex = 0; rowIndex < _constraints.rows(); ++rowIndex) {
			Poly row;
			for(unsigned colIndex = 0; colIndex < _constraints.cols(); ++colIndex) {
				row += carl::convert<Number,Rational>(_constraints(rowIndex,colIndex)) * pool.carlVarByIndex(colIndex);
			}
			row -= carl::convert<Number,Rational>(_constants(rowIndex));
			constraints.emplace_back(row,_rel);
		}
		return std::make_pair(std::move(smtrat::FormulaT(carl::FormulaType::AND, std::move(constraints))), std::move(objective));
	}

} // namespace hypro
#endif