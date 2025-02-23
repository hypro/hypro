/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../../representations/types.h"
#include "../../../types.h"
#include "../../../util/logging/Logger.h"
#include "../HybridAutomaton.h"
#include "../Location.h"
#include "../flow/operations.h"
#include "Decomposition.h"

#include <algorithm>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/graph_traits.hpp>

namespace hypro {

    template<typename Number>
    representation_name getRepresentationForAutomaton(const HybridAutomaton<Number> &ha);

    template<typename Number>
    representation_name getRepresentationForLocation(const Location<Number> &loc);

    template<typename Number>
    representation_name getRepresentationForSubspace(const Location<Number> &loc, size_t index);

/**
    * decomposed the given space into a set of set of variables. Each of the variable sets indicate
    * dependent variables
    */
    template<typename Number>
    std::vector<std::vector<std::size_t>> getSubspacePartition(const HybridAutomaton<Number> &automaton);

// Returns the subspace and index in the subspace of the dimension in the given decomposition
    inline std::pair<std::size_t, std::size_t>
    getSubspaceIndexOfDimension(std::size_t dimension, const Decomposition &decomposition);

    template<typename Number>
    std::vector<DynamicType> refineSubspaceDynamicTypes(const HybridAutomaton<Number> &automaton);

    template<typename Number>
    bool checkDecomposed(const HybridAutomaton<Number> &automaton);

    template<typename Number>
    std::pair<HybridAutomaton<Number>, Decomposition> decomposeAutomaton(const HybridAutomaton<Number> &automaton);

// adds a number of clocks (initially zero with flow 1) to the subspace
    template<typename Number>
    void addClocksToAutomaton(HybridAutomaton<Number> &ha, std::size_t subspace, std::size_t clockCount);

// adds a variable to store the initial value of the subspace variable to the subspace
    template<typename Number>
    void addInitialVarToAutomaton(HybridAutomaton<Number> &ha, std::size_t subspace, std::size_t count = 1);

// Adds a variable with given flow to the automaton as the last variable in the given subspace
    template<typename Number>
    void addVarToAutomaton(HybridAutomaton<Number> &ha, std::size_t subspace, Number flow);

    namespace detail {
/// adds edges in the subspace graph for related variables of a linear transformation
        template<typename Number>
        void addEdgesForLinTrafo(matrix_t<Number> linTrafo,
                                 boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> &graph);

/// adds edges in the subspace graph for related variables of an affine transformation
        template<typename Number>
        void addEdgesForAffineTrafo(matrix_t<Number> affineTrafo,
                                    boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> &graph);

/// adds edges in the subspace graph for related variables in a condition
        template<typename Number>
        void addEdgesForCondition(const Condition<Number> &condition,
                                  boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> &graph);

/// adds edges in the subspace graph for related variables in an interval transformation
        template<typename Number>
        void addEdgesForRectTrafo(const std::vector<carl::Interval<Number>> &intervals,
                                  boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> &graph);

/// adds edges in the subspace graph for related variables in an interval assignment
        template<typename Number>
        void addEdgesForRectMap(const std::map<carl::Variable, carl::Interval<Number>> &map,
                                boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> &graph);

// adds a variable to the condition as the last variable in the given subspace
        template<typename Number>
        Condition<Number> addVarToCondition(Condition<Number> cond, std::size_t subspace);

// adds clock to the condition and two additional constraints that set the clock to 0
        template<typename Number>
        Condition<Number> addVarToInitial(Condition<Number> cond, std::size_t subspace);
    }  // namespace detail

/// checks whether the automaton is a timed automaton
    template<typename Number>
    bool isTimedAutomaton(const HybridAutomaton<Number> &ha);

/// checks whether the automaton is a rectangular automaton
    template<typename Number>
    bool isRectangularAutomaton(const HybridAutomaton<Number> &ha);

/// checks whether the location exhibits timed automata semantics
    template<typename Number>
    bool isTimedLocation(const Location<Number> &loc);

/// checks whether the location exhibits rectangular automata semantics
    template<typename Number>
    bool isRectangularLocation(const Location<Number> &loc);

/// checks whether the subspace at index exhibits timed automata semantics
    template<typename Number>
    bool isTimedSubspace(const Location<Number> &loc, size_t index);

/// checks whether the subspace at index exhibits singular automata semantics
    template<typename Number>
    bool isSingularSubspace(const Location<Number> &loc, size_t index);

/// checks whether the subspace at index exhibits rectangular automata semantics
    template<typename Number>
    bool isRectangularSubspace(const Location<Number> &loc, size_t index);

/// checks whether the subspace at index exhibits discrete automata semantics
    template<typename Number>
    bool isDiscreteSubspace(const Location<Number> &loc, size_t index);

/// detects most common dynamics type for a hybrid automaton
    template<typename Number>
    DynamicType getDynamicType(const HybridAutomaton<Number> &automaton) {
        DynamicType res = DynamicType::undefined;
        auto locPtrs = automaton.getLocations();
        std::for_each(locPtrs.begin(), locPtrs.end(), [&res](const auto *loc) {
            DynamicType cur = getDynamicType(*loc);
            if (res == DynamicType::undefined) {
                res = cur;
            } else {
                res = cur == res ? res : DynamicType::mixed;
            }
        });
        assert(res != DynamicType::undefined);
        return res;
    }

/// detects most common dynamics type for a location of a hybrid automaton.
/// This function is NOT a sanity check - if rectangular dynamics are present we assume that the according constraints are axis-aligned.
    template<typename Number>
    DynamicType getDynamicType(const Location<Number> &location) {
        // if no flows are defined the automaton is discrete
        if (location.getFlows().empty()) {
            return DynamicType::discrete;
        }

        // first initialization, can either be linear or rectangular
        DynamicType res{DynamicType::undefined};
        // flow
        for (std::size_t i = 0; i < location.getFlowTypes().size(); ++i) {
            auto curType = std::visit(flowDynamicsTypeVisitor{}, location.getFlows()[i]);
            if (res != DynamicType::undefined && res != curType) {
                return DynamicType::mixed;
            }
            res = curType;
        }
        // invariant
        if (res != DynamicType::linear && res != DynamicType::rectangular) {
            if (!location.getInvariant().isAxisAligned()) {
                res = DynamicType::linear;
            }
        }
        // transitions: guard & reset
        if (res != DynamicType::linear && res != DynamicType::rectangular) {
            for (const auto &transition: location.getTransitions()) {
                // check guard
                if (!transition->getGuard().isAxisAligned()) {
                    res = DynamicType::linear;
                }
                // corner case: resets to intervals
                if (std::any_of(transition->getReset().getIntervalResets().begin(),
                                transition->getReset().getIntervalResets().end(),
                                [](const auto &assignment) { return !assignment.isIdentity(); })) {
                    return DynamicType::mixed;
                }
                // check reset
                if (res != DynamicType::linear) {
                    std::for_each(transition->getReset().getAffineResets().begin(),
                                  transition->getReset().getAffineResets().end(), [&res](const auto &reset) {
                                if (!reset.isConstant()) {
                                    res = DynamicType::linear;
                                }
                            });
                }
            }
        }
        return res;
    }

}  // namespace hypro

#include "DecompositionMethods.tpp"
