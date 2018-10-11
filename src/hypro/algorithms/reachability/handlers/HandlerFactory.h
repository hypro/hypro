#pragma once
#include "IHandler.h"
#include "firstSegmentHandlers/FirstSegmentHandlers.h"
#include "invariantHandlers/InvariantHandlers.h"
#include "badStateHandlers/BadStateHandlers.h"
#include "guardHandlers/GuardHandlers.h"
#include "timeEvolutionHandlers/TimeEvolutionHandlers.h"
#include "resetHandlers/ResetHandlers.h"
#include "jumpHandlers/JumpHandlers.h"

namespace hypro
{
	template<typename Number>
	class HandlerFactory : public carl::Singleton<HandlerFactory<Number>>
	{
	  friend carl::Singleton<HandlerFactory<Number>>;

	public:
		IFirstSegmentHandler<Number>* buildFirstSegmentHandler(representation_name name, State_t<Number>* state, size_t index, tNumber timeStep);
		IInvariantHandler* buildInvariantHandler(representation_name name, State_t<Number>* state, size_t index, bool noFlow);
		IBadStateHandler* buildBadStateHandler(representation_name name, State_t<Number>* state, size_t index, bool noFlow);
		IGuardHandler<Number>* buildGuardHandler(representation_name name, std::shared_ptr<State_t<Number>> state, size_t index, Transition<Number>* transition, bool noFlow);
		ITimeEvolutionHandler* buildContinuousEvolutionHandler(representation_name name, State_t<Number>* state, size_t index, tNumber timeStep, tNumber timeBound, matrix_t<Number> trafo, vector_t<Number> translation);
		IResetHandler* buildResetHandler(representation_name name, State_t<Number>* state, size_t index, matrix_t<Number> trafo, vector_t<Number> translation);

		IJumpHandler* buildDiscreteSuccessorHandler(std::vector<boost::tuple<Transition<Number>*, State_t<Number>>>* successorBuffer,
										representation_name representation,
										std::shared_ptr<Task<Number>> task,
										Transition<Number>* transition,
										StrategyNode strategy,
										WorkQueue<std::shared_ptr<Task<Number>>>* localQueue,
										WorkQueue<std::shared_ptr<Task<Number>>>* localCEXQueue);
	};
} // hypro

#include "HandlerFactory.tpp"
