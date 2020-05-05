#pragma once

#include "../../../datastructures/HybridAutomaton/decomposition/DecisionEntity.h"
#include "../../../datastructures/reachability/Settings.h"
#include "../../../datastructures/reachability/Task.h"
#include "../../../datastructures/reachability/workQueue/WorkQueue.h"
#include "../../../util/logging/Logger.h"
#include "../../../util/plotting/PlotData.h"
#include "../contexts/ContextFactory.h"
#include "../contexts/Exceptions.h"
#include "../contexts/IContext.h"
#include "IWorker.h"

#include <vector>

namespace hypro {

template <typename State>
class LTIWorker {
  private:
	using Number = typename State::NumberType;
	using JumpSuccessors = typename ltiGuardHandler<State>::TransitionStatesMap;

  public:
	REACHABILITY_RESULT computeForwardReachability( const ReachTreeNode<State>& task );

	REACHABILITY_RESULT computeTimeSuccessors( const ReachTreeNode<State>& task );
	void computeJumpSuccessors();

	const JumpSuccessors& getJumpSuccessorSets() const { return mJumpSuccessorSets; }
	const Flowpipe<State>& getFlowpipe() const { return mFlowpipe; }

  private:
	void postProcessJumpSuccessors( const JumpSuccessors& guardSatisfyingSets );

	bool requireTimeSuccessorComputation( std::size_t segmentCount ) const { return segmentCount <= SettingsProvider<State>::getInstance().getLocalTimeHorizon() / SettingsProvider<State>::getInstance().getTimeStepSize(); }

  protected:
	JumpSuccessors mJumpSuccessorSets;
	Flowpipe<State> mFlowpipe;
};

}  // namespace hypro

#include "LTIWorker.tpp"
