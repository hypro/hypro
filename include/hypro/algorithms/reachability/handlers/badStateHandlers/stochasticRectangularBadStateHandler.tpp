/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "stochasticRectangularBadStateHandler.h"

namespace hypro {
    template<typename State>
    std::vector <std::pair<CONTAINMENT, State>> stochasticRectangularIntersectBadStates(const State &stateSet,
                                                                                        const HybridAutomaton<typename State::NumberType> &automaton) {
        TRACE("hydra.worker.continuous",
              "Having a total of " << automaton.getLocalBadStates().size() << " local bad states.");
        std::vector <std::pair<CONTAINMENT, State>> results;
        bool isBad = false;
        auto localBadState = automaton.getLocalBadStates().find(stateSet.getLocation());

        if (localBadState != automaton.getLocalBadStates().end()) {
            TRACE("hydra.worker.continuous", "Checking local bad state: " << localBadState->second);

            State badState(stateSet);
            // std::cout << "current state: " << badState << std::endl;

            // create constraints for invariant. Note that we need to properly match dimension indices with variable names at some point.
            // create carlPolytope, as intersection is defined for those
            badState = State{CarlPolytope < typename State::NumberType >
                             {localBadState->second.getMatrix(), localBadState->second.getVector()}};
            // std::cout << "current state to polytope: " << badState << std::endl;

            // intersect
            auto resultingSet = stateSet.intersect(badState);

            // std::cout << "result after intersecting: " << resultingSet << std::endl;

            // reduction
            resultingSet.removeRedundancy();

            // process containment information
            if (!resultingSet.isEmpty()) {
                // std::cout << "result is not empty " << std::endl;
                results.emplace_back(std::make_pair(CONTAINMENT::YES, resultingSet));
                isBad = true;
                CarlPolytope<typename State::NumberType> badStateConstraints{localBadState->second.getMatrix(),
                                                                             localBadState->second.getVector()};
                for (size_t i = 0; i < badStateConstraints.getFormula().size(); i++) {
                    CarlPolytope<typename State::NumberType> badStateNegationConstraints(
                            !badStateConstraints.getFormula().subformulas().at(i));
                    std::vector <ConstraintT<tNumber>> newConstraints;
                    for (size_t j = 0; j < i; j++) {
                        badStateConstraints.getFormula().subformulas().at(j).getConstraints(newConstraints);
                    }
                    badStateNegationConstraints.addConstraints(newConstraints);
                    auto newStateSet = std::get < CarlPolytope < typename State::NumberType
                            >> (stateSet.getSet()).intersect(badStateNegationConstraints);
                    newStateSet.removeRedundancy();
                    State newState(stateSet);
                    newState.setSet(newStateSet);
                    results.emplace_back(std::make_pair(CONTAINMENT::NO, newState));
                }
                DEBUG("hydra.worker", "Intersection with local bad states.");
                // return std::make_pair( CONTAINMENT::YES, resultingSet );
            }
        }

        TRACE("hydra.worker.continuous", "No intersection with local, continuous bad states");

        // check global bad states
        for (const auto &badState: automaton.getGlobalBadStates()) {
            if (badState.getMatrix().rows() != 0) {
                // at least one global bad state in this subspace
                State badState(stateSet);

                // create constraints for invariant. Note that we need to properly match dimension indices with variable names at some point.
                // create carlPolytope, as intersection is defined for those
                badState = State{CarlPolytope < typename State::NumberType >
                                 {localBadState->second.getMatrix(), localBadState->second.getVector()}};

                // intersect
                auto resultingSet = stateSet.intersect(badState);

                // reduction
                resultingSet.removeRedundancy();

                // process containment information
                if (resultingSet != stateSet) {
                    results.emplace_back(std::make_pair(CONTAINMENT::YES, resultingSet));
                    isBad = true;
                    CarlPolytope<typename State::NumberType> badStateConstraints{localBadState->second.getMatrix(),
                                                                                 localBadState->second.getVector()};
                    for (size_t i = 0; i < badStateConstraints.getFormula().size(); i++) {
                        CarlPolytope<typename State::NumberType> badStateNegationConstraints(
                                !badStateConstraints.getFormula().subformulas().at(i));
                        std::vector <ConstraintT<tNumber>> newConstraints;
                        for (size_t j = 0; j < i; j++) {
                            badStateConstraints.getFormula().subformulas().at(j).getConstraints(newConstraints);
                        }
                        badStateNegationConstraints.addConstraints(newConstraints);
                        auto newStateSet = std::get < CarlPolytope < typename State::NumberType
                                >> (stateSet.getSet()).intersect(badStateNegationConstraints);
                        newStateSet.removeRedundancy();
                        State newState(stateSet);
                        newState.setSet(newStateSet);
                        results.emplace_back(std::make_pair(CONTAINMENT::NO, newState));
                    }
                    DEBUG("hydra.worker", "Intersection with local bad states.");
                    // return std::make_pair( CONTAINMENT::YES, resultingSet );
                }
            }
        }

        if (!isBad) {
            results.emplace_back(std::make_pair(CONTAINMENT::NO, stateSet));
        }

        return results;
    }

    template<typename State>
    std::vector <std::pair<CONTAINMENT, State>> stochasticRectangularBadIntersectInitialStates(const State &stateSet,
                                                                                               const StochasticHybridAutomaton<typename State::NumberType> &automaton) {
        TRACE("hydra.worker.continuous",
              "Having a total of " << automaton.getInitialStates().size() << " initial states.");
        std::vector <std::pair<CONTAINMENT, State>> results;
        for (auto initialState: automaton.getProbInitialState()) {
            if (stateSet.getLocation() == initialState.first) {
                CarlPolytope<typename State::NumberType> initialConstraints{initialState.second.first.getMatrix(),
                                                                            initialState.second.first.getVector()};

                // intersect
                auto resultingSet = std::get < CarlPolytope <
                                    typename State::NumberType >> (stateSet.getSet()).intersect(initialConstraints);

                // reduction
                resultingSet.removeRedundancy();

                // process containment information
                if (!resultingSet.empty()) {
                    results.emplace_back(std::make_pair(CONTAINMENT::YES, resultingSet));
                    CarlPolytope<typename State::NumberType> initStateConstraints{initialState.second.first.getMatrix(),
                                                                                  initialState.second.first.getVector()};
                    for (size_t i = 0; i < initStateConstraints.getFormula().size(); i++) {
                        CarlPolytope<typename State::NumberType> initStateNegationConstraints(
                                !initStateConstraints.getFormula().subformulas().at(i));
                        std::vector <ConstraintT<tNumber>> newConstraints;
                        for (size_t j = 0; j < i; j++) {
                            initStateConstraints.getFormula().subformulas().at(j).getConstraints(newConstraints);
                        }
                        initStateNegationConstraints.addConstraints(newConstraints);
                        auto newStateSet = std::get < CarlPolytope < typename State::NumberType
                                >> (stateSet.getSet()).intersect(initStateNegationConstraints);
                        newStateSet.removeRedundancy();
                        State newState(stateSet);
                        newState.setSet(newStateSet);
                        results.emplace_back(std::make_pair(CONTAINMENT::NO, newState));
                    }
                    DEBUG("hydra.worker", "Intersection with initial states.");
                }
            }
        }

        TRACE("hydra.worker.continuous", "No intersection with local, continuous bad states");

        return results;
    }

}  // namespace hypro
