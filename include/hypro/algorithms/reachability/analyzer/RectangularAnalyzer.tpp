/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "RectangularAnalyzer.h"

namespace hypro {

    template<typename State, typename Automaton, typename Multithreading>
    REACHABILITY_RESULT RectangularAnalyzer<State, Automaton, Multithreading>::run() {
        // create reachTree if not already present
        if (mReachTree.empty()) {
            mReachTree = makeRoots<State>(mHybridAutomaton);
        }
        // initialize queue
        for (auto &rtNode: mReachTree) {
            mWorkQueue.push(&rtNode);
        }
        DEBUG("hypro.reachability.rectangular", "Added " << mWorkQueue.size() << " initial states to the work queue");

        if (std::is_same_v<Multithreading, UseMultithreading>) {
            mIdle = std::vector(mNumThreads, true);
            std::mutex resultMutex;
            REACHABILITY_RESULT res{REACHABILITY_RESULT::SAFE};
            for (int i = 0; i < mNumThreads; i++) {
                mThreads.push_back(std::thread([this, i, &resultMutex, &res]() {
                    RectangularWorker<State, Automaton> worker{mHybridAutomaton, mAnalysisSettings};
                    ReachTreeNode<State, LocationT> *currentNode;
                    while (!mTerminate) {
                        {
                            std::unique_lock<std::mutex> lock(mQueueMutex);

                            mQueueNonEmpty.wait(lock, [this]() {
                                // TODO I am not sure, whether we need to lock here to access the queue
                                return !mWorkQueue.empty() || mTerminate;
                            });
                            {
                                if (mTerminate) {
                                    break;
                                }
                                // TODO I do not think we need the idle lock, since we already have the queue lock
                                std::unique_lock<std::mutex> idleLock{mIdleWorkerMutex};
                                mIdle[i] = false;
                            }
                            currentNode = getNodeFromQueue();
                            DEBUG("hypro.reachability",
                                  "Processing node @" << currentNode << " with path " << currentNode->getPath());
                        }

                        auto result = processNode(worker, currentNode);

                        {
                            std::unique_lock<std::mutex> idleLock{mIdleWorkerMutex};
                            mIdle[i] = true;
                            mAllIdle.notify_all();
                        }

                        if (result != REACHABILITY_RESULT::SAFE) {
                            mTerminate = true;
                            {
                                std::lock_guard<std::mutex> lock{resultMutex};
                                res = result;
                            }
                            break;
                        }
                    }
                }));
            }
            // busy wait?
            {
                std::unique_lock<std::mutex> lock{mThreadPoolMutex};
                mAllIdle.wait(lock, [this]() {
                    return mTerminate || (mWorkQueue.empty() &&
                                          std::all_of(std::begin(mIdle), std::end(mIdle), [](bool in) { return in; }));
                });
            }
            shutdown();
            return res;
        } else {
            REACHABILITY_RESULT safetyResult;
            if (mAnalysisSettings.strategy().front().reachability_analysis_method == REACH_SETTING::FORWARD) {
                // forward analysis
                safetyResult = forwardRun();
            }
            // else {
            //	// backward analysis
            //	safetyResult = backwardRun();
            //}

            return safetyResult;
        }
    }

    template<typename State, typename Automaton, typename Multithreading>
    REACHABILITY_RESULT RectangularAnalyzer<State, Automaton, Multithreading>::forwardRun() {
        DEBUG("hypro.reachability.rectangular", "Start forward analysis");

        RectangularWorker<State, Automaton> worker{mHybridAutomaton, mAnalysisSettings};
        while (!mWorkQueue.empty()) {
            auto *currentNode = getNodeFromQueue();
            DEBUG("hypro.reachability",
                  "Process node (@" << currentNode << ") with location " << currentNode->getLocation()->getName()
                                    << " with path " << currentNode->getTreePath());
            auto result = processNode(worker, currentNode);
            if (result != REACHABILITY_RESULT::SAFE) {
                DEBUG("hypro.reachability", "End Rectangular Reachability Analysis.");
                return result;
            }
        }

        return REACHABILITY_RESULT::SAFE;
    }

    template<typename State, typename Automaton, typename Multithreading>
    REACHABILITY_RESULT
    RectangularAnalyzer<State, Automaton, Multithreading>::processNode(RectangularWorker<State, Automaton> &worker,
                                                                       ReachTreeNode<State, LocationT> *node) {
        REACHABILITY_RESULT safetyResult;
        TRACE("hypro.reachability.rectangular", "Analyze node at depth " << node->getDepth());

        // reset worker state
        worker.clear();
        // in case the jump depth is reached, only compute time successors
        if (node->getDepth() < mAnalysisSettings.fixedParameters().jumpDepth) {
            safetyResult = worker.computeForwardReachability(*node);
        } else {
            safetyResult = worker.computeTimeSuccessors(*node);
        }

        if (safetyResult != REACHABILITY_RESULT::SAFE) {
            return safetyResult;
        }

        // create jump successor tasks
        for (const auto &transitionStatesPair: worker.getJumpSuccessorSets()) {
            for (const auto jmpSucc: transitionStatesPair.second) {
                // update reachTree
                // time is not considered in rectangular analysis so we store a dummy
                auto &childNode = node->addChild(jmpSucc, carl::Interval<SegmentInd>(0, 0), transitionStatesPair.first);
                assert(childNode.getDepth() == node->getDepth() + 1);

                // create Task
                addToQueue(&childNode);
            }
        }
        return REACHABILITY_RESULT::SAFE;
    }

/*
template <typename State, typename Automaton, typename Multithreading>
REACHABILITY_RESULT RectangularAnalyzer<State,Automaton,Multithreading>::backwardRun() {
	// initialize queue
	for ( auto& [location, condition] : mHybridAutomaton.getLocalBadStates() ) {
		// create local bad state
		State badState{ condition.getMatrix(), condition.getVector() };

		// create node from state
		auto badNode{ ReachTreeNode<State>( location, badState, carl::Interval<SegmentInd>( 0 ) ) };
		// add to reachTree
		mReachTree.emplace_back( std::move( badNode ) );
		// add to queue
		mWorkQueue.push( &mReachTree.back() );
	}

	for ( auto& condition : mHybridAutomaton.getGlobalBadStates() ) {
		if ( condition.getMatrix().rows() != 0 ) {
			for ( auto& location : mHybridAutomaton.getLocations() ) {
				// create global bad state
				State badState{ condition.getMatrix(), condition.getVector() };

				// create node from state
				auto badNode{ ReachTreeNode<State>( location, badState, carl::Interval<SegmentInd>( 0 ) ) };
				// add to reachTree
				mReachTree.emplace_back( std::move( badNode ) );
				// add to queue
				mWorkQueue.push( &mReachTree.back() );
			}
		}
	}

	while ( !mWorkQueue.empty() ) {
		RectangularWorker<State> worker{ mHybridAutomaton, mAnalysisSettings };
		ReachTreeNode<State>* currentNode = mWorkQueue.front();
		mWorkQueue.pop();
		REACHABILITY_RESULT safetyResult;

		if ( currentNode->getDepth() < mAnalysisSettings.fixedParameters().jumpDepth ) {
			safetyResult = worker.computeBackwardReachability( *currentNode );
		} else {
			safetyResult = worker.computeTimePredecessors( *currentNode );
		}

		// only for plotting
		mFlowpipes.emplace_back( worker.getFlowpipe() );

		if ( safetyResult == REACHABILITY_RESULT::UNKNOWN ) {
			return safetyResult;
		}

		// create jump predecessors tasks
		for ( const auto& transitionStatesPair : worker.getJumpPredecessorSets() ) {
			for ( const auto jmpPre : transitionStatesPair.second ) {
				// update reachTree

				//	auto* parentNode = new ReachTreeNode<State>{ jmpPre };
				//	parentNode->addChild( currentNode );
				//	currentNode->setParent( parentNode );
				//
				//	// update path (global time)
				//	currentNode->addTimeStepToPath( carl::Interval<tNumber>( jmpPre.getTimestamp().lower(), worker.//getFlowpipe().begin()->getTimestamp().upper() ) );
				//	currentNode->addTransitionToPath( transitionStatesPair.first, worker.getFlowpipe().begin()->getTimestamp//() );

				// Stefan: We have changed the code such that the tree grows from the bad states down instead of growing at the root upwards.
				auto& childNode = currentNode->addChild( jmpPre, carl::Interval<SegmentInd>( 0 ), transitionStatesPair.first );

				// create Task
				mWorkQueue.push( &childNode );
			}
		}
	}

	return REACHABILITY_RESULT::SAFE;
}
*/

}  // namespace hypro
