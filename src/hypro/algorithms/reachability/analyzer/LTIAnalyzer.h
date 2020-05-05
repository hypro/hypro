#pragma once
#include "../../../datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../../datastructures/reachability/workQueue/WorkQueue.h"
#include "../workers/LTIWorker.h"
#include "../../../types.h"

namespace hypro {

template <typename State>
class LTIAnalyzer {
	using TaskPtr = std::unique_ptr<Task<State>>;
	using Number = typename State::NumberType;

  public:
	LTIAnalyzer() = delete;
	LTIAnalyzer( const HybridAutomaton<Number>& ha, const Setting& setting )
		: mHybridAutomaton( ha )
		, mAnalysisSettings( setting )
		, mReachTree (new ReachTreeNode<State>) {
	}

	REACHABILITY_RESULT run();

  protected:
	WorkQueue<TaskPtr> mWorkQueue;
	std::vector<Flowpipe<State>> mFlowpipes;
	HybridAutomaton<Number> mHybridAutomaton;
	Setting mAnalysisSettings;
	ReachTree<State> mReachTree;
};

}  // namespace hypro

#include "LTIAnalyzer.tpp"
