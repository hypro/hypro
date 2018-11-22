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
    std::vector<Halfspace<N>> constraintToHalfspace(const ConstraintT<N> constraint, std::size_t dim) {
        TRACE("hypro.representations.carlPolytope","Compute half-spaces from " << constraint << " with dimension " << dim);
        std::vector<Halfspace<N>> res;
        vector_t<N> normalV = vector_t<N>::Zero(dim);
        N offset = 0;
        for(const auto& var : constraint.variables()) {
            assert(VariablePool::getInstance().hasDimension(var));
            assert(constraint.lhs().isLinear());
            assert(constraint.lhs().coeff(var,1).isNumber());
            if(constraint.relation() == carl::Relation::LEQ || constraint.relation() == carl::Relation::LESS || constraint.relation() == carl::Relation::EQ) {
                normalV(VariablePool::getInstance().id(var)) = constraint.lhs().coeff(var,1).constantPart();
            } else {
                normalV(VariablePool::getInstance().id(var)) = -constraint.lhs().coeff(var,1).constantPart();
            }
        }
        if(constraint.relation() == carl::Relation::LEQ || constraint.relation() == carl::Relation::LESS || constraint.relation() == carl::Relation::EQ) {
            offset = -constraint.lhs().constantPart();
        } else {
            offset = constraint.lhs().constantPart();
        }
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