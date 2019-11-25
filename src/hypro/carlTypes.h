#pragma once

#include <carl/core/MultivariatePolynomial.h>
#include <carl/formula/Formula.h>

namespace hypro {

enum class QuantifierType { EXISTS,
							FORALL };

template <typename Number>
using PolyT = carl::MultivariatePolynomial<Number>;

template <typename Number>
using ConstraintT = carl::Constraint<PolyT<Number> >;

template <typename Number>
using ConstraintsT = std::vector<ConstraintT<Number> >;

template <typename Number>
using FormulaT = carl::Formula<PolyT<Number> >;

template <typename Number>
using FormulasT = std::vector<FormulaT<Number> >;

using QEQuery = std::vector<std::pair<QuantifierType, std::vector<carl::Variable> > >;

}  // namespace hypro
