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

template<typename Number, typename Converter, typename Setting>
class CarlPolytopeT {
public:
    // typedefs
    using Settings = Setting;
    using NumberType = Number;
private:
    FormulaT<tNumber> mFormula; /// The description of the polytope as a conjunction of linear constraints.
    mutable std::vector<Halfspace<Number>> mHalfspaces; /// Caches transformed half-spaces.
    mutable std::size_t mDimension = 0; /// Stores the state space dimension the polytope resides in.
    mutable TRIBOOL mEmpty = TRIBOOL::NSET; /// Caches whether the polytope is empty.
    mutable bool mSpaceDimensionSet = false; /// used to indicate that the space dimension has been set externally, which overrides anything else.
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

    static CarlPolytopeT<Number,Converter,Setting> Empty();

    CarlPolytopeT<Number,Converter,Setting> intersect(const CarlPolytopeT<Number,Converter,Setting>& rhs) const;

    CarlPolytopeT<Number,Converter,Setting> project(const std::vector<std::size_t>& dimensions) const;

    CarlPolytopeT<Number,Converter,Setting> linearTransformation( const matrix_t<Number> &A ) const;

    CarlPolytopeT<Number,Converter,Setting> minkowskiSum(const CarlPolytopeT<Number,Converter,Setting>& ) const { assert(false && "NOT IMPLEMENTED"); return CarlPolytopeT<Number,Converter,Setting>(); }

    CarlPolytopeT<Number,Converter,Setting> unite(const CarlPolytopeT<Number,Converter,Setting>& ) const { assert(false && "NOT IMPLEMENTED"); return CarlPolytopeT<Number,Converter,Setting>(); }

    CarlPolytopeT<Number,Converter,Setting> affineTransformation(const matrix_t<Number>& , const vector_t<Number>& ) const { assert(false && "NOT IMPLEMENTED"); return CarlPolytopeT<Number,Converter,Setting>(); }

    std::pair<CONTAINMENT, CarlPolytopeT<Number,Converter,Setting>> satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const;

    bool contains(const Point<Number>& point) const;

    bool contains(const CarlPolytopeT<Number,Converter,Setting>& ) const { assert(false && "NOT IMPLEMENTED"); return false; }

    EvaluationResult<Number> evaluate(const vector_t<Number>& ) const { assert(false && "NOT IMPLEMENTED"); return EvaluationResult<Number>(); }

    std::vector<EvaluationResult<Number>> multiEvaluate(const matrix_t<Number>& , bool ) const { assert(false && "NOT IMPLEMENTED"); return std::vector<EvaluationResult<Number>>(); }

    std::size_t dimension() const { TRACE("hypro.representations.carlPolytope","Dimension " << mDimension << ". forced: " << mSpaceDimensionSet); return mDimension; }
    const FormulaT<tNumber>& getFormula() const { return mFormula; }
    const std::vector<Halfspace<Number>>& getHalfspaces() const;
    std::vector<carl::Interval<Number>> getIntervals() const;

    void setDimension(std::size_t d) { TRACE("hypro.representations.carlPolytope","Set dimension to " << d); mDimension = d; mSpaceDimensionSet = true; }
    void addConstraint(const ConstraintT<tNumber>& constraint);
    void addConstraints(const std::vector<ConstraintT<tNumber>>& constraints);
    void addIntervalConstraints(const carl::Interval<Number>& intv, const carl::Variable& var);
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

    CarlPolytopeT<Number,Converter,Setting> make_rectangular() const;

    void removeRedundancy();
    void reduceRepresentation();
    void choseOrder(QEQuery& ) {/* right now do nothing - add heuristics later. */}

    friend std::ostream& operator<<(std::ostream& out, const CarlPolytopeT<Number,Converter,Setting>& in ) {
        out << in.getFormula();
        return out;
    }

    friend bool operator==(const CarlPolytopeT<Number,Converter,Setting>& lhs, const CarlPolytopeT<Number,Converter,Setting>& rhs) {
        return lhs.mFormula == rhs.mFormula;
    }

    friend bool operator!=(const CarlPolytopeT<Number,Converter,Setting>& lhs, const CarlPolytopeT<Number,Converter,Setting>& rhs) {
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
