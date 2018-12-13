#include "rectangularBadStateHandler.h"

namespace hypro {
    template<typename State>
	void rectangularBadStateHandler<State>::handle() {

		auto& vpool = hypro::VariablePool::getInstance();
		auto& automaton = SettingsProvider<State>::getInstance().getHybridAutomaton();

		TRACE("hydra.worker.continuous","Having a total of " << automaton.getLocalBadStates().size() << " local bad states.");
	    auto localBadState = automaton.getLocalBadStates().find(mState->getLocation());
	   	if(localBadState != automaton.getLocalBadStates().end()){
			TRACE("hydra.worker.continuous","Checking local bad state: " << localBadState->second);

			// create constraints for invariant. Note that we need to properly match dimension indices with variable names at some point.
			// create carlPolytope, as intersection is defined for those
			CarlPolytopeT<typename State::NumberType> badStateConstraints{localBadState->second.getMatrix(mIndex), localBadState->second.getVector(mIndex)};
			// substitute variables in the formulas by the correct ones in the subspace of the state
			// 1. Determine offset
			std::size_t dimensionOffset = mState->getDimensionOffset(mIndex);
			// 2. substitute
			for(std::size_t i = 0; i < mState->getDimension(mIndex); ++i){
				badStateConstraints.substituteVariable(vpool.carlVarByIndex(i), vpool.carlVarByIndex(i+dimensionOffset));
			}

			// intersect
			auto resultingSet = boost::get<CarlPolytopeT<typename State::NumberType>>(mState->getSet(mIndex)).intersect(badStateConstraints);

			// reduction
			resultingSet.reduceRepresentation();

			// set containment information
			if(resultingSet.empty()) {
				mContainment = CONTAINMENT::NO;
			} else {
				mContainment = CONTAINMENT::YES;
			}

			if(mContainment != hypro::CONTAINMENT::NO) {
		    	DEBUG("hydra.worker","Intersection with local bad states. (intersection type " << badStatePair.first << ")");
		    	return;
		    }
		}

	    TRACE("hydra.worker.continuous", "No intersection with local, continuous bad states");

	    // check global bad states
	    for (const auto& badState : automaton.getGlobalBadStates()) {
	    	if(badState.getMatrix(mIndex).rows() != 0){
	    		// at least one global bad state in this subspace
		        // create constraints for invariant. Note that we need to properly match dimension indices with variable names at some point.
				// create carlPolytope, as intersection is defined for those
				CarlPolytopeT<typename State::NumberType> badStateConstraints{badState.getMatrix(mIndex), badState.getVector(mIndex)};
				// substitute variables in the formulas by the correct ones in the subspace of the state
				// 1. Determine offset
				std::size_t dimensionOffset = mState->getDimensionOffset(mIndex);
				// 2. substitute
				for(std::size_t i = 0; i < mState->getDimension(mIndex); ++i){
					badStateConstraints.substituteVariable(vpool.carlVarByIndex(i), vpool.carlVarByIndex(i+dimensionOffset));
				}

				// intersect
				auto resultingSet = boost::get<CarlPolytopeT<typename State::NumberType>>(mState->getSet(mIndex)).intersect(badStateConstraints);

				// reduction
				resultingSet.reduceRepresentation();

				// set containment information
				if(resultingSet.empty()) {
					mContainment = CONTAINMENT::NO;
				} else {
					mContainment = CONTAINMENT::YES;
				}

				if(mContainment != hypro::CONTAINMENT::NO) {
					DEBUG("hydra.worker","Intersection with global bad states.");
					return;
				}
		    }
		}
	    mContainment = CONTAINMENT::NO;
	}
} // hypro
