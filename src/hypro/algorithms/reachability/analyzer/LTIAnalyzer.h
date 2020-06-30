#pragma once
#include "../../../datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../../datastructures/reachability/Flowpipe.h"
#include "../../../types.h"
#include "../workers/LTIWorker.h"
#include "datastructures/reachability/ReachTreev2.h"

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
		, mReachTree( ReachTreeNode<State>{ nullptr, nullptr, State() } ) {
	}

	REACHABILITY_RESULT run();

	const std::list<std::vector<State>>& getFlowpipes() const { return mFlowpipes; }

  protected:
	std::queue<ReachTreeNode<State>*> mWorkQueue;
	std::list<std::vector<State>> mFlowpipes;
	HybridAutomaton<Number> mHybridAutomaton;
	Settings mAnalysisSettings;
	ReachTreeNode<State> mReachTree;  /// TODO: implement via several roots
	std::vector<State> mFirstStates;  ///< Store first segments for fixed-point detection
};

}  // namespace hypro

#include "LTIAnalyzer.tpp"
