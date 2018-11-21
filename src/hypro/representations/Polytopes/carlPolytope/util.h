#pragma once
#include "../../../carlTypes.h"
#include "../../../datastructures/Halfspace.h"
#include "../../../util/VariablePool.h"

namespace hypro {

    template<typename N>
    FormulasT<N> intervalToFormulas(const carl::Interval<N>& interval, std::size_t variableIndex) {
        FormulasT<N> res;
        res.emplace_back(ConstraintT<N>(PolyT<N>(interval.lower()*VariablePool::getInstance().carlVarByIndex(variableIndex)), carl::Relation::GEQ));
        res.emplace_back(ConstraintT<N>(PolyT<N>(interval.upper()*VariablePool::getInstance().carlVarByIndex(variableIndex)), carl::Relation::LEQ));
        return res;
    }

    template<typename N>
    std::vector<Halfspace<N>> constraintToHalfspace(const ConstraintT<N> constraint, std::size_t dim) {
        std::vector<Halfspace<N>> res;
        vector_t<N> normalV = vector_t<N>::Zero(dim);
        N offset = 0;
        for(const auto& var : constraint.getVariables()) {
            assert(VariablePool::getInstance().hasDimension(var));
            assert(constraint.getPolynomial().isLinear());
            if(constraint.relation() == carl::Relation::LEQ || constraint.relation() == carl::Relation::LESS || constraint.relation() == carl::Relation::EQ) {
                normalV(VariablePool::getInstance().id(var)) = constraint.getPolynomial().coeff(var,1);
            } else {
                normalV(VariablePool::getInstance().id(var)) = -constraint.getPolynomial().coeff(var,1);
            }
        }
        if(constraint.relation() == carl::Relation::LEQ || constraint.relation() == carl::Relation::LESS || constraint.relation() == carl::Relation::EQ) {
            offset = -constraint.getPolynomial().constantPart();
        } else {
            offset = constraint.getPolynomial().constantPart();
        }
        res.emplace_back(Halfspace<N>{normalV,offset});

        if(constraint.relation() == carl::Relation::EQ) {
            res.emplace_back(Halfspace<N>{-normalV, -offset});
        }

        return res;
    }

    template<typename N>
    std::vector<Halfspace<N>> computeHalfspaces(const FormulaT<N>& formula, std::size_t dim) {
        assert(formula.isConstraintConjunction());

        std::vector<Halfspace<N>> res;
        std::vector<ConstraintT<N>> constraints;
        formula.getConstraints(constraints);

        for(const auto& c : formula.getConstraints) {
            auto tmp = constraintToHalfspace(c, dim);
            res.emplace(res.end(), tmp.begin(), tmp.end());
        }

        return res;
    }

} // hypro