/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../../datastructures/reachability/Flowpipe.h"
#include "../../../datastructures/reachability/Settings.h"
#include "../../../util/logging/Logger.h"
#include "../../../util/plotting/PlotData.h"
#include "../FlowpipeConstructionConvenience.h"
#include "../handlers/badStateHandlers/ltiBadStateHandler.h"
#include "../handlers/guardHandlers/rectangularGuardHandler.h"
#include "../handlers/jumpHandlers/singularJumpHandler.h"
#include "../handlers/resetHandlers/rectangularResetHandler.h"
#include "../handlers/timeEvolutionHandlers/singularTimeEvolutionHandler.h"

#include <vector>

namespace hypro {

/**
 * @brief Class implementing a worker for rectangular automata.
 * @details A worker implements a method computing a time transition followed by a discrete transition. The repeated calling of a worker allows to implement a complete reachability analysis method.
 * @tparam Representation
 */
    template<typename Representation, typename Automaton>
    class SingularWorker {
    private:
        using Number = typename Representation::NumberType;
        using LocationT = typename Automaton::LocationType;
        using JumpSuccessors = typename rectangularGuardHandler<Representation, LocationT>::TransitionStatesMap;
        using JumpPredecessors = typename rectangularGuardHandler<Representation, LocationT>::TransitionStatesMap;

    public:
        /// constructor from rectangular automaton and settings
        SingularWorker(const Automaton &ha, const FixedAnalysisParameters &settings, std::size_t subspace = 0)
                : mHybridAutomaton(ha), mSettings(settings), mSubspace(subspace) {}

        /// computes a time transition followed by a discrete transition
        REACHABILITY_RESULT computeForwardReachability(const ReachTreeNode<Representation, LocationT> &task);

        /// computes a time transition
        REACHABILITY_RESULT
        computeTimeSuccessors(const ReachTreeNode<Representation, LocationT> &task, bool checkSafety = true);

        /// computes a discrete transition. Requires available time successors.
        void computeJumpSuccessors(const ReachTreeNode<Representation, LocationT> &task);

        /// getter for discrete jump successor sets
        REACHABILITY_RESULT computeBackwardReachability(const ReachTreeNode<Representation, LocationT> &task);

        REACHABILITY_RESULT computeTimePredecessors(const ReachTreeNode<Representation, LocationT> &task);

        void computeJumpPredecessors();

        const JumpSuccessors &getJumpSuccessorSets() const { return mJumpSuccessorSets; }

        const JumpSuccessors &getJumpPredecessorSets() const { return mJumpPredecessorSets; }

        /// getter for time successor sets
        const Flowpipe<Representation> &getFlowpipe() const { return mFlowpipe; }

        /// resets all stored items
        void reset() {
            mJumpSuccessorSets.clear();
            mJumpPredecessorSets.clear();
            mFlowpipe.clear();
        }

    private:
        void postProcessJumpSuccessors(const JumpSuccessors &guardSatisfyingSets);

        void reverseProcessJumpPredecessors(const JumpSuccessors &guardSatisfyingSets);

    protected:
        const Automaton &mHybridAutomaton;           ///< Reference to the singular automaton
        const FixedAnalysisParameters &mSettings;  ///< Reference to the used analysis settings
        JumpSuccessors mJumpSuccessorSets;           ///< Storage of computed jump successors
        JumpPredecessors mJumpPredecessorSets;       ///< Storage of computed jump predecessors
        Flowpipe<Representation> mFlowpipe;           ///< Storage of computed time successors
        std::size_t mSubspace;
    };

}  // namespace hypro

#include "SingularWorker.tpp"
