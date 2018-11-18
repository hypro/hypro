#pragma once
#include "../../../carlTypes.h"
#include "../../../util/VariablePool.h"

namespace hypro {

    template<typename N>
    FormulasT<N> intervalToConstraints(const carl::Interval<N>& interval, std::size_t variableIndex) {
        FormulasT<N> res;
        res.emplace_back(ConstraintT<N>(PolyT<N>(interval.lower()*VariablePool::getInstance().carlVarByIndex(variableIndex)), carl::Relation::GEQ));
        res.emplace_back(ConstraintT<N>(PolyT<N>(interval.upper()*VariablePool::getInstance().carlVarByIndex(variableIndex)), carl::Relation::LEQ));
        return res;
    }

} // hypro