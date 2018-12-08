#include "ContextFactory.h"

namespace hypro {
    template<typename State>
    IContext* ContextFactory<State>::createContext(const std::shared_ptr<Task<State>>& t,
		                    const Strategy<State>& strat,
		                    WorkQueue<std::shared_ptr<Task<State>>>* localQueue,
		                    WorkQueue<std::shared_ptr<Task<State>>>* localCEXQueue,
		                    std::vector<PlotData<State>>* localSegments,
		                    hypro::ReachabilitySettings &settings)
    {

        if(SettingsProvider<State>::getInstance().useDecider() && SettingsProvider<State>::getInstance().getLocationTypeMap().find(t->treeNode->getStateAtLevel(t->btInfo.btLevel).getLocation())->second == hypro::LOCATIONTYPE::TIMEDLOC){
			// either use on full timed automa or if context switch is enabled
			if(SettingsProvider<State>::getInstance().isFullTimed() || SettingsProvider<State>::getInstance().useContextSwitch()){
				DEBUG("hydra.worker", "Using full timed context!");
				return new TimedContext<State>(t,strat,localQueue,localCEXQueue,localSegments,settings);
			}
		}
		DEBUG("hydra.worker", "Using standard LTI context!");
		return new LTIContext<State>(t,strat,localQueue,localCEXQueue,localSegments,settings);
    }


} // hypro
