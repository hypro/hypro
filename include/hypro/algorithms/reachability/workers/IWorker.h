#pragma once

#include "../../../datastructures/reachability/Flowpipe.h"
#include "../../../datastructures/reachability/Settings.h"
#include "../../../datastructures/reachability/StrategyNode.h"
#include "../../../datastructures/reachability/Task.h"
#include "../../../datastructures/reachability/workQueue/WorkQueue.h"
#include "../../../types.h"

namespace hypro {
template <class Workable, typename State>
class IWorker {
  public:
	using Number = typename State::NumberType;
	using TaskType = std::shared_ptr<Task<State>>;
	/**
	 * Constructor responsible for setting the respective EventHandler
	 * and WorkQueue.
	 */
	IWorker( const ReachabilitySettings& settings )
		: mSettings( settings ) {}

	virtual ~IWorker() {}
	/**
	 * abstract definition of the function responsible for
	 * Flowpipe computation. It is important that the Workable class
	 * has a constructor taking a Flowpipe! this way new Workable Elements
	 * can be constructed, which then will be added to the WorkQueue.
	 */
	virtual void processTask( const Workable& w,
							  const Strategy<State>& strategy,
							  WorkQueue<TaskType>* localQueue,
							  WorkQueue<TaskType>* localCEXQueue,
							  Flowpipe<State>& localSegments ) = 0;

	bool detectedUnsafety() const { return isUnsafe; }

  protected:
	ReachabilitySettings mSettings;
	bool isUnsafe = false;
};

}  // namespace hypro
