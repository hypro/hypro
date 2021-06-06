#pragma once
#include "../../../datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../../datastructures/reachability/Flowpipe.h"
#include "../../../datastructures/reachability/ReachTreev2.h"
#include "../../../types.h"
#include "../workers/LTIWorker.h"
#include "./ReturnTypes.h"

#include <atomic>
#include <mutex>
#include <queue>

namespace hypro {

// indicates that the lti analysis succeeded, i.e. no
struct LTISuccess {};

template <typename State>
class LTIAnalyzer {
	using Number = typename State::NumberType;

  public:
	using LTIResult = AnalysisResult<LTISuccess, Failure<State>>;

	LTIAnalyzer( HybridAutomaton<Number> const& ha,
				 FixedAnalysisParameters const& fixedParameters,
				 AnalysisParameters const& parameters,
				 std::vector<ReachTreeNode<State>>& roots )
		: mHybridAutomaton( &ha )
		, mFixedParameters( fixedParameters )
		, mParameters( parameters ) {
		for ( auto& root : roots ) {
			mWorkQueue.push_front( &root );
		}
	}

	LTIResult run();
	void addToQueue( ReachTreeNode<State>* node ) { mWorkQueue.push_front( node ); }

  protected:
	std::deque<ReachTreeNode<State>*> mWorkQueue;	  /// queue which holds tasks for time successor computation
	HybridAutomaton<Number> const* mHybridAutomaton;  /// pointer to the hybrid automaton
	FixedAnalysisParameters mFixedParameters;		  /// parameters which are fixed for the analysis
	AnalysisParameters mParameters;					  /// parameters which are specific for this call (relevant for CEGAR-refinement)
};

}  // namespace hypro

#include "LTIAnalyzer.tpp"
