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

template<typename T>
struct Strategy {
    std::vector<StrategyNodeVariant<T>> mStrategy;
};

} // hypro
