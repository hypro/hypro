#pragma once
#include "../../../datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../../types.h"
#include "../workers/LTIWorker.h"

#include <queue>

namespace hypro {

template <typename State>
class LTIAnalyzer {
	using Number = typename State::NumberType;

  public:
	LTIAnalyzer() = delete;
	LTIAnalyzer( const HybridAutomaton<Number>& ha, const Setting& setting )
		: mHybridAutomaton( ha )
		, mAnalysisSettings( setting )
		, mReachTree( new ReachTreeNode<State> ) {
	}

	REACHABILITY_RESULT run();

  protected:
	std::queue<ReachTreeNode<State>*> mWorkQueue;
	std::vector<Flowpipe<State>> mFlowpipes;
	HybridAutomaton<Number> mHybridAutomaton;
	Setting mAnalysisSettings;
	ReachTree<State> mReachTree;
};

}  // namespace hypro

#include "LTIAnalyzer.tpp"
