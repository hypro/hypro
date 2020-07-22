#pragma once
#include "../../../datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../../datastructures/reachability/Flowpipe.h"
#include "../../../types.h"
#include "../workers/LTIWorker.h"
#include "datastructures/reachability/ReachTreev2.h"
#include "./ReturnTypes.h"

#include <queue>

namespace hypro {

// indicates that the lti analysis succeeded, i.e. no
struct LTISuccess {};

template <typename State>
class LTIAnalyzer {
	using Number = typename State::NumberType;

  public:
	using LTIResult = AnalysisResult<LTISuccess, Failure<State>>;

	LTIAnalyzer( HybridAutomaton<Number> const& ha, Settings const& setting, std::vector<ReachTreeNode<State>>& roots )
		: mHybridAutomaton( ha )
		, mAnalysisSettings( setting ) {
		for ( auto& root : roots ) {
			mWorkQueue.push_front( &root );
		}
	}

	LTIResult run();
	void addToQueue( ReachTreeNode<State>* node ) { mWorkQueue.push_front( node ); }

  protected:
	std::deque<ReachTreeNode<State>*> mWorkQueue;
	HybridAutomaton<Number> mHybridAutomaton;
	Settings mAnalysisSettings;
};

}  // namespace hypro

#include "LTIAnalyzer.tpp"
