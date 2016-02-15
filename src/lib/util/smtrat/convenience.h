/**
 * Holds convenience functions when working with SMTRat.
 */

#ifdef USE_SMTRAT

#pragma once
#include "../VariablePool.h"

namespace hypro {

	template<typename Number>
	static std::unordered_map<smtrat::FormulaT, std::size_t> createFormula(const matrix_t<Number>& _constraints, const vector_t<Number> _constants, carl::Relation _rel = carl::Relation::LEQ) {
		assert(_constraints.rows() == _constants.rows());

		VariablePool& pool = VariablePool::getInstance();

		std::unordered_map<smtrat::FormulaT, std::size_t> constraints;
		for(unsigned rowIndex = 0; rowIndex < _constraints.rows(); ++rowIndex) {
			Poly row;
			for(unsigned colIndex = 0; colIndex < _constraints.cols(); ++colIndex) {
				row += carl::convert<Number,Rational>(_constraints(rowIndex,colIndex)) * pool.carlVarByIndex(colIndex);
			}
			row -= carl::convert<Number,Rational>(_constants(rowIndex));
			//std::cout << "atempt to insert constraint " << rowIndex << " (" << _constraints.row(rowIndex) << ", " << _constants(rowIndex) << ")" << std::endl;
			constraints.insert(std::make_pair(smtrat::FormulaT(row,_rel), rowIndex));
		}
		return std::move(constraints);
	}

	template<typename Number>
	static Poly createObjective(const vector_t<Number>& _objective) {
		Poly objective;
		VariablePool& pool = VariablePool::getInstance();

		// get new variables
		for(unsigned index = 0; index < _objective.rows(); ++index) {
			objective += carl::convert<Number,Rational>(_objective(index))*pool.carlVarByIndex(index);
		}
		return std::move(objective);
	}

} // namespace hypro
#endif