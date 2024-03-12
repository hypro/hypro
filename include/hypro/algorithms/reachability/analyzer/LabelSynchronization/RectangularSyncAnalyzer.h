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
#include "../../../types.h"
#include "../workers/RectangularWorker.h"

#include <queue>

namespace hypro {

/**
 * @brief Class which implements a forward reachability analysis method for multiple rectangular automata with distinct variable sets with synchronization over labels
 * @details Requires the usage of a suitable state set representation, e.g., carlPolytope.
 * @tparam State state set representation type (must be polyhedral)
 * @tparam Automaton hybrid automaton type
 * @tparam Multithreading enable/disable multithreading
 */
template <typename State, typename Automaton, typename Multithreading = NoMultithreading>
class RectangularAnalyzer {
	static_assert( std::is_same<typename State::NumberType, typename Automaton::NumberType>() );
	using Number = typename State::NumberType;
	using LocationT = typename Automaton::LocationType;

  public:
	/// default constructor (deleted)
	RectangularAnalyzer() = delete;

	/// constructor from automaton and settings with additional reachTree
	RectangularAnalyzer( const Automaton& ha, const Settings& setting,
						 std::vector<ReachTreeNode<State, LocationT>>& roots )
		: mHybridAutomaton( ha )
		, mAnalysisSettings( setting )
		, mReachTree( roots ) {
	}

	/// main method for reachability analysis
	REACHABILITY_RESULT run();

	REACHABILITY_RESULT forwardRun();

	// REACHABILITY_RESULT backwardRun();

	void addToQueue( ReachTreeNode<State, LocationT>* node ) {
		if ( std::is_same_v<Multithreading, UseMultithreading> ) {
			{
				std::unique_lock<std::mutex> lock( mQueueMutex );
				mWorkQueue.push( node );
			}
			mQueueNonEmpty.notify_one();
		} else {
			mWorkQueue.push( node );
		}
	}

	ReachTreeNode<State, LocationT>* getNodeFromQueue() {
		auto* res = mWorkQueue.front();
		mWorkQueue.pop();
		return res;
	}

	void shutdown() {
		{
			std::unique_lock<std::mutex> lock( mThreadPoolMutex );
			mTerminate = true;	// use this flag in condition.wait
		}

		mQueueNonEmpty.notify_all();  // wake up all threads.

		// Join all threads.
		for ( std::thread& th : mThreads ) {
			th.join();
		}

		mThreads.clear();
		mStopped = true;
	}

  private:
	REACHABILITY_RESULT
	processNode( RectangularWorker<State, Automaton>& worker, ReachTreeNode<State, LocationT>* node );

  protected:
	std::queue<ReachTreeNode<State, LocationT>*> mWorkQueue;   ///< Queue holds all nodes that require processing
	HybridAutomaton<Number> mHybridAutomaton;				   ///< Automaton which is analyzed
	const Settings mAnalysisSettings;						   ///< Settings used for analysis
	std::vector<ReachTreeNode<State, LocationT>>& mReachTree;  ///< Forest of ReachTrees computed
	int mNumThreads = std::thread::hardware_concurrency();	   ///< number of used threads
	std::vector<std::thread> mThreads;						   ///< vector of threads
	std::vector<bool> mIdle;								   ///< vector of idle threads
	std::mutex mQueueMutex;									   ///< mutex to access the queue
	std::mutex mThreadPoolMutex;							   ///< mutex for the thread pool itself
	std::condition_variable mQueueNonEmpty;					   ///< notification variable to indicate the queue is nonempty
	std::atomic<bool> mTerminate = false;					   ///< indicates termination request
	std::atomic<bool> mStopped = false;						   ///< indicator, whether shutdown was already invoked
	std::mutex mIdleWorkerMutex;							   ///< mutex to access the idle-flag array
	std::condition_variable mAllIdle;						   ///< notification variable to trigger shutdown of the threadpool
};

}  // namespace hypro

#include "RectangularSyncAnalyzer.tpp"
