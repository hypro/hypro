#pragma once

#include "../../../datastructures/reachability/Flowpipe.h"
#include "../../../datastructures/reachability/Settings.h"
#include "../../../util/logging/Logger.h"
#include "../../../util/plotting/PlotData.h"
#include "../handlers/firstSegmentHandlers/ltiFirstSegmentHandler.h"
#include "../handlers/guardHandlers/ltiGuardHandler.h"
#include "../handlers/invariantHandlers/ltiInvariantHandler.h"
#include "../handlers/jumpHandlers/ltiJumpHandler.h"
#include "../handlers/timeEvolutionHandlers/ltiTimeEvolutionHandler.h"

#include <vector>

namespace hypro {

template <typename State>
class LTIWorker {
  private:
	using Number = typename State::NumberType;
	using JumpSuccessors = typename ltiGuardHandler<State>::TransitionStatesMap;

  public:
	LTIWorker( const HybridAutomaton<Number>& ha, const Settings& settings )
		: mHybridAutomaton( ha )
		, mSettings( settings ) {}

	REACHABILITY_RESULT computeForwardReachability( const ReachTreeNode<State>& task );

	REACHABILITY_RESULT computeTimeSuccessors( const ReachTreeNode<State>& task );
	void computeJumpSuccessors();

	const JumpSuccessors& getJumpSuccessorSets() const { return mJumpSuccessorSets; }
	const Flowpipe<State>& getFlowpipe() const { return mFlowpipe; }

  private:
	void postProcessJumpSuccessors( const JumpSuccessors& guardSatisfyingSets );

	bool requireTimeSuccessorComputation( std::size_t segmentCount ) const { return segmentCount <= mSettings.localTimeHorizon / mSettings.strategy.front().timeStep; }

  protected:
	const HybridAutomaton<Number>& mHybridAutomaton;
	const Settings& mSettings;
	JumpSuccessors mJumpSuccessorSets;
	Flowpipe<State> mFlowpipe;
};

}  // namespace hypro

#include "LTIWorker.tpp"
