#pragma once

#include "util.h"
#include "../../../algorithms/quantifierElimination/qe.h"
#include "../../../carlTypes.h"
#include "../../../util/VariablePool.h"

namespace hypro {

template<typename Number>
class CarlPolytope {
public:
    // typedefs

private:
    FormulaT<Number> mFormula;

public:

    CarlPolytope()
        : mFormula()
    {}

    CarlPolytope(const FormulaT<Number>& formula) : mFormula(formula) {
        assert(formula.isRealConstraintConjunction());
    }

    CarlPolytope(const matrix_t<Number>& constraints, const vector_t<Number>& constants);

    CarlPolytope(const std::vector<carl::Interval<Number>>& intervals);

    CarlPolytope intersect(const CarlPolytope<Number>& rhs) const;

    const FormulaT<Number>& getFormula() const { return mFormula; }

};

} // hypro

#include "carlPolytope.tpp"
