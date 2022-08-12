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
class ContextBasedReachabilityWorker : public IWorker<std::shared_ptr<Task<State>>, State> {
	using Number = typename State::NumberType;
	using TaskType = std::shared_ptr<Task<State>>;

  public:
	ContextBasedReachabilityWorker( const ReachabilitySettings& settings )
		: IWorker<std::shared_ptr<Task<State>>, State>( settings ) {
	}

	~ContextBasedReachabilityWorker() {
	}

	void processTask( const TaskType& t,
					  const Strategy<State>& strat,
					  WorkQueue<TaskType>* localQueue,
					  WorkQueue<TaskType>* localCEXQueue,
					  Flowpipe<State>& localSegments );

	void computeForwardReachability( const TaskType& task,
									 const Strategy<State>& strat,
									 WorkQueue<TaskType>* localQueue,
									 WorkQueue<TaskType>* localCEXQueue,
									 Flowpipe<State>& localSegments );

	bool isValidTask( const TaskType& task, WorkQueue<TaskType>* localCEXQueue );

  private:
	int mWorkerId;
};

}  // namespace hypro

#include "ContextBasedReachabilityWorker.tpp"
