#pragma once

#include "IWorker.h"
#include "../contexts/Exceptions.h"
#include "../contexts/IContext.h"
#include "../contexts/ContextFactory.h"
#include "../../../datastructures/reachability/WorkQueue.h"
#include "../../../datastructures/reachability/Task.h"
#include "../../../datastructures/reachability/Settings.h"

#include "../../../util/logging/Logger.h"
#include "../../../util/PlotData.h"

#include "../../../datastructures/HybridAutomaton/decomposition/DecisionEntity.h"

#include <vector>

namespace hypro
{

template<typename Number>
class ContextBasedReachabilityWorker : public IWorker<std::shared_ptr<Task<Number>>,Number>
{
public:
    ContextBasedReachabilityWorker(const hypro::ReachabilitySettings &settings) : IWorker<std::shared_ptr<Task<Number>>,Number>(settings) {
    }

    ~ContextBasedReachabilityWorker() {
    }

    void processTask(const std::shared_ptr<Task<Number>>& t,
            const std::vector<StrategyNode>& strat,
            WorkQueue<std::shared_ptr<Task<Number>>>& localQueue,
            WorkQueue<std::shared_ptr<Task<Number>>>& localCEXQueue,
            std::vector<PlotData<Number>>* localSegments
            );
    

    void computeForwardReachability(const std::shared_ptr<Task<Number>>& task,
                                    const std::vector<StrategyNode>& strat,
                                    WorkQueue<std::shared_ptr<Task<Number>>>& localQueue,
                                    WorkQueue<std::shared_ptr<Task<Number>>>& localCEXQueue,
                                    std::vector<PlotData<Number>>* localSegments);

    bool isValidTask(const std::shared_ptr<Task<Number>>& task, WorkQueue<std::shared_ptr<Task<Number>>>& localCEXQueue);

private:
    int mWorkerId;
};

}  // hypro

#include "ContextBasedReachabilityWorker.tpp"