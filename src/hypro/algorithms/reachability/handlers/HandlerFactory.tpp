#include "HandlerFactory.h"

namespace hypro
{

	template<typename Number>
	IFirstSegmentHandler<Number>* HandlerFactory<Number>::buildFirstSegmentHandler(representation_name name, State_t<Number>* state, size_t index, tNumber timeStep){

		switch(name){
 			case representation_name::box: {
 				return new ltiFirstSegmentHandler<Box<Number>,Number>(state,index,timeStep);
 			}
 			case representation_name::polytope_h: {
 				return new ltiFirstSegmentHandler<HPolytope<Number>,Number>(state,index,timeStep);
 			}
 			case representation_name::polytope_v: {
 				return new ltiFirstSegmentHandler<VPolytope<Number>,Number>(state,index,timeStep);
 			}
 			case representation_name::zonotope: {
 				return new ltiFirstSegmentHandler<Zonotope<Number>,Number>(state,index,timeStep);
 			}
 			case representation_name::support_function: {
 				return new ltiFirstSegmentHandler<SupportFunction<Number>,Number>(state,index,timeStep);
 			}
 			case representation_name::difference_bounds: {
				if(SettingsProvider<Number>::getInstance().useDecider() && SettingsProvider<Number>::getInstance().getLocationTypeMap().find(state->getLocation())->second == LOCATIONTYPE::TIMEDLOC){				
 					if(SettingsProvider<Number>::getInstance().isFullTimed() ){
	 					return new timedElapseFirstSegmentHandler<DifferenceBounds<Number>,Number>(state,index,timeStep);
 					}
 				}
 				return new timedFirstSegmentHandler<DifferenceBounds<Number>,Number>(state,index,timeStep);
 			}
 		}
 		assert(false && "SHOULD NEVER REACH THIS");
 		return nullptr;
	}


	template<typename Number>
	IInvariantHandler* HandlerFactory<Number>::buildInvariantHandler(representation_name name, State_t<Number>* state, size_t index, bool noFlow){

		if(state->getLocation()->getInvariant().size() == 0 || state->getLocation()->getInvariant().getMatrix(index).rows() == 0){ 	
			// no constraints, always full containment
			return nullptr;
		}

		switch(name){
 			case representation_name::box: {
 				if(noFlow){
 					return new discreteInvariantHandler<Box<Number>,Number>(state,index);
 				}
 				return new ltiInvariantHandler<Box<Number>,Number>(state,index);
 			}
 			case representation_name::polytope_h: {
 				if(noFlow){
 					return new discreteInvariantHandler<HPolytope<Number>,Number>(state,index);
 				}
 				return new ltiInvariantHandler<HPolytope<Number>,Number>(state,index);
 			}
 			case representation_name::polytope_v: {
 				if(noFlow){
 					return new discreteInvariantHandler<VPolytope<Number>,Number>(state,index);
 				}
 				return new ltiInvariantHandler<VPolytope<Number>,Number>(state,index);
 			}
 			case representation_name::zonotope: {
 				if(noFlow){
 					return new discreteInvariantHandler<Zonotope<Number>,Number>(state,index);
 				}
 				return new ltiInvariantHandler<Zonotope<Number>,Number>(state,index);
 			}
 			case representation_name::support_function: {
 				if(noFlow){
 					return new discreteInvariantHandler<SupportFunction<Number>,Number>(state,index);
 				}
 				return new ltiInvariantHandler<SupportFunction<Number>,Number>(state,index);
 			}
 			case representation_name::difference_bounds: {
 				if(noFlow){
 					return new discreteInvariantHandler<DifferenceBounds<Number>,Number>(state,index);
 				}
 				return new timedInvariantHandler<DifferenceBounds<Number>,Number>(state,index);
 			}
 		}
 		assert(false && "SHOULD NEVER REACH THIS");
 		return nullptr;
	}

	template<typename Number>
	IBadStateHandler* HandlerFactory<Number>::buildBadStateHandler(representation_name name, State_t<Number>* state, size_t index, bool noFlow){
		auto localBadState = SettingsProvider<Number>::getInstance().getHybridAutomaton().getLocalBadStates().find(state->getLocation());
		// no local bad states for this location or subspace
		bool noLocalBadStates = (localBadState == SettingsProvider<Number>::getInstance().getHybridAutomaton().getLocalBadStates().end() || localBadState->second.getMatrix(index).rows() == 0);
		
		// for each global bad state, check if it has constraints in this subspace
		bool noGlobalBadStates = true;
		for (const auto& badState : SettingsProvider<Number>::getInstance().getHybridAutomaton().getGlobalBadStates()) {
	    	if(badState.getMatrix(index).rows() != 0){
	    		noGlobalBadStates = false;
	    		break;
	    	}
	    }

	    if(noLocalBadStates && noGlobalBadStates){
	    	return nullptr;
	    }

		switch(name){
 			case representation_name::box: {
 				if(noFlow){
 					return new discreteBadStateHandler<Box<Number>,Number>(state,index);
 				}
 				return new ltiBadStateHandler<Box<Number>,Number>(state,index);
 			}
 			case representation_name::polytope_h: {			
 				if(noFlow){
 					return new discreteBadStateHandler<HPolytope<Number>,Number>(state,index);
 				}
 				return new ltiBadStateHandler<HPolytope<Number>,Number>(state,index);
 			}
 			case representation_name::polytope_v: { 				
 				if(noFlow){
 					return new discreteBadStateHandler<VPolytope<Number>,Number>(state,index);
 				}
 				return new ltiBadStateHandler<VPolytope<Number>,Number>(state,index);
 			}
 			case representation_name::zonotope: {
 				if(noFlow){
 					return new discreteBadStateHandler<Zonotope<Number>,Number>(state,index);
 				}
 				return new ltiBadStateHandler<Zonotope<Number>,Number>(state,index);
 			}
 			case representation_name::support_function: {
 				if(noFlow){
 					return new discreteBadStateHandler<SupportFunction<Number>,Number>(state,index);
 				}
 				return new ltiBadStateHandler<SupportFunction<Number>,Number>(state,index);
 			}
 			case representation_name::difference_bounds: {
 				if(noFlow){
 					return new discreteBadStateHandler<DifferenceBounds<Number>,Number>(state,index);
 				}
 				return new timedBadStateHandler<DifferenceBounds<Number>,Number>(state,index);
 			}
 		}
 		assert(false && "SHOULD NEVER REACH THIS");
 		return nullptr;
	}

	template<typename Number>
	IGuardHandler<Number>* HandlerFactory<Number>::buildGuardHandler(representation_name name, std::shared_ptr<State_t<Number>> state, size_t index, Transition<Number>* transition, bool noFlow){
		if(transition->getGuard().size() == 0 || transition->getGuard().getMatrix(index).rows() == 0){
			// no constraints for this subspace
			return nullptr;
		}

		switch(name){
 			case representation_name::box: {
 				if(noFlow){
 					return new discreteGuardHandler<Box<Number>,Number>(state,index,transition);
 				}
 				return new ltiGuardHandler<Box<Number>,Number>(state,index,transition);
 			}
 			case representation_name::polytope_h: {
 				if(noFlow){
 					return new discreteGuardHandler<HPolytope<Number>,Number>(state,index,transition);
 				}
 				return new ltiGuardHandler<HPolytope<Number>,Number>(state,index,transition);
 			}
 			case representation_name::polytope_v: {
 				if(noFlow){
 					return new discreteGuardHandler<VPolytope<Number>,Number>(state,index,transition);
 				}
 				return new ltiGuardHandler<VPolytope<Number>,Number>(state,index,transition);
 			}
 			case representation_name::zonotope: {
 				if(noFlow){
 					return new discreteGuardHandler<Zonotope<Number>,Number>(state,index,transition);
 				}
 				return new ltiGuardHandler<Zonotope<Number>,Number>(state,index,transition);
 			}
 			case representation_name::support_function: {
 				if(noFlow){
 					return new discreteGuardHandler<SupportFunction<Number>,Number>(state,index,transition);
 				}
 				return new ltiGuardHandler<SupportFunction<Number>,Number>(state,index,transition);
 			}
 			case representation_name::difference_bounds: {
 				if(noFlow){
 					return new discreteGuardHandler<DifferenceBounds<Number>,Number>(state,index,transition);
 				}
 				return new timedGuardHandler<DifferenceBounds<Number>,Number>(state,index,transition);
 			}
 		}
 		assert(false && "SHOULD NEVER REACH THIS");
 		return nullptr;
	}

	template<typename Number>
	ITimeEvolutionHandler* HandlerFactory<Number>::buildContinuousEvolutionHandler(representation_name name, State_t<Number>* state, size_t index, tNumber timeStep, tNumber timeBound, matrix_t<Number> trafo, vector_t<Number> translation){
		if(trafo == matrix_t<Number>::Identity(trafo.rows(),trafo.rows()) && translation == vector_t<Number>::Zero(trafo.rows())){
			return nullptr;
		}

		switch(name){
 			case representation_name::box: {
 				return new ltiTimeEvolutionHandler<Box<Number>,Number>(state,index,timeStep,trafo,translation);
 			}
 			case representation_name::polytope_h: {
 				return new ltiTimeEvolutionHandler<HPolytope<Number>,Number>(state,index,timeStep,trafo,translation);
 			}
 			case representation_name::polytope_v: {
 				return new ltiTimeEvolutionHandler<VPolytope<Number>,Number>(state,index,timeStep,trafo,translation);
 			}
 			case representation_name::zonotope: {
 				return new ltiTimeEvolutionHandler<Zonotope<Number>,Number>(state,index,timeStep,trafo,translation);
 			}
 			case representation_name::support_function: {
 				return new ltiTimeEvolutionHandler<SupportFunction<Number>,Number>(state,index,timeStep,trafo,translation);
 			}
 			case representation_name::difference_bounds: {
 				if(SettingsProvider<Number>::getInstance().useDecider() && SettingsProvider<Number>::getInstance().getLocationTypeMap().find(state->getLocation())->second == LOCATIONTYPE::TIMEDLOC){	
					if(SettingsProvider<Number>::getInstance().isFullTimed()){
						return new timedElapseTimeEvolutionHandler<DifferenceBounds<Number>,Number>(state,index,timeStep,timeBound,trafo,translation);
					}
					// on mixed contexts a first segment with tick was computed
					else if(SettingsProvider<Number>::getInstance().useContextSwitch()){
						return new timedElapseAfterTickTimeEvolutionHandler<DifferenceBounds<Number>,Number>(state,index,timeStep,timeBound,trafo,translation);
					}
				}
 				return new timedTickTimeEvolutionHandler<DifferenceBounds<Number>,Number>(state,index,timeStep,trafo,translation);
 			}
 		}
 		assert(false && "SHOULD NEVER REACH THIS");
 		return nullptr;
	}

	template<typename Number>
	IResetHandler* HandlerFactory<Number>::buildResetHandler(representation_name name, State_t<Number>* state, size_t index,matrix_t<Number> trafo, vector_t<Number> translation){
		if(trafo.rows() == 0 || (trafo == matrix_t<Number>::Identity(trafo.rows(),trafo.rows()) && translation == vector_t<Number>::Zero(translation.rows()))){
			return nullptr;
		}

		switch(name){
 			case representation_name::box: {
 				return new ltiResetHandler<Box<Number>,Number>(state,index,trafo,translation);
 			}
 			case representation_name::polytope_h: {
 				return new ltiResetHandler<HPolytope<Number>,Number>(state,index,trafo,translation);
 			}
 			case representation_name::polytope_v: {
 				return new ltiResetHandler<VPolytope<Number>,Number>(state,index,trafo,translation);
 			}
 			case representation_name::zonotope: {
 				return new ltiResetHandler<Zonotope<Number>,Number>(state,index,trafo,translation);
 			}
 			case representation_name::support_function: {
 				return new ltiResetHandler<SupportFunction<Number>,Number>(state,index,trafo,translation);
 			}
 			case representation_name::difference_bounds: {
 				return new timedResetHandler<DifferenceBounds<Number>,Number>(state,index,trafo,translation);
 			}
 		}
 		assert(false && "SHOULD NEVER REACH THIS");
 		return nullptr;
	}



	template<typename Number>
	IJumpHandler* HandlerFactory<Number>::buildDiscreteSuccessorHandler(std::vector<boost::tuple<Transition<Number>*, State_t<Number>>>* successorBuffer,
										representation_name representation,
										std::shared_ptr<Task<Number>> task,
										Transition<Number>* transition,
										StrategyNode strategy,
										WorkQueue<std::shared_ptr<Task<Number>>>* localQueue,
										WorkQueue<std::shared_ptr<Task<Number>>>* localCEXQueue){
		return new ltiJumpHandler<Number>(successorBuffer, representation, task,transition, strategy, localQueue, localCEXQueue);		
	}

} // hypro
