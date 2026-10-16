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

    template<typename State, typename Automaton>
    REACHABILITY_RESULT RectangularAnalyzer<State, Automaton>::run() {
        // create reachTree if not already present
        if (mReachTree.empty()) {
            mReachTree = makeRoots<State, Automaton>(*mHybridAutomaton);
        }
        // initialize queue
        for (auto &rtNode: mReachTree) {
            mWorkQueue.push(&rtNode);
        }
        DEBUG("hypro.reachability.rectangular", "Added " << mWorkQueue.size() << " initial states to the work queue");

        if (mAnalysisSettings.strategy().front().useMultithreading) {
            mIdle = std::vector(mNumThreads, true);
            std::mutex resultMutex;
            REACHABILITY_RESULT res{REACHABILITY_RESULT::SAFE};
            for (int i = 0; i < mNumThreads; i++) {
                mThreads.push_back(std::thread([this, i, &resultMutex, &res]() {
                    RectangularWorker<State, Automaton> worker{*mHybridAutomaton, mAnalysisSettings};
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

                        const bool unsafe = result != REACHABILITY_RESULT::SAFE;
                        if (unsafe) {
                            {
                                std::lock_guard<std::mutex> lock{resultMutex};
                                res = result;
                            }
                            // before the notification below, so that the main thread sees it when it wakes up
                            mTerminate = true;
                        }

                        {
                            std::unique_lock<std::mutex> idleLock{mIdleWorkerMutex};
                            mIdle[i] = true;
                        }
                        // Notify while holding mThreadPoolMutex, the mutex the main thread waits with: otherwise the
                        // notification can fall between its check of the predicate and its wait, and is lost, so
                        // that it waits forever while all workers wait for an empty queue.
                        {
                            std::lock_guard<std::mutex> poolLock{mThreadPoolMutex};
                            mAllIdle.notify_all();
                        }

                        if (unsafe) {
                            break;
                        }
                    }
                }));
            }
            // busy wait?
            {
                std::unique_lock<std::mutex> lock{mThreadPoolMutex};
                // The predicate below reads mWorkQueue and mIdle, which are otherwise only ever
                // touched while holding mQueueMutex / mIdleWorkerMutex respectively (see the worker
                // lambda above). mThreadPoolMutex (held here by `lock`, required by
                // condition_variable::wait) protects neither of them, so reading them without also
                // taking their own mutexes here is a genuine data race with the concurrently-running
                // worker threads (confirmed via ThreadSanitizer: concurrent std::deque::empty() vs.
                // pop_front()/push_back(), and concurrent std::vector<bool> element read vs. write on
                // mIdle) -- not just a theoretical one. Taking mQueueMutex/mIdleWorkerMutex here is
                // deadlock-safe since no other code path ever holds mThreadPoolMutex while acquiring
                // them.
                mAllIdle.wait(lock, [this]() {
                    if (mTerminate) {
                        return true;
                    }
                    bool queueEmpty;
                    {
                        std::unique_lock<std::mutex> queueLock(mQueueMutex);
                        queueEmpty = mWorkQueue.empty();
                    }
                    if (!queueEmpty) {
                        return false;
                    }
                    std::unique_lock<std::mutex> idleLock(mIdleWorkerMutex);
                    return std::all_of(std::begin(mIdle), std::end(mIdle), [](bool in) { return in; });
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

    template<typename State, typename Automaton>
    REACHABILITY_RESULT RectangularAnalyzer<State, Automaton>::forwardRun() {
        DEBUG("hypro.reachability.rectangular", "Start forward analysis");

        RectangularWorker<State, Automaton> worker{*mHybridAutomaton, mAnalysisSettings};
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

    template<typename State, typename Automaton>
    REACHABILITY_RESULT
    RectangularAnalyzer<State, Automaton>::processNode(RectangularWorker<State, Automaton> &worker,
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
    	
    	bool goalReached = false;
    	if (mSpecs.has_value()) {
    		assert(mStochasticTransitions.has_value());
    		const Flowpipe<State>& flowpipe = worker.getFlowpipe();
    		const State& state = *( flowpipe.begin() );
    		const Location<Number>* location = node->getLocation();

    		for (const auto& spec : mSpecs.value()) {
    			const Location<Number>* _loc = spec.first;
    			if (_loc == nullptr || _loc == location) {
    				const hypro::Condition<Number>& _constraints = spec.second;
					if (_constraints.isTrue()) {
						goalReached = true;
						break;
					}
    				auto [isEmpty, states] = state.satisfiesHalfspaces(_constraints.getMatrix(), _constraints.getVector());
    				if (isEmpty != hypro::CONTAINMENT::NO) {
    					goalReached = true;
    				}
    			}
    		}

    	}

        // create jump successor tasks
        for (const auto &transitionStatesPair: worker.getJumpSuccessorSets()) {
        	// Opt-in cycle-group filter (mTransitionCycleGroup/mMaxCycleGroupRepetitions, both
        	// std::nullopt by default -- no-op for every caller that doesn't set them). Decided once
        	// per transitionStatesPair since every jmpSucc sharing this transition shares the same
        	// group id and the same ancestor path, so the skip/keep decision is identical for all of
        	// them. node->getTreePath()/getTransition() only read already-finalized ancestor nodes
        	// (a node's ancestors are fully built, via addChild below, before any descendant is ever
        	// enqueued), so this is safe to call here even when processNode runs concurrently across
        	// worker threads under UseMultithreading -- no additional locking needed.
        	//
        	// This intentionally counts only plain root-to-node-path occurrences of the transition's
        	// group, unlike the authoritative post-hoc pass (librealyst::recursivelyConvertSubtreeLimitCycles)
        	// which also folds in sibling transitions at the same branch point and an extra
        	// exactly-at-the-boundary exception -- both of which can only ever *shrink* that pass's
        	// keep-set relative to plain path counting. So this filter's keep-set is always a
        	// superset of the post-hoc pass's keep-set: it can never prune a branch the post-hoc pass
        	// would have kept (safe), it just may leave a few extra branches for the post-hoc pass
        	// (still run unconditionally downstream) to trim afterward, same as before this filter
        	// existed. mTransitionCycleLimit lets the caller replace the bound per transition by the exact one of
        	// that pass, so that the search skips exactly the branches it would prune.
        	bool skipDueToCycleLimit = false;
        	if (mTransitionCycleGroup.has_value() && mMaxCycleGroupRepetitions.has_value()) {
        		auto groupIt = mTransitionCycleGroup->find(transitionStatesPair.first);
        		if (groupIt != mTransitionCycleGroup->end()) {
        			std::size_t occurrences = 1;  // this prospective occurrence
        			for (const auto *ancestor : node->getTreePath()) {
        				const auto *ancestorTransition = ancestor->getTransition();
        				if (ancestorTransition == nullptr) continue;
        				auto ancestorGroupIt = mTransitionCycleGroup->find(ancestorTransition);
        				if (ancestorGroupIt != mTransitionCycleGroup->end() && ancestorGroupIt->second == groupIt->second) {
        					++occurrences;
        				}
        			}
        			std::size_t limit = mMaxCycleGroupRepetitions.value() + 1;
        			if (mTransitionCycleLimit.has_value()) {
        				auto limitIt = mTransitionCycleLimit->find(transitionStatesPair.first);
        				if (limitIt != mTransitionCycleLimit->end()) limit = limitIt->second;
        			}
        			skipDueToCycleLimit = occurrences > limit;
        		}
        	}
        	if (skipDueToCycleLimit) {
        		continue;
        	}
        	// Opt-in path filter (mAllowedPaths): only the allowed transition sequences are expanded.
        	if (mAllowedPaths.has_value()) {
        		std::vector<const hypro::Transition<hypro::Location<Number>>*> path;
        		const auto treePath = node->getTreePath();	// from node to (excluding) the root
        		for (auto it = treePath.rbegin(); it != treePath.rend(); ++it) {
        			if ((*it)->getTransition() != nullptr) path.push_back((*it)->getTransition());
        		}
        		path.push_back(transitionStatesPair.first);
        		if (mAllowedPaths->count(path) == 0) {
        			continue;
        		}
        	}

        	//TODO wieso kann eine transition zu mehreren nachfolge zuständen führen?
        	if (goalReached && mStochasticTransitions.has_value()) {
        		if (mStochasticTransitions.value().find(transitionStatesPair.first) != mStochasticTransitions.value().end()) {
        			assert(transitionStatesPair.second.size() == 1);
        			auto &childNode = node->addChild(transitionStatesPair.second.front(), carl::Interval<SegmentInd>(0, 0), transitionStatesPair.first);
        			assert(childNode.getDepth() == node->getDepth() + 1);

        			// create Task
        			addToQueue(&childNode);
        		}
        	} else {
        		for (const auto jmpSucc: transitionStatesPair.second) {
        			// update reachTree
        			// time is not considered in rectangular analysis so we store a dummy
        			auto &childNode = node->addChild(jmpSucc, carl::Interval<SegmentInd>(0, 0), transitionStatesPair.first);
        			assert(childNode.getDepth() == node->getDepth() + 1);

        			// create Task
        			addToQueue(&childNode);
        		}
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
