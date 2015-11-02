/**
 * Holds convenience functions when working with SMTRat.
 */

#ifdef USE_SMTRAT
namespace hypro {

	template<typename Number>
	static smtrat::FormulaT createFormula(const matrix_t<Number>& _constraints, const vector_t<Number> _constants, carl::Relation _rel = carl::Relation::LEQ) {
		assert(_constraints.rows() == _constants.rows());

		// get new variables
		std::map<unsigned, carl::Variable> lambdas;
		for(unsigned colIndex = 0; colIndex < _constraints.cols(); ++colIndex) {
			lambdas.insert(std::make_pair(colIndex, carl::freshRealVariable()));
		}

		std::vector<smtrat::FormulaT> constraints;
		for(unsigned rowIndex = 0; rowIndex < _constraints.rows(); ++rowIndex) {
			Poly row;
			for(unsigned colIndex = 0; colIndex < _constraints.cols(); ++colIndex) {
				row += Rational(_constraints(rowIndex,colIndex)) * lambdas.find(colIndex)->second;
			}
			row -= Rational(_constants(rowIndex));
			constraints.emplace_back(row,_rel);
		}
		return std::move(smtrat::FormulaT(carl::FormulaType::AND, std::move(constraints)));
	}

} // namespace hypro
#endif