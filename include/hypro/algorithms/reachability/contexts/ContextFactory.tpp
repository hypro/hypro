#include "ContextFactory.h"

namespace hypro {
template <typename State>
IContext* ContextFactory<State>::createContext( const std::shared_ptr<Task<State>>& t,
												const Strategy<State>& strat,
												WorkQueue<std::shared_ptr<Task<State>>>* localQueue,
												WorkQueue<std::shared_ptr<Task<State>>>* localCEXQueue,
												Flowpipe<State>& localSegments,
												hypro::ReachabilitySettings& settings ) {
	if ( SettingsProvider<State>::getInstance().getStrategy().getParameters( t->btInfo.btLevel ).representation_type == representation_name::polytope_t ) {
		DEBUG( "hydra.worker", "Using TPoly context!" );
		return new TemplatePolyhedronContext<State>( t, strat, localQueue, localCEXQueue, localSegments, settings );
	}
	if ( SettingsProvider<State>::getInstance().useDecider() ) {
		auto locType = SettingsProvider<State>::getInstance().getLocationTypeMap().find( t->treeNode->getStateAtLevel( t->btInfo.btLevel ).getLocation() )->second;
		if ( locType == hypro::LOCATIONTYPE::TIMEDLOC ) {
			// either use on full timed automa or if context switch is enabled
			if ( SettingsProvider<State>::getInstance().isFullTimed() || SettingsProvider<State>::getInstance().useContextSwitch() ) {
				DEBUG( "hydra.worker", "Using full timed context!" );
				return new TimedContext<State>( t, strat, localQueue, localCEXQueue, localSegments, settings );
			}
		} else if ( locType == hypro::LOCATIONTYPE::RECTANGULARLOC ) {
			DEBUG( "hydra.worker", "Using lti context, but actually is rectangular!" );
			return new LTIContext<State>( t, strat, localQueue, localCEXQueue, localSegments, settings );
		}
	}
	DEBUG( "hydra.worker", "Using standard LTI context!" );
	return new LTIContext<State>( t, strat, localQueue, localCEXQueue, localSegments, settings );
}

}  // namespace hypro
