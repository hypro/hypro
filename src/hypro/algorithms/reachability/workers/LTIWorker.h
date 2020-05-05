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
	using TaskType = std::shared_ptr<Task<State>>;
	using JumpSuccessors = typename ltiGuardHandler::TransitionStatesMap;

  public:
	REACHABILITY_RESULT computeForwardReachability( const TaskType& task );

	REACHABILITY_RESULT computeTimeSuccessors();
	void computeJumpSuccessors();

	const JumpSuccessors& getJumpSuccessorSets() const { return mJumpSuccessorSets; }
	const Flowpipe<State>& getFlowpipe() const { return mFlowpipe; }

  private:
	void postProcessJumpSuccessors( const JumpSuccessors& guardSatisfyingSets );

	bool requireTimeSuccessorComputation( std::size_t segmentCount ) const { return segmentCount <= SettingsProvider::getInstance().getLocalTimeHorizon() / SettingsProvider::getInstance().getTimeStepSize(); }

  protected:
	JumpSuccessors mJumpSuccessorSets;
	Flowpipe<State> mFlowpipe;
};

}  // namespace hypro

#include "LTIWorker.tpp"
