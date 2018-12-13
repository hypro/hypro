#pragma once
#include "rectangular.h"
#include "../../../carlTypes.h"

namespace hypro {

    template<typename N>
    FormulaT<N> createFlowConstraints(carl::Variable original, carl::Variable primed, carl::Variable t, const carl::Interval<N>& flow) {
        FormulaT<N> res = FormulaT<N>(carl::FormulaType::AND);

        // lower flow bound
        if(flow.lowerBoundType() != carl::Interval::BoundType::INFTY) {
            ConstraintT<Number> lb = ConstraintT<N>(Pol(primed) + Pol(flow.lower()) * Pol(t) - Pol(original), carl::Relation::LEQ);
            res.addConstraint(lb);
        }

        // upper flow bound
        if(flow.upperBoundType() != carl::Interval::BoundType::INFTY) {
            ConstraintT<Number> ub = ConstraintT<N>(Pol(primed) + Pol(flow.upper()) * Pol(t) - Pol(original), carl::Relation::GEQ);
            res.addConstraint(ub);
        }

        return res;
    }

} // hypro
