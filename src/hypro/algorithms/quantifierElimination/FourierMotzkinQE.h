#pragma once
#include "../../carlTypes.h"

namespace hypro {

/**
 * @brief Provides a simple implementation for Fourier Motzkin variable elimination for linear, existentially quantified constraints.
 *
 */
template<typename Number>
class FourierMotzkinQE {
public:
    // we use four vectors, one for the discovered lower bounds, one for the upper bounds, one for the equations and one for unrelated constraints.
    using FormulaPartition = std::vector<std::vector<FormulaT<Number>>>;

private:
    QEQuery mQuery;
    FormulaT<Number> mFormula;
public:

    FourierMotzkinQE(const FormulaT<Number>& qfree, const QEQuery& quantifiers)
        : mQuery(quantifiers)
        , mFormula(qfree)
    {
        assert(qfree.getType() == carl::FormulaType::CONSTRAINT || qfree.isRealConstraintConjunction());
    }

    FormulaT<Number> eliminateQuantifiers();

private:
    FormulaPartition findBounds(const carl::Variable& variable);

    FormulasT<Number> createNewConstraints(const FormulaPartition& bounds, carl::Variable v);

    FormulasT<Number> substituteEquations(const FormulaPartition& bounds, carl::Variable v);

    bool isLinearLowerBound(const ConstraintT<Number>& f, carl::Variable v);

    PolyT<Number> getRemainder(const ConstraintT<Number>& c, carl::Variable v, bool isLowerBnd);
};

} // hypro

#include "FourierMotzkinQE.tpp"
