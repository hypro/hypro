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
} // detail

template<typename State>
using StrategyNodeVariant = typename detail::StrategyVariant<typename State::repVariant>::types;

template<typename StateType>
class Strategy {
    std::vector<StrategyNodeVariant<StateType>> mStrategy;

public:
    Strategy() = default;
    Strategy(std::initializer_list<StrategyNodeVariant<StateType>> in) : mStrategy(in) {}

    const std::vector<StrategyNodeVariant<StateType>>& getStrategy() const {return mStrategy;}
    void setStrategy(const std::vector<StrategyNodeVariant<StateType>>& s) {mStrategy = s;}
    void emplace_back(StrategyNodeVariant<StateType>&& n) {mStrategy.emplace_back(std::move(n));}

    std::size_t size() const {return mStrategy.size();}
    const StrategyNodeVariant<StateType>& operator[](std::size_t i) const {return mStrategy[i];}

    void advanceToLevel( StateType& state, std::size_t lvl, std::size_t subset=0) const {
        boost::apply_visitor(detail::strategyConversionVisitor<StateType>(state,subset), mStrategy[lvl]);
    }

    StrategyParameters getParameters(std::size_t lvl) const {
        assert(lvl < mStrategy.size());
        return boost::apply_visitor(detail::getParametersVisitor(), mStrategy[lvl]);
    }
};

} // hypro
