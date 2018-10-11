#include "ContextFactory.h"

namespace hypro {
    template<typename Number>
    IContext* ContextFactory<Number>::createContext(const std::shared_ptr<Task<Number>>& t,
		                    const std::vector<StrategyNode>& strat,
		                    WorkQueue<std::shared_ptr<Task<Number>>>* localQueue,
		                    WorkQueue<std::shared_ptr<Task<Number>>>* localCEXQueue,
		                    std::vector<PlotData<Number>>* localSegments,
		                    hypro::ReachabilitySettings<tNumber> &settings)
    {
        /*
        if(SettingsProvider::getInstance().useDecider() && SettingsProvider::getInstance().getLocationTypeMap().find(t->treeNode->getStateAtLevel(t->btInfo.btLevel).getLocation())->second == hydra::LOCATIONTYPE::TIMEDLOC){				
			// either use on full timed automa or if context switch is enabled
			if(SettingsProvider::getInstance().isFullTimed() || SettingsProvider::getInstance().useContextSwitch()){
				DEBUG("hydra.worker", "Using full timed context!");
				return new FullTimedContext(t,strat,localQueue,localCEXQueue,localSegments,settings);
			}
		}
        */
		DEBUG("hydra.worker", "Using standard LTI context!");
		return new LTIContext<Number>(t,strat,localQueue,localCEXQueue,localSegments,settings);
    }


} // hypro