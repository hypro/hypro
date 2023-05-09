/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../../../datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../../../datastructures/reachability/ReachTreev2.h"
#include "../../../../types.h"
#include "../../workers/LTIWorker.h"
#include "../ReturnTypes.h"

#include <deque>

namespace hypro {

    template<class Representation, class Location>
    struct RefinementSuccess {
        static_assert(is_location_type<Location>());
        std::vector<ReachTreeNode<Representation, Location> *> pathSuccessors{};
    };
    template<class Representation, class Location>
    RefinementSuccess(
            std::vector<ReachTreeNode<Representation, Location> *>) -> RefinementSuccess<Representation, Location>;

/**
 * @brief Analyzer implementation for refinement (internal)
 * @tparam Representation
 */
    template<typename Representation, typename Automaton>
    class RefinementAnalyzer {
    public:
        using Number = rep_number<Representation>;
        using LocationType = typename Automaton::LocationType;
        using RefinementResult = AnalysisResult<RefinementSuccess<Representation, LocationType>, Failure<Representation, LocationType>>;

        RefinementAnalyzer(Automaton const &ha,
                           FixedAnalysisParameters const &fixedParameters,
                           AnalysisParameters const &parameters)
                : mHybridAutomaton(ha), mFixedParameters(fixedParameters), mParameters(parameters) {}

        /**
         * @brief Refinement on a specific path
         * @param path
         * @return REACHABILITY_RESULT
         */
        void setRefinement(ReachTreeNode<Representation, LocationType> *node, Path<Number, LocationType> path) {
            assert(mWorkQueue.empty());
            mWorkQueue.push_front(node);
            mPath = std::move(path);
        }

        RefinementResult run();

        void addToQueue(ReachTreeNode<Representation, LocationType> *node) {
            // add node if it's past the end of the path or otherwise matches the path
            if (node->getDepth() > mPath.elements.size() || (matchesPathTiming(node) && matchesPathTransition(node))) {
                mWorkQueue.push_front(node);
            }
        }

        void addPastPath(ReachTreeNode<Representation, LocationType> *node) {
            mWorkQueue.push_front(node);
        }

    private:
        bool matchesPathTiming(ReachTreeNode<Representation, LocationType> *node);

        bool matchesPathTransition(ReachTreeNode<Representation, LocationType> *node);

    protected:
        std::deque<ReachTreeNode<Representation, LocationType> *> mWorkQueue;  ///< Queue for nodes in the tree which require processing
        const HybridAutomaton<Number> &mHybridAutomaton;                      ///< Hybrid automaton
        FixedAnalysisParameters mFixedParameters;
        AnalysisParameters mParameters;     ///< Used analysis settings
        Path<Number, LocationType> mPath{};
    };

}  // namespace hypro

#include "RefinementAnalyzer.tpp"
