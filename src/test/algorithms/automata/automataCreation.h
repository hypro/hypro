#pragma once
#include <hypro/datastructures/HybridAutomaton/HybridAutomaton.h>
#include <hypro/datastructures/Point.h>
#include <tuple>

namespace hypro {
namespace testing {

template <typename Number>
HybridAutomaton<Number> createPLTSingularAutomaton();

template <typename Number>
std::tuple<HybridAutomaton<Number>, std::vector<Point<Number>>, std::vector<Point<Number>>> createRectangularHA();
}  // namespace testing
}  // namespace hypro

#include "automataCreation.tpp"
