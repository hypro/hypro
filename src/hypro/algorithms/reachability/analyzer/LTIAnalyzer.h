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
	LTIAnalyzer( const HybridAutomaton<Number>& ha, const Settings& setting )
		: mHybridAutomaton( ha )
		, mAnalysisSettings( setting )
		, mReachTree( new ReachTreeNode<State> ) {
	}

	REACHABILITY_RESULT run();

	const std::vector<Flowpipe<State>>& getFlowpipes() const { return mFlowpipes; }

  protected:
	std::queue<ReachTreeNode<State>*> mWorkQueue;
	std::vector<Flowpipe<State>> mFlowpipes;
	HybridAutomaton<Number> mHybridAutomaton;
	Settings mAnalysisSettings;
	ReachTree<State> mReachTree;
	std::vector<State> mFirstStates;  ///< Store first segments for fixed-point detection
};

}  // namespace hypro

#include "LTIAnalyzer.tpp"
