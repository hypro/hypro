#pragma once

#include "IWorker.h"
#include "../contexts/Exceptions.h"
#include "../contexts/IContext.h"
#include "../contexts/ContextFactory.h"
#include "../../../datastructures/reachability/Task.h"
#include "../../../datastructures/reachability/Settings.h"
#include "../../../datastructures/reachability/workQueue/WorkQueue.h"

#include "../../../util/logging/Logger.h"
#include "../../../util/plotting/PlotData.h"

#include "../../../datastructures/HybridAutomaton/decomposition/DecisionEntity.h"

#include <vector>

namespace hypro
{

template<typename State>
class ContextBasedReachabilityWorker : public IWorker<std::shared_ptr<Task<State>>,State>
{
    using Number = typename State::NumberType;
public:
    ContextBasedReachabilityWorker(const ReachabilitySettings &settings) : IWorker<std::shared_ptr<Task<State>>,State>(settings) {
    }

    ~ContextBasedReachabilityWorker() {
    }

    void processTask(const std::shared_ptr<Task<State>>& t,
            const Strategy<State>& strat,
            WorkQueue<std::shared_ptr<Task<State>>>& localQueue,
            WorkQueue<std::shared_ptr<Task<State>>>& localCEXQueue,
            std::vector<PlotData<Number>>* localSegments
            );

    void computeForwardReachability(const std::shared_ptr<Task<State>>& task,
                                    const Strategy<State>& strat,
                                    WorkQueue<std::shared_ptr<Task<State>>>& localQueue,
                                    WorkQueue<std::shared_ptr<Task<State>>>& localCEXQueue,
                                    std::vector<PlotData<Number>>* localSegments);

    bool isValidTask(const std::shared_ptr<Task<State>>& task, WorkQueue<std::shared_ptr<Task<State>>>& localCEXQueue);

private:
    int mWorkerId;
};

}  // hypro

#include "ContextBasedReachabilityWorker.tpp"