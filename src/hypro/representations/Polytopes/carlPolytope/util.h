#pragma once
#include "../../../carlTypes.h"
#include "../../../datastructures/Halfspace.h"
#include "../../../util/VariablePool.h"

namespace hypro {

    template<typename N>
    inline FormulasT<N> constraintsToFormulas(const std::vector<ConstraintT<N>>& in) {
        FormulasT<N> res;
        std::for_each(in.begin(),in.end(), [&](auto in){res.emplace_back(FormulaT<N>(in));});
        return res;
    }

    template<typename N>
    FormulasT<N> intervalToFormulas(const carl::Interval<N>& interval, std::size_t variableIndex) {
        TRACE("hypro.representations.carlPolytope","Create interval constraints for variable index " << variableIndex);
        FormulasT<N> res;
        res.emplace_back(ConstraintT<N>(PolyT<N>(VariablePool::getInstance().carlVarByIndex(variableIndex)) - PolyT<N>(interval.lower()), carl::Relation::GEQ));
        res.emplace_back(ConstraintT<N>(PolyT<N>(VariablePool::getInstance().carlVarByIndex(variableIndex)) - PolyT<N>(interval.upper()), carl::Relation::LEQ));
        return res;
    }

    template<typename N>
    vector_t<N> constraintNormal(const ConstraintT<N>& c, std::size_t dim) {
        vector_t<N> normal = vector_t<N>::Zero(dim);
        for(const auto& var : c.variables()) {
            assert(VariablePool::getInstance().hasDimension(var));
            assert(c.lhs().isLinear());
            assert(c.lhs().coeff(var,1).isNumber());
            if(c.relation() == carl::Relation::LEQ || c.relation() == carl::Relation::LESS || c.relation() == carl::Relation::EQ) {
                normal(VariablePool::getInstance().id(var)) = c.lhs().coeff(var,1).constantPart();
            } else {
                normal(VariablePool::getInstance().id(var)) = -c.lhs().coeff(var,1).constantPart();
            }
        }
        return normal;
    }

    template<typename N>
    N normalizedOffset(const ConstraintT<N>& c) {
        if(c.relation() == carl::Relation::LEQ || c.relation() == carl::Relation::LESS || c.relation() == carl::Relation::EQ) {
            return -c.lhs().constantPart();
        } else {
            return c.lhs().constantPart();
        }
    }

    template<typename N>
    std::vector<Halfspace<N>> constraintToHalfspace(const ConstraintT<N> constraint, std::size_t dim) {
        TRACE("hypro.representations.carlPolytope","Compute half-spaces from " << constraint << " with dimension " << dim);
        std::vector<Halfspace<N>> res;

        N offset = normalizedOffset(constraint);
        vector_t<N> normalV = constraintNormal(constraint,dim);

        res.emplace_back(Halfspace<N>{normalV,offset});
        TRACE("hypro.representations.carlPolytope","Hsp: " << res.back());

        if(constraint.relation() == carl::Relation::EQ) {
            res.emplace_back(Halfspace<N>{-normalV, -offset});
            TRACE("hypro.representations.carlPolytope","Hsp: " << res.back());
        }

        return res;
    }

    template<typename N>
    std::vector<Halfspace<N>> computeHalfspaces(const FormulaT<N>& formula, std::size_t dim) {
        assert(formula.isConstraintConjunction());

        std::vector<Halfspace<N>> res;
        std::vector<ConstraintT<N>> constraints;
        formula.getConstraints(constraints);

        for(const auto& c : constraints) {
            auto tmp = constraintToHalfspace(c, dim);
            res.insert(res.end(), tmp.begin(), tmp.end());
        }

        return res;
    }

} // hypro