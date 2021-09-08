#pragma once
#include "../../../datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../../datastructures/reachability/Flowpipe.h"
#include "../../../datastructures/reachability/ReachTreev2.h"
#include "../../../datastructures/reachability/TreeTraversal.h"
#include "../../../types.h"
#include "../workers/LTISetMinusWorker.h"
#include "./ReturnTypes.h"

#include <atomic>
#include <mutex>
#include <queue>

namespace hypro {

// indicates that the lti analysis succeeded, i.e. no
struct LTISetMinusSuccess {};

template <typename State>
class LTISetMinusAnalyzer {
	using Number = typename State::NumberType;

  public:
	using LTISetMinusResult = AnalysisResult<LTISetMinusSuccess, Failure<State>>;

	LTISetMinusAnalyzer( HybridAutomaton<Number> const& ha,
				 FixedAnalysisParameters const& fixedParameters,
				 AnalysisParameters const& parameters,
				 std::vector<ReachTreeNode<State>>& roots )
		: mHybridAutomaton( &ha )
		, mFixedParameters( fixedParameters )
		, mParameters( parameters )
		, mRoots( roots ) {
		for ( auto& root : roots ) {
			mWorkQueue.push_front( &root );
		}
	}

	LTISetMinusResult run();
	void addToQueue( ReachTreeNode<State>* node ) { mWorkQueue.push_front( node ); }

  private:
	bool detectFixedPoint( const State& valuationSet, const Location<Number>* loc );

  protected:
	std::deque<ReachTreeNode<State>*> mWorkQueue;	  ///< queue which holds tasks for time successor computation
	HybridAutomaton<Number> const* mHybridAutomaton;  ///< pointer to the hybrid automaton
	FixedAnalysisParameters mFixedParameters;		  ///< parameters which are fixed for the analysis
	AnalysisParameters mParameters;					  ///< parameters which are specific for this call (relevant for CEGAR-refinement)
	std::vector<ReachTreeNode<State>>& mRoots;		  ///< reference to the search tree, required for fixed-point detection
};

}  // namespace hypro

#include "LTISetMinusAnalyzer.tpp"
