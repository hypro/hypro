#pragma once
#include "../../../datastructures/reachability/workQueue/WorkQueueManager.h"
#include "../workers/LTIWorker.h"

namespace hypro {

template <typename State>
class LTIAnalyzer {
	using TaskPtr = std::unique_ptr<Task<State>>;

  public:
	LTIAnalyzer();

	void run();

  protected:
	WorkQueue<TaskPtr> mWorkQueue;
};

}  // namespace hypro

#include "LTIAnalyzer.tpp"
