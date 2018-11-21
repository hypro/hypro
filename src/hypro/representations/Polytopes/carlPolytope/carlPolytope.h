#pragma once

#include "carlPolytopeSettings.h"
#include "util.h"
#include "../../../datastructures/Halfspace.h"
#include "../../../algorithms/quantifierElimination/qe.h"
#include "../../../carlTypes.h"
#include "../../../util/VariablePool.h"

namespace hypro {

template<typename Number, typename Converter, typename Settings>
class CarlPolytopeT {
public:
    // typedefs

private:
    FormulaT<Number> mFormula;
    mutable std::vector<Halfspace<Number>> mHalfspaces; /// Caches transformed half-spaces.

public:

    CarlPolytopeT()
        : mFormula()
        , mHalfspaces()
    {}

    CarlPolytopeT(const FormulaT<Number>& formula)
        : mFormula(formula)
        , mHalfspaces()
    {
        assert(formula.isRealConstraintConjunction());
    }

    CarlPolytopeT(const matrix_t<Number>& constraints, const vector_t<Number>& constants);

    CarlPolytopeT(const std::vector<carl::Interval<Number>>& intervals);

    CarlPolytopeT<Number,Converter,Settings> intersect(const CarlPolytopeT<Number,Converter,Settings>& rhs) const;

    const FormulaT<Number>& getFormula() const { return mFormula; }
    const std::vector<Halfspace<Number>>& getHalfspaces() const;

    void addConstraint(const ConstraintT<Number>& constraint);
    void addConstraints(const std::vector<ConstraintT<Number>>& constraints);

    std::vector<Point<Number>> vertices() const;
};

} // hypro

#include "carlPolytope.tpp"
