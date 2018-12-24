#include "carlPolytope.h"

namespace hypro {

    template<typename Number, typename Converter, typename Setting>
    CarlPolytopeT<Number,Converter,Setting>::CarlPolytopeT(const matrix_t<Number>& constraints, const vector_t<Number>& constants) {
        TRACE("hypro.representations.carlPolytope","Construct P from " << constraints << " and " << constants);
        FormulasT<tNumber> newConstraints = halfspacesToConstraints<tNumber,Number>(constraints,constants);

        mFormula = FormulaT<tNumber>{carl::FormulaType::AND, newConstraints};
        TRACE("hypro.representations.carlPolytope","Result formula: " << mFormula);
        detectDimension();
    }

    template<typename Number, typename Converter, typename Setting>
    CarlPolytopeT<Number,Converter,Setting>::CarlPolytopeT(const std::vector<carl::Interval<Number>>& intervals) {
        TRACE("hypro.representations.carlPolytope","Construct P from interval vector.");
        FormulasT<tNumber> newConstraints;

        for(std::size_t i = 0; i < intervals.size(); ++i) {
            auto tmp = intervalToFormulas<tNumber,Number>(intervals[i], i);
            newConstraints.insert(newConstraints.end(),tmp.begin(),tmp.end());
        }
        mFormula = FormulaT<tNumber>{carl::FormulaType::AND, newConstraints};
        TRACE("hypro.representations.carlPolytope","Result formula: " << mFormula);
        detectDimension();
    }

    template<typename Number, typename Converter, typename Setting>
    CarlPolytopeT<Number,Converter,Setting> CarlPolytopeT<Number,Converter,Setting>::Empty() {
        auto res = CarlPolytopeT();
        res.mEmpty = TRIBOOL::TRUE;
        return res;
    }

    template<typename Number, typename Converter, typename Setting>
    CarlPolytopeT<Number,Converter,Setting> CarlPolytopeT<Number,Converter,Setting>::intersect(const CarlPolytopeT<Number,Converter,Setting>& rhs) const {
        TRACE("hypro.representations.carlPolytope","Intersect " << *this << " and " << rhs);
        //assert(mFormula.isConstraintConjunction());
        //assert(rhs.getFormula().isConstraintConjunction());
        // test for emptiness
        if(this->empty() || rhs.empty()) {
            return Empty();
        }

        // collect constraints
        std::vector<ConstraintT<tNumber>> newConstraints;
        mFormula.getConstraints(newConstraints);
        rhs.getFormula().getConstraints(newConstraints);

        return CarlPolytopeT<Number,Converter,Setting>(FormulaT<tNumber>(carl::FormulaType::AND, constraintsToFormulas(newConstraints)));
    }

    template<typename Number, typename Converter, typename Setting>
    CarlPolytopeT<Number,Converter,Setting> CarlPolytopeT<Number,Converter,Setting>::project(const std::vector<std::size_t>& dimensions) const {
        TRACE("hypro.representations.CarlPolytope","on dimensions " << dimensions);
        /*
        if(dimensions.empty()) {
            return Empty();
        }
        */

        // projection by means of a linear transformation
        matrix_t<Number> projectionMatrix = matrix_t<Number>::Zero(this->dimension(), this->dimension());
        for(auto i : dimensions) {
            projectionMatrix(i,i) = 1;
        }
        return this->linearTransformation(projectionMatrix);
    }

    template <typename Number, typename Converter, typename Setting>
    CarlPolytopeT<Number,Converter,Setting> CarlPolytopeT<Number,Converter,Setting>::linearTransformation( const matrix_t<Number> &A ) const {
        TRACE("hypro.representations.CarlPolytope","P' = A*P, A:" << std::endl << A);
        if(A.nonZeros() == 0) {
            return CarlPolytopeT<Number,Converter,Setting>::Empty();
        }
        if(!this->empty()) {
            Eigen::FullPivLU<matrix_t<Number>> lu(A);
            // if A has full rank, we can simply re-transform, otherwise use v-representation.
            if(lu.rank() == A.rows()) {
                TRACE("hypro.representations.HPolytope","A has full rank - do not use v-conversion.");
                matrix_t<Number> constraints = this->matrix();
                vector_t<Number> constants = this->vector();
                assert( (CarlPolytopeT<Number,Converter,Setting>(constraints*A.inverse(), constants).size() == this->size()) );
                return CarlPolytopeT<Number,Converter,Setting>(constraints*A.inverse(), constants);
            } else {
                TRACE("hypro.representations.HPolytope","Use V-Conversion for linear transformation.");
                auto intermediate = Converter::toVPolytope( *this );
                intermediate = intermediate.linearTransformation( A );
                auto res = Converter::toCarlPolytope(intermediate);
                return res;
            }
        } else {
            return *this;
        }
    }

    template<typename Number, typename Converter, typename Setting>
    std::pair<CONTAINMENT, CarlPolytopeT<Number,Converter,Setting>> CarlPolytopeT<Number,Converter,Setting>::satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {
        auto resPoly = this->intersect(CarlPolytopeT<Number,Converter,Setting>(_mat,_vec));
        resPoly.removeRedundancy();

        if(resPoly == *this) {
            return std::make_pair(CONTAINMENT::FULL, *this);
        }

        if(resPoly.empty()) {
            return std::make_pair(CONTAINMENT::NO, resPoly);
        }
        return std::make_pair(CONTAINMENT::PARTIAL, resPoly);
    }

    template<typename Number, typename Converter, typename Setting>
    const std::vector<Halfspace<Number>>& CarlPolytopeT<Number,Converter,Setting>::getHalfspaces() const {
        if(mHalfspaces.empty()) {
            mHalfspaces = computeHalfspaces<tNumber,Number>(mFormula, this->dimension());
        }
        TRACE("hypro.representations.carlPolytope","Computed halfspaces..");
        return mHalfspaces;
    }

    template<typename Number, typename Converter, typename Setting>
    std::vector<carl::Interval<Number>> CarlPolytopeT<Number,Converter,Setting>::getIntervals() const {
        // Note: Alternatively use FM-elimination.
        Optimizer<Number> opt{this->matrix(), this->vector()};
        auto dim = Eigen::Index(this->dimension());
        // use box-template, first normal points towards dimension, then negative
        auto directions = computeTemplate<Number>(dim,4);
        std::vector<EvaluationResult<Number>> evalResult;
        std::for_each(directions.begin(), directions.end(),
            [&evalResult, &opt](const auto& in){ evalResult.emplace_back(std::move(opt.evaluate(in,true)));}
        );

        std::vector<carl::Interval<Number>> res;

        // assemble intervals from evaluation results
        assert(Eigen::Index(evalResult.size()) == 2*dim );
        for(Eigen::Index d = 0; d < dim; ++d) {
            res.emplace_back(-evalResult[2*d + 1].supportValue, evalResult[2*d].supportValue);
        }
        return res;
    }

    template<typename Number, typename Converter, typename Setting>
    void CarlPolytopeT<Number,Converter,Setting>::addConstraint(const ConstraintT<tNumber>& constraint) {
        // reset Half-space cache
        mHalfspaces.clear();
        // if not empty, reset cache
        if(mEmpty != TRIBOOL::TRUE) {
            mEmpty = TRIBOOL::NSET;
        }
        // add constraint to formula
        std::vector<ConstraintT<tNumber>> constraints;
        mFormula.getConstraints(constraints);
        constraints.push_back(constraint);
        mFormula = FormulaT<tNumber>(carl::FormulaType::AND, constraintsToFormulas(constraints));
        TRACE("hypro.representations.CarlPolytope","After adding a constraint " << *this);
        detectDimension();
    }

    template<typename Number, typename Converter, typename Setting>
    void CarlPolytopeT<Number,Converter,Setting>::addConstraints(const std::vector<ConstraintT<tNumber>>& constraints) {
        // reset Half-space cache
        mHalfspaces.clear();
        // if not empty, reset cache
        if(mEmpty != TRIBOOL::TRUE) {
            mEmpty = TRIBOOL::NSET;
        }
        // add constraints to formula
        auto cCopy = constraints;
        mFormula.getConstraints(cCopy);
        mFormula = FormulaT<tNumber>(carl::FormulaType::AND, constraintsToFormulas(cCopy));
        TRACE("hypro.representations.CarlPolytope","After adding constraints " << *this);
        detectDimension();
    }

    template<typename Number, typename Converter, typename Setting>
    void CarlPolytopeT<Number,Converter,Setting>::substituteVariable(carl::Variable oldVar, carl::Variable newVar) {
        // reset half-space cache
        mHalfspaces.clear();
        // substitute
        mFormula = mFormula.substitute(oldVar, PolyT<tNumber>(newVar));
        TRACE("hypro.representations.CarlPolytope","After substituting " << oldVar << " by " << newVar << ": " << *this);
        detectDimension();
    }

    template<typename Number, typename Converter, typename Setting>
    std::vector<carl::Variable> CarlPolytopeT<Number,Converter,Setting>::getVariables() const {
        return std::vector<carl::Variable>{mFormula.variables().begin(), mFormula.variables().end()};
    }

    template<typename Number, typename Converter, typename Setting>
    void CarlPolytopeT<Number,Converter,Setting>::eliminateVariable(carl::Variable var) {
        DEBUG("hypro.representations.carlPolytope","Eliminate variable " << var);
        QEQuery query;
        query.emplace_back(std::make_pair(QuantifierType::EXISTS, std::vector<carl::Variable>({var})));
        mFormula = eliminateQuantifiers(mFormula, query);
        detectDimension();
    }

    template<typename Number, typename Converter, typename Setting>
    void CarlPolytopeT<Number,Converter,Setting>::eliminateVariables(const std::vector<carl::Variable>& vars) {
        DEBUG("hypro.representations.carlPolytope","Eliminate variables..");
        QEQuery query;
        query.emplace_back(std::make_pair(QuantifierType::EXISTS, vars));
        mFormula = eliminateQuantifiers(mFormula, query);
        detectDimension();
    }

    template<typename Number, typename Converter, typename Setting>
    void CarlPolytopeT<Number,Converter,Setting>::eliminateVariables(const QEQuery& vars) {
        DEBUG("hypro.representations.carlPolytope","Eliminate variables..");
        mFormula = eliminateQuantifiers(mFormula, vars);
        detectDimension();
    }

    template<typename Number, typename Converter, typename Setting>
    std::vector<Point<Number>> CarlPolytopeT<Number,Converter,Setting>::vertices() const {
        auto hpoly = Converter::toHPolytope(*this);
        return hpoly.vertices();
    }

    template<typename Number, typename Converter, typename Setting>
    matrix_t<Number> CarlPolytopeT<Number,Converter,Setting>::matrix() const {
        assert(dimensionWasCorrectlySet());
        matrix_t<Number> res = matrix_t<Number>(mFormula.size(),dimension());
        std::vector<ConstraintT<tNumber>> constraints;
        mFormula.getConstraints(constraints);
        std::size_t i = 0;
        for(const auto& c : constraints) {
            res.row(i) = constraintNormal<tNumber,Number>(c,dimension());
            if(c.relation() == carl::Relation::EQ) {
                //res.conservativeResize(res.rows()+1, Eigen::NoChange_t);
                res.conservativeResize(res.rows()+1, res.cols());
                ++i;
                res.row(i) = -constraintNormal<tNumber,Number>(c,dimension());
            }
            ++i;
        }
        return res;
    }

    template<typename Number, typename Converter, typename Setting>
    vector_t<Number> CarlPolytopeT<Number,Converter,Setting>::vector() const {
        assert(dimensionWasCorrectlySet());
        vector_t<Number> res = vector_t<Number>(mFormula.size());
        std::vector<ConstraintT<tNumber>> constraints;
        mFormula.getConstraints(constraints);
        std::size_t i = 0;
        for(const auto& c : constraints) {
            res(i) = normalizedOffset<tNumber,Number>(c);
            if(c.relation() == carl::Relation::EQ) {
                res.conservativeResize(res.rows()+1);
                ++i;
                res(i) = -normalizedOffset<tNumber,Number>(c);
            }
            ++i;
        }
        return res;
    }

    template<typename Number, typename Converter, typename Setting>
    bool CarlPolytopeT<Number,Converter,Setting>::empty() const {
        if(mFormula.size() <= 1) {
            return false;
        }

        if(mEmpty == TRIBOOL::NSET) {
            Optimizer<Number> opt = Optimizer<Number>(this->matrix(), this->vector());
            mEmpty = opt.checkConsistency() ? TRIBOOL::FALSE : TRIBOOL::TRUE;
        }
        return mEmpty == TRIBOOL::TRUE;
    }

    template<typename Number, typename Converter, typename Setting>
    CarlPolytopeT<Number,Converter,Setting> CarlPolytopeT<Number,Converter,Setting>::make_rectangular() const {
        // Idea: Use FM-elimination to obtain all intervals for all variables consecutively.
        // Alternative: Use optimizer (current version).

        Optimizer<Number> opt{this->matrix(), this->vector()};
        // use box-template
        auto directions = computeTemplate<Number>(this->dimension(),4);
        std::vector<EvaluationResult<Number>> evalResult;
        for(const auto& dir : directions) {
            evalResult.emplace_back(std::move(opt.evaluate(dir,true)));
        }
        vector_t<Number> constants = vector_t<Number>(directions.rows());
        Eigen::Index pos = 0;
        for(const auto& res : evalResult) {
            constants(pos) = res.supportValue;
            ++pos;
        }
        return CarlPolytopeT<Number,Converter,Setting>(directions,constants);
    }

    template<typename Number, typename Converter, typename Setting>
    void CarlPolytopeT<Number,Converter,Setting>::removeRedundancy() {
        if(mFormula.size() <= 1) {
            return;
        }
        Optimizer<Number> opt = Optimizer<Number>(this->matrix(), this->vector());
        std::vector<ConstraintT<tNumber>> constraints;
        mFormula.getConstraints(constraints);
        auto redundantConstraints = opt.redundantConstraints();
        for(auto it = redundantConstraints.rbegin(); it != redundantConstraints.rend(); ++it ) {
            constraints.erase(constraints.begin() + *it);
        }
        mFormula = FormulaT<tNumber>(carl::FormulaType::AND, constraintsToFormulas(constraints));
    }

    template<typename Number, typename Converter, typename Setting>
    void CarlPolytopeT<Number,Converter,Setting>::clearCache() const {
        // reset half-space cache
        mHalfspaces.clear();
        // reset empty-cache
        mEmpty = TRIBOOL::NSET;
    }

    template<typename Number, typename Converter, typename Setting>
    void CarlPolytopeT<Number,Converter,Setting>::detectDimension() const {
        std::size_t d = 0;
        // get maximal state space dimension based on the variables used in mFormula.
        std::for_each(mFormula.variables().begin(),mFormula.variables().end(), [&](const carl::Variable& v){ d = std::max(d,VariablePool::getInstance().id(v));});
        mDimension = d+1; // add one as we start counting from zero.
        TRACE("hypro.representations.carlPolytope","Set dimension to " << mDimension );
    }

    template<typename Number, typename Converter, typename Setting>
    bool CarlPolytopeT<Number,Converter,Setting>::dimensionWasCorrectlySet() const {
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
