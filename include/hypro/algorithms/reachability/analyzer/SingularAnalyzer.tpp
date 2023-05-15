/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "SingularAnalyzer.h"

namespace hypro {

    template<typename Representation, typename Automaton>
    typename SingularAnalyzer<Representation, Automaton>::SingularResult
    SingularAnalyzer<Representation, Automaton>::run() {
        return forwardRun();
    }

    template<typename Representation, typename Automaton>
    typename SingularAnalyzer<Representation, Automaton>::SingularResult
    SingularAnalyzer<Representation, Automaton>::forwardRun() {
        SingularWorker<Representation, Automaton> worker{*mHybridAutomaton, mAnalysisSettings};
        DEBUG("hypro.reachability", "Start singular analysis.");
        while (!mWorkQueue.empty()) {
            ReachTreeNode<Representation, LocationT> *currentNode = mWorkQueue.front();
            mWorkQueue.pop_front();
            REACHABILITY_RESULT safetyResult;
            DEBUG("hypro.reachability", "Compute forward time successors in node " << *currentNode);
            if (currentNode->getDepth() < mAnalysisSettings.jumpDepth) {
                safetyResult = worker.computeForwardReachability(*currentNode);
            } else {
                safetyResult = worker.computeTimeSuccessors(*currentNode);
            }

            // only for plotting
            auto &flowpipe = currentNode->getFlowpipe();
            flowpipe.insert(flowpipe.begin(), worker.getFlowpipe().begin(), worker.getFlowpipe().end());
            if (!flowpipe.empty()) {
                DEBUG("hypro.reachability", "Resulting state set " << flowpipe.back());
            } else {
                DEBUG("hypro.reachability", "Resulting state set is empty");
            }

            if (safetyResult == REACHABILITY_RESULT::UNKNOWN) {
                return {Failure{currentNode}};
            }

            // create jump successor tasks
            for (const auto &[transition, stateSets]: worker.getJumpSuccessorSets()) {
                for (const auto jmpSucc: stateSets) {
                    // update reachTree
                    // time is not considered in singular analysis so we store a dummy
                    auto &childNode = currentNode->addChild(jmpSucc, carl::Interval<SegmentInd>(0, 0), transition);
                    DEBUG("hypro.reachability", "Added jump successor node " << childNode);

                    // create Task
                    mWorkQueue.push_back(&childNode);
                }
            }
            // reset worker for next task
            worker.reset();
        }

        return {VerificationSuccess{}};
    }

}  // namespace hypro
