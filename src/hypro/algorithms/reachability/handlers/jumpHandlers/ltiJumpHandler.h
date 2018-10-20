#pragma once
#include "../IHandler.h"
#include "../../../../datastructures/HybridAutomaton/State.h"
#include "../../../../datastructures/reachability/WorkQueue.h"
#include "../../../../datastructures/reachability/Task.h"
#include "../../../../datastructures/reachability/ReachTreeNode.h"

#include "../HandlerFactory.h"
namespace hypro {

	template<typename Number>
	class ltiJumpHandler : public IJumpHandler {
		std::vector<boost::tuple<Transition<Number>*, State_t<Number>>>* mSuccessorBuffer;
		representation_name mRepresentation;
		std::shared_ptr<Task<Number>> mTask;
		Transition<Number>* mTransition;
		StrategyNode mStrategy;
		WorkQueue<std::shared_ptr<Task<Number>>>* mLocalQueue;
		WorkQueue<std::shared_ptr<Task<Number>>>* mLocalCEXQueue;

	public:
		ltiJumpHandler() = delete;
		ltiJumpHandler(std::vector<boost::tuple<Transition<Number>*, State_t<Number>>>* successorBuffer,
										representation_name representation,
										std::shared_ptr<Task<Number>> task,
										Transition<Number>* transition,
										StrategyNode strategy,
										WorkQueue<std::shared_ptr<Task<Number>>>* localQueue,
										WorkQueue<std::shared_ptr<Task<Number>>>* localCEXQueue) : mStrategy(strategy){
			mSuccessorBuffer = successorBuffer;
			mRepresentation = representation;
			mTask = task;
			mTransition = transition;
			//mStrategy = strategy;
			mLocalQueue = localQueue;
			mLocalCEXQueue = localCEXQueue;			
		}
		
		void handle();
		const char* handlerName() {return "ltiJumpHandler";}
		std::map<Transition<Number>*, std::vector<State_t<Number>>> aggregate(const std::vector<boost::tuple<Transition<Number>*, State_t<Number>>>& states, Transition<Number>* transition, const StrategyNode& strategy);
		typename ReachTreeNode<Number>::NodeList_t createNodesFromStates(Transition<Number>* transition, const std::vector<State_t<Number>>& states, representation_name repName, std::size_t targetLevel, carl::Interval<tNumber>& coveredTimeInterval, typename ReachTreeNode<Number>::Node_t parent);

	};
} // hypro

#include "ltiJumpHandler.tpp"