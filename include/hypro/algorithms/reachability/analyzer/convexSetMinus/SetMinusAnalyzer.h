/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once


#include "../../../datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../../datastructures/reachability/Flowpipe.h"
#include "../../../datastructures/reachability/ReachTreev2.h"
#include "../../../datastructures/reachability/ReachTreev2Heuristics.h"
#include "../../../datastructures/reachability/TreeTraversal.h"
#include "../../../types.h"
#include "../ReachabilityCallbacks.h"
#include "../fixedPointDetection.h"
#include "../workers/LTIWorker.h"
#include "./ReturnTypes.h"


#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>

namespace hypro {

// indicates that the lti analysis succeeded, i.e. no
    struct LTISuccess {
    };

/**
 * Analyzer for linear hybrid automata
 * @tparam State state set representation type
 * @tparam Automaton automaton type
 * @tparam Heuristics used search heuristics
 * @tparam Multithreading enable/disable multithreading
 */
    template<typename State, typename Automaton, typename Heuristics = DepthFirst<State, typename Automaton::LocationType>, typename Multithreading = NoMultithreading>
    class LTIAnalyzer {
        using Number = typename State::NumberType;
        using LocationT = typename Automaton::LocationType;
        using TransitionT = Transition<LocationT>;

    public:
        using LTIResult = AnalysisResult<LTISuccess, Failure<State, LocationT>>;

        LTIAnalyzer(Automaton const &ha,
                    FixedAnalysisParameters const &fixedParameters,
                    AnalysisParameters const &parameters,
                    std::vector<ReachTreeNode<State, LocationT>> &roots)
                : mHybridAutomaton(&ha), mFixedParameters(fixedParameters), mParameters(parameters), mRoots(roots) {
            for (auto &root: roots) {
                addToQueue(&root);
            }
        }

        /// move constructor
        LTIAnalyzer(LTIAnalyzer &&other)
                : mWorkQueue(), mHybridAutomaton(other.mHybridAutomaton),
                  mFixedParameters(std::move(other.mFixedParameters)), mParameters(std::move(other.mParameters)),
                  mRoots(other.mRoots), mNumThreads(), mThreads(), mIdle(), mQueueMutex(), mThreadPoolMutex(),
                  mQueueNonEmpty(), mTerminate(), mStopped() {
        }

        ~LTIAnalyzer() {
            if (std::is_same_v<Multithreading, UseMultithreading> && !mStopped) {
                shutdown();
            }
        }

        LTIResult run();

        void addToQueue(ReachTreeNode<State, LocationT> *node) {
            if (std::is_same<Multithreading, UseMultithreading>::value) {
                {
                    std::unique_lock<std::mutex> lock(mQueueMutex);
                    mWorkQueue.push(node);
                }
                mQueueNonEmpty.notify_one();
            } else {
                mWorkQueue.push(node);
            }
        }

        ReachTreeNode<State, LocationT> *getNodeFromQueue() {
            auto res = mWorkQueue.top();
            mWorkQueue.pop();
            return res;
        }

        void shutdown() {
            {
                std::unique_lock<std::mutex> lock(mThreadPoolMutex);
                mTerminate = true;    // use this flag in condition.wait
            }

            mQueueNonEmpty.notify_all();  // wake up all threads.

            // Join all threads.
            for (std::thread &th: mThreads) {
                th.join();
            }

            mThreads.clear();
            mStopped = true;
        }

        void setCallbacks(const ReachabilityCallbacks<State, LocationT> &callbacks) { mCallbacks = callbacks; };

    private:
        LTIResult run_impl();

        LTIResult processNode(LTIWorker<State, Automaton> &worker, ReachTreeNode<State, LocationT> *node,
                              TimeTransformationCache<LocationT> &transformationCache);

        bool detectFixedPoint(ReachTreeNode<State, LocationT> &node);

    protected:
        std::priority_queue<ReachTreeNode<State, LocationT> *, std::vector<ReachTreeNode<State, LocationT> *>, Heuristics> mWorkQueue;  ///< queue which holds tasks for time successor computation
        Automaton const *mHybridAutomaton;                                                                                              ///< pointer to the hybrid automaton
        FixedAnalysisParameters mFixedParameters;                                                                                      ///< parameters which are fixed for the analysis
        AnalysisParameters mParameters;                                                                                                  ///< parameters which are specific for this call (relevant for CEGAR-refinement)
        std::vector<ReachTreeNode<State, LocationT>> &mRoots;                                                                          ///< reference to the search tree, required for fixed-point detection
        int mNumThreads = std::thread::hardware_concurrency();                                                                          ///< number of used threads
        std::vector<std::thread> mThreads;                                                                                              ///< vector of threads
        std::vector<bool> mIdle;                                                                                                      ///< vector of idle threads
        std::mutex mQueueMutex;                                                                                                          ///< mutex to access the queue
        std::mutex mThreadPoolMutex;                                                                                                  ///< mutex for the thread pool itself
        std::condition_variable mQueueNonEmpty;                                                                                          ///< notification variable to indicate the queue is nonempty
        std::atomic<bool> mTerminate = false;                                                                                          ///< indicates termination request
        std::atomic<bool> mStopped = false;                                                                                              ///< indicator, whether shutdown was already invoked
        std::mutex mIdleWorkerMutex;                                                                                                  ///< mutex to access the idle-flag array
        std::condition_variable mAllIdle;                                                                                              ///< notification variable to trigger shutdown of the threadpool
        ReachabilityCallbacks<State, LocationT> mCallbacks;                                                                              ///< collection of callback functions
    };

}  // namespace hypro

#include "SetMinusAnalyzer.tpp"
