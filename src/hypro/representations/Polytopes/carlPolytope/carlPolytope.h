#pragma once

#include "carlPolytopeSettings.h"
#include "util.h"
#include "../../../datastructures/Halfspace.h"
#include "../../../algorithms/quantifierElimination/qe.h"
#include "../../../carlTypes.h"
#include "../../../util/VariablePool.h"
#include "../../../util/logging/Logger.h"

namespace hypro {

template<typename Number, typename Converter, typename Settings>
class CarlPolytopeT {
public:
    // typedefs

private:
    FormulaT<Number> mFormula;
    mutable std::vector<Halfspace<Number>> mHalfspaces; /// Caches transformed half-spaces.
    std::size_t mDimension = 0;

public:

    CarlPolytopeT()
        : mFormula()
        , mHalfspaces()
    {}

    CarlPolytopeT(const FormulaT<Number>& formula, std::size_t dimension = 0)
        : mFormula(formula)
        , mHalfspaces()
        , mDimension(dimension)
    {
        assert(formula.isRealConstraintConjunction());
        if(dimension==0) {
            detectDimension();
        }
        TRACE("hypro.representations.carlPolytope","Constructed P from " << mFormula);
    }

    CarlPolytopeT(const matrix_t<Number>& constraints, const vector_t<Number>& constants);

    CarlPolytopeT(const std::vector<carl::Interval<Number>>& intervals);

    CarlPolytopeT<Number,Converter,Settings> intersect(const CarlPolytopeT<Number,Converter,Settings>& rhs) const;

    std::size_t dimension() const { return mDimension; }
    const FormulaT<Number>& getFormula() const { return mFormula; }
    const std::vector<Halfspace<Number>>& getHalfspaces() const;

    void setDimension(std::size_t d) { mDimension = d; }
    void addConstraint(const ConstraintT<Number>& constraint);
    void addConstraints(const std::vector<ConstraintT<Number>>& constraints);

    std::vector<Point<Number>> vertices() const;

    friend std::ostream& operator<<(std::ostream& out, const CarlPolytopeT<Number,Converter,Settings>& in ) {
        out << in.getFormula();
        return out;
    }

private:
    void detectDimension();
};

} // hypro

#include "carlPolytope.tpp"
