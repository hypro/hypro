#pragma once
#include "rectangular.h"
#include "../../../carlTypes.h"

namespace hypro {

    template<typename N, typename D>
    std::vector<ConstraintT<N>> createFlowConstraints(carl::Variable original, carl::Variable primed, carl::Variable t, const carl::Interval<D>& flow) {
        std::vector<ConstraintT<N>> res;

        // lower flow bound
        if(flow.lowerBoundType() != carl::BoundType::INFTY) {
            //ConstraintT<N> lb = ConstraintT<N>(PolyT<N>(primed) + PolyT<N>(flow.lower()) * PolyT<N>(t) - PolyT<N>(original), carl::Relation::LEQ);
            res.emplace_back(PolyT<N>(primed) + PolyT<N>(carl::convert<D,N>(flow.lower())) * PolyT<N>(t) - PolyT<N>(original), carl::Relation::LEQ);
        }

        // upper flow bound
        if(flow.upperBoundType() != carl::BoundType::INFTY) {
            //ConstraintT<N> ub = ConstraintT<N>(PolyT<N>(primed) + PolyT<N>(flow.upper()) * PolyT<N>(t) - PolyT<N>(original), carl::Relation::GEQ);
            res.emplace_back(PolyT<N>(primed) + PolyT<N>(carl::convert<D,N>(flow.upper())) * PolyT<N>(t) - PolyT<N>(original), carl::Relation::GEQ);
        }

        return res;
    }

} // hypro
