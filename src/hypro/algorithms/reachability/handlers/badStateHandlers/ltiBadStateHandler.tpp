#include "ltiBadStateHandler.h"

namespace hypro {
    template <class Representation,typename Number>
	void ltiBadStateHandler<Representation,Number>::handle() {
		
	    TRACE("hydra.worker.continuous","Having a total of " << SettingsProvider<Number>::getInstance().getHybridAutomaton().getLocalBadStates().size() << " local bad states.");
	    auto localBadState = SettingsProvider<Number>::getInstance().getHybridAutomaton().getLocalBadStates().find(mState->getLocation());
	   	if(localBadState != SettingsProvider<Number>::getInstance().getHybridAutomaton().getLocalBadStates().end()){
			TRACE("hydra.worker.continuous","Checking local bad state: " << localBadState->second);
			std::pair<CONTAINMENT,State_t<Number>> badStatePair = mState->partiallySatisfies(localBadState->second, mIndex);
		    if(badStatePair.first != hypro::CONTAINMENT::NO) {
		    	DEBUG("hydra.worker","Intersection with local bad states. (intersection type " << badStatePair.first << ")");
		    	hypro::Box<Number> tmp = hypro::Converter<Number>::toBox(boost::get<Representation>(mState->getSet(mIndex)));
		    	TRACE("hydra.worker", "Intersecting box: " << tmp);
		    	mIntersects = true;
		    	return;
		    }
		}
	    TRACE("hydra.worker.continuous", "No intersection with local, continuous bad states");

	    // check global bad states
	    for (const auto& badState : SettingsProvider<Number>::getInstance().getHybridAutomaton().getGlobalBadStates()) {
	    	if(badState.getMatrix(mIndex).rows() != 0){
	    		// at least one global bad state in this subspace
		        std::pair<CONTAINMENT,State_t<Number>> badStatePair = mState->partiallySatisfies(badState, mIndex);
		        if (badStatePair.first != CONTAINMENT::NO) {
		            DEBUG("hydra.worker", "Intersection with global bad states");
		            mIntersects = true;
			    	return;
		        }
		    }
		}
	    mIntersects = false;
	}
} // hypro