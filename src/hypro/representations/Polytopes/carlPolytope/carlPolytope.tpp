#include "carlPolytope.h"

namespace hypro {

    template<typename Number>
    CarlPolytope<Number>::CarlPolytope(const matrix_t<Number>& constraints, const vector_t<Number>& constants) {
        FormulasT<Number> newConstraints;

        for(Eigen::Index row = 0; row < constraints.rows(); ++row) {
            PolyT<Number> p;
            for(Eigen::Index col = 0; col < constraints.cols(); ++col) {
                p += constraints(row,col)*PolyT<Number>(VariablePool::getInstance().carlVarByIndex(col));
            }
            p -= constants(row);
            newConstraints.emplace_back(FormulaT<Number>(ConstraintT<Number>(p, carl::Relation::LEQ)));
        }

        mFormula = FormulaT<Number>{carl::FormulaType::AND, newConstraints};
    }

    template<typename Number>
    CarlPolytope<Number>::CarlPolytope(const std::vector<carl::Interval<Number>>& intervals) {
        FormulasT<Number> newConstraints;

        for(std::size_t i = 0; i < intervals.size(); ++i) {
            auto tmp = intervalToConstraints(intervals[i], i);
            newConstraints.insert(newConstraints.end(),tmp.begin(),tmp.end());
        }
        mFormula = FormulaT<Number>{carl::FormulaType::AND, newConstraints};
    }

    template<typename Number>
    CarlPolytope<Number> CarlPolytope<Number>::intersect(const CarlPolytope<Number>& rhs) const {
        FormulasT<Number> newConstraints;
        mFormula.getConstraints(newConstraints);
        for(const auto& subformula : rhs.getFormula()) {
            newConstraints.emplace_back(FormulaT<Number>(subformula));
        }
        return CarlPolytope<Number>{FormulaT<Number>(carl::FormulaType::AND, newConstraints)};
    }

} // hypro