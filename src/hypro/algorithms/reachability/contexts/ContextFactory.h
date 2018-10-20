#pragma once
#include "IContext.h"
#include "LTIContext.h"
#include "../workers/IWorker.h"
#include "../../../datastructures/reachability/Settings.h"
#include "../../../datastructures/reachability/Task.h"
#include "../../../datastructures/reachability/workQueue/WorkQueue.h"
#include "../../../util/PlotData.h"
#include "../../../util/logging/Logger.h"

namespace hypro
{
    template<typename Number>
    class ContextFactory : public carl::Singleton<ContextFactory<Number>>
	{
	    friend carl::Singleton<ContextFactory<Number>>;
    public:
        IContext* createContext(const std::shared_ptr<Task<Number>>& t,
		                    const std::vector<StrategyNode>& strat,
		                    WorkQueue<std::shared_ptr<Task<Number>>>* localQueue,
		                    WorkQueue<std::shared_ptr<Task<Number>>>* localCEXQueue,
		                    std::vector<PlotData<Number>>* localSegments,
		                    hypro::ReachabilitySettings &settings);


        // Todo: Add destructor and vector which keeps the pointers to the contexts.
    };
    
} // hypro

#include "ContextFactory.tpp"
