#pragma once
#include "../../carlTypes.h"

#include <vector>

namespace hypro {
namespace qe {
using cellDescription = std::vector<FormulasT>;

static cellDescription getCellDescription( const FormulasT& poly, const std::vector<carl::Variable>& variableOrder, const FormulaT& newConstraint ) {
	cellDescription res;

	// Data to store in tree
	using FormulaIterators = std::vector<FormulasT::const_iterator>;

	// tree to keep track of the whole process
	CellTree<FormulaIterators> cTree;

	// iterate over all passed variables
	for ( auto vIt = variableOrder.begin(); vIt != variableOrder.end(); ++vIt ) {
	}

	return res;
}
}  // namespace qe
}  // namespace hypro