#include "carlPolytope.h"

namespace hypro {

    template<typename Number, typename Converter, typename Settings>
    CarlPolytopeT<Number,Converter,Settings>::CarlPolytopeT(const matrix_t<Number>& constraints, const vector_t<Number>& constants) {
        TRACE("hypro.representations.carlPolytope","Construct P from " << constraints << " and " << constants);
        FormulasT<Number> newConstraints = halfspacesToConstraints(constraints,constants);

        mFormula = FormulaT<Number>{carl::FormulaType::AND, newConstraints};
        TRACE("hypro.representations.carlPolytope","Result formula: " << mFormula);
        detectDimension();
    }

    template<typename Number, typename Converter, typename Settings>
    CarlPolytopeT<Number,Converter,Settings>::CarlPolytopeT(const std::vector<carl::Interval<Number>>& intervals) {
        TRACE("hypro.representations.carlPolytope","Construct P from interval vector.");
        FormulasT<Number> newConstraints;

        for(std::size_t i = 0; i < intervals.size(); ++i) {
            auto tmp = intervalToFormulas(intervals[i], i);
            newConstraints.insert(newConstraints.end(),tmp.begin(),tmp.end());
        }
        mFormula = FormulaT<Number>{carl::FormulaType::AND, newConstraints};
        TRACE("hypro.representations.carlPolytope","Result formula: " << mFormula);
        detectDimension();
    }

    template<typename Number, typename Converter, typename Settings>
    CarlPolytopeT<Number,Converter,Settings> CarlPolytopeT<Number,Converter,Settings>::Empty() {
        auto res = CarlPolytopeT();
        res.mEmpty = TRIBOOL::TRUE;
        return res;
    }

    template<typename Number, typename Converter, typename Settings>
    CarlPolytopeT<Number,Converter,Settings> CarlPolytopeT<Number,Converter,Settings>::intersect(const CarlPolytopeT<Number,Converter,Settings>& rhs) const {
        TRACE("hypro.representations.carlPolytope","Intersect " << *this << " and " << rhs);
        assert(mFormula.isConstraintConjunction());
        assert(rhs.getFormula().isConstraintConjunction());
        // test for emptiness
        if(this->empty() || rhs.empty()) {
            return Empty();
        }

        // collect constraints
        std::vector<ConstraintT<Number>> newConstraints;
        mFormula.getConstraints(newConstraints);
        rhs.getFormula().getConstraints(newConstraints);

        return CarlPolytopeT<Number,Converter,Settings>{FormulaT<Number>(carl::FormulaType::AND, constraintsToFormulas(newConstraints))};
    }

    template<typename Number, typename Converter, typename Settings>
    const std::vector<Halfspace<Number>>& CarlPolytopeT<Number,Converter,Settings>::getHalfspaces() const {
        if(mHalfspaces.empty()) {
            mHalfspaces = computeHalfspaces(mFormula, this->dimension());
        }
        TRACE("hypro.representations.carlPolytope","Computed halfspaces..");
        return mHalfspaces;
    }

    template<typename Number, typename Converter, typename Settings>
    void CarlPolytopeT<Number,Converter,Settings>::addConstraint(const ConstraintT<Number>& constraint) {
        // reset Half-space cache
        mHalfspaces.clear();
        // if not empty, reset cache
        if(mEmpty != TRIBOOL::TRUE) {
            mEmpty = TRIBOOL::NSET;
        }
        // add constraint to formula
        std::vector<ConstraintT<Number>> constraints;
        mFormula.getConstraints(constraints);
        constraints.push_back(constraint);
        mFormula = FormulaT<Number>(carl::FormulaType::AND, constraintsToFormulas(constraints));
        detectDimension();
    }

    template<typename Number, typename Converter, typename Settings>
    void CarlPolytopeT<Number,Converter,Settings>::addConstraints(const std::vector<ConstraintT<Number>>& constraints) {
        // reset Half-space cache
        mHalfspaces.clear();
        // if not empty, reset cache
        if(mEmpty != TRIBOOL::TRUE) {
            mEmpty = TRIBOOL::NSET;
        }
        // add constraints to formula
        auto cCopy = constraints;
        mFormula.getConstraints(cCopy);
        mFormula = FormulaT<Number>(carl::FormulaType::AND, cCopy);
        detectDimension();
    }

    template<typename Number, typename Converter, typename Settings>
    void CarlPolytopeT<Number,Converter,Settings>::substituteVariable(carl::Variable oldVar, carl::Variable newVar) {
        // reset half-space cache
        mHalfspaces.clear();
        // substitute
        mFormula = mFormula.substitute(oldVar, PolyT<Number>(newVar));
        detectDimension();
    }

    template<typename Number, typename Converter, typename Settings>
    std::vector<carl::Variable> CarlPolytopeT<Number,Converter,Settings>::getVariables() const {
        return std::vector<carl::Variable>{mFormula.variables().begin(), mFormula.variables().end()};
    }

    template<typename Number, typename Converter, typename Settings>
    void CarlPolytopeT<Number,Converter,Settings>::eliminateVariable(carl::Variable var) {
        DEBUG("hypro.representations.carlPolytope","Eliminate variable " << var);
        QEQuery query;
        query.emplace_back(std::make_pair(QuantifierType::EXISTS, std::vector<carl::Variable>({var})));
        mFormula = eliminateQuantifiers(mFormula, query);
        detectDimension();
    }

    template<typename Number, typename Converter, typename Settings>
    void CarlPolytopeT<Number,Converter,Settings>::eliminateVariables(const std::vector<carl::Variable>& vars) {
        DEBUG("hypro.representations.carlPolytope","Eliminate variables..");
        QEQuery query;
        query.emplace_back(std::make_pair(QuantifierType::EXISTS, vars));
        mFormula = eliminateQuantifiers(mFormula, query);
        detectDimension();
    }

    template<typename Number, typename Converter, typename Settings>
    void CarlPolytopeT<Number,Converter,Settings>::eliminateVariables(const QEQuery& vars) {
        DEBUG("hypro.representations.carlPolytope","Eliminate variables..");
        mFormula = eliminateQuantifiers(mFormula, vars);
        detectDimension();
    }

    template<typename Number, typename Converter, typename Settings>
    std::vector<Point<Number>> CarlPolytopeT<Number,Converter,Settings>::vertices() const {
        auto hpoly = Converter::toHPolytope(*this);
        return hpoly.vertices();
    }

    template<typename Number, typename Converter, typename Settings>
    matrix_t<Number> CarlPolytopeT<Number,Converter,Settings>::matrix() const {
        assert(dimensionWasCorrectlySet());
        matrix_t<Number> res = matrix_t<Number>(mFormula.size(),dimension());
        std::vector<ConstraintT<Number>> constraints;
        mFormula.getConstraints(constraints);
        std::size_t i = 0;
        for(const auto& c : constraints) {
            res.row(i) = constraintNormal(c,dimension());
            if(c.relation() == carl::Relation::EQ) {
                //res.conservativeResize(res.rows()+1, Eigen::NoChange_t);
                res.conservativeResize(res.rows()+1, res.cols());
                ++i;
                res.row(i) = -constraintNormal(c,dimension());
            }
            ++i;
        }
        return res;
    }

    template<typename Number, typename Converter, typename Settings>
    vector_t<Number> CarlPolytopeT<Number,Converter,Settings>::vector() const {
        assert(dimensionWasCorrectlySet());
        vector_t<Number> res = vector_t<Number>(mFormula.size());
        std::vector<ConstraintT<Number>> constraints;
        mFormula.getConstraints(constraints);
        std::size_t i = 0;
        for(const auto& c : constraints) {
            res(i) = normalizedOffset(c);
            if(c.relation() == carl::Relation::EQ) {
                res.conservativeResize(res.rows()+1);
                ++i;
                res(i) = -normalizedOffset(c);
            }
            ++i;
        }
        return res;
    }

    template<typename Number, typename Converter, typename Settings>
    bool CarlPolytopeT<Number,Converter,Settings>::empty() const {
        if(mFormula.size() <= 1) {
            return false;
        }

        if(mEmpty == TRIBOOL::NSET) {
            Optimizer<Number> opt = Optimizer<Number>(this->matrix(), this->vector());
            mEmpty = opt.checkConsistency() ? TRIBOOL::FALSE : TRIBOOL::TRUE;
        }
        return mEmpty == TRIBOOL::TRUE;
    }

    template<typename Number, typename Converter, typename Settings>
    void CarlPolytopeT<Number,Converter,Settings>::reduceRepresentation() {
        if(mFormula.size() <= 1) {
            return;
        }
        Optimizer<Number> opt = Optimizer<Number>(this->matrix(), this->vector());
        std::vector<ConstraintT<Number>> constraints;
        mFormula.getConstraints(constraints);
        auto redundantConstraints = opt.redundantConstraints();
        for(auto it = redundantConstraints.rbegin(); it != redundantConstraints.rend(); ++it ) {
            constraints.erase(constraints.begin() + *it);
        }
        mFormula = FormulaT<Number>(carl::FormulaType::AND, constraintsToFormulas(constraints));
    }

    template<typename Number, typename Converter, typename Settings>
    void CarlPolytopeT<Number,Converter,Settings>::clearCache() const {
        // reset half-space cache
        mHalfspaces.clear();
        // reset empty-cache
        mEmpty = TRIBOOL::NSET;
    }

    template<typename Number, typename Converter, typename Settings>
    void CarlPolytopeT<Number,Converter,Settings>::detectDimension() const {
        std::size_t d = 0;
        // get maximal state space dimension based on the variables used in mFormula.
        std::for_each(mFormula.variables().begin(),mFormula.variables().end(), [&](const carl::Variable& v){ d = std::max(d,VariablePool::getInstance().id(v));});
        mDimension = d+1; // add one as we start counting from zero.
        TRACE("hypro.representations.carlPolytope","Set dimension to " << mDimension );
    }

    template<typename Number, typename Converter, typename Settings>
    bool CarlPolytopeT<Number,Converter,Settings>::dimensionWasCorrectlySet() const {
        bool res = true;
        #ifndef NDEBUG
        auto tmpDim = mDimension;
        detectDimension();
        if(tmpDim != mDimension) {
            return false;
        }
        #endif
        return res;
    }

} // hypro
