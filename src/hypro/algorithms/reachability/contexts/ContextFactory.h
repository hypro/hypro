#pragma once
#include "IContext.h"
#include "LTIContext.h"
#include "../workers/IWorker.h"
#include "../../../datastructures/reachability/Settings.h"
#include "../../../datastructures/reachability/Strategy.h"
#include "../../../datastructures/reachability/Task.h"
#include "../../../datastructures/reachability/workQueue/WorkQueue.h"
#include "../../../util/plotting/PlotData.h"
#include "../../../util/logging/Logger.h"

namespace hypro
{
    template<typename State>
    class ContextFactory : public carl::Singleton<ContextFactory<State>>
	{
		using Number = typename State::NumberType;
	    friend carl::Singleton<ContextFactory<State>>;
    public:
        IContext* createContext(const std::shared_ptr<Task<State>>& t,
		                    const Strategy<State>& strat,
		                    WorkQueue<std::shared_ptr<Task<State>>>* localQueue,
		                    WorkQueue<std::shared_ptr<Task<State>>>* localCEXQueue,
		                    std::vector<PlotData<State>>* localSegments,
		                    hypro::ReachabilitySettings &settings);


        // Todo: Add destructor and vector which keeps the pointers to the contexts.
    };

} // hypro

#include "ContextFactory.tpp"
