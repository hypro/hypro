/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../HybridAutomaton/Path.h"
#include "ReachTreeNodev2.h"

namespace hypro {

/**
 * @brief      Struct holding all currently required information for backtracking
 * @details    Its contents currently are the path (starting and including the current node) and the
 * 			   desired refinementLevel. The Bt-Path also contains the location in which the bad state
 * 			   was hit.
 */
    template<typename Number>
    struct TBacktrackingInfo {
        /**
         * Holds the whole Path to the root. Note that the actual(current) path starts at btPath.at(currentBTPosition).
         */
        Path<Number, tNumber> btPath;
        /**
         * Index referencing the current position. Note that we cannot simply truncate the path whenever a part of it has
         * been refined as we require the full path to determine possible prefixes for other BT-runs.
         */
        unsigned currentBTPosition = 0;
        /**
         * The desired level (strategy index) of this BT-run.
         */
        unsigned btLevel = 0;

        unsigned timingLevel = 0;  /// required for the correct entry node in the timing tree

        TBacktrackingInfo<Number>()
                : btPath(), currentBTPosition(0), btLevel(0) {}

        friend bool operator==(const TBacktrackingInfo &lhs, const TBacktrackingInfo &rhs) {
            return (lhs.currentBTPosition == rhs.currentBTPosition && lhs.btLevel == rhs.btLevel &&
                    lhs.btPath == rhs.btPath);
        }
    };

    template<typename State>
    struct Task {
        using Number = typename State::NumberType;

        ReachTreeNode <State> *treeNode = nullptr;
        TBacktrackingInfo<Number> btInfo = TBacktrackingInfo<Number>();

        Task(ReachTreeNode <State> *node)
                : treeNode(node), btInfo() {
            assert(btInfo.btPath.size() <= 0 || btInfo.btLevel > 0);
        }

        Task(ReachTreeNode <State> *node, const TBacktrackingInfo<Number> &btI)
                : treeNode(node), btInfo(btI) {}

        const State &getInitialStateSet() {
            assert(treeNode != nullptr);
            return treeNode->getState();
        }

        friend std::ostream &operator<<(std::ostream &out, const Task<State> &task) {
            // out << *task.treeNode;
            out << task.treeNode;
            return out;
        }

        friend bool operator==(const Task<State> &lhs, const Task<State> &rhs) {
            return (lhs.treeNode == rhs.treeNode && lhs.btInfo == rhs.btInfo);
        }

        friend bool operator!=(const Task<State> &lhs, const Task<State> &rhs) {
            return !(lhs == rhs);
        }

        friend bool operator<(const Task<State> &lhs, const Task<State> &rhs) {
            DEBUG("hypro.workQueue", "Compare " << lhs << " and " << rhs << ": ");
            if (lhs == rhs) {     // strict weak ordering requires this, thus rhs is inserted before lhs.
                // however, this should never happen(?)
                assert(false);
                DEBUG("hypro.workQueue", "Should not happen.");
                return false;
            }

            if (lhs.btInfo.btPath.size() > 0 && rhs.btInfo.btPath.size() > 0) {
                // check whether there are common nodes in the btPath.
                if (lhs.btInfo.btPath.sharesPrefix(rhs.btInfo.btPath)) {
                    // we simply don't care but can return an arbitrary value. keep strict ordering by btLevel
                    DEBUG("hypro.workQueue", (lhs.btInfo.btLevel > rhs.btInfo.btLevel));
                    return lhs.btInfo.btLevel > rhs.btInfo.btLevel;
                }

                // TODO we have a node in common - how do we handle this?
            }

            if (lhs.btInfo.btLevel == rhs.btInfo.btLevel && lhs.btInfo.btLevel != 0) {
                DEBUG("hypro.workQueue", (lhs.btInfo.btPath.size() > rhs.btInfo.btPath.size()));
                return lhs.btInfo.btPath.size() > rhs.btInfo.btPath.size();     // insert longer path first
            }

            DEBUG("hypro.workQueue", (lhs.btInfo.btLevel > rhs.btInfo.btLevel));

            if (lhs.btInfo.btLevel == rhs.btInfo.btLevel && lhs.btInfo.btLevel == 0) {
                return lhs.treeNode->getDepth() < rhs.treeNode->getDepth();
            }

            return lhs.btInfo.btLevel > rhs.btInfo.btLevel;     // insert higher btLevel first
        }
    };

    template<typename Number, typename State>
    bool operator==(const std::shared_ptr<Task<State>> &lhs, const std::shared_ptr<Task<State>> &rhs) {
        return *lhs == *rhs;
    }

}  // namespace hypro
