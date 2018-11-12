#pragma once

#include "StrategyNode.h"
#include <vector>

namespace hypro {

namespace detail {
    template<typename T>
    struct StrategyVariant;
    template<typename... Ts>
    struct StrategyVariant<boost::variant<Ts...>> {
        using types = boost::variant<StrategyNode<Ts>...>;
    };
}

template<typename State>
using StrategyNodeVariant = typename detail::StrategyVariant<typename State::repVariant>::types;

template<typename StateType>
struct Strategy {
    std::vector<StrategyNodeVariant<StateType>> mStrategy;

    void advanceToLevel( StateType& state, std::size_t lvl) {
        boost::apply_visitor(detail::strategyConversionVisitor<StateType>(state), mStrategy[lvl]);
    }
};

} // hypro
