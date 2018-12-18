#pragma once

#include "carlPolytopeSettings.h"
#include "util.h"
#include "../../../datastructures/Halfspace.h"
#include "../../../algorithms/quantifierElimination/qe.h"
#include "../../../carlTypes.h"
#include "../../../util/VariablePool.h"
#include "../../../util/logging/Logger.h"
#include "../../../util/linearOptimization/Optimizer.h"

namespace hypro {

template<typename Number, typename Converter, typename Settings>
class CarlPolytopeT {
public:
    // typedefs

private:
    FormulaT<tNumber> mFormula; /// The description of the polytope as a conjunction of linear constraints.
    mutable std::vector<Halfspace<Number>> mHalfspaces; /// Caches transformed half-spaces.
    mutable std::size_t mDimension = 0; /// Stores the state space dimension the polytope resides in.
    mutable TRIBOOL mEmpty = TRIBOOL::NSET; /// Caches whether the polytope is empty.
public:

    CarlPolytopeT()
        : mFormula()
        , mHalfspaces()
    {}

    CarlPolytopeT(const FormulaT<tNumber>& formula, std::size_t dimension = 0)
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

    static CarlPolytopeT<Number,Converter,Settings> Empty();

    CarlPolytopeT<Number,Converter,Settings> intersect(const CarlPolytopeT<Number,Converter,Settings>& rhs) const;

    std::size_t dimension() const { return mDimension; }
    const FormulaT<tNumber>& getFormula() const { return mFormula; }
    const std::vector<Halfspace<Number>>& getHalfspaces() const;

    void setDimension(std::size_t d) { mDimension = d; }
    void addConstraint(const ConstraintT<tNumber>& constraint);
    void addConstraints(const std::vector<ConstraintT<tNumber>>& constraints);
    void substituteVariable(carl::Variable oldVar, carl::Variable newVar);

    std::vector<carl::Variable> getVariables() const;
    void eliminateVariable(carl::Variable var);
    void eliminateVariables(const std::vector<carl::Variable>& vars);
    void eliminateVariables(const QEQuery& vars);

    std::vector<Point<Number>> vertices() const;
    matrix_t<Number> matrix() const;
    vector_t<Number> vector() const;
    std::size_t size() const { return mFormula.size(); }
    bool empty() const;
    static representation_name type() { return representation_name::carl_polytope; }

    void removeRedundancy();
    void choseOrder(QEQuery& in) {/* right now do nothing - add heuristics later. */}

    friend std::ostream& operator<<(std::ostream& out, const CarlPolytopeT<Number,Converter,Settings>& in ) {
        out << in.getFormula();
        return out;
    }

    friend bool operator==(const CarlPolytopeT<Number,Converter,Settings>& lhs, const CarlPolytopeT<Number,Converter,Settings>& rhs) {
        return lhs.mFormula == rhs.mFormula;
    }

    friend bool operator!=(const CarlPolytopeT<Number,Converter,Settings>& lhs, const CarlPolytopeT<Number,Converter,Settings>& rhs) {
        return !(lhs.mFormula == rhs.mFormula);
    }

private:
    void clearCache() const;
    void detectDimension() const ;

    /**
     * @brief Should only be used in assertions to detect inconsistency in mDimension.
     */
    bool dimensionWasCorrectlySet() const;
};

} // hypro

#include "carlPolytope.tpp"
