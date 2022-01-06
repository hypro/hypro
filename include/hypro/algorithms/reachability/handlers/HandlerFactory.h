#pragma once
#include "../../../datastructures/HybridAutomaton/Location.h"
#include "../../../datastructures/reachability/timing/EventTimingNode.h"
#include "../../../datastructures/reachability/workQueue/WorkQueue.h"
#include "IHandler.h"
#include "forwardDeclarations.h"

namespace hypro {

template <typename State>
class HandlerFactory : public carl::Singleton<HandlerFactory<State>> {
	friend carl::Singleton<HandlerFactory<State>>;
	using Number = typename State::NumberType;

  public:
	IFirstSegmentHandler<State>* buildFirstSegmentHandler( representation_name name, State* state, size_t index, tNumber timeStep );
	IInvariantHandler* buildInvariantHandler( representation_name name, State* state, size_t index, bool noFlow );
	IBadStateHandler* buildBadStateHandler( representation_name name, State* state, size_t index, bool noFlow );
	IGuardHandler<State>* buildGuardHandler( representation_name name, std::shared_ptr<State> state, size_t index, Transition<Number>* transition, bool noFlow );
	ITimeEvolutionHandler* buildContinuousEvolutionHandler( representation_name name, State* state, size_t index, tNumber timeStep, tNumber timeBound, flowVariant<Number> flow );
	IResetHandler* buildResetHandler( representation_name name, State* state, size_t index, matrix_t<Number> trafo, vector_t<Number> translation );
	IResetHandler* buildResetHandler( representation_name name, State* state, size_t index, const std::vector<carl::Interval<Number>>& assignments );

	IJumpHandler* buildDiscreteSuccessorHandler( std::vector<std::tuple<Transition<Number>*, State>>* successorBuffer,
												 std::shared_ptr<Task<State>> task,
												 Transition<Number>* transition,
												 StrategyParameters sPars,
												 WorkQueue<std::shared_ptr<Task<State>>>* localQueue,
												 WorkQueue<std::shared_ptr<Task<State>>>* localCEXQueue,
												 const EventTimingContainer<typename State::NumberType>& timings );
};
}  // namespace hypro

#include "HandlerFactory.tpp"
#include "badStateHandlers/BadStateHandlers.h"
#include "firstSegmentHandlers/FirstSegmentHandlers.h"
#include "guardHandlers/GuardHandlers.h"
#include "invariantHandlers/InvariantHandlers.h"
#include "jumpHandlers/JumpHandlers.h"
#include "resetHandlers/ResetHandlers.h"
#include "timeEvolutionHandlers/TimeEvolutionHandlers.h"
