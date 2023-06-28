/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "DecompositionMethods.h"

namespace hypro {
    template<typename Number>
    representation_name getRepresentationForSubspace(const Location<Number> &loc, size_t index) {
        // in the beginning we assume it is a timed automaton
        bool isTimed = isTimedSubspace(loc, index);

        TRACE("hypro.decisionEntity", "Is Timed subspace? " << isTimed);
        if (isTimed) {
            return representation_name::difference_bounds;
        }
        return representation_name::UNDEF;
    }

    template<typename Number>
    representation_name getRepresentationForAutomaton(const HybridAutomaton<Number> &ha) {
        // in the beginning we assume it is a timed automaton
        bool isTimed = isTimedAutomaton(ha);

        TRACE("hypro.decisionEntity", "Is Timed automaton? " << isTimed);
        if (isTimed) {
            return representation_name::difference_bounds;
        }
        return representation_name::UNDEF;
    }

    template<typename Number>
    representation_name getRepresentationForLocation(const Location<Number> &loc) {
        // in the beginning we assume it is a timed automaton
        bool isTimed = isTimedLocation(loc);

        TRACE("hypro.decisionEntity", "Is Timed location? " << isTimed);
        if (isTimed) {
            return representation_name::difference_bounds;
        }
        return representation_name::UNDEF;
    }

    template<typename Number>
    bool isDiscreteSubspace(const Location<Number> &loc, size_t index) {
        assert(index < loc.getNumberSubspaces());
        if (loc.getFlowTypes()[index] == DynamicType::rectangular) {
            return false;
        }
        return loc.getLinearFlow(index).isDiscrete();
    }

    template<typename Number>
    bool isTimedSubspace(const Location<Number> &loc, size_t index) {
        assert(index < loc.getNumberSubspaces());
        TRACE("hypro.decisionEntity", "Investigating " << loc.getName() << ", subspace " << index);
        if (loc.getFlowTypes()[index] == DynamicType::rectangular) {
            return false;
        }
        // check if flow is of the form
        //	0 ... 0 1
        //  .........
        //	0 ... 0 1
        //  0 ....0 0

        if (!(loc.getLinearFlow(index)).isTimed()) {
            TRACE("hypro.decisionEntity", "Flow is not timed.");
            return false;
        }

        // check if the constraints of the invariant set only contain 0s and one entry 1/-1 at most
        if (loc.getInvariant().size() > 0) {
            if (!loc.getInvariant().isAxisAligned(index)) {
                TRACE("hypro.decisionEntity", "Invariant is not axis-aligned.");
                return false;
            }
        }

        for (const auto &transition: loc.getTransitions()) {
            TRACE("hypro.decisionEntity", "Investigating " << transition->getSource()->getName() << " -> "
                                                           << transition->getTarget()->getName());

            // for each transitions check if the constraints of the guard set only only contain 0s and one entry 1/-1 at most

            if (transition->getGuard().size() > 0) {
                if (!transition->getGuard().isAxisAligned(index)) {
                    TRACE("hypro.decisionEntity", "Guard is not axis-aligned.");
                    return false;
                }
            }

            // check if for each transition the reset function is of the form
            //
            //	0/1	 0  ...  0 | 0
            //	0  0/1 0 ... 0 | 0
            //	..................
            //  0 ...... 0 0/1 | 0
            if (transition->getReset().size() > 0) {
                matrix_t<Number> reset = transition->getReset().getMatrix(index);
                for (int i = 0; i < reset.rows(); i++) {
                    matrix_t<Number> expected0 = matrix_t<Number>::Zero(1, reset.cols());
                    matrix_t<Number> expected1 = matrix_t<Number>::Zero(1, reset.cols());
                    expected1(0, i) = Number(1.0);
                    if (!(reset.row(i) == expected0 || reset.row(i) == expected1)) {
                        TRACE("hypro.decisionEntitiy", "Reset matrix rows do not match.");
                        return false;
                    }
                }
            }

            if (transition->getReset().size() > 0) {
                matrix_t<Number> reset = transition->getReset().getVector(index);
                if (reset != matrix_t<Number>::Zero(reset.rows(), 1)) {
                    TRACE("hypro.decisionEntitiy", "Reset vector rows do not reset to zero.");
                    return false;
                }
            }
        }
        TRACE("hypro.decisionEntitiy", "Is timed.");
        return true;
    }

    template<typename Number>
    bool isSingularSubspace(const Location<Number> &loc, size_t index) {
        assert(index < loc.getNumberSubspaces());
        TRACE("hypro.decisionEntity", "Investigating " << loc.getName() << ", subspace " << index);
        if (loc.getFlowTypes()[index] == DynamicType::rectangular) {
            return false;
        }
        // check if flow is of the form
        //	0 ... 0 c_1
        //  .........
        //	0 ... 0 c_n
        //  0 ....0 0

        if (!(loc.getLinearFlow(index)).isSingular()) {
            TRACE("hypro.decisionEntity", "Flow is not singular.");
            return false;
        }

        // check if the constraints of the invariant set only contain 0s and one entry 1/-1 at most
        if (loc.getInvariant().size() > 0) {
            if (!loc.getInvariant().isAxisAligned(index)) {
                TRACE("hypro.decisionEntity", "Invariant is not axis-aligned.");
                return false;
            }
        }

        for (const auto &transition: loc.getTransitions()) {
            TRACE("hypro.decisionEntity", "Investigating " << transition->getSource()->getName() << " -> "
                                                           << transition->getTarget()->getName());

            // for each transitions check if the constraints of the guard set only only contain 0s and one entry 1/-1 at most

            if (transition->getGuard().size() > 0) {
                if (!transition->getGuard().isAxisAligned(index)) {
                    TRACE("hypro.decisionEntity", "Guard is not axis-aligned.");
                    return false;
                }
            }

            // Check that all resets are interval based
            if (transition->getReset().size() > 0) {
                if (!transition->getReset().getAffineReset(index).isSingular()) {
                    TRACE("hypro.decisionEntity", "Reset is not interval-based.");
                    return false;
                }
            }
        }
        TRACE("hypro.decisionEntitiy", "Is timed.");
        return true;
    }

    template<typename Number>
    bool isRectangularSubspace(const Location<Number> &loc, size_t index) {
        assert(index < loc.getNumberSubspaces());
        TRACE("hypro.decisionEntity", "Investigating " << loc.getName() << ", subspace " << index);
        if (loc.getFlowTypes()[index] != DynamicType::rectangular) {
            TRACE("hypro.decisionEntity", "Flow is not rectangular.");
            return false;
        }

        // check if the constraints of the invariant set only contain 0s and one entry 1/-1 at most
        if (loc.getInvariant().size() > 0) {
            if (!loc.getInvariant().isAxisAligned(index)) {
                TRACE("hypro.decisionEntity", "Invariant is not axis-aligned.");
                return false;
            }
        }

        for (const auto &transition: loc.getTransitions()) {
            TRACE("hypro.decisionEntity", "Investigating " << transition->getSource()->getName() << " -> "
                                                           << transition->getTarget()->getName());

            // for each transitions check if the constraints of the guard set only only contain 0s and one entry 1/-1 at most

            if (transition->getGuard().size() > 0) {
                if (!transition->getGuard().isAxisAligned(index)) {
                    TRACE("hypro.decisionEntity", "Guard is not axis-aligned.");
                    return false;
                }
            }

            // check if for each transition the reset function is of the form
            //
            //	0/1	 0  ...  0 | 0
            //	0  0/1 0 ... 0 | 0
            //	..................
            //  0 ...... 0 0/1 | 0
            if (transition->getReset().size() > 0) {
                if (!transition->getReset().getAffineReset(index).isIdentity()) {
                    TRACE("hypro.decisionEntity", "Reset is not interval-based.");
                    return false;
                }
            }
        }
        TRACE("hypro.decisionEntitiy", "Is rectangular.");
        return true;
    }

    template<typename Number>
    bool isTimedLocation(const Location<Number> &loc) {
        TRACE("hypro.decisionEntity", "Investigating " << loc.getName());
        // check if flow is of the form
        //	0 ... 0 1
        //  .........
        //	0 ... 0 1
        //  0 ....0 0
        for (size_t i = 0; i < loc.getNumberFlow(); i++) {
            if (!loc.getLinearFlow(i).isTimed()) {
                TRACE("hypro.decisionEntity", "Flow is not timed.");
                return false;
            }
        }

        // check if the constraints of the invariant set only contain 0s and one entry 1/-1 at most
        if (!loc.getInvariant().isAxisAligned()) {
            TRACE("hypro.decisionEntity", "Invariant is not axis-aligned.");
            return false;
        }

        for (const auto &transition: loc.getTransitions()) {
            TRACE("hypro.decisionEntity", "Investigating " << transition->getSource()->getName() << " -> "
                                                           << transition->getTarget()->getName());

            // for each transitions check if the constraints of the guard set only only contain 0s and one entry 1/-1 at most
            if (!transition->getGuard().isAxisAligned()) {
                TRACE("hypro.decisionEntity", "Guard is not axis-aligned.");
                return false;
            }

            // check if for each transition the reset function is of the form
            //
            //	0/1	 0  ...  0 | 0
            //	0  0/1 0 ... 0 | 0
            //	..................
            //  0 ...... 0 0/1 | 0
            for (size_t i = 0; i < transition->getReset().size(); i++) {
                matrix_t<Number> reset = transition->getReset().getMatrix(i);
                for (int i = 0; i < reset.rows(); i++) {
                    matrix_t<Number> expected0 = matrix_t<Number>::Zero(1, reset.cols());
                    matrix_t<Number> expected1 = matrix_t<Number>::Zero(1, reset.cols());
                    expected1(0, i) = Number(1.0);
                    if (!(reset.row(i) == expected0 || reset.row(i) == expected1)) {
                        TRACE("hypro.decisionEntity", "Reset is not timed.");
                        return false;
                    }
                }
            }

            for (size_t i = 0; i < transition->getReset().size(); i++) {
                matrix_t<Number> reset = transition->getReset().getVector(i);
                if (reset != matrix_t<Number>::Zero(reset.rows(), 1)) {
                    TRACE("hypro.decisionEntity", "Reset is not timed.");
                    return false;
                }
            }
        }

        return true;
    }

    template<typename Number>
    bool isRectangularLocation(const Location<Number> &loc) {
        for (size_t i = 0; i < loc.getNumberFlow(); i++) {
            if (!isRectangularSubspace(loc, i)) {
                return false;
            }
        }
        return true;
    }

    template<typename Number>
    bool isTimedAutomaton(const HybridAutomaton<Number> &ha) {
        return std::all_of(ha.getLocations().begin(), ha.getLocations().end(),
                           [](auto locPtr) { return isTimedLocation(*locPtr); });
    }

    template<typename Number>
    bool isRectangularAutomaton(const HybridAutomaton<Number> &ha) {
        return std::all_of(ha.getLocations().begin(), ha.getLocations().end(),
                           [](auto locPtr) { return isRectangularLocation(*locPtr); });
    }

    template<typename Number>
    bool checkDecomposed(const HybridAutomaton<Number> &automaton) {
        for (const auto &locConditionPair: automaton.getInitialStates()) {
            if (locConditionPair.second.size() > 1) {
                return true;
            }
        }
        return false;
    }

    namespace detail {

        template<typename Number>
        void addEdgesForAffineTrafo(matrix_t<Number> affineTrafo,
                                    boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> &graph) {
            matrix_t<Number> tmp(affineTrafo);
            // we do not consider the constant part of the trafo
            tmp.conservativeResize(tmp.rows() - 1, tmp.cols() - 1);

            addEdgesForLinTrafo(tmp, graph);
        }

        template<typename Number>
        void addEdgesForLinTrafo(matrix_t<Number> linTrafo,
                                 boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> &graph) {
            for (Eigen::Index i = 0; i < linTrafo.rows(); i++) {
                for (Eigen::Index j = 0; j < linTrafo.cols(); j++) {
                    if (linTrafo(i, j) != 0) {
                        boost::add_edge(i, j, graph);
                    }
                }
            }
        }

        template<typename Number>
        void addEdgesForRectTrafo(const std::vector<carl::Interval<Number>> &intervals,
                                  boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> &graph) {
            for (size_t i = 0; i < intervals.size(); i++) {
                for (size_t j = 0; j < intervals.size(); j++) {
                    if (i != j && intervals[i] != createEmptyInterval<Number>() &&
                        intervals[j] != createEmptyInterval<Number>()) {
                        boost::add_edge(i, j, graph);
                    }
                }
            }
        }

        template<typename Number>
        void addEdgesForRectMap(const std::map<carl::Variable, carl::Interval<Number>> &map,
                                boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> &graph) {
            auto &vpool = VariablePool::getInstance();
            for (const auto &keyValPair1: map) {
                for (const auto &keyValPair2: map) {
                    if (keyValPair1.first != keyValPair2.first) {
                        boost::add_edge(vpool.id(keyValPair1.first), vpool.id(keyValPair2.first), graph);
                    }
                }
            }
        }

        template<typename Number>
        void addEdgesForCondition(const Condition<Number> &condition,
                                  boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> &graph) {
            if (!(condition.size() > 0)) {
                // empty condition (e.g. location with no invariant) --> do nothing
                return;
            }
            matrix_t<Number> tmp(condition.getMatrix());

            for (Eigen::Index i = 0; i < tmp.rows(); i++) {
                // pairwise comparison of the row entries
                for (Eigen::Index j = 0; j < tmp.cols(); j++) {
                    for (Eigen::Index k = 0; k < tmp.cols(); k++) {
                        // Example:
                        //  row i: 0,0,2,0,0,-4
                        //             j      k
                        //  => j and k are dependent
                        if (tmp(i, j) != 0 && tmp(i, k) != 0) {
                            boost::add_edge(j, k, graph);
                        }
                    }
                }
            }
        }

        template<typename Number>
        Condition<Number> addVarToCondition(Condition<Number> cond, std::size_t subspace) {
            if (cond.empty()) {
                return cond;
            }
            auto matrix = cond.getMatrix(subspace);
            matrix_t<Number> newConditionMatrix(matrix.rows(), matrix.cols() + 1);
            newConditionMatrix.leftCols(matrix.cols()) = matrix;
            for (Eigen::Index i = 0; i < newConditionMatrix.rows(); ++i) {
                newConditionMatrix(i, newConditionMatrix.cols() - 1) = 0;
            }
            cond.setMatrix(newConditionMatrix, subspace);
            return cond;
        }

    }  // namespace detail

    template<typename Number>
    std::vector<std::vector<std::size_t>> getSubspacePartition(const HybridAutomaton<Number> &automaton) {
        if (checkDecomposed(automaton)) {
            // return empty decomposition
            return std::vector<std::vector<std::size_t>>();
        }
        typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;
        Graph G(automaton.dimension());

        // check flow and invariant of locations
        for (auto locPtr: automaton.getLocations()) {
            // Automaton is not decomposed so every location should have exactly one flow
            if (locPtr->getNumberSubspaces() != 1) {
                std::cout << "Number subspaces: " << locPtr->getNumberSubspaces() << "\n";
            }
            assert(locPtr->getNumberSubspaces() == 1 && "Subspace decomposition called on decomposed automaton");
            switch (locPtr->getFlowTypes()[0]) {
                case DynamicType::discrete:
                    [[fallthrough]];
                case DynamicType::timed:
                    [[fallthrough]];
                case DynamicType::singular:
                    [[fallthrough]];
                case DynamicType::affine:
                    [[fallthrough]];
                case DynamicType::linear:
                    detail::addEdgesForAffineTrafo(locPtr->getLinearFlow().getFlowMatrix(), G);
                    break;
                case DynamicType::rectangular:
                    // Rectangular flows do not introduce dependencies
                    // detail::addEdgesForRectMap( locPtr->getRectangularFlow().getFlowIntervals(), G );
                    break;
                default:
                    assert(false && "Decompososition for flow type not implemented yet.");
                    break;
            }
            detail::addEdgesForCondition(locPtr->getInvariant(), G);
        }

        // check reset and guards of transitions
        for (const auto &transition: automaton.getTransitions()) {
            detail::addEdgesForLinTrafo(transition->getReset().getMatrix(), G);
            // Resets to intervals do not introduce dependencies
            // detail::addEdgesForRectTrafo( transition->getReset().getIntervals(), G );
            detail::addEdgesForCondition(transition->getGuard(), G);
        }

        // check local bad states
        for (const auto &locConditionPair: automaton.getLocalBadStates()) {
            detail::addEdgesForCondition(locConditionPair.second, G);
        }
        // check global bad states
        for (const auto &condition: automaton.getGlobalBadStates()) {
            detail::addEdgesForCondition(condition, G);
        }

        std::vector<int> component(num_vertices(G));
        int num = boost::connected_components(G, &component[0]);
        // components now holds an array. It has one entry for each variable specifying its component
        // we parse this to a vector of vectors. each vector contains the variable indices for one component
        // and can consequently can be given to project.
        std::vector<std::vector<size_t>> res(num);
        std::vector<size_t>::size_type i;
        for (i = 0; i != component.size(); i++) {
            res[component[i]].push_back(i);
        }
        return res;
    }

    inline std::pair<std::size_t, std::size_t>
    getSubspaceIndexOfDimension(std::size_t dimension, const Decomposition &decomposition) {
        std::size_t accumulatedDimensions = 0;
        std::size_t subspaceSize;
        for (std::size_t subspace = 0; subspace < decomposition.subspaces.size(); ++subspace) {
            subspaceSize = decomposition.subspaces[subspace].size();
            if (accumulatedDimensions + subspaceSize > dimension) {
                return std::make_pair(subspace, dimension - accumulatedDimensions);
            }
            accumulatedDimensions += subspaceSize;
        }
        assert(false && "Dimension not found in decomposition (dimension too large)");
        return std::make_pair(0, 0);
    }

    template<typename Number>
    std::pair<HybridAutomaton<Number>, Decomposition> decomposeAutomaton(const HybridAutomaton<Number> &automaton) {
        // compute decomposition
        auto partition = getSubspacePartition(automaton);

        // Todo: What if partition.size() == 0? In that case decomposition must have been called twice
        if (partition.size() == 0) {
            // decomposing failed/was already done(0-case)
            return std::make_pair(automaton, Decomposition());
        }
        TRACE("hypro.decisionEntity", "Automaton before decomposition: " << automaton);
        auto automatonCopy = automaton;
        automatonCopy.decompose(partition);
        Decomposition res;
        res.subspaces = partition;
        res.subspaceTypes = refineSubspaceDynamicTypes(automatonCopy);

        TRACE("hypro.decisionEntity", "Automaton after decomposition: " << automatonCopy);
        return std::make_pair(automatonCopy, res);
    }

    template<typename Number>
    std::vector<DynamicType> refineSubspaceDynamicTypes(const HybridAutomaton<Number> &automaton) {
        std::vector<DynamicType> subspaceTypes(automaton.getLocations()[0]->getNumberSubspaces(),
                                               DynamicType::undefined);
        // Check for every location which dynamics it has in the subspace. Combine them

#ifndef NDEBUG
        // Assume that every location is decomposed in the same number of subspaces, as is done by the decomposeAutomaton function
        for (auto &loc: automaton.getLocations()) {
            assert(loc->getNumberSubspaces() == subspaceTypes.size());
        }
#endif
        for (std::size_t subspaceIndex = 0; subspaceIndex < subspaceTypes.size(); ++subspaceIndex) {
            bool discrete = true, singular = true, timed = true, rectangular = true, linear = true;
            for (const auto &loc: automaton.getLocations()) {
                if (discrete && !isDiscreteSubspace(*loc, subspaceIndex)) {
                    discrete = false;
                }
                if (singular && !isSingularSubspace(*loc, subspaceIndex)) {
                    singular = false;
                }
                if (timed && !isTimedSubspace(*loc, subspaceIndex)) {
                    timed = false;
                }
                if (rectangular && !isRectangularSubspace(*loc, subspaceIndex)) {
                    rectangular = false;
                }
                if (linear && isRectangularSubspace(*loc, subspaceIndex)) {
                    linear = false;
                }
            }
            if (discrete) {
                subspaceTypes[subspaceIndex] = DynamicType::discrete;
            } else if (timed) {
                subspaceTypes[subspaceIndex] = DynamicType::timed;
            } else if (singular) {
                subspaceTypes[subspaceIndex] = DynamicType::singular;
            } else if (rectangular) {
                subspaceTypes[subspaceIndex] = DynamicType::rectangular;
            } else if (linear) {
                subspaceTypes[subspaceIndex] = DynamicType::linear;
            } else {
                subspaceTypes[subspaceIndex] = DynamicType::mixed;
            }
        }
        return subspaceTypes;
    }

    template<typename Number>
    void addClocksToAutomaton(HybridAutomaton<Number> &ha, std::size_t subspace, std::size_t clockCount) {
        for (std::size_t clockIndex = 0; clockIndex < clockCount; ++clockIndex) {
            addVarToAutomaton(ha, subspace, Number(1));
            // initially zero
            std::map<const Location<Number> *, Condition<Number>> newInitialStates;
            for (auto &[loc, cond]: ha.getInitialStates()) {
                Condition<Number> newCond = cond;
                auto condMatrix = cond.getMatrix(subspace);
                auto condVector = cond.getVector(subspace);
                condMatrix.conservativeResize(condMatrix.rows() + 2, condMatrix.cols());
                condVector.conservativeResize(condVector.rows() + 2);
                for (Eigen::Index i = 0; i < condMatrix.cols() - 1; ++i) {
                    condMatrix(condMatrix.rows() - 2, i) = 0;
                    condMatrix(condMatrix.rows() - 1, i) = 0;
                }
                condMatrix(condMatrix.rows() - 2, condMatrix.cols() - 1) = 1;
                condMatrix(condMatrix.rows() - 1, condMatrix.cols() - 1) = -1;
                condVector(condVector.rows() - 2) = 0;
                condVector(condVector.rows() - 1) = 0;
                newCond.setMatrix(condMatrix, subspace);
                newCond.setVector(condVector, subspace);
                newInitialStates[loc] = newCond;
            }
            ha.setInitialStates(newInitialStates);
        }
    }

    template<typename Number>
    void addInitialVarToAutomaton(HybridAutomaton<Number> &ha, std::size_t subspace, std::size_t count) {
        for (std::size_t varIndex = 0; varIndex < count; ++varIndex) {
            addVarToAutomaton(ha, subspace, Number(0));
            // initial state doesn't matter because there are no dependencies before first clock reset,
            // so the variables are set to 0
            std::map<const Location<Number> *, Condition<Number>> newInitialStates;
            for (auto &[loc, cond]: ha.getInitialStates()) {
                Condition<Number> newCond = cond;
                auto condMatrix = cond.getMatrix(subspace);
                auto condVector = cond.getVector(subspace);
                condMatrix.conservativeResize(condMatrix.rows() + 2, condMatrix.cols());
                condVector.conservativeResize(condVector.rows() + 2);
                for (Eigen::Index i = 0; i < condMatrix.cols() - 1; ++i) {
                    condMatrix(condMatrix.rows() - 2, i) = 0;
                    condMatrix(condMatrix.rows() - 1, i) = 0;
                }
                condMatrix(condMatrix.rows() - 2, condMatrix.cols() - 1) = 1;
                condMatrix(condMatrix.rows() - 1, condMatrix.cols() - 1) = -1;
                condVector(condVector.rows() - 2) = 0;
                condVector(condVector.rows() - 1) = 0;
                newCond.setMatrix(condMatrix, subspace);
                newCond.setVector(condVector, subspace);
                newInitialStates[loc] = newCond;
            }
            ha.setInitialStates(newInitialStates);
        }
    }

    template<typename Number>
    void addVarToAutomaton(HybridAutomaton<Number> &ha, std::size_t subspace, Number flow) {
        for (auto &loc: ha.getLocations()) {
            if (loc->getFlowTypes()[subspace] == DynamicType::rectangular) {
                // rectangular flow
                auto clockVariable = VariablePool::getInstance().newCarlVariable();
                auto locFlow = loc->getRectangularFlow(subspace);
                locFlow.setFlowIntervalForDimension(carl::Interval<Number>(flow), clockVariable);
            } else {
                // linear flow types
                auto flowMatrix = loc->getLinearFlow(subspace).getFlowMatrix();
                std::size_t dim = flowMatrix.rows() - 1;
                // add var as last variable (second to last row/col, since last row/col is affine)
                matrix_t<Number> newFlowMatrix(flowMatrix.rows() + 1, flowMatrix.cols() + 1);
                // flow for variables doesn't change
                newFlowMatrix.topLeftCorner(dim, dim) = flowMatrix.topLeftCorner(dim, dim);
                for (std::size_t i = 0; i < dim; ++i) {
                    // no variable depends on the var
                    newFlowMatrix(i, dim) = 0;
                    // old affine coefficients
                    newFlowMatrix(i, dim + 1) = flowMatrix(i, dim);
                }
                // bottom 2 rows for var + affine
                newFlowMatrix.bottomRows(2) = matrix_t<Number>::Zero(2, dim + 2);
                newFlowMatrix(dim, dim + 1) = flow;
                loc->setFlow(newFlowMatrix, subspace);
            }
            // invariant
            loc->setInvariant(detail::addVarToCondition(loc->getInvariant(), subspace));
        }
        // local bad states
        std::map<const Location<Number> *, Condition<Number>> newLocalBadStates;
        for (auto &[loc, cond]: ha.getLocalBadStates()) {
            newLocalBadStates[loc] = detail::addVarToCondition(cond, subspace);
        }
        ha.setLocalBadStates(newLocalBadStates);
        // global bad states
        std::vector<Condition<Number>> newGlobalBadStates;
        for (auto &badState: ha.getGlobalBadStates()) {
            newGlobalBadStates.push_back(detail::addVarToCondition(badState, subspace));
        }
        ha.setGlobalBadStates(newGlobalBadStates);
        // initial states
        std::map<const Location<Number> *, Condition<Number>> newInitialStates;
        for (auto &[loc, cond]: ha.getInitialStates()) {
            newInitialStates[loc] = detail::addVarToCondition(cond, subspace);
        }
        ha.setInitialStates(newInitialStates);
        // transitions
        for (auto &trans: ha.getTransitions()) {
            // guards
            trans->setGuard(detail::addVarToCondition(trans->getGuard(), subspace));
            // resets
            auto reset = trans->getReset();
            if (reset.size() > subspace) {
                auto resetMatrix = reset.getMatrix(subspace);
                auto resetVec = reset.getVector(subspace);
                auto resetIntervals = reset.getIntervals(subspace);
                resetMatrix.conservativeResize(resetMatrix.rows() + 1, resetMatrix.cols() + 1);
                resetMatrix.bottomRows(1) = matrix_t<Number>::Zero(1, resetMatrix.cols());
                resetMatrix.rightCols(1) = matrix_t<Number>::Zero(resetMatrix.rows(), 1);
                resetMatrix(resetMatrix.rows() - 1, resetMatrix.cols() - 1) = 1;
                resetVec.conservativeResize(resetVec.rows() + 1);
                resetVec(resetVec.rows() - 1) = 0;
                resetIntervals.push_back(carl::Interval<Number>());
                reset.setMatrix(resetMatrix, subspace);
                reset.setVector(resetVec, subspace);
                reset.setIntervals(resetIntervals, subspace);
                trans->setReset(reset);
            }
        }
    }

}  // namespace hypro
